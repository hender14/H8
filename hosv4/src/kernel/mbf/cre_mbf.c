/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���b�Z�[�W�o�b�t�@                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ���b�Z�[�W�o�b�t�@�̐��� */
ER cre_mbf(
		ID           mbfid,		/* �����Ώۂ̃��b�Z�[�W�o�b�t�@��ID�ԍ� */
		const T_CMBF *pk_cmbf)	/* ���b�Z�[�W�o�b�t�@����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < KERNEL_TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* �s��ID */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ���b�Z�[�W�o�b�t�@���o�^�\���ǂ����`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_MBFID_TO_MBFCB_RAM(mbfid) != NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_OBJ;	/* ���ɓo�^�ς� */
	}
#endif

	/* ���b�Z�[�W�o�b�t�@�̐��� */
	ercd = kernel_cre_mbf(mbfid, pk_cmbf);
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
