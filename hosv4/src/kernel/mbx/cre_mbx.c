/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���[���{�b�N�X                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* ���[���{�b�N�X�̐��� */
ER cre_mbx(
		ID           mbxid,		/* �����Ώۂ̃��[���{�b�N�X��ID�ԍ� */
		const T_CMBX *pk_cmbx)	/* ���[���{�b�N�X����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < KERNEL_TMIN_MBXID || mbxid > KERNEL_TMAX_MBXID )
	{
		return E_ID;	/* �s��ID */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ���[���{�b�N�X���o�^�\���ǂ����`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_MBXID_TO_MBXCB_RAM(mbxid) != NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_OBJ;	/* ���ɓo�^�ς� */
	}
#endif

	/* ���[���{�b�N�X�̐��� */
	ercd = kernel_cre_mbx(mbxid, pk_cmbx);
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
