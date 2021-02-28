/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "kernel.h"
#include "kernel_id.h"
#include "sh7750.h"
#include "scif.h"


/* ���C���֐� */
int main()
{
	/* �J�n���b�Z�[�W */
	scif_puts("HOS-V4/SH4 test program start.\n");
	sta_hos();
	
	return 0;
}


/* �������n���h�� */
void Initialize(VP_INT exinf)
{
	act_tsk(TSKID_SAMPLE1);
}

/* �T���v���^�X�N */
void Task1(VP_INT exinf)
{
	SYSTIM st;
	
	for ( ; ; )
	{
		/* �^�C�}�l�擾 */
		get_tim(&st);
		
		/* �^�C�}�l�o�� */
		scif_putc('0' + (st.ltime / 10000) % 10);
		scif_putc('0' + (st.ltime / 1000) % 10);
		scif_putc('0' + (st.ltime / 100) % 10);
		scif_putc('0' + (st.ltime / 10) % 10);
		scif_putc('0' + (st.ltime / 1) % 10);
		scif_putc(':');
		
		/* �^�X�N���b�Z�[�W */
		scif_puts("Task1\r\n");
		
		/* 1�b�҂� */
		dly_tsk(1000);
	}
}


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
