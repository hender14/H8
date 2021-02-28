/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���b�Z�[�W�o�b�t�@                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "knl_sys.h"


/* ���b�Z�[�W�o�b�t�@�̏�ԎQ�� */
ER ref_mbf(
		ID     mbfid,		/* ��Ԏ擾�Ώۂ̃��b�Z�[�W�o�b�t�@��ID�ԍ� */
		T_RMBF *pk_rmbf)	/* ���b�Z�[�W�o�b�t�@��Ԃ�Ԃ��p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_MBFCB_RAM *mbfcb_ram;
	T_MKNL_TCB         *mtcb;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < KERNEL_TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rmbf == NULL )
	{
		return E_PAR;
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

	/* ���b�Z�[�W�o�b�t�@�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ��擾 */
	mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb == NULL )
	{
		pk_rmbf->stskid = TSK_NONE;		/* �҂��^�X�N�Ȃ� */
	}
	else
	{
		/* �^�X�NID������ */
		pk_rmbf->stskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}
	
	/* ���b�Z�[�W�o�b�t�@�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ��擾 */
	mtcb = mknl_ref_qhd(&mbfcb_ram->rcvque);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb == NULL )
	{
		pk_rmbf->rtskid = TSK_NONE;		/* �҂��^�X�N�Ȃ� */
	}
	else
	{
		/* �^�X�NID������ */
		pk_rmbf->rtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}
	
	/* ���b�Z�[�W�o�b�t�@�ɓ����Ă��郁�b�Z�[�W���̎擾*/
	pk_rmbf->smsgcnt = mbfcb_ram->smsgcnt;
	
	/* ���b�Z�[�W�o�b�t�@�̈�̋󂫗̈�̃T�C�Y�̎擾 */
	pk_rmbf->fmbfsz = mbfcb_ram->fmbfsz;
	if ( pk_rmbf->fmbfsz > sizeof(UINT) )
	{
		pk_rmbf->fmbfsz -= sizeof(UINT);
	}
	else
	{
		pk_rmbf->fmbfsz = 0;
	}

	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
