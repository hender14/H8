/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l�� �������q�[�v                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_hep_h__
#define __HOS_V4__knl_hep_h__


#include "itron.h"


#define KERNEL_HEP_MEMALIGN		32			/* �������A���C�����g */
#define KERNEL_HEP_USING		0x1234		/* �g�p�� */
#define KERNEL_HEP_FREE			0xabcd		/* ���g�p */



/** %jp{�T�C�Y�A���C�����g} */
#define KERNEL_HEP_ALIGNED(size)	(((size) + KERNEL_HEP_MEMALIGN - 1) & ~(KERNEL_HEP_MEMALIGN - 1))


/** %jp{�q�[�v�������u���b�N} */
typedef struct kernel_t_hepblk
{
	struct kernel_t_hepblk* prev;	/* �O�̃u���b�N */
	SIZE   size;					/* �u���b�N�̃T�C�Y */
	INT    flag;					/* �g�p���t���O */
} T_KERNEL_HEPBLK;


/** %jp{�q�[�v����u���b�N} */
typedef struct kernel_t_hepcb
{
	T_KERNEL_HEPBLK *base;			/* �J�[�l���p�������擪�u���b�N�̃A�h���X */
	SIZE            heapsz;			/* �J�[�l���p�������T�C�Y */
} T_KERNEL_HEPCB;


/** %jp{�J�[�l���������Ǘ��u���b�N�T�C�Y} */
#define KERNEL_HEP_BLKSIZE			KERNEL_HEP_ALIGNED(sizeof(T_KERNEL_HEPBLK))


#ifdef __cplusplus
extern "C" {
#endif

void    kernel_cre_hep(T_KERNEL_HEPCB *pk_hepcb, void *p_base, SIZE size);	/* �������q�[�v�𐶐� */
#define kernel_del_hep(pk_hepcb)	do {} while(0)							/* �������q�[�v���폜 */
VP      kernel_alc_hep(T_KERNEL_HEPCB *pk_hepcb, SIZE size);				/* �������̊��蓖�� */
void    kernel_fre_hep(T_KERNEL_HEPCB *pk_hepcb, VP ptr);					/* �������̉�� */
#define kernel_alg_hep(size)		KERNEL_HEP_ALIGNED(size)				/* �������T�C�Y�̃A���C�����g�����킹�� */

#ifdef __cplusplus
}
#endif


#endif	/* __HOS_V4__knl_hep_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
