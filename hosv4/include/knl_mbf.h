/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���b�Z�[�W�o�b�t�@                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mbf_h__
#define __HOS_V4__knl_mbf_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_MBFID	TMIN_MBFID			/* ���b�Z�[�W�o�b�t�@ID�̍ŏ��l */
#define KERNEL_TMAX_MBFID	(KERNEL_TMIN_MBFID + kernel_mbfcb_cnt - 1)
												/* ���b�Z�[�W�o�b�t�@ID�̍ő�l */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* ���b�Z�[�W�o�b�t�@������� */
typedef struct t_cmbf
{
	ATR  mbfatr;		/* ���b�Z�[�W�o�b�t�@���� */
	UINT maxmsz;		/* ���b�Z�[�W�̍ő�T�C�Y(�o�C�g��) */
	SIZE mbfsz;			/* ���b�Z�[�W�o�b�t�@�̈�̃T�C�Y(�o�C�g��) */
    VP   mbf;			/* ���b�Z�[�W�o�b�t�@�̈�̐擪�Ԓn */
} T_CMBF;

/* ���b�Z�[�W�o�b�t�@��ԏ�� */
typedef struct t_rmbf
{
	ID   stskid;		/* ���b�Z�[�W�o�b�t�@�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ� */
	ID   rtskid;		/* ���b�Z�[�W�o�b�t�@�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ� */
	UINT smsgcnt;		/* ���b�Z�[�W�o�b�t�@�ɓ����Ă��郁�b�Z�[�W�̐� */
	SIZE fmbfsz;		/* ���b�Z�[�W�o�b�t�@�̈�̋󂫗̈�̃T�C�Y(�o�C�g���A�Œ���̊Ǘ��̈������) */
} T_RMBF;


/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_mbfcb_rom
{
	ATR  mbfatr;		/* ���b�Z�[�W�o�b�t�@���� */
	UINT maxmsz;		/* ���b�Z�[�W�̍ő�T�C�Y(�o�C�g��) */
	SIZE mbfsz;			/* ���b�Z�[�W�o�b�t�@�̈�̃T�C�Y(�o�C�g��) */
    VP   mbf;			/* ���b�Z�[�W�o�b�t�@�̈�̐擪�Ԓn */
} T_KERNEL_MBFCB_ROM;

/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_mbfcb_ram
{
	T_MKNL_QUE sndque;	/* ���b�Z�[�W�o�b�t�@���M�҂��^�X�N�L���[ */
	T_MKNL_QUE rcvque;	/* ���b�Z�[�W�o�b�t�@��M�҂��^�X�N�L���[ */
	SIZE       head;	/* �擪���b�Z�[�W�̈ʒu */
	SIZE       fmbfsz;	/* ���b�Z�[�W�o�b�t�@�̈�̋󂫃T�C�Y */
	UINT       smsgcnt;	/* ���b�Z�[�W�o�b�t�@�ɓ����Ă��郁�b�Z�[�W�̐� */
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_MBFCB_RAM;

/* ���M���b�Z�[�W�f�[�^��� */
typedef struct t_kernel_mbfdat
{
	UINT msgsz;			/* ���b�Z�[�W�T�C�Y */
	VP   msg;			/* ���b�Z�[�W�̐擪�Ԓn */
} T_KERNEL_MBFDAT;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* ���b�Z�[�W�o�b�t�@�Ǘ� */
extern       T_KERNEL_MBFCB_RAM *kernel_mbfcb_ram_tbl[];	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N�e�[�u��(RAM��) */
extern const INT kernel_mbfcb_cnt;							/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N�� */

/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N�ϊ��}�N�� */
#define KERNEL_MBFID_TO_MBFCB_RAM(mbfid)	(kernel_mbfcb_ram_tbl[(mbfid) - KERNEL_TMIN_MBFID])
															/* ���b�Z�[�W�o�b�t�@ID����MBFCB RAM�A�h���X���擾 */



/* ------------------------------------------ */
/*                 �}�N����`                 */
/* ------------------------------------------ */

/* �������̈�̃T�C�Y */
#define TSZ_MBF(msgcnt, msgsz)		((SIZE)((UINT)(msgcnt) * ((UINT)(msgsz) + 2) + 1))



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ���b�Z�[�W�o�b�t�@ */
void    kernel_ini_mbf(void);								/* ���b�Z�[�W�o�b�t�@�̏����� */
ER      cre_mbf(ID mbfid, const T_CMBF *pk_cmbf);			/* ���b�Z�[�W�o�b�t�@�̐��� */
ER_ID   acre_mbf(const T_CMBF *pk_cmbf);					/* ���b�Z�[�W�o�b�t�@�̐���(ID�ԍ��������t��) */
ER      kernel_cre_mbf(ID mbfid, const T_CMBF *pk_cmbf);	/* ���b�Z�[�W�o�b�t�@�̐���(�J�[�l�������֐�) */
ER      del_mbf(ID mbfid);									/* ���b�Z�[�W�o�b�t�@�̍폜 */
ER      snd_mbf(ID mbfid, VP msg, UINT msgsz);				/* ���b�Z�[�W�o�b�t�@�ւ̑��M */
ER      psnd_mbf(ID mbfid, VP msg, UINT msgsz);				/* ���b�Z�[�W�o�b�t�@�ւ̑��M(�|�[�����O) */
ER      tsnd_mbf(ID mbfid, VP msg, UINT msgsz, TMO tmout);	/* ���b�Z�[�W�o�b�t�@�ւ̑��M(�^�C���A�E�g����) */
ER      kernel_snd_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
			T_KERNEL_MBFCB_RAM *mbfcb_ram, VP msg, UINT msgsz);	/* ���b�Z�[�W�o�b�t�@�ւ̑��M(�J�[�l�������֐�) */
ER_UINT rcv_mbf(ID mbfid, VP msg);							/* ���b�Z�[�W�o�b�t�@����̎�M */
ER_UINT prcv_mbf(ID mbfid, VP msg);							/* ���b�Z�[�W�o�b�t�@����̎�M(�|�[�����O) */
ER_UINT trcv_mbf(ID mbfid, VP msg,  TMO tmout);				/* ���b�Z�[�W�o�b�t�@����̎�M(�^�C���A�E�g����) */
ER_UINT kernel_rcv_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
			T_KERNEL_MBFCB_RAM *mbfcb_ram, VP msg);			/* ���b�Z�[�W�o�b�t�@����̎�M(�J�[�l�������֐�) */
ER      ref_mbf(ID mbfid, T_RMBF *pk_rmbf);					/* ���b�Z�[�W�o�b�t�@�̏�ԎQ�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mbf_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
