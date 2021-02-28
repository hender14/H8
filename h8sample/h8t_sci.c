/* ------------------------------------------------------------------------ */
/*  H8/3664�p SCI3���䃉�C�u����                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "kernel.h"
#include "kernel_id.h"
#include "h83664f.h"
#include "h8t_sci.h"
#include <stdio.h>
static SciRxBuffer rx1_buff;

#define RECV_BUFSIZE	32		/* ��M�o�b�t�@�̃T�C�Y */

static unsigned char recv_buf[RECV_BUFSIZE];
static int head;
static int tail;
//-----------------------------------------------------------------------------
//  �T�@�v�F������
//  ��  ���F�Ȃ�
//  �߂�l�F�Ȃ�
//-----------------------------------------------------------------------------
void Sci_init(void)
{
	long i;
	
	SCI3.SCR3.BIT.TE	= 0;	//	���M�֎~
	SCI3.SCR3.BIT.RE	= 0;	//	��M�֎~

	SCI3.SMR.BIT.CKS	= 0;	//	n = 0	(�{�[���[�g:19200bps)

	SCI3.SMR.BIT.COM	= 0;	//	����������
	SCI3.SMR.BIT.CHR	= 0;	//	�f�[�^��8bit
	SCI3.SMR.BIT.PE		= 0;	//	�p���e�B�Ȃ�
	SCI3.SMR.BIT.PM		= 0;	//	�����p���e�B
	SCI3.SMR.BIT.STOP	= 0;	//	1stop bit
	SCI3.SMR.BIT.MP		= 0;	//	�}���`�f�B�X�G�[�u��
	
	SCI3.BRR			= 19;	//	N = 19	(�{�[���[�g:19200bps)

	for (i=0 ; i<1000 ; i++);	//	1bit�]�����ԑ҂�

	SCI3.SCR3.BYTE	= 0x70;	//	����M�A��M���荞�݋���
	IO.PMR1.BIT.TXD		= 1;	//	P22�̃|�[�g���V���A�����M�[�q�֕ύX
//	Rx1BufferClear();
}

//-----------------------------------------------------------------------------
//  �T�@�v�F�����̑��M
//  ��  ���Fmoji	���M����������
//  �߂�l�F0	����
//			-1	�ُ�
//-----------------------------------------------------------------------------
int Sci_putChar(char moji)
{
	while (SCI3.SSR.BIT.TDRE == 0);		//	�]���\�҂�

	SCI3.TDR = moji;					//	�Ώە����̃f�[�^�]���v��

	while (SCI3.SSR.BIT.TEND == 0);		//	�]�������҂�

	return 0;
}

//-----------------------------------------------------------------------------
//  �T�@�v�F������̑��M
//  ��  ���Fstr		���M������������
//  �߂�l�F0	����
//			-1	�ُ�
//-----------------------------------------------------------------------------
int Sci_putString(char * str)
{
	if (str == NULL)
	{
		return -1;
	}

	//	���Ԃɕ�����I�[�܂�1���������M
	while (*str != '\0')
	{
		Sci_putChar(*str);
		str++;
	}

	return 0;
}

//-----------------------------------------------------------------------------
//  �T�@�v�F��M���荞��
//  ��  ���F���荞�݊g�����
//  �߂�l�F0	
//			-1	
//-----------------------------------------------------------------------------
void Sci_RxiHandler(VP_INT exinf)
{
	char msg;
	int index;
	
	if (RXD1F) {
		msg = RD1D;
		if (rx1_buff.data_count < SCI_RX_BUFF_SIZE) {
			index = (rx1_buff.start_index + rx1_buff.data_count) & SCI_RX_BUFF_MASK;
			rx1_buff.data_buff[index] = msg;
			rx1_buff.data_count++;
		}
	}
	if (RERR) {
			RERR = 0; }
}
//-----------------------------------------------------------------------------
//  �T�@�v�F��M�Ăяo���֐�
//  ��  ���F*msg�@��M�����f�[�^pointer
//  �߂�l�F0	
//			-1	
//-----------------------------------------------------------------------------
int Sci1Rx1(char *msg)
{
	if (rx1_buff.data_count > 0) {
		*msg = rx1_buff.data_buff[rx1_buff.start_index];
		rx1_buff.start_index = (rx1_buff.start_index + 1) & SCI_RX_BUFF_MASK;
		rx1_buff.data_count--;
		return(0);
	}
	*msg = 0;
	return(-1);
}
//-----------------------------------------------------------------------------
//  �T�@�v�F��M�֐�
//  ��  ���F����
//  �߂�l�F0	
//			-1	
//-----------------------------------------------------------------------------
char Sci1Read(void)
{
	char c;
	while(Sci1Rx1(&c)) {
		;
	}
	return(c);
}

//-----------------------------------------------------------------------------
//  �T�@�v�F��M�֐�������
//  ��  ���F����
//  �߂�l�F0	
//			-1	
//-----------------------------------------------------------------------------
void Rx1BufferClear(void)
{
	rx1_buff.start_index = 0;
	rx1_buff.data_count = 0;
}

//-----------------------------------------------------------------------------


/* �P�����o�� */
void SCI3_PutChar(char c)
{
	while ( !(SCI3.SSR.BYTE & 0x80) )
		;

	SCI3.TDR  = c;
}

/* �P�������� */
int SCI3_GetChar(void)
{
	unsigned char c;

	if ( head == tail )
	{
		return -1;
	}

	c = recv_buf[head++];
	if ( head >= RECV_BUFSIZE )
	{
		head = 0;
	}
	
	return c;
}

/* SCI��M���荞�� */
void SCI3_RxiHandler(VP_INT exinf)
{
	unsigned char c;
	int next;
	
	/* 1������M */
	c = SCI3.RDR;
	
	/* ���̖����ʒu���v�Z */
	next = tail + 1;
	if ( next == RECV_BUFSIZE )
	{
		next = 0;
	}
	
	/* �I�[�o�[�t���[�`�F�b�N */
	if ( next == head )
	{
		return;
	}
	
	/* ��M�o�b�t�@�Ɋi�[ */
	recv_buf[tail] = c;
	tail = next;
}