/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*   ������N�w�҂̐H���̖��                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "user_id.h"
#include "sh7045.h"
#include "sci.h"
#include "sample.h"


#define SCIID			ID_SCI1


#define LEFT_FORK(id)	((id) % 5 + 1)
#define RIGHT_FORK(id)	(id)



void SetLed(INT id);		/* �Ή���LED�_�� */
void ResetLed(INT id);		/* �Ή�LDE�̏��� */

int led = 0;

/* ���C���֐� */
int main()
{
	/* I/O �̏����� */
	*SH_PEIOR   = 0x00ff;
	*SH_PEDR    = 0;
	*SH_PACRL2 |= 0x0100;
	*SH_PEDR    = 0xff;
	
	/* HOS-V4 �̊J�n */
	sta_hos();
	
	return 0;
}


/* ATT_INI �o�^�̊֐� */
void SampleInitialize(VP_INT exinf)
{
	/* �^�X�N�N�� */
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER1);
//	act_tsk(TSKID_PHILOSOPHER1);
}


/* �N�w�҃^�X�N */
void PhilosopherTask(VP_INT exinf)
{
	INT id;
	INT i;
	
	*SH_PEDR = ~led;
	led++;
	ext_tsk();
	
	*SH_PEDR = 0xaaaa;
	for ( ; ; )
		;
	
	id = (INT)exinf;
	
	/* �����n���A���S���Y�� */
	for ( ; ; )
	{
		/* �K���Ȏ��ԔY��ł݂� */
		for ( i = rand() % 10 + 5; i > 0; i-- )
		{
			/* �_�ł����� */
			SetLed(id);
			dly_tsk(100);
			ResetLed(id);
			dly_tsk(100);
		}
		
		/* ���E�̃t�H�[�N����� */
		for ( ; ; )
		{
			wai_sem(LEFT_FORK(id));
			if ( pol_sem(RIGHT_FORK(id)) == E_OK )
			{
				break;
			}
			sig_sem(LEFT_FORK(id));
			dly_tsk((rand() % 10 + 1) * 10);	/* �K���ɑ҂� */
		}
		
		/* ���H���� */
		SetLed(id);			/* �_�������� */
		dly_tsk(1000);
		ResetLed(id);
		
		/* �t�H�[�N����� */
		sig_sem(LEFT_FORK(id));
		sig_sem(RIGHT_FORK(id));
	}
}


/* �Ή���LED�_�� */
void SetLed(INT id)
{
	wai_sem(SEMID_SYSCS);
	*SH_PEDR &= ~(0x01 << (id - 1));
	sig_sem(SEMID_SYSCS);
}


/* �Ή�LDE�̏��� */
void ResetLed(INT id)
{
	wai_sem(SEMID_SYSCS);
	*SH_PEDR |= (0x01 << (id - 1));
	sig_sem(SEMID_SYSCS);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
