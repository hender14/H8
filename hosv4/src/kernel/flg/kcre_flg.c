/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �C�x���g�t���O                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"
#include "knl_mem.h"



/* �C�x���g�t���O�R���g���[���u���b�N(���I�����p) */
typedef struct t_kernel_flgcb
{
	T_KERNEL_FLGCB_RAM flgcb_ram;	/* �C�x���g�t���O�R���g���[���u���b�N(RAM��) */
	T_KERNEL_FLGCB_ROM flgcb_rom;	/* �C�x���g�t���O�R���g���[���u���b�N(ROM��) */
} T_KERNEL_FLGCB;



/* �C�x���g�t���O�̐���(�J�[�l�������֐�) */
ER kernel_cre_flg(
		ID           flgid,		/* �����Ώۂ̃C�x���g�t���O��ID�ԍ� */
		const T_CFLG *pk_cflg)	/* �C�x���g�t���O����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_FLGCB     *flgcb;
	T_KERNEL_FLGCB_RAM *flgcb_ram;
	T_KERNEL_FLGCB_ROM *flgcb_rom;

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cflg->flgatr & ~(TA_TFIFO | TA_TPRI | TA_WSGL | TA_WMUL | TA_CLR) )
	{
		return E_RSATR;
	}
#endif

	/* �C�x���g�t���O�p�������̊m�� */
	flgcb = (T_KERNEL_FLGCB *)kernel_alc_mem(sizeof(T_KERNEL_FLGCB));
	if ( flgcb == NULL )
	{
		return E_NOMEM;		/* �������s�� */
	}

	/* �C�x���g�t���O�̐ݒ� */
	flgcb_ram = &flgcb->flgcb_ram;
	flgcb_rom = &flgcb->flgcb_rom;
	flgcb_rom->flgatr  = pk_cflg->flgatr;
	flgcb_rom->iflgptn = pk_cflg->iflgptn;
	mknl_ini_que(&flgcb_ram->que);
	flgcb_ram->flgptn    = flgcb_rom->iflgptn;
	flgcb_ram->flgcb_rom = flgcb_rom;

	/* �Ǘ��e�[�u���֒ǉ� */
	KERNEL_FLGID_TO_FLGCB_RAM(flgid) = flgcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
