/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
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

//  各イベント定義
#define dis_0_flg     (0x0001)    // 緑LED点灯
#define dis_L_flg     (0x0002)    // 緑LED消灯
#define dis_R_flg     (0x0004)    // 橙LED点灯
#define dis_S_flg     (0x0008)    // 橙LED消灯

#define qin 0 // 状態1
#define qleft 1 // 状態2
#define qright 2 // 状態3
#define qst 3 // 状態5
#define NIL -1 //未定義
#define dis_0 0 //入力記号0
#define dis_L 1 //入力記号1
#define dis_R 2// 入力記号2
#define dis_S 3// 入力記号3
#define State_Num 4 //状態数
#define Input_Num 4//入力記号数
int NowSt = qin; //初期状態
int Delta[State_Num][Input_Num] = {{qin, qleft, qright, qst}, {qin, qleft, qright, qst}, {qin, qleft, qright, qst}, {qin, qleft, qright, qst}}; //状態関数

//  全イベントパターン
#define D_FLG1_ALLPTN ( qin     |   \
                        qright    |   \
                        qleft    |   \
                        qst   )
//------------------------------------------------
//  型宣言
//------------------------------------------------

//  データキュー送信用のテーブルデータ定義
const static S_LED_CTR gLedCtrTbl[] =
{
    { D_LED_KIND_ORANGE,    D_LED_LIGHT_ON,     1000    },
    { D_LED_KIND_GREEN,     D_LED_LIGHT_ON,     1000    },
    { D_LED_KIND_ORANGE,    D_LED_LIGHT_OFF,    2000    },
    { D_LED_KIND_GREEN,     D_LED_LIGHT_OFF,    2000    },
};

//------------------------------------------------
//  内部プロトタイプ宣言
//------------------------------------------------


//------------------------------------------------
//  システムエントリーポイント
//------------------------------------------------
int main(void)
{
    // HOS起動
    sta_hos();

    return 0;
}

//------------------------------------------------
//  概  要：MAINタスク
//------------------------------------------------

int state_func(int st, int c)
{
    return Delta[st][c];
}

void output(int st) //switch分による分岐
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
	FLGPTN  flg = 0; //フラグ処理
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
	  
	    NowSt = state_func(NowSt, x); //状態遷移
	    output(NowSt);
		
		dly_tsk(100);
    }
    return;
}

//------------------------------------------------
//  概  要：TASK1関数
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
//  概  要：TASK2関数
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
//  概  要：システム初期化
//------------------------------------------------
void Main_init(VP_INT exinf)
{
    //---------------------------------------------------
    //  ウォッチドッグタイマの停止(消さないこと)
    //---------------------------------------------------
    WDT.TCSRWD.BYTE = 0x92;
    WDT.TCSRWD.BYTE = 0x92;
    //---------------------------------------------------
    //  PCRの設定(PCRは書き込み専用レジスタ)
    //---------------------------------------------------
    IO.PCR3         = 0x0F;     //  P30,P31,P32,P33を出力(モーター回転方向制御)
    IO.PCR6         = 0x11;     //  P60,P64を出力
    IO.PCR7         = 0x00;     //  P74を入力
    //---------------------------------------------------
    //  モジュールの初期化(各モジュールの初期化を実施)
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
