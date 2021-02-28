/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �f�[�^�L���[                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"
#include "knl_mem.h"




/* �f�[�^�L���[�R���g���[���u���b�N(���I�����p) */
typedef struct t_kernel_dtqcb
{
	T_KERNEL_DTQCB_RAM dtqcb_ram;	/* �f�[�^�L���[�R���g���[���u���b�N(RAM��) */
	T_KERNEL_DTQCB_ROM dtqcb_rom;	/* �f�[�^�L���[�R���g���[���u���b�N(ROM��) */
} T_KERNEL_DTQCB;

/* �f�[�^�L���[�R���g���[���u���b�N(���I�����A�J�[�l���������p) */
typedef struct t_kernel_dtqcb_with_blk
{
	T_KERNEL_DTQCB_RAM dtqcb_ram;	/* �f�[�^�L���[�R���g���[���u���b�N(RAM��) */
	T_KERNEL_DTQCB_ROM dtqcb_rom;	/* �f�[�^�L���[�R���g���[���u���b�N(ROM��) */
	VP_INT	blk[1];			/* �_�~�[�f�[�^�u���b�N */
} T_KERNEL_DTQCB_WBLK;



/* �f�[�^�L���[�̐���(�J�[�l�������֐�) */
ER kernel_cre_dtq(
		ID           dtqid,		/* �����Ώۂ̃f�[�^�L���[��ID�ԍ� */
		const T_CDTQ *pk_cdtq)	/* �f�[�^�L���[����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_DTQCB     *dtqcb;
	T_KERNEL_DTQCB_RAM *dtqcb_ram;
	T_KERNEL_DTQCB_ROM *dtqcb_rom;

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cdtq->dtqatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* �f�[�^�L���[�p�������̊m�� */
	dtqcb = (T_KERNEL_DTQCB *)kernel_alc_mem(
		pk_cdtq->dtq != NULL ?
			sizeof(T_KERNEL_DTQCB) :
			sizeof(T_KERNEL_DTQCB_WBLK) - sizeof(VP_INT)
			+ ( sizeof(VP_INT *) * pk_cdtq->dtqcnt )
		);
	if ( dtqcb == NULL )
	{
		return E_NOMEM;		/* �������s�� */
	}
	
	/* �f�[�^�L���[�̐ݒ� */
	dtqcb_ram = &dtqcb->dtqcb_ram;
	dtqcb_rom = &dtqcb->dtqcb_rom;
	dtqcb_rom->dtqatr = pk_cdtq->dtqatr;
	dtqcb_rom->dtqcnt = pk_cdtq->dtqcnt;
	dtqcb_rom->dtq =  pk_cdtq->dtq != NULL ?
	    (VP_INT *)pk_cdtq->dtq : ((T_KERNEL_DTQCB_WBLK *)dtqcb)->blk;
	mknl_ini_que(&dtqcb_ram->sndque);
	mknl_ini_que(&dtqcb_ram->rcvque);
	dtqcb_ram->head      = 0;
	dtqcb_ram->datacnt   = 0;
	dtqcb_ram->dtqcb_rom = dtqcb_rom;

	/* �Ǘ��e�[�u���֒ǉ� */
	KERNEL_DTQID_TO_DTQCB_RAM(dtqid) = dtqcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
