/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �ϒ��������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"
#include "knl_sys.h"



/* �ϒ��������u���b�N�̏�ԎQ�� */
ER ref_mpl(
		ID     mplid,		/* ��Ԏ擾�Ώۂ̉ϒ��������v�[����ID�ԍ� */
		T_RMPL *pk_rmpl)	/* �ϒ��������v�[����Ԃ�Ԃ��p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rmpl == NULL )
	{
		return E_PAR;
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
	
	/* �ϒ��������u���b�N�̑҂��s��̐擪�̃^�X�N��ID�ԍ��擾 */
	mtcb = mknl_ref_qhd(&mplcb_ram->que);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb == NULL )
	{
		pk_rmpl->wtskid = TSK_NONE;		/* �҂��^�X�N�Ȃ� */
	}
	else
	{
		/* �^�X�NID������ */
		pk_rmpl->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* �󂫃u���b�N�̏��(������) */
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
