/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Z�}�t�H                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"
#include "knl_mem.h"


/* �Z�}�t�H�R���g���[���u���b�N(���I�����p) */
typedef struct t_kernel_semcb
{
	T_KERNEL_SEMCB_RAM semcb_ram;	/* �Z�}�t�H�R���g���[���u���b�N(RAM��) */
	T_KERNEL_SEMCB_ROM semcb_rom;	/* �Z�}�t�H�R���g���[���u���b�N(ROM��) */
} T_KERNEL_SEMCB;



/* �Z�}�t�H�̐���(�J�[�l�������֐�) */
ER kernel_cre_sem(
		ID           semid,		/* �����Ώۂ̃Z�}�t�H��ID�ԍ� */
		const T_CSEM *pk_csem)	/* �Z�}�t�H����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_SEMCB     *semcb;
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_KERNEL_SEMCB_ROM *semcb_rom;

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_csem->sematr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* �Z�}�t�H�p�������̊m�� */
	semcb = (T_KERNEL_SEMCB *)kernel_alc_mem(sizeof(T_KERNEL_SEMCB));
#ifdef HOS_ERCHK_E_NOMEM
	if ( semcb == NULL )
	{
		return E_NOMEM;		/* �������s�� */
	}
#endif

	/* �Z�}�t�H�̐ݒ� */
	semcb_ram = &semcb->semcb_ram;
	semcb_rom = &semcb->semcb_rom;
	mknl_ini_que(&semcb_ram->que);
	semcb_ram->semcnt    = pk_csem->isemcnt;
	semcb_ram->semcb_rom = semcb_rom;
	semcb_rom->sematr    = pk_csem->sematr;
	semcb_rom->isemcnt   = pk_csem->isemcnt;
	semcb_rom->maxsem    = pk_csem->maxsem;

	/* �Ǘ��e�[�u���֒ǉ� */
	KERNEL_SEMID_TO_SEMCB_RAM(semid) = semcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
