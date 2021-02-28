/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���荞�ݐ���                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_int.h"



/* ���荞�݃R���e�L�X�g�̊J�n */
void kernel_sta_int(void)
{
	/* ��^�X�N��(���荞�݃R���e�L�X�g�Ɉڍs) */
	mknl_sta_ind();
}


/* ���荞�݃R���e�L�X�g�̏I�� */
void kernel_end_int(void)
{
	/* �^�X�N���Ɉڍs */
	mknl_ext_ind();

	/* �x���f�B�X�p�b�`���s */
	mknl_dly_dsp();
}


/* ���荞�ݏ������s */
void kernel_exe_int(
		INTNO intno)		/* ���荞�ݔԍ� */
{
	T_KERNEL_INTCB intcb;
	
	if ( intno < KERNEL_TMIN_INTNO || intno > KERNEL_TMAX_INTNO )
	{
		return;
	}

	
	intcb = KERNEL_INTNO_TO_INTCB(intno);	/* ���[�J���ɃR�s�[ */
	
	mknl_unl_sys();		/* ���d���荞�݋��� */
	
	if ( intcb.isr != NULL )
	{
		intcb.isr(intcb.exinf);			/* ���荞�݃T�[�r�X���[�`�����s */
	}
	
	mknl_loc_sys();		/* ���d���荞�݋֎~ */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
