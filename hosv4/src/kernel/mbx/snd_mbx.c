/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���[���{�b�N�X                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* ���[���{�b�N�X�ւ̑��M */
ER snd_mbx(
		ID    mbxid,		/* ���M�Ώۂ̃��[���{�b�N�X��ID�ԍ� */
		T_MSG *pk_msg)		/* ���[���{�b�N�X�֑��M���郁�b�Z�[�W�p�P�b�g�̐擪�Ԓn */
{
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_KERNEL_MBXCB_RAM       *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	T_MSG      *msg;
	PRI        msgpri;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < KERNEL_TMIN_MBXID || mbxid > KERNEL_TMAX_MBXID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	mbxcb_ram = KERNEL_MBXID_TO_MBXCB_RAM(mbxid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbxcb_ram == NULL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_NOEXS;
	}
#endif

	mbxcb_rom = mbxcb_ram->mbxcb_rom;

	/* ���b�Z�[�W�D��x�擾 */
	if ( mbxcb_rom->mbxatr & TA_MPRI )	/* �D��x���Ȃ� */
	{
		msgpri = (PRI)(((T_MSG_PRI*)pk_msg)->msgpri - TMIN_MPRI);

		/* �D��x�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
		if ( msgpri < 0	|| msgpri > mbxcb_rom->maxmpri - TMIN_MPRI )
		{
			mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
			return E_PAR;
		}
#endif
	}
	else	/* �D��x�Ȃ�(FIFO��)�Ȃ� */
	{
		msgpri = 0;
	}

	mtcb = mknl_ref_qhd(&mbxcb_ram->que);		/* �҂��s��擪�^�X�N���擾 */
	if ( mtcb != NULL )
	{
		/* �҂��^�X�N������ΊJ�� */
		mtcb->data = (VP_INT)pk_msg;			/* ���b�Z�[�W��n�� */
		mknl_rmv_que(mtcb);						/* ���[���{�b�N�X�̑҂��s�񂩂�폜 */
		mknl_rmv_tmout(mtcb);					/* �^�C���A�E�g�҂��s�񂩂�폜 */
		mknl_wup_tsk(mtcb, E_OK);				/* �^�X�N�̑҂����� */
		
		mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();		/* ��O�����̎��s */
	}
	else
	{
		/* �҂��^�X�N���Ȃ���΃��[���{�b�N�X�ɐڑ� */
		if ( mbxcb_rom->mprihd[msgpri] == NULL )
		{
			/* �ŏ��̂P�̓o�^ */
			mbxcb_rom->mprihd[msgpri] = pk_msg;
			pk_msg->next              = pk_msg;
		}
		else
		{
			/* �����ɒǉ� */
			msg                       = mbxcb_rom->mprihd[msgpri];
			pk_msg->next              = msg->next;
			msg->next                 = pk_msg;
			mbxcb_rom->mprihd[msgpri] = pk_msg;
		}
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;	/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
