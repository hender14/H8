/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (���� H8/300H �p)                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__H83__hospac_h__
#define __HOS_V4__H83__hospac_h__



#include "itron.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ���荞�݃}�X�N��` */
#define H83_IMSK_I_BIT		0x80	/* ���荞�݃}�X�N�r�b�g */
#define H83_IMSK_UI_BIT		0x40	/* ���[�U�[�r�b�g�^���荞�݃}�X�N�r�b�g */

#define H83_IMSK_LEVEL0		0x00								/* �v���C�I���e�B�[���x��0/1������ */
#define H83_IMSK_LEVEL1		(H83_IMSK_I_BIT)					/* �v���C�I���e�B�[���x��1�̂݋��� */
#define H83_IMSK_LEVEL2		(H83_IMSK_I_BIT | H83_IMSK_UI_BIT)	/* ���ׂċ֎~ */



/* ------------------------------------------ */
/*                   �^��`                   */
/* ------------------------------------------ */

typedef UB	IMSK;		/* ���荞�݃}�X�N */


/* �R���e�L�X�g���ۑ��u���b�N */
typedef struct t_hos_pac_ctxinf
{
	VP sp;
} T_HOSPAC_CTXINF;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

extern UB kernel_h83_imsk;		/* ���荞�݃}�X�N�l */
extern UB kernel_h83_ibmsk;		/* ���荞�݃x�[�X�}�X�N�l */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

void hospac_ini_sys(void);			/* �V�X�e���̏����� */

void hospac_dis_int(void);			/* ���荞�݋֎~ */
void hospac_ena_int(void);			/* ���荞�݋��� */

#if ( __CPU__ == 2 ) /* �H��C H8/300HN */
void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					FP task, VP sp, VP_INT exinf);			/* ���s�R���e�L�X�g�̍쐬(�A�Z���u���p) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk)	\
	hospac_cre_ctx_asm(pk_ctxinf, task, ((VP)((UB *)(stk) + ((stksz) & 0xfffffffc))), exinf)
#else				/* �H��C H8/300H or GCC */
void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);			/* ���s�R���e�L�X�g�̍쐬(�A�Z���u���p) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk)	\
	hospac_cre_ctx_asm(pk_ctxinf, ((VP)((UB *)(stk) + ((stksz) & 0xfffffffc))), task, exinf)
#endif
	/* �A�Z���u�����œs���������悤�Ɉ��������ւ� */
#define hospac_del_ctx(pk_ctxinf)	do {} while (0)			/* ���s�R���e�L�X�g�̍폜(�s�v) */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* ���s�R���e�L�X�g�̐ؑ� */
#define hospac_idle()	do {} while (0)						/* �A�C�h�����̓���(�������Ȃ�) */


ER chg_imsk(IMSK imsk);				/* ���荞�݃}�X�N�̃x�[�X�l�̕ύX */
ER get_imsk(IMSK *p_imsk);			/* ���荞�݃}�X�N�̃x�[�X�l�̎Q�� */

ER fchg_imsk(IMSK imsk);			/* ���݂̊����݃}�X�N�l�̋����ύX */
ER fget_imsk(IMSK *p_imsk);			/* ���݂̊����݃}�X�N�l�̋����Q�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__H83__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
