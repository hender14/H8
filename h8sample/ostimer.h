/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*    H8/3048 用 OSタイマ (ITU0を利用)                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__SAMPLE__ostimer_h__
#define __HOS_V4__SAMPLE__ostimer_h__


#ifdef __cplusplus
extern "C" {
#endif

void Ostimer_init(VP_INT exinf);		/* OSタイマの初期化 */
void Ostimer_interruptHandler(VP_INT exinf);	/* タイマ用割り込みハンドラ */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__SAMPLE__ostimer_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */