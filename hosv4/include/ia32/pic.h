/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (IA32�p�����݃R���g���[������)         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__pic_h__
#define __HOS_V4__IA32__pic_h__
/*
  +--------+-----------------+--------------------------------------+
  |Address |Read/Write       |Function                              |
  +--------+-----------------+--------------------------------------+
  |20h     |Write            |Initialization Command Word 1 (ICW1)  |
  |        +-----------------+--------------------------------------+
  |        |Write            |Operation Command Word 2 (OCW2)       |
  |        +-----------------+--------------------------------------+
  |        |Write            |Operation Command Word 3 (OCW3)       |
  |        +-----------------+--------------------------------------+
  |        |Read             |Interrupt Request Register (IRR)      |
  |        +-----------------+--------------------------------------+
  |        |Read             |In-Service Register (ISR)             |
  +--------+-----------------+--------------------------------------+
  |21h     |Write            |Initialization Command Word 2 (ICW2)  |
  |        +-----------------+--------------------------------------+
  |        |Write            |Initialization Command Word 3 (ICW3)  |
  |        +-----------------+--------------------------------------+
  |        |Write            |Initialization Command Word 4 (ICW4)  |
  |        +-----------------+--------------------------------------+
  |        |Read/Write       |Interrupt Mask Register (IMR)         |
  +--------+-----------------+--------------------------------------+
               Addresses of  i8259 PIC1 on AT


  +--------+-----------------+--------------------------------------+
  |Address |Read/Write       |Function                              |
  +--------+-----------------+--------------------------------------+
  |A0h     |Write            |Initialization Command Word 1 (ICW1)  |
  |        +-----------------+--------------------------------------+
  |        |Write            |Operation Command Word 2 (OCW2)       |
  |        +-----------------+--------------------------------------+
  |        |Write            |Operation Command Word 3 (OCW3)       |
  |        +-----------------+--------------------------------------+
  |        |Read             |Interrupt Request Register (IRR)      |
  |        +-----------------+--------------------------------------+
  |        |Read             |In-Service Register (ISR)             |
  +--------+-----------------+--------------------------------------+
  |A1h     |Write            |Initialization Command Word 2 (ICW2)  |
  |        +-----------------+--------------------------------------+
  |        |Write            |Initialization Command Word 3 (ICW3)  |
  |        +-----------------+--------------------------------------+
  |        |Write            |Initialization Command Word 4 (ICW4)  |
  |        +-----------------+--------------------------------------+
  |        |Read/Write       |Interrupt Mask Register (IMR)         |
  +--------+-----------------+--------------------------------------+
              Addresses of  i8259 PIC2 on AT 
*/

/*  Programmable Interrupt Controller's Addresses   */
#define PIC1_BASE_ADDR1  0x20
#define PIC1_BASE_ADDR2  0x21
#define PIC2_BASE_ADDR1  0xA0
#define PIC2_BASE_ADDR2  0xA1

/*
+------------+------+----------------------------------------------+
|  Bit       |value |Function                                      |
+------------+------+----------------------------------------------+
|7:5         |      |Interrupt Vector Addresses for MCS-80/85 Mode.|
+------------+------+----------------------------------------------+
|  4         |1     |Must be set to 1 for ICW1                     |
+------------+------+----------------------------------------------+
|  3         |1     |Level Triggered Interrupts                    |
|            |0     |Edge Triggered Interrupts                     |
+------------+------+----------------------------------------------+
|  2         |1     |Call Address Interval of 4                    |
|            |0     |Call Address Interval of 8                    |
+------------+------+----------------------------------------------+
|  1         |1     |Single PIC                                    |
|            |0     |Cascaded PICs                                 |
+------------+------+----------------------------------------------+
|  0         |1     |Will be Sending ICW4                          |
|            |0     |Don't need ICW4                               |
+------------+------+----------------------------------------------+
               Initialization Command Word 1
*/

/*  Initialization Command Word 1  */
#define _PIC_ICW1_SENDICW4     0x01  /* ICW4�𑗐M���� */
#define _PIC_ICW1_SINGLPIC     0x02  /* PIC��������ō\������Ă��� */
#define _PIC_ICW1_CASCDPIC     0x00  /* ������PIC���J�X�P�[�h */
#define _PIC_ICW1_4BYTE        0x04  /* ���荞�݃x�N�^��4 byte */
#define _PIC_ICW1_8BYTE        0x00  /* ���荞�݃x�N�^��8 byte */
#define _PIC_ICW1_LELSENS      0x08  /* ���x���Z���V�e�B�u */
#define _PIC_ICW1_EDGSEND      0x00  /* �G�b�W�Z���V�e�B�u */
#define _PIC_ICW1_VALID        0x10  /* ICW1 bit4 is alway on */
/*
 *  Initialization Command Word 2  
 *  Vector Base address
 */
#define PIC1_VBASE_ADDR        0x20
#define PIC2_VBASE_ADDR        0x28
/*
+-------+---------------------------+
|Bit    |Function                   |
+-------+---------------------------+
|  7    |IR7 is connected to a Slave|
+-------+---------------------------+
|  6    |IR6 is connected to a Slave|
+-------+---------------------------+
|  5    |IR5 is connected to a Slave|
+-------+---------------------------+
|  4    |IR4 is connected to a Slave|
+-------+---------------------------+
|  3    |IR3 is connected to a Slave|
+-------+---------------------------+
|  2    |IR2 is connected to a Slave|
+-------+---------------------------+
|  1    |IR1 is connected to a Slave|
+-------+---------------------------+
|  0    |IR0 is connected to a Slave|
+-------+---------------------------+
        ICW3 Connection
*/
#define _PIC1_ICW3_IRQ0         0x00
#define _PIC1_ICW3_IRQ1         0x01
#define _PIC1_ICW3_IRQ2         0x02
#define _PIC1_ICW3_IRQ3         0x03
#define _PIC1_ICW3_IRQ4         0x04
#define _PIC1_ICW3_IRQ5         0x05
#define _PIC1_ICW3_IRQ6         0x06
#define _PIC1_ICW3_IRQ7         0x07

/* ICW3 for Slave Device: */
#define _PIC2_ICW3_SLAVE0       0x00  
#define _PIC2_ICW3_SLAVE1       0x01  
#define _PIC2_ICW3_SLAVE2       0x02  
#define _PIC2_ICW3_SLAVE3       0x03  
#define _PIC2_ICW3_SLAVE4       0x04  
#define _PIC2_ICW3_SLAVE5       0x05  
#define _PIC2_ICW3_SLAVE6       0x06  
#define _PIC2_ICW3_SLAVE7       0x07  
/*
 *  +------+--------------------------------------+
 *  |Bit(s)| Function                             |
 *  +------+--------------------------------------+
 *  | 7    |Reserved. Set to 0                    |
 *  +------+--------------------------------------+
 *  | 6    |Reserved. Set to 0                    |
 *  +------+--------------------------------------+
 *  | 5    |Reserved. Set to 0                    |
 *  +------+--------------------------------------+
 *  | 4    | 1  Special Fully Nested Mode         |
 *  |      | 0  Not Special Fully Nested Mode     |
 *  +------+--------------------------------------+
 *  |3:2   |0x  Non - Buffered Mode               |
 *  |      |10  Buffered Mode - Slave             |
 *  |      |11  Buffered Mode - Master            |
 *  +------+--------------------------------------+
 *  | 1    | 1  Auto EOI                          |
 *  |      | 0  Normal EOI                        |
 *  +------+--------------------------------------+
 *  | 0    | 1  8086/8080 Mode                    |
 *  |      | 0  MCS-80/85                         |
 *  +------+--------------------------------------+
 *
 *      ICW4 
 *
 */
#define _PIC_ICW4_MODE_X86     0x01     /* 80x86 mode */
#define _PIC_ICW4_MODE_MCS80   0x00     /* MCS 80/85 mode */
#define _PIC_ICW4_MODE_SFNM    0x10     /* special fully nested mode  */
#define _PIC_ICW4_MODE_SEQ     0x00     /* not special fully nested mode  */
#define _PIC_ICW4_EOI_AUTO     0x02     /* Auto EOI  */
#define _PIC_ICW4_EOI_NORMAL   0x00     /* Normal EOI  */
#define _PIC_ICW4_BUF_SLAVE    0x08     /* Buffered Mode - Slave */
#define _PIC_ICW4_BUF_MASTER   0x0c     /* Buffered Mode - Master */

/*
 * Initilization Codes
 */
#define PIC1_ICW1_CODE (_PIC_ICW1_VALID|_PIC_ICW1_8BYTE|_PIC_ICW1_EDGSEND|_PIC_ICW1_CASCDPIC|_PIC_ICW1_SENDICW4)
#define PIC1_ICW2_CODE PIC1_VBASE_ADDR
#define PIC1_ICW3_CODE _PIC1_ICW3_IRQ2
#define PIC1_ICW4_CODE (_PIC_ICW4_MODE_SFNM|_PIC_ICW4_EOI_NORMAL|_PIC_ICW4_MODE_X86)

#define PIC2_ICW1_CODE PIC1_ICW1_CODE  /*  �����R�[�h  */
#define PIC2_ICW2_CODE PIC2_VBASE_ADDR
#define PIC2_ICW3_CODE _PIC2_ICW3_SLAVE2
#define PIC2_ICW4_CODE (_PIC_ICW4_EOI_NORMAL|_PIC_ICW4_MODE_X86)

/* Operation Control Word1 */
#define PIC1_OCW1_ADDR PIC1_BASE_ADDR2
#define PIC1_OCW1_MASK_ALL  0xff
#define PIC1_OCW1_MASK_IRQ0 0x1
#define PIC1_OCW1_MASK_IRQ1 0x2
#define PIC1_OCW1_MASK_IRQ2 0x4
#define PIC1_OCW1_MASK_IRQ3 0x8
#define PIC1_OCW1_MASK_IRQ4 0x10
#define PIC1_OCW1_MASK_IRQ5 0x20
#define PIC1_OCW1_MASK_IRQ6 0x40
#define PIC1_OCW1_MASK_IRQ7 0x80
#define PIC2_OCW1_ADDR PIC2_BASE_ADDR2
#define PIC2_OCW1_MASK_ALL   0xff
#define PIC2_OCW1_MASK_IRQ8  0x1
#define PIC2_OCW1_MASK_IRQ9  0x2
#define PIC2_OCW1_MASK_IRQ10 0x4
#define PIC2_OCW1_MASK_IRQ11 0x8
#define PIC2_OCW1_MASK_IRQ12 0x10
#define PIC2_OCW1_MASK_IRQ13 0x20
#define PIC2_OCW1_MASK_IRQ14 0x40
#define PIC2_OCW1_MASK_IRQ15 0x80

/* Operation Control Word 2 (specify how EOI work)  */
#define PIC1_OCW2_ADDR PIC1_BASE_ADDR1
#define PIC2_OCW2_ADDR PIC2_BASE_ADDR1
#define PIC_OCW2_IRQ_MASK     0x07  /* Act on IRQ 7 or 15  */
#define PIC_OCW2_EOI_NONSPEC  0x20  
#define PIC_OCW2_EOI_NOP      0x40  
#define PIC_OCW2_EOI_SPEC     0x60  
#define PIC_OCW2_EOI_ROT_AUTO 0x80  
#define PIC_OCW2_EOI_ROT_NOSPEC 0xa0  
#define PIC_OCW2_EOI_SET_PRI  0xc0  
#define PIC_OCW2_EOI_ROT_SPEC 0xe0  
#define pic_mk_spec_eoi(irq) ( ( (irq) & (0x7) ) | (PIC_OCW2_EOI_SPEC) )
/* Operation Control Word 3 (Next register state):  */
#define PIC1_OCW3_ADDR PIC1_BASE_ADDR1
#define PIC2_OCW3_ADDR PIC2_BASE_ADDR1
#define PIC_OCW3_NEXT_IRR    0x2    /*  Next Read Intr. Request Reg. */
#define PIC_OCW3_NEXT_ISR    0x3    /*  Next Read In-Service .  Reg. */
#define PIC_OCW3_NEXT_POLL   0x4    /*  Poll Command */
#define PIC_OCW3_NEXT_NONPOL 0x0    /*  Non Poll Command */
#define PIC_OCW3_CONSTANT    0x8    /*  Need to set */
#define PIC_OCW3_RST_SPCMSK  0x40   /*  Reset Special mask*/
#define PIC_OCW3_SET_SPCMSK  0x60   /*  Set Special mask*/
#define pic_mk_ocw3code(func) ( (func) | (PIC_OCW3_CONSTANT) )

#endif  /*  __HOS_V4__IA32__pic_h__ */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
