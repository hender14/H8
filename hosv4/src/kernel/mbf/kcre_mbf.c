/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���b�Z�[�W�o�b�t�@                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "knl_mem.h"


/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(���I�����p) */
typedef struct t_kernel_mbfcb
{
	T_KERNEL_MBFCB_RAM mbfcb_ram;	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(RAM��) */
	T_KERNEL_MBFCB_ROM mbfcb_rom;	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(ROM��) */
} T_KERNEL_MBFCB;



/* ���b�Z�[�W�o�b�t�@�̐���(�J�[�l�������֐�) */
ER kernel_cre_mbf(
		ID           mbfid,		/* �����Ώۂ̃��b�Z�[�W�o�b�t�@��ID�ԍ� */
		const T_CMBF *pk_cmbf)	/* ���b�Z�[�W�o�b�t�@����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_MBFCB     *mbfcb;
	T_KERNEL_MBFCB_RAM *mbfcb_ram;
	T_KERNEL_MBFCB_ROM *mbfcb_rom;

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmbf->mbfatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* ���b�Z�[�W�o�b�t�@�p�������̊m�� */
	mbfcb = (T_KERNEL_MBFCB *)kernel_alc_mem(sizeof(T_KERNEL_MBFCB));
	if ( mbfcb == NULL )
	{
		return E_NOMEM;		/* �������s�� */
	}

	/* ���b�Z�[�W�o�b�t�@�̐ݒ� */
	mbfcb_ram = &mbfcb->mbfcb_ram;
	mbfcb_rom = &mbfcb->mbfcb_rom;
	mknl_ini_que(&mbfcb_ram->sndque);
	mknl_ini_que(&mbfcb_ram->rcvque);
	mbfcb_ram->head      = 0;
	mbfcb_ram->fmbfsz    = pk_cmbf->mbfsz;
	mbfcb_ram->smsgcnt   = 0;
	mbfcb_ram->mbfcb_rom = mbfcb_rom;
	mbfcb_rom->mbfatr    = pk_cmbf->mbfatr;
	mbfcb_rom->maxmsz    = pk_cmbf->maxmsz;
	mbfcb_rom->mbfsz     = pk_cmbf->mbfsz;
	mbfcb_rom->mbf       = pk_cmbf->mbf;

	/* �Ǘ��e�[�u���֒ǉ� */
	KERNEL_MBFID_TO_MBFCB_RAM(mbfid) = mbfcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
