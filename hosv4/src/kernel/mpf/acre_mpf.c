/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Œ蒷�������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* �Œ蒷�������v�[���̐���(ID�ԍ��������t��) */
ER_ID acre_mpf(
		const T_CMPF *pk_cmpf)	/* �Œ蒷�������v�[������������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ID mpfid;
	ER ercd;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ���p�\��ID�̌��� */
	for ( mpfid = KERNEL_TMAX_MPFID; mpfid >= KERNEL_TMIN_MPFID; mpfid-- )
	{
		if ( KERNEL_MPFID_TO_MPFCB_RAM(mpfid) == NULL )
		{
			break;
		}
	}
	
	/* ID�ԍ��s���`�F�b�N */
#ifdef HOS_ERCHK_E_NOID
	if ( mpfid < KERNEL_TMIN_MPFID )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOID;	/* ID�ԍ��s�� */
	}
#endif

	/* �Œ蒷�������v�[���̐��� */
	ercd = kernel_cre_mpf(mpfid, pk_cmpf);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return (ER_ID)mpfid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
