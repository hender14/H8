/* ------------------------------------------------------------------------*/
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (IA32�p)                                   */
/*      �v���Z�b�T���ۉ��R���|�[�l���g���ʒ�`                                   */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__hospac_h__
#define __HOS_V4__IA32__hospac_h__
#include "pic.h"                 /*  �����݃R���g���[���֘A����  */
#if defined(__GNUC__ ) 
#include "ia32gcc/linkage.h"     /*  gcc �ŗL�����P�[�W��`  */
#include "ia32gcc/ioport.h"      /*  I/O �|�[�g�֘A����  */
#include "ia32gcc/hosexp.h"      /*  ���荞�ݗ�O�֘A��`  */
#include "ia32gcc/descriptor.h"  /*  IA32�f�B�X�N���v�^�֘A��`  */
#include "ia32gcc/switch.h"  /*  IA32�f�B�X�N���v�^�֘A��`  */
#include "ia32gcc/idle.h"    /*  IA32�A�C�h�������֘A��`  */
#else
#error "IA32 port can not support your compiler."
#endif  /*  __GNUC__  */
#include "itron.h"


/* ------------------------------------------ */
/*                   �^��`                   */
/* ------------------------------------------ */
/* IA32�ŗL ���荞�݊Ǘ��@�\ */
typedef UH		IMSK;		/* ���荞�݃}�X�N�p�^�[�� */

/* �R���e�L�X�g���ۑ��u���b�N */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* �X�^�b�N�|�C���^�ۑ��̈� */
} T_HOSPAC_CTXINF;


/* ------------------------------------------ */
/*                �}�N����`                  */
/* ------------------------------------------ */
#define MAX_IRQ_NR  16  /*  �O�������݂̍ő吔  */


/* ------------------------------------------ */
/*                �֐��錾                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif
extern void hospac_ini_sys(void);  /* �v���Z�b�T���ۉ��R���|�[�l���g�̏����� */

/* ���s�R���e�N�X�g�쐬���� */
extern void hospac_cre_ctx(
        T_HOSPAC_CTXINF *pk_ctxinf,  /* �R���e�L�X�g���i�[��̐擪�Ԓn */
        VP_INT          exinf,       /* �N�������� */
        FP              task,        /* �N���Ԓn */
        SIZE            stksz,       /* �X�^�b�N�T�C�Y */
        VP              stk          /* �X�^�b�N�擪�Ԓn */
      );

  /* ���s�R���e�L�X�g�̐ؑ� */
extern void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
			   T_HOSPAC_CTXINF *pk_nxt_ctxinf);
/* IA32�ŗL ���荞�݊Ǘ��@�\ */
ER   chg_imsk(IMSK imsk);		/* ���荞�݃}�X�N�w�� */
ER   get_imsk(IMSK *p_imsk);		/* ���荞�݃}�X�N�̎Q�� */

ER   _kernel_ia32__send_eoi(UW irq);	/* ���荞�݊����ʒm */


#ifdef __cplusplus
}
#endif

#endif  /*  __HOS_V4__IA32__hospac_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
