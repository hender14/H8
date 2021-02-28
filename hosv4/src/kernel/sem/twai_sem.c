/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Z�}�t�H                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* �Z�}�t�H�����̊l��(�^�C���A�E�g����) */
ER twai_sem(
		ID  semid,	/* �����l���Ώۂ̃Z�}�t�HID�ԍ� */
		TMO tmout)	/* �^�C���A�E�g�w�� */
{
	const T_KERNEL_SEMCB_ROM *semcb_rom;
	T_KERNEL_SEMCB_RAM       *semcb_ram;
	T_MKNL_TCB *mtcb;
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( semid < KERNEL_TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;
	}
#endif

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR 
	if ( tmout != TMO_FEVR && tmout < 0 )
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

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	if ( semcb_ram->semcnt > 0 )
	{
		/* �Z�}�t�H�������l���ł���ΐ��� */
		semcb_ram->semcnt--;	/* �Z�}�t�H�����̊l�� */
		ercd = E_OK;
	}
	else
	{
		/* �l���ł��Ȃ������Ȃ� */
		if ( tmout == TMO_POL )
		{
			/* �|�[�����O�Ȃ瑦���^�C���A�E�g */
			ercd = E_TMOUT;
		}
		else
		{
			/* �^�C���A�E�g�t���ő҂��ɓ��� */
			semcb_rom = semcb_ram->semcb_rom;
			mtcb = mknl_get_run_tsk();
			mknl_wai_tsk(mtcb, TTW_SEM);
			mknl_add_que(&semcb_ram->que, mtcb, semcb_rom->sematr);	/* �҂��s��ɒǉ� */

			/* �����҂��łȂ���΃^�C���A�E�g�ݒ� */
			if ( tmout != TMO_FEVR )
			{
				mknl_add_tmout(mtcb, (RELTIM)tmout);	/* �^�C���A�E�g�L���[�ɒǉ� */
			}
			
			ercd = (ER)mknl_exe_dsp();	/* �^�X�N�f�B�X�p�b�`�̎��s */
			mknl_exe_tex();				/* ��O�����̎��s */
		}
	}

	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
