/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Œ蒷�������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* �Œ蒷�������u���b�N�̊l�� */
ER get_mpf(
		ID mpfid,		/* �������u���b�N�l���Ώۂ̌Œ蒷�������v�[����ID�ԍ� */
		VP *p_blk)		/* �l�������������u���b�N�̐擪�Ԓn */
{
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;
	T_KERNEL_MPFCB_RAM       *mpfcb_ram;
	T_MKNL_TCB *mtcb;
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < KERNEL_TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �R���e�L�X�g�`�F�b�N */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_CTX;	/* �R���e�L�X�g�s�� */
	}
#endif

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
		/* �󂫃u���b�N��������Α҂��ɓ��� */
		mpfcb_rom = mpfcb_ram->mpfcb_rom;
		mtcb = mknl_get_run_tsk();
		mknl_wai_tsk(mtcb, TTW_MPF);
		mknl_add_que(&mpfcb_ram->que, mtcb, mpfcb_rom->mpfatr);	/* �҂��s��ɒǉ� */
		
		ercd = (ER)mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
		
		if ( ercd == E_OK )
		{
			*p_blk = (VP)mtcb->data;	/* �l���u���b�N�擪�Ԓn�i�[ */
		}
		
		mknl_exe_tex();		/* ��O�����̎��s */
	}
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
