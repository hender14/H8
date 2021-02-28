#include "iodefine.h"
#include "motor.h"

#define	D_MOTOR_KP					(0.0125)	//	���Q�C��
#define	D_MOTOR_DUTY_BASE			(10)		//	��{���s�f���[�e�B��
#define	D_MOTOR_DUTY_WIDTH			(5)			//	�ő�duty������
#define	D_MOTOR_TARGET_BRIGHTNESS	(435.0)		//	�ڕW�Z���T�l

//-----------------------------------------------------------------------------
//  �T�@�v�F������
//  ��  ���F�Ȃ�
//  �߂�l�F�Ȃ�
//-----------------------------------------------------------------------------
void Motor_init(void)
{
	TZ.TSTR.BIT.STR0	= 0;		// �^�C�}Z��ch0���J�E���g��~

	TZ0.TCR.BIT.TPSC	= 0;		//	�����Ȃ�
	TZ0.TCR.BIT.CKEG	= 0;		//	�����G�b�W�J�E���g
	TZ0.TCR.BIT.CCLR	= 1;		//	GRA�ŃR���y�A�}�b�`�N���A

	TZ.TPMR.BIT.PWMB0	= 1;		//	�E���[�^�[PWM���[�h
	TZ.TPMR.BIT.PWMC0	= 1;		//	�����[�^�[PWM���[�h

	//	High����Low�֐؂�ւ��g�`
	TZ.TOCR.BIT.TOB0	= 0;		//	PWM�g�`��High
	TZ.TOCR.BIT.TOC0	= 0;		//	PWM�g�`��High
	TZ0.POCR.BIT.POLB	= 0;		//	���[�A�N�e�B�u
	TZ0.POCR.BIT.POLC	= 0;		//	���[�A�N�e�B�u

	TZ.TOER.BIT.EB0		= 0;		//	FTIOB0�͏o��
	TZ.TOER.BIT.EC0		= 0;		//	FTIOC0�͏o��

	TZ0.TCNT			= 0;		//	�J�E���^�N���A
	TZ0.GRA				= 12000;	//	1ms������PWM�Ƃ��ē��삳����
	TZ0.GRB				= 0;		//	���ݒ�
	TZ0.GRC				= 0;		//	���ݒ�
}

//-----------------------------------------------------------------------------
//  �T�@�v�F���s�J�n
//  ��  ���Fdir		����	E_MOTOR_FORWARD		�O��
//							E_MOTOR_BACKARD		���
//  						E_MOTOR_TURN_RIGHT	�E��]
//							E_MOTOR_TURN_LEFT	����]
//			duty	�f���[�e�B��(0 - 99)
//  �߂�l�F0	����
//			-1	�ُ�
//-----------------------------------------------------------------------------
int Motor_runStart(E_MOTOR_DIR dir, unsigned char duty)
{
	//	�f���[�e�B��100%�ȏ�ُ͈툵��
	if (duty >= 100)
	{
		return -1;
	}

	//	���s�����ɏ]�����|�[�g�؂�ւ�
	if (dir == E_MOTOR_FORWARD)
	{
		//	�E���[�^�[�O�i
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 0;

		//	�����[�^�[�O�i
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	}
	else if (dir == E_MOTOR_BACKARD)
	{
		//	�E���[�^�[���
		IO.PDR3.BIT.B0 = 0;
		IO.PDR3.BIT.B1 = 1;

		//	�����[�^�[���
		IO.PDR3.BIT.B2 = 0;
		IO.PDR3.BIT.B3 = 1;
	}
	else if (dir == E_MOTOR_TURN_RIGHT)
	{
		//	�E���[�^�[���
		IO.PDR3.BIT.B0 = 0;
		IO.PDR3.BIT.B1 = 1;

		//	�����[�^�[�O�i
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	}
	else if (dir == E_MOTOR_TURN_LEFT)
	{
		//	�E���[�^�[�O�i
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 0;

		//	�����[�^�[���
		IO.PDR3.BIT.B2 = 0;
		IO.PDR3.BIT.B3 = 1;
	}
	else
	{
		return -1;
	}

	//	GRA�̎������W�X�^���x�[�X�Ƀf���[�e�B��̊�����ݒ�
	TZ0.GRB	= TZ0.GRA * (duty / 100.0);
	TZ0.GRC	= TZ0.GRA * (duty / 100.0);

	TZ.TSTR.BIT.STR0 = 1;		// �^�C�}Z��ch0���J�E���g�J�n����PWM����J�n

	return 0;
}

//-----------------------------------------------------------------------------
//  �T�@�v�FON-OFF���䑖�s�J�n
//  ��  ���Fbrightness		���Z���T�l
//			duty			�f���[�e�B��(0 - 99)
//  �߂�l�F0	����
//			-1	�ُ�
//-----------------------------------------------------------------------------
int Motor_runOnOff(unsigned short right, unsigned char left)
{

//	if (right < 99)	{	//	���Ȃ獶������
	
		//	�E���[�^�[�O�i
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 0;

		//	�����[�^�[�O�i
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	
/*	else						//	���Ȃ�E������
	{
		//	�E���[�^�[��~
		IO.PDR3.BIT.B0 = 1;
		IO.PDR3.BIT.B1 = 1;

		//	�����[�^�[�O�i
		IO.PDR3.BIT.B2 = 1;
		IO.PDR3.BIT.B3 = 0;
	}
*/
	//	GRA�̎������W�X�^���x�[�X�Ƀf���[�e�B��̊�����ݒ�
	TZ0.GRB	= TZ0.GRA * (right / 100.0);
	TZ0.GRC	= TZ0.GRA * (left / 100.0);

	TZ.TSTR.BIT.STR0 = 1;		// �^�C�}Z��ch0���J�E���g�J�n����PWM����J�n

	return 0;
}

//-----------------------------------------------------------------------------
//  �T�@�v�FP���䑖�s�J�n
//  ��  ���Fbrightness		���Z���T�l
//  �߂�l�F0	����
//			-1	�ُ�
//-----------------------------------------------------------------------------
int Motor_runPcon(unsigned short brightness)
{
	short dutyDiff;

	//	�E���[�^�[�O�i
	IO.PDR3.BIT.B0 = 1;
	IO.PDR3.BIT.B1 = 0;

	//	�����[�^�[�O�i
	IO.PDR3.BIT.B2 = 1;
	IO.PDR3.BIT.B3 = 0;

	//	�ڕW�ɑ΂���duty����ʂ̎Z�o
	dutyDiff = (D_MOTOR_TARGET_BRIGHTNESS - brightness) * D_MOTOR_KP;

	//	�ő咲��duty�����ł̕␳����
	if (dutyDiff > D_MOTOR_DUTY_WIDTH)
	{
		dutyDiff = D_MOTOR_DUTY_WIDTH;
	}
	else if (dutyDiff < -D_MOTOR_DUTY_WIDTH)
	{
		dutyDiff = -D_MOTOR_DUTY_WIDTH;
	}

	//	GRA�̎������W�X�^���x�[�X�Ƀf���[�e�B��̊�����ݒ�
	TZ0.GRB	= TZ0.GRA * ((D_MOTOR_DUTY_BASE - dutyDiff) / 100.0);	//	�E
	TZ0.GRC	= TZ0.GRA * ((D_MOTOR_DUTY_BASE + dutyDiff) / 100.0);	//	��

	TZ.TSTR.BIT.STR0 = 1;	// �^�C�}Z��ch0���J�E���g�J�n����PWM����J�n

	return 0;
}

//-----------------------------------------------------------------------------
//  �T�@�v�F���s��~
//  ��  ���F�Ȃ�
//  �߂�l�F0	����
//			-1	�ُ�
//-----------------------------------------------------------------------------
int Motor_runStop(void)
{
	//	�E���[�^�[��~
	IO.PDR3.BIT.B0 = 1;
	IO.PDR3.BIT.B1 = 1;

	//	�����[�^�[��~
	IO.PDR3.BIT.B2 = 1;
	IO.PDR3.BIT.B3 = 1;

	TZ.TSTR.BIT.STR0 = 0;		// �^�C�}Z��ch0���J�E���g��~����PWM�����~

	return 0;
}

