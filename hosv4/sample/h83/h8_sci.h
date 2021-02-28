/* ------------------------------------------------------------------------ */
/*  H8/3048�p SCI���䃉�C�u����                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#ifndef __PROJECT_HOS__h8_sci_h__
#define __PROJECT_HOS__h8_sci_h__



/* SCI�ʐM���x��` (16MHz�̂Ƃ�) */
#define SCI_2400   207
#define SCI_4800   103
#define SCI_9600    51
#define SCI_19200   25
#define SCI_31250   15
#define SCI_38400   12
#define SCI_57600    8		/* �덷 -3.5% ���肬�肢���邩�� (^^;; */



/* SCI */
void Sci_Initialize(unsigned char rate);	/* SCI������ */
void Sci_PutChar(char c);					/* �P�����o�� */
int  Sci_GetChar(void);						/* �P�������� */
void Sci_RxiHandler(VP_INT exinf);			/* SCI��M���荞�� */


#endif	/* __PROJECT_HOS__h8_sci_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
