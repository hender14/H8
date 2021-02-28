/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*    �X�^�[�g�A�b�v���W���[�� (���� SH4 gcc �p)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

		.global	start
		.text
start:
	/* ���荞�݃}�X�N�ݒ� */
	stc	sr,r0
	or	#0xf0,r0
	ldc	r0,sr

	/* setup_cache��P2�̈�Ƃ��ČĂяo����Ȃ���΂Ȃ�Ȃ� */
	mov.l	l_setup_cache,r0
	mov.l	l_addr_mask,r1
	and	r1,r0
	mov.l	l_p2_mask,r1
	or	r1,r0
	jsr	@r0
	nop

	/* �x�N�^�x�[�X���W�X�^�Z�b�g */
	mov.l	l_vbr_data,r2
	ldc	r2,vbr

	/* BSS clear */
	mov.l	l_bss_start,r1	/* bss_start��ALIGN(0x4)��O�� */
	mov.l	l_bss_end,r2
	cmp/eq	r2,r1
	bt	clr_end
	mov	#0,r0
clr_loop:
	mov.l	r0,@r1
	add	#4,r1
	cmp/hs	r2,r1
	bf	clr_loop
clr_end:

	/* main�ďo */	
	mov.l	l_main,r8
	jsr	@r8
	nop

end_loop:
	bra	end_loop
	nop

/* �L���b�V���Z�b�g�A�b�v (�K��P2�̈�Ƃ��ăR�[��)*/
setup_cache:
	mov.l	l_ccr_p4addr,r0
	mov.l	l_ccr_data,r1
	mov.l	r1,@r0
	nop	/* 1 */
	nop	/* 2 */
	nop	/* 3 */
	nop	/* 4 */
	nop	/* 5 */
	nop	/* 6 */
	nop	/* 7 */
	nop	/* 8 */
	rts
	nop

	.align	2
l_setup_cache:
	.long	setup_cache
l_addr_mask:
	.long	0x1fffffff
l_p2_mask:
	.long	0xa0000000
l_vbr_data:
	.long	__exception_handler - 0x100
l_main:
	.long	_main
l_bss_start:
	.long	__bss_start
l_bss_end:
	.long	_end

l_ccr_p4addr:
	.long	0xff00001c
l_ccr_data:
	.long	0x0000090b
/*
	IIX(15) = 0 IC entry use adr[12:5]
	ICI(11) = 1 IC invalid
	ICE( 8) = 1 IC enable
	OIX( 7) = 0 IC entry use adr[13:5]
	ORA( 5) = 0 OC 16K
	OCI( 3) = 1 OC invalid
	CB ( 2) = 0 P1 Write-Through
	WT ( 1) = 1 U0,P0,P3 Write-Through
	OCE( 0) = 1 OC enable
*/
		.end

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
