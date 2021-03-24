/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "kernel.h"
#include "kernel_id.h"
#include "h83664f.h"
#include "h8t_sci.h"
#include <stdio.h>
#include "ostimer.h"
#include "led.h"
#include "lsen.h"
#include "motor.h"

//  �e�C�x���g��`
#define dis_0_flg     (0x0001)    // ��LED�_��
#define dis_L_flg     (0x0002)    // ��LED����
#define dis_R_flg     (0x0004)    // ��LED�_��
#define dis_S_flg     (0x0008)    // ��LED����

#define qin 0 // ���1
#define qleft 1 // ���2
#define qright 2 // ���3
#define qst 3 // ���5
#define NIL -1 //����`
#define dis_0 0 //���͋L��0
#define dis_L 1 //���͋L��1
#define dis_R 2// ���͋L��2
#define dis_S 3// ���͋L��3
#define State_Num 4 //��Ԑ�
#define Input_Num 4//���͋L����
int NowSt = qin; //�������
int Delta[State_Num][Input_Num] = {{qin, qleft, qright, qst}, {qin, qleft, qright, qst}, {qin, qleft, qright, qst}, {qin, qleft, qright, qst}}; //��Ԋ֐�

//  �S�C�x���g�p�^�[��
#define D_FLG1_ALLPTN ( qin     |   \
                        qright    |   \
                        qleft    |   \
                        qst   )
//------------------------------------------------
//  �^�錾
//------------------------------------------------

//  �f�[�^�L���[���M�p�̃e�[�u���f�[�^��`
const static S_LED_CTR gLedCtrTbl[] =
{
    { D_LED_KIND_ORANGE,    D_LED_LIGHT_ON,     1000    },
    { D_LED_KIND_GREEN,     D_LED_LIGHT_ON,     1000    },
    { D_LED_KIND_ORANGE,    D_LED_LIGHT_OFF,    2000    },
    { D_LED_KIND_GREEN,     D_LED_LIGHT_OFF,    2000    },
};

//------------------------------------------------
//  �����v���g�^�C�v�錾
//------------------------------------------------


//------------------------------------------------
//  �V�X�e���G���g���[�|�C���g
//------------------------------------------------
int main(void)
{
    // HOS�N��
    sta_hos();

    return 0;
}

//------------------------------------------------
//  �T  �v�FMAIN�^�X�N
//------------------------------------------------

int state_func(int st, int c)
{
    return Delta[st][c];
}

void output(int st) //switch���ɂ�镪��
{
    switch (st) { 
        case qin  : Motor_runOnOff(30, 30);
            break;
        case qright : Motor_runOnOff(0, 30);
            break;
	    case qleft : Motor_runOnOff(30, 0);
            break;
        case qst : Motor_runStop();
            break;  
        default : break;
    } 
}

void MAIN(VP_INT exinf)
{
	FLGPTN  flg = 0; //�t���O����
	int x;

    while(1)
    {
			
    	wai_flg(FLGID_FLG1, D_FLG1_ALLPTN, TWF_ORW, &flg);	

		if ((flg & dis_S_flg) == dis_S_flg)
			x = dis_S;

		else if ((flg & dis_R_flg) == dis_R_flg)
			x = dis_R;
		
		else if ((flg & dis_L_flg) == dis_L_flg)
			x = dis_L;
		
		else if ((flg & dis_0_flg) == dis_0_flg)
			x = dis_0;
	  
	    NowSt = state_func(NowSt, x); //��ԑJ��
	    output(NowSt);
		
		dly_tsk(100);
    }
    return;
}

//------------------------------------------------
//  �T  �v�FTASK1�֐�
//------------------------------------------------
void TASK1(VP_INT exinf)
{		
    while(1)
    {	
		unsigned short sen1;
        unsigned short sen2;
		
		Lsen_getSensor(&sen1, &sen2);
		
		if  ( sen1 < 900)
			{ if  ( sen2 < 900)
				set_flg(FLGID_FLG1, dis_S_flg);
			else
				set_flg(FLGID_FLG1, dis_R_flg);
            }
		else 
			{ if  ( sen2 < 900)
				set_flg(FLGID_FLG1, dis_L_flg);
			else
				set_flg(FLGID_FLG1, dis_0_flg);
			}	
    }
    return;
}

//------------------------------------------------
//  �T  �v�FTASK2�֐�
//------------------------------------------------

void TASK2(VP_INT exinf)
{
	int dis;
	
    while(1)
    {
		dis = SCI3_GetChar();
		
		if ( dis == 1 ) {
			set_flg(FLGID_FLG1, dis_S_flg);
			SCI3_PutChar(3);		
		} 
        else if ( dis == 2) {
			set_flg(FLGID_FLG1, dis_S_flg);
			SCI3_PutChar(4);
		} 
        else if ( dis == 0)  {
			SCI3_PutChar(5);
		}			
		dly_tsk(500);				
    }
    return;
}
//------------------------------------------------
//  �T  �v�F�V�X�e��������
//------------------------------------------------
void Main_init(VP_INT exinf)
{
    //---------------------------------------------------
    //  �E�H�b�`�h�b�O�^�C�}�̒�~(�����Ȃ�����)
    //---------------------------------------------------
    WDT.TCSRWD.BYTE = 0x92;
    WDT.TCSRWD.BYTE = 0x92;
    //---------------------------------------------------
    //  PCR�̐ݒ�(PCR�͏������ݐ�p���W�X�^)
    //---------------------------------------------------
    IO.PCR3         = 0x0F;     //  P30,P31,P32,P33���o��(���[�^�[��]��������)
    IO.PCR6         = 0x11;     //  P60,P64���o��
    IO.PCR7         = 0x00;     //  P74�����
    //---------------------------------------------------
    //  ���W���[���̏�����(�e���W���[���̏����������{)
    //---------------------------------------------------
    Led_init();
    Sw_init();
    Lsen_init();
    Sci_init();
    Spk_init();
    Motor_init();
//	output(NowSt);
}

//------------------------------------------------

/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
