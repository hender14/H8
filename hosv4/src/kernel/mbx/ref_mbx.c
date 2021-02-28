/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���[���{�b�N�X                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"
#include "knl_sys.h"



/* ���[���{�b�N�X�̏�ԎQ�� */
ER ref_mbx(
		ID     mbxid,		/* ��ԎQ�ƑΏۂ̃��[���{�b�N�X��ID�ԍ� */
		T_RMBX *pk_rmbx)	/* ���[���{�b�N�X��Ԃ�Ԃ��p�P�b�g�ւ̃|�C���^ */
{
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_KERNEL_MBXCB_RAM       *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	PRI        msgpri;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < KERNEL_TMIN_MBXID || mbxid > KERNEL_TMAX_MBXID )
	{
		return E_ID;
	}
#endif

	/* �p�����[�^�̃`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_rmbx == NULL )
	{
		return E_PAR;	/* �p�����[�^�G���[ */
	}
#endif
	
	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	mbxcb_ram = KERNEL_MBXID_TO_MBXCB_RAM(mbxid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbxcb_ram == NULL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_NOEXS;
	}
#endif

	mbxcb_rom = mbxcb_ram->mbxcb_rom;

	/* ���[���{�b�N�X�̑҂��s��̐擪�̃^�X�N��ID�ԍ��擾 */
	mtcb = mknl_ref_qhd(&mbxcb_ram->que);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb == NULL )
	{
		pk_rmbx->wtskid = TSK_NONE;		/* �҂��^�X�N�Ȃ� */
	}
	else
	{
		/* �^�X�NID������ */
		pk_rmbx->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* ���b�Z�[�W��D��x���Ɍ��� */
	for ( msgpri = 0; msgpri <= mbxcb_rom->maxmpri - TMIN_MPRI; msgpri++ )
	{
		if ( mbxcb_rom->mprihd[msgpri] != NULL )
		{
			break;
		}
	}

	if ( msgpri <= mbxcb_rom->maxmpri - TMIN_MPRI )
	{
		/* ���[���{�b�N�X�Ƀf�[�^������Ύ��o�� */
		pk_rmbx->pk_msg = mbxcb_rom->mprihd[msgpri];
	}
	else
	{
		/* ���[���{�b�N�X����Ȃ� */
		pk_rmbx->pk_msg = NULL;
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;	/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
