/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �T���v���v���O����                                                     */
/*   ���[�U�[�쐬�֐� StrongARM�p                                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���荞�݃R���g���[���[���W�X�^�A�h���X */
#define ICIP		(*(volatile UW *)0x9005000)
#define ICMR		(*(volatile UW *)0x9005004)
#define ICLR		(*(volatile UW *)0x9005008)
#define ICFP		(*(volatile UW *)0x9005010)
#define ICPR		(*(volatile UW *)0x9005020)
#define ICCR		(*(volatile UW *)0x900500c)



/* ���[�J���ϐ� */
static UW fiq_save_imask;		/* FIQ�����荞�݃}�X�N�l�ۑ��p */



/* IRQ�̏����� */
void hos_arm_ini_int(void)
{
	/* ���荞�݃R���g���[���[������ */
	ICMR = 0x00000000;		/* �S���荞�݂��}�X�N */
}


/* IRQ���荞�ݏ����J�n�i���[�U�[�쐬�֐��j */
INTNO hos_arm_sta_irq(void)
{
	UW    status;
	UW    mask;
	INTNO intno;
	
	/* ���荞�ݔԍ����� */
	status = SA_ICIP;
	mask   = 0x00000001;
	for ( intno = TMIN_INTNO; intno <= TMAX_INTNO ; intno++ )
	{
		if ( status & mask )
		{
			break;
		}
		mask <<= 1;
	}
	
	/* ���荞�݃}�X�N�ݒ� */
	hospac_arm_imask |= (ARM_IMASK_IRQ | ARM_IMASK_USR_MODE);	/* IRQ���}�X�N(FIQ�̂݋���) */
	
	mknl_ena_int();		/* ���d���荞�݋��� */
	
	return intno;
}


/* IRQ���荞�ݏ����I���i���[�U�[�쐬�֐��j */
void  hos_arm_end_irq(void)
{
	mknl_dis_int();		/* ���d���荞�݋֎~ */
	
	hospac_arm_imask = ARM_IMASK_USR_MODE;	/* IRQ�}�X�N������ */
}


/* FIQ���荞�ݏ����J�n�i���[�U�[�쐬�֐��j */
INTNO hos_arm_sta_fiq(void)
{
	UW    status;
	UW    mask;
	INTNO intno;
	
	/* ���荞�ݔԍ����� */
	status = SA_ICFP;
	mask   = 0x00000001;
	for ( intno = TMIN_INTNO; intno <= TMAX_INTNO ; intno++ )
	{
		if ( status & mask )
		{
			break;
		}
		mask <<= 1;
	}
	
	fiq_save_imask   = hospac_arm_imask;	/* ���荞�݃}�X�N��ԕۑ� */
	hospac_arm_imask = (ARM_IMASK_IRQ | ARM_IMASK_FIQ | ARM_IMASK_USR_MODE)
											/* ���荞�݂�S�}�X�N */
	
	return intno;	/* ���荞�ݔԍ���Ԃ� */
}


/* FIQ���荞�ݏ����I���i���[�U�[�쐬�֐��j */
void  hos_arm_end_fiq(void)
{
	fiq_save_imask   = hospac_arm_imask;	/* ���荞�݃}�X�N��ԕ��A */
}


/* ���荞�݂̋��� */
ER ena_int(INTNO intno)
{
	mknl_loc_sys();		/* �V�X�e�����b�N */
	
	ICMR |= 0x00000001 << (intno - TMIN_INTNO);
	
	mknl_unl_sys();		/* �V�X�e�����b�N���� */
	
	return E_OK;
}


/* ���荞�݂̋֎~ */
ER dis_int(INTNO intno)
{
	mknl_loc_sys();		/* �V�X�e�����b�N */
	
	ICMR &= ~(0x00000001 << (intno - TMIN_INTNO));
	
	mknl_unl_sys();		/* �V�X�e�����b�N���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
