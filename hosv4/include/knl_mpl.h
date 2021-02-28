/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ �ϒ��������v�[��                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mpl_h__
#define __HOS_V4__knl_mpl_h__


#include "knl_hos.h"
#include "knl_hep.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_MPLID	TMIN_MPLID			/* �ϒ��������v�[��ID�̍ŏ��l */
#define KERNEL_TMAX_MPLID	(KERNEL_TMIN_MPLID + kernel_mplcb_cnt - 1)
												/* �ϒ��������v�[��ID�̍ő�l */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �ϒ��������v�[��������� */
typedef struct t_cmpl
{
	ATR  mplatr;		/* �ϒ��������v�[������ */
	UINT mplsz;			/* �ϒ��������v�[���̈�̃T�C�Y(�o�C�g��) */
	VP   mpl;			/* �ϒ��������v�[���̈�̐擪�Ԓn */
} T_CMPL;

/* �ϒ��������v�[����� */
typedef struct t_rmpl
{
	ID   wtskid;		/* �ϒ��������v�[���̑҂��s��̐擪�̃^�X�N��ID�ԍ� */
	SIZE fmplsz;		/* �ϒ��������v�[���̋󂫗̈�̍��v�T�C�Y(�o�C�g��) */
	UINT fblksz;		/* �����Ɋl���\�ȍő僁�����u���b�N�T�C�Y(�o�C�g��) */
} T_RMPL;


/* �ϒ��������v�[���R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_mplcb_rom
{
	ATR  mplatr;		/* �ϒ��������v�[������ */
	UINT mplsz;			/* �ϒ��������v�[���̈�̃T�C�Y(�o�C�g��) */
	VP   mpl;			/* �ϒ��������v�[���̈�̐擪�Ԓn */
} T_KERNEL_MPLCB_ROM;


/* �ϒ��������v�[���R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_mplcb_ram
{
	T_MKNL_QUE     que;	/* �ϒ��������v�[���҂��^�X�N�L���[ */
	T_KERNEL_HEPCB hep;	/* �������q�[�v */
	const T_KERNEL_MPLCB_ROM *mplcb_rom;	/* �ϒ��������v�[���R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_MPLCB_RAM;


/* �������҂����\���� */
typedef struct t_kernel_mplinf
{
	UINT blksz;			/* �l�����郁�����u���b�N�̃T�C�Y(�o�C�g��) */
	VP   *p_blk;		/* �l�������������u���b�N�̐擪�Ԓn */
} T_KERNEL_MPLINF;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �ϒ��������v�[���Ǘ� */
extern       T_KERNEL_MPLCB_RAM *kernel_mplcb_ram_tbl[];	/* �ϒ��������v�[���R���g���[���u���b�N�e�[�u��(RAM��) */
extern const INT kernel_mplcb_cnt;							/* �ϒ��������v�[���R���g���[���u���b�N�� */


/* ---------------------------------- */
/*            �}�N����`              */
/* ---------------------------------- */

/* �ϒ��������v�[���R���g���[���u���b�N�ϊ��}�N�� */
#define KERNEL_MPLID_TO_MPLCB_RAM(mplid)	(kernel_mplcb_ram_tbl[(mplid) - KERNEL_TMIN_MPLID])
															/* �ϒ��������v�[��ID����MPLCB RAM�A�h���X���擾 */


/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �ϒ��������v�[�� */
void    kernel_ini_mpl(void);								/* �ϒ��������v�[���̏����� */
ER      cre_mpl(ID mplid, const T_CMPL *pk_cmpl);			/* �ϒ��������v�[���̐��� */
ER_ID   acre_mpl(const T_CMPL *pk_cmpl);					/* �ϒ��������v�[���̐���(ID�ԍ��������t��) */
ER      kernel_cre_mpl(ID mplid, const T_CMPL *pk_cmpl);	/* �ϒ��������v�[���̐���(�J�[�l�������֐�) */
ER      del_mpl(ID mplid);									/* �ϒ��������v�[���̍폜 */
ER      get_mpl(ID mplid, UINT blksz, VP *p_blk);			/* �ϒ��������u���b�N�̊l�� */
ER      pget_mpl(ID mplid, UINT blksz, VP *p_blk);			/* �ϒ��������u���b�N�̊l��(�|�[�����O) */
ER      tget_mpl(ID mplid, UINT blksz, VP *p_blk, TMO tmout);
															/* �ϒ��������u���b�N�̊l��(�^�C���A�E�g����) */
ER      rel_mpl(ID mplid, VP blk);							/* �ϒ��������u���b�N�̕ԋp */
ER      ref_mpl(ID mplid, T_RMPL *pk_rmpl);					/* �ϒ��������u���b�N�̏�ԎQ�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mpl_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
