/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l���ˑ�����`�w�b�_                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__mknl_h__
#define __HOS_V4__mknl_h__



#include "itron.h"
#include "hosdenv.h"



/* ------------------------------------------ */
/*                �萔��`                    */
/* ------------------------------------------ */

/* �^�X�N�D��x�͈̔� */
#define TMIN_TPRI			1					/* �^�X�N�D��x�̍ŏ��l */
#define TMAX_TPRI			(TMIN_TPRI + mknl_rdq_cnt - 1)
												/* �^�X�N�D��x�̍ő�l */


/* �V�X�e���̏�� */
#define MKNL_TSS_TSK		0x00				/* �^�X�N�����s�� */
#define MKNL_TSS_INDP		0x04				/* �^�X�N�Ɨ������s�� */
#define MKNL_TSS_DDSP		0x01				/* �f�B�X�p�b�`�֎~ (dis_dsp �L��) */
#define MKNL_TSS_DINT		0x02				/* ���荞�݋֎~(loc_cpu �L��) */
#define MKNL_TSS_DDLY		0x80				/* �f�B�X�p�b�`�x���� */

/* �^�X�N�̗�O������� */
#define MKNL_TTS_RDLY		0x01				/* ��O�����ۗ���� */
#define MKNL_TTS_DRAS		0x02				/* ��O�����֎~��� */



/* ------------------------------------------ */
/*                 �^��`                     */
/* ------------------------------------------ */

/* �L���[�Ǘ��u���b�N */
typedef struct t_mknl_que
{
	struct t_mknl_tcb *head;	/* �L���[�̐擪 */
} T_MKNL_QUE;


/* �ʃJ�[�l�� �^�X�N�R���g���[���u���b�N */
typedef struct t_mknl_tcb
{
	T_HOSPAC_CTXINF   ctxinf;		/* �R���e�L�X�g���ۑ��u���b�N */
	STAT              tskwait;		/* �҂��v�� */
	UB                tskstat;		/* �^�X�N�̏�� */
	UB                texstat;		/* ��O�����̏�� */
	PRI               tskpri;		/* ���݂̗D��x */
	ER_UINT           ercd;			/* �҂������v���p�G���[�R�[�h */
	VP_INT            data;			/* �ėp�f�[�^�̈� */
	struct t_mknl_que *que;			/* �����Ă���L���[  */
	struct t_mknl_tcb *next;		/* �L���[�ł̎���TCB */
	struct t_mknl_tcb *prev;		/* �L���[�ł̑O��TCB */
	struct t_mknl_tcb *tm_next;		/* �^�C���A�E�g�L���[�̎���TCB */
	struct t_mknl_tcb *tm_prev;		/* �^�C���A�E�g�L���[�̑O��TCB */
	RELTIM            diftim;		/* ���O��TCB�Ƃ̃^�C���A�E�g�܂ł̎��ԍ� */
} T_MKNL_TCB;


/* �^�C���A�E�g�Ǘ��p�\���� */
typedef struct t_mknl_timout
{
	T_MKNL_TCB *mtcb;		/* �^�C���A�E�g�҂��̃^�X�N */
	RELTIM     diftim;		/* �z�񒼑O�̑҂��^�X�N�Ƃ̎��ԍ� */
} T_MKNL_TIMOUT;



/* ------------------------------------------ */
/*              �O���ϐ��錾                  */
/* ------------------------------------------ */

/* �V�X�e���Ǘ� */
extern STAT            mknl_ctx_stat;		/* �V�X�e���̃R���e�L�X�g��� */
extern T_MKNL_TCB      *mknl_run_mtcb;		/* ���s���^�X�N�R���g���[���u���b�N */

/* �A�C�h�����[�v�Ǘ� */
extern T_HOSPAC_CTXINF mknl_idlctx;			/* �A�C�h�����[�v�̃R���e�L�X�g */
extern const VP        mknl_idl_stk;		/* �A�C�h�����[�v�̃X�^�b�N */
extern const SIZE      mknl_idl_stksz;		/* �A�C�h�����[�v�̃X�^�b�N�T�C�Y */

/* �^�X�N�Ǘ� */
extern T_MKNL_QUE      mknl_rdq_tbl[];		/* ���f�B�[�L���[�e�[�u�� */
extern const INT       mknl_rdq_cnt;		/* ���f�B�[�L���[�� */

extern       INT       mknl_timout_tskcnt;	/* �^�C���A�E�g�҂��s��̃^�X�N�� */

/* �^�C���A�E�g�Ǘ� */
extern T_MKNL_TCB      *mknl_timout_head;	/* �^�C���A�E�g�L���[�̐擪 */


/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �ʃJ�[�l���̃T�[�r�X�R�[���͌��� mknl_sys_loc() �� */
/* ���b�N���ꂽ��ԂŌĂяo����邱��                 */

/* �V�X�e������ */
void    mknl_ini_sys(void);									/* �ʃJ�[�l���V�X�e���̏����� */
void    mknl_sta_startup(void);								/* �X�^�[�g�A�b�v���[�`���̊J�n���� */
void    mknl_ext_startup(void);								/* �X�^�[�g�A�b�v���[�`���̏I������ */
void    mknl_exe_sys(FP exec, VP_INT exinf);				/* */
void    mknl_idl_loop(void);								/* �A�C�h�����[�v */

/* �^�X�N���� */
#define mknl_ini_tsk(mtcb)	do { (mtcb)->tskstat = TTS_DMT; } while (0)
															/* �^�X�N�̏�����(�}�N���֐�) */
void    mknl_sta_tsk(T_MKNL_TCB *mtcb, VP_INT exinf,
							FP task, PRI tskpri,
							SIZE stksz, VP stk);			/* �^�X�N�̊J�n */
void    mknl_ter_tsk(T_MKNL_TCB *mtcb);						/* �^�X�N�̏I�� */
void    mknl_chg_pri(T_MKNL_TCB *mtcb, PRI tskpri);			/* �^�X�N�D��x�ύX */
void    mknl_wai_tsk(T_MKNL_TCB *mtcb, STAT tskwait);		/* �^�X�N�̑҂� */
void    mknl_wup_tsk(T_MKNL_TCB *mtcb, ER_UINT ercd);		/* �^�X�N�̑҂����� */
void    mknl_sus_tsk(T_MKNL_TCB *mtcb);						/* �^�X�N�̋����҂� */
void    mknl_rsm_tsk(T_MKNL_TCB *mtcb);						/* �^�X�N�̋����҂����� */
void    mknl_rot_rdq(PRI tskpri);							/* �^�X�N�D�揇�ʂ̉�] */
ER_UINT mknl_exe_dsp(void);									/* �^�X�N�f�B�X�p�b�`�̎��s */
void    mknl_dly_dsp(void);									/* �x�����Ă����f�B�X�p�b�`�̎��s */
T_MKNL_TCB* mknl_srh_top(void);								/* ���f�B�[�L���[�擪�̃^�X�N��T�� */
#define mknl_get_run_tsk()		(mknl_run_mtcb)				/* ���s���^�X�N�̎擾(�}�N���֐�) */
#define mknl_get_pri(mtcb)		((PRI)(mtcb)->tskpri)		/* �^�X�N�D��x�擾(�}�N���֐�) */
#define mknl_get_tskstat(mtcb)	((STAT)(mtcb)->tskstat)		/* �^�X�N��Ԏ擾(�}�N���֐�) */
#define mknl_get_tskwait(mtcb)	((STAT)(mtcb)->tskwait)		/* �҂��v���擾(�}�N���֐�) */

void    kernel_task_entry(VP_INT exinf);					/* �^�X�N�̃G���g���[�|�C���g(�J�[�l�����ŗp�ӂ��邱��) */


/* �^�X�N��O���� */
void    mknl_ras_tex(T_MKNL_TCB *mtcb);						/* �^�X�N��O�����̗v�� */
void    mknl_exe_tex(void);									/* �^�X�N��O�����̎��s */
#define mknl_dis_tex(mtcb)	\
	do { (mtcb)->texstat |= MKNL_TTS_DRAS; } while (0)		/* �^�X�N��O�����̋֎~ */
#define mknl_ena_tex(mtcb)	\
	do { (mtcb)->texstat &= ~MKNL_TTS_DRAS; } while (0)		/* �^�X�N��O�����̋��� */
#define mknl_sns_tex()	\
	((mknl_run_mtcb == NULL || (mknl_run_mtcb->texstat & MKNL_TTS_DRAS)) ? TRUE: FALSE)
															/* �^�X�N��O�����֎~��Ԃ̎Q�� */

void    kernel_tex_entry(void);								/* �^�X�N��O�����G���g���[�|�C���g(�J�[�l�����ŗp�ӂ��邱��) */
	

/* �V�X�e������ */
#define mknl_loc_sys()	\
	do { if ( !(mknl_ctx_stat & MKNL_TSS_DINT) ) { hospac_dis_int(); } } while (0)
															/* �V�X�e���̃��b�N(�}�N���֐�) */
#define mknl_unl_sys()	\
	do { if ( !(mknl_ctx_stat & MKNL_TSS_DINT) ) { hospac_ena_int(); } } while (0)
															/* �V�X�e���̃��b�N����(�}�N���֐�) */
#define mknl_dis_int()	do { hospac_dis_int(); } while (0)	/* ���荞�݋֎~ */
#define mknl_ena_int()	do { hospac_ena_int(); } while (0)	/* ���荞�݋��� */
#define mknl_sta_ind()	do { mknl_ctx_stat |= MKNL_TSS_INDP; } while (0)
															/* ��^�X�N���̊J�n(�}�N���֐�) */
#define mknl_ext_ind()	do { mknl_ctx_stat &= ~MKNL_TSS_INDP; } while (0)
															/* ��^�X�N���̏I��(�}�N���֐�) */
#define mknl_loc_cpu()	do { mknl_ctx_stat |= MKNL_TSS_DINT; } while (0)
															/* CPU�̃��b�N(�}�N���֐�) */
#define mknl_unl_cpu()	do { mknl_ctx_stat &= ~MKNL_TSS_DINT; } while (0)
															/* CPU�̃��b�N����(�}�N���֐�) */
#define mknl_dis_dsp()	do { mknl_ctx_stat |= MKNL_TSS_DDSP; } while (0)
															/* �f�B�X�p�b�`�̋֎~(�}�N���֐�) */
#define mknl_ena_dsp()	do { mknl_ctx_stat &= ~MKNL_TSS_DDSP; } while (0)
															/* �f�B�X�p�b�`�̋���(�}�N���֐�) */
#define mknl_sns_ctx()	((mknl_ctx_stat & MKNL_TSS_INDP) ? TRUE : FALSE)
															/* �R���e�L�X�g�̎Q��(�}�N���֐�) */
#define mknl_sns_loc()	((mknl_ctx_stat & MKNL_TSS_DINT) ? TRUE : FALSE)
															/* CPU���b�N��Ԃ̎Q��(�}�N���֐�) */
#define mknl_sns_dsp()	((mknl_ctx_stat & MKNL_TSS_DDSP) ? TRUE : FALSE)
															/* �f�B�X�p�b�`�֎~��Ԃ̎Q��(�}�N���֐�) */
#define mknl_sns_dpn()	((mknl_ctx_stat & MKNL_TSS_DDLY) ? TRUE : FALSE)
															/* �f�B�X�p�b�`�ۗ���Ԃ̎Q��(�}�N���֐�) */
#define mknl_sns_wai()	((mknl_ctx_stat & (MKNL_TSS_INDP | MKNL_TSS_DDSP | MKNL_TSS_DINT)) ? TRUE : FALSE)
															/* �҂���Ԉڍs�\�Q��(�}�N���֐�) */


/* �L���[���� */
#define mknl_ini_que(que)	do { (que)->head = NULL; } while (0)
void    mknl_clr_que(T_MKNL_QUE *que);						/* �L���[�̍폜 */
															/* �L���[�̏����� */
void    mknl_add_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb, ATR atr);
															/* �^�X�N���L���[�ɒǉ� */
void    mknl_adf_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb);	/* �^�X�N��FIFO���ŃL���[�ɒǉ� */
void    mknl_adp_que(T_MKNL_QUE *que, T_MKNL_TCB *mtcb);	/* �^�X�N��D��x���ŃL���[�ɒǉ� */
void    mknl_rmv_que(T_MKNL_TCB *mtcb);						/* �^�X�N���L���[�����菜�� */
void    mknl_rot_que(T_MKNL_QUE *que);						/* ���f�B�[�L���[�̉�] */
#define mknl_ref_qhd(que)	((que)->head)					/* �L���[�̐擪�^�X�N�̎Q��(�}�N���֐�) */
#define mknl_ref_nxt(que, mtcb)		\
		((mtcb)->next != (que)->head ? (mtcb)->next : NULL)	/* ���̃L���[���擾 */

/* �^�C���A�E�g�҂��s�� */
void    mknl_tic_tmout(RELTIM tictim);						/* �^�C���A�E�g�Ƀ^�C���e�B�b�N���� */
ER      mknl_add_tmout(T_MKNL_TCB *mtcb, RELTIM tmout);		/* �^�C���A�E�g�҂��s��Ƀ^�X�N��ǉ� */
void    mknl_rmv_tmout(T_MKNL_TCB *mtcb);					/* �^�C���A�E�g�҂��s�񂩂�^�X�N����菜�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__mknl_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
