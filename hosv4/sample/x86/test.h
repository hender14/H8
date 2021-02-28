/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �T���v���v���O����                                                     */
/*   ���C�����[�`��                                                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __test_h__
#define __test_h__



#ifdef __cplusplus
extern "C" {
#endif

void TestStart(VP_INT exinf);	/* ATT_INI �o�^�̊֐� */

void Task1(VP_INT exinf);		/* �T���v���^�X�N1 */
void Task2(VP_INT exinf);		/* �T���v���^�X�N2 */
void Task3(VP_INT exinf);		/* �T���v���^�X�N3 */

void CycHandler1(VP_INT exinf);	/* �����n���h���T���v�� */

void IntHndler1(VP_INT exinf);	/* ���荞�݃n���h���T���v�� */

#ifdef __cplusplus
}
#endif



#endif	/* __test_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
