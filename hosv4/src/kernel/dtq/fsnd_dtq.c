/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �f�[�^�L���[                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* �f�[�^�L���[�ւ̋������M */
ER fsnd_dtq(
		ID     dtqid,	/* ���M�Ώۂ̃f�[�^�L���[��ID�ԍ� */
		VP_INT data)	/* �f�[�^�L���[�֑��M����f�[�^ */
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;
	UINT tail;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;
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
	}
	else
	{
		/* �҂��^�X�N��������΃f�[�^�L���[�Ɋi�[ */
		dtqcb_rom = dtqcb_ram->dtqcb_rom;
		if ( dtqcb_ram->datacnt >= dtqcb_rom->dtqcnt )
		{
			/* �f�[�^�L���[�T�C�Y�m�F */
#ifdef HOS_ERCHK_E_ILUSE
			if ( dtqcb_rom->dtqcnt == 0 )
			{
				mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
				return E_ILUSE;	/* �T�[�r�X�R�[���s���g�p */
			}
#endif

			/* �L���[�擪�̃f�[�^�𖕏����đ��M */
			dtqcb_rom->dtq[dtqcb_ram->head] = data;
			dtqcb_ram->head++;
			if ( dtqcb_ram->head >= dtqcb_rom->dtqcnt )
			{
				dtqcb_ram->head -= dtqcb_rom->dtqcnt;
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
		}
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
