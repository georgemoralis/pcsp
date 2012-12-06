#include "stdafx.h"

#include "common_base.h"
#include "ge_DisplayListInterpreter.h"
#include "ge_Context.h"
#include "ge_Constants.h"
#include "ge_Matrix.h"
#include "ge_Decoder.h"
#include "ge_TextureManager.h"

#include "memory/memory.h"
#include "log.h"

#include "renderer.h"

#include "opengl/gl_Uniforms.h"

inline float getFloat24(u32 data){ data<<=8; return *(float*)(&data);}

static int cntr = 1;




#define PSP_GE_SIGNAL_HANDLER_SUSPEND  0x01
#define PSP_GE_SIGNAL_HANDLER_CONTINUE 0x02
#define PSP_GE_SIGNAL_HANDLER_PAUSE    0x03
#define PSP_GE_SIGNAL_SYNC             0x08
#define PSP_GE_SIGNAL_JUMP             0x10
#define PSP_GE_SIGNAL_CALL             0x11
#define PSP_GE_SIGNAL_RETURN           0x12
#define PSP_GE_SIGNAL_TBP0_REL         0x20
#define PSP_GE_SIGNAL_TBP1_REL         0x21
#define PSP_GE_SIGNAL_TBP2_REL         0x22
#define PSP_GE_SIGNAL_TBP3_REL         0x23
#define PSP_GE_SIGNAL_TBP4_REL         0x24
#define PSP_GE_SIGNAL_TBP5_REL         0x25
#define PSP_GE_SIGNAL_TBP6_REL         0x26
#define PSP_GE_SIGNAL_TBP7_REL         0x27
#define PSP_GE_SIGNAL_TBP0_REL_OFFSET  0x28
#define PSP_GE_SIGNAL_TBP1_REL_OFFSET  0x29
#define PSP_GE_SIGNAL_TBP2_REL_OFFSET  0x2A
#define PSP_GE_SIGNAL_TBP3_REL_OFFSET  0x2B
#define PSP_GE_SIGNAL_TBP4_REL_OFFSET  0x2C
#define PSP_GE_SIGNAL_TBP5_REL_OFFSET  0x2D
#define PSP_GE_SIGNAL_TBP6_REL_OFFSET  0x2E
#define PSP_GE_SIGNAL_TBP7_REL_OFFSET  0x2F
#define PSP_GE_SIGNAL_BREAK            0xFF

ge_DisplayListInterpreter	theDisplayInterpreter;

ge_DisplayListInterpreter::ge_DisplayListInterpreter()
{
}

ge_DisplayListInterpreter::~ge_DisplayListInterpreter()
{

}

u32 ge_DisplayListInterpreter::Add(u32 inListPC, u32 inStallAddr)
{
	DisplayList theList;
	
	theList.id		= cntr++;
	theList.pc		= inListPC & Memory::address_mask;
	theList.stall_addr	= inStallAddr & Memory::address_mask;
	
	mDisplayLists.push_back(theList);
	
	if (!InterpretDisplayLists())
		return theList.id;
	else
		return 0;
}

void ge_DisplayListInterpreter::UpdateStall(int inListId, u32 inNewStall)
{
	for (std::vector<DisplayList>::iterator iter = mDisplayLists.begin(); iter != mDisplayLists.end(); iter++)
	{
		DisplayList &l = *iter;
		if (l.id == inListId)
		{
			l.stall_addr = inNewStall & Memory::address_mask;
		}
	}
	
	InterpretDisplayLists();
}

bool ge_DisplayListInterpreter::InterpretDisplayLists()
{
	std::vector<DisplayList>::iterator iter = mDisplayLists.begin();
	while (!(iter == mDisplayLists.end()))
	{
		DisplayList &l		= *iter;
		
		if (InterpretDisplayList(l))
		{
			mDisplayLists.erase(iter);
			iter = mDisplayLists.begin();
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool ge_DisplayListInterpreter::InterpretDisplayList(DisplayList &list)
{
	u32 memory_operation	= 0;
	u32 data				= 0;
    u32 operation			= 0;
    u32 last_operation  	= 0;

	ge_VertexInfo lastVertInfo;

	while (true)
	{
		// if we reach a stall we need to report this callee
		if (list.pc == list.stall_addr)
		{
			return false;
		}

        last_operation      = operation;
		memory_operation	= Memory::memw(list.pc);
		operation			= memory_operation>>24;
		data				= memory_operation&0x00FFFFFF;

		switch (operation) 
		{
		case CMD_NOP: // 0x00
			break;

		case CMD_VADDR: // 0x01
			theGeContext.vertex_address = (theGeContext.base_address | data) + theGeContext.offset_address;
            infof(dList,"CMD_VADDR %08x", theGeContext.vertex_address);
			break;

		case CMD_IADDR: // 0x02
			theGeContext.index_address = (theGeContext.base_address | data) + theGeContext.offset_address;
            infof(dList,"CMD_IADDR %08x", theGeContext.index_address);
			break;

		case CMD_PRIM: // 0x04
			{
				u32 count = (data >>  0) & 0xFFFF;
				u32 type  = (data >> 16) & 0x0007;

                theRenderer.DrawArray(lastVertInfo, type, count, (last_operation == CMD_PRIM));

				static char const *types[8] = 
				{
                    "POINTS:0",
                    "LINES:1",
                    "LINE_STRIP:2",
                    "TRIANGLES:3",
                    "TRIANGLE_STRIP:4",
                    "TRIANGLE_FAN:5",
                    "RECTANGLES:6",
                    "???:7"
				};
                infof(dList, "CMD_PRIM type=%s, count=%i, vaddr=%08x, iaddr=%08x", types[type], count, theGeContext.vertex_address, theGeContext.index_address);
			}
			break;

		case CMD_BEZIER: // 0x05
            {
                u32 ucount =  data       & 0xFF;
                u32 vcount = (data >> 8) & 0xFF;

                theRenderer.DrawBezier(lastVertInfo, ucount, vcount, (last_operation == CMD_BEZIER));
            
                infof(dList,"CMD_BEZIER ucount=%u, vcount=%u, vaddr=%08x, iaddr=%08x", ucount, vcount, theGeContext.vertex_address, theGeContext.index_address);
            }
		    break;

		case CMD_SPLINE: // 0x06
			{
				u32 ucount = (data >>  0) & 0xFF;
				u32 vcount = (data >>  8) & 0xFF;
				u32 uflag  = (data >> 16) & 0x03;
				u32 vflag  = (data >> 18) & 0x03;

                theRenderer.DrawSpline(lastVertInfo, ucount, vcount, uflag, vflag, (last_operation == CMD_SPLINE));
				
                infof(dList,"CMD_SPLINE ucount=%u, vcount=%u, uf=%u, vf=%u, vaddr=%08x, iaddr=%08x", ucount, vcount, uflag, vflag, theGeContext.vertex_address, theGeContext.index_address);
			}
			break;

		case CMD_BBOX: // 0x07
			{
                u32 count = data & 0xFF;
                theRenderer.CullObject(lastVertInfo, count);
				infof(dList,"CMD_BBOX count=%u", count);
			}
			break;

		case CMD_JUMP: // 0x08
			{
				u32 target = ((theGeContext.base_address | data) & 0xFFFFFFFC) + theGeContext.offset_address;
                infof(dList,"CMD_JUMP from %08x to %08x", list.pc, target);
				list.pc = target;
			}
			continue;

		case CMD_BJUMP: // 0x09
			{
                if (theRenderer.IsObjectCulled())
                {
                    u32 target = ((theGeContext.base_address | data) & 0xFFFFFFFC) +  theGeContext.offset_address;
                    list.pc = target;
                    infof(dList, "CMD_BJUMP true, from %08x to %08x", list.pc, target);
                }
                else
                {
                    infof(dList, "CMD_BJUMP false, %08x", list.pc);
                }
			}
			break;

		case CMD_CALL: // 0x0A
			{
				u32 old = list.pc;
                list.call_relative_offset(data);
				list.pc = list.pc;
				infof(dList,"CMD_CALL from %08x to %08x", old, list.pc);
			}
			continue;

		case CMD_RET: // 0x0B
			{
				u32 old = list.pc;
				list.ret_stack();
				u32 newpc = list.pc;
				infof(dList,"CMD_RET from %08x to %08x", old, newpc);
			}
			break;

		case CMD_END: // 0x0C
			return true; //???
			break;

		case CMD_SIGNAL: // 0x0E
			{
				u32 behavior = (data >> 16) & 0xFF;
				u32 signal = data & 0xFFFF;
				infof(dList, "CMD_SIGNAL (behavior=%d, signal=0x%X)", behavior, signal);	

				switch (behavior) 
				{
        			case PSP_GE_SIGNAL_SYNC: 
					{
	        			// Skip END / FINISH / END
						if ((Memory::memw(list.pc) >> 24) == CMD_END) 
						{
	        				list.pc += 4;
	        				if ((Memory::memw(list.pc) >> 24) == CMD_FINISH) 
							{
	            				list.pc += 4;
	                			if ((Memory::memw(list.pc) >> 24) == CMD_END) 
								{
	                				list.pc += 4;
	                			}
	        				}
	        			}
						infof(dList, "PSP_GE_SIGNAL_SYNC ignored PC: 0x%08X", list.pc);
	        			break;
        			}
        			case PSP_GE_SIGNAL_CALL: 
					{
						// Call list using absolute address from SIGNAL + END.
	        			if ((Memory::memw(list.pc) >> 24) == CMD_END)
						{
							u32 hi16 = signal & 0x0FFF;
	        				u32 lo16 = (Memory::memw(list.pc) & 0xFFFF);
							u32 addr = (hi16 << 16) | lo16;
							// Skip END
							list.pc += 4;
							u32 oldPc = list.pc;
							list.call_absolute(addr);
							u32 newPc = list.pc;

							infof(dList,"PSP_GE_SIGNAL_CALL old PC: 0x%08X, new PC: 0x%08X", oldPc, newPc);

						}
						break;
        			}
        			case PSP_GE_SIGNAL_RETURN: 
					{
						// Return from PSP_GE_SIGNAL_CALL.
	        			if ((Memory::memw(list.pc) >> 24) == CMD_END)
						{
	        				// Skip END
							list.pc += 4;
							int oldPc = list.pc;
							list.ret_stack();
							int newPc = list.pc;
							infof(dList,"PSP_GE_SIGNAL_RETURN old PC: 0x%08X, new PC: 0x%08X", oldPc, newPc);
						}
	        			break;
        			}
        			case PSP_GE_SIGNAL_TBP0_REL:
        			case PSP_GE_SIGNAL_TBP1_REL:
        			case PSP_GE_SIGNAL_TBP2_REL:
        			case PSP_GE_SIGNAL_TBP3_REL:
        			case PSP_GE_SIGNAL_TBP4_REL:
        			case PSP_GE_SIGNAL_TBP5_REL:
        			case PSP_GE_SIGNAL_TBP6_REL:
        			case PSP_GE_SIGNAL_TBP7_REL: 
					{
						// Overwrite TBPn and TBPw with SIGNAL + END (uses relative address only).
            			if ((Memory::memw(list.pc) >> 24) == CMD_END) 
						{
							u32 hi16 = signal & 0xFFFF;
            				u32 lo16 = ((Memory::memw(list.pc) & 0xFFFF));
							u32 width = ((Memory::memw(list.pc) >> 16) & 0xFF);
							u32 addr = list.get_address_rel((hi16 << 16) | lo16);
							// Skip END
							list.pc += 4;
							theGeContext.texture_base_pointer[behavior - PSP_GE_SIGNAL_TBP0_REL] = addr;
							theGeContext.texture_buffer_width[behavior - PSP_GE_SIGNAL_TBP0_REL] = width;
						}
        				break;
        			}
        			case PSP_GE_SIGNAL_TBP0_REL_OFFSET:
        			case PSP_GE_SIGNAL_TBP1_REL_OFFSET:
        			case PSP_GE_SIGNAL_TBP2_REL_OFFSET:
        			case PSP_GE_SIGNAL_TBP3_REL_OFFSET:
        			case PSP_GE_SIGNAL_TBP4_REL_OFFSET:
        			case PSP_GE_SIGNAL_TBP5_REL_OFFSET:
        			case PSP_GE_SIGNAL_TBP6_REL_OFFSET:
        			case PSP_GE_SIGNAL_TBP7_REL_OFFSET: 
					{
						// Overwrite TBPn and TBPw with SIGNAL + END (uses relative address with offset).
            			if ((Memory::memw(list.pc) >> 24) == CMD_END)  
						{
							int hi16 = signal & 0xFFFF;
            				int lo16 = ((Memory::memw(list.pc) & 0xFFFF));
							int width = ((Memory::memw(list.pc) >> 16) & 0xFF);
							int addr = list.get_address_rel_offset((hi16 << 16) | lo16);
							// Skip END
							list.pc += 4;
							theGeContext.texture_base_pointer[behavior - PSP_GE_SIGNAL_TBP0_REL_OFFSET] = addr;
							theGeContext.texture_buffer_width[behavior - PSP_GE_SIGNAL_TBP7_REL_OFFSET] = width;
						}
        				break;
        			}
        			case PSP_GE_SIGNAL_HANDLER_SUSPEND:
        			case PSP_GE_SIGNAL_HANDLER_CONTINUE:
        			case PSP_GE_SIGNAL_HANDLER_PAUSE: 
					{
						errorf(dList, "Not implemented: PSP_GE_SIGNAL_HANDLER_SUSPEND, PSP_GE_SIGNAL_HANDLER_CONTINUE, PSP_GE_SIGNAL_HANDLER_PAUSE");
            			break;
        			}
        			default: 
					{
						errorf(dList, "CMD_SIGNAL (behavior=%d, signal=0x%X) unknown behavior at 0x%08X", behavior, signal, list.pc - 4);
        			}
				}

			}
			break;
		
		case CMD_FINISH: // 0x0F
			infof(dList, "CMD_FINISH");				
			break;
		
		case CMD_BASE: // 0x10
			theGeContext.base_address = (data << 8) & 0xff000000;
			infof(dList, "CMD_BASE base=%08x", theGeContext.base_address);
			break;

		case CMD_VTYPE: // 0x12
		{
			theGeContext.transform_mode = data;
			theDecoder.SetVertexInfo(lastVertInfo);
			infof(dList, "CMD_VTYPE (%06X) tm=%u, mc=%u, wc=%u, it=%u, wt=%u, vt=%u, nt=%u, ct=%u, tt=%u", data, lastVertInfo.tm, lastVertInfo.mc, lastVertInfo.wc, lastVertInfo.it, lastVertInfo.wt, lastVertInfo.vt, lastVertInfo.nt, lastVertInfo.ct, lastVertInfo.tt);
			break;
		}
		case CMD_OFFSET: // 0x13
			theGeContext.offset_address = (data << 8);
            infof(dList, "CMD_OFFSET BASE+%06x", theGeContext.offset_address);
			break;
		
		case CMD_ORIGIN: // 0x14
			theGeContext.offset_address = list.pc - 4 - theGeContext.base_address;
            infof(dList, "CMD_ORIGIN BASE+%06x", theGeContext.offset_address);
			break;
		
		case CMD_REGION1: // 0x15
			{
				theGeContext.region[0] = u16((data >>  0) & 0x3ff);
				theGeContext.region[1] = u16((data >> 10) & 0x3ff);
				infof(dList, "CMD_REGION1 l=%d, t=%d", theGeContext.region[0], theGeContext.region[1]);
			}
			break;

		case CMD_REGION2: // 0x16
			{
                theGeContext.region[2]		= u16((data >>  0) & 0x3ff);
                theGeContext.region[3]		= u16((data >> 10) & 0x3ff);
				theGeContext.region_width	= u32(theGeContext.region[2] + 1) - u32(theGeContext.region[0]);
				theGeContext.region_height	= u32(theGeContext.region[3] + 1) - u32(theGeContext.region[1]);
                theRenderer.SetDrawingRegion(theGeContext.region);
				infof(dList, "CMD_REGION2 r=%d, b=%d", theGeContext.region[2], theGeContext.region[3]);
			}
			break;

		case CMD_LTE: // 0x17
			{
				theGeContext.lighting_enable = data & 1;
				infof(dList, "CMD_LTE enable=%i", data);
			}
			break;

		case CMD_LE0: // 0x18
		case CMD_LE1: // 0x19
		case CMD_LE2: // 0x1A
		case CMD_LE3: // 0x1B
			{
                theGeContext.ChangeUniform(U_LE);
                if (data & 1)
                {
                    theGeContext.light_enabled |= 1<<(operation-CMD_LE0);
                }
                else
                {
                    theGeContext.light_enabled &= ~(1<<(operation-CMD_LE0));
                }
                infof(dList,"CMD_LE #%i, enable=%d", operation-CMD_LE0, data);
			}
			break;

		case CMD_CLE: // 0x1C
			{
                theGeContext.clipping_enable = data & 1;
			    infof(dList,"CMD_CLE enable=%i", data);
			}
			break;

		case CMD_BCE: // 0x1D
			{
				theGeContext.face_culling_enable = data & 1;
				infof(dList,"CMD_BCE enable=%d", theGeContext.face_culling_enable);
			}
			break;

		case CMD_TME: // 0x1E
			{
				theGeContext.texture_mapping_enable = data & 1;
				infof(dList,"CMD_TME enable=%i", data);
			}
			break;

		case CMD_FGE: // 0x1F
			{
				theGeContext.fogging_enable = data & 1;
				infof(dList, "CMD_FGE enable=%i", data);
			}
			break;
		
		case CMD_DTE: // 0x20
			{
				theGeContext.dithering_enable = data & 1;
				infof(dList, "CMD_DTE enable=%i", data);
			}
			break;

		case CMD_ABE: // 0x21
			{
				theGeContext.alpha_blending_enable = data & 1;
				infof(dList, "CMD_ABE enable=%i", data);
			}
			break;
		case CMD_ATE: // 0x22
			{
                theGeContext.alpha_test_enable = data & 1;
                infof(dList, "CMD_ATE enable=%i", data);
			}
			break;

		case CMD_ZTE: // 0x23
			{
				theGeContext.depth_test_enable = data & 1;
				infof(dList, "CMD_ZTE enable=%i", data);
			}
			break;

		case CMD_STE: // 0x24
			{
				theGeContext.stencil_test_enable = data & 1;
				infof(dList, "CMD_STE enable=%i", data);
			}
			break;

		case CMD_AAE: // 0x25
			{
				theGeContext.antialiasing_enable = data & 1;
			    infof(dList,"CMD_AAE enable=%i", data);
			}
			break;

		case CMD_PCE: // 0x26
            {
                theGeContext.patch_culling_enable = data & 1;
                infof(dList,"CMD_PCE enable=%i", data);
            }
			break;

		case CMD_CTE: // 0x27
			{
                // IMPLEMENT
				infof(dList,"CMD_CTE data=%i", data);
			}
			break;

		case CMD_LOE: // 0x28
			{
				theGeContext.logical_operation_enable = data & 1;
				infof(dList,"CMD_LOE enable=%i", data);
			}
			break;

        case CMD_BONEN: // 0x2A
            {
                theGeContext.matrix_bone_num = data & 0x7F;
                infof(dList,"CMD_BONEN #%i", data);
            }
			break;

		case CMD_BONED: // 0x2B
			{
                static ge_Matrix43	MatrixBones[8];
                int matrix_bone = theGeContext.matrix_bone_num / 12;
                ge_Matrix43 &Matrix = MatrixBones[matrix_bone];
                int current_matrix_bone_num = (theGeContext.matrix_bone_num++) % 12;
                Matrix.mData[current_matrix_bone_num] = getFloat24(data);
				
				if (current_matrix_bone_num == 11)
				{
                    theGeContext.ChangeUniform(U_BM); 
					infof(dList,"CMD_BONED: \n[%f %f %f %f %f %f %f %f %f %f %f %f]", Matrix.mData[0],Matrix.mData[1], Matrix.mData[2] 
																				    , Matrix.mData[3],Matrix.mData[4], Matrix.mData[5]
																					, Matrix.mData[6],Matrix.mData[7], Matrix.mData[8]
                                                                                    , Matrix.mData[9],Matrix.mData[10],Matrix.mData[11]);
				    ge_Matrix44	ConvertedMatrix(&Matrix);
                    theRenderer.SetMatrix((ge_matrix_type)(SCE_GE_MTXNO_BONE0 + matrix_bone), &ConvertedMatrix);				
				} 
			}
			break;

		case CMD_WEIGHT0: // 0x2C
		case CMD_WEIGHT1: // 0x2D
		case CMD_WEIGHT2: // 0x2E
		case CMD_WEIGHT3: // 0x2F
		case CMD_WEIGHT4: // 0x30
		case CMD_WEIGHT5: // 0x31
		case CMD_WEIGHT6: // 0x32
		case CMD_WEIGHT7: // 0x33
			{
				theGeContext.morphing_weights[operation - CMD_WEIGHT0] = getFloat24(data);
                infof(dList, "CMD_WEIGHT%i data=%f", operation - CMD_WEIGHT0, theGeContext.morphing_weights[operation - CMD_WEIGHT0]);
			}
			break;
	
		case CMD_DIVIDE: // 0x36
            {
                theGeContext.patch_div_u = (data >> 0) & 0x7f;
                theGeContext.patch_div_v = (data >> 8) & 0x7f;
                infof(dList, "CMD_DIVIDE udivs=%d, vdivs=%d", theGeContext.patch_div_u, theGeContext.patch_div_v);
            }
			break;

		case CMD_PPM: // 0x37
			{
                static const char *patch_primitive_name[4] = { "TRIANGLE:0", "LINE:1", "POINT:2", "???" };
                theGeContext.patch_primitive = data & 3;
				infof(dList,"CMD_PPM prim=%s", patch_primitive_name[theGeContext.patch_primitive]);
			}
			break;

		case CMD_PFACE: // 0x38
			{
                static const char *patch_facing_name[2] = { "CW", "CCW" };
                theGeContext.patch_face = data & 1;
				infof(dList,"CMD_PATCHFACING face=%s", patch_facing_name[theGeContext.patch_face]);
			}
			break;

		case CMD_WORLDN: // 0x3A
            {
                theGeContext.matrix_world_num = data & 0xF;
                infof(dList,"CMD_WORLDN #%i", data);
            }
			break;

		case CMD_WORLDD: // 0x3B
			{
				static ge_Matrix43	Matrix;
				Matrix.mData[theGeContext.matrix_world_num++] = getFloat24(data);
				
				// we need to set the matrix when all data is there
				if (theGeContext.matrix_world_num == 12)
				{
                    theGeContext.ChangeUniform(U_WM); 
					infof(dList,"CMD_WORLDD: \n[%f %f %f %f %f %f %f %f %f %f %f %f]", Matrix.mData[0], Matrix.mData[1],  Matrix.mData[2] 
																					 , Matrix.mData[3], Matrix.mData[4],  Matrix.mData[5]
																					 , Matrix.mData[6], Matrix.mData[7],  Matrix.mData[8]
																					 , Matrix.mData[9], Matrix.mData[10], Matrix.mData[11]);
					ge_Matrix44	ConvertedMatrix(&Matrix);
					theRenderer.SetMatrix(SCE_GE_MTXNO_WORLD,&ConvertedMatrix);
				}
			}
			break;

		case CMD_VIEWN: // 0x3C
            {
                theGeContext.matrix_view_num = data & 0xF;
                infof(dList,"CMD_VIEWN #%i", data);
            }
			break;

		case CMD_VIEWD: // 0x3D
			{
				static ge_Matrix43	Matrix;
				Matrix.mData[theGeContext.matrix_view_num++] = getFloat24(data);
				
				// we need to set the matrix when all data is there
				if (theGeContext.matrix_view_num == 12)
				{
                    theGeContext.ChangeUniform(U_VM); 
					infof(dList,"CMD_VIEWD: \n[%f %f %f %f %f %f %f %f %f %f %f %f]", Matrix.mData[0], Matrix.mData[1],  Matrix.mData[2] 
																					, Matrix.mData[3], Matrix.mData[4],  Matrix.mData[5]
																					, Matrix.mData[6], Matrix.mData[7],  Matrix.mData[8]
																					, Matrix.mData[9], Matrix.mData[10], Matrix.mData[11]);
					ge_Matrix44	ConvertedMatrix(&Matrix);
					theRenderer.SetMatrix(SCE_GE_MTXNO_VIEW, &ConvertedMatrix);
				}
			}
			break;

		case CMD_PROJN: // 0x3E
            {
                theGeContext.matrix_projection_num = data & 0xF;
                infof(dList,"CMD_PROJN #%i", data);
            }
			break;

		case CMD_PROJD: // 0x3F
			{
				static ge_Matrix44	Matrix;
				Matrix.mData[theGeContext.matrix_projection_num++] = getFloat24(data);
				
				// we need to set the matrix when all data is there
				if (theGeContext.matrix_projection_num == 16)
				{
                    theGeContext.ChangeUniform(U_PM); 
                    infof(dList,"CMD_PROJD: \n[%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f]", Matrix.mData[0],  Matrix.mData[1],  Matrix.mData[2],  Matrix.mData[3]
                                                                                                , Matrix.mData[4],  Matrix.mData[5],  Matrix.mData[6],  Matrix.mData[7]
                                                                                                , Matrix.mData[8],  Matrix.mData[9],  Matrix.mData[10], Matrix.mData[11]
																								, Matrix.mData[12], Matrix.mData[13], Matrix.mData[14], Matrix.mData[15]);
					theRenderer.SetMatrix(SCE_GE_MTXNO_PROJ,&Matrix);
				}
			}
			break;

		case CMD_TGENN: // 0x40
            {
                theGeContext.matrix_texture_num = data & 0xF;
                infof(dList,"CMD_TGENN #%i", data);
            }
			break;

		case CMD_TGEND: // 0x41
			{
                static ge_Matrix43	Matrix;
				Matrix.mData[theGeContext.matrix_texture_num++] = getFloat24(data);
				
				if (theGeContext.matrix_texture_num == 12)
				{
                    theGeContext.ChangeUniform(U_TPROJ); 
					infof(dList,"CMD_TGEND: \n[%f %f %f %f %f %f %f %f %f %f %f %f]", Matrix.mData[0], Matrix.mData[1],  Matrix.mData[2] 
																					, Matrix.mData[3], Matrix.mData[4],  Matrix.mData[5]
																					, Matrix.mData[6], Matrix.mData[7],  Matrix.mData[8]
                                                                                    , Matrix.mData[9], Matrix.mData[10], Matrix.mData[11]);
				    ge_Matrix44	ConvertedMatrix(&Matrix);
					theRenderer.SetMatrix(SCE_GE_MTXNO_TEXGEN,&ConvertedMatrix);				
				} 
			}
			break;

		case CMD_SX: // 0x42
            {
                theGeContext.viewport_sx = getFloat24(data);
                infof(dList,"CMD_SX %f", theGeContext.viewport_sx);
            }
            break;

        case CMD_SY: // 0x43
            {
                theGeContext.viewport_sy = getFloat24(data);
                infof(dList,"CMD_SY %f", theGeContext.viewport_sy);
            }
            break;

		case CMD_SZ: // 0x44
            {
                theGeContext.viewport_sz = getFloat24(data);
                infof(dList,"CMD_SZ %f", theGeContext.viewport_sz);
            }
			break;

		case CMD_TX: // 0x45
            {
                theGeContext.viewport_tx = getFloat24(data);
                infof(dList,"CMD_TX %f", theGeContext.viewport_tx);
            }
            break;

        case CMD_TY: // 0x46
            {
                theGeContext.viewport_ty = getFloat24(data);
                infof(dList,"CMD_TY %f", theGeContext.viewport_ty);
            }
            break;

		case CMD_TZ: // 0x47
            {
                theGeContext.viewport_tz = getFloat24(data);
                infof(dList,"CMD_TZ %f", theGeContext.viewport_tz);
            }
			break;

		case CMD_SU: // 0x48
            {
                theGeContext.ChangeUniform(U_TSCALE); 
                theGeContext.texture_scale_u = getFloat24(data); 
                infof(dList, "CMD_SU %f", theGeContext.texture_scale_u);
            }
			break;

		case CMD_SV: // 0x49
            {
                theGeContext.ChangeUniform(U_TSCALE); 
                theGeContext.texture_scale_v = getFloat24(data); 
                infof(dList, "CMD_SV %f", theGeContext.texture_scale_v);
            }
			break;

		case CMD_TU: // 0x4A
            {
                theGeContext.ChangeUniform(U_TTRANS); 
                theGeContext.texture_offset_u = getFloat24(data);  
                infof(dList,"CMD_TU %f", theGeContext.texture_offset_u);
            }
			break;

		case CMD_TV: // 0x4Bh
            {
                theGeContext.ChangeUniform(U_TTRANS); 
                theGeContext.texture_offset_v = getFloat24(data);  
                infof(dList,"CMD_TV %f", theGeContext.texture_offset_v);
            }
			break;

		case CMD_OFFSETX: // 0x4C
            {
                theGeContext.offset_x = float(data & 65535) / 16.0f; 
                infof(dList,"CMD_OFFSETX %f", theGeContext.offset_x);
            }
			break;

		case CMD_OFFSETY: // 0x4D
            {
                theGeContext.offset_y = float(data & 65535) / 16.0f; 
                infof(dList,"CMD_OFFSETY %f", theGeContext.offset_y);
            }
			break;

		case CMD_SHADE: // 0x4E
            {
                theGeContext.gouraud_enable = data & 1;
                infof(dList, "CMD_SHADE smooth=%i", data);
            }
			break;
		
		case CMD_NREV: // 0x4F
            {
                bool nrev = data & 1;
                theGeContext.ChangeUniform(U_NREV);
                theGeContext.reverse_normals = nrev;
                infof(dList, "CMD_NREV enable=%i", nrev);
            }
			break;
		
		case CMD_MATERIAL: // 0x53
            {
                u32 material = data & 7;
                theGeContext.ChangeUniform(U_LMADS); 
                theGeContext.material_flags = material;
                infof(dList,"CMD_MATERIAL ae=%i, de=%i, se=%i", (material>>0) & 1, (material>>1) & 1, (material>>2) & 1);
            }
			break;

		case CMD_MEC: // 0x54
			{
                theGeContext.ChangeUniform(U_MC); 
				theGeContext.material_mec[0] = ((data      ) & 255) / 255.f;
            	theGeContext.material_mec[1] = ((data >>  8) & 255) / 255.f;
            	theGeContext.material_mec[2] = ((data >> 16) & 255) / 255.f;
                theGeContext.material_mec[3] = 1.0;
                infof(dList, "CMD_MEC r=%f, g=%f, b=%f", theGeContext.material_mec[0], theGeContext.material_mec[1], theGeContext.material_mec[2]);
			}
			break;

		case CMD_MAC: // 0x55
            {
                theGeContext.ChangeUniform(U_MC); 
                theGeContext.material_mac[0] = ((data	  ) & 255) / 255.f;
                theGeContext.material_mac[1] = ((data >>  8) & 255) / 255.f;
                theGeContext.material_mac[2] = ((data >> 16) & 255) / 255.f;
                infof(dList, "CMD_MAC r=%f, g=%f, b=%f", theGeContext.material_mac[0], theGeContext.material_mac[1], theGeContext.material_mac[2]);
            }
			break;

		case CMD_MDC: // 0x56
            {
                theGeContext.ChangeUniform(U_MC); 
                theGeContext.material_mdc[0] = ((data      ) & 255) / 255.f;
                theGeContext.material_mdc[1] = ((data >>  8) & 255) / 255.f;
                theGeContext.material_mdc[2] = ((data >> 16) & 255) / 255.f;
                theGeContext.material_mdc[3] = 1.0;
                infof(dList, "CMD_MDC r=%f, g=%f, b=%f", theGeContext.material_mdc[0], theGeContext.material_mdc[1], theGeContext.material_mdc[2]);
            }
			break;

		case CMD_MSC: // 0x57
            {
                theGeContext.ChangeUniform(U_MC); 
                theGeContext.material_msc[0] = ((data      ) & 255) / 255.f;
                theGeContext.material_msc[1] = ((data >>  8) & 255) / 255.f;
                theGeContext.material_msc[2] = ((data >> 16) & 255) / 255.f;
                theGeContext.material_msc[3] = 1.0f;
                infof(dList, "CMD_MSC r=%f, g=%f, b=%f", theGeContext.material_msc[0], theGeContext.material_msc[1], theGeContext.material_msc[2]);
            }
			break;

		case CMD_MAA: // 0x58
            {
                theGeContext.ChangeUniform(U_MC);
                theGeContext.material_mac[3] = (data & 255) / 255.f;
                infof(dList, "CMD_MAA a=%f", theGeContext.material_mac[3]);
            }
			break;

		case CMD_MK: // 0x5B
			{
                theGeContext.ChangeUniform(U_MK); 
                theGeContext.light_mk = getFloat24(data); 
                infof(dList, "CMD_MK %f", theGeContext.light_mk);
			}
			break;

		case CMD_AC: // 0x5C
			{
                theGeContext.ChangeUniform(U_AC); 
				theGeContext.light_ac[0] = ((data      ) & 255) / 255.f;
            	theGeContext.light_ac[1] = ((data >>  8) & 255) / 255.f;
            	theGeContext.light_ac[2] = ((data >> 16) & 255) / 255.f;
				infof(dList, "CMD_AC r=%f, g=%f, b=%f", theGeContext.light_ac[0], theGeContext.light_ac[1], theGeContext.light_ac[2]);
			}
			break;

		case CMD_AA: // 0x5D
            {
                theGeContext.ChangeUniform(U_AC); 
                theGeContext.light_ac[3] = (data & 255) / 255.f;
                infof(dList, "CMD_AA a=%f", theGeContext.light_ac[3]);
            }		
			break;
		
		case CMD_LMODE: //0x5E
			{
                theGeContext.ChangeUniform(U_LMADS); 
                theGeContext.light_mode = data & 1;     
                infof(dList, "CMD_LMODE enable=%i", data & 1);
			}
			break;

		case CMD_LTYPE0: //0x5F
		case CMD_LTYPE1: //0x60
		case CMD_LTYPE2: //0x61
		case CMD_LTYPE3: //0x62
			{
                theGeContext.ChangeUniform(U_LTYPE); 
                theGeContext.ChangeUniform(U_LV); 
				theGeContext.light_type[operation-CMD_LTYPE0] = (data >> 8) & 3;
				theGeContext.light_kind[operation-CMD_LTYPE0] = (data >> 0) & 3;
				switch (theGeContext.light_type[operation-CMD_LTYPE0]) 
				{
                case GE_LIGHT_TYPE_DIRECTIONAL:
                    theGeContext.light_lv[operation-CMD_LTYPE0][3] = 0.0f;
                    break;
                case GE_LIGHT_TYPE_POINT:
                    theGeContext.light_lv[operation-CMD_LTYPE0][3] = 1.0f;
                    break;
                case GE_LIGHT_TYPE_SPOT:
                    theGeContext.light_lv[operation-CMD_LTYPE0][3] = 1.0f;
                    break;
            	}
				infof(dList, "CMD_LTYPE%i kind=%02x, type=%02x", operation-CMD_LTYPE0, theGeContext.light_kind, theGeContext.light_type);
			}
			break;

		case CMD_LX0: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[0][0] = getFloat24(data); infof(dList, "CMD_LX0 %f", getFloat24(data)); break; // 0x63h
		case CMD_LY0: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[0][1] = getFloat24(data); infof(dList, "CMD_LY0 %f", getFloat24(data)); break; // 0x64h
		case CMD_LZ0: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[0][2] = getFloat24(data); infof(dList, "CMD_LZ0 %f", getFloat24(data)); break; // 0x65h
		case CMD_LX1: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[1][0] = getFloat24(data); infof(dList, "CMD_LX1 %f", getFloat24(data)); break; // 0x66h
		case CMD_LY1: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[1][1] = getFloat24(data); infof(dList, "CMD_LY1 %f", getFloat24(data)); break; // 0x67h
		case CMD_LZ1: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[1][2] = getFloat24(data); infof(dList, "CMD_LZ1 %f", getFloat24(data)); break; // 0x68h
		case CMD_LX2: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[2][0] = getFloat24(data); infof(dList, "CMD_LX2 %f", getFloat24(data)); break; // 0x69h
		case CMD_LY2: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[2][1] = getFloat24(data); infof(dList, "CMD_LY2 %f", getFloat24(data)); break; // 0x6Ah
		case CMD_LZ2: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[2][2] = getFloat24(data); infof(dList, "CMD_LZ2 %f", getFloat24(data)); break; // 0x6Bh
		case CMD_LX3: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[3][0] = getFloat24(data); infof(dList, "CMD_LX3 %f", getFloat24(data)); break; // 0x6Ch
		case CMD_LY3: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[3][1] = getFloat24(data); infof(dList, "CMD_LY3 %f", getFloat24(data)); break; // 0x6Dh
		case CMD_LZ3: theGeContext.ChangeUniform(U_LV); theGeContext.light_lv[3][2] = getFloat24(data); infof(dList, "CMD_LZ3 %f", getFloat24(data)); break; // 0x6Eh

		case CMD_LDX0: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[0][0] = getFloat24(data); infof(dList, "CMD_LDX0 %f", getFloat24(data)); break; // 0x6F
		case CMD_LDY0: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[0][1] = getFloat24(data); infof(dList, "CMD_LDY0 %f", getFloat24(data)); break; // 0x70
		case CMD_LDZ0: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[0][2] = getFloat24(data); infof(dList, "CMD_LDZ0 %f", getFloat24(data)); break; // 0x71
        case CMD_LDX1: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[1][0] = getFloat24(data); infof(dList, "CMD_LDX1 %f", getFloat24(data)); break; // 0x72
        case CMD_LDY1: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[1][1] = getFloat24(data); infof(dList, "CMD_LDY1 %f", getFloat24(data)); break; // 0x73
        case CMD_LDZ1: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[1][2] = getFloat24(data); infof(dList, "CMD_LDZ1 %f", getFloat24(data)); break; // 0x74
        case CMD_LDX2: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[2][0] = getFloat24(data); infof(dList, "CMD_LDX2 %f", getFloat24(data)); break; // 0x75
        case CMD_LDY2: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[2][1] = getFloat24(data); infof(dList, "CMD_LDY2 %f", getFloat24(data)); break; // 0x76
        case CMD_LDZ2: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[2][2] = getFloat24(data); infof(dList, "CMD_LDZ2 %f", getFloat24(data)); break; // 0x77
        case CMD_LDX3: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[3][0] = getFloat24(data); infof(dList, "CMD_LDX3 %f", getFloat24(data)); break; // 0x78
        case CMD_LDY3: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[3][1] = getFloat24(data); infof(dList, "CMD_LDY3 %f", getFloat24(data)); break; // 0x79
        case CMD_LDZ3: theGeContext.ChangeUniform(U_LD); theGeContext.light_ld[3][2] = getFloat24(data); infof(dList, "CMD_LDZ3 %f", getFloat24(data)); break; // 0x7A

		case CMD_LKA0: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[0][0] = getFloat24(data); infof(dList, "CMD_LKA0 %f", getFloat24(data)); break; // 0x7Bh
		case CMD_LKB0: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[0][1] = getFloat24(data); infof(dList, "CMD_LKB0 %f", getFloat24(data)); break; // 0x7Ch
		case CMD_LKC0: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[0][2] = getFloat24(data); infof(dList, "CMD_LKC0 %f", getFloat24(data)); break; // 0x7Dh
		case CMD_LKA1: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[1][0] = getFloat24(data); infof(dList, "CMD_LKA1 %f", getFloat24(data)); break; // 0x7Eh
		case CMD_LKB1: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[1][1] = getFloat24(data); infof(dList, "CMD_LKB1 %f", getFloat24(data)); break; // 0x7Fh
		case CMD_LKC1: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[1][2] = getFloat24(data); infof(dList, "CMD_LKC1 %f", getFloat24(data)); break; // 0x80h
		case CMD_LKA2: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[2][0] = getFloat24(data); infof(dList, "CMD_LKA2 %f", getFloat24(data)); break; // 0x81h
		case CMD_LKB2: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[2][1] = getFloat24(data); infof(dList, "CMD_LKB2 %f", getFloat24(data)); break; // 0x82h
		case CMD_LKC2: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[2][2] = getFloat24(data); infof(dList, "CMD_LKC2 %f", getFloat24(data)); break; // 0x83h
		case CMD_LKA3: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[3][0] = getFloat24(data); infof(dList, "CMD_LKA3 %f", getFloat24(data)); break; // 0x84h
		case CMD_LKB3: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[3][1] = getFloat24(data); infof(dList, "CMD_LKB3 %f", getFloat24(data)); break; // 0x85h
		case CMD_LKC3: theGeContext.ChangeUniform(U_LKA); theGeContext.light_lka[3][2] = getFloat24(data); infof(dList, "CMD_LKC3 %f", getFloat24(data)); break; // 0x86h

		case CMD_LKS0: // 0x87
		case CMD_LKS1: // 0x88
		case CMD_LKS2: // 0x89
		case CMD_LKS3: // 0x8A
            {
                theGeContext.ChangeUniform(U_LKS);
                theGeContext.light_lks[operation - CMD_LKS0] = getFloat24(data);
                infof(dList, "CMD_LKS%i %f", operation - CMD_LKS0, getFloat24(data));
            }
			break;

		case CMD_LKO0: // 0x8B
        case CMD_LKO1: // 0x8C
        case CMD_LKO2: // 0x8D
        case CMD_LKO3: // 0x8E
			{
                theGeContext.ChangeUniform(U_LKO);
                theGeContext.light_lko[operation - CMD_LKO0] = getFloat24(data);
                infof(dList, "CMD_LKO%i %f", operation - CMD_LKO0, getFloat24(data));
        	} 
        	break;
		
		case CMD_LAC0: // 0x8F
		case CMD_LAC1: // 0x92
		case CMD_LAC2: // 0x95
		case CMD_LAC3: // 0x98
			{
                theGeContext.ChangeUniform(U_LAC);
				int light = (operation - CMD_LAC0) / 3;
				theGeContext.light_lac[light][0] = ((data      ) & 255) / 255.f;
				theGeContext.light_lac[light][1] = ((data >>  8) & 255) / 255.f;
				theGeContext.light_lac[light][2] = ((data >> 16) & 255) / 255.f;
				theGeContext.light_lac[light][3] = 1.0f;
                infof(dList, "CMD_LAC%i r=%f, g=%f, b=%f", operation - CMD_LAC0, theGeContext.light_lac[light][0], theGeContext.light_lac[light][1], theGeContext.light_lac[light][2]);
			}
			break;

		case CMD_LDC0: // 0x90
		case CMD_LDC1: // 0x93
		case CMD_LDC2: // 0x96
		case CMD_LDC3: // 0x99
			{
                theGeContext.ChangeUniform(U_LDC);
				int light = (operation - CMD_LDC0) / 3;
				theGeContext.light_ldc[light][0] = ((data      ) & 255) / 255.f;
				theGeContext.light_ldc[light][1] = ((data >>  8) & 255) / 255.f;
				theGeContext.light_ldc[light][2] = ((data >> 16) & 255) / 255.f;
				theGeContext.light_ldc[light][3] = 1.0f;
                infof(dList, "CMD_LDC%i r=%f, g=%f, b=%f", operation - CMD_LDC0, theGeContext.light_ldc[light][0], theGeContext.light_ldc[light][1], theGeContext.light_ldc[light][2]);
			}
			break;
		
		case CMD_LSC0: // 0x91
		case CMD_LSC1: // 0x94
		case CMD_LSC2: // 0x97
		case CMD_LSC3: // 0x9A
			{
                theGeContext.ChangeUniform(U_LSC);
				int light = (operation - CMD_LSC0) / 3;
				theGeContext.light_lsc[light][0] = ((data      ) & 255) / 255.f;
				theGeContext.light_lsc[light][1] = ((data >>  8) & 255) / 255.f;
				theGeContext.light_lsc[light][2] = ((data >> 16) & 255) / 255.f;
				theGeContext.light_lsc[light][3] = 1.0f;
                infof(dList, "CMD_LSC%i r=%f, g=%f, b=%f", operation - CMD_LDC0, theGeContext.light_lsc[light][0], theGeContext.light_lsc[light][1], theGeContext.light_lsc[light][2]);
			}
			break;
		
		case CMD_CULL: // 0x9B
            {
                theGeContext.face_culling_direction = (data != 0);
                infof(dList, "CMD_CULL cw=%i", data);
            }
			break;

		case CMD_FBP: // 0x9C
            {
                theGeContext.fbp = (theGeContext.fbp & 0xff000000) | data;
                infof(dList, "CMD_FBP %08x", theGeContext.fbp);
            }
			break;
		
		case CMD_FBW: // 0x9D
            {
                theGeContext.fbp  = (theGeContext.fbp  & 0x00ffffff) | ((data << 8) & 0xff000000);
                theGeContext.fbw = data & 0xffff;
                infof(dList, "CMD_FBW %08x, %d", theGeContext.fbp, theGeContext.fbw);
            }
            break;

		case CMD_ZBP: // 0x9E
            {
                theGeContext.zbp = (theGeContext.zbp & 0xff000000) | data;    
                infof(dList, "CMD_ZBP %08x", theGeContext.zbp);
            }
			break;

        case CMD_ZBW: // 0x9F
            {
                theGeContext.zbp = (theGeContext.zbp & 0x00ffffff) | ((data << 8) & 0xff000000);
                theGeContext.zbw = data & 0xffff;
                infof(dList, "CMD_ZBW %08x, %d", theGeContext.zbp, theGeContext.zbw);
            }
			break;

        case CMD_TBP0: // 0xA0
        case CMD_TBP1: // 0xA1
        case CMD_TBP2: // 0xA2
        case CMD_TBP3: // 0xA3
        case CMD_TBP4: // 0xA4
        case CMD_TBP5: // 0xA5
        case CMD_TBP6: // 0xA6
        case CMD_TBP7: // 0xA7
			{
        		int level = operation - CMD_TBP0;
				theGeContext.texture_base_pointer[level] = (theGeContext.texture_base_pointer[level] & 0xff000000) | data;
                infof(dList, "CMD_TBP%i %08x", operation - CMD_TBP0, theGeContext.texture_base_pointer[level]);
			}
			break;
		
		case CMD_TBW0: // 0xA8
		case CMD_TBW1: // 0xA9
		case CMD_TBW2: // 0xAA
		case CMD_TBW3: // 0xAB
		case CMD_TBW4: // 0xAC
		case CMD_TBW5: // 0xAD
		case CMD_TBW6: // 0xAE
		case CMD_TBW7: // 0xAF
			{
				int level = operation - CMD_TBW0;
				theGeContext.texture_base_pointer[level] = (theGeContext.texture_base_pointer[level] & 0x00ffffff) | ((data << 8) & 0xff000000);
				theGeContext.texture_buffer_width[level] = data & 0x7ff;
                infof(dList, "CMD_TBW%i %08x, %d", operation - CMD_TBP0, theGeContext.texture_base_pointer[level], theGeContext.texture_buffer_width[level]);
			}
			break;

		case CMD_CBP: // 0xB0
			{
				theGeContext.texture_clut_address = (theGeContext.texture_clut_address & 0xff000000) | data;
				theGeContext.texture_clut_is_dirty = true;
                infof(dList, "CMD_CBP %08x", theGeContext.texture_clut_address);
			}
			break;

		case CMD_CBW: // 0xB1
			{
                theGeContext.texture_clut_address = (theGeContext.texture_clut_address & 0x00ffffff) | ((data << 8) & 0x0f000000);
                infof(dList, "CMD_CBW %08x", theGeContext.texture_clut_address);
            }
			break;

		case CMD_XBP1: // 0xB2
            {
                theGeContext.textureTx_sourceAddress = (theGeContext.textureTx_sourceAddress & 0xFF000000) | data;
                infof(dList, "CMD_XBP1 %08x", theGeContext.textureTx_sourceAddress);
            }
        	break;

        case CMD_XBPW1: // 0xB3
            {
                theGeContext.textureTx_sourceAddress = (theGeContext.textureTx_sourceAddress & 0x00FFFFFF) | ((data << 8) & 0xFF000000);
                theGeContext.textureTx_sourceLineWidth = data & 0x0000FFFF;
                infof(dList, "CMD_XBW1 %08x", theGeContext.textureTx_sourceAddress, theGeContext.textureTx_sourceLineWidth);
            }
        	break;

        case CMD_XBP2: // 0xB4
            {
                theGeContext.textureTx_destinationAddress = (theGeContext.textureTx_destinationAddress & 0xFF000000) | data;
                infof(dList, "CMD_XBP1 %08x", theGeContext.textureTx_destinationAddress);
            }
        	break;

        case CMD_XBPW2:  // 0xB5
            {
                theGeContext.textureTx_destinationAddress = (theGeContext.textureTx_destinationAddress & 0x00FFFFFF) | ((data << 8) & 0xFF000000);
                theGeContext.textureTx_destinationLineWidth = data & 0x0000FFFF;
                infof(dList, "CMD_XBW1 %08x", theGeContext.textureTx_destinationAddress, theGeContext.textureTx_destinationLineWidth);
            }
        	break;

		case CMD_TSIZE0: // 0xB8
		case CMD_TSIZE1: // 0xB9
		case CMD_TSIZE2: // 0xBA
		case CMD_TSIZE3: // 0xBB
		case CMD_TSIZE4: // 0xBC
		case CMD_TSIZE5: // 0xBD
		case CMD_TSIZE6: // 0xBE
		case CMD_TSIZE7: // 0xBF
			{				
				int level = operation - CMD_TSIZE0;
				theGeContext.texture_width[level]  = 1 << ((data>>0) & 0x0F);
                theGeContext.texture_height[level] = 1 << ((data>>8) & 0x0F);
				infof(dList, "CMD_TSIZE%i width=%d, height=%d", level, theGeContext.texture_width[level], theGeContext.texture_height[level]);
			}
			break;

		case CMD_TMAP: // 0xC0
            {
                theGeContext.ChangeUniform(U_TMAP);
                theGeContext.texture_mapping_mode       = (data >> 0) & 3;
                theGeContext.texture_projection_mapping = (data >> 8) & 3;
                infof(dList, "CMD_TMAP tmn=%d, tmi=%d", theGeContext.texture_mapping_mode, theGeContext.texture_projection_mapping);
            }
			break;

		case CMD_TSHADE: // 0xC1
			{
                theGeContext.ChangeUniform(U_TSHADE);
                theGeContext.texture_shade.u = (data >> 0) & 0x03;
                theGeContext.texture_shade.v = (data >> 8) & 0x03;
                infof(dList,"CMD_TSHADE u=%d, v=%d", theGeContext.texture_shade.u, theGeContext.texture_shade.v);
			}
			break;

		case CMD_TMODE: // 0xC2
            {
                theGeContext.texture_num_mip_maps = ((data >> 16) & 0xFF);
                theGeContext.mipmap_share_clut    = ((data >>  8) & 0xFF) != 0;
                theGeContext.texture_swizzle 	 = ((data      ) & 0xFF) != 0;
                infof(dList, "CMD_TMODE mipmaps=%d shared_clut=%d swizzled=%d", theGeContext.texture_num_mip_maps, theGeContext.mipmap_share_clut, theGeContext.texture_swizzle );
            }
			break;

		case CMD_TPF: // 0xC3
            {
                theGeContext.texture_storage		= data & 0x0F;
                infof(dList, "CMD_TPF %d", theGeContext.texture_storage);
            }
			break;

		case CMD_CLOAD: // 0xC4
            {
                theGeContext.texture_clut_np = data & 63;
                theGeContext.texture_clut_is_dirty = true;
                infof(dList, "CMD_CLOAD np=%d", theGeContext.texture_clut_np);			
            }
			break;

		case CMD_CLUT: // 0xC5
            {
                theGeContext.texture_clut_mode = (data >>  0) & 0x03;
                theGeContext.texture_clut_sft  = (data >>  2) & 0x1F;
                theGeContext.texture_clut_msk  = (data >>  8) & 0xFF;
                theGeContext.texture_clut_csa  = (data >> 16) & 0x1F;
                infof(dList, "CMD_CLUT mode=%d, stf=%d, msk=%02x, csa=%d", theGeContext.texture_clut_mode, theGeContext.texture_clut_sft, theGeContext.texture_clut_msk, theGeContext.texture_clut_csa);
            }
			break;

		case CMD_TFILTER: // 0xC6
            {
                theGeContext.texture_mag_filter = (data>>8) & 0xFF;
                theGeContext.texture_min_filter = data & 0xFF;
                infof(dList, "CMD_TFILTER tex_mag_filter:%d tex_min_filter: %d", theGeContext.texture_mag_filter, theGeContext.texture_min_filter);
            }
			break;

		case CMD_TWRAP: // 0xC7
            {
                theGeContext.texture_wrap_mode_s =  data       & 0xFF;
                theGeContext.texture_wrap_mode_t = (data >> 8) & 0xFF;
                infof(dList, "CMD_TWRAP wms=%d, wmt=%d", theGeContext.texture_wrap_mode_s, theGeContext.texture_wrap_mode_t);
            }
			break;

		case CMD_TLEVEL: // 0xC8
            {
                theGeContext.texture_mipmap_mode = data & 0x3;
                theGeContext.texture_mipmap_bias = f32(s32(s8(data >> 16))) / 16.0f;
                infof(dList,"CMD_TLEVEL tex_mipmap_mode=%d, tex_mipmap_bias=%f", theGeContext.texture_mipmap_mode, theGeContext.texture_mipmap_bias);
            }
			break;

		case CMD_TFUNC: // 0xC9
			{
                theGeContext.ChangeUniform(U_TFUNC);
                theGeContext.texture_function.txf = (data >>  0) & 7;
                theGeContext.texture_function.tcc = (data >>  8) & 1;
                theGeContext.texture_function.cd  = (data >> 16) & 1;
				infof(dList,"CMD_TFUNC");
			}
			break;

		case CMD_TEC: // 0xCA
			{
                theGeContext.ChangeUniform(U_TRGB);
                theGeContext.texture_function.rgba[0] = ((data      ) & 255) / 255.f;
                theGeContext.texture_function.rgba[1] = ((data >>  8) & 255) / 255.f;
                theGeContext.texture_function.rgba[2] = ((data >> 16) & 255) / 255.f;
                theGeContext.texture_function.rgba[3] = 1.f;
				infof(dList,"CMD_TEC", data);
			}
			break;

		case CMD_TFLUSH: // 0xCB
            {
                infof(dList,"CMD_TFLUSH");
            }
			break;

		case CMD_TSYNC: // 0xCC
            {
                infof(dList,"CMD_TSYNC");
            }
			break;

		case CMD_FOG1: // 0xCD
            {
                theGeContext.fog_end = getFloat24(data);		
                infof(dList, "CMD_FOG1 %f", theGeContext.fog_end);
            }
			break;

		case CMD_FOG2: // 0xCE
			{
				theGeContext.fog_dist = getFloat24(data);
                infof(dList, "CMD_FOG2 %f", theGeContext.fog_dist);
			}
			break;

		case CMD_FC: // 0xCF
			{
				theGeContext.fog_color = (data & 0xFFFFFF);
                infof(dList, "CMD_FC r=%u, g=%u, b=%u", (data >>  0) & 255, (data >>  8) & 255, (data >> 16) & 255);
			}
			break;

		case CMD_TSLOPE: // 0xD0
            {
                theGeContext.texture_mipmap_slope = getFloat24(data);
                infof(dList, "CMD_TSLOPE %f", theGeContext.texture_mipmap_slope);
            }
			break;
		
		case CMD_FPF: // 0xD2
            {
                infof(dList, "CMD_FPF format=%i", data & 3);
            }
			break;

		case CMD_CMODE: // 0xD3
            {
                theGeContext.clear_mode_enable  = (data & 0x001) != 0;
                theGeContext.clear_color_masked = (data & 0x100) != 0;
                theGeContext.clear_alpha_masked = (data & 0x200) != 0;
                theGeContext.clear_depth_masked = (data & 0x400) != 0;
                infof(dList, "CMD_CMODE ce=%i, cen=%i, aen=%i, zen=%i", theGeContext.clear_mode_enable, theGeContext.clear_color_masked, theGeContext.clear_alpha_masked, theGeContext.clear_depth_masked);
            }
			break;

		case CMD_SCISSOR1: // 0xD4
			{
                theGeContext.scissor[0] = u16((data >>  0) & 0x3ff);
                theGeContext.scissor[1] = u16((data >> 10) & 0x3ff);
				infof(dList, "CMD_SCISSOR1 l=%d, t=%d", theGeContext.scissor[0], theGeContext.scissor[1]);
			}
			break;
		case CMD_SCISSOR2: // 0xD5
			{
                theGeContext.scissor[2] = u16((data >>  0) & 0x3ff);
                theGeContext.scissor[3] = u16((data >> 10) & 0x3ff);
				infof(dList, "CMD_SCISSOR2 r=%d, b=%d", theGeContext.scissor[2], theGeContext.scissor[3]);
			}
			break;

		case CMD_MINZ: // 0xD6
            {
                theGeContext.minz = (data & 0xFFFF) / 65535.0f;
                infof(dList, "CMD_MINZ %f", theGeContext.minz);
            }
			break;

		case CMD_MAXZ: // 0xD7
            {
                theGeContext.maxz = (data & 0xFFFF) / 65535.0f;
                infof(dList, "CMD_MAXZ %d", theGeContext.maxz);
            }
			break;
		
		case CMD_CTEST: // 0xD8
            {
                theGeContext.ChangeUniform(U_CTEST);
                theGeContext.color_test_function  = (data) & 0x03;
                infof(dList, "CMD_CTEST func=%u", theGeContext.color_test_function);
            }
			break;

		case CMD_CREF: // 0xD9
            {
                theGeContext.ChangeUniform(U_CREF);
                theGeContext.color_test_color_ref[0] = ((data >>  0) & 0xFF);
                theGeContext.color_test_color_ref[1] = ((data >>  8) & 0xFF);
                theGeContext.color_test_color_ref[2] = ((data >> 16) & 0xFF);
                infof(dList, "CMD_CREF ref=%02x,%02x,%02x", theGeContext.color_test_color_ref[0], theGeContext.color_test_color_ref[1], theGeContext.color_test_color_ref[2]);
            }
			break;
		
		case CMD_CMSK: // 0xDA
            {
                theGeContext.ChangeUniform(U_CMSK);
                theGeContext.color_test_color_msk[0] = ((data >>  0) & 0xFF);
                theGeContext.color_test_color_msk[1] = ((data >>  8) & 0xFF);
                theGeContext.color_test_color_msk[2] = ((data >> 16) & 0xFF);
                infof(dList, "CMD_CMSK msk=%02x,%02x,%02x", theGeContext.color_test_color_msk[0], theGeContext.color_test_color_msk[1], theGeContext.color_test_color_msk[2]);
            }
			break;
		
		case CMD_ATEST: // 0xDB
			{
                theGeContext.ChangeUniform(U_CTEST);
                theGeContext.ChangeUniform(U_CREF);
                theGeContext.ChangeUniform(U_CMSK);
                theGeContext.alpha_test_function  = ((data >>  0) & 0x07);
                theGeContext.alpha_test_color_ref = ((data >>  8) & 0xFF);
                theGeContext.alpha_test_color_msk = ((data >> 16) & 0xFF);
                infof(dList, "CMD_ATEST func=%u, ref=%02x, msk=%02x", theGeContext.alpha_test_function, theGeContext.alpha_test_color_ref, theGeContext.alpha_test_color_msk);
			}
	            	
			break;

		case CMD_STEST: // 0xDC
			{
                theGeContext.stencil_test_function  = ((data >>  0) & 0x07);
                theGeContext.stencil_test_ref       = ((data >>  8) & 0xFF);
                theGeContext.stencil_test_msk       = ((data >> 16) & 0xFF);
                infof(dList, "CMD_STEST func=%u, ref=%02x, msk=%02x", theGeContext.stencil_test_function, theGeContext.stencil_test_ref, theGeContext.stencil_test_msk);
			}
			break;
		
		case CMD_SOP: // 0xDD
			{
				theGeContext.stencil_sfail = (data >>  0) & 0x07;
				theGeContext.stencil_zfail = (data >>  8) & 0x07;
				theGeContext.stencil_zpass = (data >> 16) & 0x07;
				infof(dList, "CMD_SOP fail=%u zfail=%u zpass=%u", theGeContext.stencil_sfail, theGeContext.stencil_zfail, theGeContext.stencil_zpass);
			}
			break;
		
		case CMD_ZTEST: // 0xDE
			{
                theGeContext.depth_test_function = data & 0x07;
				infof(dList, "CMD_ZTEST func=%u", theGeContext.depth_test_function);
			}
			break;

		case CMD_BLEND: // 0xDF
			{
                theGeContext.alpha_blending_a   = (data >> 0) & 0x0F;
                theGeContext.alpha_blending_b   = (data >> 4) & 0x0F;
                theGeContext.alpha_blending_equ = (data >> 8) & 0x07;
                infof(dList, "CMD_BLEND A=%i, B=%i, EQU=%i", theGeContext.alpha_blending_a, theGeContext.alpha_blending_b, theGeContext.alpha_blending_equ);
			}
			break;

		case CMD_FIXA: // 0xE0
            {
                theGeContext.alpha_blending_fixa = data & 0xFFFFFF;
                infof(dList, "CMD_FIXA r=%u, g=%u, b=%u", (data >> 0) & 0xFF, (data >> 8) & 0xFF, (data >> 12) & 0xFF);
            }
			break;

		case CMD_FIXB: // 0xE1
            {
                theGeContext.alpha_blending_fixb = data & 0xFFFFFF;
                infof(dList, "CMD_FIXB r=%u, g=%u, b=%u", (data >> 0) & 0xFF, (data >> 8) & 0xFF, (data >> 12) & 0xFF);
            }

			break;

		case CMD_DITH1: // 0xE2
		case CMD_DITH2: // 0xE3
		case CMD_DITH3: // 0xE4
		case CMD_DITH4: // 0xE5
			{
				u32 dith = (operation - CMD_DITH1) * 4;
				theGeContext.dither_matrix[dith + 0] = (data      ) & 0x0F;
				theGeContext.dither_matrix[dith + 1] = (data >> 4 ) & 0x0F;
				theGeContext.dither_matrix[dith + 2] = (data >> 8 ) & 0x0F;
				theGeContext.dither_matrix[dith + 3] = (data >> 12) & 0x0F;
	           
				for(int i = 0; i < 16; i++)
				{
					if (theGeContext.dither_matrix[i] > 4)
                    {
                        theGeContext.dither_matrix[i] -= 16;
                    }
					else if (theGeContext.dither_matrix[i] < -4)
                    {
                        theGeContext.dither_matrix[i] += 16;
                    }
				}
                infof(dList, "CMD_DITH%i", operation - CMD_DITH1);
			}
			break;
	
		case CMD_LOP: // 0xE6
			{
				theGeContext.logical_operation_function = data & 0x0F;
				infof(dList, "CMD_LOP op=%u", theGeContext.logical_operation_function);
			}
			break;
		
		case CMD_ZMSK: // 0xE7
			{
                theGeContext.depth_mask = (data & 1) == 0;
                infof(dList, "CMD_ZMSK mask=%u", data);
			}
			break;

		case CMD_PMSK1: // 0xE8
			{
				theGeContext.color_mask[0] = ((data >>  0) & 0xFF) == 0; 
				theGeContext.color_mask[1] = ((data >>  8) & 0xFF) == 0; 
				theGeContext.color_mask[2] = ((data >> 16) & 0xFF) == 0; 
                infof(dList, "CMD_PMSK1 r=%02x, g=%02x b=%02x", theGeContext.color_mask[0], theGeContext.color_mask[1], theGeContext.color_mask[2]);
			}
			break;

		case CMD_PMSK2: // 0xE9
            {
                theGeContext.alpha_mask = (data && 0xFF) == 0;
                infof(dList,"CMD_PMSK2 a=%02x", theGeContext.alpha_mask);
            }
			break;

		case CMD_XSTART: // 0xEA
            {
                theGeContext.textureTx_pixelSize = data & 0x1;
                infof(dList,"CMD_XSTART(unimplemented)");
            }
			break;

		case CMD_XPOS1: // 0xEB
            {
                theGeContext.textureTx_sx = data & 0x1FF;
                theGeContext.textureTx_sy = (data >> 10) & 0x1FF;
                infof(dList,"CMD_XPOS1(unimplemented)");
            }
			break;

		case CMD_XPOS2: // 0xEC	
            {
                theGeContext.textureTx_dx = data & 0x1FF;
                theGeContext.textureTx_dy = (data >> 10) & 0x1FF;
                infof(dList,"CMD_XPOS2(unimplemented)");
            }
			break;

		case CMD_XSIZE: // 0xEE
            {
                theGeContext.textureTx_width = (data & 0x3FF) + 1;
                theGeContext.textureTx_height = ((data >> 10) & 0x1FF) + 1;
                infof(dList,"CMD_XSIZE(unimplemented)");
            }
			break;

		case CMD_X2: // 0xF0 - its use is prohibited
            {
                infof(dList, "CMD_X2");
            }
			break;

        case CMD_Y2: // 0xF1 - its use is prohibited
            {
                infof(dList, "CMD_Y2");
            }
			break;

		case CMD_Z2: // 0xF2 - its use is prohibited
            {
                infof(dList, "CMD_Z2");
            }
			break;

		case CMD_S2: // 0xF3 - its use is prohibited
            {
                infof(dList, "CMD_S2");
            }
			break;

		case CMD_T2: // 0xF4 - its use is prohibited
            {
                infof(dList, "CMD_T2");
            }
			break;

		case CMD_Q2: // 0xF5h - its use is prohibited
            {
                infof(dList, "CMD_Q2");
            }
			break;

		case CMD_RGB2: // 0xF6 - its use is prohibited
            {
                infof(dList, "CMD_RGB2");
            }
			break;

		case CMD_AP2: // 0xF7 - its use is prohibited
            {
                infof(dList, "CMD_AP2");
            }
			break;

		case CMD_F2: // 0xF8 - its use is prohibited
            {
                infof(dList, "CMD_F2");
            }
			break;

		case CMD_I2: // 0xF9 - its use is prohibited
            {
                infof(dList, "CMD_I2");
            }
			break;

        case 0xFF: // 0xFF - dummy command to avoid skinning/morphing hardware bug
            break;

		default:
            {
                errorf(dList,"Unknown CMD! %u", operation);
            }
			break;
		}

		list.pc += 4;
	}
}

