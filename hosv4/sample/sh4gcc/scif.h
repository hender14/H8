/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*  SH7750 SCIF����                                                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

/* �{�[���[�g�f�[�^ */
#define B9600  0xa2
#define B19200  0x50
#define B38400  0x28
#define B57600  0x1a
#define B115200  0x0c


#ifdef __cplusplus
extern "C" {
#endif

void scif_init( VP_INT);
void scif_open( int);
void scif_putc( int code);
void scif_puts( char *str);
int  scif_getc( void);

void    scif_snd_hdr(VP_INT exinf);	/* ���M���荞�݃n���h�� */
void    scif_rcv_hdr(VP_INT exinf);	/* ��M���荞�݃n���h�� */

#ifdef __cplusplus
}
#endif

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
