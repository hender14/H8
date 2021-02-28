/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���b�Z�[�W�o�b�t�@                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ���b�Z�[�W�o�b�t�@�ւ̑��M */
ER snd_mbf(
		ID   mbfid,		/* ���M�Ώۂ̃��b�Z�[�W�o�b�t�@��ID�ԍ� */
		VP   msg,		/* ���M���b�Z�[�W�̐擪�Ԓn */
		UINT msgsz)		/* ���M���b�Z�[�W�̃T�C�Y(�o�C�g��) */
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	T_MKNL_TCB               *mtcb;
	T_KERNEL_MBFDAT          mbfdat;
	ER                       ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < KERNEL_TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
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

	mbfcb_ram = KERNEL_MBFID_TO_MBFCB_RAM(mbfid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	mbfcb_rom = mbfcb_ram->mbfcb_rom;

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( msg == NULL || msgsz > mbfcb_rom->maxmsz )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_PAR;	/* �p�����[�^�[�s�� */		
	}
#endif

	/* ���M */
	ercd = kernel_snd_mbf(mbfcb_rom, mbfcb_ram, msg, msgsz);
	if ( ercd == E_TMOUT )	/* �^�C���A�E�g�Ȃ� */
	{
		/* �^�X�N��҂���Ԃɂ��� */
		mtcb = mknl_get_run_tsk();
		mbfdat.msg   = msg;
		mbfdat.msgsz = msgsz;
		mtcb->data   = (VP_INT)&mbfdat;
		mknl_wai_tsk(mtcb, TTW_SMBF);
		mknl_add_que(&mbfcb_ram->sndque, mtcb, mbfcb_rom->mbfatr);	/* �҂��s��ɒǉ� */

		ercd = (ER)mknl_exe_dsp();	/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();				/* ��O�����̎��s */
	}
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
