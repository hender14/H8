#include "iodefine.h"
#include "motor.h"

#define	D_MOTOR_KP					(0.0125)	//	比例ゲイン
#define	D_MOTOR_DUTY_BASE			(10)		//	基本走行デューティ比
#define	D_MOTOR_DUTY_WIDTH			(5)			//	最大duty調整幅
#define	D_MOTOR_TARGET_BRIGHTNESS	(435.0)		//	目標センサ値

//-----------------------------------------------------------------------------
//  概　要：初期化
//  引  数：なし
//  戻り値：なし
//-----------------------------------------------------------------------------
void Motor_init(void)
{
	TZ.TSTR.BIT.STR0	= 0;		// タイマZのch0をカウント停止

	TZ0.TCR.BIT.TPSC	= 0;		//	分周なし
	TZ0.TCR.BIT.CKEG	= 0;		//	立上りエッジカウント
	TZ0.TCR.BIT.CCLR	= 1;		//	GRAでコンペアマッチクリア

	TZ.TPMR.BIT.PWMB0	= 1;		//	右モーターPWMモード
	TZ.TPMR.BIT.PWMC0	= 1;		//	左モーターPWMモード

	//	HighからLowへ切り替わる波形
	TZ.TOCR.BIT.TOB0	= 0;		//	PWM波形はHigh
	TZ.TOCR.BIT.TOC0	= 0;		//	PWM波形はHigh
	TZ0.POCR.BIT.POLB	= 0;		//	ローアクティブ
	TZ0.POCR.BIT.POLC	= 0;		//	ローアクティブ

	TZ.TOER.BIT.EB0		= 0;		//	FTIOB0は出力
	TZ.TOER.BIT.EC0		= 0;		//	FTIOC0は出力

	TZ0.TCNT			= 0;		//	カウンタクリア
	TZ0.GRA				= 12000;	//	1ms周期のPWMとして動作させる
	TZ0.GRB				= 0;		//	仮設定
	TZ0.GRC				= 0;		//	仮設定
}

//-----------------------------------------------------------------------------
//  概　要：走行開始
//  引  数：dir		方向	E_MOTOR_FORWARD		前方
//							E_MOTOR_BACKARD		後方
//  						E_MOTOR_TURN_RIGHT	右回転
//							E_MOTOR_TURN_LEFT	左回転
//			duty	デューティ比(0 - 99)
//  戻り値：0	正常
//			-1	異常
//-----------------------------------------------------------------------------
int Motor_runStart(E_MOTOR_DIR dir, unsigned char duty)
{
	//	デューティ比100%以上は異常扱い
	if (duty >= 100)
	{
		return -1;
	}

	//	走行方向に従ったポート切り替え
	if (dir == E_MOTOR_FORWARD)
	{
		//	右モーター前進
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 0;

		//	左モーター前進
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	}
	else if (dir == E_MOTOR_BACKARD)
	{
		//	右モーター後退
		IO.PDR3.BIT.B0 = 0;
		IO.PDR3.BIT.B1 = 1;

		//	左モーター後退
		IO.PDR3.BIT.B2 = 0;
		IO.PDR3.BIT.B3 = 1;
	}
	else if (dir == E_MOTOR_TURN_RIGHT)
	{
		//	右モーター後退
		IO.PDR3.BIT.B0 = 0;
		IO.PDR3.BIT.B1 = 1;

		//	左モーター前進
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	}
	else if (dir == E_MOTOR_TURN_LEFT)
	{
		//	右モーター前進
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 0;

		//	左モーター後退
		IO.PDR3.BIT.B2 = 0;
		IO.PDR3.BIT.B3 = 1;
	}
	else
	{
		return -1;
	}

	//	GRAの周期レジスタをベースにデューティ比の割合を設定
	TZ0.GRB	= TZ0.GRA * (duty / 100.0);
	TZ0.GRC	= TZ0.GRA * (duty / 100.0);

	TZ.TSTR.BIT.STR0 = 1;		// タイマZのch0をカウント開始してPWM動作開始

	return 0;
}

//-----------------------------------------------------------------------------
//  概　要：ON-OFF制御走行開始
//  引  数：brightness		光センサ値
//			duty			デューティ比(0 - 99)
//  戻り値：0	正常
//			-1	異常
//-----------------------------------------------------------------------------
int Motor_runOnOff(unsigned short right, unsigned char left)
{

//	if (right < 99)	{	//	黒なら左方向へ
	
		//	右モーター前進
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 0;

		//	左モーター前進
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	
/*	else						//	白なら右方向へ
	{
		//	右モーター停止
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 1;

		//	左モーター前進
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	}
*/
	//	GRAの周期レジスタをベースにデューティ比の割合を設定
	TZ0.GRB	= TZ0.GRA * (right / 100.0);
	TZ0.GRC	= TZ0.GRA * (left / 100.0);

	TZ.TSTR.BIT.STR0 = 1;		// タイマZのch0をカウント開始してPWM動作開始

	return 0;
}

//-----------------------------------------------------------------------------
//  概　要：P制御走行開始
//  引  数：brightness		光センサ値
//  戻り値：0	正常
//			-1	異常
//-----------------------------------------------------------------------------
int Motor_runPcon(unsigned short brightness)
{
	short dutyDiff;

	//	右モーター前進
	IO.PDR3.BIT.B0 = 1;
	IO.PDR3.BIT.B1 = 0;

	//	左モーター前進
	IO.PDR3.BIT.B2 = 1;
	IO.PDR3.BIT.B3 = 0;

	//	目標に対するduty制御量の算出
	dutyDiff = (D_MOTOR_TARGET_BRIGHTNESS - brightness) * D_MOTOR_KP;

	//	最大調整duty幅内での補正処理
	if (dutyDiff > D_MOTOR_DUTY_WIDTH)
	{
		dutyDiff = D_MOTOR_DUTY_WIDTH;
	}
	else if (dutyDiff < -D_MOTOR_DUTY_WIDTH)
	{
		dutyDiff = -D_MOTOR_DUTY_WIDTH;
	}

	//	GRAの周期レジスタをベースにデューティ比の割合を設定
	TZ0.GRB	= TZ0.GRA * ((D_MOTOR_DUTY_BASE - dutyDiff) / 100.0);	//	右
	TZ0.GRC	= TZ0.GRA * ((D_MOTOR_DUTY_BASE + dutyDiff) / 100.0);	//	左

	TZ.TSTR.BIT.STR0 = 1;	// タイマZのch0をカウント開始してPWM動作開始

	return 0;
}

//-----------------------------------------------------------------------------
//  概　要：走行停止
//  引  数：なし
//  戻り値：0	正常
//			-1	異常
//-----------------------------------------------------------------------------
int Motor_runStop(void)
{
	//	右モーター停止
	IO.PDR3.BIT.B0 = 1;
	IO.PDR3.BIT.B1 = 1;

	//	左モーター停止
	IO.PDR3.BIT.B2 = 1;
	IO.PDR3.BIT.B3 = 1;

	TZ.TSTR.BIT.STR0 = 0;		// タイマZのch0をカウント停止してPWM動作停止

	return 0;
}

