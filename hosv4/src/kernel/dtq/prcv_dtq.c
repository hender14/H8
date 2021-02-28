/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �f�[�^�L���[                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* �f�[�^�L���[����̎�M(�|�[�����O) */
ER prcv_dtq(
		ID     dtqid,	/* ��M�Ώۂ̃f�[�^�L���[��ID�ԍ� */
		VP_INT *p_data)	/* �f�[�^�L���[�����M�����f�[�^ */
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;
	ER  ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;	/* ID�s�� */
	}
#endif
	
		/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR 
	if ( p_data == NULL )
	{
		return E_PAR;	/* �p�����[�^�[�s�� */
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

	dtqcb_rom = dtqcb_ram->dtqcb_rom;

	if ( dtqcb_ram->datacnt == 0 )
	{
		/* �f�[�^�L���[����Ȃ� */
		if ( mknl_ref_qhd(&dtqcb_ram->sndque) != NULL )
		{
			/* ���M�҂��^�X�N������ΊJ�� */
			mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);	/* �҂��s��擪����^�X�N���o�� */
			mknl_rmv_que(mtcb);							/* �҂��s�񂩂�폜 */
			mknl_rmv_tmout(mtcb);						/* �^�C���A�E�g���� */
			*p_data = mtcb->data;						/* �f�[�^�����o�� */
			mknl_wup_tsk(mtcb, E_OK);					/* �^�X�N�̑҂����� */
			
			mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
			mknl_exe_tex();		/* ��O�����̎��s */
			
			ercd = E_OK;
		}
		else
		{
			/* �f�[�^�L���[����ő��M�҂��^�X�N��������΃^�C���A�E�g */
			ercd = E_TMOUT;
		}
	}
	else
	{
		/* �f�[�^�L���[����f�[�^�����o�� */
		*p_data = dtqcb_rom->dtq[dtqcb_ram->head];
		dtqcb_ram->head++;
		if ( dtqcb_ram->head >= dtqcb_rom->dtqcnt )
		{
			dtqcb_ram->head = 0;
		}
		
		/* ���M�҂��^�X�N������Ȃ�J�� */
		mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);
		if ( mtcb!= NULL )
		{
			UINT tail;
			
			/* �f�[�^�L���[�����Ƀf�[�^���i�[ */
			tail = dtqcb_ram->head + dtqcb_ram->datacnt - 1;
			if ( tail >= dtqcb_rom->dtqcnt )
			{
				tail -= dtqcb_rom->dtqcnt;
			}
			dtqcb_rom->dtq[tail] = mtcb->data;
			
			mknl_rmv_que(mtcb);			/* �҂��s�񂩂�폜 */
			mknl_rmv_tmout(mtcb);		/* �^�C���A�E�g���� */
			mknl_wup_tsk(mtcb, E_OK);	/* �^�X�N�̑҂����� */
			
			mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
			mknl_exe_tex();		/* ��O�����̎��s */
		}
		else
		{
			dtqcb_ram->datacnt--;
		}
		
		ercd = E_OK;
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
