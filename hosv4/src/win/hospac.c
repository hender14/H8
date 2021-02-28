/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (Windows�p)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <stdlib.h>
#include "hospac.h"
#include <tchar.h>


/* �^�X�N��� */
typedef struct t_TaskInfo
{
	VP_INT exinf;			/* �^�X�N�̎��s���p�����[�^ */
	FP     task;			/* �^�X�N�̋N���Ԓn */
} T_TaskInfo;



DWORD WINAPI TaskEntry(LPVOID param);	/* �X���b�h�̊J�n�֐� */
void  HookPrimaryThread(void);			/* �v���C�}���X���b�h�̃t�b�N */

HANDLE hospac_hSem  = NULL;				/* �V�X�e���̔r������p�Z�}�t�H */
BOOL   hospac_blInt = FALSE;			/* ���荞�ݏ������t���O */

static DWORD  hPrimaryThreadId;			/* �v���C�}���X���b�hID */
static HANDLE hThreadDelete = NULL;		/* �폜����X���b�h�n���h�� */



/* �V�X�e���̏����� */
void hospac_ini_sys(void)
{
	/* �v���C�}���X���b�hID�̕ۑ� */
	hPrimaryThreadId = GetCurrentThreadId();

	/* ���荞�݋֎~�Ɍ����Ă�Z�}�t�H�̍쐬 */
	hospac_hSem = CreateSemaphore(NULL, 0, 1, NULL);
}


/* ���荞�݋��� */
void hospac_ena_int(void)
{
	if ( !hospac_blInt )
	{
		ReleaseSemaphore(hospac_hSem, 1, NULL);
	}
}


/* ���荞�݋֎~ */
void hospac_dis_int(void)
{
	if ( !hospac_blInt )
	{
		WaitForSingleObject(hospac_hSem, INFINITE);
	}
}


/* ���s�R���e�L�X�g�̍쐬 */
void hospac_cre_ctx(
		T_HOSPAC_CTXINF *pk_ctxinf,		/* �R���e�L�X�g���쐬����A�h���X */
		VP_INT          exinf,			/* �^�X�N�̎��s���p�����[�^ */
		FP              task,			/* �^�X�N�̋N���Ԓn */
		SIZE            stksz,			/* �X�^�b�N�̈�̃T�C�Y */
		VP              stk)			/* �X�^�b�N�̈�̐擪�Ԓn */
{
	T_TaskInfo *pInfo;

	/* �^�X�N�����i�[ */
	pInfo = (T_TaskInfo *)GlobalAlloc(GMEM_FIXED, sizeof(T_TaskInfo));
	pInfo->task  = task;
	pInfo->exinf = exinf;
	
	/* ���� */
	pk_ctxinf->blIntSuspend = FALSE;
	pk_ctxinf->hThread = CreateThread(NULL, 0, TaskEntry, (LPVOID)pInfo,
									CREATE_SUSPENDED, &pk_ctxinf->dwThreadId);
}


/* �X���b�h�̊J�n�֐� */
DWORD WINAPI TaskEntry(LPVOID param)
{
	T_TaskInfo Info;

	Info = *(T_TaskInfo *)param;

	GlobalFree((HGLOBAL)param);

	Info.task(Info.exinf);

	return 0;
}


/* ���s�R���e�L�X�g�̍폜 */
void hospac_del_ctx(T_HOSPAC_CTXINF *pk_ctxinf)
{
	if ( GetCurrentThreadId() != pk_ctxinf->dwThreadId )
	{
		/* ���s���X���b�h�łȂ���Α��폜 */
		TerminateThread(pk_ctxinf->hThread, 0);
	}
	else
	{
		/* ���s���X���b�h�Ȃ�폜��\�� */
		hThreadDelete = pk_ctxinf->hThread;
	}
}


/* ���s�R���e�L�X�g�̐ؑ� */
void hospac_swi_ctx(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		/* ���݂̃R���e�L�X�g�̕ۑ��� */
		T_HOSPAC_CTXINF *pk_nxt_ctxinf)		/* �V���Ɏ��s����R���e�L�X�g */
{
	DWORD dwCount;

	if ( hospac_blInt )
	{
		return;
	}

	/* �X���b�h���قȂ�ΐ؂�ւ��� */
	if ( pk_nxt_ctxinf != pk_pre_ctxinf )
	{
		/* �؂�ւ��Ώۂ��T�X�y���h���ł��邱�Ƃ��m�F */
		for ( ; ; )
		{
			/* �T�X�y���h�J�E���^�𓾂�ׂɃT�X�y���h�����Ă݂� */
			dwCount = SuspendThread(pk_nxt_ctxinf->hThread);
			ResumeThread(pk_nxt_ctxinf->hThread);
			
			/* �J�E���^��0�łȂ���΃T�X�y���h���Ă��� */
			if ( dwCount > 0 )
			{
				break;
			}
			
			/* �T�X�y���h�����܂ő҂� */
			Sleep(1);
		}
		
		/* �؂�ւ���̃X���b�h���N���� */
		ResumeThread(pk_nxt_ctxinf->hThread);
		
		/* �Z�}�t�H��ԋp */
		if ( pk_nxt_ctxinf->blIntSuspend )
		{
			pk_nxt_ctxinf->blIntSuspend = FALSE;
			ReleaseSemaphore(hospac_hSem, 1, NULL);
		}
		
		/* �v���C�}���X���b�hI�̃t�b�N */
		if ( hPrimaryThreadId == GetCurrentThreadId() )
		{
			HookPrimaryThread();
		}

		/* �������g���T�X�y���h������ */
		SuspendThread(GetCurrentThread());
	}
	
	/* �폜�\��̃X���b�h������΍폜 */
	if ( hThreadDelete != NULL )
	{
		TerminateThread(hThreadDelete, 0);
		CloseHandle(hThreadDelete);
		hThreadDelete = NULL;
	}
}


/* �A�C�h�����̏��� */
void hospac_idle(void)
{
	/* �}�C�R���Ȃ�ȏ���d�̓��[�h�ɐ؂�ւ���Ȃǉ\ */
	
	/* ���̃v���Z�X�Ɏ��s�^�C�~���O��^���� */
	Sleep(1);
}


/* �v���C�}���X���b�h�̃t�b�N */
void  HookPrimaryThread(void)
{
	/* �_�C�A���O��\�� */
	MessageBox(NULL, _T("OK�������ƏI�����܂�"), _T("Hyper Operationg System V4 for Win32"), MB_OK);

	/* �I�� */
	ExitProcess(0);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
