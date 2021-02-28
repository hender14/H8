/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Z�}�t�H                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"
#include "knl_sys.h"



/* �Z�}�t�H�̏�ԎQ�� */
ER ref_sem(
		ID     semid,		/* ��ԎQ�ƑΏۂ̃Z�}�t�H��ID�ԍ� */
		T_RSEM *pk_rsem)	/* �Z�}�t�H��Ԃ�Ԃ��p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( semid < KERNEL_TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;
	}
#endif

	/* �p�����[�^�̃`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_rsem == NULL )
	{
		return E_PAR;	/* �p�����[�^�G���[ */
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

	/* �Z�}�t�H�̑҂��s��̐擪�̃^�X�N��ID�ԍ��擾 */
	mtcb = mknl_ref_qhd(&semcb_ram->que);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb == NULL )
	{
		pk_rsem->wtskid = TSK_NONE;		/* �҂��^�X�N�Ȃ� */
	}
	else
	{
		/* �^�X�NID������ */
		pk_rsem->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}
	
	/* �Z�}�t�H�̌��݂̎������擾 */
	pk_rsem->semcnt = semcb_ram->semcnt;

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;	/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
