/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l�� �������Ǘ�                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_hep.h"



/** �������̉�� */
void kernel_fre_hep(
		T_KERNEL_HEPCB *pk_hepcb,
		VP             ptr)
{
	T_KERNEL_HEPBLK *mblk;
	T_KERNEL_HEPBLK *mblktmp;
	T_KERNEL_HEPBLK *mblknext;

	/* %jp{�|�C���^�͈̓`�F�b�N */
	if ( ptr < (VP)pk_hepcb->base || ptr >= (VP)((UB*)pk_hepcb->base + pk_hepcb->heapsz) )
	{
		return;
	}

	/* %jp{�������u���b�N�ʒu���擾 */
	mblk = (T_KERNEL_HEPBLK *)((UB *)ptr - KERNEL_HEP_BLKSIZE);

	/* %jp{�p�����[�^�[�`�F�b�N */
	if ( mblk->flag != KERNEL_HEP_USING )	/* %jp{�g�p���Ŗ������ */
	{
		return;
	}

	/* %jp{�t���O�𖢎g�p�ɐݒ�} */
	mblk->flag = KERNEL_HEP_FREE;
	
	/* %jp{���̃u���b�N���`�F�b�N} */
	mblktmp = (T_KERNEL_HEPBLK *)((UB *)ptr + mblk->size);
	if ( mblktmp->flag == KERNEL_HEP_FREE )
	{
		/* %jp{���̃u���b�N�����g�p�Ȃ猋������} */
		mblknext = (T_KERNEL_HEPBLK *)((UB *)mblktmp + mblktmp->size + KERNEL_HEP_BLKSIZE);
		mblknext->prev = mblk;
		mblk->size += mblktmp->size + KERNEL_HEP_BLKSIZE;
	}

	/* %jp{�O�̃u���b�N���`�F�b�N} */
	if ( mblk->prev != NULL )
	{
		mblktmp = mblk->prev;
		if ( mblktmp->flag == KERNEL_HEP_FREE )
		{
			/* %jp{�O�̃u���b�N�����g�p�Ȃ猋������} */
			mblknext = (T_KERNEL_HEPBLK *)((UB *)mblk + mblk->size + KERNEL_HEP_BLKSIZE);
			mblknext->prev = mblktmp;
			mblktmp->size += mblk->size + KERNEL_HEP_BLKSIZE;
		}
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */

