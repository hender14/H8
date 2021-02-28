/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Œ蒷�������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"
#include "knl_mem.h"



/* �Œ蒷�������v�[���̍폜 */
ER del_mpf(
		ID mpfid)	/* �폜�Ώۂ̌Œ蒷�������v�[����ID�ԍ� */
{
	T_KERNEL_MPFCB_RAM *mpfcb_ram;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < KERNEL_TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
	{
		return E_ID;	/* �s��ID */
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
	
	/* �҂��^�X�N�̉��� */
	mknl_clr_que(&mpfcb_ram->que);
	
	/* �������̉�� */
	kernel_fre_mem(mpfcb_ram);
	KERNEL_MPFID_TO_MPFCB_RAM(mpfid) = NULL;
	
	mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();		/* ��O�����̎��s */
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
