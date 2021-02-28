/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �C�x���g�t���O                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* �C�x���g�t���O�̃Z�b�g */
ER set_flg(
		ID     flgid,		/* �Z�b�g�Ώۂ̃C�x���g�t���O��ID�ԍ� */
		FLGPTN setptn)		/* �Z�b�g����r�b�g�p�^�[�� */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
	T_KERNEL_FLGINF          *pk_flginf;
	T_MKNL_TCB *mtcb;
	T_MKNL_TCB *mtcb_next;
	BOOL       wupflg = FALSE;	/* �N���t���O */

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < KERNEL_TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* �s��ID�ԍ� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_NOEXS;
	}
#endif

	flgcb_rom = flgcb_ram->flgcb_rom;

	/* �t���O�̃Z�b�g */
	flgcb_ram->flgptn = (FLGPTN)(flgcb_ram->flgptn | setptn);

	/* �҂��^�X�N������΋N���`�F�b�N */
	mtcb = mknl_ref_qhd(&flgcb_ram->que);
	while ( mtcb != NULL )
	{
		mtcb_next = mknl_ref_nxt(&flgcb_ram->que, mtcb);	/* ���̑҂��^�X�N���擾 */
		
		/* �t���O�`�F�b�N */
		pk_flginf = (T_KERNEL_FLGINF *)mtcb->data;
		if ( kernel_chk_flg(flgcb_ram, pk_flginf) )
		{
			/* �N�������𖞂����Ă���Ȃ� */
			pk_flginf->waiptn = flgcb_ram->flgptn;	/* ���݂̃t���O�p�^�[�����i�[ */
			if ( flgcb_rom->flgatr & TA_CLR )
			{
				flgcb_ram->flgptn = 0;				/* �N���A����������΃N���A */
			}

			/* �҂����� */
			mknl_rmv_que(mtcb);			/* �҂��s�񂩂�O�� */
			mknl_rmv_tmout(mtcb);		/* �^�C���A�E�g���� */
			mknl_wup_tsk(mtcb, E_OK);	/* �҂��^�X�N�̋N�� */
			wupflg = TRUE;
		}
		mtcb = mtcb_next;	/* ���̃^�X�N�ɐi�߂� */
	}

	/* �N�����s�����^�X�N������Ȃ�f�B�X�p�b�`���s�� */
	if ( wupflg )
	{
		mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();		/* ��O�����̎��s */
	}
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
	
	return E_OK;	/* ����I�� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
