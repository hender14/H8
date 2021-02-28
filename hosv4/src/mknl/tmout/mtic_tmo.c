/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�C���A�E�g�L���[�Ǘ�                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �O���[�o���ϐ� */
T_MKNL_TCB *mknl_timout_head;		/* �^�C���A�E�g�L���[�̐擪 */



/* �^�C���A�E�g�Ƀ^�C���e�B�b�N���� */
void mknl_tic_tmout(
		RELTIM tictim)		/* �ǉ�����^�C���e�B�b�N */
{
	register T_MKNL_TCB *mtcb;

	/* ���[�J���ɃR�s�[ */
	mtcb = mknl_timout_head;

	/* �^�C���A�E�g�L���[����Ȃ烊�^�[�� */
	if ( mtcb == NULL )
	{
		return;
	}

	/* �^�C���A�E�g�L���[�̏��� */
	for ( ; ; )
	{
		/* �^�C���A�E�g�ɒB���Ȃ��Ȃ� */
		if ( tictim < mtcb->diftim )
		{
			mtcb->diftim -= tictim;		/* �^�C���A�E�g���Ԃ����Z */
			break;
		}
		
		tictim -= mtcb->diftim;			/* �^�C���e�B�b�N�����Z */
		
		mknl_wup_tsk(mtcb, E_TMOUT);	/* �^�C���A�E�g�N�� */
		mknl_exe_dsp();					/* �x���f�B�X�p�b�`�\����s�� */
		
		/* �L���[����O�� */
		if ( mtcb->tm_next == mtcb )	/* �Ō�̂P�Ȃ� */
		{
			/* �L���[����ɂ��� */
			mtcb->tm_prev = NULL;
			mtcb          = NULL;
			break;
		}
		else
		{
			/* �L���[������O�� */
			mtcb->tm_next->tm_prev = mtcb->tm_prev;
			mtcb->tm_prev->tm_next = mtcb->tm_next;
			mtcb->tm_prev = NULL;
			mtcb = mtcb->tm_next;
		}

		/* �����ň�x�A���d���荞�݂̋@���^���� */
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		mknl_loc_sys();		/* �V�X�e���̃��b�N */
	}
	
	/* �������ɏ����߂� */
	mknl_timout_head = mtcb;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
