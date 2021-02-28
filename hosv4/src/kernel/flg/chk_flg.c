/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �C�x���g�t���O                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* �t���O���N�������𖞂����Ă��邩�`�F�b�N */
BOOL kernel_chk_flg(
		T_KERNEL_FLGCB_RAM *flgcb_ram,	/* �R���g���[���u���b�N RAM�� */
		T_KERNEL_FLGINF    *pk_flginf)	/* �҂��t���O���p�P�b�g�̐擪�Ԓn */
{
	if ( pk_flginf->wfmode == TWF_ANDW )
	{
		/* AND�҂����� */
		return ((flgcb_ram->flgptn & pk_flginf->waiptn) == pk_flginf->waiptn);
	}
	else
	{
		/* OR�҂����� */
		return ((flgcb_ram->flgptn & pk_flginf->waiptn) != 0);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
