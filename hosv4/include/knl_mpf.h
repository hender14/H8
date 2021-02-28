/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ �Œ蒷�������v�[��                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mpf_h__
#define __HOS_V4__knl_mpf_h__


#include "knl_hos.h"
#include "knl_mem.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_MPFID	TMIN_MPFID			/* �Œ蒷�������v�[��ID�̍ŏ��l */
#define KERNEL_TMAX_MPFID	(KERNEL_TMIN_MPFID + kernel_mpfcb_cnt - 1)
												/* �Œ蒷�������v�[��ID�̍ő�l */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �Œ蒷�������v�[��������� */
typedef struct t_cmpf
{
	ATR  mpfatr;		/* �Œ蒷�������v�[������ */
	UINT blkcnt;		/* �l���ł��郁�����u���b�N��(��) */
	UINT blksz;			/* �������u���b�N�̃T�C�Y(�o�C�g��) */
	VP   mpf;			/* �Œ蒷�������v�[���̈�̐擪�Ԓn */
} T_CMPF;

/* �Œ蒷�������v�[����� */
typedef struct t_rmpf
{
	ID   wtskid;		/* �Œ蒷�������v�[���̑҂��s��̐擪�̃^�X�N��ID�ԍ� */
	UINT fblkcnt;		/* �Œ蒷�������v�[���̋󂫃������u���b�N��(��) */
} T_RMPF;


/* �Œ蒷�������v�[���R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_mpfcb_rom
{
	ATR  mpfatr;		/* �Œ蒷�������v�[������ */
	UINT blkcnt;		/* �l���ł��郁�����u���b�N��(��) */
	UINT blksz;			/* �������u���b�N�̃T�C�Y(�o�C�g��) */
	VP   mpf;			/* �Œ蒷�������v�[���̈�̐擪�Ԓn */
} T_KERNEL_MPFCB_ROM;


/* �Œ蒷�������v�[���R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_mpfcb_ram
{
	T_MKNL_QUE que;		/* �Œ蒷�������v�[���҂��^�X�N�L���[ */
	VP         free;	/* �󂫃u���b�N�ւ̃|�C���^ */
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;	/* �Œ蒷�������v�[���R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_MPFCB_RAM;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �Œ蒷�������v�[���Ǘ� */
extern       T_KERNEL_MPFCB_RAM *kernel_mpfcb_ram_tbl[];	/* �Œ蒷�������v�[���R���g���[���u���b�N�e�[�u��(RAM��) */
extern const INT kernel_mpfcb_cnt;							/* �Œ蒷�������v�[���R���g���[���u���b�N�� */

/* ---------------------------------- */
/*            �}�N����`              */
/* ---------------------------------- */
/* �Œ蒷�������v�[���R���g���[���u���b�N�ϊ��}�N�� */
#define KERNEL_MPFID_TO_MPFCB_RAM(mpfid)	(kernel_mpfcb_ram_tbl[(mpfid) - KERNEL_TMIN_MPFID])
															/* �Œ蒷�������v�[��ID����MPFCB RAM�A�h���X���擾 */
/* �������v�[���̈�̃T�C�Y */
#define TSZ_MPF(blkcnt,blksz)	((SIZE)((blkcnt) * TSZ_ALIGNED(blksz)))



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �Œ蒷�������v�[�� */
void    kernel_ini_mpf(void);								/* �Œ蒷�������v�[���̏����� */
ER      cre_mpf(ID mpfid, const T_CMPF *pk_cmpf);			/* �Œ蒷�������v�[���̐��� */
ER_ID   acre_mpf(const T_CMPF *pk_cmpf);					/* �Œ蒷�������v�[���̐���(ID�ԍ��������t��) */
ER      kernel_cre_mpf(ID mpfid, const T_CMPF *pk_cmpf);	/* �Œ蒷�������v�[���̐���(�J�[�l�������֐�) */
ER      del_mpf(ID mpfid);									/* �Œ蒷�������v�[���̍폜 */
ER      get_mpf(ID mpfid, VP *p_blk);						/* �Œ蒷�������u���b�N�̊l�� */
ER      pget_mpf(ID mpfid, VP *p_blk);						/* �Œ蒷�������u���b�N�̊l��(�|�[�����O) */
ER      tget_mpf(ID mpfid, VP *p_blk, TMO tmout);			/* �Œ蒷�������u���b�N�̊l��(�^�C���A�E�g����) */
ER      rel_mpf(ID mpfid, VP blk);							/* �Œ蒷�������u���b�N�̕ԋp */
ER      ref_mpf(ID mpfid, T_RMPF *pk_rmpf);					/* �Œ蒷�������u���b�N�̏�ԎQ�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mpf_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
