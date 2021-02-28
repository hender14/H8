/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Z�}�t�H                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* �Z�}�t�H�̐���(ID�ԍ��������t��) */
ER_ID acre_sem(
		const T_CSEM *pk_csem)	/* �Z�}�t�H����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ID semid;
	ER ercd;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ���p�\��ID�̌��� */
	for ( semid = KERNEL_TMAX_SEMID; semid >= KERNEL_TMIN_SEMID; semid-- )
	{
		if ( KERNEL_SEMID_TO_SEMCB_RAM(semid) == NULL )
		{
			break;
		}
	}
	
	/* ID�ԍ��s���`�F�b�N */
#ifdef HOS_ERCHK_E_NOID
	if ( semid < KERNEL_TMIN_SEMID )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOID;	/* ID�ԍ��s�� */
	}
#endif

	/* �Z�}�t�H�̐��� */
	ercd = kernel_cre_sem(semid, pk_csem);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return (ER_ID)semid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
