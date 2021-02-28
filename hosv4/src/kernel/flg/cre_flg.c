/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �C�x���g�t���O                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* �C�x���g�t���O�̐��� */
ER cre_flg(
		ID           flgid,		/* �����Ώۂ̃C�x���g�t���O��ID�ԍ� */
		const T_CFLG *pk_cflg)	/* �C�x���g�t���O����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < KERNEL_TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* �s��ID */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �C�x���g�t���O���o�^�\���ǂ����`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_FLGID_TO_FLGCB_RAM(flgid) != NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_OBJ;	/* ���ɓo�^�ς� */
	}
#endif

	/* �C�x���g�t���O�̐��� */
	ercd = kernel_cre_flg(flgid, pk_cflg);
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
