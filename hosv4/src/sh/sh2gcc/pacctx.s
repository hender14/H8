/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (���� SH2�p)                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



				.global	_hospac_dis_int			/* ���荞�݋֎~ */
				.global	_hospac_ena_int			/* ���荞�݋��� */
				.global	_hospac_cre_ctx_asm		/* ���s�R���e�L�X�g�̍쐬 */
				.global	_hospac_swi_ctx			/* ���s�R���e�L�X�g�̐ؑ� */



/************************************************
  ���荞�݋֎~
  void hospac_dis_int(void)
************************************************/
				.text
				.align	2
_hospac_dis_int:
				stc		sr, r0
				or		#0xf0, r0		/* �S���荞�݃}�X�N */
				rts
				ldc		r0, sr



/************************************************
  ���荞�݋���
  void hospac_ena_int(void)
************************************************/
				.text
				.align	2
_hospac_ena_int:
				mov		#0xf0, r1		/* 0x00f0 �𔽓]������ 0xff0f ���쐬 */
				not		r1, r1
				stc		sr, r0
				and		r1, r0			/* ���荞�݃}�X�N�l�ȊO���擾 */
				mov.l	imsk_addr, r1
				mov.l	@r1, r1
				or		r1, r0			/* ���荞�݃}�X�N�̒l��ݒ� */
				rts
				ldc		r0, sr

				.align	2
imsk_addr:
				.long	_hospac_sh_imsk			/* ���荞�݃}�X�N */



/************************************************
  ���s�R���e�L�X�g�G���g���[�A�h���X
************************************************/
				.text
				.align 2
ctx_entry:	 	
				jmp		@r14			/* ���s�A�h���X�ɃW�����v */
				mov		r13, r4			/* ���s���p�����[�^��������ɐݒ� */


/************************************************
  ���s�R���e�L�X�g�̍쐬
  void hospac_cre_ctx_asm(
		 T_HOSPAC_CTXINF *pk_ctxinf,	�쐬����R���e�L�X�g
		 VP 	sp, 					�X�^�b�N�|�C���^
		 void	(*task)(VP_INT),		���s�A�h���X
		 VP_INT exinf)					���s���p�����[�^
************************************************/
				.text
				.align 2
_hospac_cre_ctx_asm:
				add 	#-20, r5				/* r14-10���R���e�L�X�g��stack��L�΂� */
				mov.l	r7, @-r5				/* ���s�p�����[�^�̊i�[(r9) */
				mov.l	r6, @-r5				/* ���s�A�h���X�̊i�[(r8) */
				mov.l	ctx_entry_addr, r0		/* ���s�G���g���|�C���g���R���e�L�X�g�� */
				mov.l	r0, @-r5				/* �X�^�b�N�ɕۑ� */
				rts
				mov.l	r5, @(0,r4) 			/* �R���e�L�X�g�̃X�^�b�N�|�C���^�ۑ� */

				.align	2
ctx_entry_addr:
				.long	ctx_entry



/************************************************
  ���s�R���e�L�X�g�̐ؑ�
  void hospac_swi_ctx(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,	���݂̃R���e�L�X�g�̕ۑ���
		T_HOSPAC_CTXINF *pk_nxt_ctxinf)	�؂�ւ���R���e�L�X�g
************************************************/
				.text
				.align 2
_hospac_swi_ctx:
				mov.l	 r8, @-r15		/* 8-r14,pr��ޔ� */
				mov.l	 r9, @-r15
				mov.l	 r10, @-r15
				mov.l	 r11, @-r15
				mov.l	 r12, @-r15
				mov.l	 r13, @-r15
				mov.l	 r14, @-r15
				sts.l	 pr, @-r15

				mov.l	 r15, @(0, r4)	/* �X�^�b�N�|�C���^�ۑ� */
				mov.l	 @(0, r5), r15	/* �X�^�b�N�|�C���^���A */

				lds.l	 @r15+, pr		/* r8-r14,pr�𕜋A */
				mov.l	 @r15+, r14
				mov.l	 @r15+, r13
				mov.l	 @r15+, r12
				mov.l	 @r15+, r11
				mov.l	 @r15+, r10
				mov.l	 @r15+, r9
				rts
				mov.l	 @r15+, r8



				.end


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
