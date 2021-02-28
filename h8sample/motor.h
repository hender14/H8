#ifndef MOTOR_H
#define	MOTOR_H
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  マクロ定義(Macro definition)
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  型定義(Type definition)
//-----------------------------------------------------------------------------
typedef enum
{
	E_MOTOR_FORWARD = 0,		//	前方
	E_MOTOR_BACKARD,			//	後方
	E_MOTOR_TURN_RIGHT,			//	右回転
	E_MOTOR_TURN_LEFT,			//	左回転
} E_MOTOR_DIR;

//-----------------------------------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//-----------------------------------------------------------------------------
void Motor_init(void);
int Motor_runStart(E_MOTOR_DIR dir, unsigned char duty);
int Motor_runOnOff(unsigned short brightness, unsigned char duty);
int Motor_runPcon(unsigned short brightness);
int Motor_runStop(void);
//-----------------------------------------------------------------------------
#endif	// MOTOR_H