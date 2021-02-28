/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �G���[�`�F�b�N���x���ݒ�                                              */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__hoserchk_h__
#define __HOS_V4__hoserchk_h__



#if !defined(_HOS_ERCHK_LEVEL)
#if defined(_HOS_ERCHK_CUSTOM)
#define _HOS_ERCHK_LEVEL 0
#else
#define _HOS_ERCHK_LEVEL 4
#endif
#endif


#if _HOS_ERCHK_LEVEL >= 1
#define HOS_ERCHK_E_OBJ						/* E_OBJ �̃G���[�`�F�b�N���s�� */
#define HOS_ERCHK_E_NOMEM					/* E_NOMEM �̃G���[�`�F�b�N���s�� */
#endif

#if _HOS_ERCHK_LEVEL >= 2
#define HOS_ERCHK_E_QOVR					/* E_QOVR �̃G���[�`�F�b�N���s�� */
#endif

#if _HOS_ERCHK_LEVEL >= 3
#define HOS_ERCHK_E_PAR						/* E_PAR �̃G���[�`�F�b�N���s�� */
#define HOS_ERCHK_E_ID						/* E_ID �̃G���[�`�F�b�N���s�� */
#define HOS_ERCHK_E_RSATR					/* E_RSATR �̃G���[�`�F�b�N���s�� */
#define HOS_ERCHK_E_NOID					/* E_NOID �̃G���[�`�F�b�N���s�� */
#endif

#if _HOS_ERCHK_LEVEL >= 4
#define HOS_ERCHK_E_NOEXS					/* E_NOEXS �̃G���[�`�F�b�N���s�� */
#define HOS_ERCHK_E_CTX						/* E_CTX �̃G���[�`�F�b�N���s�� */
#define HOS_ERCHK_E_ILUSE					/* E_ILUSE �̃G���[�`�F�b�N���s�� */
#endif



#endif	/* __HOS_V4__hoserchk_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
