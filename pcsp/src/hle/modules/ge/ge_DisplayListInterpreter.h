#pragma once

#include <vector>

#include "types.h"
#include "ge_Decoder.h"
#include "ge_Types.h"
#include "sceGe_user.h"
#include "ge_Context.h"

#define pc_address_mask 0xFFFFFFFC

class DisplayList
{
private:

public:
	int id;
	u32 pc;
	u32 stall_addr;
	u32 stack[64];
	u32 stack_ptr;

	DisplayList()
	{
		id = 0;
		u32 pc = 0;
		u32 stall_addr = 0;
		
		memset(stack, 0, sizeof(u32) * 64);
		stack_ptr = 0;
	}

	void push_stack(u32 pushable)
	{
		stack[stack_ptr++] = pushable;
	}

	u32 pop_stack()
	{
		return stack[--stack_ptr];
	}

	u32 get_address_rel(u32 argument) {
    	return normalizeAddress((theGeContext.base_address | argument));
    }

	u32 get_address_rel_offset(u32 argument) {
    	return normalizeAddress((theGeContext.base_address | argument) + theGeContext.offset_address);
    }

	void call_absolute(u32 argument) 
	{
    	push_stack(pc);
    	push_stack(theGeContext.offset_address);
    	jumpAbsolute(argument);
    }

	void jumpAbsolute(u32 argument) {
    	pc = normalizeAddress(argument) & pc_address_mask;
    }

	void call_relative_offset(u32 argument) 
	{
    	push_stack(pc);
    	push_stack(theGeContext.offset_address);
    	jump_relative_offset(argument);
    }

	void jump_relative_offset(u32 argument)
	{
		pc = get_address_rel_offset(argument) & pc_address_mask;
	}

	u32 normalizeAddress(u32 address) 
	{
		address = address & Memory::address_mask;
    	// Test on a PSP: 0x4200000 is equivalent to 0x4000000
    	if ((address & 0xFF000000) == sceGe_user::START_VRAM) {
    	    address &= 0xFF1FFFFF;
    	}
    	return address;
    }

	void ret_stack()
	{
		if (!(stack_ptr <= 0)) 
		{
    		theGeContext.offset_address = pop_stack();
    		pc = pop_stack();
    	}
	}

};

class ge_DisplayListInterpreter
{
public:
	ge_DisplayListInterpreter();
	~ge_DisplayListInterpreter();
	
	u32		Add(u32 inListPC, u32 inStallAddr);
	void	UpdateStall(int inListId, u32 inNewStall);
	
	bool	InterpretDisplayLists();
	bool	InterpretDisplayList(DisplayList &list);

private:
	std::vector<DisplayList>	mDisplayLists; 
};

extern ge_DisplayListInterpreter	theDisplayInterpreter;
extern ge_VertexInfo				lastVertInfo;