/* ------------------------------------------------------------------------ */
/*  �X�g���[���f�[�^�p FIFO�o�b�t�@                                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "stmfifo.h"



/* �R���X�g���N�^ */
void stmfifo_cre_fifo(
		T_STMFIFO *this,	/* FIFO�o�b�t�@�N���X�̃|�C���^ */
		UB        *buf,		/* ���蓖�Ă�o�b�t�@�������̃A�h���X */
		INT       bufsz)	/* ���蓖�Ă�o�b�t�@�������̃T�C�Y */
{
	this->buf   = buf;
	this->bufsz = bufsz;
	this->head  = 0;
	this->tail  = 0;
}


/* �f�X�g���N�^ */
void stmfifo_del_fifo(
		T_STMFIFO *this)	/* FIFO�o�b�t�@�N���X�̃|�C���^ */
{
	/* ���ɏ����͖��� */
}



/* �P�L�����N�^�������� */
ER stmfifo_snd_chr(
		T_STMFIFO *this,	/* FIFO�o�b�t�@�N���X�̃|�C���^ */
		UB        chr)		/* �������ރL�����N�^ */
{
	INT next_tail;
	
	/* ���̖����ʒu�v�Z */
	if ( this->tail + 1 < this->bufsz )
	{
		next_tail = this->tail + 1;
	}
	else
	{
		next_tail = 0;		/* �����O�o�b�t�@�����Ȃ�܂�Ԃ� */
	}
	
	/* �o�b�t�@�t���̃`�F�b�N */
	if ( next_tail == this->head )
	{
		return E_TMOUT;
	}
	
	/* �f�[�^�̒ǉ� */
	this->buf[this->tail] = chr;
	this->tail = next_tail;
	
	return E_OK;
}


/* �P�L�����N�^�ǂݍ��� */
ER stmfifo_rcv_chr(
		T_STMFIFO *this,	/* FIFO�o�b�t�@�N���X�̃|�C���^ */
		UB        *p_chr)	/* �P�L�����N�^��ǂݍ��ރ|�C���^ */
{
	/* �o�b�t�@�G���v�e�B�[�̃`�F�b�N */
	if ( this->head == this->tail )
	{
		return E_TMOUT;
	}
	
	/* �f�[�^�̓ǂݏo�� */
	*p_chr = this->buf[this->head];
	
	/* ���̐擪�ʒu�̐ݒ� */
	if ( this->head + 1 < this->bufsz )
	{
		this->head = this->head + 1;
	}
	else
	{
		this->head = 0;
	}
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
