/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �f�[�^�L���[                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"
#include "knl_mem.h"



/* �f�[�^�L���[�̍폜 */
ER del_dtq(
		ID dtqid)	/* �폜�Ώۂ̃f�[�^�L���[��ID�ԍ� */
{
	T_KERNEL_DTQCB_RAM *dtqcb_ram;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;	/* �s��ID */
	}
#endif

	mknl_loc_sys();		/* �V�X�e���̃��b�N */

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif
	
	/* �^�X�N�̉��� */
	mknl_clr_que(&dtqcb_ram->sndque);	/* ���M�҂��^�X�N�̉��� */
	mknl_clr_que(&dtqcb_ram->rcvque);	/* ��M�҂��^�X�N�̉��� */
	
	/* �������̉�� */
	kernel_fre_mem(dtqcb_ram);
	KERNEL_DTQID_TO_DTQCB_RAM(dtqid) = NULL;
	
	mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();		/* ��O�����̎��s */
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
