/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l�� �������Ǘ�                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "knl_hep.h"



/* �������q�[�v�𐶐� */
void kernel_cre_hep(
		T_KERNEL_HEPCB *pk_hepcb,
		void           *p_base,
		SIZE           size)
{
	T_KERNEL_HEPBLK *blk_last;
	
	/* �T�C�Y�̃A���C�����g�𒲐� */
	size &= ~(KERNEL_HEP_MEMALIGN - 1);

	/* �T�C�Y�`�F�b�N */
	if ( size <= sizeof(T_KERNEL_HEPBLK) )
	{
		pk_hepcb->base = NULL;
		return;
	}

	/* �ݒ�ۑ� */
	pk_hepcb->base   = (T_KERNEL_HEPBLK *)p_base;
	pk_hepcb->heapsz = size;
	
	/* �I�[�ʒu�ɔԐl��ݒ� */
	blk_last = (T_KERNEL_HEPBLK *)((UB *)p_base + size - KERNEL_HEP_BLKSIZE);
	
	/* �S�̂��󂫗̈�ɐݒ� */
	pk_hepcb->base->prev = NULL;
	pk_hepcb->base->size = size - (KERNEL_HEP_BLKSIZE * 2);
	pk_hepcb->base->flag = KERNEL_HEP_FREE;
	
	/* �I�[�̔Ԑl�𗘗p���ɐݒ� */
	blk_last->prev = NULL;
	blk_last->size = 0;
	blk_last->flag = KERNEL_HEP_USING;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */

