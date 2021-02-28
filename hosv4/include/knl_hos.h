/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l�� HOS �ŗL����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_hos_h__
#define __HOS_V4__knl_hos_h__


#include <stddef.h>
#include "itron.h"
#include "mknl.h"
#include "hoserchk.h"


/* ------------------------------------------ */
/*                �}�N����`                  */
/* ------------------------------------------ */

/* C++ �� static_cast ���Z�q�Ɠ������ʂ̃}�N�� */
#define KERNEL_STATIC_CAST(s, m, p)	((s *)((B*)(p))-offsetof(s, m))	/* �����o�̃A�h���X����\���̂̃A�h���X�Z�o */

/* C����̍\���̂�p���ă|�����[�t�B�Y������������ۂ� */
/* �\���̃����o�̃|�C���^����A�\���̐擪�̃|�C���^��  */
/* �Z�o���邱�Ƃ��K�{�ƂȂ�B��L�� C++ ����ł�       */
/* dynamic_cast �� static_cast ���Z�q�ň��S�ɍs���邪  */
/* C����ł͂�����x�����Ɏ�������K�v������B         */



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �J�[�l���V�X�e���Ǘ� */
extern STAT kernel_ctx_stat;				/* �V�X�e���̃R���e�L�X�g��� */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �J�[�l���V�X�e���Ǘ� */
ER      sta_hos(void);								/* �J�[�l������J�n */


/* �J�[�l�������֐� */
#define kernel_get_run_tsk()	\
			(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mknl_get_run_tsk()))
													/* ���s���^�X�N�擾(�}�N���֐�) */


/* �R���t�B�M�����[�^�[�����֐� */
void    kernel_cfg_init(void);						/* �ϐ��̏����� */
void    kernel_cfg_start(void);						/* �������֐��Ăяo�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_hos_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
