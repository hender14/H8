/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �C�x���g�t���O                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"
#include "knl_mem.h"



/* �C�x���g�t���O�̍폜 */
ER del_flg(
		ID flgid)	/* �폜�Ώۂ̃C�x���g�t���O��ID�ԍ� */
{
	T_KERNEL_FLGCB_RAM *flgcb_ram;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < KERNEL_TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* �s��ID */
	}
#endif

	mknl_loc_sys();		/* �V�X�e���̃��b�N */

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif
	
	/* �҂��^�X�N�̉��� */
	mknl_clr_que(&flgcb_ram->que);
	
	/* �������̉�� */
	kernel_fre_mem(flgcb_ram);
	KERNEL_FLGID_TO_FLGCB_RAM(flgid) = NULL;
	
	mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();		/* ��O�����̎��s */
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
