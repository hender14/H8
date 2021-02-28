/* ------------------------------------------------------------------------ */
/*  SH7045 SCI����                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __sci_h__
#define __sci_h__


#define ID_SCI0			1
#define ID_SCI1			2

#define SCI_SND_BUFSZ	128
#define SCI_RCV_BUFSZ	128


#ifdef __cplusplus
extern "C" {
#endif

void    sci_init(VP_INT exinf);			/* ������ */
ER      sci_open(ID id, UB brr);		/* �I�[�v�� */
ER      sci_close(ID id);				/* �N���[�Y */
ER      sci_putc(ID id, UB chr);		/* �P�����o�� */
ER_UINT sci_puts(ID id, const UB *str);	/* ������o�� */
ER_UINT sci_getc(ID id);				/* �P�������� */
ER_UINT sci_gets(ID id, UB *str);		/* ��������� */

void    sci_snd_hdr(VP_INT exinf);		/* ���M���荞�݃n���h�� */
void    sci_rcv_hdr(VP_INT exinf);		/* ��M���荞�݃n���h�� */

#ifdef __cplusplus
}
#endif


#endif


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
