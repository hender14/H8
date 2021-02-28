/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ���ˑ���񔻕�                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__hosdenv_h__
#define __HOS_V4__hosdenv_h__



#if defined(__CC_ARM) || defined(__arm__)	/* ARM�R���p�C�� */

#include "arm/hospac.h"	

#elif defined(__CPU__)	/* ����H8�R���p�C�� */

#if (__CPU__ == 3) || (__CPU__ == 2)        /* H8/300H */
#include "h83/hospac.h"
#endif

#elif defined(__H8300H__)	/* gcc H8/300H �R���p�C�� */

#include "h83/hospac.h"

#elif defined(__sh__) || defined(_SH1) || defined(_SH2) ||  defined(_SH3) || defined(_SH4)	/* SH �R���p�C�� */

#include "sh/hospac.h"

#elif defined(_WIN32)	/* VC++ */

#include "win/hospac.h"

#elif defined(LSI_C)	/* LSI-C(86) */

#include "x86/hospac.h"

#elif defined(__i386__)	/* i386-elf-gcc */
#include "ia32/hospac.h"

#elif defined(__mips__) /* mips-elf-gcc */
#include "mips/hospac.h"

#else

#include "hospac.h"		/* ���ʂł��Ȃ��ꍇ�̓C���N���[�h�p�X�̎w������҂��� */

#endif



#endif	/* __HOS_V4__hosdenv_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
