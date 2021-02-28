/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �ϒ��������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"
#include "knl_mem.h"



/* �ϒ��������v�[���̍폜 */
ER del_mpl(
		ID mplid)	/* �폜�Ώۂ̉ϒ��������v�[����ID�ԍ� */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* �s��ID */
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
	
	/* �҂��^�X�N�̉��� */
	mknl_clr_que(&mplcb_ram->que);
	
	/* �������̉�� */
	kernel_fre_mem(mplcb_ram);
	KERNEL_MPLID_TO_MPLCB_RAM(mplid) = NULL;
	
	mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();		/* ��O�����̎��s */
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
