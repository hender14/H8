/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �f�[�^�L���[                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* �f�[�^�L���[�̐���(ID�ԍ��������t��) */
ER_ID acre_dtq(
		const T_CDTQ *pk_cdtq)	/* �f�[�^�L���[����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ID dtqid;
	ER ercd;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ���p�\��ID�̌��� */
	for ( dtqid = KERNEL_TMAX_DTQID; dtqid >= KERNEL_TMIN_DTQID; dtqid-- )
	{
		if ( KERNEL_DTQID_TO_DTQCB_RAM(dtqid) == NULL )
		{
			break;
		}
	}
	
	/* ID�ԍ��s���`�F�b�N */
#ifdef HOS_ERCHK_E_NOID
	if ( dtqid < KERNEL_TMIN_DTQID )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOID;	/* ID�ԍ��s�� */
	}
#endif

	/* �f�[�^�L���[�̐��� */
	ercd = kernel_cre_dtq(dtqid, pk_cdtq);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return (ER_ID)dtqid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
