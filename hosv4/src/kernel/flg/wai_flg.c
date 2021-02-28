/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �C�x���g�t���O                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* �C�x���g�t���O�҂� */
ER wai_flg(
		ID     flgid,		/* �҂��Ώۂ̃C�x���g�t���O��ID�ԍ� */
		FLGPTN waiptn,		/* �҂��r�b�g�p�^�[�� */
		MODE   wfmode,		/* �҂����[�h */
		FLGPTN *p_flgptn)	/* �҂��������̃r�b�g�p�^�[���i�[�A�h���X */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
	T_MKNL_TCB      *mtcb;
	T_KERNEL_FLGINF flginf;
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < KERNEL_TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* �s��ID�ԍ� */
	}
#endif

	/* �p�����[�^�̃`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( (wfmode != TWF_ANDW && wfmode != TWF_ORW) || waiptn == 0 )
	{
		return E_PAR;	/* �p�����[�^�G���[ */
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

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);

	/* �I�u�W�F�N�g�̑��݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	flgcb_rom = flgcb_ram->flgcb_rom;

	/* �T�[�r�X�R�[���s���g�p�`�F�b�N */
#ifdef HOS_ERCHK_E_ILUSE
	if ( !(flgcb_rom->flgatr & TA_WMUL) && mknl_ref_qhd(&flgcb_ram->que) != NULL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_ILUSE;		/* �T�[�r�X�R�[���s���g�p */
	}
#endif

	/* �҂������ݒ� */
	flginf.waiptn = waiptn;
	flginf.wfmode = wfmode;
	
	/* �t���O�`�F�b�N */
	if ( kernel_chk_flg(flgcb_ram, &flginf) )
	{
		/* ���ɏ����𖞂����Ă���Ȃ� */
		*p_flgptn = flgcb_ram->flgptn;		/* �������̃t���O�p�^�[�����i�[ */
		if ( flgcb_rom->flgatr & TA_CLR )
		{
			flgcb_ram->flgptn = 0;		/* �N���A����������΃N���A */
		}
		ercd = E_OK;
	}
	else
	{
		/* �����𖞂����Ă��Ȃ���Α҂��ɓ��� */
		mtcb       = mknl_get_run_tsk();		/* ���s���^�X�N���擾 */
		mtcb->data = (VP_INT)&flginf;			/* �҂���Ԃ�ۑ� */
		mknl_wai_tsk(mtcb, TTW_FLG);
		mknl_add_que(&flgcb_ram->que, mtcb, flgcb_rom->flgatr);	/* �҂��s��ɒǉ� */
		
		ercd = (ER)mknl_exe_dsp();	/* �^�X�N�f�B�X�p�b�`���s */
		
		/* �����𖞂����ĉ������ꂽ�̂Ȃ� */
		if ( ercd == E_OK )
		{
			*p_flgptn = flginf.waiptn;			/* �������̃t���O�p�^�[�����i�[ */
		}
		
		mknl_exe_tex();		/* ��O�����̎��s */
	}
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
