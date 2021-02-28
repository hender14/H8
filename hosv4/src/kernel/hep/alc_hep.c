/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l�� �������Ǘ�                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "knl_hep.h"


/* �������̊��蓖�� */
VP kernel_alc_hep(
		T_KERNEL_HEPCB *pk_hepcb,
		SIZE           size)
{
	T_KERNEL_HEPBLK *mblk;
	T_KERNEL_HEPBLK *mblk_next;
	T_KERNEL_HEPBLK *mblk_next2;
	
	/* �q�[�v�̑��݃`�F�b�N */
	if ( pk_hepcb->base == NULL )
	{
		return NULL;
	}
	
	/* �T�C�Y�̃A���C�����g�𒲐�} */
	size = KERNEL_HEP_ALIGNED(size);
	
	/* �󂫗̈������ */
	mblk = pk_hepcb->base;
	while ( mblk->size != 0 )
	{
		if ( mblk->flag == KERNEL_HEP_FREE && mblk->size >= size )
		{
			/* �\���ȗe�ʂ��������� */
			if ( mblk->size - size > KERNEL_HEP_BLKSIZE + KERNEL_HEP_MEMALIGN )
			{
				/* �u���b�N�𕪊����� */
				mblk_next  = (T_KERNEL_HEPBLK *)((UB *)mblk + KERNEL_HEP_BLKSIZE + size);
				mblk_next2 = (T_KERNEL_HEPBLK *)((UB *)mblk + KERNEL_HEP_BLKSIZE + mblk->size);
				mblk_next->prev  = mblk;
				mblk_next->size  = mblk->size - size - KERNEL_HEP_BLKSIZE;
				mblk_next->flag  = KERNEL_HEP_FREE;
				mblk_next2->prev = mblk_next;
				mblk->size       = size;
			}
			mblk->flag = KERNEL_HEP_USING;
			
			return (VP)((UB *)mblk + KERNEL_HEP_BLKSIZE);
		}
		
		/* ���̃u���b�N�֐i�� */
		mblk = (T_KERNEL_HEPBLK *)((UB *)mblk + mblk->size + KERNEL_HEP_BLKSIZE);
	}

	return NULL;	/* �󂫂����� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */

