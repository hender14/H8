/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (MIPS�p)                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2007 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__MIPS__hospac_h__
#define __HOS_V4__MIPS__hospac_h__

/* ------------------------------------------ */
/*                   �^��`                   */
/* ------------------------------------------ */

/* �R���e�L�X�g���ۑ��u���b�N */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* �X�^�b�N�|�C���^�ۑ��̈� */
} T_HOSPAC_CTXINF;



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

#define hospac_ini_sys()							/* �v���Z�b�T���ۉ��R���|�[�l���g�̏����� */
void hospac_dis_int(void);							/* ���荞�݋֎~ */
void hospac_ena_int(void);							/* ���荞�݋��� */
void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* ���s�R���e�L�X�g�̍쐬(�A�Z���u���p) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk)	\
	hospac_cre_ctx_asm(pk_ctxinf, (VP)((UB *)(stk) + ((stksz) & 0xfffffffc)), task, exinf)
													/* �A�Z���u�����œs���������悤�Ɉ��������ւ� */
#define hospac_del_ctx(pk_ctxinf)					/* ���s�R���e�L�X�g�̍폜 */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* ���s�R���e�L�X�g�̐ؑ� */
#define hospac_idle()   /* �A�C�h�������� */

#ifdef __cplusplus
}
#endif

#endif	/* __HOS_V4__MIPS__hospac_h__ */

/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2007 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
