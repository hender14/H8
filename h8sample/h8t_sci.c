/* ------------------------------------------------------------------------ */
/*  H8/3664用 SCI3制御ライブラリ                                            */
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

#define RECV_BUFSIZE	32		/* 受信バッファのサイズ */

static unsigned char recv_buf[RECV_BUFSIZE];
static int head;
static int tail;
//-----------------------------------------------------------------------------
//  概　要：初期化
//  引  数：なし
//  戻り値：なし
//-----------------------------------------------------------------------------
void Sci_init(void)
{
	long i;
	
	SCI3.SCR3.BIT.TE	= 0;	//	送信禁止
	SCI3.SCR3.BIT.RE	= 0;	//	受信禁止

	SCI3.SMR.BIT.CKS	= 0;	//	n = 0	(ボーレート:19200bps)

	SCI3.SMR.BIT.COM	= 0;	//	調歩同期式
	SCI3.SMR.BIT.CHR	= 0;	//	データ長8bit
	SCI3.SMR.BIT.PE		= 0;	//	パリティなし
	SCI3.SMR.BIT.PM		= 0;	//	偶数パリティ
	SCI3.SMR.BIT.STOP	= 0;	//	1stop bit
	SCI3.SMR.BIT.MP		= 0;	//	マルチディスエーブル
	
	SCI3.BRR			= 19;	//	N = 19	(ボーレート:19200bps)

	for (i=0 ; i<1000 ; i++);	//	1bit転送時間待ち

	SCI3.SCR3.BYTE	= 0x70;	//	送受信、受信割り込み許可
	IO.PMR1.BIT.TXD		= 1;	//	P22のポートをシリアル送信端子へ変更
//	Rx1BufferClear();
}

//-----------------------------------------------------------------------------
//  概　要：文字の送信
//  引  数：moji	送信したい文字
//  戻り値：0	正常
//			-1	異常
//-----------------------------------------------------------------------------
int Sci_putChar(char moji)
{
	while (SCI3.SSR.BIT.TDRE == 0);		//	転送可能待ち

	SCI3.TDR = moji;					//	対象文字のデータ転送要求

	while (SCI3.SSR.BIT.TEND == 0);		//	転送完了待ち

	return 0;
}

//-----------------------------------------------------------------------------
//  概　要：文字列の送信
//  引  数：str		送信したい文字列
//  戻り値：0	正常
//			-1	異常
//-----------------------------------------------------------------------------
int Sci_putString(char * str)
{
	if (str == NULL)
	{
		return -1;
	}

	//	順番に文字列終端まで1文字ずつ送信
	while (*str != '\0')
	{
		Sci_putChar(*str);
		str++;
	}

	return 0;
}

//-----------------------------------------------------------------------------
//  概　要：受信割り込み
//  引  数：割り込み拡張情報
//  戻り値：0	
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
//  概　要：受信呼び出し関数
//  引  数：*msg　受信したデータpointer
//  戻り値：0	
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
//  概　要：受信関数
//  引  数：無し
//  戻り値：0	
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
//  概　要：受信関数初期化
//  引  数：無し
//  戻り値：0	
//			-1	
//-----------------------------------------------------------------------------
void Rx1BufferClear(void)
{
	rx1_buff.start_index = 0;
	rx1_buff.data_count = 0;
}

//-----------------------------------------------------------------------------


/* １文字出力 */
void SCI3_PutChar(char c)
{
	while ( !(SCI3.SSR.BYTE & 0x80) )
		;

	SCI3.TDR  = c;
}

/* １文字入力 */
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

/* SCI受信割り込み */
void SCI3_RxiHandler(VP_INT exinf)
{
	unsigned char c;
	int next;
	
	/* 1文字受信 */
	c = SCI3.RDR;
	
	/* 次の末尾位置を計算 */
	next = tail + 1;
	if ( next == RECV_BUFSIZE )
	{
		next = 0;
	}
	
	/* オーバーフローチェック */
	if ( next == head )
	{
		return;
	}
	
	/* 受信バッファに格納 */
	recv_buf[tail] = c;
	tail = next;
}