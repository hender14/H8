/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���ˑ�����`�w�b�_ �C�x���g�t���O                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_flg_h__
#define __HOS_V4__knl_flg_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  �萔��`                  */
/* ------------------------------------------ */

/* ID�͈̔� */
#define KERNEL_TMIN_FLGID	TMIN_FLGID			/* �C�x���g�t���OID�̍ŏ��l */
#define KERNEL_TMAX_FLGID	(KERNEL_TMIN_FLGID + kernel_flgcb_cnt - 1)
												/* �C�x���g�t���OID�̍ő�l */

/* �r�b�g�p�^�[���̃r�b�g�� */
#define TBIT_FLGPTN			16					/* �C�x���g�t���O�̃r�b�g�� */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �C�x���g�t���O������� */
typedef struct t_cflg
{
	ATR    flgatr;		/* �C�x���g�t���O���� */
	FLGPTN iflgptn;		/* �C�x���g�t���O�̃r�b�g�p�^�[���̏����l */
} T_CFLG;

/* �C�x���g�t���O��� */
typedef struct t_rflg
{
	ID     wtskid;		/* �C�x���g�t���O�̑҂��s��̐擪�̃^�X�N��ID�ԍ� */
	FLGPTN flgptn;		/* �C�x���g�t���O�̌��݂̃r�b�g�p�^�[�� */
} T_RFLG;


/* �C�x���g�t���O�R���g���[���u���b�N(ROM��) */
typedef struct t_kernel_flgcb_rom
{
	ATR    flgatr;		/* �C�x���g�t���O���� */
	FLGPTN iflgptn;		/* �C�x���g�t���O�̃r�b�g�p�^�[���̏����l */
} T_KERNEL_FLGCB_ROM;

/* �C�x���g�t���O�R���g���[���u���b�N(RAM��) */
typedef struct t_kernel_flgcb_ram
{
	T_MKNL_QUE que;			/* �C�x���g�t���O�҂��s�� */
	FLGPTN     flgptn;		/* �C�x���g�t���O�̃r�b�g�p�^�[�� */
	const T_KERNEL_FLGCB_ROM* flgcb_rom;	/* �C�x���g�t���O�R���g���[���u���b�NROM���ւ̃|�C���^ */
} T_KERNEL_FLGCB_RAM;


/* �҂��t���O���\���� */
typedef struct t_kernel_flginf
{
	MODE   wfmode;		/* �҂����[�h */
	FLGPTN waiptn;		/* �҂��r�b�g�p�^�[���i�������p�^�[���ƌ��p) */
} T_KERNEL_FLGINF;



/* ---------------------------------- */
/*        �O���[�o���ϐ��錾          */
/* ---------------------------------- */

/* �C�x���g�t���O�Ǘ� */
extern       T_KERNEL_FLGCB_RAM *kernel_flgcb_ram_tbl[];	/* �C�x���g�t���O�R���g���[���u���b�N�e�[�u��(RAM��) */
extern const INT kernel_flgcb_cnt;							/* �C�x���g�t���O�R���g���[���u���b�N�� */

#define KERNEL_FLGID_TO_FLGCB_RAM(flgid)	(kernel_flgcb_ram_tbl[(flgid) - KERNEL_TMIN_FLGID])
															/* �C�x���g�t���OID����FLGCB RAM�A�h���X���擾 */



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �C�x���g�t���O */
void    kernel_ini_flg(void);								/* �C�x���g�t���O�̏����� */
ER      cre_flg(ID flgid, const T_CFLG *pk_cflg);			/* �C�x���g�t���O�̐��� */
ER_ID   acre_flg(const T_CFLG *pk_cflg);					/* �C�x���g�t���O�̐���(ID�ԍ��������t��) */
ER      kernel_cre_flg(ID flgid, const T_CFLG *pk_cflg);	/* �C�x���g�t���O�̐���(�J�[�l�������֐�) */
ER      del_flg(ID flgid);									/* �C�x���g�t���O�̍폜 */
ER      set_flg(ID flgid, FLGPTN setptn);					/* �C�x���g�t���O�̃Z�b�g */
#define iset_flg	set_flg									/* �C�x���g�t���O�̃Z�b�g(��^�X�N�R���e�L�X�g�p�}�N��) */
ER      clr_flg(ID flgid, FLGPTN clrptn);					/* �C�x���g�t���O�̃N���A */
ER      wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
															/* �C�x���g�t���O�҂� */
ER      pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
															/* �C�x���g�t���O�҂�(�|�[�����O) */
ER      twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
															/* �C�x���g�t���O�҂�(�^�C���A�E�g����) */
ER      ref_flg(ID flgid, T_RFLG *pk_rflg);					/* �C�x���g�t���O�̏�ԎQ�� */
BOOL    kernel_chk_flg(T_KERNEL_FLGCB_RAM *flgcb_ram, T_KERNEL_FLGINF *pk_flginf);
															/* �t���O���N�������𖞂����Ă��邩�`�F�b�N */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_flg_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
