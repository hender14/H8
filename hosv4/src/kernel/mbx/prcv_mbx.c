/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���[���{�b�N�X                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* ���[���{�b�N�X����̎�M(�|�[�����O) */
ER prcv_mbx(
		ID    mbxid,		/* ��M�Ώۂ̃��[���{�b�N�X��ID�ԍ� */
		T_MSG **pk_msg)		/* ���[���{�b�N�X�����M�������b�Z�[�W�p�P�b�g�̐擪�Ԓn */
{
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_KERNEL_MBXCB_RAM       *mbxcb_ram;
	T_MSG *msg;
	PRI   msgpri;
	ER    ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < KERNEL_TMIN_MBXID || mbxid > KERNEL_TMAX_MBXID )
	{
		return E_ID;
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
		msg = mbxcb_rom->mprihd[msgpri];
		if ( msg == msg->next )		/* �Ō�̂P�Ȃ� */
		{
			*pk_msg                   = msg;
			mbxcb_rom->mprihd[msgpri] = NULL;
		}
		else
		{
			*pk_msg   = msg->next;
			msg->next = msg->next->next;
		}
		ercd = E_OK;	/* ���� */
	}
	else
	{
		/* ���[���{�b�N�X����Ȃ�^�C���A�E�g */
		ercd = E_TMOUT;
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
