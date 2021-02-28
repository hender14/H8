/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �f�o�b�O�x��  �f�B�X�p�b�`�t�b�N                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__dsp_hok_h__
#define __HOS_V4__dsp_hok_h__



/* �f�B�X�p�b�`�t�b�N�}�N�� */
#ifdef _HOS_DSP_HOK_ENABLE
#ifndef _HOS_TSW_HOK_ENABLE
#define _HOS_TSW_HOK_ENABLE
#endif
#ifndef _HOS_INT_HOK_ENABLE
#define _HOS_INT_HOK_ENABLE
#endif
#endif

/* �^�X�N�X�C�b�` �t�b�N�}�N���̒�` */
#ifdef _HOS_TSW_HOK_ENABLE
#define _HOS_TSW_HOK()	_hos_tsw_hok()	/* �L�� */
#else
#define _HOS_TSW_HOK()					/* ���� */
#endif

/* ���荞�� �t�b�N�}�N���̒�` */
#ifdef _HOS_INT_HOK_ENABLE
#define _HOS_INTSTA_HOK(intno)	_hos_intsta_hok(intno)	/* �L�� */
#define _HOS_INTEXT_HOK(intno)	_hos_intext_hok(intno)
#else
#define _HOS_INTSTA_HOK(intno)							/* ���� */
#define _HOS_INTEXT_HOK(intno)
#endif

/* �f�B�X�p�b�`�^�C�v��` */
#define _HOS_DSPTYPE_TSKSWC		1	/* �^�X�N�X�C�b�`���� */
#define _HOS_DSPTYPE_STAINT		2	/* ���荞�ݏ����J�n */
#define _HOS_DSPTYPE_EXTINT		3	/* ���荞�ݏ����I�� */

/* �t�b�N�}�X�N */
#define _HOS_HOKMSK_TSW			0x01	/* �^�X�N�X�C�b�`�t�b�N */
#define _HOS_HOKMSK_INT			0x02	/* ���荞�݃t�b�N */


/* �f�B�X�p�b�`��� */
typedef struct t_dbg_dspinf
{
	UW  time;		/* ���� */
	INT type;		/* �������� */
	INT id;			/* ID */
} T_DBG_DSPINF;



/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ����֐� */
void _hosdbg_ini_dsphok(T_DBG_DSPINF dspinf[], INT infcnt);	/* �t�b�N���������� */
void _hosdbg_sta_dsphok(INT mask);							/* �t�b�N�����J�n */
void _hosdbg_stp_dsphok(void);								/* �t�b�N������~ */

/* ���O�ǂݏo���֐� */
T_DBG_DSPINF *_hosdbg_red_fst(void);		/* �ǂݏo���J�n */
T_DBG_DSPINF *_hosdbg_red_nxt(void);		/* ����ǂݏo�� */

/* �f�B�X�p�b�`�t�b�N�֐� */
void _hos_tsw_hok(void);			/* �^�X�N�X�C�b�` �t�b�N */
void _hos_intsta_hok(INTNO intno);	/* ���荞�݊J�n �t�b�N */
void _hos_intext_hok(INTNO intno);	/* ���荞�ݏI�� �t�b�N */

/* ���[�U�[�쐬�֐� */
UW   _hosdbg_get_tim(void);			/* �����x���Ԏ擾 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__dsp_hok_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
