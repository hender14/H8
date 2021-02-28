/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �V�X�e��                                                              */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_hos.h"
#include "knl_int.h"
#include "knl_tim.h"



/* HOS �J�[�l������J�n */
ER sta_hos(void)
{
	/* �R���t�B�M�����[�^�[�ϐ��̏����� */
	kernel_cfg_init();

	/* �J�[�l���̏����� */
	mknl_ini_sys();		/* �ʃJ�[�l���V�X�e���̏����� */
	
	/* �[���I�Ɋ��荞�݃n���h���ƌ��Ȃ� */
	kernel_int_cnt = 1;

	/* �X�^�[�g�A�b�v�p�R���e�L�X�g�Ɉڍs */
	mknl_sta_startup();
	
	/* ������ */
	kernel_ini_tim();	/* ���ԊǗ��@�\�̏����� */
	kernel_cfg_start();	/* �R���t�B�M�����[�V�����̏����� */
	
	/* ���荞�݃l�X�g�񐔃N���A */
	kernel_int_cnt = 0;

	/* �J�[�l�������Ԃֈڍs */
	mknl_ext_startup();

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
