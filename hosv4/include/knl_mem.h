/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l�� �������Ǘ�                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mem_h__
#define __HOS_V4__knl_mem_h__


#include "knl_hos.h"
#include "knl_hep.h"



/* --------------------------------------- */
/*            �}�N����`                   */
/* --------------------------------------- */
/* �T�C�Y�A���C�����g */
#define TSZ_ALIGNED(size)	(((size) + KERNEL_HEP_MEMALIGN - 1) & ~(KERNEL_HEP_MEMALIGN - 1))



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �J�[�l���������Ǘ� */
extern T_KERNEL_HEPCB kernel_mem_hep;		/* �J�[�l���p�������q�[�v */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �V�X�e���������Ǘ� */
void    kernel_ini_mem(void *p_base, SIZE size);	/* �������Ǘ��������� */
VP      kernel_alc_mem(SIZE size);					/* �������̊��蓖�� */
void    kernel_fre_mem(VP ptr);						/* �������̉�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mem_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
