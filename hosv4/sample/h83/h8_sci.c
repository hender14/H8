/* ------------------------------------------------------------------------ */
/*  H8/3048�p SCI���䃉�C�u����                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "kernel.h"
#include "h8_3048.h"
#include "h8_sci.h"



/* �g�p�|�[�g�̒�` */
#ifdef __USE_SCI0
#define SMR     SMR0
#define BRR     BRR0
#define SCR     SCR0
#define TDR     TDR0
#define SSR     SSR0
#define RDR     RDR0
#else
#define SMR     SMR1
#define BRR     BRR1
#define SCR     SCR1
#define TDR     TDR1
#define SSR     SSR1
#define RDR     RDR1
#endif

#define RECV_BUFSIZE	32		/* ��M�o�b�t�@�̃T�C�Y */



static unsigned char recv_buf[32];
static int head;
static int tail;



/* SCI������ */
void Sci_Initialize(unsigned char rate)
{
	volatile int v;
	int i;
	
	/* SCI������ */
	SCR  = 0x00;
	SMR  = 0x00;
	BRR  = rate;
	for ( i = 0; i < 280; i++ )
		v++;
	SCR  = 0x70;
	SSR &= 0x80;
	
	/* ��M�o�b�t�@������ */
	head = 0;
	tail = 0;
}


/* �P�����o�� */
void Sci_PutChar(char c)
{
	while ( !(SSR & 0x80) )
		;
	
	TDR  = c;
	SSR &= 0x7f;
}


/* �P�������� */
int Sci_GetChar(void)
{
	if ( head == tail )
	{
		return -1;
	}
	
	return recv_buf[head++];
}


/* SCI��M���荞�� */
void Sci_RxiHandler(VP_INT exinf)
{
	unsigned char c;
	int next;
	
	/* 1������M */
	c = RDR;
	SSR &= 0xbf;
	
	/* ���̖����ʒu���v�Z */
	next = tail + 1;
	if ( next >= RECV_BUFSIZE )
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


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
