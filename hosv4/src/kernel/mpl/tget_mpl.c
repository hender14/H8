/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �ϒ��������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* �ϒ��������u���b�N�̊l��(�^�C���A�E�g����) */
ER tget_mpl(
		ID   mplid,		/* �������u���b�N�l���Ώۂ̉ϒ��������v�[����ID�ԍ� */
		UINT blksz,		/* �l�����郁�����u���b�N�̃T�C�Y(�o�C�g��) */
		VP   *p_blk,	/* �l�������������u���b�N�̐擪�Ԓn */
		TMO  tmout)		/* �^�C���A�E�g�w�� */
{
	const T_KERNEL_MPLCB_ROM *mplcb_rom;
	T_KERNEL_MPLCB_RAM       *mplcb_ram;
	T_MKNL_TCB               *mtcb;
	T_KERNEL_MPLINF          mplinf;
	VP mem;
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
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

	mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(mplid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mplcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	/* �������m�ۂɃg���C */
	mem = kernel_alc_hep(&mplcb_ram->hep, blksz);

	if ( mem != NULL )
	{
		/* ���蓖�Đ��� */
		*p_blk          = mem;
		ercd = E_OK;
	}
	else
	{
		/* �󂫂�������Α҂��ɓ��� */
		mplcb_rom = mplcb_ram->mplcb_rom;
		mtcb = mknl_get_run_tsk();

		mplinf.blksz = blksz;
		mplinf.p_blk = p_blk;
		mtcb->data = (VP_INT)&mplinf;

		mknl_wai_tsk(mtcb, TTW_MPL);
		mknl_add_que(&mplcb_ram->que, mtcb, mplcb_rom->mplatr);	/* �҂��s��ɒǉ� */

		/* �����҂��łȂ���΃^�C���A�E�g�ݒ� */
		if ( tmout != TMO_FEVR )
		{
			mknl_add_tmout(mtcb, (RELTIM)tmout);	/* �^�C���A�E�g�L���[�ɒǉ� */
		}

		ercd = (ER)mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
		
		mknl_exe_tex();		/* ��O�����̎��s */
	}
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
