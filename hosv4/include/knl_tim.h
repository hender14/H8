/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���ԊǗ�                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_tim_h__
#define __HOS_V4__knl_tim_h__



#include "knl_hos.h"



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �^�C�}�I�u�W�F�N�g�\���� */
typedef struct t_kernel_tim
{
	struct t_kernel_tim *next;
	struct t_kernel_tim *prev;
	FP                  timhdr;
} T_KERNEL_TIM;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �V�X�e�������Ǘ� */
extern const UW kernel_tic_deno;				/* �R���t�B�M�����[�V������ TIC_DENO ��ݒ� */
extern const UW kernel_tic_div;					/* �R���t�B�M�����[�V������ TIC_NUME / TIC_DENO ��ݒ� */
extern const UW kernel_tic_mod;					/* �R���t�B�M�����[�V������ TIC_NUME % TIC_DENO ��ݒ� */
extern UW       kernel_tic_cnt;					/* �^�C���e�B�b�N�p�J�E���^ */
extern SYSTIM   kernel_systim;					/* �V�X�e������ */


/* �^�C�}���X�g�Ǘ� */
extern T_KERNEL_TIM *kernel_tml_head;	/* �^�C�}���X�g�擪�ʒu */
extern T_KERNEL_TIM *kernel_tml_ptr;	/* �^�C�}���X�g�|�C���^ */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �V�X�e�������Ǘ� */
void    kernel_ini_tim(void);						/* ���ԊǗ��@�\�̏����� */
ER      set_tim(const SYSTIM *p_systim);			/* �V�X�e�������̐ݒ� */
ER      get_tim(SYSTIM *p_systim);					/* �V�X�e�������̎擾 */
ER      isig_tim(void);								/* �^�C���e�B�b�N�̋��� */

/* �^�C�}���X�g���� */
void    kernel_add_tml(T_KERNEL_TIM *timobj);		/* �^�C�}�I�u�W�F�N�g�̃��X�g�ւ̒ǉ� */
void    kernel_rmv_tml(T_KERNEL_TIM *timobj);		/* �^�C�}�I�u�W�F�N�g�̃��X�g����̍폜 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_tim_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
