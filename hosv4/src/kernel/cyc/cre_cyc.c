/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �����n���h��                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"


/* �^�X�N�̐��� */
ER cre_cyc(
		ID           cycid,		/* �����Ώۂ̎����n���h����ID�ԍ� */
		const T_CCYC *pk_ccyc)	/* �����n���h������������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ER ercd;

	/* ID �͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < KERNEL_TMIN_CYCID || cycid > KERNEL_TMAX_CYCID )
	{
		return E_ID;	/* �s��ID�ԍ� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �^�X�N���o�^�\���`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_CYCID_TO_CYCCB_RAM(cycid) != NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_OBJ;	/* ���ɓo�^�ς� */
	}
#endif
	
	/* �^�X�N�̐��� */
	ercd = kernel_cre_cyc(cycid, pk_ccyc);

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
