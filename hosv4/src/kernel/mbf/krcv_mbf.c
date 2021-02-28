/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���b�Z�[�W�o�b�t�@                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "hoslib.h"


static UB kernel_rch_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
								T_KERNEL_MBFCB_RAM *mbfcb_ram);	/* �P�L�����N�^��M */



/* ���b�Z�[�W�o�b�t�@����̎�M(�J�[�l�������֐�) */
ER_UINT kernel_rcv_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram,	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(RAM��) */
		VP                       msg)			/* ��M���b�Z�[�W���i�[����擪�Ԓn */
{
	T_MKNL_TCB *mtcb;
	UINT       msgsz;
	UINT       tmpsz;
	INT        i;

	/* ���b�Z�[�W���݃`�F�b�N */
	if ( mbfcb_ram->smsgcnt == 0 )	/* ���b�Z�[�W�������ꍇ */
	{
		/* ���M�҂��^�X�N�`�F�b�N */
		mtcb = mknl_ref_qhd(&mbfcb_ram->sndque);	/* ��M�҂��s��̐擪�^�X�N���Q�� */
		if ( mtcb != NULL )
		{
			T_KERNEL_MBFDAT *mbfdat;
			
			/* ���M�f�[�^�󂯎�� */
			mbfdat = (T_KERNEL_MBFDAT *)mtcb->data;
			__hos_bcopy(msg, mbfdat->msg, mbfdat->msgsz);	/* �f�[�^�R�s�[ */

			/* ���M�^�X�N�̑҂������� */
			mknl_rmv_que(mtcb);				/* �҂��s�񂩂�폜 */
			mknl_rmv_tmout(mtcb);			/* �^�C���A�E�g�҂��s�񂩂�폜 */
			mknl_wup_tsk(mtcb, E_OK);		/* �^�X�N�̑҂����� */

			return (ER_UINT)mbfdat->msgsz;	/* ���튮�� */
		}

		return E_TMOUT;		/* �^�C���A�E�g */
	}
	
	/* �T�C�Y��M */
	msgsz = 0;
	for ( i = 0; i < sizeof(UINT); i++ )
	{
		/* ��ʂ��珇��8bit���ǂݏo�� */
		msgsz <<= 8;
		msgsz += kernel_rch_mbf(mbfcb_rom, mbfcb_ram);
	}
	
	/* �f�[�^��M */
	tmpsz = (UINT)mbfcb_rom->mbfsz - mbfcb_ram->head;	/* �܂�Ԃ��_�܂ł̃T�C�Y���Z�o */
	if ( tmpsz >= msgsz )	/* �܂�Ԃ����� */
	{
		__hos_bcopy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, msgsz);		/* �f�[�^�R�s�[ */
	}
	else
	{
		__hos_bcopy(msg, (UB *)mbfcb_rom->mbf + mbfcb_ram->head, tmpsz);		/* �܂�Ԃ��_�܂ŃR�s�[ */
		__hos_bcopy((UB *)msg + tmpsz, (UB *)mbfcb_rom->mbf, msgsz - tmpsz);	/* �c���擪����R�s�[ */
	}

	/* �|�C���^�X�V */
	mbfcb_ram->head += msgsz;
	if ( mbfcb_ram->head >= mbfcb_rom->mbfsz )
	{
		mbfcb_ram->head -= (UINT)mbfcb_rom->mbfsz;
	}

	/* �o�b�t�@�󂫃T�C�Y�X�V */
	mbfcb_ram->fmbfsz += msgsz;

	/* ���M���f�N�������g */
	mbfcb_ram->smsgcnt--;

	return (ER_UINT)msgsz;	/* ���M�T�C�Y��Ԃ� */
}


/* �P�L�����N�^��M */
UB kernel_rch_mbf(
		const T_KERNEL_MBFCB_ROM *mbfcb_rom,	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(ROM��) */
		T_KERNEL_MBFCB_RAM       *mbfcb_ram)	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(RAM��) */
{
	UB chr;

	/* �P�L�����N�^��M */
	chr = *((UB *)mbfcb_rom->mbf + mbfcb_ram->head);

	/* �|�C���^�X�V */
	if ( mbfcb_ram->head + 1 < (UINT)mbfcb_rom->mbfsz )
	{
		mbfcb_ram->head++;
	}
	else
	{
		mbfcb_ram->head = 0;
	}

	/* �o�b�t�@�󂫃T�C�Y�X�V */
	mbfcb_ram->fmbfsz++;
	
	return chr;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
