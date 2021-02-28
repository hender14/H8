/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Z�}�t�H                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* �Z�}�t�H�����̕ԋp */
ER sig_sem(
		ID semid)		/* �Z�}�t�H�����ԋp�Ώۂ̃Z�}�t�H��ID�ԍ� */
{
	const T_KERNEL_SEMCB_ROM *semcb_rom;
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_MKNL_TCB *mtcb;
	
	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( semid < KERNEL_TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* �V�X�e���̃��b�N */
	
	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);
	
	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif
	
	semcb_rom = semcb_ram->semcb_rom;
	
	/* �L���[�C���O�I�[�o�[�t���[�`�F�b�N */
#ifdef HOS_ERCHK_E_QOVR
	if ( semcb_ram->semcnt >= semcb_rom->maxsem )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_QOVR;
	}
#endif
	
	mtcb = mknl_ref_qhd(&semcb_ram->que);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb != NULL )
	{
		/* �҂��^�X�N������Α҂����� */
		mknl_rmv_que(mtcb);						/* �Z�}�t�H�̑҂��s�񂩂�폜 */
		mknl_rmv_tmout(mtcb);					/* �^�C���A�E�g�҂��s�񂩂�폜 */
		mknl_wup_tsk(mtcb, E_OK);				/* �^�X�N�̑҂����� */
		
		mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();		/* ��O�����̎��s */
	}
	else
	{
		semcb_ram->semcnt++;	/* �Z�}�t�H�����ԋp */
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;	/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
