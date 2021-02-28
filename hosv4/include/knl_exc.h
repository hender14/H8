/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ CPU��O�n���h���Ǘ�                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_exc_h__
#define __HOS_V4__knl_exc_h__


#include "knl_hos.h"

/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ���荞�ݔԍ��͈̔� */
#define KERNEL_TMIN_EXCNO	(kernel_min_excno)	/* CPU��O�n���h���ԍ��̍ŏ��l */
#define KERNEL_TMAX_EXCNO	(KERNEL_TMIN_EXCNO + kernel_exccb_cnt - 1)
												/* CPU��O�n���h���ԍ��̍ő�l */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* CPU��O�n���h���R���g���[���u���b�N */
typedef struct t_kernel_exccb
{
	FP exchdr;			/* CPU��O�n���h���̋N���Ԓn */
} T_KERNEL_EXCCB;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/*  CPU��O�n���h���Ǘ� */
extern T_KERNEL_EXCCB  kernel_exccb_tbl[];	/* CPU��O�n���h���R���g���[���u���b�N�e�[�u�� */
extern const INT       kernel_exccb_cnt;	/* CPU��O�n���h���ԍ��� */
extern const EXCNO     kernel_min_excno;	/* CPU��O�n���h���ԍ��ŏ��l */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* CPU��O�n���h���Ǘ� */
void    kernel_sta_exc(void);			/* CPU��O�n���h���̊J�n */
void    kernel_end_exc(void);			/* CPU��O�n���h���̏I�� */
void    kernel_exe_exc(EXCNO excno);	/* CPU��O�n���h���������s */

#ifdef __cplusplus
}
#endif



#endif	/*  __HOS_V4__knl_exc_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
