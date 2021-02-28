/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �ϒ��������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"
#include "knl_mem.h"


/* �ϒ��������v�[�� �R���g���[���u���b�N(���I�����p) */
typedef struct t_kernel_mplcb
{
	T_KERNEL_MPLCB_RAM mplcb_ram;	/* �ϒ��������v�[�� �R���g���[���u���b�N(RAM��) */
	T_KERNEL_MPLCB_ROM mplcb_rom;	/* �ϒ��������v�[�� �R���g���[���u���b�N(ROM��) */
} T_KERNEL_MPLCB;

/* �ϒ��������v�[�� �R���g���[���u���b�N(���I�����A�J�[�l���������p) */
typedef struct t_kernel_mplcb_with_blk
{
	T_KERNEL_MPLCB_RAM mplcb_ram;	/* �ϒ��������v�[�� �R���g���[���u���b�N(RAM��) */
	T_KERNEL_MPLCB_ROM mplcb_rom;	/* �ϒ��������v�[�� �R���g���[���u���b�N(ROM��) */
	VP	blk[1];			/* �������u���b�N�_�~�[ */
} T_KERNEL_MPLCB_WBLK;



/* �ϒ��������v�[���̐���(�J�[�l�������֐�) */
ER kernel_cre_mpl(
		ID           mplid,		/* �����Ώۂ̉ϒ��������v�[����ID�ԍ� */
		const T_CMPL *pk_cmpl)	/* �ϒ��������v�[������������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_MPLCB     *mplcb;
	T_KERNEL_MPLCB_RAM *mplcb_ram;
	T_KERNEL_MPLCB_ROM *mplcb_rom;
	VP   mpl;

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmpl->mplatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* �p�����[�^�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_cmpl->mplsz == 0 )
	{
		return E_PAR;   /* �p�����[�^�s�� */
	}
#endif

	/* �ϒ��������v�[���p�������̊m�� */
	mplcb = (T_KERNEL_MPLCB *)kernel_alc_mem(
		pk_cmpl->mpl != NULL ? 	sizeof(T_KERNEL_MPLCB) :
		sizeof(T_KERNEL_MPLCB_WBLK) - sizeof(VP)
		+ pk_cmpl->mplsz 
		);
	if ( mplcb == NULL )
	{
		return E_NOMEM;		/* �������s�� */
	}
	
	/* �������v�[���擪�Ԓn�Z�b�g */
	if ( pk_cmpl->mpl == NULL )
	{
		mpl = ((T_KERNEL_MPLCB_WBLK *)mplcb)->blk;
	}
	else
	{
		mpl = pk_cmpl->mpl;
	}

	/* �ϒ��������v�[���̐ݒ� */
	mplcb_ram = &mplcb->mplcb_ram;
	mplcb_rom = &mplcb->mplcb_rom;
	mknl_ini_que(&mplcb_ram->que);
	mplcb_ram->mplcb_rom = mplcb_rom;
	mplcb_rom->mplatr    = pk_cmpl->mplatr;
	mplcb_rom->mplsz     = pk_cmpl->mplsz;
	mplcb_rom->mpl       = pk_cmpl->mpl;

	/* �q�[�v���� */
	kernel_cre_hep(&mplcb_ram->hep, mplcb_rom->mpl, mplcb_rom->mplsz);

	/* �Ǘ��e�[�u���֒ǉ� */
	KERNEL_MPLID_TO_MPLCB_RAM(mplid) = mplcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
