/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e�����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* �^�C�}���X�g�Ǘ� */
T_KERNEL_TIM *kernel_tml_head;		/* �^�C�}���X�g�擪�ʒu */
T_KERNEL_TIM *kernel_tml_ptr;		/* �^�C�}���X�g�|�C���^ */



/* �^�C���e�B�b�N�̋��� */
ER isig_tim(void)
{
	T_KERNEL_TIM* tim_ptr;
	UW            prev_tim;
	RELTIM        tic;

	/* ���Z����^�C���e�B�b�N���Z�o */
	/* �Ⴆ�� 10/3 ms �����Ȃ� 3, 3, 4, 3, 3, 4, ... �ƃJ�E���g���Ă��� */
	kernel_tic_cnt--;
	if ( kernel_tic_cnt < kernel_tic_mod )
	{
		tic = kernel_tic_div + 1;	/* ����؂�Ȃ�����␳ */
	}
	else
	{
		tic = kernel_tic_div;
	}
	if ( kernel_tic_cnt == 0 )
	{
		kernel_tic_cnt = kernel_tic_deno;
	}

	mknl_loc_sys();		/* �V�X�e���̃��b�N */

	/* �V�X�e���^�C���ɉ��Z */
	prev_tim = kernel_systim.ltime;
	kernel_systim.ltime += tic;
	if ( kernel_systim.ltime < prev_tim )	/* ���オ�肪����Ȃ� */
	{
		kernel_systim.utime++;
	}
	
	/* �^�C�}�I�u�W�F�N�g�̃n���h���Ăяo�� */
	if ( kernel_tml_head != NULL )
	{
		/* �����|�C���^�ݒ� */
		kernel_tml_ptr = kernel_tml_head;
		
		do /* ���X�g�����܂ŌJ��Ԃ� */
		{
			/* ���̃|�C���^�����O�ɐݒ� */
			tim_ptr        = kernel_tml_ptr;
			kernel_tml_ptr = tim_ptr->next;
			
			/* �^�C�}�n���h���Ăяo�� */
			tim_ptr->timhdr(tim_ptr, tic);
			
			/* �n���h�����ō폜���ꂽ�ꍇ */
			if ( kernel_tml_ptr == NULL )
			{
				break;
			}
		} while ( kernel_tml_ptr != kernel_tml_head );
		
		/* �����|�C���^�̃N���A */
		kernel_tml_ptr = NULL;
	}
	
	/* �^�C���A�E�g�҂��s��̃^�X�N�N�� */
	mknl_tic_tmout(tic);	/* �^�C���A�E�g�L���[�Ƀ^�C���e�B�b�N������ */
	
	mknl_unl_sys();			/* �V�X�e���̃��b�N���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
