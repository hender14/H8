#include <stdio.h>
#include "iodefine.h"
#include "lsen.h"

//-----------------------------------------------------------------------------
//  �T�@�v�F������
//  ��  ���F�Ȃ�
//  �߂�l�F�Ȃ�
//-----------------------------------------------------------------------------
void Lsen_init(void)
{
	//	AD���䃌�W�X�^������
	AD.ADCSR.BYTE	= 0x00;		//	ADIE:0	���荞�݋֎~
								//	ADST:0	AD�ϊ���~
								//	SCAN:0	�P�ꃂ�[�h
								//	CKS :0	137�X�e�[�g
}

//-----------------------------------------------------------------------------
//  �T�@�v�F���Z���T�[��AD�l�擾
//  ��  ���Fsen1	�Z���T�[1�Ɋւ���AD�l(0-1023)
//			sen2	�Z���T�[2�Ɋւ���AD�l(0-1023)
//  �߂�l�F0	����
//			-1	�ُ�
//-----------------------------------------------------------------------------
int Lsen_getSensor(unsigned short * sen1, unsigned short * sen2)
{
	if (sen1 == NULL || sen2 == NULL)
	{
		return -1;
	}

	//-----------------------------------------
	//	���Z���T�[1��AD�ϊ�����
	//-----------------------------------------
	AD.ADCSR.BIT.CH		= 0;	//	�ϊ��`���l���w��
	AD.ADCSR.BIT.ADST	= 1;	//	AD�ϊ��J�n

	//	AD�ϊ������҂�
	while (AD.ADCSR.BIT.ADF == 0);

	AD.ADCSR.BIT.ADF = 0;		//	�����t���O�N���A
	*sen1 = AD.ADDRA >> 6;		//	AD�l�擾

	//-----------------------------------------
	//	���Z���T�[1��AD�ϊ�����
	//-----------------------------------------
	AD.ADCSR.BIT.CH		= 1;	//	�ϊ��`���l���w��
	AD.ADCSR.BIT.ADST	= 1;	//	AD�ϊ��J�n

	//	AD�ϊ������҂�
	while (AD.ADCSR.BIT.ADF == 0);

	AD.ADCSR.BIT.ADF = 0;		//	�����t���O�N���A
	*sen2= AD.ADDRB >> 6;		//	AD�l�擾

	return 0;
}