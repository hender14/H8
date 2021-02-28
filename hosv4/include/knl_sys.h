/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ �V�X�e����ԊǗ�                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2007 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_sys_h__
#define __HOS_V4__knl_sys_h__


#include "knl_hos.h"
#include "knl_tsk.h"


/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* �o�[�W������� */
#define TKERNEL_MAKER	0x0008				/* ���[�J�[�R�[�h(�l) */
#define TKERNEL_PRID	0x0000				/* �J�[�l���̎��ʔԍ�(����) */
#define TKERNEL_SPVER	0x5401				/* ITRON�d�l�̃o�[�W����(��ITRON Ver 4.01) */
#define TKERNEL_PRVER	0x0102				/* �J�[�l���̃o�[�W�����ԍ� (HOS-V4 Ver 1.02) */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �o�[�W������� */
typedef struct t_rver
{
	UH    maker;		/* �J�[�l���̃��[�J�[�R�[�h */
	UH    prid;			/* �J�[�l���̎��ʔԍ� */
	UH    spver;		/* ITRON�d�l�̃o�[�W������� */
	UH    prver;		/* �J�[�l���̃o�[�W�����ԍ� */
	UH    prno[4];		/* �J�[�l�����i�̊Ǘ���� */
} T_RVER;



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �V�X�e����ԊǗ��@�\ */
ER      rot_rdq(PRI tskpri);						/* �^�X�N�D�揇�ʂ̉�] */
#define irot_rdq	rot_rdq							/* �^�X�N�D�揇�ʂ̉�](��^�X�N�R���e�L�X�g�p�}�N��) */
ER      get_tid(ID *p_tskid);						/* ���s��ԃ^�X�NID�̎Q�� */
#define iget_tid	get_tid							/* ���s��ԃ^�X�NID�̎Q��(��^�X�N�R���e�L�X�g�p�}�N��) */
ID      kernel_get_tid(T_KERNEL_TCB_RAM *tcb_ram);	/* �^�X�NID�̎擾(�J�[�l�������֐�) */
ER      loc_cpu(void);								/* CPU���b�N��Ԃւ̈ڍs */
#define iloc_cpu	loc_cpu							/* CPU���b�N��Ԃւ̈ڍs(��^�X�N�R���e�L�X�g�p�}�N��) */
ER      unl_cpu(void);								/* CPU���b�N��Ԃ̉��� */
#define iunl_cpu	unl_cpu							/* CPU���b�N��Ԃ̉���(��^�X�N�R���e�L�X�g�p�}�N��)  */
ER      dis_dsp(void);								/* �f�B�X�p�b�`�̋֎~ */
ER      ena_dsp(void);								/* �f�B�X�p�b�`�̋��� */
BOOL    sns_ctx(void);								/* �R���e�L�X�g�̎Q�� */
BOOL    sns_loc(void);								/* CPU���b�N��Ԃ̎Q�� */
BOOL    sns_dsp(void);								/* �f�B�X�p�b�`�֎~��Ԃ̎Q�� */
BOOL    sns_dpn(void);								/* �f�B�X�p�b�`�ۗ���Ԃ̎Q�� */

/* �V�X�e���\���Ǘ��@�\ */
ER      ref_ver(T_RVER *pk_rver);					/* �o�[�W�����ԍ��̎Q�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_sys_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2007 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
