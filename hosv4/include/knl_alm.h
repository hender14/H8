/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ �A���[���n���h��                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_alm_h__
#define __HOS_V4__knl_alm_h__



#include "knl_hos.h"
#include "knl_tim.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_ALMID	TMIN_ALMID			/* �A���[���n���h��ID�̍ŏ��l */
#define KERNEL_TMAX_ALMID	(KERNEL_TMIN_ALMID + kernel_almcb_cnt - 1)
												/* �A���[���n���h��ID�̍ő�l */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �A���[���n���h���R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_almcb_rom
{
	ATR    almatr;		/* �A���[���n���h������ */
	VP_INT exinf;		/* �A���[���n���h���̊g����� */
	FP     almhdr;		/* �A���[���n���h���̋N���Ԓn */
} T_KERNEL_ALMCB_ROM;

/* �A���[���n���h���R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_almcb_ram
{
	T_KERNEL_TIM timobj;		/* �^�C�}�I�u�W�F�N�g���p�� */
	RELTIM       lefttim;		/* �A���[���n���h���̂����ɋN�����鎞���܂ł̎��� */
	const T_KERNEL_ALMCB_ROM *almcb_rom;	/* �A���[���n���h���R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_ALMCB_RAM;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �A���[���n���h�� */
extern       T_KERNEL_ALMCB_RAM *kernel_almcb_ram_tbl[];	/* �A���[���n���h���R���g���[���u���b�N�e�[�u�� */
extern const INT kernel_almcb_cnt;							/* �A���[���n���h���R���g���[���u���b�N�� */

#define KERNEL_ALMID_TO_ALMCB_RAM(almid)	(kernel_almcb_ram_tbl[(almid) - KERNEL_TMIN_ALMID])
															/* �A���[���n���h��ID����ALMCB RAM�A�h���X���擾 */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �A���[���n���h�� */
void    kernel_ini_alm(void);								/* �A���[���n���h���̏����� */
void    kernel_alm_hdr(T_KERNEL_TIM *timobj, RELTIM tic);	/* �A���[���n���h���̃^�C�}�n���h�� */
ER      sta_alm(ID almid, RELTIM almtim);					/* �A���[���n���h���̓���J�n */
ER      stp_alm(ID almid);									/* �A���[���n���h���̓����~ */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_alm_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
