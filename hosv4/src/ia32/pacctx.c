/* ------------------------------------------------------------------------  */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                   */
/*   �v���Z�b�T���ۉ��R���|�[�l���g (IA32�p)  �R���e�L�X�g�֘A����           */
/*                                                                           */
/*                                  Copyright (C) 1998-2002 by Project HOS   */
/*                                  http://sourceforge.jp/projects/hos/      */
/* ------------------------------------------------------------------------  */
#include "hosdenv.h"
#include "kernel.h"

#define STACK_POINTER_SIZE  4  /* �X�^�b�N�|�C���^�T�C�Y  */
#define start_stack_addr(top,size) /*  �X�^�b�N�J�n�A�h���X  */\
           ((top)+((size) & (~STACK_POINTER_SIZE)))

void 
hospac_cre_ctx(T_HOSPAC_CTXINF *pk_ctxinf, 
	       VP_INT exinf, 
	       FP task, 
	       SIZE stksz, 
	       VP  stk)
{

  pk_ctxinf->sp=(VP)start_stack_addr((UW)stk,(UW)stksz);
  __hos_pac_ia32_prep_ini_stack(&(pk_ctxinf->sp),task, ext_tsk,exinf);
}

void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
		    T_HOSPAC_CTXINF *pk_nxt_ctxinf)
{
/*
 *  �����Ċ֐��Ăяo�����ЂƂ��ނ��Ƃ�, �X�N���b�`���W�X�^��
 *  �Ҕ����ďo����(�{�֐�)�ɈϏ����邱�Ƃ��o����.
 *  �����������, �R���p�C���ς��ŕK�v�ȃ��W�X�^������Ҕ�������悤�ɂ���
 */
    __hos_pac_ia32_do_task_switch(&(pk_pre_ctxinf->sp),&(pk_nxt_ctxinf->sp));
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
