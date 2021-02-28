/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*   ������N�w�҂̐H���̖��                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include "kernel.h"
#include "kernel_id.h"
#include "sample.h"



#define LEFT_FORK(id)	((id) % 5 + 1)
#define RIGHT_FORK(id)	(id)


static char status[] = "TTTTT\n";



/* ���C���֐� */
int main()
{
	/* HOS-V4 �̊J�n */
	sta_hos();
	
	return 0;
}


/* ATT_INI �o�^�̊֐� */
void SampleInitialize(VP_INT exinf)
{
	/* �^�X�N�N�� */
	act_tsk(TSKID_OUTPUT);
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER2);
	act_tsk(TSKID_PHILOSOPHER3);
	act_tsk(TSKID_PHILOSOPHER4);
	act_tsk(TSKID_PHILOSOPHER5);
}


/* �N�w�҃^�X�N */
void PhilosopherTask(VP_INT exinf)
{
	INT id;

	id = (INT)exinf;

	/* ���΂��A���S���Y�� */
	for ( ; ; )
	{
		/* �K���Ȏ��ԔY��ł݂� */
		status[id -1] = 'T';
		snd_mbf(MBFID_OUTPUT, status, 7);
		dly_tsk((rand() % 100) * 10 + 500);

		/* ���E�̃t�H�[�N�����܂ŔS�� */
		status[id -1] = 'W';
		snd_mbf(MBFID_OUTPUT, status, 7);
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
		status[id -1] = 'E';
		snd_mbf(MBFID_OUTPUT, status, 7);
		dly_tsk(1000);

		/* �t�H�[�N����� */
		sig_sem(LEFT_FORK(id));
		sig_sem(RIGHT_FORK(id));
	}
}


void OutputTask(VP_INT exinf)
{
	ER_UINT ercd;
	char buf[128];

	for ( ; ; )
	{
		ercd = rcv_mbf(MBFID_OUTPUT, buf);
		printf("%d : %s", ercd, buf);
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
