/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �f�[�^�L���[                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"
#include "knl_sys.h"



/* �f�[�^�L���[�̏�ԎQ�� */
ER ref_dtq(
		ID     dtqid,		/* ��ԎQ�ƑΏۂ̃f�[�^�L���[��ID�ԍ� */
		T_RDTQ *pk_rdtq)	/* �f�[�^�L���[��Ԃ�Ԃ��p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;
	}
#endif

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rdtq == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* �I�u�W�F�N�g�̑��݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif
	
	/* �f�[�^�L���[�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ��擾 */
	mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb == NULL )
	{
		pk_rdtq->stskid = TSK_NONE;		/* �҂��^�X�N�Ȃ� */
	}
	else
	{
	/* �^�X�NID������ */
		pk_rdtq->stskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* �C�x���g�t���O�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ��擾 */
	mtcb = mknl_ref_qhd(&dtqcb_ram->rcvque);	/* �҂��s��擪����^�X�N���o�� */
	if ( mtcb == NULL )
	{
		pk_rdtq->rtskid = TSK_NONE;		/* �҂��^�X�N�Ȃ� */
	}
	else
	{
		/* �^�X�NID������ */
		pk_rdtq->rtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* �f�[�^���̎擾 */
	pk_rdtq->sdtqcnt = dtqcb_ram->datacnt;

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
