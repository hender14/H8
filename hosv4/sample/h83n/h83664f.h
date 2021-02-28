/* ------------------------------------------------------------------------- */
/*  H8/3664F �p �w�b�_�t�@�C��                                               */
/*  �S�Ẵf�o�C�X�Ō��؂����Ă����ł͖����̂ŁA�g�p�ɂ������Ă͏\������   */
/*  ���K�v�ł��B                                                             */
/*  ���̕ӂ��l�̌��E�ƌ������ŁA�o�O�񍐑҂��Ă܂��B                       */
/*                                                                           */
/*  ��������w�b�_�[�t�@�C�� �o�[�W�����Q�Ƃ̈Ⴂ                            */
/*  �����̃w�b�_�[�t�@�C���ł�16bit���̃t�B�[���h�� int�ŕ\���Ă��܂��B      */
/*  ���̃w�b�_�[�t�@�C��������ɕ킨�����Ƃ��v���܂������Ashort�ŕ\������    */
/*  ���܂����B�ƌ����̂� SH�Ȃ񂩂����\ H8�ō쐬�����R�[�f�B���O���̂܂ܓ�   */
/*  �����Ⴄ���������̂ł���(���� SCI��)�A�Ⴆ�� AD�͂�͂�10bit�ł��̒���   */
/*  �� H8�� SH���ς�炸�A���W�X�^��16bit�ŃA�N�Z�X���܂��B�������� int��    */
/*  �������� short�ƂȂ�̂��C�}�C�`���Ȃ̂ŁA�����Ƃ�������ׂ� short�Ő�   */
/*  �����Ă��܂��B                                                           */
/*  �܂��A�����R���p�C���[ �o�[�W�����R�ȏ�ł͖��ƂȂ�Ȃ��r�b�g�t�B�[    */
/*  ���h�̏ȗ��ł����A�H���R���p�C���A�܂�����R���p�C�� �o�[�W�����Q��    */
/*  �T�u�Z�b�g�ł̓R���p�C���G���[�ƂȂ�̂ŁA�K���ȃt�B�[���h�����[�ĂĂ�   */
/*  �܂��B                                                                   */
/*                                                                           */
/*                                   Copyright (C) 1998-2003 by Project HOS  */
/* ------------------------------------------------------------------------- */


#ifndef __PROJECT_HOS__H8_3664_H_
#define __PROJECT_HOS__H8_3664_H_

/* IO �f�o�C�X�A�h���X��` */
#define	__EKR_ADD__		0xFF10		/* EKR���W�X�^�X�^�[�g�A�h���X */
#define	__TIMER_W_ADD__	0xFF80		/* TW���W�X�^�X�^�[�g�A�h���X */
#define	__FLASH_ADD__	0xFF90		/* FLASH���W�X�^�X�^�[�g�A�h���X */
#define	__TIMER_V_ADD__	0xFFA0		/* TV���W�X�^�X�^�[�g�A�h���X */
#define	__TIMER_A_ADD__	0xFFA6		/* TA���W�X�^�X�^�[�g�A�h���X */
#define	__SCI3_ADD__	0xFFA8		/* SCI3���W�X�^�X�^�[�g�A�h���X */
#define	__AD_ADD__		0xFFB0		/* A/D���W�X�^�X�^�[�g�A�h���X */
#define	__WDT_ADD__		0xFFC0		/* WDT���W�X�^�X�^�[�g�A�h���X */
#define	__IIC_ADD__		0xFFC4		/* IIC���W�X�^�X�^�[�g�A�h���X */
#define	__ADDRESS_BREAK_ADD__	0xFFC8		/* �A�h���X�u���C�N���W�X�^�X�^�[�g�A�h���X */
#define	__IO_PORT_ADD__		0xFFD0	/* IO�|�[�g���W�X�^�X�^�[�g�A�h���X */
#define	__SYSCR1_ADD__	0xFFF0		/* SYSCR1���W�X�^�X�^�[�g�A�h���X */
#define	__SYSCR2_ADD__	0xFFF1		/* SYSCR2���W�X�^�X�^�[�g�A�h���X */
#define	__IEGR1_ADD__	0xFFF2		/* IEGR1���W�X�^�X�^�[�g�A�h���X */
#define	__IEGR2_ADD__	0xFFF3		/* IEGR2���W�X�^�X�^�[�g�A�h���X */
#define	__IENR1_ADD__	0xFFF4		/* IENR1���W�X�^�X�^�[�g�A�h���X */
#define	__IRR1_ADD__	0xFFF6		/* IRR1���W�X�^�X�^�[�g�A�h���X */
#define	__IWPR_ADD__	0xFFF8		/* IWPR���W�X�^�X�^�[�g�A�h���X */
#define	__MSTCR1_ADD__	0xFFF9		/* MSTCR1���W�X�^�X�^�[�g�A�h���X */
#define	__TSCR_ADD__	0xFFFC		/* TSCR���W�X�^�X�^�[�g�A�h���X */

/*TIMER W*/
struct __TIMER_W_REGISTER__
{
	union								/*TMRW*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CTS:1;		/*�J�E���^�X�^�[�g*/
			unsigned char rsv1:1;		/*�\��*/
			unsigned char BUFEB:1;		/*�o�b�t�@���� B*/
			unsigned char BUFEA:1;		/*�o�b�t�@���� A*/
			unsigned char rsv2:1;		/*�\��*/
			unsigned char PWMD:1;		/*PWM���[�h D*/
			unsigned char PWMC:1;		/*PWM���[�h C*/
			unsigned char PWMB:1;		/*PWM���[�h B*/
		} BIT;
	} TMRW;
	union								/*TCRW*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CCLR:1;		/*�J�E���^�N���A*/
			unsigned char CKS:3;		/*�N���b�N�Z���N�g*/
			unsigned char TOD:1;		/*�^�C�}�o�̓��x���Z�b�g D*/
			unsigned char TOC:1;		/*�^�C�}�o�̓��x���Z�b�g C*/
			unsigned char TOB:1;		/*�^�C�}�o�̓��x���Z�b�g B*/
			unsigned char TOA:1;		/*�^�C�}�o�̓��x���Z�b�g A*/
		} BIT;
	} TCRW;
	union								/*TIERW*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char OVIE:1;		/*�^�C�}�I�[�o�[�t���[�����݃C�l�[�u��*/
			unsigned char rsv1:3;		/*�\��*/
			unsigned char IMIED:1;		/*�C���v�b�g�L���v�`��/�R���y�A�}�b�`�����݃C�l�[�u�� D*/
			unsigned char IMIEC:1;		/*�C���v�b�g�L���v�`��/�R���y�A�}�b�`�����݃C�l�[�u�� C*/
			unsigned char IMIEB:1;		/*�C���v�b�g�L���v�`��/�R���y�A�}�b�`�����݃C�l�[�u�� B*/
			unsigned char IMIEA:1;		/*�C���v�b�g�L���v�`��/�R���y�A�}�b�`�����݃C�l�[�u�� A*/
		} BIT;
	} TIERW;
	union								/*TSRW*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char OVF:1;		/*�^�C�}�I�[�o�[�t���[*/
			unsigned char rsv1:3;		/*�\��*/
			unsigned char IMFD:1;		/*�C���v�b�g�L���v�`��/�R���y�A�}�b�`�t���O D*/
			unsigned char IMFC:1;		/*�C���v�b�g�L���v�`��/�R���y�A�}�b�`�t���O C*/
			unsigned char IMFB:1;		/*�C���v�b�g�L���v�`��/�R���y�A�}�b�`�t���O B*/
			unsigned char IMFA:1;		/*�C���v�b�g�L���v�`��/�R���y�A�}�b�`�t���O A*/
		} BIT;
	} TSRW;
	union								/*TIOR0*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:1;		/*�\��*/
			unsigned char IOB:3;		/*IO�R���g���[�� B*/
			unsigned char rsv2:1;		/*�\��*/
			unsigned char IOA:3;		/*IO�R���g���[�� A*/
		} BIT;
	} TIOR0;
	union								/*TIOR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:1;		/*�\��*/
			unsigned char IOD:3;		/*IO�R���g���[�� D*/
			unsigned char rsv2:1;		/*�\��*/
			unsigned char IOC:3;		/*IO�R���g���[�� C*/
		} BIT;
	} TIOR1;
	unsigned short	TCNT;				/*�^�C�}�J�E���^*/
	unsigned short	GRA;				/*�W�F�l�������W�X�^ A*/
	unsigned short	GRB;				/*�W�F�l�������W�X�^ B*/
	unsigned short	GRC;				/*�W�F�l�������W�X�^ C*/
	unsigned short	GRD;				/*�W�F�l�������W�X�^ D*/
};

#define	TW	(*(volatile struct __TIMER_W_REGISTER__ *)__TIMER_W_ADD__)


/*FLASH ROM*/
struct __FLASH_ROM_REGISTER__
{
	union								/*FLMCR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:1;		/*�\��*/
			unsigned char SWE:1;		/*�\�t�g�E�G�A���C�g�C�l�[�u��*/
			unsigned char ESU:1;		/*�C���[�X�Z�b�g�A�b�v*/
			unsigned char PSU:1;		/*�v���O�����Z�b�g�A�b�v*/
			unsigned char EV:1;			/*�C���[�X�x���t�@�C*/
			unsigned char PV:1;			/*�v���O�����x���t�@�C*/
			unsigned char E:1;			/*���C���[�X*/
			unsigned char P:1;			/*�v���O����*/
		} BIT;
	} FLMCR1;
	union								/*FLMCR2*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char FLER:1;		/*FLASH ROM �������݃G���[*/
			unsigned char rsv1:7;		/*�\��*/
		} BIT;
	} FLMCR2;
	union								/*FLPWCR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char PDWND:1;		/*�p���[�_�E���f�B�X�G�[�u��*/
			unsigned char rsv1:7;		/*�\��*/
		} BIT;
	} FLPWCR;
	union								/*EBR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:3;		/*�\��*/
			unsigned char EB4:1;		/*�C���[�X�u���b�N 4*/
			unsigned char EB3:1;		/*�C���[�X�u���b�N 3*/
			unsigned char EB2:1;		/*�C���[�X�u���b�N 2*/
			unsigned char EB1:1;		/*�C���[�X�u���b�N 1*/
			unsigned char EB0:1;		/*�C���[�X�u���b�N 0*/
		} BIT;
	} EBR1;
	char	rsv1[ 0xff9b - 0xff93 - 1 ];	/*��*/
	union								/*FENR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char FLSHE:1;		/*�t���b�V���������R���g���[�����W�X�^�C�l�[�u��*/
			unsigned char rsv1:7;		/*�\��*/
		} BIT;
	} FENR;
};

#define	FLASH	(*(volatile struct __FLASH_ROM_REGISTER__ *)__FLASH_ADD__)

/*TIMER V*/
struct __TIMER_V_REGISTER__
{
	union								/*TCRV0*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CMIEB:1;		/*�R���y�A�}�b�`�C���^���v�g�C�l�[�u�� B*/
			unsigned char CMIEA:1;		/*�R���y�A�}�b�`�C���^���v�g�C�l�[�u�� A*/
			unsigned char OVIE:1;		/*�^�C�}�I�[�o�[�t���[�C���^���v�g�C�l�[�u�� B*/
			unsigned char CCLR:2;		/*�J�E���^�N���A*/
			unsigned char CKS:3;		/*�N���b�N�Z���N�g*/
		} BIT;
	} TCRV0;
	union								/*TCSRV*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CMFB:1;		/*�R���y�A�}�b�`�t���O B*/
			unsigned char CMFA:1;		/*�R���y�A�}�b�`�t���O A*/
			unsigned char OVF:1;		/*�^�C�}�I�[�o�[�t���[�t���O*/
			unsigned char rsv1:1;		/*�\��*/
			unsigned char OS:4;			/*�A�E�g�v�b�g�Z���N�g*/
		} BIT;
	} TCSRV;
	unsigned char TCORA;				/*�^�C���R���X�^���g���W�X�^ A*/
	unsigned char TCORB;				/*�^�C���R���X�^���g���W�X�^ B*/
	unsigned char TCNTV;				/*�^�C�}�J�E���g�^ V*/
	union								/*TCRV1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:3;		/*�\��*/
			unsigned char TVEG:2;		/*TRGV ���̓G�b�W�Z���N�g*/
			unsigned char TRGE:1;		/*�J�E���g�A�b�v�̊J�n�ƃJ�E���g�A�b�v�̒�~�̋֎~��*/
			unsigned char rsv2:1;		/*�\��*/
			unsigned char ICKS:1;		/*�C���^�[�i���N���b�N�Z���N�g 0*/
		} BIT;
	} TCRV1;
};

#define	TV	(*(volatile struct __TIMER_V_REGISTER__ *)__TIMER_V_ADD__)

/*TIMER A*/
struct __TIMER_A_REGISTER__
{
	union								/*TMA*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CKSO:3;		/*TMOW�[�q����o�͂���N���b�N�̑I��*/
			unsigned char rsv1:1;		/*�\��*/
			unsigned char CKSI:4;		/*�^�C�}A�̓��샂�[�h�̐ݒ�*/
		} BIT;
	} TMA;
	unsigned char TCA;					/*�^�C�}�J�E���^ A*/
};

#define	TA	(*(volatile struct __TIMER_A_REGISTER__ *)__TIMER_A_ADD__)

/*SCI3*/
struct __SCI3_REGISTER__
{
	union								/*SMR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char COM:1;		/*�R�~���j�P�[�V�������[�h*/
			unsigned char CHR:1;		/*�L�����N�^�����O�X*/
			unsigned char PE:1;			/*�p���e�B�C�l�[�u��*/
			unsigned char PM:1;			/*�p���e�B���[�h*/
			unsigned char STOP:1;		/*�X�g�b�v�r�b�g�����O�X*/
			unsigned char MP:1;			/*�}���`�v���Z�b�T���[�h*/
			unsigned char CKS:2;		/*�N���b�N�Z���N�g*/
		} BIT;
	} SMR;
	unsigned char BRR;					/*�r�b�g���[�g���W�X�^*/
	union								/*SCR3*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char TIE:1;		/*�g�����X�~�b�g�C���^���v�g�C�l�[�u��*/
			unsigned char RIE:1;		/*���V�[�u�C���^���v�g�C�l�[�u��*/
			unsigned char TE:1;			/*�g�����X�~�b�g�C�l�[�u��*/
			unsigned char RE:1;			/*���V�[�u�C�l�[�u��*/
			unsigned char MPIE:1;		/*�}���`�v���Z�b�T�C���^���v�g�C�l�[�u��*/
			unsigned char TEIE:1;		/*�g�����X�~�b�g�G���h�C���^���v�g�C�l�[�u��*/
			unsigned char CKE:2;		/*�N���b�N�C�l�[�u��*/
		} BIT;
	} SCR3;
	unsigned char TDR;					/**/
	union								/*SSR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char TDRE:1;		/*�g�����X�~�b�g�f�[�^���W�X�^�G���v�e�B*/
			unsigned char RDRF:1;		/*���V�[�u�f�[�^���W�X�^�t��*/
			unsigned char OER:1;		/*�I�[�o�[�����G���[*/
			unsigned char FER:1;		/*�t���[�~���O�G���[*/
			unsigned char PER:1;		/*�p���e�B�G���[*/
			unsigned char TEND:1;		/*�g�����X�~�b�g�G���h*/
			unsigned char MPBR:1;		/*�}���`�v���Z�b�T�r�b�g���V�[�u*/
			unsigned char MPBT:1;		/*�}���`�v���Z�b�T�r�b�g�g�����X�t�@*/
		} BIT;
	} SSR;
	unsigned char RDR;					/*���V�[�u�f�[�^���W�X�^*/
};

#define	SCI3	(*(volatile struct __SCI3_REGISTER__ *)__SCI3_ADD__)

/*AD*/
struct __AD_REGISTER__
{
	unsigned short ADDRA;				/*A/D �f�[�^���W�X�^ A*/
	unsigned short ADDRB;				/*A/D �f�[�^���W�X�^ B*/
	unsigned short ADDRC;				/*A/D �f�[�^���W�X�^ C*/
	unsigned short ADDRD;				/*A/D �f�[�^���W�X�^ D*/
	union								/*ADCSR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char ADF:1;		/*A/D �G���h�t���O*/
			unsigned char ADIE:1;		/*A/D �C���^���v�g�C�l�[�u��*/
			unsigned char ADST:1;		/*A/D �X�^�[�g*/
			unsigned char SCAN:1;		/*�X�L�������[�h*/
			unsigned char CKS:1;		/*�N���b�N�Z���N�g*/
			unsigned char CH:3;			/*�`���l���Z���N�g*/
		} BIT;
	} ADCSR;
	union								/*ADCR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char TRGE:1;		/*�g���K�C�l�[�u��*/
			unsigned char rsv1:7;		/*�\��*/
		} BIT;
	} ADCR;
};

#define	AD	(*(volatile struct __AD_REGISTER__ *)__AD_ADD__)

/*WDT*/
struct __WDT_REGISTER__
{
	union								/*TCSRWD*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B6WI:1;		/*�r�b�g 6 �����݋֎~*/
			unsigned char TCWE:1;		/*�^�C�}�J�E���^ W �������݋���*/
			unsigned char B4WI:1;		/*�r�b�g 4 �����݋֎~*/
			unsigned char TCSRWE:1;		/*�^�C�}�R���g���[��/�X�e�[�^�X���W�X�^ W �������݋���*/
			unsigned char B2WI:1;		/*�r�b�g 2 �����݋֎~*/
			unsigned char WDON:1;		/*�E�I�b�`�h�b�O�^�C�}�I��*/
			unsigned char B0WI:1;		/*�r�b�g 0 �����݋֎~*/
			unsigned char WRST:1;		/*�E�I�b�`�h�b�O�^�C�}���Z�b�g*/
		} BIT;
	} TCSRWD;
	unsigned char	TCWD;				/*�^�C�}�J�E���^*/
	union								/*TMWD*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:4;		/*�\��*/
			unsigned char CKS:4;		/*�N���b�N�Z���N�g*/
		} BIT;
	} TMWD;
};

#define	WDT	(*(volatile struct __WDT_REGISTER__ *)__WDT_ADD__)

/*IIC*/
struct __IIC_REGISTER__
{
	union								/*ICCR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char ICE:1;		/*I2C�o�X�C���^�t�F�[�X�C�l�[�u��*/
			unsigned char IEIC:1;		/*I2C�o�X�C���^�t�F�[�X�����݃C�l�[�u��*/
			unsigned char MST:1;		/*�}�X�^�[/�X���[�u�I��*/
			unsigned char TRS:1;		/*����I��*/
			unsigned char ACKE:1;		/*�A�N�m���b�W�r�b�g����I��*/
			unsigned char BBSY:1;		/*�o�X�r�W�[*/
			unsigned char IRIC:1;		/*I2C�o�X�C���^�t�F�[�X�����ݗv���t���O*/
			unsigned char SCP:1;		/*�J�n����/��~�������s�֎~�r�b�g*/
		} BIT;
	} ICCR;
	union								/*ICSR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char ESTP:1;		/*�G���[��~�������o�t���O*/
			unsigned char STOP:1;		/*�����~�������o�t���O*/
			unsigned char IRTR:1;		/*I2C�o�X�C���^�t�F�[�X�A������M�����ݗv���t���O*/
			unsigned char AASX:1;		/*���X���[�u�A�h���X�F���t���O*/
			unsigned char AL:1;			/*�A�[�r�g���[�V�������X�g�t���O*/
			unsigned char AAS:1;		/*�X���[�u�A�h���X�F���t���O*/
			unsigned char ADZ:1;		/*�[�l�����R�[���A�h���X�F���t���O*/
			unsigned char ACKB:1;		/*�A�N�m���b�W�r�b�g*/
		} BIT;
	} ICSR;
	union
	{
		struct
		{
			union
			{
				unsigned char	BYTE;	/*Byte Access*/
				struct					/*Bit Access*/
				{
					unsigned char SVAX:7;	/*���X���[�u�A�h���X*/
					unsigned char FSX:1;	/*SAR��FS�Ƃ̑g�ݍ��킹�œ]���t�H�[�}�b�g��ݒ�*/
				} BIT;
			} UN_SARX;
			union
			{
				unsigned char	BYTE;	/*Byte Access*/
				struct					/*Bit Access*/
				{
					unsigned char SVA:7;	/*�X���[�u�A�h���X*/
					unsigned char FS:1;		/*SARX��FSX�Ƃ̑g�ݍ��킹�œ]���t�H�[�}�b�g��ݒ�*/
				} BIT;
			} UN_SAR;
		} ICE0;
		struct
		{
			unsigned char	UN_ICDR;	/* I2C�o�X �f�[�^���W�X�^*/
			union
			{
				unsigned char	BYTE;	/*Byte Access*/
				struct					/*Bit Access*/
				{
					unsigned char MLS:1;	/*MSB�t�@�[�X�g/LSB�t�@�[�X�g�I��*/
					unsigned char WAIT:1;	/*�E�G�C�g�}���r�b�g*/
					unsigned char CKS:3;	/*�]���N���b�N�I��*/
					unsigned char BC:3;		/*�r�b�g�J�E���^�[*/
				} BIT;
			} UN_ICMR;
		} ICE1;
	} EQU;
};

#define	IIC	(*(volatile struct __IIC_REGISTER__ *)__IIC_ADD__)
#define	ICDR	EQU.ICE1.UN_ICDR		/* ICDR */
#define	ICMR	EQU.ICE1.UN_ICMR		/* ICDR */
#define	SAR		EQU.ICE0.UN_SAR			/* SAR  */
#define	SARX	EQU.ICE0.UN_SARX		/* SARX */

/*ADDRESS BREAK*/
struct __ADDRESS_BREAK_REGISTER__
{
	union								/*ABRKCR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char RTINTE:1;		/*RTE�����݃C�l�[�u��*/
			unsigned char CSEL:2;		/*�R���f�B�V�����Z���N�g*/
			unsigned char ACMP:3;		/*�A�h���X�R���y�A*/
			unsigned char DCMP:2;		/*�f�[�^�R���y�A*/
		} BIT;
	} CR;
	union								/*ABRKSR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char ABIF:1;		/*ABRKCR�Őݒ肳�ꂽ����������������*/
			unsigned char ABIE:1;		/* 1�̎��A�h���X�u���[�N�����ݗv�����C�l�[�u���ɂ��܂�*/
			unsigned char rsv1:6;		/*�\��*/
		} BIT;
	} SR;
	void			*BAR;				/*�u���[�N�A�h���X���W�X�^*/
	unsigned short	BDR;				/*�u���[�N�f�[�^���W�X�^*/
};

#define	ABRK	(*(volatile struct __ADDRESS_BREAK_REGISTER__ *)__ADDRESS_BREAK_ADD__)

/*IO PORT*/
struct __IO_PORT_REGISTER__
{
	union								/*PUCR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char rsv1:1;		/*�\��*/
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PUCR1;
	union								/*PUCR5*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:2;		/*�\��*/
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char B3:1;			/* Bit 3 */
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PUCR5;
	char	rsv1[ 0xffd4 - 0xffd1 - 1 ];	/*��*/
	union								/*PDR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char rsv1:1;		/*�\��*/
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDR1;
	union								/*PDR2*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:5;		/*�\��*/
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDR2;
	char	rsv2[ 0xffd8 - 0xffd5 - 1 ];	/*��*/
	union								/*PDR5*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char B3:1;			/* Bit 3 */
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDR5;
	char	rsv3[ 0xffda - 0xffd8 - 1 ];	/*��*/
	union								/*PDR7*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:1;		/*�\��*/
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char rsv2:4;		/*�\��*/
		} BIT;
	} PDR7;
	union								/*PDR8*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char B3:1;			/* Bit 3 */
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDR8;
	char	rsv4[ 0xffdd - 0xffdb - 1 ];	/*��*/
	union								/*PDRB*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char B3:1;			/* Bit 3 */
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDRB;
	char	rsv5[ 0xffe0 - 0xffdd - 1 ];	/*��*/
	union								/*PMR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char IRQ3:1;		/*P17/IRQ3/TRGV�[�q�̋@�\�̑I�������܂�*/
			unsigned char IRQ2:1;		/*P16/IRQ2�[�q�̋@�\�̑I�������܂�*/
			unsigned char IRQ1:1;		/*P15/IRQ1�[�q�̋@�\�̑I�������܂�*/
			unsigned char IRQ0:1;		/*P14/IRQ0�[�q�̋@�\�̑I�������܂�*/
			unsigned char rsv1:2;		/*�\��*/
			unsigned char TXD:1;		/*P22/TXD�[�q�̋@�\�̑I�������܂�*/
			unsigned char TMOW:1;		/*P10/TMOW�[�q�̋@�\�̑I�������܂�*/
		} BIT;
	} PMR1;
	union								/*PMR5*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:2;		/*�\��*/
			unsigned char WKP5:1;		/*P55/WKP5�[�q�̋@�\�̑I�������܂�*/
			unsigned char WKP4:1;		/*P54/WKP4�[�q�̋@�\�̑I�������܂�*/
			unsigned char WKP3:1;		/*P53/WKP3�[�q�̋@�\�̑I�������܂�*/
			unsigned char WKP2:1;		/*P52/WKP2�[�q�̋@�\�̑I�������܂�*/
			unsigned char WKP1:1;		/*P51/WKP1�[�q�̋@�\�̑I�������܂�*/
			unsigned char WKP0:1;		/*P50/WKP0�[�q�̋@�\�̑I�������܂�*/
		} BIT;
	} PMR5;
	char	rsv6[ 0xffe4 - 0xffe1 - 1 ];	/*��*/
	unsigned char	PCR1;				/**/
	unsigned char	PCR2;				/**/
	char	rsv7[ 0xffe8 - 0xffe5 - 1 ];	/*��*/
	unsigned char	PCR5;				/**/
	char	rsv8[ 0xffea - 0xffe8 - 1 ];	/*��*/
	unsigned char	PCR7;				/**/
	unsigned char	PCR8;				/**/
};

#define	IO	(*(volatile struct __IO_PORT_REGISTER__ *)__IO_PORT_ADD__)

/*SYSCR1*/
union __SYSCR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char SSBY:1;			/*�\�t�g�E�G�A�X�^���o�C*/
		unsigned char STS:3;			/*�X�^���o�C�^�C�}�Z���N�g*/
		unsigned char NESEL:1;			/*�m�C�Y�����T���v�����O���g���I��*/
		unsigned char rsv1:3;			/*�\��*/
	} BIT;
};

#define	SYSCR1	(*(volatile union __SYSCR1_REGISTER__ *)__SYSCR1_ADD__)

/*SYSCR2*/
union __SYSCR2_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char SMSEL:1;			/*�X���[�v���[�h�I��*/
		unsigned char LSON:1;			/*���[�X�s�[�h�I���t���O*/
		unsigned char DTON:1;			/*�_�C���N�g�g�����X�t�@�I���t���O*/
		unsigned char MA:3;				/*�A�N�e�B�u���[�h�N���b�N�Z���N�g*/
		unsigned char SA:2;				/*�T�u�A�N�e�B�u���[�h�N���b�N�Z���N�g*/
	} BIT;
};

#define	SYSCR2	(*(volatile union __SYSCR2_REGISTER__ *)__SYSCR2_ADD__)

/*IEGR1*/
union __IEGR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char NMIEG:1;			/*NMI�G�b�W�Z���N�g*/
		unsigned char rsv1:3;			/*�\��*/
		unsigned char IEG3:1;			/*IRQ3�G�b�W�Z���N�g*/
		unsigned char IEG2:1;			/*IRQ2�G�b�W�Z���N�g*/
		unsigned char IEG1:1;			/*IRQ1�G�b�W�Z���N�g*/
		unsigned char IEG0:1;			/*IRQ0�G�b�W�Z���N�g*/
	} BIT;
};

#define	IEGR1	(*(volatile union __IEGR1_REGISTER__ *)__IEGR1_ADD__)

/*IEGR2*/
union __IEGR2_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char rsv1:2;			/*�\��*/
		unsigned char WPEG5:1;			/*WKOP5�G�b�W�Z���N�g*/
		unsigned char WPEG4:1;			/*WKOP4�G�b�W�Z���N�g*/
		unsigned char WPEG3:1;			/*WKOP3�G�b�W�Z���N�g*/
		unsigned char WPEG2:1;			/*WKOP2�G�b�W�Z���N�g*/
		unsigned char WPEG1:1;			/*WKOP1�G�b�W�Z���N�g*/
		unsigned char WPEG0:1;			/*WKOP0�G�b�W�Z���N�g*/
	} BIT;
};

#define	IEGR2	(*(volatile union __IEGR2_REGISTER__ *)__IEGR2_ADD__)

/*IENR1*/
union __IENR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char IENDT:1;			/*���ڑJ�ڊ����ݗv���C�l�[�u��*/
		unsigned char IENTA:1;			/*�^�C�} A �����ݗv���C�l�[�u��*/
		unsigned char IENWP:1;			/* WAKE UP �����ݗv���C�l�[�u��*/
		unsigned char rsv1:1;			/*�\��*/
		unsigned char IEN3:1;			/*IRQ3 �����ݗv���C�l�[�u��*/
		unsigned char IEN2:1;			/*IRQ2 �����ݗv���C�l�[�u��*/
		unsigned char IEN1:1;			/*IRQ1 �����ݗv���C�l�[�u��*/
		unsigned char IEN0:1;			/*IRQ0 �����ݗv���C�l�[�u��*/
	} BIT;
};

#define	IENR1	(*(volatile union __IENR1_REGISTER__ *)__IENR1_ADD__)

/*IRR1*/
union __IRR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char IRRDT:1;			/*���ڑJ�ڊ����ݗv���t���O*/
		unsigned char IRRTA:1;			/*�^�C�} A �����ݗv���t���O*/
		unsigned char rsv1:2;			/*�\��*/
		unsigned char IRRI3:1;			/*IRQ3 �����ݗv���t���O*/
		unsigned char IRRI2:1;			/*IRQ2 �����ݗv���t���O*/
		unsigned char IRRI1:1;			/*IRQ1 �����ݗv���t���O*/
		unsigned char IRRI0:1;			/*IRQ0 �����ݗv���t���O*/
	} BIT;
};

#define	IRR1	(*(volatile union __IRR1_REGISTER__ *)__IRR1_ADD__)

/*IWPR*/
union __IWPR_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char rsv1:2;			/*�\��*/
		unsigned char IWPF5:1;			/*WKP5 �����ݗv���t���O*/
		unsigned char IWPF4:1;			/*WKP4 �����ݗv���t���O*/
		unsigned char IWPF3:1;			/*WKP3 �����ݗv���t���O*/
		unsigned char IWPF2:1;			/*WKP2 �����ݗv���t���O*/
		unsigned char IWPF1:1;			/*WKP1 �����ݗv���t���O*/
		unsigned char IWPF0:1;			/*WKP0 �����ݗv���t���O*/
	} BIT;
};

#define	IWPR	(*(volatile union __IWPR_REGISTER__ *)__IWPR_ADD__)

/*MSTCR1*/
union __MSTCR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char rsv1:1;			/*�\��*/
		unsigned char MSTIIC:1;			/*IIC���W���[���X�^���o�C*/
		unsigned char MSTS3:1;			/*SCI3���W���[���X�^���o�C*/
		unsigned char MSTAD:1;			/*A/D�ϊ����W���[���X�^���o�C*/
		unsigned char MSTWD:1;			/*�E�I�b�`�h�b�O�^�C�}�[���W���[���X�^���o�C*/
		unsigned char MSTTW:1;			/*�^�C�} W ���W���[���X�^���o�C*/
		unsigned char MSTTV:1;			/*�^�C�} V ���W���[���X�^���o�C*/
		unsigned char MSTTA:1;			/*�^�C�} A ���W���[���X�^���o�C*/
	} BIT;
};

#define	MSTCR1	(*(volatile union __MSTCR1_REGISTER__ *)__MSTCR1_ADD__)

/*TSCR*/
union __TSCR_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char rsv1:6;			/*�\��*/
		unsigned char IICRST:1;			/*IICRST�́AI2C���W�X�^�������R���g���[������RESET���܂��B*/
		unsigned char IICX:1;			/*ICMR��CKS2�`0�Ƃ̑g�ݍ��킹�ŁA�}�X�^�[���[�h�̓]�����[�g��I�����܂��B*/
	} BIT;
};

#define	TSCR	(*(volatile union __TSCR_REGISTER__ *)__TSCR_ADD__)

/*EKR*/
union __EKR_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char B7:1;				/* Bit 7 */
		unsigned char B6:1;				/* Bit 6 */
		unsigned char B5:1;				/* Bit 5 */
		unsigned char B4:1;				/* Bit 4 */
		unsigned char B3:1;				/* Bit 3 */
		unsigned char B2:1;				/* Bit 2 */
		unsigned char B1:1;				/* Bit 1 */
		unsigned char B0:1;				/* Bit 0 */
	} BIT;
};

#define	EKR	(*(volatile union __EKR_REGISTER__ *)__EKR_ADD__)

#endif /* __PROJECT_HOS__H8_3664_H_ */
