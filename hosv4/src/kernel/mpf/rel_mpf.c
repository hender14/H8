/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Œ蒷�������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* �Œ蒷�������u���b�N�̕ԋp */
ER rel_mpf(
		ID mpfid,		/* �������u���b�N�l���Ώۂ̌Œ蒷�������v�[����ID�ԍ� */
		VP blk)			/* �ԋp���郁�����u���b�N�̐擪�Ԓn */
{
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < KERNEL_TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	mpfcb_ram = KERNEL_MPFID_TO_MPFCB_RAM(mpfid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mpfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	mtcb = mknl_ref_qhd(&mpfcb_ram->que);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb != NULL )
	{
		/* �҂��^�X�N������Α҂����� */
		mknl_rmv_que(mtcb);						/* �������v�[���̑҂��s�񂩂�폜 */
		mknl_rmv_tmout(mtcb);					/* �^�C���A�E�g�҂��s�񂩂�폜 */
		mtcb->data = (VP_INT)blk;				/* �u���b�N�̐擪�Ԓn��ݒ� */
		mknl_wup_tsk(mtcb, E_OK);				/* �^�X�N�̑҂����� */
		
		mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();		/* ��O�����̎��s */
	}
	else
	{
		/* �҂��^�X�N��������΃������v�[���ɕԋp */
		*(VP *)blk      = mpfcb_ram->free;
		mpfcb_ram->free = blk;
	}

	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
