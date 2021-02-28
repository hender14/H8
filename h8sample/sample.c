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
#include "sw.h"
#include "lsen.h"
#include "spk.h"
#include "motor.h"

//  �e�C�x���g��`
#define dis_0_flg     (0x0001)    // ��LED�_��
#define dis_L_flg     (0x0002)    // ��LED����
#define dis_R_flg     (0x0004)    // ��LED�_��
#define dis_S_flg     (0x0008)    // ��LED����

#define qin 0 // ���1
#define qleft 1 // ���2
#define qright 2 // ���3
//#define qbrake 3 // ���4
#define qst 3 // ���5
#define NIL -1 //����`
#define dis_0 0 //�@���͋L��0
#define dis_L 1 //�@���͋L��1
#define dis_R 2// ���͋L��2
#define dis_S 3// ���͋L��3
#define State_Num 4 //��Ԑ�
#define Input_Num 4//���͋L����
int NowSt = qin; //�������
int Delta[State_Num][Input_Num] = {{qin, qleft, qright, qst}, {qin, qleft, qright, qst}, {qin, qleft, qright, qst}, {qin, qleft, qright, qst}}; //��Ԋ֐�
//int Delta[3][2] = {{A, B, C}, {A, C, B}}; //��Ԋ֐�
//char [State_Num][6] = {"dis_0", "dis_B","dis_A"}; //�o�͊֐�


//  �S�C�x���g�p�^�[��
#define D_FLG1_ALLPTN ( qin     |   \
                        qright    |   \
                        qleft    |   \
                        qst   )
//------------------------------------------------
//  �^�錾
//------------------------------------------------
//  �X�s�[�J�[����p�̃��b�Z�[�W�p�P�b�g��`
typedef struct
{
    T_MSG       msg;    //  ���b�Z�[�W�w�b�_
    E_SPK_SCALE scale;  //  �A�v���P�[�V�����f�[�^
} S_MSGPK_SPK;

//  �O���[�o���ϐ��Ƃ��ă��b�Z�[�W�p�P�b�g���쐬
static S_MSGPK_SPK msgpkt;
static int flag = 0;

//�f�[�^�L���[�p�^��`
typedef struct
{
    int     ledKind;    //  ��/��LED
    int     ledOnoff;   //  ON/OFF
    RELTIM  time;       //  ���䎞��
} S_LED_CTR;

//  �f�[�^�L���[���M�p�̃e�[�u���f�[�^��`
const static S_LED_CTR gLedCtrTbl[] =
{
    { D_LED_KIND_ORANGE,    D_LED_LIGHT_ON,     1000    },
    { D_LED_KIND_GREEN,     D_LED_LIGHT_ON,     1000    },
    { D_LED_KIND_ORANGE,    D_LED_LIGHT_OFF,    2000    },
    { D_LED_KIND_GREEN,     D_LED_LIGHT_OFF,    2000    },
};
//�Z�}�t�H�^��`
typedef struct
{
	int	x;
	int y;
} S_POS;

S_POS globalPos;

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
    //  ���b�Z�[�W�p�P�b�g�̃|�C���^��`
 //   S_MSGPK_SPK * pMsg = NULL;

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

/*        rcv_mbx(MBXID_MBX1, (T_MSG **)&pMsg);
        Spk_start(pMsg->scale);
*/

    }

    return;
}

//------------------------------------------------
//  �T  �v�F���K�pTASK1�֐�
//------------------------------------------------
void TASK1(VP_INT exinf)
{
//	E_SPK_SCALE scale; //���[���{�b�N�X�̊֐���`
/*�@�f�[�^�L���[��`
    VP_INT  data; 
    int     ledKind;
    int     ledOnoff; 
    RELTIM  time;     
*/	
		
    while(1)
    {	
		unsigned short sen1;
        unsigned short sen2;
		
		Lsen_getSensor(&sen1, &sen2);
		
		if  ( sen1 < 900)
			{ if  ( sen2 < 900)
//    			x = dis_S; 
				set_flg(FLGID_FLG1, dis_S_flg);
			else
//				x = dis_R;}
				set_flg(FLGID_FLG1, dis_R_flg);}
/*							
		else if (sen1 < 900)
			{ if  ( sen2 < 700)
//    			x = dis_L; 
				set_flg(FLGID_FLG1, dis_L_flg);
			else 
//				x = dis_B;}
				set_flg(FLGID_FLG1, dis_B_flg);}
*/		else 
			{ if  ( sen2 < 900)
//    			x = dis_L;
				set_flg(FLGID_FLG1, dis_L_flg);
/*			else if ( sen2 < 900)
//				x = dis_L;
				set_flg(FLGID_FLG1, dis_L_flg);
*/			else
//				x = dis_0;
				set_flg(FLGID_FLG1, dis_0_flg);
			}	


/*	�f�[�^�L���[����
        rcv_dtq(DTQID_DTQ1, &data);

        //  �f�[�^�t�H�[�}�b�g��͏���
        ledKind     = (data >> 24) & 0xFF;
        ledOnoff    = (data >> 16) & 0xFF; 
        time        = data & 0xFFFF;

        Led_setLight(ledKind, ledOnoff);
        dly_tsk(time);
*/

// �t���O����
/*        wai_flg(FLGID_FLG1, D_FLG1_ALLPTN, TWF_ORW, &flg);
      
        if ((flg & D_FLG1_GREEN_LED_ON) == D_FLG1_GREEN_LED_ON)
        {
            Led_setLight(D_LED_KIND_GREEN, D_LED_LIGHT_ON);
        }

        if ((flg & D_FLG1_GREEN_LED_OFF) == D_FLG1_GREEN_LED_OFF)
        {
            Led_setLight(D_LED_KIND_GREEN, D_LED_LIGHT_OFF);
        }

        if ((flg & D_FLG1_ORANGE_LED_ON) == D_FLG1_ORANGE_LED_ON)
        {
            Led_setLight(D_LED_KIND_ORANGE, D_LED_LIGHT_ON);
        }

        if ((flg & D_FLG1_ORANGE_LED_OFF) == D_FLG1_ORANGE_LED_OFF)
        {
            Led_setLight(D_LED_KIND_ORANGE, D_LED_LIGHT_OFF);
        }
				
*/
/*		for (scale = E_SPK_SCALE_DO ; scale <= E_SPK_SCALE_MI ; scale++)
        {
            msgpkt.scale = scale;
            snd_mbx(MBXID_MBX1, (T_MSG *)&msgpkt);
            dly_tsk(1000);
        }
*/
		
/*�I�����WLED��؂�ւ�
		long i;
    	int flg = 0;

        if (flg == 0)
        {
            Led_setLight(D_LED_KIND_ORANGE, D_LED_LIGHT_ON);
            flg = 1;
        }
        else
        {
            Led_setLight(D_LED_KIND_ORANGE, D_LED_LIGHT_OFF);
            flg = 0;
        }

        for (i=0 ; i < 5000000 ; i++);

        slp_tsk();
*/
    }
    return;
}

//------------------------------------------------
//  �T  �v�F���K�pTASK2�֐�
//------------------------------------------------

void TASK2(VP_INT exinf)
{
/* �C�x���g�t���O����
	VP_INT data;
    int i = 0;
*/
	int dis;
	
    while(1)
    {
		dis = SCI3_GetChar();
		
		if ( dis == 1 ) {
			set_flg(FLGID_FLG1, dis_S_flg);
			Led_setLight(D_LED_KIND_GREEN, D_LED_LIGHT_ON);
//			SCI3_PutChar(3);
		
		} else if ( dis == 2) {
			set_flg(FLGID_FLG1, dis_S_flg);
			Led_setLight(D_LED_KIND_ORANGE, D_LED_LIGHT_ON);
//			SCI3_PutChar(4);
		
		} else if ( dis == 0)  {
			Led_setLight(D_LED_KIND_ORANGE, D_LED_LIGHT_OFF);
			Led_setLight(D_LED_KIND_GREEN, D_LED_LIGHT_OFF);
//			SCI3_PutChar(5);
		}
			
		dly_tsk(500);
		
/*�@�f�[�^�L���[����
        //  �f�[�^�t�H�[�}�b�g�\�z����
        data =  ((VP_INT)gLedCtrTbl[i].ledKind  << 24)  |
                ((VP_INT)gLedCtrTbl[i].ledOnoff << 16)  |
                ((VP_INT)gLedCtrTbl[i].time);

        //  �f�[�^�L���[�̑��M
        snd_dtq(DTQID_DTQ1, data);

        //  �e�[�u���f�[�^�̎Q�ƈʒu�ύX
        i++;
        if (i >= sizeof(gLedCtrTbl) / sizeof(gLedCtrTbl[0]))
        {
            i = 0;
        }

        //  100�~���b�҂�
        dly_tsk(100);
*/
		
/*�@�t���O����
		if (Sw_getPressed() == D_SW_PRESSED_ON)
		{
			set_flg(FLGID_FLG1, D_FLG1_GREEN_LED_ON);	
		} else {
			set_flg(FLGID_FLG1, D_FLG1_GREEN_LED_OFF);
		}

        dly_tsk(100);
*/    }

    return;
}

//------------------------------------------------
//  �T  �v�F���K�p�����n���h���֐�
//------------------------------------------------
void CYC1(VP_INT exinf)
{	
/*	�t���O����
	if (flag == 0)
	{
		set_flg(FLGID_FLG1, D_FLG1_ORANGE_LED_ON);
		flag = 1;
		
	} else {
		set_flg(FLGID_FLG1, D_FLG1_ORANGE_LED_OFF);
		flag = 0;
	}
*/	
//	iwup_tsk(TSKID_TASK1);

}

//------------------------------------------------
//  �T  �v�F���K�p�A���[���n���h���֐�
//------------------------------------------------
void ALM1(VP_INT exinf)
{
	Led_setLight(D_LED_KIND_GREEN, D_LED_LIGHT_ON);

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
