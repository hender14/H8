/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N��O�����@�\                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"


/* �^�X�N��O�����̗v�� */
ER ras_tex(
		ID     tskid,		/* �v���Ώۂ̃^�X�N��ID�ԍ� */
		TEXPTN rasptn)		/* �v������^�X�N��O�����̃^�X�N��O�v�� */
{
	T_KERNEL_TCB_RAM   *tcb_ram;
	T_KERNEL_TEXCB_RAM *texcb;

	/* ID �͈̓`�F�b�N */
	if ( tskid == TSK_SELF )
	{
		/* �R���e�L�X�g�`�F�b�N */
#ifdef HOS_ERCHK_E_ID
		if ( sns_ctx() )
		{
			return E_ID;	/* �s��ID�ԍ� */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
		texcb = tcb_ram->texcb;
		
		mknl_loc_sys();	/* �V�X�e���̃��b�N */
	}
	else
	{
		/* ID �͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_ID
		if ( tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID )
		{
			return  E_ID;	/* �s��ID�ԍ� */
		}
#endif
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		mknl_loc_sys();	/* �V�X�e���̃��b�N */
	
		/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
			return E_NOEXS;		/* �I�u�W�F�N�g������ */
		}
#endif
		
		texcb = tcb_ram->texcb;
		
		/* �I�u�W�F�N�g��ԃ`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
		if ( texcb == NULL || mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
		{
			mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
			return E_OBJ;		/* �I�u�W�F�N�g��ԕs�� */
		}
#endif
	}

	/* ��O�����̗v�� */
	texcb->rasptn = (TEXPTN)(texcb->rasptn | rasptn);
	mknl_ras_tex(&tcb_ram->mtcb);

	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
