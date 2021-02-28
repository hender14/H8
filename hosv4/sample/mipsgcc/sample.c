/*******************************************************************************
 * Hyper Operating System V4  �T���v���v���O����
 *
 *  �e�^�X�N�̋N�������ƃ^�X�N�����V���A���R���\�[���֕\������v���O����
 *      �^�X�N��    �D��x  �N������
 *      Task1       1       Task2�����sig_sem()�ɂ��N��
 *      Task2       2       1[s]�����̎����^�C�}�ɂ��N��
 *
 *                                      Copyright (C) 1998-2007 by Project HOS
 *                                      http://sourceforge.jp/projects/hos/
 *******************************************************************************/

#include <semb1200a/semb1200a.h>
#include "semb1200a/ux_signal.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sample.h"

/**
 *  main�֐�
 */
int
main(void)
{
	/* HOS-V4 �̊J�n */
	sta_hos();
	return 0;
}

/**
 *  �������֐�
 *  �^�X�N�̋N�����s��
 */
void
sample_init (VP_INT exinf)
{
    act_tsk (TSKID_SAMPLE_1);
    act_tsk (TSKID_SAMPLE_2);

    /* �����^�C�}�̋N�� */
    sta_cyc (CYCID_SAMPLE_1);
}

/**
 *  �T���v���^�X�N1
 *  - �^�X�N2���Z�}�t�H����������܂ő҂�
 *  - ���ݎ����ƃ^�X�N����\��
 */
void
sample_task_1 (VP_INT exinf)
{
    for (;;) {
        wai_sem (SEMID_SAMPLE_1);
        sample_print (1);
    }
}

/**
 *  �T���v���^�X�N2
 *  - 1[s]�̊�sleep����
 *  - �Z�}�t�H������
 *  - ���ݎ����ƃ^�X�N����\��
 */
void
sample_task_2 (VP_INT exinf)
{
    for (;;){
        slp_tsk ();
        sig_sem (SEMID_SAMPLE_1);
        sample_print (2);
    }
}

/**
 *  ���ݎ����ƃ^�X�Nno��\������
 */
void
sample_print (int no)
{
    SYSTIM st;

    get_tim (&st);

    uart1_putc ('0'+ (st.ltime / 10000) % 10);
    uart1_putc ('0'+ (st.ltime / 1000) % 10);
    uart1_putc ('0'+ (st.ltime / 100) % 10);
    uart1_putc ('0'+ (st.ltime / 10) % 10);
    uart1_putc ('0'+ (st.ltime / 1) % 10);
    uart1_puts (":Task ");
    uart1_putc ('0'+no);
    uart1_puts ("\n\r");
}

void
sample_cycle_handler (VP_INT exinf)
{
    iwup_tsk (TSKID_SAMPLE_2);
}
