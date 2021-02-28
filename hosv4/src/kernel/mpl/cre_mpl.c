/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �ϒ��������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* �ϒ��������v�[���̐��� */
ER cre_mpl(
		ID           mplid,		/* �����Ώۂ̉ϒ��������v�[����ID�ԍ� */
		const T_CMPL *pk_cmpl)	/* �ϒ��������v�[������������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* �s��ID */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �������v�[�����o�^�\���ǂ����`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_MPLID_TO_MPLCB_RAM(mplid) != NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_OBJ;	/* ���ɓo�^�ς� */
	}
#endif

	/* �ϒ��������v�[���̐��� */
	ercd = kernel_cre_mpl(mplid, pk_cmpl);
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
