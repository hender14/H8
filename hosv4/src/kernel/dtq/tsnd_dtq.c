/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �f�[�^�L���[                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* �f�[�^�L���[�ւ̑��M(�^�C���A�E�g����) */
ER      tsnd_dtq(
		ID     dtqid,	/* ���M�Ώۂ̃f�[�^�L���[��ID�ԍ� */
		VP_INT data,	/* �f�[�^�L���[�֑��M����f�[�^ */
		TMO    tmout)	/* �^�C���A�E�g�w�� */
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;
	UINT tail;
	ER   ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;
	}
#endif

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR 
	if ( tmout != TMO_FEVR && tmout < 0 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �R���e�L�X�g�`�F�b�N */
#ifdef HOS_ERCHK_E_CTX
	if (  tmout != TMO_POL && mknl_sns_wai() )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_CTX;	/* �R���e�L�X�g�s�� */
	}
#endif

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* �I�u�W�F�N�g�̑��݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	if ( mknl_ref_qhd(&dtqcb_ram->rcvque) != NULL )
	{
		/* ��M�҂��^�X�N������ΊJ�� */
		mtcb = mknl_ref_qhd(&dtqcb_ram->rcvque);	/* �҂��s��擪����^�X�N���o�� */
		mknl_rmv_que(mtcb);							/* �҂��s�񂩂�폜 */
		mknl_rmv_tmout(mtcb);						/* �^�C���A�E�g���� */
		mtcb->data = data;							/* �f�[�^���i�[ */
		mknl_wup_tsk(mtcb, E_OK);					/* �^�X�N�̑҂����� */
		
		mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();		/* ��O�����̎��s */
		
		ercd = E_OK;
	}
	else
	{
		/* �҂��^�X�N��������΃f�[�^�L���[�Ɋi�[ */
		dtqcb_rom = dtqcb_ram->dtqcb_rom;
		if ( dtqcb_ram->datacnt >= dtqcb_rom->dtqcnt )
		{
			/* �f�[�^�L���[����t�Ȃ� */
			if ( tmout == TMO_POL )
			{
				/* �|�[�����O�Ȃ瑦���^�C���A�E�g */
				ercd = E_TMOUT;
			}
			else
			{
				/* ���M�҂��ɓ��� */
				mtcb = mknl_get_run_tsk();		/* ���݂̃^�X�N���擾 */
				mtcb->data = data;				/* �f�[�^�ۑ� */
				mknl_wai_tsk(mtcb, TTW_SDTQ);	/* �҂���Ԃɐݒ� */
				mknl_add_que(&dtqcb_ram->sndque, mtcb, dtqcb_rom->dtqatr);	/* �҂��s��ɒǉ� */
				
				/* �����҂��łȂ���� */
				if ( tmout != TMO_FEVR )
				{
					mknl_add_tmout(mtcb, (RELTIM)tmout);	/* �^�C���A�E�g�L���[�ɒǉ� */
				}
				
				ercd = (ER)mknl_exe_dsp();	/* �^�X�N�f�B�X�p�b�`�̎��s */
				mknl_exe_tex();				/* ��O�����̎��s */
			}
		}
		else
		{
			/* �f�[�^�L���[�����Ƀf�[�^���i�[ */
			tail = dtqcb_ram->head + dtqcb_ram->datacnt;
			if ( tail >= dtqcb_rom->dtqcnt )
			{
				tail -= dtqcb_rom->dtqcnt;
			}
			dtqcb_rom->dtq[tail] = data;
			dtqcb_ram->datacnt++;
			
			ercd = E_OK;
		}
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
