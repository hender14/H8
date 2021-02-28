#ifndef __H8TINY_SCI_H_
#define __H8TINY_SCI_H_
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  �}�N����`(Macro definition)
//-----------------------------------------------------------------------------
#define TXD1F SCI3.SSR.BIT.TDRE //�@���M�f�[�^�t���O
#define RXD1F SCI3.SSR.BIT.RDRF //�@��M�f�[�^�t���O
#define TD1D SCI3.TDR           //�@���M�f�[�^
#define RD1D SCI3.RDR           //�@��M�f�[�^
#define RERR SCI3.SCR3.BIT.RIE //�@�G���[�t���O

#define SCI_RX_BUFF_SIZE 32
#define SCI_RX_BUFF_MASK (SCI_RX_BUFF_SIZE-1)
//-----------------------------------------------------------------------------
//  �^��`(Type definition)
//-----------------------------------------------------------------------------
	typedef struct{
		unsigned short start_index;
		unsigned short data_count;
		char data_buff[SCI_RX_BUFF_SIZE];
	} SciRxBuffer;
//-----------------------------------------------------------------------------
//  �v���g�^�C�v�錾(Prototype declaration)
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
void SCI3_RxiHandler(VP_INT exinf);		/* ��M���荞�݃n���h�� */
void SCI3_PutChar(char c);			/* �P�����o�� */
int  SCI3_GetChar(void);			/* �P�������� */
//-----------------------------------------------------------------------------
//#define Sci_RxiHandler SCI3_RxiHandler
//-----------------------------------------------------------------------------
#endif /* __H8TINY_SCI_H__ */
