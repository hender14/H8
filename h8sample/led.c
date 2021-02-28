#include "iodefine.h"
#include "led.h"

//-----------------------------------------------------------------------------
//  概　要：初期化
//  引  数：なし
//  戻り値：なし
//-----------------------------------------------------------------------------
void Led_init(void)
{
	IO.PDR6.BIT.B0	= 1;		//	オレンジLEDの消灯
	IO.PDR6.BIT.B4	= 1;		//	グリーンLEDの消灯
}

//-----------------------------------------------------------------------------
//  概　要：LEDの点灯・消灯制御
//  引  数：kind    LEDの色種別
//			onoff	点灯・消灯状態
//  戻り値：0	正常
//			-1	異常
//-----------------------------------------------------------------------------
int Led_setLight(int kind, int onoff)
{
	if (kind == D_LED_KIND_ORANGE)
	{
		if (onoff == D_LED_LIGHT_OFF)
		{
			IO.PDR6.BIT.B0	= 1;
		}
		else
		{
			IO.PDR6.BIT.B0	= 0;
		}		
	}
	else if (kind == D_LED_KIND_GREEN)
	{
		if (onoff == D_LED_LIGHT_OFF)
		{
			IO.PDR6.BIT.B4	= 1;
		}
		else
		{
			IO.PDR6.BIT.B4	= 0;
		}
	}
	else
	{
		//	色指定が規定外の場合異常終了
		return -1;
	}
	
	return 0;
}
