/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �����n���h��                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"


/* �����n���h���̐���(ID�ԍ��������t��) */
ER_ID acre_cyc(
		const T_CCYC *pk_ccyc)	/* �����n���h������������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ID cycid;
	ER ercd;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ��ID�̌��� */
	for ( cycid = KERNEL_TMAX_CYCID; cycid >= KERNEL_TMIN_CYCID; cycid-- )
	{
		if ( KERNEL_CYCID_TO_CYCCB_RAM(cycid) == NULL )
		{
			break;
		}
	}
	if ( cycid < KERNEL_TMIN_CYCID )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_NOID;		/* ID�ԍ��s�� */
	}
	
	/* �����n���h���̐��� */
	ercd = kernel_cre_cyc(cycid, pk_ccyc);

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	if ( ercd != E_OK )
	{
		return (ER_ID)ercd;	/* �G���[���� */
	}

	return (ER_ID)cycid;		/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
