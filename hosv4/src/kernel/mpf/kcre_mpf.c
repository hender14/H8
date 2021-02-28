/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Œ蒷�������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"
#include "knl_mem.h"


/* �Œ蒷�������v�[�� �R���g���[���u���b�N(���I�����p) */
typedef struct t_kernel_mpfcb
{
	T_KERNEL_MPFCB_RAM mpfcb_ram;	/* �Œ蒷�������v�[�� �R���g���[���u���b�N(RAM��) */
	T_KERNEL_MPFCB_ROM mpfcb_rom;	/* �Œ蒷�������v�[�� �R���g���[���u���b�N(ROM��) */
} T_KERNEL_MPFCB;

/* �Œ蒷�������v�[�� �R���g���[���u���b�N(���I�����A�J�[�l���������p) */
typedef struct t_kernel_mpfcb_with_blk
{
	T_KERNEL_MPFCB_RAM mpfcb_ram;	/* �Œ蒷�������v�[�� �R���g���[���u���b�N(RAM��) */
	T_KERNEL_MPFCB_ROM mpfcb_rom;	/* �Œ蒷�������v�[�� �R���g���[���u���b�N(ROM��) */
	VP	blk[1];			/* �������u���b�N�_�~�[ */
} T_KERNEL_MPFCB_WBLK;



/* �Œ蒷�������v�[���̐���(�J�[�l�������֐�) */
ER kernel_cre_mpf(
		ID           mpfid,		/* �����Ώۂ̌Œ蒷�������v�[����ID�ԍ� */
		const T_CMPF *pk_cmpf)	/* �Œ蒷�������v�[������������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_MPFCB     *mpfcb;
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_KERNEL_MPFCB_ROM *mpfcb_rom;
	VP   mpf;
	UINT i;

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmpf->mpfatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

        /* �p�����[�^�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
        if ( pk_cmpf->blkcnt == 0 || pk_cmpf->blksz == 0 )
	{
                return E_PAR;   /* �p�����[�^�s�� */
	}
#endif

	/* �Œ蒷�������v�[���p�������̊m�� */
	mpfcb = (T_KERNEL_MPFCB *)kernel_alc_mem(
		pk_cmpf->mpf != NULL ? 	sizeof(T_KERNEL_MPFCB) :
		sizeof(T_KERNEL_MPFCB_WBLK) - sizeof(VP)
		+ TSZ_MPF( pk_cmpf->blkcnt, pk_cmpf->blksz ) 
		);
	if ( mpfcb == NULL )
	{
		return E_NOMEM;		/* �������s�� */
	}
	
	/* �������v�[���擪�Ԓn�Z�b�g */
	if ( pk_cmpf->mpf == NULL )
	{
		mpf = ((T_KERNEL_MPFCB_WBLK *)mpfcb)->blk;
	}
	else
	{
		mpf = pk_cmpf->mpf;
	}

	/* �Œ蒷�������v�[���̐ݒ� */
	mpfcb_ram = &mpfcb->mpfcb_ram;
	mpfcb_rom = &mpfcb->mpfcb_rom;
	mknl_ini_que(&mpfcb_ram->que);
	mpfcb_ram->free      = mpf;
	mpfcb_ram->mpfcb_rom = mpfcb_rom;
	mpfcb_rom->mpfatr    = pk_cmpf->mpfatr;
	mpfcb_rom->blkcnt    = pk_cmpf->blkcnt;
	mpfcb_rom->blksz     = TSZ_ALIGNED(pk_cmpf->blksz);

	/* �u���b�N�̏����� */
	for ( i = 0; i < mpfcb_rom->blkcnt - 1; i++ )
	{
		*(VP *)mpf = (VP)((UB *)mpf + mpfcb_rom->blksz);
		mpf        = (VP)((UB *)mpf + mpfcb_rom->blksz);
	}
	*(VP *)mpf = NULL;	/* �ŏI�u���b�N */

	/* �Ǘ��e�[�u���֒ǉ� */
	KERNEL_MPFID_TO_MPFCB_RAM(mpfid) = mpfcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
