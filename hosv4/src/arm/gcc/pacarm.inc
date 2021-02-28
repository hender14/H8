/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (ARM gcc�p)                            */
/*   �A�Z���u�����ꋤ�ʃC���N���[�h�t�@�C��                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



				/* �t���O��` */
				.equ	Mode_USR, 0x10		/* USR ���[�h */
				.equ	Mode_FIQ, 0x11		/* FIQ ���[�h */
				.equ	Mode_IRQ, 0x12		/* IRQ ���[�h */
				.equ	Mode_SVR, 0x13		/* Supervisor ���[�h */
				.equ	Mode_ABT, 0x17		/* Abort ���[�h */
				.equ	Mode_UND, 0x1b		/* Undefined ���[�h */
				.equ	Mode_SYS, 0x1f		/* System ���[�h */

				.equ	T_Bit, 0x20			/* T �r�b�g */
				.equ	F_Bit, 0x40			/* F �r�b�g */
				.equ	I_Bit, 0x80			/* I �r�b�g */


				/* CPU��O�n���h���ԍ���` */
				.equ	EXCNO_UND, 1		/* Undefined��O */
				.equ	EXCNO_SWI, 2		/* SWI��O */
				.equ	EXCNO_PRE, 3		/* �v���t�F�b�`�A�{�[�g */
				.equ	EXCNO_DAT, 4		/* �f�[�^�A�{�[�g */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */