/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (ARM �p)                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__ARM__hospac_h__
#define __HOS_V4__ARM__hospac_h__


#include "itron.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ARM�ŗL ���荞�݊Ǘ��@�\ */
#define ARM_IMSK_USR_MODE		0x00000010		/* ���[�U�[���[�h */
#define ARM_IMSK_FIQ			0x00000040		/* FIQ�}�X�N�r�b�g */
#define ARM_IMSK_IRQ			0x00000080		/* IRQ�}�X�N�r�b�g */



/* ------------------------------------------ */
/*                   �^��`                   */
/* ------------------------------------------ */

/* �R���e�L�X�g���ۑ��u���b�N */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* �X�^�b�N�|�C���^�ۑ��̈� */
} T_HOSPAC_CTXINF;


/* ARM�ŗL ���荞�݊Ǘ��@�\ */
typedef UW		IMSK;			/* ���荞�݃}�X�N */



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

extern UW hospac_arm_imsk;		/* ���荞�݃}�X�N */
extern UW hospac_arm_bimsk;		/* �x�[�X���荞�݃}�X�N */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

#define hospac_ini_sys()	hos_arm_ini_int()		/* �v���Z�b�T���ۉ��R���|�[�l���g�̏����� */
void hospac_dis_int(void);							/* ���荞�݋֎~ */
void hospac_ena_int(void);							/* ���荞�݋��� */
void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* ���s�R���e�L�X�g�̍쐬(�A�Z���u���p) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk) \
	hospac_cre_ctx_asm(pk_ctxinf, (VP)((UB *)(stk) + ((stksz) & 0xfffffffc)), task, exinf);
													/* �A�Z���u�����œs���������悤�Ɉ��������ւ� */
#define hospac_del_ctx(pk_ctxinf)					/* ���s�R���e�L�X�g�̍폜 */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* ���s�R���e�L�X�g�̐ؑ� */

#define hospac_idle()				/* �A�C�h�������� */

void  hos_arm_ini_int(void);		/* ���荞�ݏ����̏������i���[�U�[�쐬�֐��j */ 
INTNO hos_arm_sta_irq(void);		/* IRQ���荞�ݏ����J�n�i���[�U�[�쐬�֐��j */
void  hos_arm_end_irq(void);		/* IRQ���荞�ݏ����I���i���[�U�[�쐬�֐��j */
INTNO hos_arm_sta_fiq(void);		/* FIQ���荞�ݏ����J�n�i���[�U�[�쐬�֐��j */
void  hos_arm_end_fiq(void);		/* FIQ���荞�ݏ����I���i���[�U�[�쐬�֐��j */


/* ARM�ŗL ���荞�݊Ǘ��@�\ */
ER    chg_imsk(IMSK imsk);			/* ���荞�݃}�X�N�w�� */
ER    get_imsk(IMSK *p_imsk);		/* ���荞�݃}�X�N�̎Q�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__ARM__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
