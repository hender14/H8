/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"
#include "dsp_hok.h"



/* �^�X�N�f�B�X�p�b�`�̎��s */
ER_UINT mknl_exe_dsp(void)
{
	T_HOSPAC_CTXINF *ctxinf_top;
	T_HOSPAC_CTXINF *ctxinf_run;
	T_MKNL_TCB *mtcb_top;
	T_MKNL_TCB *mtcb_run;

	/* �R���e�L�X�g�`�F�b�N */
	if ( mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP | MKNL_TSS_DINT) )
	{
		/* �f�B�X�p�b�`���s�\��ԂŖ�����Εۗ����� */
		mknl_ctx_stat |= MKNL_TSS_DDLY;	/* �f�B�X�p�b�`�x���t���O���Z�b�g */
		return E_OK;
	}

	/* �ō��D��x�̎��s�\�^�X�N��T�� */
	mtcb_top = mknl_srh_top();

	mtcb_run = mknl_run_mtcb;	/* ���݂̃^�X�N�����[�J���ɑޔ� */

	/* ���s���^�X�N�������Ȃ牽�����Ȃ�(�A�C�h������A�C�h�����܂ށj */
	if ( mtcb_top == mtcb_run )
	{
		if ( mtcb_run == NULL )
		{
			return E_OK;
		}
		return mtcb_run->ercd;
	}

	/* �A�C�h���^�X�N���s���łȂ����`�F�b�N */
	if ( mtcb_run == NULL )
	{
		/* �A�C�h���Ȃ�A�C�h���R���e�L�X�g��ݒ� */
		ctxinf_run = &mknl_idlctx;
	}
	else
	{
		/* ���s���̃R���e�L�X�g��ݒ� */
		ctxinf_run = &mtcb_run->ctxinf;
	}

	/* ���Ɏ��s����^�X�N�����邩�ǂ����`�F�b�N */
	if ( mtcb_top == NULL )
	{
		/* ���s�悪������΃A�C�h���R���e�L�X�g��ݒ� */
		mknl_run_mtcb = NULL;
		ctxinf_top    = &mknl_idlctx;
	}
	else
	{
		/* ���s��̃^�X�N�����s���^�X�N�Ƃ��ēo�^ */
		mknl_run_mtcb     = mtcb_top;
		mtcb_top->tskstat = TTS_RDY;
		
		/* ���s��̃R���e�L�X�g��ݒ� */
		ctxinf_top = &mtcb_top->ctxinf;
	}

	/* �^�X�N�R���e�L�X�g�X�C�b�`���s */
	hospac_swi_ctx(ctxinf_run, ctxinf_top);

	_HOS_TSW_HOK();		/* �R���e�L�X�g�X�C�b�`�̃t�b�N */

	if ( mtcb_run == NULL )
	{
		return E_OK;
	}

	return mtcb_run->ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
