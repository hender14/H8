/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (MIPS3�݊��R�A�p)                      */
/*    ���荞�݃n���h��                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "mipsregs.h"

                .global int_handler     /* ���荞�݃n���h�� */
        
/**
 * ���荞�݃n���h��
 * �����Ŋ��荞�ݗv���𔻒肵�ēo�^�����n���h�����Ăяo���B
 * ���݂̓^�C�}���荞�݂����T�|�[�g���Ă��Ȃ��B
 */
				.text
				.align	2
int_handler:	
				/* ���W�X�^�ޔ�(r1-r1) */
                move    k0, sp          /* �L���O�̃X�^�b�N�|�C���^��ޔ� */
                addiu   sp, -288        /* �X�^�b�N�t���[���̊m�� */
                sw      $2, 4*2(sp)
                sw      $3, 4*3(sp)
                sw      $4, 4*4(sp)
                sw      $5, 4*5(sp)
                sw      $6, 4*6(sp)
                sw      $7, 4*7(sp)
                sw      $8, 4*8(sp)
                sw      $9, 4*9(sp)
                sw      $10, 4*10(sp)
                sw      $11, 4*11(sp)
                sw      $12, 4*12(sp)
                sw      $13, 4*13(sp)
                sw      $14, 4*14(sp)
                sw      $15, 4*15(sp)
                sw      $16, 4*16(sp)
                sw      $17, 4*17(sp)
                sw      $18, 4*18(sp)
                sw      $19, 4*19(sp)
                sw      $20, 4*20(sp)
                sw      $21, 4*21(sp)
                sw      $22, 4*22(sp)
                sw      $23, 4*23(sp)
                sw      $24, 4*24(sp)
                sw      $25, 4*25(sp)
                sw      $26, 4*26(sp)
                sw      $27, 4*27(sp)
                sw      k0,  4*29(sp)           /* sp   ��ޔ��i�L���O�̒l�j*/
                sw      $31, 4*31(sp)           /* ra��ޔ�*/

        		mfc0	v1, CP0_EPC
        		sw      v1, 4*34(sp)            /* EPC��ޔ� */

           		/* �X�^�b�N�̑ޔ� */
                la      k0, kernel_int_ssp
                sw      sp, (k0)
                la      k0, kernel_int_sp
                lw      sp, (k0)

				/* ���荞�݊J�n�����Ăяo�� */
				la      k0, kernel_sta_int
				jal		k0
				nop

                /* ���荞�ݔԍ����������Ď��s�����Ăяo��
                �i�Ƃ肠�����^�C�}���荞�݂�����������Ƃ���B���荞�݃x�N�^�ԍ�=1�j*/
                la      k0, kernel_exe_int
                li      a0, 1
                jal     k0
                nop
        
           		/* �X�^�b�N�̕��A */
                la      k0, kernel_int_ssp
                lw      sp, (k0)

                /* IE=0, EXL=0�ɃZ�b�g�i���荞�݂͋֎~�̂܂܁j*/
                mfc0    k0, CP0_STATUS
                la      k1, 0xfffffffc
                and     k0, k0, k1                      /* IE=0, EXL=0 */
                mtc0    k0, CP0_STATUS

				/* ���荞�ݏI�������Ăяo�� */
                la      k0, kernel_end_int
				jal     k0
				nop

                /* IE=1, EXL=1�ɃZ�b�g�i���荞�݂͋֎~�̂܂܁j*/
                mfc0    k0, CP0_STATUS
                la      k1, 0x00000003
                or      k0, k0, k1                      /* IE=1, EXL=1 */
                mtc0    k0, CP0_STATUS

				/* ���W�X�^���A */
                lw      $2, 4*2(sp)
                lw      $3, 4*3(sp)
                lw      $4, 4*4(sp)
                lw      $5, 4*5(sp)
                lw      $6, 4*6(sp)
                lw      $7, 4*7(sp)
                lw      $8, 4*8(sp)
                lw      $9, 4*9(sp)
                lw      $10, 4*10(sp)
                lw      $11, 4*11(sp)
                lw      $12, 4*12(sp)
                lw      $13, 4*13(sp)
                lw      $14, 4*14(sp)
                lw      $15, 4*15(sp)
                lw      $16, 4*16(sp)
                lw      $17, 4*17(sp)
                lw      $18, 4*18(sp)
                lw      $19, 4*19(sp)
                lw      $20, 4*20(sp)
                lw      $21, 4*21(sp)
                lw      $22, 4*22(sp)
                lw      $23, 4*23(sp)
                lw      $24, 4*24(sp)
                lw      $25, 4*25(sp)
                lw      $26, 4*26(sp)
                lw      $27, 4*27(sp)
                lw      $31, 4*31(sp)           /* ra�̕��A */
        
        		lw      v1, 4*34(sp)            /* EPC�̕��A */
         		mtc0	v1, CP0_EPC
                lw      $29, 4*29(sp)           /* �X�^�b�N�|�C���^�̕��A */

                eret

/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */