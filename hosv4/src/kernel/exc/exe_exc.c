/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� CPU��O�n���h���Ǘ�                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_exc.h"



/* CPU��O�n���h���̊J�n */
void kernel_sta_exc(void)
{
	/* ��^�X�N��(���荞�݃R���e�L�X�g�Ɉڍs) */
	mknl_sta_ind();
}


/* CPU��O�n���h���̏I�� */
void kernel_end_exc(void)
{
	/* �^�X�N���Ɉڍs */
	mknl_ext_ind();

	/* �x���f�B�X�p�b�`���s */
	mknl_dly_dsp();
}


/* CPU��O�n���h���ݏ������s */
void kernel_exe_exc(
		EXCNO excno)		/* CPU��O�n���h���ԍ� */
{
	T_KERNEL_EXCCB exccb;
	
	if ( excno < KERNEL_TMIN_EXCNO || excno > KERNEL_TMAX_EXCNO )
	{
		return;
	}
	
	exccb = kernel_exccb_tbl[excno];	/* ���[�J���ɃR�s�[ */
	
	mknl_unl_sys();		/* ���d���荞�݋��� */
	
	if ( exccb.exchdr != NULL )
	{
		exccb.exchdr();			/* CPU��O�n���h�����s */
	}
	
	mknl_loc_sys();		/* ���d���荞�݋֎~ */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
