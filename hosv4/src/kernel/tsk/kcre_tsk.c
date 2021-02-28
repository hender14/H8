/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�Ǘ��@�\                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_tsk.h"
#include "knl_mem.h"



/* �^�X�N�̐���(�J�[�l������) */
ER kernel_cre_tsk(
		ID           tskid,		/* �����Ώۂ̃^�X�NID�ԍ� */
		const T_CTSK *pk_ctsk)	/* �^�X�N����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_KERNEL_TCB_ROM *tcb_rom;
	SIZE memsize;
	UB   *memptr;
	
	/* �K�v�ȃ������T�C�Y���v�Z */
	memsize = sizeof(T_KERNEL_TCB_RAM) + sizeof(T_KERNEL_TCB_ROM);
	if ( pk_ctsk->stk == NULL )
	{
		memsize += pk_ctsk->stksz;	/* �X�^�b�N�T�C�Y�����Z */
	}
	
	/* �������m�� */
	memptr = (UB *)kernel_alc_mem(memsize);
#ifdef HOS_ERCHK_E_NOMEM
	if ( memptr == NULL )
	{
		return E_NOMEM;		/* �������s�� */
	}
#endif

	/* �|�C���^�ݒ� */	
	tcb_ram  = (T_KERNEL_TCB_RAM *)memptr;
	memptr  += sizeof(T_KERNEL_TCB_RAM);
	tcb_rom  = (T_KERNEL_TCB_ROM *)memptr;
	if ( pk_ctsk->stk == NULL )
	{
		memptr  += sizeof(T_KERNEL_TCB_ROM);
		tcb_rom->stk = (VP)memptr;
	}
	else
	{
		tcb_rom->stk = pk_ctsk->stk;
	}

	/* �ʃJ�[�l���^�X�N�̏����� */
	memset(&tcb_ram->mtcb, 0, sizeof(tcb_ram->mtcb));
	mknl_ini_tsk(&tcb_ram->mtcb);

	/* �l�ݒ� */
	tcb_ram->actcnt  = 0;					/* �N���v���L���[�C���O�� */
	tcb_ram->suscnt  = 0;					/* SUSPEND�v���l�X�g�� */
	tcb_ram->wupcnt  = 0;					/* �N���v���L���[�C���O�� */
	tcb_ram->tcb_rom = tcb_rom;				/* �^�X�N�R���g���[���u���b�NROM���ւ̃|�C���^ */
	tcb_rom->tskatr  = pk_ctsk->tskatr;		/* �^�X�N���� */
	tcb_rom->exinf   = pk_ctsk->exinf;		/* �^�X�N�̊g����� */
	tcb_rom->task    = pk_ctsk->task;		/* �^�X�N�̋N���Ԓn */
	tcb_rom->itskpri = pk_ctsk->itskpri;	/* �^�X�N�̋N�����D��x */
	tcb_rom->stksz   = pk_ctsk->stksz;		/* �^�X�N�̃X�^�b�N�̃T�C�Y�i�o�C�g���j */

	/* �^�X�N�R���g���[���u���b�N�e�[�u���ɓo�^ */
	KERNEL_TSKID_TO_TCB_RAM(tskid) = tcb_ram;

	/* ���s��ԂŐ��� */
	if ( pk_ctsk->tskatr & TA_ACT )
	{
		/* ���s�R���e�L�X�g�o�^ */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* �o�^����^�X�N */
				tcb_rom->exinf,			/* �^�X�N�̊g����� */
				(FP)kernel_task_entry,	/* �^�X�N�̋N���Ԓn */
				tcb_rom->itskpri,		/* �^�X�N�̋N�����D��x */
				tcb_rom->stksz,			/* �^�X�N�̃X�^�b�N�̈�T�C�Y */
				tcb_rom->stk			/* �^�X�N�̃X�^�b�N�̈�̐擪�Ԓn */
			);	
		
		mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();		/* ��O�����̎��s */
	}

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
