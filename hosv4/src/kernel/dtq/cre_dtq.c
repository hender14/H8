/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �f�[�^�L���[                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* �f�[�^�L���[�̐��� */
ER cre_dtq(
		ID           dtqid,		/* �����Ώۂ̃f�[�^�L���[��ID�ԍ� */
		const T_CDTQ *pk_cdtq)	/* �f�[�^�L���[����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;	/* �s��ID */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �f�[�^�L���[���o�^�\���ǂ����`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_DTQID_TO_DTQCB_RAM(dtqid) != NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_OBJ;	/* ���ɓo�^�ς� */
	}
#endif

	/* �f�[�^�L���[�̐��� */
	ercd = kernel_cre_dtq(dtqid, pk_cdtq);
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
