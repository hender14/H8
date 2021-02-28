/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �ϒ��������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* �ϒ��������v�[���̐���(ID�ԍ��������t��) */
ER_ID acre_mpl(
		const T_CMPL *pk_cmpl)	/* �ϒ��������v�[������������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ID mplid;
	ER ercd;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ���p�\��ID�̌��� */
	for ( mplid = KERNEL_TMAX_MPLID; mplid >= KERNEL_TMIN_MPLID; mplid-- )
	{
		if ( KERNEL_MPLID_TO_MPLCB_RAM(mplid) == NULL )
		{
			break;
		}
	}
	
	/* ID�ԍ��s���`�F�b�N */
#ifdef HOS_ERCHK_E_NOID
	if ( mplid < KERNEL_TMIN_MPLID )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOID;	/* ID�ԍ��s�� */
	}
#endif

	/* �ϒ��������v�[���̐��� */
	ercd = kernel_cre_mpl(mplid, pk_cmpl);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return (ER_ID)mplid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
