/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Œ蒷�������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"
#include "knl_sys.h"



/* �Œ蒷�������u���b�N�̏�ԎQ�� */
ER ref_mpf(
		ID     mpfid,		/* ��Ԏ擾�Ώۂ̌Œ蒷�������v�[����ID�ԍ� */
		T_RMPF *pk_rmpf)	/* �Œ蒷�������v�[����Ԃ�Ԃ��p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_MKNL_TCB *mtcb;
	VP   blk;
	UINT blkcnt;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < KERNEL_TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rmpf == NULL )
	{
		return E_PAR;
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
	
	/* �Œ蒷�������u���b�N�̑҂��s��̐擪�̃^�X�N��ID�ԍ��擾 */
	mtcb = mknl_ref_qhd(&mpfcb_ram->que);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb == NULL )
	{
		pk_rmpf->wtskid = TSK_NONE;		/* �҂��^�X�N�Ȃ� */
	}
	else
	{
		/* �^�X�NID������ */
		pk_rmpf->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* �󂫃u���b�N�̃J�E���g */
	blkcnt = 0;
	blk    = mpfcb_ram->free;
	while ( blk != NULL )
	{
		blk = *(VP *)blk;
		blkcnt++;
	}

	pk_rmpf->fblkcnt = blkcnt;
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
