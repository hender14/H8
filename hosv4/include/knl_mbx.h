/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ ���[���{�b�N�X                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mbx_h__
#define __HOS_V4__knl_mbx_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_MBXID	TMIN_MBXID			/* ���[���{�b�N�XID�̍ŏ��l */
#define KERNEL_TMAX_MBXID	(KERNEL_TMIN_MBXID + kernel_mbxcb_cnt - 1)
												/* ���[���{�b�N�XID�̍ő�l */


/* �D��x�͈̔� */
#define TMIN_MPRI			1					/* ���b�Z�[�W�D��x�̍ŏ��l */
#define TMAX_MPRI			32767				/* ���b�Z�[�W�D��x�̍ő�l */

/* �K�v�ȃ������̈�̃T�C�Y */
#define TSZ_MPRIHD(maxmpri)	(sizeof(T_MSG *) * ((maxmpri) - TMIN_MPRI + 1))
												/* �D��x�ʃL���[�w�b�_�̃������̈�̃T�C�Y */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* ���[���{�b�N�X�̃��b�Z�[�W�w�b�_ */
typedef struct t_msg
{
	struct t_msg *next;		/* ���̃��b�Z�[�W�ւ̃|�C���^ */
} T_MSG;

/* ���[���{�b�N�X�̗D��x�t�����b�Z�[�W�w�b�_ */
typedef struct t_msg_pri
{
	T_MSG msg;				/* ���b�Z�[�W�w�b�_ */
	PRI   msgpri;			/* ���b�Z�[�W�D��x */
} T_MSG_PRI;


/* ���[���{�b�N�X������� */
typedef struct t_cmbx
{
	ATR   mbxatr;		/* ���[���{�b�N�X���� */
	PRI   maxmpri;		/* ���M����郁�b�Z�[�W�̗D��x�̍ő�l */
	VP    mprihd;		/* �D��x�ʂ̃��b�Z�[�W�L���[�w�b�_�̈�̐擪�Ԓn */
} T_CMBX;

/* ���[���{�b�N�X��� */
typedef struct t_rmbx
{
	ID    wtskid;		/* ���[���{�b�N�X�̑҂��s��̐擪�̃^�X�N��ID�ԍ� */
	T_MSG *pk_msg;		/* ���b�Z�[�W�L���[�̐擪�̃��b�Z�[�W�p�P�b�g�̐擪�Ԓn */
} T_RMBX;


/* ���[���{�b�N�X�R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_mbxcb_rom
{
	ATR   mbxatr;		/* ���[���{�b�N�X���� */
	PRI   maxmpri;		/* ���M����郁�b�Z�[�W�̗D��x�̍ő�l */
	T_MSG **mprihd;		/* �D��x�ʂ̃��b�Z�[�W�L���[�w�b�_�̈�̐擪�Ԓn */
} T_KERNEL_MBXCB_ROM;

/* ���[���{�b�N�X�R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_mbxcb_ram
{
	T_MKNL_QUE que;							/* ���[���{�b�N�X�҂��^�X�N�L���[ */
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;	/* ���[���{�b�N�X�R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_MBXCB_RAM;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* ���[���{�b�N�X�Ǘ� */
extern       T_KERNEL_MBXCB_RAM *kernel_mbxcb_ram_tbl[];	/* ���[���{�b�N�X�R���g���[���u���b�N�e�[�u��(RAM��) */
extern const INT kernel_mbxcb_cnt;							/* ���[���{�b�N�X�R���g���[���u���b�N�� */

#define KERNEL_MBXID_TO_MBXCB_RAM(mbxid)	(kernel_mbxcb_ram_tbl[(mbxid) - KERNEL_TMIN_MBXID])
															/* ���[���{�b�N�XID����MBXCB RAM�A�h���X���擾 */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ���[���{�b�N�X */
#define kernel_ini_mbx()									/* ���[���{�b�N�X�̏����� */
ER      cre_mbx(ID semid, const T_CMBX *pk_cmbx);			/* �Z�}�t�H�̐��� */
ER_ID   acre_mbx(const T_CMBX *pk_cmbx);					/* �Z�}�t�H�̐���(ID�ԍ��������t��) */
ER      kernel_cre_mbx(ID mbxid, const T_CMBX *pk_cmbx);	/* �Z�}�t�H�̐���(�J�[�l�������֐�) */
ER      del_mbx(ID semid);									/* �Z�}�t�H�̍폜 */
ER      snd_mbx(ID mbxid, T_MSG *pk_msg);					/* ���[���{�b�N�X�ւ̑��M */
ER      rcv_mbx(ID mbxid, T_MSG **ppk_msg);					/* ���[���{�b�N�X����̎�M */
ER      prcv_mbx(ID mbxid, T_MSG **ppk_msg);				/* ���[���{�b�N�X����̎�M(�|�[�����O) */
ER      trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout);		/* ���[���{�b�N�X����̎�M(�^�C���A�E�g����) */
ER      ref_mbx(ID mbxid, T_RMBX *pk_rmbx);					/* ���[���{�b�N�X�̏�ԎQ�� */

#ifdef __cplusplus
}
#endif



#endif	/*__HOS_V4__knl_mbx_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
