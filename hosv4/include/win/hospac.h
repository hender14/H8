/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (Windows�p)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__win__hospac_h__
#define __HOS_V4__win__hospac_h__



/* Windows �w�b�_�t�@�C���̓ǂ݂��� */
#define SIZE  WIN_SIZE
#include <windows.h>
#undef  SIZE

/*   Windows �W���� SIZE �\���̂� ITRON �̕W���^�Əd�Ȃ�̂� */
/* ��L�̂悤�ɋ����I�� WIN_SIZE �ɖ��O��ς��Ă���          */
/* Windows API�� SIZE �𗘗p����Ƃ��͗v����                 */

#include <itron.h>



/* ------------------------------------------ */
/*                   �^��`                   */
/* ------------------------------------------ */

/* �R���e�L�X�g���ۑ��u���b�N */
typedef struct t_hos_pac_ctxinf
{
	HANDLE hThread;			/* �X���b�h�n���h�� */
	DWORD  dwThreadId;		/* �X���b�hID */
	BOOL   blIntSuspend;	/* ���荞�݂ł̃T�X�y���h�t���O */
} T_HOSPAC_CTXINF;


/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

extern HANDLE hospac_hSem;		/* �V�X�e���̔r������p�Z�}�t�H */
extern BOOL   hospac_blInt;		/* ���荞�ݏ������t���O */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

void hospac_ini_sys(void);			/* �V�X�e���̏����� */
void hospac_ena_int(void);			/* ���荞�݋��� */
void hospac_dis_int(void);			/* ���荞�݋֎~ */

void hospac_cre_ctx(T_HOSPAC_CTXINF *pk_ctxinf,
					VP_INT exinf, FP task,
					SIZE stksz, VP stk);					/* ���s�R���e�L�X�g�̍쐬 */
void hospac_del_ctx(T_HOSPAC_CTXINF *pk_ctxinf);			/* ���s�R���e�L�X�g�̍폜 */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* ���s�R���e�L�X�g�̐ؑ� */
void hospac_set_tex(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					void (*exp)(TEXPTN), TEXPTN rasptn);	/* ��O�������s�ݒ� */
void hospac_idle(void);				/* �A�C�h�����̏��� */


void hospac_win_int(INTNO intno);	/* �[�����荞�݂̃G�~�����[�g(ITRON�^�X�N�Ƃ͖��֌W�̃X���b�h����ĂԂ���) */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__win__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
