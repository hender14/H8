/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ �f�[�^�L���[                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_dtq_h__
#define __HOS_V4__knl_dtq_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_DTQID	TMIN_DTQID			/* �f�[�^�L���[ID�̍ŏ��l */
#define KERNEL_TMAX_DTQID	(KERNEL_TMIN_DTQID + kernel_dtqcb_cnt - 1)
												/* �f�[�^�L���[ID�̍ő�l */



/* ------------------------------------------ */
/*                 �}�N����`                 */
/* ------------------------------------------ */

/* �������̈�̃T�C�Y */
#define TSZ_DTQ(dtqcnt)		((SIZE)((UINT)(dtqcnt) * sizeof(VP_INT)))



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �f�[�^�L���[������� */
typedef struct t_cdtq
{
	ATR    dtqatr;		/* �f�[�^�L���[���� */
	UINT   dtqcnt;		/* �f�[�^�L���[�̈�̗e��(�f�[�^�̌�) */
	VP     dtq;			/* �f�[�^�L���[�̈�̐擪�Ԓn */
} T_CDTQ;

/* �f�[�^�L���[��� */
typedef struct t_rdtq
{
	ID   stskid;		/* �f�[�^�L���[�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ� */
	ID   rtskid;		/* �f�[�^�L���[�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ� */
	UINT sdtqcnt;		/* �f�[�^�L���[�ɓ����Ă���f�[�^�̐� */
} T_RDTQ;


/* �f�[�^�L���[�R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_dtqcb_rom
{
	ATR    dtqatr;		/* �f�[�^�L���[���� */
	UINT   dtqcnt;		/* �f�[�^�L���[�̈�̗e��(�f�[�^�̌�) */
	VP_INT *dtq;		/* �f�[�^�L���[�̈�̐擪�Ԓn */
} T_KERNEL_DTQCB_ROM;

/* �f�[�^�L���[�R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_dtqcb_ram
{
	T_MKNL_QUE sndque;	/* �f�[�^�L���[���M�҂��^�X�N�L���[ */
	T_MKNL_QUE rcvque;	/* �f�[�^�L���[���M�҂��^�X�N�L���[ */
	UINT       head;	/* �f�[�^�̐擪 */
	UINT       datacnt;	/* �f�[�^�̌� */
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;	/* �f�[�^�L���[�R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_DTQCB_RAM;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �f�[�^�L���[�Ǘ� */
extern       T_KERNEL_DTQCB_RAM *kernel_dtqcb_ram_tbl[];	/* �f�[�^�L���[�R���g���[���u���b�N�e�[�u��(RAM��) */
extern const INT kernel_dtqcb_cnt;							/* �f�[�^�L���[�R���g���[���u���b�N�� */

/* �f�[�^�L���[�R���g���[���u���b�N�ϊ��}�N�� */
#define KERNEL_DTQID_TO_DTQCB_RAM(dtqid)	(kernel_dtqcb_ram_tbl[(dtqid) - KERNEL_TMIN_DTQID])
															/* �f�[�^�L���[ID����DTQCB RAM�A�h���X���擾 */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */
#ifdef __cplusplus
extern "C" {
#endif

/* �f�[�^�L���[ */
#define kernel_ini_dtq()									/* �f�[�^�L���[�̏����� */
ER      cre_dtq(ID dtqid, const T_CDTQ *pk_cdtq);			/* �f�[�^�L���[�̐��� */
ER_ID   acre_dtq(const T_CDTQ *pk_cdtq);					/* �f�[�^�L���[�̐���(ID�ԍ��������t��) */
ER      kernel_cre_dtq(ID dtqid, const T_CDTQ *pk_cdtq);	/* �f�[�^�L���[�̐���(�J�[�l�������֐�) */
ER      del_dtq(ID dtqid);									/* �f�[�^�L���[�̍폜 */
ER      snd_dtq(ID dtqid, VP_INT data);						/* �f�[�^�L���[�ւ̑��M */
ER      psnd_dtq(ID dtqid, VP_INT data);					/* �f�[�^�L���[�ւ̑��M(�|�[�����O) */
#define ipsnd_dtq	psnd_dtq								/* �f�[�^�L���[�ւ̑��M(�|�[�����O ��^�X�N�R���e�L�X�g�p�}�N��) */
ER      tsnd_dtq(ID dtqid, VP_INT data, TMO tmout);			/* �f�[�^�L���[�ւ̑��M(�^�C���A�E�g����) */
ER      fsnd_dtq(ID dtqid, VP_INT data);					/* �f�[�^�L���[�ւ̋������M */
#define ifsnd_dtq	fsnd_dtq								/* �f�[�^�L���[�ւ̋������M(��^�X�N�R���e�L�X�g�p�}�N��) */
ER      rcv_dtq(ID dtqid, VP_INT *p_data);					/* �f�[�^�L���[����̎�M */
ER      prcv_dtq(ID dtqid, VP_INT *p_data);					/* �f�[�^�L���[����̎�M(�|�[�����O) */
ER      trcv_dtq(ID dtqid, VP_INT *p_data, TMO tmout);		/* �f�[�^�L���[����̎�M(�^�C���A�E�g����) */
ER      ref_dtq(ID dtqid, T_RDTQ *pk_rdtq);					/* �f�[�^�L���[�̏�ԎQ�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_dtq_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
