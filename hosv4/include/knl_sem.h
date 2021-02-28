/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ �Z�}�t�H                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_sem_h__
#define __HOS_V4__knl_sem_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_SEMID	TMIN_SEMID			/* �Z�}�t�HID�̍ŏ��l */
#define KERNEL_TMAX_SEMID	(KERNEL_TMIN_SEMID + kernel_semcb_cnt - 1)
												/* �Z�}�t�HID�̍ő�l */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �Z�}�t�H������� */
typedef struct t_csem
{
	ATR  sematr;		/* �Z�}�t�H���� */
	UINT isemcnt;		/* �Z�}�t�H�������̏����l */
	UINT maxsem;		/* �Z�}�t�H�̍ő厑���� */
} T_CSEM;

/* �Z�}�t�H��ԏ�� */
typedef struct t_rsem
{
	ID   wtskid;		/* �Z�}�t�H�̑҂��s��̐擪�̃^�X�N��ID�ԍ� */
	UINT semcnt;		/* �Z�}�t�H�̌��݂̎����� */
} T_RSEM;


/* �Z�}�t�H�R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_semcb_rom
{
	ATR  sematr;		/* �Z�}�t�H���� */
	UINT isemcnt;		/* �Z�}�t�H�������̏����l */
	UINT maxsem;		/* �Z�}�t�H�̍ő厑���� */
} T_KERNEL_SEMCB_ROM;

/* �Z�}�t�H�R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_semcb_ram
{
	T_MKNL_QUE que;		/* �Z�}�t�H�҂��^�X�N�L���[ */
	UINT       semcnt;	/* �Z�}�t�H�̎����� */
	const T_KERNEL_SEMCB_ROM *semcb_rom;	/* �Z�}�t�H�R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_SEMCB_RAM;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �Z�}�t�H�Ǘ� */
extern       T_KERNEL_SEMCB_RAM *kernel_semcb_ram_tbl[];	/* �Z�}�t�H�R���g���[���u���b�N�e�[�u��(RAM��) */
extern const INT kernel_semcb_cnt;							/* �Z�}�t�H�R���g���[���u���b�N�� */

/* �Z�}�t�H�R���g���[���u���b�N�ϊ��}�N�� */
#define KERNEL_SEMID_TO_SEMCB_RAM(semid)	(kernel_semcb_ram_tbl[(semid) - KERNEL_TMIN_SEMID])
															/* �Z�}�t�HID����SEMCB RAM�A�h���X���擾 */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �Z�}�t�H */
void    kernel_ini_sem(void);								/* �Z�}�t�H�̏����� */
ER      cre_sem(ID semid, const T_CSEM *pk_csem);			/* �Z�}�t�H�̐��� */
ER_ID   acre_sem(const T_CSEM *pk_csem);					/* �Z�}�t�H�̐���(ID�ԍ��������t��) */
ER      kernel_cre_sem(ID semid, const T_CSEM *pk_csem);	/* �Z�}�t�H�̐���(�J�[�l�������֐�) */
ER      del_sem(ID semid);									/* �Z�}�t�H�̍폜 */
ER      sig_sem(ID semid);									/* �Z�}�t�H�����̕ԋp */
#define isig_sem sig_sem									/* �Z�}�t�H�����̕ԋp(��^�X�N�R���e�L�X�g�p�}�N��) */
ER      wai_sem(ID semid);									/* �Z�}�t�H�����̊l�� */
ER      pol_sem(ID semid);									/* �Z�}�t�H�����̊l��(�|�[�����O) */
ER      twai_sem(ID semid, TMO tmout);						/* �Z�}�t�H�����̊l��(�^�C���A�E�g����) */
ER      ref_sem(ID semid, T_RSEM *pk_rsem);					/* �Z�}�t�H�̏�ԎQ�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_sem_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
