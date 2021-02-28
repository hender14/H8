/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���b�Z�[�W�o�b�t�@                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "hoslib.h"


static void kernel_sch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
						T_KERNEL_MBFCB_RAM *mbfcb_ram, UB chr);	/* �P�L�����N�^���M */



/* ���b�Z�[�W�o�b�t�@�ւ̑��M */
ER kernel_snd_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(RAM��) */
		VP                       msg,			/* ���M���b�Z�[�W�̐擪�Ԓn */
		UINT                     msgsz)			/* ���M���b�Z�[�W�̃T�C�Y(�o�C�g��) */
{
	T_MKNL_TCB *mtcb;
	SIZE       fresz;
	SIZE       tail;
	INT        i;

	/* ���M�҂��^�X�N���`�F�b�N */
	mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* ���M�҂��s��̐擪�^�X�N���Q�� */
	if ( mtcb != NULL )
	{
		return E_TMOUT;		/* ���M�҂������ɂ���΃^�C���A�E�g */
	}

	/* ��M�҂��^�X�N�`�F�b�N */
	mtcb = mknl_ref_qhd(&mbfcb_ram->rcvque);	/* ��M�҂��s��̐擪�^�X�N���Q�� */
	if ( mtcb != NULL )
	{
		/* ��M�^�X�N�̑҂������� */
		__hos_bcopy((VP)mtcb->data, msg, msgsz);		/* �f�[�^�R�s�[ */
		mknl_rmv_que(mtcb);						/* �҂��s�񂩂�폜 */
		mknl_rmv_tmout(mtcb);					/* �^�C���A�E�g�҂��s�񂩂�폜 */
		mknl_wup_tsk(mtcb, (ER_UINT)msgsz);		/* �^�X�N�̑҂����� */

		return E_OK;	/* ���튮�� */
	}

	/* �󂫃T�C�Y�`�F�b�N */
	if ( mbfcb_ram->fmbfsz < msgsz + sizeof(UINT) )
	{
		return E_TMOUT;		/* �^�C���A�E�g */
	}
	
	/* �T�C�Y���M */
	for ( i = sizeof(UINT) - 1; i >= 0; i-- )
	{
		/* ��ʂ��珇��8bit�P�ʂŏ������� */
		kernel_sch_mbf(mbfcb_rom, mbfcb_ram, (UB)((msgsz >> (i * 8)) & 0xff));
	}

	/* �����ʒu�Z�o */
	tail = mbfcb_ram->head - mbfcb_ram->fmbfsz;
	if ( mbfcb_ram->head < mbfcb_ram->fmbfsz )
	{
		tail += mbfcb_rom->mbfsz;
	}

	/* �f�[�^���M */
	fresz = (UINT)mbfcb_rom->mbfsz - tail;	/* �o�b�t�@�܂�Ԃ��܂ł̋󂫃T�C�Y�Z�o */
	if ( fresz >= msgsz )					/* �܂�Ԃ��s�v������ */
	{
		__hos_bcopy((UB *)mbfcb_rom->mbf + tail, msg, msgsz);				/* �f�[�^�R�s�[ */
	}
	else
	{
		__hos_bcopy((UB *)mbfcb_rom->mbf + tail, msg, fresz);				/* �܂�Ԃ��_�܂ŃR�s�[ */
		__hos_bcopy((UB *)mbfcb_rom->mbf, (UB *)msg + fresz, msgsz - fresz);	/* �c���擪����R�s�[ */
	}

	/* �󂫃T�C�Y�X�V */
	mbfcb_ram->fmbfsz -= msgsz;

	/* ���M���C���N�������g */
	mbfcb_ram->smsgcnt++;

	return E_OK;
}


/* �P�L�����N�^���M */
void kernel_sch_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(RAM��) */
		UB                       chr)			/* ���M����L�����N�^ */
{
	SIZE tail;

	/* �����ʒu�Z�o */
	tail = mbfcb_ram->head - mbfcb_ram->fmbfsz;
	if ( mbfcb_ram->head < mbfcb_ram->fmbfsz )
	{
		tail += mbfcb_rom->mbfsz;
	}

	/* �P�L�����N�^���M */
	*((UB *)mbfcb_rom->mbf + tail) = chr;

	/* �o�b�t�@�󂫃T�C�Y�X�V */
	mbfcb_ram->fmbfsz--;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
