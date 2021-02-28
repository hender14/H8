/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*  OS �^�C�}                                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#include "kernel.h"
#include "ostimer.h"
#include "sh7750.h"

/* OS�p�^�C�}������ */
void ostim_init(VP_INT exinf)
{
  /* �^�C�}������ */
  /* �ꉞ,TMU0���ꎞ��~���� */
  TMU.TSTR.BYTE &= 0xfe;

  /*
   * UNF=0|00|UNIE=1|CKEG1=0|CKEG0=0|TPSC=000
   * P��/4=50MHz/4=12.5MHz�ŃJ�E���g,���荞�݋���
   */
  TMU0.TCR.WORD = 0x20;
  TMU0.TCOR = TMU0.TCNT = (((UH)(INT)exinf) * 100) >> 3;
  /* TMU0 �J�E���^�X�^�[�g */
  TMU.TSTR.BYTE |= 0x01;
}


/* ���荞�݃n���h���T���v�� */
void ostim_hdr(VP_INT exinf)	/* OS�^�C�}�p�n���h�� */
{
  /* �A���_�[�t���[�t���O�N���A */
  TMU0.TCR.WORD &= 0xfeff;

  isig_tim();		/* �^�C���e�B�b�N�̋��� */
}


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
