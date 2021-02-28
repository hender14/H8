/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �ϒ��������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* �ϒ��������u���b�N�̊l��(�|�[�����O) */
ER pget_mpl(
		ID mplid,		/* �������u���b�N�l���Ώۂ̉ϒ��������v�[����ID�ԍ� */
		UINT blksz,		/* �l�����郁�����u���b�N�̃T�C�Y(�o�C�g��) */
		VP *p_blk)		/* �l�������������u���b�N�̐擪�Ԓn */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;
	VP mem;
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(mplid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mplcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	/* �������m�ۂɃg���C */
	mem = kernel_alc_hep(&mplcb_ram->hep, blksz);

	if ( mem != NULL )
	{
		/* ���蓖�Đ��� */
		*p_blk          = mem;
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
