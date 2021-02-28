/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �T���v���v���O����                                                     */
/*   ���C�����[�`��                                                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __sample_h__
#define __sample_h__


/* �N�w�҃^�X�N�ƃt�H�[�N�Z�}�t�H��ID���Œ�l�Ŏw�� */
#define TSKID_PHILOSOPHER1	1
#define TSKID_PHILOSOPHER2	2
#define TSKID_PHILOSOPHER3	3
#define TSKID_PHILOSOPHER4	4
#define TSKID_PHILOSOPHER5	5
#define SEMID_FORK1			1
#define SEMID_FORK2			2
#define SEMID_FORK3			3
#define SEMID_FORK4			4
#define SEMID_FORK5			5


#ifdef __cplusplus
extern "C" {
#endif

void SampleInitialize(VP_INT exinf);	/* ATT_INI �o�^�̊֐� */
void PhilosopherTask(VP_INT exinf);		/* �N�w�҃^�X�N */
void OutputTask(VP_INT exinf);			/* �o�̓^�X�N */

#ifdef __cplusplus
}
#endif



#endif	/* __sample_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
