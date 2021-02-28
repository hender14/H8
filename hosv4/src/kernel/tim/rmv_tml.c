/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���ԊǗ�                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* �^�C�}�I�u�W�F�N�g�����X�g����폜 */
void kernel_rmv_tml(
		T_KERNEL_TIM *timobj)	/* �폜����^�C�}�I�u�W�F�N�g */
{
	/* ���o�^�Ȃ牽�����Ȃ� */
	if ( timobj->next == NULL )
	{
		return;
	}
	
	/* �������̃^�C�}�Ȃ�|�C���^�����炷(�ē��΍�) */
	if ( timobj == kernel_tml_ptr )
	{
		if ( timobj->next == kernel_tml_head )
		{
			kernel_tml_ptr = NULL;			/* �����Ȃ�A���̃|�C���^�͖��� */
		}
		else
		{
			kernel_tml_ptr = timobj->next;	/* ���̃I�u�W�F�N�g�Ɉړ� */
		}
	}
	
	/* ���X�g����폜 */
	if ( timobj == timobj->next )
	{
		/* ���X�g����ɂȂ�ꍇ */
		kernel_tml_head = NULL;
	}
	else
	{
		/* �擪�Ȃ�擪�ʒu�����炷 */
		if ( timobj == kernel_tml_head )
		{
			kernel_tml_head = timobj->next;
		}
		
		/* ���X�g����폜 */
		timobj->next->prev = timobj->prev;
		timobj->prev->next = timobj->next;
	}

	/* ���o�^�ɐݒ� */
	timobj->next = NULL;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
