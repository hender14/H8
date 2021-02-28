/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*    H8/3048 �p OS�^�C�} (ITU0�𗘗p)                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__SAMPLE__ostimer_h__
#define __HOS_V4__SAMPLE__ostimer_h__


#ifdef __cplusplus
extern "C" {
#endif

void Ostimer_init(VP_INT exinf);		/* OS�^�C�}�̏����� */
void Ostimer_interruptHandler(VP_INT exinf);	/* �^�C�}�p���荞�݃n���h�� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__SAMPLE__ostimer_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */