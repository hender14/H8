/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �C�x���g�t���O                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* �C�x���g�t���O�̃N���A */
ER clr_flg(
		ID     flgid,	/* �N���A�Ώۂ̃C�x���g�t���O��ID�ԍ� */
		FLGPTN clrptn)	/* �N���A����r�b�g�p�^�[��(�r�b�g���̔��]�l) */
{
	T_KERNEL_FLGCB_RAM *flgcb_ram;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < KERNEL_TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* �s��ID�ԍ� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_NOEXS;
	}
#endif

	/* �t���O�̃N���A */
	flgcb_ram->flgptn = (FLGPTN)(flgcb_ram->flgptn & clrptn);

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
