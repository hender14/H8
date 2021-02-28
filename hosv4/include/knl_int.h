/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���荞�݊Ǘ�                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_int_h__
#define __HOS_V4__knl_int_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ���荞�ݔԍ��͈̔� */
#define KERNEL_TMIN_INTNO	(kernel_min_intno)	/* ���荞�ݔԍ��̍ŏ��l */
#define KERNEL_TMAX_INTNO	(KERNEL_TMIN_INTNO + kernel_intcb_cnt - 1)
												/* ���荞�ݔԍ��̍ő�l */

/* ID�͈̔� */
#define KERNEL_TMIN_ISRID	TMIN_ISRID			/* ���荞�݃T�[�r�X���[�`��ID�̍ŏ��l */
#define KERNEL_TMAX_ISRID	(KERNEL_TMIN_ISRID + kernel_isrcb_cnt - 1)
												/* ���荞�݃T�[�r�X���[�`��ID�̍ő�l */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* ���荞�݊Ǘ��R���g���[���u���b�N */
typedef struct t_kernel_intcb
{
	VP_INT exinf;		/* ���荞�݃T�[�r�X���[�`���̊g����� */
	FP     isr;			/* ���荞�݃T�[�r�X���[�`���̋N���Ԓn */
} T_KERNEL_INTCB;


/* ���荞�݃n���h���̒�`�p */
typedef struct t_dinh
{
	ATR inhatr;			/* ���荞�݃n���h������ */
	FP  inthdr;			/* ���荞�݃n���h���̋N���Ԓn */
} T_DINH;


/* ���荞�݃T�[�r�X���[�`���R���g���[���u���b�N */
typedef struct t_kernel_isrcb
{
	INTNO  intno;		/* ���荞�ݔԍ� */
} T_KERNEL_ISRCB;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* ���荞�݊Ǘ� */
extern T_KERNEL_INTCB  kernel_intcb_tbl[];	/* ���荞�݊Ǘ��R���g���[���u���b�N�e�[�u�� */
extern const INT       kernel_intcb_cnt;	/* ���荞�ݔԍ��� */
extern const INTNO     kernel_min_intno;	/* ���荞�ݔԍ��ŏ��l */

/* ���荞�݃T�[�r�X���[�`�� */
extern T_KERNEL_ISRCB* kernel_isrcb_tbl[];	/* ���荞�݃T�[�r�X���[�`���R���g���[���u���b�N�e�[�u�� */
extern const INT       kernel_isrcb_cnt;	/* ���荞�݃T�[�r�X���[�`���R���g���[���u���b�N�̌� */

/* ���荞�ݐ���ϐ� */
extern INT kernel_int_cnt;		/* ���荞�݃l�X�g�� */
extern VP  kernel_int_ssp;		/* ���荞�ݎ��X�^�b�N�ޔ� */

#define KERNEL_INTNO_TO_INTCB(intno)	(kernel_intcb_tbl[(intno) - KERNEL_TMIN_INTNO])


/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ���荞�ݐ��� */
void    kernel_sta_int(void);						/* ���荞�݃R���e�L�X�g�J�n���� */
void    kernel_end_int(void);						/* ���荞�݃R���e�L�X�g�I������ */

/* ���荞�݊Ǘ� */
void    kernel_exe_int(INTNO intno);				/* ���荞�ݏ������s */
ER      dis_int(INTNO intno);						/* ���荞�݂̋֎~ */
ER      ena_int(INTNO intno);						/* ���荞�݂̋��� */


/* ���荞�݃n���h�� */
ER      def_inh(INTNO intno, T_DINH *pk_dinh);		/* ���荞�݃n���h����` */


/* ���荞�݃T�[�r�X���[�`�� */
/*
ER      cre_isr();
ER      acre_isr();
*/

#ifdef __cplusplus
}
#endif



#endif	/*  __HOS_V4__knl_int_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
