/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (���� H8/300H �p)                      */
/*    �R���e�L�X�g����                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
				.h8300hn
#else
				.h8300h
#endif


				.text
				.align 2



				.global	_hospac_dis_int		/* ���荞�݋֎~ */
				.global	_hospac_ena_int		/* ���荞�݋��� */
				.global	_hospac_cre_ctx_asm	/* ���s�R���e�L�X�g�̍쐬 */
				.global	_hospac_swi_ctx		/* ���s�R���e�L�X�g�̐ؑ� */
				.global	_hospac_set_tex		/* ��O�������s�ݒ� */



/************************************************
  ���荞�݋֎~
  void hospac_dis_int(void)
*************************************************/
_hospac_dis_int:
				orc	#0xc0, ccr			/* ���荞�݂̋֎~ */
				rts


/************************************************
  ���荞�݋���
  void hospac_ena_int(void)
*************************************************/
_hospac_ena_int:
				mov.b	@_kernel_h83_imsk:16, r0l
				ldc.b	r0l, ccr		/* ���荞�݂̋��� */
				rts



/************************************************
  ���s�R���e�L�X�g�G���g���[�A�h���X
*************************************************/
ctx_entry:	
				mov.l	er4, er0		/* ���s���p�����[�^��������ɐݒ� */
				jmp		@er5			/* ���s�A�h���X�ɃW�����v */


/************************************************
  ���s�R���e�L�X�g�̍쐬
  void hospac_cre_ctx_asm(
			T_HOSPAC_CTXINF *pk_ctxinf,			�쐬����R���e�L�X�g
			VP              sp,					�X�^�b�N�|�C���^
			void            (*task)(VP_INT),	���s�A�h���X
			VP_INT          exinf				���s���p�����[�^
		)
*************************************************/
_hospac_cre_ctx_asm:
				mov.w   #ctx_entry, r3	/* ���s�G���g���[�|�C���g�̐ݒ� */
				mov.w   r3, @-er1
				mov.l   @(2:16,er7), er3	/* ���s���p�����[�^�̎��o�� */
				mov.l   er3, @-er1		/* ���s���p�����[�^�i�[ (er4�̑ޔ�) */
				mov.l   er2, @-er1		/* ���s�h���X���i�[ (er5 �̑ޔ�) */
				sub.l   #4, er1			/* er6�̑ޔ� */

#if ( __GNUC__ > 3 || ( __GNUC__ == 3 && __GNUC_MINOR__ >= 3))
				mov.w   r1, @(0:16, er0)	/* �X�^�b�N�|�C���^�̊i�[ */
#else
				mov.l   er1, @(0:16, er0)	/* �X�^�b�N�|�C���^�̊i�[ */
#endif	/* 3.3�ȍ~�ł́A-mn�Ń|�C���^��WORD�T�C�Y�ƂȂ� */

				rts


/************************************************
  ���s�R���e�L�X�g�̐ؑ�
  void hospac_swi_ctx(
			T_HOSPAC_CTXINF *pk_pre_ctxinf,		���݂̃R���e�L�X�g�̕ۑ���
			T_HOSPAC_CTXINF *pk_nxt_ctxinf		�؂�ւ���R���e�L�X�g
		)
*************************************************/
_hospac_swi_ctx:
				push.l	er4
				push.l	er5
				push.l	er6

#if ( __GNUC__ > 3 || ( __GNUC__ == 3 && __GNUC_MINOR__ >= 3))
				mov.w	r7,@(0, er0)	/* �X�^�b�N�|�C���^�ۑ� */
				mov.w	@(0, er1), r7	/* �X�^�b�N�|�C���^���A */
#else
				mov.l	er7,@(0, er0)	/* �X�^�b�N�|�C���^�ۑ� */
				mov.l	@(0, er1), er7	/* �X�^�b�N�|�C���^���A */
#endif	/* 3.3�ȍ~�ł́A-mn�Ń|�C���^��WORD�T�C�Y�ƂȂ� */

				pop.l	er6
				pop.l	er5
				pop.l	er4
				rts



				.end


/* -------------------------------------------------------------------------*/
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* -------------------------------------------------------------------------*/