/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*  OS �^�C�}                                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2007 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "semb1200a/ux_signal.h"
#include "kernel.h"
#include "kernel_id.h"
#include "ostimer.h"

// CPU�N���b�N��1/2�ŃJ�E���g
// 300000 / (600000000 / 2) = 0.001
// 600MHz�̏ꍇ�A1ms = 300000
#define COMPARE  (300000)

/* OS�p�^�C�}������ */
void ostim_init(VP_INT exinf)
{
	SET_CP0_COUNT (0);
	SET_CP0_COMPARE (COMPARE);
	SET_CP0_STATUS (IE_IRQ5);
}

/* OS�^�C�}�p�n���h�� */
void ostim_hdr(VP_INT exinf)
{
    /* �J�E���^���W�X�^�̃N���A */
	SET_CP0_COUNT (0);
	SET_CP0_COMPARE (COMPARE);
    /* �^�C���e�B�b�N�̋��� */
    isig_tim();
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2007 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
