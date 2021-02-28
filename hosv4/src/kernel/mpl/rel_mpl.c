/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �ϒ��������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* �ϒ��������u���b�N�̕ԋp */
ER rel_mpl(
		ID mplid,		/* �������u���b�N�l���Ώۂ̉ϒ��������v�[����ID�ԍ� */
		VP blk)			/* �ԋp���郁�����u���b�N�̐擪�Ԓn */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;
	T_MKNL_TCB         *mtcb;
	T_KERNEL_MPLINF    *mplinf;
	VP                 mem;
	BOOL               wup = FALSE;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(mplid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mplcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	/* �������v�[���ɕԋp */
	kernel_fre_hep(&mplcb_ram->hep, blk);

	/* �҂��^�X�N�̋N�� */
	for ( ; ; )
	{
		/* �҂��s��擪����^�X�N���o�� */
		mtcb = mknl_ref_qhd(&mplcb_ram->que);
		if ( mtcb == NULL )
		{
			break;
		}
		
		/* �������m�ۂɃg���C */
		mplinf = (T_KERNEL_MPLINF *)mtcb->data;
		mem = kernel_alc_hep(&mplcb_ram->hep, mplinf->blksz);
		if ( mem == NULL )
		{
			break;
		}

		/* �҂��^�X�N������Α҂����� */
		*mplinf->p_blk = mem;
		mknl_rmv_que(mtcb);					/* �������v�[���̑҂��s�񂩂�폜 */
		mknl_rmv_tmout(mtcb);				/* �^�C���A�E�g�҂��s�񂩂�폜 */
		mknl_wup_tsk(mtcb, E_OK);			/* �^�X�N�̑҂����� */
		
		wup = TRUE;
	}
	
	if ( wup )
	{
		mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();		/* ��O�����̎��s */
	}

	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
