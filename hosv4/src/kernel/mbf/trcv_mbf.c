/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���b�Z�[�W�o�b�t�@                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ���b�Z�[�W�o�b�t�@����̎�M(�^�C���A�E�g����) */
ER_UINT trcv_mbf(
		ID   mbfid,		/* ��M�Ώۂ̃��b�Z�[�W�o�b�t�@��ID�ԍ� */
		VP   msg,		/* ��M���b�Z�[�W���i�[����擪�Ԓn */
		TMO  tmout)		/* �^�C���A�E�g�w�� */
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	T_MKNL_TCB               *mtcb;
	ER_UINT                  ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < KERNEL_TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR 
	if ( (tmout != TMO_FEVR && tmout < 0) || msg == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �R���e�L�X�g�`�F�b�N */
#ifdef HOS_ERCHK_E_CTX
	if ( tmout != TMO_POL && mknl_sns_wai() )
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

	/* �o�b�t�@��M */
	ercd = kernel_rcv_mbf(mbfcb_rom, mbfcb_ram, msg);
	if ( ercd == E_TMOUT )	/* �^�C���A�E�g�Ȃ� */
	{
		if ( tmout != TMO_POL )		/* �|�[�����O�w��łȂ���� */
		{
			/* �^�X�N��҂���Ԃɂ��� */
			mtcb = mknl_get_run_tsk();
			mtcb->data = (VP_INT)msg;
			mknl_wai_tsk(mtcb, TTW_RMBF);
			mknl_add_que(&mbfcb_ram->rcvque, mtcb, mbfcb_rom->mbfatr);	/* �҂��s��ɒǉ� */
			
			/* �����҂��łȂ���΃^�C���A�E�g�ݒ� */
			if ( tmout != TMO_FEVR )
			{
				mknl_add_tmout(mtcb, (RELTIM)tmout);	/* �^�C���A�E�g�L���[�ɒǉ� */
			}
			
			ercd = mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
			mknl_exe_tex();				/* ��O�����̎��s */
		}
	}
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
