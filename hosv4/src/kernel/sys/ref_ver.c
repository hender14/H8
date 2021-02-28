/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* �o�[�W�����ԍ��̎Q�� */
ER ref_ver(
	T_RVER *pk_rver)	/* �o�[�W��������Ԃ��p�P�b�g�ւ̃|�C���^ */
{
	pk_rver->maker   = TKERNEL_MAKER;	/* �J�[�l���̃��[�J�[�R�[�h */
	pk_rver->prid    = TKERNEL_PRID;	/* �J�[�l���̎��ʔԍ� */
	pk_rver->spver   = TKERNEL_SPVER;	/* ITRON�d�l�̃o�[�W������� */
	pk_rver->prver   = TKERNEL_PRVER;	/* �J�[�l���̃o�[�W�����ԍ� */
	pk_rver->prno[0] = 0;				/* �J�[�l�����i�̊Ǘ����(1) */
	pk_rver->prno[1] = 0;				/* �J�[�l�����i�̊Ǘ����(2) */
	pk_rver->prno[2] = 0;				/* �J�[�l�����i�̊Ǘ����(3) */
	pk_rver->prno[3] = 0;				/* �J�[�l�����i�̊Ǘ����(4) */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
