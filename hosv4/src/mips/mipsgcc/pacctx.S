#include "mipsregs.h"

#define SF_SIZE (4*72)        
/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (MIPS4�݊��R�A�p)                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
                .global hospac_dis_int         /* ���荞�݋֎~ */
                .global hospac_ena_int         /* ���荞�݋��� */
                .global hospac_cre_ctx_asm     /* ���s�R���e�L�X�g�̍쐬 */
                .global hospac_swi_ctx         /* ���s�R���e�L�X�g�̐ؑ� */

/************************************************
  ���荞�݋֎~
  void hospac_dis_int(void)
************************************************/
/* �X�e�[�^�X�E���W�X�^��IE�r�b�g��0�ɂ��� */
                .text
                .align  2
hospac_dis_int:
                mfc0    t0, CP0_STATUS          /* CP0���W�X�^�����[�h */
                la      t1, 0xfffffffe          /* IE=0 */
                and     t0, t0, t1
                mtc0    t0, CP0_STATUS          /* CP0���W�X�^���X�g�A */
                jr      ra
                nop

/************************************************
  ���荞�݋���
  void hospac_ena_int(void)
************************************************/
/* �X�e�[�^�X�E���W�X�^��IE�r�b�g��1�ɂ��� */
                .text
                .align  2
hospac_ena_int:
                mfc0    t0, CP0_STATUS          /* CP0���W�X�^�����[�h */
                la      t1, 0x00000001          /* IE=1 */
                or      t0, t0, t1
                mtc0    t0, CP0_STATUS          /* CP0���W�X�^���X�g�A */
                jr      ra
                nop

/************************************************
  ���s�R���e�L�X�g�G���g���[�A�h���X
************************************************/
                .text
                .align 2
ctx_entry:      
                j       a1                      /* ���s�A�h���Xa1�ɃW�����v�Ba0�����s���p�����[�^ */
                nop

/************************************************
  ���s�R���e�L�X�g�̍쐬
  void hospac_cre_ctx_asm(
         T_HOSPAC_CTXINF *pk_ctxinf,    �쐬����R���e�L�X�g
         VP     sp,                     �X�^�b�N�|�C���^
         void   (*task)(VP_INT),        ���s�A�h���X
         VP_INT exinf)                  ���s���p�����[�^
************************************************/
                .text
                .align 2
hospac_cre_ctx_asm:
                move    k0, a1                  /* �X�^�b�N�|�C���^��ޔ� */
                subu    a1, a1, SF_SIZE         /* �X�^�b�N�̐L���i4*72=288�o�C�g�j*/
//                sw      a2, 4*5(a1)             /* ���s�A�h���X�̊i�[ */
                sw      a3, 4*4(a1)             /* ���s�p�����[�^�̊i�[ */
                sw      k0, 4*29(a1)            /* �X�^�b�N�|�C���^�̐ݒ� */
#if 0        
                la      k0, ctx_entry           /* ���s�G���g���|�C���g�����^�[���A�h���X�ɐݒ� */
                sw      k0, 4*31(a1)
#else
                sw      a2, 4*31(a1)
#endif
                mfc0    k0, CP0_STATUS          /* CP0_STATUS��ޔ� */
                sw      k0, 4*36(a1)
                
                sw      a1, (a0)                /* �R���e�L�X�g�̃X�^�b�N�|�C���^�ۑ� */
                jr      ra                      /* �Ăяo�����֋A�� */
                nop

/************************************************
  ���s�R���e�L�X�g�̐ؑ�
  void hospac_swi_ctx(
        T_HOSPAC_CTXINF *pk_pre_ctxinf, ���݂̃R���e�L�X�g�̕ۑ���
        T_HOSPAC_CTXINF *pk_nxt_ctxinf) �؂�ւ���R���e�L�X�g
************************************************/
                .text
                .align 2
hospac_swi_ctx:
                move    k0, sp                  /* �L���O�̃X�^�b�N�|�C���^��ޔ� */
                subu    sp, sp, SF_SIZE         /* �X�^�b�N��L�� */
#if 0
                sw      $0, 4*0(sp)             /* zero ��ޔ��i�K�v�Ȃ��j*/
                .set noat
                sw      $1, 4*1(sp)             /* at   ��ޔ� */
#endif        
                sw      $2, 4*2(sp)             /* v0   ��ޔ� */
                sw      $3, 4*3(sp)             /* v1   ��ޔ� */
                sw      $4, 4*4(sp)             /* a0   ��ޔ� */
                sw      $5, 4*5(sp)             /* a1   ��ޔ� */
                sw      $6, 4*6(sp)             /* a2   ��ޔ� */
                sw      $7, 4*7(sp)             /* a3   ��ޔ� */
                sw      $8, 4*8(sp)             /* t0   ��ޔ� */
                sw      $9, 4*9(sp)             /* t1   ��ޔ� */
                sw      $10, 4*10(sp)           /* t2   ��ޔ� */
                sw      $11, 4*11(sp)           /* t3   ��ޔ� */
                sw      $12, 4*12(sp)           /* t4   ��ޔ� */
                sw      $13, 4*13(sp)           /* t5   ��ޔ� */
                sw      $14, 4*14(sp)           /* t6   ��ޔ� */
                sw      $15, 4*15(sp)           /* t7   ��ޔ� */
                sw      $16, 4*16(sp)           /* s0   ��ޔ� */
                sw      $17, 4*17(sp)           /* s1   ��ޔ� */
                sw      $18, 4*18(sp)           /* s2   ��ޔ� */
                sw      $19, 4*19(sp)           /* s3   ��ޔ� */
                sw      $20, 4*20(sp)           /* s4   ��ޔ� */
                sw      $21, 4*21(sp)           /* s5   ��ޔ� */
                sw      $22, 4*22(sp)           /* s6   ��ޔ� */
                sw      $23, 4*23(sp)           /* s7   ��ޔ� */
                sw      $24, 4*24(sp)           /* t8   ��ޔ� */
                sw      $25, 4*25(sp)           /* t9   ��ޔ� */
                sw      $26, 4*26(sp)           /* k0   ��ޔ��i�K�v�Ȃ��H�j*/
                sw      $27, 4*27(sp)           /* k1   ��ޔ��i�K�v�Ȃ��H�j*/
#if 0
                sw      $28, 4*28(sp)           /* gp   ��ޔ��i�K�v�Ȃ��H�j*/
#endif
                sw      k0,  4*29(sp)           /* sp   ��ޔ��i�L���O�̒l�j*/
#if 1
                sw      $30, 4*30(sp)           /* fp   ��ޔ��i�K�v�Ȃ��H�j*/
#endif
                sw      $31, 4*31(sp)           /* ra   ��ޔ� */

                sw      sp, (a0)                /* sp���Ǘ��̈�֑ޔ� */
                lw      sp, (a1)                /* �Ǘ��̈悩��sp�𕜋A */
                lw      $2, 4*2(sp)             /* v0   �𕜋A */
                lw      $3, 4*3(sp)             /* v1   �𕜋A */
                lw      $4, 4*4(sp)             /* a0   �𕜋A */
                lw      $5, 4*5(sp)             /* a1   �𕜋A */
                lw      $6, 4*6(sp)             /* a2   �𕜋A */
                lw      $7, 4*7(sp)             /* a3   �𕜋A */
                lw      $8, 4*8(sp)             /* t0   �𕜋A */
                lw      $9, 4*9(sp)             /* t1   �𕜋A */
                lw      $10, 4*10(sp)           /* t2   �𕜋A */
                lw      $11, 4*11(sp)           /* t3   �𕜋A */
                lw      $12, 4*12(sp)           /* t4   �𕜋A */
                lw      $13, 4*13(sp)           /* t5   �𕜋A */
                lw      $14, 4*14(sp)           /* t6   �𕜋A */
                lw      $15, 4*15(sp)           /* t7   �𕜋A */
                lw      $16, 4*16(sp)           /* s0   �𕜋A */
                lw      $17, 4*17(sp)           /* s1   �𕜋A */
                lw      $18, 4*18(sp)           /* s2   �𕜋A */
                lw      $19, 4*19(sp)           /* s3   �𕜋A */
                lw      $20, 4*20(sp)           /* s4   �𕜋A */
                lw      $21, 4*21(sp)           /* s5   �𕜋A */
                lw      $22, 4*22(sp)           /* s6   �𕜋A */
                lw      $23, 4*23(sp)           /* s7   �𕜋A */
                lw      $24, 4*24(sp)           /* t8   �𕜋A */
                lw      $25, 4*25(sp)           /* t9   �𕜋A */
                lw      $26, 4*26(sp)           /* k0   �𕜋A�i�K�v�Ȃ��H�j*/
                lw      $27, 4*27(sp)           /* k1   �𕜋A�i�K�v�Ȃ��H�j*/
#if 0
                lw      $28, 4*28(sp)           /* gp   �𕜋A�i�K�v�Ȃ��H�j*/
#endif
                lw      $30, 4*30(sp)           /* fp   �𕜋A�i�K�v�Ȃ��H�j*/
                lw      $31, 4*31(sp)           /* ra   �𕜋A */

                lw      $29, 4*29(sp)           /* sp   �𕜋A */
                jr      ra                      /* �R���e�L�X�g�փW�����v */
                nop

/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */