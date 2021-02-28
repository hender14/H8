/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ �^�X�N�Ǘ�                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_tsk_h__
#define __HOS_V4__knl_tsk_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_TSKID	TMIN_TSKID			/* �^�X�NID�̍ŏ��l */
#define KERNEL_TMAX_TSKID	(KERNEL_TMIN_TSKID + kernel_tcb_cnt - 1)
												/* �^�X�NID�̍ő�l */

/* �r�b�g�p�^�[���̃r�b�g�� */
#define TBIT_TEXPTN			16					/* �^�X�N��O�v���̃r�b�g�� */
												/* �^�X�NID�̍ő�l */


/* �L���[�C���O�^�l�X�g�񐔂̍ő�l */
#define TMAX_ACTCNT			255					/* �^�X�N�N���v���L���[�C���O���̍ő�l */
#define TMAX_WUPCNT			65535				/* �^�X�N�N���v���L���[�C���O���̍ő�l */
#define TMAX_SUSCNT			255					/* �^�X�N�����҂��v���l�X�g���̍ő�l */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �^�X�N������� */
typedef struct t_ctsk
{
	ATR     tskatr;			/* �^�X�N���� */
	VP_INT  exinf;			/* �^�X�N�̊g����� */
	FP      task;			/* �^�X�N�̋N���Ԓn */
	PRI     itskpri;		/* �^�X�N�̋N�����D��x */
	SIZE    stksz;			/* �X�^�b�N�̈�̃T�C�Y(�o�C�g��) */
	VP      stk;			/* �X�^�b�N�̈�̐擪�Ԓn */
} T_CTSK;

/* �^�X�N��� */
typedef struct t_rtsk
{
	STAT   tskstat;			/* �^�X�N��� */
	PRI    tskpri;			/* �^�X�N�̌��ݗD��x */
	PRI	   tskbpri;			/* �^�X�N�̃x�[�X�D��x */
	STAT   tskwait;			/* �҂��v�� */
	ID     wobjid;			/* �҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ� */
	TMO    lefttmo;			/* �^�C���A�E�g����܂ł̎��� */
	UINT   actcnt;			/* �N���v���L���[�C���O�� */
	UINT   wupcnt;			/* �N���v���L���[�C���O�� */
	UINT   suscnt;			/* �����҂��v���l�X�g�� */
	VP_INT exinf;			/* �^�X�N�̊g����� */
} T_RTSK;

/* �^�X�N���(�ȈՔ�) */
typedef struct t_rtst
{
	STAT   tskstat;			/* �^�X�N��� */
	STAT   tskwait;			/* �҂��v�� */
	VP_INT exinf;			/* �^�X�N�̊g����� */
} T_RTST;


/* �^�X�N��O�����R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_texcb_ram
{
	TEXPTN rasptn;			/* �^�X�N��O�����̃^�X�N��O�v�� */
	FP     texrtn;			/* �^�X�N��O�����̋N���Ԓn */
} T_KERNEL_TEXCB_RAM;


/* �^�X�N�R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_tcb_rom
{
	ATR    tskatr;			/* �^�X�N���� */
	VP_INT exinf;			/* �^�X�N�̊g����� */
	FP     task;			/* �^�X�N�̋N���Ԓn */
	PRI    itskpri;			/* �^�X�N�̋N�����D��x */
	SIZE   stksz;			/* �^�X�N�̃X�^�b�N�̃T�C�Y�i�o�C�g���j */
	VP	   stk;				/* �^�X�N�̃X�^�b�N�̈�̐擪�Ԓn */
} T_KERNEL_TCB_ROM;


/* �^�X�N�R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_tcb_ram
{
	T_MKNL_TCB mtcb;		/* �ʃJ�[�l�� �^�X�N�R���g���[���u���b�N */	
	UB         actcnt;		/* �N���v���L���[�C���O�� */
	UB         suscnt;		/* SUSPEND�v���l�X�g�� */
	UH         wupcnt;		/* �N���v���L���[�C���O�� */
	T_KERNEL_TEXCB_RAM     *texcb;		/* �^�X�N��O�����R���g���[���u���b�N�ւ̃|�C���^ */
	const T_KERNEL_TCB_ROM *tcb_rom;	/* �^�X�N�R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_TCB_RAM;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �^�X�N�Ǘ� */
extern       T_KERNEL_TCB_RAM* kernel_tcb_ram_tbl[];		/* �^�X�N�R���g���[���u���b�N�e�[�u��(RAM��) */
extern const INT kernel_tcb_cnt;							/* �^�X�N�R���g���[���u���b�N�� */

/* �ϊ��}�N�� */
#define KERNEL_TSKID_TO_TCB_RAM(tskid)	(kernel_tcb_ram_tbl[(tskid) - KERNEL_TMIN_TSKID])
															/* �^�X�NID����TCB RAM�A�h���X���擾 */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �^�X�N�Ǘ��@�\ */
void    kernel_ini_tsk(void);								/* �^�X�N�̏����� */
ER      cre_tsk(ID tskid, const T_CTSK *pk_ctsk);			/* �^�X�N�̐��� */
ER_ID   acre_tsk(const T_CTSK *pk_ctsk);					/* �^�X�N�̐���(ID�ԍ��������t��) */
ER      kernel_cre_tsk(ID tskid, const T_CTSK *pk_ctsk);	/* �^�X�N����(�J�[�l������) */
ER      del_tsk(ID tskid);									/* �^�X�N�̍폜 */
ER      act_tsk(ID tskid);									/* �^�X�N�̋N�� */
#define	iact_tsk	act_tsk									/* �^�X�N�̋N��(��^�X�N�R���e�L�X�g�p�}�N��) */
ER_UINT can_act(ID tskid);									/* �^�X�N�N���v���̃L�����Z�� */
ER      sta_tsk(ID tskid, VP_INT stacd);					/* �^�X�N�̋N��(�N���R�[�h�w��) */
void    ext_tsk(void);										/* ���^�X�N�̏I�� */
void    exd_tsk(void);										/* ���^�X�N�̏I���ƍ폜 */
ER      ter_tsk(ID tskid);									/* �^�X�N�̋����I�� */
ER      chg_pri(ID tskid, PRI tskpri);						/* �^�X�N�D��x�̕ύX */
ER      get_pri(ID tskid, PRI *p_tskpri);					/* �^�X�N�D��x�̎Q�� */
ER      ref_tsk(ID tskid, T_RTSK *p_rtsk);					/* �^�X�N�̏�ԎQ�� */
ER      ref_tst(ID tskid, T_RTST *p_rtst);					/* �^�X�N�̏�ԎQ��(�ȈՔ�) */

/* �^�X�N�t�������@�\ */
ER      slp_tsk(void);										/* �^�X�N�̋N���҂� */
ER      tslp_tsk(TMO tmout);								/* �^�X�N�̋N���҂�(�^�C���A�E�g����) */
ER      wup_tsk(ID tskid);									/* �^�X�N�̋N�� */
#define	iwup_tsk	wup_tsk									/* �^�X�N�̋N��(��^�X�N�R���e�L�X�g�p�}�N��) */
ER_UINT can_wup(ID tskid);									/* �^�X�N�N���v���̃L�����Z�� */
ER      rel_wai(ID tskid);									/* �҂���Ԃ̋������� */
#define	irel_wai	rel_wai									/* �҂���Ԃ̋�������(��^�X�N�R���e�L�X�g�p�}�N��) */
ER      sus_tsk(ID tskid);									/* �����҂���Ԃւ̈ڍs */
ER      rsm_tsk(ID tskid);									/* �����҂���Ԃ���̍ĊJ */
ER      frsm_tsk(ID tskid);									/* �����҂���Ԃ���̋����ĊJ */
ER      dly_tsk(RELTIM dlytim);								/* ���^�X�N�̒x�� */

/* �^�X�N��O�����@�\ */
ER      ras_tex(ID tskid, TEXPTN rasptn);					/* �^�X�N��O�����̗v�� */
#define iras_tex	ras_tex									/* �^�X�N��O�����̗v��(��^�X�N�R���e�L�X�g�p�}�N��) */
ER      dis_tex(void);										/* �^�X�N��O�����̋֎~ */
ER      ena_tex(void);										/* �^�X�N��O�����̋֎~ */
BOOL    sns_tex(void);										/* �^�X�N��O�����֎~��Ԃ̎Q�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_tsk_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
