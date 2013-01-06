        case 0: /* SPECIAL */
            switch ((opcode >> 0) & 0x0000003f)
            {
            case 0: IDO(SLL);

            case 1: break;

            case 2: if ((opcode & 0x00200000) == 0x00000000) IDO(SRL); else IDO(ROTR);
            case 3: IDO(SRA);
            case 4: IDO(SLLV);

            case 5: break;

            case 6: if ((opcode & 0x00000040) == 0x00000000) IDO(SRLV); else IDO(ROTRV);
            case 7: IDO(SRAV);
            case 8: IDO(JR);
            case 9: if ((opcode & 0x0000F800) == 0x0000F800) IDO(RET); else IDO(JALR);
            case 10: IDO(MOVZ);
            case 11: IDO(MOVN);
            case 12: IDO(SYSCALL);
            case 13: IDO(BREAK);

            case 14: break;

            case 15: IDO(SYNC);
            case 16: IDO(MFHI);
            case 17: IDO(MTHI);
            case 18: IDO(MFLO);
            case 19: IDO(MTLO);

            case 20:
            case 21: break;

            case 22: IDO(CLZ);
            case 23: IDO(CLO);
            case 24: IDO(MULT);
            case 25: IDO(MULTU);
            case 26: IDO(DIV);
            case 27: IDO(DIVU);
            case 28: IDO(MADD);
            case 29: IDO(MADDU);

            case 30:
            case 31: break;

            case 32: IDO(ADD);
            case 33: IDO(ADDU);
            case 34: IDO(SUB);
            case 35: IDO(SUBU);
            case 36: IDO(AND);
            case 37: IDO(OR);
            case 38: IDO(XOR);
            case 39: IDO(NOR);

            case 40:
            case 41: break;

            case 42: IDO(SLT);
            case 43: IDO(SLTU);
            case 44: IDO(MAX);
            case 45: IDO(MIN);
            case 46: IDO(MSUB);
            case 47: IDO(MSUBU);

            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
            case 56:
            case 57:
            case 58:
            case 59:
            case 60:
            case 61:
            case 62:
            case 63: break;
            }

            break;

        case 1: /* REGIMM */
            switch ((opcode >> 16) & 0x00000003)
            {
            case 0: if ((opcode & 0x00100000) == 0x00000000)  IDO(BLTZ); else IDO(BLTZAL);
            case 1: if ((opcode & 0x00100000) == 0x00000000)  IDO(BGEZ); else IDO(BGEZAL);
            case 2: if ((opcode & 0x00100000) == 0x00000000)  IDO(BLTZL); else IDO(BLTZALL);
            case 3: if ((opcode & 0x00100000) == 0x00000000)  IDO(BGEZL); else IDO(BGEZALL);
            }

            break;

        case 2: IDO(J);
        case 3: IDO(JAL);
        case 4: IDO(BEQ);
        case 5: IDO(BNE);
        case 6: IDO(BLEZ);
        case 7: IDO(BGTZ);
        case 8: IDO(ADDI);
        case 9: IDO(ADDIU);
        case 10: IDO(SLTI);
        case 11: IDO(SLTIU);
        case 12: IDO(ANDI);
        case 13: IDO(ORI);
        case 14: IDO(XORI);
        case 15: IDO(LUI);

        case 16: /* COP0 */
            switch ((opcode >> 22) & 0x00000003)
            {
            case 0: if ((opcode & 0x00000008) == 0x00000000)  IDO(MFC0); else IDO(ERET);
            case 1: IDO(CFC0);
            case 2: IDO(MTC0);
            case 3: IDO(CTC0);
            }

            break;

        case 17: /* COP1 */
            switch ((opcode >> 23) & 0x00000007)
            {
            case 0: if ((opcode & 0x00400000) == 0x00000000)  IDO(MFC1); else IDO(CFC1);
            case 1: if ((opcode & 0x00400000) == 0x00000000)  IDO(MTC1); else IDO(CTC1);

            case 2:
                switch ((opcode >> 16) & 0x00000003)
                {
                case 0: IDO(BC1F);
                case 1: IDO(BC1T);
                case 2: IDO(BC1FL);
                case 3: IDO(BC1TL);
                };

                break;

            case 3: break;

            case 4:
                switch ((opcode >> 0) & 0x0000001f)
                {
                case 0: IDO(ADD_S);
                case 1: IDO(SUB_S);
                case 2: IDO(MUL_S);
                case 3: IDO(DIV_S);
                case 4: if ((opcode & 0x00000020) == 0x00000000)  IDO(SQRT_S); else IDO(CVT_W_S);
                case 5: IDO(ABS_S);
                case 6: IDO(MOV_S);
                case 7: IDO(NEG_S);

                case 8:
                case 9:
                case 10:
                case 11: break;

                case 12: IDO(ROUND_W_S);
                case 13: IDO(TRUNC_W_S);
                case 14: IDO(CEIL_W_S);
                case 15: IDO(FLOOR_W_S);
                case 16: IDO(C_F_S);	
                case 17: IDO(C_UN_S);
                case 18: IDO(C_EQ_S);
                case 19: IDO(C_UEQ_S);
                case 20: IDO(C_OLT_S);
                case 21: IDO(C_ULT_S);
                case 22: IDO(C_OLE_S);
                case 23: IDO(C_ULE_S);
                case 24: IDO(C_SF_S);
                case 25: IDO(C_NGLE_S);
                case 26: IDO(C_SEQ_S);
                case 27: IDO(C_NGL_S);
                case 28: IDO(C_LT_S);
                case 29: IDO(C_NGE_S);
                case 30: IDO(C_LE_S);
                case 31: IDO(C_NGT_S);
                }

                break;

            case 5: IDO(CVT_S_W);

            case 6:
            case 7: break;
            }

            break;

        case 18: /* VFPU2 */
            if ((opcode & 0x00200000) == 0x00000000)
            {
                switch ((opcode >> 16) & 0x00000003)
                {
                case 0: IDO(BVF);
                case 1: IDO(BVT);
                case 2: IDO(BVFL);
                case 3: IDO(BVTL);
                }
            }
            else
            {
                if ((opcode & 0x00000080) == 0x00000000)
                {
                    if ((opcode & 0x00800000) == 0x00000000)  IDO(MFV); else IDO(MTV);
                }
                else
                {
                    if ((opcode & 0x00800000) == 0x00000000)  IDO(MFVC); else IDO(MTVC);
                }
            }

            break;

        case 19: break;

        case 20: IDO(BEQL);
        case 21: IDO(BNEL);
        case 22: IDO(BLEZL);
        case 23: IDO(BGTZL);

        case 24: /* VFPU0 */
            switch ((opcode >> 23) & 0x00000003)
            {
            case 0: IDO_VSIZE(opcode, IDO(VADD_S), IDO(VADD_P), IDO(VADD_T), IDO(VADD_Q));
            case 1: IDO_VSIZE(opcode, IDO(VSUB_S), IDO(VSUB_P), IDO(VSUB_T), IDO(VSUB_Q));
            case 2: IDO_VSIZE(opcode, IDO(VSBN_S), break,       break,       break);
            case 3: IDO_VSIZE(opcode, IDO(VDIV_S), IDO(VDIV_P), IDO(VDIV_T), IDO(VDIV_Q));
            }

            break;

        case 25: /* VFPU1 */
            switch ((opcode >> 23) & 0x00000007)
            {
            case 0: IDO_VSIZE(opcode, IDO(VMUL_S), IDO(VMUL_P), IDO(VMUL_T), IDO(VMUL_Q));
            case 1: IDO_VSIZE(opcode, break,       IDO(VDOT_P), IDO(VDOT_T), IDO(VDOT_Q));
            case 2: IDO_VSIZE(opcode, break,       IDO(VSCL_P), IDO(VSCL_T), IDO(VSCL_Q));

            case 3: break;

            case 4: IDO_VSIZE(opcode, break,       IDO(VHDP_P), IDO(VHDP_T), IDO(VHDP_Q));
            case 5: IDO_VSIZE(opcode, break,       break,       IDO(VCRS_T), break      );
            case 6: IDO_VSIZE(opcode, break,       IDO(VDET_P), break,       break      );

            case 7: break;
            }

            break;

        case 26: break;

        case 27: /* VFPU3 */
            switch ((opcode >> 23) & 0x00000007)
            {
            case 0: IDO_VSIZE(opcode, IDO(VCMP_S), IDO(VCMP_P), IDO(VCMP_T), IDO(VCMP_Q));

            case 1: break;

            case 2: IDO_VSIZE(opcode, IDO(VMIN_S), IDO(VMIN_P), IDO(VMIN_T), IDO(VMIN_Q));
            case 3: IDO_VSIZE(opcode, IDO(VMAX_S), IDO(VMAX_P), IDO(VMAX_T), IDO(VMAX_Q));

            case 4: break;

            case 5: IDO_VSIZE(opcode, IDO(VSCMP_S), IDO(VSCMP_P), IDO(VSCMP_T), IDO(VSCMP_Q));
            case 6: IDO_VSIZE(opcode, IDO(VSGE_S),  IDO(VSGE_P),  IDO(VSGE_T),  IDO(VSGE_Q));
            case 7: IDO_VSIZE(opcode, IDO(VSLT_S),  IDO(VSLT_P),  IDO(VSLT_T),  IDO(VSLT_Q));
            }

            break;

        case 28: /* SPECIAL2 */
            if ((opcode & 0x00000002) == 0x00000000)
            {
                if ((opcode & 0x00000004) == 0x00000000)  IDO(HALT); else IDO(MFIC);
            }
            else
            {
                IDO(MTIC);
            }

            break;

        case 29:
        case 30: break;

        case 31: /* SPECIAL3 */
            if ((opcode & 0x00000021) == 0x00000020)
            {
                if ((opcode & 0x00000080) == 0x00000000)
                {
                    if ((opcode & 0x00000100) == 0x00000000)  IDO(SEH); else IDO(BITREV);
                }
                else
                {
                    if ((opcode & 0x00000040) == 0x00000000)  IDO(WSBH); else IDO(WSBW);
                }
            }
            else
            {
                if ((opcode & 0x00000001) == 0x00000000)
                {
                    if ((opcode & 0x00000004) == 0x00000000)  IDO(EXT); else IDO(INS);
                }
                else
                {
                    IDO(SEB);
                }
            }

            break;

        case 32: IDO(LB);
        case 33: IDO(LH);
        case 34: IDO(LWL);
        case 35: IDO(LW);
        case 36: IDO(LBU);
        case 37: IDO(LHU);
        case 38: IDO(LWR);

        case 40: IDO(SB);
        case 41: IDO(SH);
        case 42: IDO(SWL);
        case 43: IDO(SW);

        case 44:
        case 45: break;

        case 46: IDO(SWR);

        case 47: /* CACHE */
            switch ((opcode >> 17) & 0x0000000f)
            {
            case 0:
            case 1: break;

            case 2: IDO(ICACHE_INDEX_INVALIDATE);
            case 3: IDO(ICACHE_INDEX_UNLOCK);
            case 4: IDO(ICACHE_HIT_INVALIDATE);

            case 5: if ((opcode & 0x00010000) == 0x00000000)  IDO(ICACHE_FILL); else IDO(ICACHE_FILL_WITH_LOCK);

            case 6:
            case 7:
            case 8:
            case 9: break;

            case 10: IDO(DCACHE_INDEX_WRITEBACK_INVALIDATE);
            case 11: IDO(DCACHE_INDEX_UNLOCK);

            case 12:
                if ((opcode & 0x00010000) == 0x00000000)  IDO(DCACHE_CREATE_DIRTY_EXCLUSIVE); else IDO(DCACHE_HIT_INVALIDATE);

            case 13:
                if ((opcode & 0x00010000) == 0x00000000)  IDO(DCACHE_HIT_WRITEBACK); else IDO(DCACHE_HIT_WRITEBACK_INVALIDATE);

            case 14: IDO(DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK);

            case 15:
                if ((opcode & 0x00010000) == 0x00000000)  IDO(DCACHE_FILL); else IDO(DCACHE_FILL_WITH_LOCK);
            }

            break;

        case 48: IDO(LL);
        case 49: IDO(LWC1);
        case 50: IDO(LV_S);

        case 51: break;

        case 52: /* VFPU4 */
            {
                switch ((opcode >> 23) & 0x00000007)
                {
                case 0:
                    {
                        switch ((opcode >> 20) & 0x00000007)
                        {
                        case 0:
                            {
                                switch ((opcode >> 16) & 0x0000000F)
                                {
                                case 0: IDO_VSIZE(opcode, IDO(VMOV_S),  IDO(VMOV_P),  IDO(VMOV_T),  IDO(VMOV_Q));
                                case 1: IDO_VSIZE(opcode, IDO(VABS_S),  IDO(VABS_P),  IDO(VABS_T),  IDO(VABS_Q));
                                case 2: IDO_VSIZE(opcode, IDO(VNEG_S),  IDO(VNEG_P),  IDO(VNEG_T),  IDO(VNEG_Q));
                                case 3: IDO_VSIZE(opcode, IDO(VIDT_S),  IDO(VIDT_P),  IDO(VIDT_T),  IDO(VIDT_Q));
                                case 4: IDO_VSIZE(opcode, IDO(VSAT0_S), IDO(VSAT0_P), IDO(VSAT0_T), IDO(VSAT0_Q));
                                case 5: IDO_VSIZE(opcode, IDO(VSAT1_S), IDO(VSAT1_P), IDO(VSAT1_T), IDO(VSAT1_Q));
                                case 6: IDO_VSIZE(opcode, IDO(VZERO_S), IDO(VZERO_P), IDO(VZERO_T), IDO(VZERO_Q));
                                case 7: IDO_VSIZE(opcode, IDO(VONE_S),  IDO(VONE_P),  IDO(VONE_T),  IDO(VONE_Q));
                                }
                            }

                            break;
                        case 1:
                            {
                                switch ((opcode >> 16) & 0x0000000F)
                                {
                                case  0: IDO_VSIZE(opcode, IDO(VRCP_S),   IDO(VRCP_P),   IDO(VRCP_T),   IDO(VRCP_Q));
                                case  1: IDO_VSIZE(opcode, IDO(VRSQ_S),   IDO(VRSQ_P),   IDO(VRSQ_T),   IDO(VRSQ_Q));
                                case  2: IDO_VSIZE(opcode, IDO(VSIN_S),   IDO(VSIN_P),   IDO(VSIN_T),   IDO(VSIN_Q));
                                case  3: IDO_VSIZE(opcode, IDO(VCOS_S),   IDO(VCOS_P),   IDO(VCOS_T),   IDO(VCOS_Q));
                                case  4: IDO_VSIZE(opcode, IDO(VEXP2_S),  IDO(VEXP2_P),  IDO(VEXP2_T),  IDO(VEXP2_Q));
                                case  5: IDO_VSIZE(opcode, IDO(VLOG2_S),  IDO(VLOG2_P),  IDO(VLOG2_T),  IDO(VLOG2_Q));
                                case  6: IDO_VSIZE(opcode, IDO(VSQRT_S),  IDO(VSQRT_P),  IDO(VSQRT_T),  IDO(VSQRT_Q));
                                case  7: IDO_VSIZE(opcode, IDO(VASIN_S),  IDO(VASIN_P),  IDO(VASIN_T),  IDO(VASIN_Q));
                                case  8: IDO_VSIZE(opcode, IDO(VNRCP_S),  IDO(VNRCP_P),  IDO(VNRCP_T),  IDO(VNRCP_Q));
                                
                                case 10: IDO_VSIZE(opcode, IDO(VNSIN_S),  IDO(VNSIN_P),  IDO(VNSIN_T),  IDO(VNSIN_Q));
                                
                                case 12: IDO_VSIZE(opcode, IDO(VREXP2_S), IDO(VREXP2_P), IDO(VREXP2_T), IDO(VREXP2_Q));
                                }
                            }

                            break;
                        case 2:
                            {
                                switch ((opcode >> 16) & 0x0000000F)
                                {
                                case 0: IDO_VSIZE(opcode, IDO(VRNDS_S),  break,         break,         break);
                                case 1: IDO_VSIZE(opcode, IDO(VRNDI_S),  IDO(VRNDI_P),  IDO(VRNDI_T),  IDO(VRNDI_Q));
                                case 2: IDO_VSIZE(opcode, IDO(VRNDF1_S), IDO(VRNDF1_P), IDO(VRNDF1_T), IDO(VRNDF1_Q));
                                case 3: IDO_VSIZE(opcode, IDO(VRNDF2_S), IDO(VRNDF2_P), IDO(VRNDF2_T), IDO(VRNDF2_Q));
                                }
                            }

                            break;
                        case 3:
                            {
                                switch ((opcode >> 16) & 0x0000000F)
                                {
                                case  2: IDO_VSIZE(opcode, break,        IDO(VF2H_P),  break, IDO(VF2H_Q));
                                case  3: IDO_VSIZE(opcode, IDO(VH2F_S),  IDO(VH2F_P),  break, break);
                                
                                case  6: IDO_VSIZE(opcode, break,        IDO(VSBZ_P),  break, break);
                                case  7: IDO_VSIZE(opcode, IDO(VLGB_S),  break,        break, break);
                                case  8: IDO_VSIZE(opcode, IDO(VUC2I_S), break,        break, break);
                                case  9: IDO_VSIZE(opcode, IDO(VC2I_S),  break,        break, break);
                                case 10: IDO_VSIZE(opcode, IDO(VUS2I_S), IDO(VUS2I_P), break, break);
                                case 11: IDO_VSIZE(opcode, IDO(VS2I_S),  IDO(VS2I_P),  break, break);
                                case 12: IDO_VSIZE(opcode, break,        break,        break, IDO(VI2UC_Q));
                                case 13: IDO_VSIZE(opcode, break,        break,        break, IDO(VI2C_Q));
                                case 14: IDO_VSIZE(opcode, break,        IDO(VI2US_P), break, IDO(VI2US_Q));
                                case 15: IDO_VSIZE(opcode, break,        IDO(VI2S_P),  break, IDO(VI2S_Q));
                                }
                            }

                            break;

                        case 4:
                            {
                                switch ((opcode >> 16) & 0x0000000F)
                                {
                                case  0: IDO_VSIZE(opcode, break,        break,        break,       IDO(VSRT1_Q));
                                case  1: IDO_VSIZE(opcode, break,        break,        break,       IDO(VSRT2_Q));
                                case  2: IDO_VSIZE(opcode, break,        IDO(VBFY1_P), break,       IDO(VBFY1_Q));
                                case  3: IDO_VSIZE(opcode, break,        break,        break,       IDO(VBFY2_Q));
                                case  4: IDO_VSIZE(opcode, IDO(VOCP_S),  IDO(VOCP_P),  IDO(VOCP_T), IDO(VOCP_Q));
                                case  5: IDO_VSIZE(opcode, IDO(VSOCP_S), IDO(VSOCP_P), break,       break);
                                case  6: IDO_VSIZE(opcode, break,        IDO(VFAD_P),  IDO(VFAD_T), IDO(VFAD_Q));
                                case  7: IDO_VSIZE(opcode, break,        IDO(VAVG_P),  IDO(VAVG_T), IDO(VAVG_Q));
                                case  8: IDO_VSIZE(opcode, break,        break,        break,       IDO(VSRT3_Q));
                                case  9: IDO_VSIZE(opcode, break,        break,        break,       IDO(VSRT4_Q));
                                case 10: IDO_VSIZE(opcode, IDO(VSGN_S),  IDO(VSGN_P),  IDO(VSGN_T), IDO(VSGN_Q));
                                }
                            }

                            break;

                        case 5:
                            {
                                switch ((opcode >> 16) & 0x0000000F)
                                {
                                case  0: IDO(VMTVC);
                                case  1: IDO(VMFVC);

                                case  9: IDO_VSIZE(opcode, break, break, break, IDO(VT4444_Q));
                                case 10: IDO_VSIZE(opcode, break, break, break, IDO(VT5551_Q));
                                case 11: IDO_VSIZE(opcode, break, break, break, IDO(VT5650_Q));
                                }
                            }

                            break;

                        case 6:
                        case 7:
                            IDO_VSIZE(opcode, IDO(VCST_S), IDO(VCST_P), IDO(VCST_T), IDO(VCST_Q));
                        }
                    }

                    break;
                case 4:
                    {
                        switch ((opcode >> 21) & 0x00000003)
                        {
                        case 0: IDO_VSIZE(opcode, IDO(VF2IN_S), IDO(VF2IN_P), IDO(VF2IN_T), IDO(VF2IN_Q));
                        case 1: IDO_VSIZE(opcode, IDO(VF2IZ_S), IDO(VF2IZ_P), IDO(VF2IZ_T), IDO(VF2IZ_Q));
                        case 2: IDO_VSIZE(opcode, IDO(VF2IU_S), IDO(VF2IU_P), IDO(VF2IU_T), IDO(VF2IU_Q));
                        case 3: IDO_VSIZE(opcode, IDO(VF2ID_S), IDO(VF2ID_P), IDO(VF2ID_T), IDO(VF2ID_Q));
                        }
                    }

                    break;
                case 5:
                    {
                        switch ((opcode >> 21) & 0x00000003)
                        {

                        case 0: IDO_VSIZE(opcode, IDO(VI2F_S),   IDO(VI2F_P),   IDO(VI2F_T),   IDO(VI2F_Q));
                        case 1:
                            {
                                if ((opcode & 0x00080000) == 0x00000000)
                                {
                                    IDO_VSIZE(opcode, IDO(VCMOVT_S), IDO(VCMOVT_P), IDO(VCMOVT_T), IDO(VCMOVT_Q));
                                }
                                else
                                {
                                    IDO_VSIZE(opcode, IDO(VCMOVF_S), IDO(VCMOVF_P), IDO(VCMOVF_T), IDO(VCMOVF_Q));
                                }
                            }
                        }
                    }

                    break;
                case 6:
                case 7: IDO_VSIZE(opcode, IDO(VWBN_S), break, break, break);
                }

                break;
            }

            break;

        case 53: if ((opcode & 0x00000002) == 0x00000000)  IDO(LVL_Q); else IDO(LVR_Q);

        case 54: IDO(LV_Q);

        case 55: /* VFPU5 */
            switch ((opcode >> 24) & 0x00000003)
            {
            case 0: IDO(VPFXS);
            case 1: IDO(VPFXT);
            case 2: IDO(VPFXD);
            case 3:
                {
                    if ((opcode & 0x00800000) == 0x00000000) IDO(VIIM); else IDO(VFIM);
                }

                break;
            }

            break;

        case 56: IDO(SC);
        case 57: IDO(SWC1);
        case 58: IDO(SV_S);

        case 59: break;

        case 60: /* VFPU6 */
            switch ((opcode >> 23) & 0x00000007)
            {
            case 0: IDO_VSIZE(opcode, break,         IDO(VMMUL_P),  IDO(VMMUL_T),  IDO(VMMUL_Q));
            case 1: IDO_VSIZE(opcode, IDO(VHTFM2_P), IDO(VTFM2_P),  break,         break);
            case 2: IDO_VSIZE(opcode, break,         IDO(VHTFM3_T), IDO(VTFM3_T),  break);
            case 3: IDO_VSIZE(opcode, break,         break,         IDO(VHTFM4_Q), IDO(VTFM4_Q));
            case 4: IDO_VSIZE(opcode, break,         IDO(VMSCL_P),  IDO(VMSCL_T),  IDO(VMSCL_Q));
            case 5: IDO_VSIZE(opcode, break,         break,         IDO(VCRSP_T),  IDO(VQMUL_Q));

            case 6: break;

            case 7:
                switch ((opcode >> 21) & 0x00000003)
                {
                case 0:
                    {
                        switch ((opcode >> 16) & 0x00000007)
                        {
                        case 0: IDO_VSIZE(opcode, break, IDO(VMMOV_P),  IDO(VMMOV_T),  IDO(VMMOV_Q));
                        case 3: IDO_VSIZE(opcode, break, IDO(VMIDT_P),  IDO(VMIDT_T),  IDO(VMIDT_Q));
                        case 6: IDO_VSIZE(opcode, break, IDO(VMZERO_P), IDO(VMZERO_T), IDO(VMZERO_Q));
                        case 7: IDO_VSIZE(opcode, break, IDO(VMONE_P),  IDO(VMONE_T),  IDO(VMONE_Q));
                        }
                    }
                    break;
                case 1: IDO_VSIZE(opcode, break, IDO(VROT_P), IDO(VROT_T), IDO(VROT_Q));
                }
            }

            break;

        case 61: if ((opcode & 0x00000002) == 0x00000000)  IDO(SVL_Q); else IDO(SVR_Q);

        case 62: IDO(SV_Q);

        case 63: /* VFPU7 */
            if ((opcode & 0x00000001) == 0x00000000)
            {
                if ((opcode & 0x00000020) == 0x00000000)  IDO(VNOP); else IDO(VSYNC);
            }
            else
            {
                IDO(VFLUSH);
            }

            break;
