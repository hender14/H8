/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���[���{�b�N�X                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* ���[���{�b�N�X�̐���(ID�ԍ��������t��) */
ER_ID acre_mbx(
		const T_CMBX *pk_cmbx)	/* ���[���{�b�N�X����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ID mbxid;
	ER ercd;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ���p�\��ID�̌��� */
	for ( mbxid = KERNEL_TMAX_MBXID; mbxid >= KERNEL_TMIN_MBXID; mbxid-- )
	{
		if ( KERNEL_MBXID_TO_MBXCB_RAM(mbxid) == NULL )
		{
			break;
		}
	}
	
	/* ID�ԍ��s���`�F�b�N */
#ifdef HOS_ERCHK_E_NOID
	if ( mbxid < KERNEL_TMIN_MBXID )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOID;	/* ID�ԍ��s�� */
	}
#endif

	/* ���[���{�b�N�X�̐��� */
	ercd = kernel_cre_mbx(mbxid, pk_cmbx);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return (ER_ID)mbxid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
