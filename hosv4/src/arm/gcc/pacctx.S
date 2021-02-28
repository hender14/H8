/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (ARM gcc�p)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


				.global	hospac_dis_int		/* ���荞�݋֎~ */
				.global	hospac_ena_int		/* ���荞�݋��� */
				.global	hospac_cre_ctx_asm	/* ���s�R���e�L�X�g�̍쐬 */
				.global	hospac_swi_ctx		/* ���s�R���e�L�X�g�̐ؑ� */


				.text
				.align	4


/************************************************
  ���荞�݋֎~
  void hospac_dis_int(void)
*************************************************/
hospac_dis_int:
				mov		a1, #0				/* ���荞�݋֎~���w�� */
				swi		0x10				/* �X�[�p�o�C�[�U�[�R�[�� */
				mov		pc, lr


/************************************************
  ���荞�݋���
  void hospac_ena_int(void)
*************************************************/
hospac_ena_int:
				mov		a1, #1				/* ���荞�݋����w�� */
				swi		0x10				/* �X�[�p�o�C�[�U�[�R�[�� */
				mov		pc, lr


/************************************************
  ���s�R���e�L�X�g�G���g���[�A�h���X
*************************************************/
ctx_entry:
				mov		a1, v2				/* ���s���p�����[�^��������ɐݒ� */
				mov		pc, v1				/* ���s�A�h���X�ɕ��� */


/************************************************
  ���s�R���e�L�X�g�̍쐬
  void hospac_cre_ctx_asm(
		T_HOSPAC_CTXINF *pk_ctxinf,			�쐬����R���e�L�X�g
		VP     sp,							�X�^�b�N�|�C���^
		void   (*task)(VP_INT),				���s�A�h���X
		VP_INT exinf						���s���p�����[�^
	)
*************************************************/
hospac_cre_ctx_asm:
				stmfd	sp!, {v1}			/* ��ƃ��W�X�^�ޔ� */
				ldr		v1, =ctx_entry
				stmfd	a2!, {v1}			/* �G���g���[�|�C���g��ݒ� */
				sub		a2, a2, #28			/* v3-v8, ip �����Z */
				stmfd	a2!, {a3,a4}		/* v1, v2 �̗̈�Ɏ��s�A�h���X�ƃp�����[�^�i�[ */
				str		a2, [a1]			/* �R���e�L�X�g�Ƃ��� sp ��ۑ� */
				ldmfd	sp!, {v1}			/* ��ƃ��W�X�^���A */
				mov		pc, lr				/* ���^�[�� */


/************************************************
  ���s�R���e�L�X�g�̐ؑ�
  void hospac_swi_ctx(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		���݂̃R���e�L�X�g�̕ۑ���
		T_HOSPAC_CTXINF *pk_nxt_ctxinf		�؂�ւ���R���e�L�X�g
		)
*************************************************/
hospac_swi_ctx:
				stmfd	sp!, {v1-v8,ip,lr}	/* ���W�X�^�ۑ� */
				str		sp, [a1]			/* �X�^�b�N�|�C���^�ۑ� */
				ldr		sp, [a2]			/* �X�^�b�N�|�C���^���A */
				ldmfd	sp!, {v1-v8,ip,pc}	/* ���W�X�^���A�����^�[�� */



				.end


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */