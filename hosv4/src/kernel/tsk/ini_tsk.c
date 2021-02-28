/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�Ǘ��@�\                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �^�X�N�̏����� */
void kernel_ini_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	int i;

	/* TCB��RAM���̓[���̈�ɂ��Ă����ăR�[�h�ŏ����������ق����������悢 */
	for ( i = KERNEL_TMIN_TSKID; i <= KERNEL_TMAX_TSKID; i++ )
	{
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(i);
		if ( tcb_ram != NULL )
		{
			/* �ʃJ�[�l�������̏����� */
			mknl_ini_tsk(&tcb_ram->mtcb);
			
			/* TA_ACT�����̂��̂��N������ */
			if ( tcb_ram->tcb_rom->tskatr & TA_ACT )
			{
				act_tsk(i);
			}
		}
	}
}


/* �^�X�N�̃G���g���[�|�C���g */
void kernel_task_entry(
		VP_INT exinf)		/* �^�X�N�̊g����� */
{
	register const T_KERNEL_TCB_ROM *tcb_rom;
	register T_KERNEL_TCB_RAM *tcb_ram;

	/* �X�^�[�g�A�h���X�̎Z�o */
	tcb_ram = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mknl_get_run_tsk());
	tcb_rom = tcb_ram->tcb_rom;

	mknl_unl_sys();			/* �V�X�e���̃��b�N���� */

	tcb_rom->task(exinf);	/* �^�X�N���s */

	ext_tsk();	/* ���^�[�����͏I�� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
