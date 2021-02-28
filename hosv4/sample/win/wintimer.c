/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*   Windows�p �C���^�[�o���^�C�}�I�u�W�F�N�g                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "wintimer.h"



DWORD WINAPI WinTimer_Thread(LPVOID param);	/* �^�C�}���荞�ݗp�X���b�h�֐� */


static HANDLE hEventTimer;
static INTNO  intnoTimer;


/* ������ */
void WinTimer_Initialize(INTNO intno)
{
	DWORD dwThreadId;

	/* �[�����荞�ݔԍ���ݒ� */
	intnoTimer = intno;

	/* �^�C�}�p�C�x���g�̍쐬 */
	hEventTimer = CreateEvent(NULL, FALSE, FALSE, NULL);

	/* �}���`���f�B�A�^�C�}�̊J�n */
	timeSetEvent(10, 1, (LPTIMECALLBACK)hEventTimer, 0, TIME_PERIODIC | TIME_CALLBACK_EVENT_PULSE);

	CreateThread(NULL, 0, WinTimer_Thread, 0, 0, &dwThreadId);
}


/* �^�C�}���荞�ݗp�X���b�h�֐� */
DWORD WINAPI WinTimer_Thread(LPVOID param)
{
	for ( ; ; )
	{
		WaitForSingleObject(hEventTimer, INFINITE);

		hospac_win_int(intnoTimer);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
