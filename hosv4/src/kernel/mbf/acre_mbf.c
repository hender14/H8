/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���b�Z�[�W�o�b�t�@                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ���b�Z�[�W�o�b�t�@�̐���(ID�ԍ��������t��) */
ER_ID acre_mbf(
		const T_CMBF *pk_cmbf)	/* ���b�Z�[�W�o�b�t�@����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ID mbfid;
	ER ercd;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ���p�\��ID�̌��� */
	for ( mbfid = KERNEL_TMAX_MBFID; mbfid >= KERNEL_TMIN_MBFID; mbfid-- )
	{
		if ( KERNEL_MBFID_TO_MBFCB_RAM(mbfid) == NULL )
		{
			break;
		}
	}
	
	/* ID�ԍ��s���`�F�b�N */
#ifdef HOS_ERCHK_E_NOID
	if ( mbfid < KERNEL_TMIN_MBFID )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOID;	/* ID�ԍ��s�� */
	}
#endif

	/* ���b�Z�[�W�o�b�t�@�̐��� */
	ercd = kernel_cre_mbf(mbfid, pk_cmbf);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return (ER_ID)mbfid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
