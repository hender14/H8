/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �v���Z�b�T���ۉ��R���|�[�l���g (IA32�p)  �����݊֘A����                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "hosdenv.h"
#include "kernel.h"

ER   
chg_imsk(IMSK imsk)		/* ���荞�݃}�X�N�w�� */
{
  out_port_byte (PIC1_BASE_ADDR2, ((UB)(imsk>>8)));
  out_port_byte (PIC2_BASE_ADDR2, ((UB)(imsk&0xff)));

  return E_OK;
}

/* ���荞�݃}�X�N�̎Q�� */
ER   
get_imsk(IMSK *p_imsk)
{
  if (!p_imsk)
    return E_PAR;

  *p_imsk = in_port_byte (PIC1_BASE_ADDR2)<<8|in_port_byte (PIC2_BASE_ADDR2);
  
  return E_OK;
}

int
_kernel_ia32__send_eoi(unsigned long exp)
{
  volatile unsigned char isr=0;
  unsigned char irq=(unsigned char)exp - PIC1_VBASE_ADDR;

  if (MAX_IRQ_NR <= irq)
    return E_PAR;

  if ( irq < 8 )
    out_port_byte(PIC1_OCW2_ADDR, pic_mk_spec_eoi(irq));
  else {
    out_port_byte(PIC2_OCW2_ADDR, pic_mk_spec_eoi(irq));
    out_port_byte(PIC2_OCW3_ADDR, pic_mk_ocw3code(PIC_OCW3_NEXT_ISR));
    isr =in_port_byte(PIC2_OCW3_ADDR);
    if (!isr)
      out_port_byte(PIC1_OCW2_ADDR, pic_mk_spec_eoi(0x2));
  }

  return E_OK;
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
