/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �T���v���v���O����                                                     */
/*   ���C�����[�`��                                                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include "kernel.h"
#include "kernel_id.h"
#include "test.h"



/* ���C���֐� */
int main()
{
	/* �K�v�Ȃ炱���� �n�[�h�E�F�A�̐ݒ�ȂǍs�� */

	/* HOS-V4 �̊J�n */
	sta_hos();
	
	return 0;
}


/* ATT_INI �o�^�̊֐� */
void TestStart(VP_INT exinf)
{
	/* �^�X�N�N�� */
	act_tsk(TSKID_TEST1);
//	act_tsk(TSKID_TEST2);
//	act_tsk(TSKID_TEST3);
}


/* �T���v���^�X�N�P */
void Task1(VP_INT exinf)
{
	ER ercd;

	printf("Task1:Start\n");

	wup_tsk(1);
	slp_tsk();

	printf("Task1:slp_tsk()\n");
	ercd = slp_tsk();
	printf("Task1:slp_tsk() ret = %d\n", ercd);

	printf("Task1:End\n");
	ext_tsk();
}


/* �T���v���^�X�N�Q */
void Task2(VP_INT exinf)
{
	ER ercd;

	printf("Task2:Start\n");

	printf("Task2:wup_tsk()\n");
	ercd = wup_tsk(1);
	printf("Task2:wup_tsk(1) ret = %d\n", ercd);

	printf("Task2:End\n");
	ext_tsk();
}


/* �T���v���^�X�N3 */
void Task3(VP_INT exinf)
{
	ER ercd;

	printf("Task3:Start\n");

	printf("Task3:wup_tsk(1)\n");
	ercd = wup_tsk(1);
	printf("Task3:wup_tsk(1) ret = %d\n", ercd);

	printf("Task3:End\n");

	ext_tsk();
}



/* �����n���h���T���v�� */
void CycHandler1(VP_INT exinf)
{
}


/* ���荞�݃n���h���T���v�� */
void IntHndler1(VP_INT exinf)
{
	isig_tim();		/* �^�C���e�B�b�N�̋��� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
