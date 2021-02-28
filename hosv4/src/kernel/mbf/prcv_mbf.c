/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���b�Z�[�W�o�b�t�@                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ���b�Z�[�W�o�b�t�@����̎�M(�|�[�����O) */
ER_UINT prcv_mbf(
		ID   mbfid,		/* ��M�Ώۂ̃��b�Z�[�W�o�b�t�@��ID�ԍ� */
		VP   msg)		/* ��M���b�Z�[�W���i�[����擪�Ԓn */
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	ER_UINT                  ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < KERNEL_TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( msg == NULL )
	{
		return E_PAR;	/* �p�����[�^�[�s�� */		
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	mbfcb_ram = KERNEL_MBFID_TO_MBFCB_RAM(mbfid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	mbfcb_rom = mbfcb_ram->mbfcb_rom;

	/* �o�b�t�@��M */
	ercd = kernel_rcv_mbf(mbfcb_rom, mbfcb_ram, msg);
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
