/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (���� SH4�p)                           */
/*    ���荞�݃n���h��                                                      */
/*                                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


		.global	__exception_handler
/* ��ʗ�O�n���h�� */
		.text
		.align	2
__exception_handler:
	mov.l	expevt_adr,r4
	stc	spc,r5
	stc	ssr,r6
	mov.l	exception_hdr_adr,r0
	jsr	@r0
	mov.l	@r4,r4

		.align	2
expevt_adr:
	.long	0xff000024		/* ��ʗ�O���W�X�^     */
exception_hdr_adr:
	.long	_exception_hdr


/* TLB�~�X��O�n���h�� */
		.text
		.org	__exception_handler+0x300
__tlb_mis_handler:
	bra	__exception_handler
	nop


/* ���荞�ݗ�O�n���h�� */
		.text
		.org	__exception_handler+0x500
__interrupt_handler:
	stc.l	ssr,@-r15
	stc.l	spc,@-r15
	mov.l	r4,@-r15

	/* ���荞�ݔԍ� = ( ���荞�ݎ��ۃ��W�X�^ >> 5 ) - 16 */
	mov.l	intevt_adr,r4
	mov.l	@r4,r4
	shlr2	r4
	shlr2	r4
	shlr	r4
	add	#-16,r4

	/* ���W�X�^�ޔ�(r0-r1) */
	mov.l	r0,@-r15
	mov.l	r1,@-r15

	/* ���Y���荞�݂̃}�X�N��ۑ� */
	mov.l	int_pri_tbl_adr,r0
	mov.b	@(r0,r4),r0
	shll2	r0
	shll2	r0
	mov.l	imsk_addr,r1
	mov.l	r0,@r1

	/* ���W�X�^�ۑ�(r2-r7,mach,macl,pr) */
	mov.l	r2,@-r15
	mov.l	r3,@-r15
	mov.l	r5,@-r15
	mov.l	r6,@-r15
	mov.l	r7,@-r15
	sts.l	mach,@-r15
	sts.l	macl,@-r15
	sts.l	pr,@-r15

	/* ���d���荞�ݔ��� */
	mov.l	int_cnt_addr,r1
	mov.l	@r1,r0
	cmp/eq	#0,r0
	bf/s	int_multi
	add	#1,r0

	/* �P�Ɗ��荞�ݎ� */
	mov.l	r0,@r1				/* ���荞�݃l�X�g�l��ݒ� */

	/* �X�^�b�N����ւ� */
	mov.l	save_sp_addr,r0
	mov.l	r15,@r0			/* ���݂̃X�^�b�N��ޔ� */
	mov.l	int_sp_addr,r0
	mov.l	@r0,r15			/* ���荞�ݗp�X�^�b�N��ݒ� */

	mov.l	r4,@-r15			/* ���荞�ݔԍ���ޔ� */

	/* ���荞�݊J�n�����Ăяo�� */
	mov.l	sta_int_addr,r1
	jsr	@r1
	nop

	/* ���荞�ݎ��s�����Ăяo�� */
	mov.l	exe_int_addr,r1
	jsr	@r1
	mov.l	@r15+,r4			/* ���荞�ݔԍ��������Ƃ��� */

	/* �X�^�b�N�̕��A */
	mov.l	save_sp_addr,r0
	mov.l	@r0,r15

	/* ���荞�݃J�E���^�̃N���A */
	mov.l	int_cnt_addr,r1
	xor	r0,r0
	mov.l	r0,@r1

	/* �x�[�X�}�X�N�l�ɖ߂� */
	mov.l	imsk_base_addr,r0
	mov.l	@r0,r1
	mov.l	imsk_addr,r0
	mov.l	r1,@r0

	/* ���荞�ݏI�������Ăяo�� */
	mov.l	end_int_addr,r1
	jsr	@r1
	nop

	/* ���W�X�^���A */
	lds.l	@r15+,pr
	lds.l	@r15+,macl
	lds.l	@r15+,mach
	mov.l	@r15+,r7
	mov.l	@r15+,r6
	mov.l	@r15+,r5
	mov.l	@r15+,r3
	mov.l	@r15+,r2
	mov.l	@r15+,r1
	mov.l	@r15+,r0
	mov.l	@r15+,r4
	ldc.l	@r15+,spc
	ldc.l	@r15+,ssr
	rte
	nop

	/* ���d���荞�ݏ��� */
int_multi:
	mov.l	r0,@r1				/* ���荞�݃l�X�g�l��ݒ� */

	/* ���荞�ݎ��s�����Ăяo�� */
	mov.l	exe_int_addr,r1
	jsr	@r1				/* ���荞�ݔԍ��������Ƃ��� */
	nop

	/* ���荞�݃J�E���^�̌��Z */
	mov.l	int_cnt_addr,r1
	mov.l	@r1,r0
	add	#-1,r0
	mov.l	r0,@r1

	/* ���W�X�^���A */
	lds.l	@r15+,pr
	lds.l	@r15+,macl
	lds.l	@r15+,mach
	mov.l	@r15+,r7
	mov.l	@r15+,r6
	mov.l	@r15+,r5
	mov.l	@r15+,r3
	mov.l	@r15+,r2
	mov.l	@r15+,r1
	mov.l	@r15+,r0
	mov.l	@r15+,r4
	ldc.l	@r15+,spc
	ldc.l	@r15+,ssr
	rte
	nop


	.align	2
imsk_addr:
	.long	_hospac_sh_imsk		/* ���荞�݃}�X�N */
imsk_base_addr:
	.long	_hospac_sh_imsk_base	/* ���荞�݃}�X�N�x�[�X�l */
int_cnt_addr:
	.long	_kernel_int_cnt		/* ���荞�݃l�X�g�� */
save_sp_addr:
	.long	_kernel_int_ssp		/* ���荞�ݗp�X�^�b�N�|�C���^�ޔ� */
int_sp_addr:
	.long	_kernel_int_sp		/* ���荞�ݗp�X�^�b�N�|�C���^ */
sta_int_addr:
	.long	_kernel_sta_int		/* ���荞�݊J�n���� */
end_int_addr:
	.long	_kernel_end_int		/* ���荞�ݏI������ */
exe_int_addr:
	.long	_kernel_exe_int		/* ���荞�ݎ��s���� */
int_pri_tbl_adr:
	.long	_int_pri_tbl		/* UB int_pri_tbl[] */
					/* ���荞�ݗD�揇�ʂ̃e�[�u�� */
intevt_adr:
	.long	0xff000028		/* ���荞�ݎ��ۃ��W�X�^ */

	.end



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
