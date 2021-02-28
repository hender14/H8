/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�Ǘ��@�\                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"
#include "knl_mem.h"


static void kernel_exd_tsk(VP_INT exinf);	/* ���^�X�N�̏I���ƍ폜(�V�X�e���^�X�N�Ŏ��s) */


/* ���^�X�N�̏I���ƍ폜 */
void exd_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB       *mtcb_run;

	/* ���s���^�X�N�̎擾 */
	mtcb_run = mknl_get_run_tsk();
	tcb_ram  = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb_run);

	mknl_loc_sys();		/* �V�X�e���̃��b�N */

	/* �V�X�e���^�X�N���珈�����s�� */
	mknl_exe_sys((FP)kernel_exd_tsk, (VP_INT)tcb_ram);
}


/* ���^�X�N�̏I���ƍ폜(�V�X�e���^�X�N�Ŏ��s) */
void kernel_exd_tsk(VP_INT exinf)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ID               tskid;
	
	tcb_ram = (T_KERNEL_TCB_RAM *)exinf;
	tskid   = kernel_get_tid(tcb_ram);

	/* �^�X�N���I�������� */
	mknl_ter_tsk(&tcb_ram->mtcb);
	
	/* �������̉�� */
	kernel_fre_mem(tcb_ram);
	
	/* �^�X�N�R���g���[���u���b�N�e�[�u������o�^���� */
	KERNEL_TSKID_TO_TCB_RAM(tskid) = NULL;

	/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_dsp();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
