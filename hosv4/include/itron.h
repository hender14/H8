/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ��ITRON4.0 �W���w�b�_                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__itron_h__
#define __HOS_V4__itron_h__



/* ------------------------------------ */
/*          �f�[�^�^��`                */
/* ------------------------------------ */

typedef signed char		B;			/* �����t��8�r�b�g���� */
typedef signed short	H;			/* �����t��16�r�b�g���� */
typedef signed long		W;			/* �����t��32�r�b�g���� */

typedef unsigned char	UB;			/* ��������8�r�b�g���� */
typedef unsigned short 	UH;			/* ��������16�r�b�g���� */
typedef unsigned long	UW;			/* ��������32�r�b�g���� */

typedef signed char		VB;			/* �f�[�^�^�C�v����܂�Ȃ�8�r�b�g�̒l */
typedef signed short	VH;			/* �f�[�^�^�C�v����܂�Ȃ�16�r�b�g�̒l */
typedef signed long		VW;			/* �f�[�^�^�C�v����܂�Ȃ�32�r�b�g�̒l */

typedef void			*VP;		/* �f�[�^�^�C�v����܂�Ȃ����̂ւ̃|�C���^ */
typedef void			(*FP)();	/* �v���O�����̋N���Ԓn�i�|�C���^�j */

typedef signed   int	INT;		/* �v���Z�b�T�Ɏ��R�ȃT�C�Y�̕����t������(16bit�ȏ�) */
typedef unsigned int	UINT;		/* �v���Z�b�T�Ɏ��R�ȃT�C�Y�̕�����������(16bit�ȏ�) */

typedef INT		BOOL;		/* �^�U�l */

typedef INT		FN;			/* �@�\�R�[�h */
typedef INT		ER;			/* �G���[�R�[�h */
typedef INT		ID;			/* �I�u�W�F�N�g��ID�ԍ� */
typedef UH		ATR;		/* �I�u�W�F�N�g�̑��� */
typedef UH		STAT;		/* �I�u�W�F�N�g�̏�� */
typedef UH		MODE;		/* �T�[�r�X�R�[���̓��샂�[�h */
typedef INT		PRI;		/* �D��x */
typedef UW		SIZE;		/* �������̈�̃T�C�Y */
typedef W		TMO;		/* �^�C���A�E�g�w�� */
typedef UW		RELTIM;		/* ���Ύ��� */

typedef struct t_systim		/* �V�X�e������ */
{
	UW ltime;				/* ���� 32bit */
	UH utime;				/* ��� 16bit */
} SYSTIM;

typedef long	VP_INT;		/* VP �܂��� INT */

typedef ER		ER_BOOL;	/* ER �܂��� BOOL */

typedef W		ER_UINT;	/* ER �܂��� UINT */

typedef INT		ER_ID;		/* ER �܂��� ID */

typedef UH		TEXPTN;		/* �^�X�N��O�v���̃p�^�[�� */

typedef UH		FLGPTN;		/* �t���O�p�^�[�� */

typedef INT     EXCNO;		/* CPU��O�n���h���ԍ� */

typedef INT		INHNO;		/* ���荞�݃n���h���ԍ� */
typedef INT		INTNO;		/* ���荞�ݔԍ� */



/* ------------------------------------ */
/*             �萔��`                 */
/* ------------------------------------ */

/* ��� */
#ifdef NULL		/* C����W���w�b�_�Ƃ̋������ */
#undef NULL
#endif

#ifdef __cplusplus
#define NULL		0			/* �����|�C���^ */
#else
#define NULL		((void *)0)	/* �����|�C���^ */
#endif

#define TRUE		1			/* �^ */
#define FALSE		0			/* �U */
#define E_OK		0			/* ����I�� */


/* �I�u�W�F�N�g���� */
#define TA_NULL		0			/* �I�u�W�F�N�g�������w�肵�Ȃ� */
#define TA_HLNG		0x00		/* ��������p�̃C���^�[�t�F�[�X�ŏ����P�ʂ��N�� */
#define TA_ASM		0x01		/* �A�Z���u������p�̃C���^�[�t�F�[�X�ŏ����P�ʂ��N�� */

#define TA_TFIFO	0x00		/* �^�X�N�̑҂��s���FIFO���� */
#define TA_TPRI		0x01		/* �^�X�N�̑҂��s����^�X�N�̗D��x���� */

#define TA_MFIFO	0x00		/* ���b�Z�[�W�̑҂��s���FIFO���� */
#define TA_MPRI		0x02		/* ���b�Z�[�W�̑҂��s������b�Z�[�W�̗D��x���� */

#define TA_ACT		0x02		/* �^�X�N���N�����ꂽ��ԂŐ��� */
#define TA_RSTR		0x04		/* ����^�X�N */

#define TA_WSGL		0x00		/* �C�x���g�t���O�𕡐��̃^�X�N���҂��Ƃ������Ȃ� */
#define TA_WMUL		0x02		/* �C�x���g�t���O�𕡐��̃^�X�N���҂��Ƃ����� */
#define TA_CLR		0x04		/* �҂��������ɃC�x���g�t���O���N���A */

#define TA_INHERIT	0x02		/* �~���[�e�b�N�X���D��x�p���v���g�R�����T�|�[�g */
#define TA_CEILING	0x03		/* �~���[�e�b�N�X���D��x����v���g�R�����T�|�[�g */

#define TA_STA		0x02		/* �����n���h���𓮍삵�Ă����ԂŐ��� */
#define TA_PHS		0x04		/* �����n���h���̈ʑ���ۑ� */


/* �^�C���A�E�g�w�� */
#define TMO_POL		0			/* �|�[�����O */
#define TMO_FEVR	(-1)		/* �i�v�҂� */
#define TMO_NBLK	(-2)		/* �m���u���b�L���O */


/* �T�[�r�X�R�[���̓��샂�[�h */
#define TWF_ANDW	0x00		/* �C�x���g�t���O��AND�҂� */
#define TWF_ORW		0x01		/* �C�x���g�t���O��OR�҂� */


/* �I�u�W�F�N�g�̏�� */
#define TTS_RUN		0x01		/* ���s��� */
#define TTS_RDY		0x02		/* ���s�\��� */
#define TTS_WAI		0x04		/* �҂���� */
#define TTS_SUS		0x08		/* �����҂���� */
#define TTS_WAS		0x0c		/* ��d�҂���� */
#define TTS_DMT		0x10		/* �x�~��� */

#define TTW_SLP		0x0001		/* �N���҂���� */
#define TTW_DLY		0x0002		/* ���Ԍo�ߑ҂���� */
#define TTW_SEM		0x0004		/* �Z�}�t�H�����̊l���҂���� */
#define TTW_FLG		0x0008		/* �C�x���g�t���O�҂���� */
#define TTW_SDTQ	0x0010		/* �f�[�^�L���[�ւ̑��M�҂���� */
#define TTW_RDTQ	0x0020		/* �f�[�^�L���[����̎�M�҂���� */
#define TTW_MBX		0x0040		/* ���[���{�b�N�X����̎�M�҂���� */
#define TTW_MTX		0x0080		/* �~���[�e�b�N�X�̃��b�N�҂���� */
#define TTW_SMBF	0x0100		/* ���b�Z�[�W�o�b�t�@�ւ̑��M�҂���� */
#define TTW_RMBF	0x0200		/* ���b�Z�[�W�o�b�t�@����̎�M�҂���� */
#define TTW_CAL		0x0400		/* �����f�u�̌Ăяo���҂���� */
#define TTW_ACP		0x0800		/* �����f�u�̎�t�҂���� */
#define TTW_RDV		0x1000		/* �����f�u�̏I���҂���� */
#define TTW_MPF		0x2000		/* �Œ蒷�������u���b�N�̊l���҂���� */
#define TTW_MPL		0x4000		/* �ϒ��������u���b�N�̊l���҂���� */

#define TTEX_ENA	0x00		/* �^�X�N�̗�O��������� */
#define TTEX_DIS	0x01		/* �^�X�N��O�����֎~��� */

#define TCYC_STP	0x00		/* �����n���h�������삵�Ă��Ȃ� */
#define TCYC_STA	0x01		/* �����n���h�������삵�Ă��� */

#define TALM_STP	0x00		/* �A���[���n���h�������삵�Ă��Ȃ� */
#define TALM_STA	0x00		/* �A���[���n���h�������삵�Ă��� */

#define TOVR_STP	0x00		/* ����v���Z�b�T���Ԃ��ݒ肳��Ă��Ȃ� */
#define TOVR_STA	0x01		/* ����v���Z�b�T���Ԃ��ݒ肳��Ă��� */

/* ���̑��̒萔 */
#define TSK_SELF	0			/* ���^�X�N�w�� */
#define TSK_NONE	0			/* �Y������^�X�N������ */

#define TPRI_SELF	0			/* ���^�X�N�̃x�[�X�D��x�̎w�� */
#define TPRI_INI	0			/* �^�X�N�̋N�����D��x�̎w�� */


/* �G���[�R�[�h */
#define E_SYS		(-5)		/* �V�X�e���G���[ */
#define E_NOSPT		(-9)		/* ���T�|�[�g�@�\ */
#define E_RSFN		(-10)		/* �\��@�\�R�[�h */
#define E_RSATR		(-11)		/* �\�񑮐� */
#define E_PAR		(-17)		/* �p�����[�^�G���[ */
#define E_ID		(-18)		/* �s��ID�ԍ� */
#define E_CTX		(-25)		/* �R���e�L�X�g�G���[ */
#define E_MACV		(-26)		/* �������A�N�Z�X�ᔽ */
#define E_OACV		(-27)		/* �I�u�W�F�N�g�A�N�Z�X�ᔽ */
#define E_ILUSE		(-28)		/* �T�[�r�X�R�[���s���g�p */
#define E_NOMEM		(-33)		/* �������s�� */
#define E_NOID		(-34)		/* ID�ԍ��s�� */
#define E_OBJ		(-41)		/* �I�u�W�F�N�g��ԃG���[ */
#define E_NOEXS		(-42)		/* �I�u�W�F�N�g������ */
#define E_QOVR		(-43)		/* �L���[�C���O�I�[�o�[�t���[ */
#define E_RLWAI		(-49)		/* �҂���Ԃ̋������� */
#define E_TMOUT		(-50)		/* �|�[�����O���s�܂��̓^�C���A�E�g */
#define E_DLT		(-51)		/* �҂��I�u�W�F�N�g�̍폜 */
#define E_CLS		(-52)		/* �҂��I�u�W�F�N�g�̏�ԕω� */
#define E_WBLK		(-57)		/* �m���u���b�L���O��t�� */
#define E_BOVR		(-58)		/* �o�b�t�@�I�[�o�[�t���[ */


/* ID�͈̔�(HOS�Ǝ�) */
#define TMIN_TSKID	1			/* �^�X�N��ID�ԍ��̍ŏ��l */
#define TMIN_SEMID	1			/* �Z�}�t�H��ID�ԍ��̍ŏ��l */
#define TMIN_FLGID	1			/* �C�x���g�t���O��ID�ԍ��̍ŏ��l */
#define TMIN_DTQID	1			/* �f�[�^�L���[��ID�ԍ��̍ŏ��l */
#define TMIN_MBXID	1			/* ���[���{�b�N�X�^�X�N��ID�ԍ��̍ŏ��l */
#define TMIN_MBFID	1			/* ���b�Z�[�W�o�b�t�@��ID�ԍ��̍ŏ��l */
#define TMIN_MPFID	1			/* �Œ蒷�������v�[����ID�ԍ��̍ŏ��l */
#define TMIN_MPLID	1			/* �ϒ��������v�[����ID�ԍ��̍ŏ��l */
#define TMIN_CYCID	1			/* �����n���h����ID�ԍ��̍ŏ��l */
#define TMIN_ALMID	1			/* �A���[���n���h����ID�ԍ��̍ŏ��l */
#define TMIN_ISRID	1			/* ���荞�݃T�[�r�X���[�`����ID�ԍ��̍ŏ��l */



/* ------------------------------------ */
/*           �}�N����`                 */
/* ------------------------------------ */


/* �G���[�R�[�h���o�� */
#define	MERCD(ercd)		((ER)((B)(ercd)))		/* �G���[�R�[�h���烁�C���G���[�R�[�h�����o�� */
#define	SERCD(ercd)		((ercd) >> 8)			/* �G���[�R�[�h����T�u�G���[�R�[�h�����o�� */



#endif /* __HOS_V4__itron_h__ */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
