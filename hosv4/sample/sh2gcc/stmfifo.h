/* ------------------------------------------------------------------------ */
/*  �X�g���[���f�[�^�p FIFO�o�b�t�@                                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __stmfifo_h__
#define __stmfifo_h__


/* FIFO�o�b�t�@ */
typedef struct t_stmfifo
{
	UB  *buf;		/* �o�b�t�@�p�������̐擪�A�h���X */
	INT bufsz;		/* �o�b�t�@�p�������̃T�C�Y */
	INT head;		/* �f�[�^�擪�ʒu */
	INT tail;		/* �f�[�^�����ʒu */
} T_STMFIFO;


#ifdef __cplusplus
extern "C" {
#endif

void stmfifo_cre_fifo(T_STMFIFO *this, UB *buf, INT bufsz);		/* �R���X�g���N�^ */
void stmfifo_del_fifo(T_STMFIFO *this);							/* �f�X�g���N�^ */

ER   stmfifo_snd_chr(T_STMFIFO *this, UB chr);					/* �P�L�����N�^�������� */
ER   stmfifo_rcv_chr(T_STMFIFO *this, UB *p_chr);				/* �P�L�����N�^�ǂݍ��� */

#ifdef __cplusplus
}
#endif


#endif	/* __stmfifo_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
