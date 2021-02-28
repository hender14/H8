/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���[���{�b�N�X                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"
#include "knl_mem.h"



/* ���[���{�b�N�X�R���g���[���u���b�N(���I�����p) */
typedef struct t_kernel_mbxcb
{
	T_KERNEL_MBXCB_RAM mbxcb_ram;	/* ���[���{�b�N�X�R���g���[���u���b�N(RAM��) */
	T_KERNEL_MBXCB_ROM mbxcb_rom;	/* ���[���{�b�N�X�R���g���[���u���b�N(ROM��) */
} T_KERNEL_MBXCB;

/* �D��x�ʃL���[�w�b�_���J�[�l���Ŋm�ۂ���ꍇ */
typedef struct t_kernel_mbxcb_ph
{
	T_KERNEL_MBXCB	mbxcb;
	T_MSG		*mprihd[1];
} T_KERNEL_MBXCB_PH;


/* ���[���{�b�N�X�̐���(�J�[�l�������֐�) */
ER kernel_cre_mbx(
		ID           mbxid,		/* �����Ώۂ̃��[���{�b�N�X��ID�ԍ� */
		const T_CMBX *pk_cmbx)	/* ���[���{�b�N�X����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_MBXCB     *mbxcb;
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_MSG **mprihd;
	PRI   maxmpri;
	PRI   msgpri;

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmbx->mbxatr & ~(TA_TFIFO | TA_TPRI | TA_MFIFO | TA_MPRI) )
	{
		return E_RSATR;
	}
#endif

	/* ���b�Z�[�W�D��x�t�������� */
	if ( pk_cmbx->mbxatr & TA_MPRI )
	{
		maxmpri = pk_cmbx->maxmpri;
		mprihd  = (T_MSG **)pk_cmbx->mprihd;
	}
	else
	{
		maxmpri = TMIN_MPRI;
		mprihd  = NULL;
	}

	/* ���[���{�b�N�X�p�������̊m�� */
	mbxcb = (T_KERNEL_MBXCB *)kernel_alc_mem(
			mprihd == NULL ?
			sizeof(T_KERNEL_MBXCB_PH)+TSZ_MPRIHD(maxmpri-1) :
			sizeof(T_KERNEL_MBXCB));
	if ( mbxcb == NULL )
	{
		return E_NOMEM;		/* �������s�� */
	}

	/* ���b�Z�[�W�L���[�w�b�_���J�[�l���Ŋm�ۂ���ꍇ�̃|�C���^�Z�b�g */
	if ( mprihd == NULL )
	{
		mprihd = ((T_KERNEL_MBXCB_PH *)mbxcb)->mprihd;
	}

	/* ���[���{�b�N�X�̐ݒ� */
	mbxcb_ram = &mbxcb->mbxcb_ram;
	mbxcb_rom = &mbxcb->mbxcb_rom;
	mknl_ini_que(&mbxcb_ram->que);
	mbxcb_ram->mbxcb_rom = mbxcb_rom;
	mbxcb_rom->mbxatr    = pk_cmbx->mbxatr;
	mbxcb_rom->maxmpri   = maxmpri;
	mbxcb_rom->mprihd    = mprihd;

	/* �D��x�ʂ̃��b�Z�[�W�L���[�̏����� */
	for ( msgpri = 0; msgpri <= maxmpri - TMIN_MPRI; msgpri++ )
	{
		mprihd[msgpri] = NULL;
	}

	/* �Ǘ��e�[�u���֒ǉ� */
	KERNEL_MBXID_TO_MBXCB_RAM(mbxid) = mbxcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
