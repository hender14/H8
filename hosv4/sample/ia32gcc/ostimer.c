/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*  IA32 OS �^�C�}                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "kernel.h"
#include "ia32/ia32gcc/ioport.h"
#include "ostimer.h"
/* OS�p�^�C�}������ */
void ostim_init(VP_INT exinf)
{
  unsigned short divisor;

  /* �����^�C�}�̐ݒ�  */
#if PERIOD<1000
    divisor=PIT_I8254_INPFREQ / (1000 * 1000) * PERIOD + 1;
#else
    divisor=PIT_I8254_INPFREQ / (1000 / (PERIOD/1000)) + 1;
#endif

  /*  Set timer Channel2 as rate Genarator  */
  out_port_byte(PIT_PORT_MODECNTL, 0x34);
  /*
   *  Set interval as period_us  
   */
  out_port_byte(PIT_PORT_CHANNEL0, (divisor&(0xff)));      /*  write LSB  */
  out_port_byte(PIT_PORT_CHANNEL0, ((divisor>>8)&(0xff))); /*  write MSB  */
  
  return ;
}


/* ���荞�݃n���h���T���v�� */
void ostim_hdr(VP_INT exinf)	/* OS�^�C�}�p�n���h�� */
{
  isig_tim();		/* �^�C���e�B�b�N�̋��� */
}
/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
