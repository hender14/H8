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
#include "sw.h"
#include "lsen.h"
#include "spk.h"
#include "motor.h"

//  各イベント定義
#define dis_0_flg     (0x0001)    // 緑LED点灯
#define dis_L_flg     (0x0002)    // 緑LED消灯
#define dis_R_flg     (0x0004)    // 橙LED点灯
#define dis_S_flg     (0x0008)    // 橙LED消灯

#define qin 0 // 状態1
#define qleft 1 // 状態2
#define qright 2 // 状態3
//#define qbrake 3 // 状態4
#define qst 3 // 状態5
#define NIL -1 //未定義
#define dis_0 0 //　入力記号0
#define dis_L 1 //　入力記号1
#define dis_R 2// 入力記号2
#define dis_S 3// 入力記号3
#define State_Num 4 //状態数
#define Input_Num 4//入力記号数
int NowSt = qin; //初期状態
int Delta[State_Num][Input_Num] = {{qin, qleft, qright, qst}, {qin, qleft, qright, qst}, {qin, qleft, qright, qst}, {qin, qleft, qright, qst}}; //状態関数
//int Delta[3][2] = {{A, B, C}, {A, C, B}}; //状態関数
//char [State_Num][6] = {"dis_0", "dis_B","dis_A"}; //出力関数


//  全イベントパターン
#define D_FLG1_ALLPTN ( qin     |   \
                        qright    |   \
                        qleft    |   \
                        qst   )
//------------------------------------------------
//  型宣言
//------------------------------------------------
//  スピーカー制御用のメッセージパケット定義
typedef struct
{
    T_MSG       msg;    //  メッセージヘッダ
    E_SPK_SCALE scale;  //  アプリケーションデータ
} S_MSGPK_SPK;

//  グローバル変数としてメッセージパケットを作成
static S_MSGPK_SPK msgpkt;
static int flag = 0;

//データキュー用型定義
typedef struct
{
    int     ledKind;    //  橙/緑LED
    int     ledOnoff;   //  ON/OFF
    RELTIM  time;       //  制御時間
} S_LED_CTR;

//  データキュー送信用のテーブルデータ定義
const static S_LED_CTR gLedCtrTbl[] =
{
    { D_LED_KIND_ORANGE,    D_LED_LIGHT_ON,     1000    },
    { D_LED_KIND_GREEN,     D_LED_LIGHT_ON,     1000    },
    { D_LED_KIND_ORANGE,    D_LED_LIGHT_OFF,    2000    },
    { D_LED_KIND_GREEN,     D_LED_LIGHT_OFF,    2000    },
};
//セマフォ型定義
typedef struct
{
	int	x;
	int y;
} S_POS;

S_POS globalPos;

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
    //  メッセージパケットのポインタ定義
 //   S_MSGPK_SPK * pMsg = NULL;

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

/*        rcv_mbx(MBXID_MBX1, (T_MSG **)&pMsg);
        Spk_start(pMsg->scale);
*/

    }

    return;
}

//------------------------------------------------
//  概  要：練習用TASK1関数
//------------------------------------------------
void TASK1(VP_INT exinf)
{
//	E_SPK_SCALE scale; //メールボックスの関数定義
/*　データキュー定義
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


/*	データキュー処理
        rcv_dtq(DTQID_DTQ1, &data);

        //  データフォーマット解析処理
        ledKind     = (data >> 24) & 0xFF;
        ledOnoff    = (data >> 16) & 0xFF; 
        time        = data & 0xFFFF;

        Led_setLight(ledKind, ledOnoff);
        dly_tsk(time);
*/

// フラグ処理
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
		
/*オレンジLEDを切り替え
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
//  概  要：練習用TASK2関数
//------------------------------------------------

void TASK2(VP_INT exinf)
{
/* イベントフラグ処理
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
		
/*　データキュー処理
        //  データフォーマット構築処理
        data =  ((VP_INT)gLedCtrTbl[i].ledKind  << 24)  |
                ((VP_INT)gLedCtrTbl[i].ledOnoff << 16)  |
                ((VP_INT)gLedCtrTbl[i].time);

        //  データキューの送信
        snd_dtq(DTQID_DTQ1, data);

        //  テーブルデータの参照位置変更
        i++;
        if (i >= sizeof(gLedCtrTbl) / sizeof(gLedCtrTbl[0]))
        {
            i = 0;
        }

        //  100ミリ秒待ち
        dly_tsk(100);
*/
		
/*　フラグ処理
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
//  概  要：練習用周期ハンドラ関数
//------------------------------------------------
void CYC1(VP_INT exinf)
{	
/*	フラグ処理
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
//  概  要：練習用アラームハンドラ関数
//------------------------------------------------
void ALM1(VP_INT exinf)
{
	Led_setLight(D_LED_KIND_GREEN, D_LED_LIGHT_ON);

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
