/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ �����n���h��                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_cyc_h__
#define __HOS_V4__knl_cyc_h__



#include "knl_hos.h"
#include "knl_tim.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_CYCID	TMIN_CYCID			/* �����n���h��ID�̍ŏ��l */
#define KERNEL_TMAX_CYCID	(KERNEL_TMIN_CYCID + kernel_cyccb_cnt - 1)
												/* �����n���h��ID�̍ő�l */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �����n���h���R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_cyccb_rom
{
	ATR    cycatr;		/* �����n���h������ */
	VP_INT exinf;		/* �����n���h���̊g����� */
	FP     cychdr;		/* �����n���h���̋N���Ԓn */
	RELTIM cyctim;		/* �����n���h���̋N������ */
/*	RELTIM cycphs;	*/	/* �����n���h���̋N���ʑ�(���g�p) */
} T_KERNEL_CYCCB_ROM, T_CCYC;

/* �����n���h���R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_cyccb_ram
{
	T_KERNEL_TIM timobj;		/* �^�C�}�I�u�W�F�N�g���p�� */
	RELTIM       lefttim;		/* �����n���h�������ɋN�����鎞���܂ł̎��� */
	const T_KERNEL_CYCCB_ROM *cyccb_rom;	/* �����n���h���R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_CYCCB_RAM;

/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �����n���h�� */
extern       T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[];	/* �����n���h���R���g���[���u���b�N�e�[�u�� */
extern const INT kernel_cyccb_cnt;							/* �����n���h���R���g���[���u���b�N�� */

#define KERNEL_CYCID_TO_CYCCB_RAM(cycid)	(kernel_cyccb_ram_tbl[(cycid) - KERNEL_TMIN_CYCID])
															/* �����n���h��ID����CYCCB RAM�A�h���X���擾 */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �����n���h�� */
void    kernel_ini_cyc(void);								/* �����n���h���̏����� */
void    kernel_cyc_hdr(T_KERNEL_TIM *timobj, RELTIM tic);	/* �����n���h���̃^�C�}�n���h�� */
ER      sta_cyc(ID cycid);									/* �����n���h���̓���J�n */
ER      stp_cyc(ID cycid);									/* �����n���h���̓����~ */
ER      cre_cyc(ID cycid, const T_CCYC *pk_ccyc);			/* �����n���h���̐��� */
ER_ID   acre_cyc(const T_CCYC *pk_ccyc);					/* �����n���h���̐���(ID�ԍ��������t��) */
ER      kernel_cre_cyc(ID cycid, const T_CCYC *pk_ccyc);	/* �����n���h������(�J�[�l������) */
ER      del_cyc(ID cycid);	/* �����n���h���̍폜 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_cyc_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
