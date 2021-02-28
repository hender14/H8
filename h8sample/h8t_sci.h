#ifndef __H8TINY_SCI_H_
#define __H8TINY_SCI_H_
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  マクロ定義(Macro definition)
//-----------------------------------------------------------------------------
#define TXD1F SCI3.SSR.BIT.TDRE //　送信データフラグ
#define RXD1F SCI3.SSR.BIT.RDRF //　受信データフラグ
#define TD1D SCI3.TDR           //　送信データ
#define RD1D SCI3.RDR           //　受信データ
#define RERR SCI3.SCR3.BIT.RIE //　エラーフラグ

#define SCI_RX_BUFF_SIZE 32
#define SCI_RX_BUFF_MASK (SCI_RX_BUFF_SIZE-1)
//-----------------------------------------------------------------------------
//  型定義(Type definition)
//-----------------------------------------------------------------------------
	typedef struct{
		unsigned short start_index;
		unsigned short data_count;
		char data_buff[SCI_RX_BUFF_SIZE];
	} SciRxBuffer;
//-----------------------------------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//-----------------------------------------------------------------------------
void Sci_init(void);
/*
int Sci_putChar(char moji);
int Sci_putString(char * str);
int Sci1Rx1(char * msg);
char Sci1Read(void);
void Rx1BufferClear(void);
void Sci_RxiHandler(VP_INT exinf);
*/
void SCI3_RxiHandler(VP_INT exinf);		/* 受信割り込みハンドラ */
void SCI3_PutChar(char c);			/* １文字出力 */
int  SCI3_GetChar(void);			/* １文字入力 */
//-----------------------------------------------------------------------------
//#define Sci_RxiHandler SCI3_RxiHandler
//-----------------------------------------------------------------------------
#endif /* __H8TINY_SCI_H__ */
