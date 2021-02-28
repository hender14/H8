/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Œ蒷�������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* �Œ蒷�������u���b�N�̊l��(�|�[�����O) */
ER pget_mpf(
		ID mpfid,		/* �������u���b�N�l���Ώۂ̌Œ蒷�������v�[����ID�ԍ� */
		VP *p_blk)		/* �l�������������u���b�N�̐擪�Ԓn */
{
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < KERNEL_TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	mpfcb_ram = KERNEL_MPFID_TO_MPFCB_RAM(mpfid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mpfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	if ( mpfcb_ram->free != NULL )
	{
		/* �󂫃u���b�N������Ί��蓖�Ă� */
		*p_blk          = mpfcb_ram->free;
		mpfcb_ram->free = *(VP *)mpfcb_ram->free;	/* ���̋󂫃G���A��ݒ� */
		ercd = E_OK;
	}
	else
	{
		/* �󂫃u���b�N��������΃^�C���A�E�g */
		ercd = E_TMOUT;
	}

	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
