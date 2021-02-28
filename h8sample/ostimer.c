/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*    H8/3664 �p OS�^�C�} (Timer A�𗘗p)                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "kernel.h"
#include "kernel_id.h"
#include "h83664f.h"
#include "ostimer.h"



//------------------------------------------------
//  �T  �v�FOS�^�C�}������
//------------------------------------------------
void Ostimer_init(VP_INT exinf)
{
	// 1ms�̃I�[�o�[�t���[���荞�ݗp�̐ݒ�
	TB1.TMB1.BIT.RLD = 1; // �I�[�g�����[�h�@�\�L��
	TB1.TMB1.BIT.CKS = 4; // ������/16��I��
	TB1.TCB1 = 256 - 187; // �����[�h�J�E���g�l

	//  �^�C�}B1�I�[�o�[�t���[���荞�݋���
	IENR2.BIT.IENTB1 = 1;

	return ;
}

//------------------------------------------------
//  �T  �v�F�I�[�o�[�t���[���荞�݃n���h��
//			1ms�Ԋu�Ŋ��荞�݃n���h������R�[�������
//			OS�^�C�}�Ƃ���OS�փ^�C���e�B�b�N������
//  ��  ���F�Ȃ�
//------------------------------------------------
void Ostimer_interruptHandler(VP_INT exinf)
{
	// ���荞�ݗv���t���O�N���A
	IRR2.BIT.IRRTB1 = 0;

	// 1ms�̃^�C���e�B�b�N����
	isig_tim();
}
