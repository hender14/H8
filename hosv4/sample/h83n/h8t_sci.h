#ifndef __H8TINY_SCI_H_
#define __H8TINY_SCI_H_


/* SCI�ʐM���x��` (16MHz�̂Ƃ�) */
#define SCI_2400   207
#define SCI_4800   103
#define SCI_9600    51
#define SCI_19200   25
#define SCI_31250   15
#define SCI_38400   12
#define SCI_57600    8		/* �덷 -3.5% ���肬�肢���邩�� (^^;; */

/* SCI3 */
void SCI3_Initialize(unsigned char rate);	/* SCI3������ */
void SCI3_PutChar(char c);			/* �P�����o�� */

/* assign SCI3 for SCI*/
#define Sci_Initialize SCI3_Initialize
#define Sci_PutChar SCI3_PutChar

#endif /* __H8TINY_SCI_H__ */
