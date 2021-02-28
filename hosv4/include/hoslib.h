/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l�����p���C�u����                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__hoslib_h__
#define __HOS_V4__hoslib_h__



#ifdef _HOS_USE_STDLIB	/* �W�����C�u�����g�p�Ȃ� */

#include <string.h>

#define __hos_bcopy(dst, src, size)		memcpy(dst, src, size)			/* �o�C�g�P�ʃR�s�[ */
#define __hos_hcopy(dst, src, size)		memcpy(dst, src, (size) * 2)	/* �n�[�t���[�h�P�ʃR�s�[ */
#define __hos_wcopy(dst, src, size)		memcpy(dst, src, (size) * 4)	/* ���[�h�P�ʃR�s�[ */

#else	/* �W�����C�u�����s�g�p�Ȃ� */

/* �o�C�g�P�ʃR�s�[ */
#define __hos_bcopy(dst, src, size)					\
	do {											\
		SIZE i;										\
		for ( i = 0; i < (SIZE)(size); i++ )		\
		{											\
			((VB *)(dst))[i] = ((VB *)(src))[i];	\
		}											\
	} while (0)

/* �n�[�t���[�h�P�ʃR�s�[ */
#define __hos_hcopy(dst, src, size)					\
	do {											\
		SIZE i;										\
		for ( i = 0; i < (SIZE)(size); i++ )		\
		{											\
			((VH *)(dst))[i] = ((VH *)(src))[i];	\
		}											\
	} while (0)

/* ���[�h�P�ʃR�s�[ */
#define __hos_wcopy(dst, src, size)					\
	do {											\
		SIZE i;										\
		for ( i = 0; i < (SIZE)(size); i++ )		\
		{											\
			((VW *)(dst))[i] = ((VW *)(src))[i];	\
		}											\
	} while (0)

#endif	/* _HOS_USE_STDLIB */



#endif	/* __HOS_V4__hoslib_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
