; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  ���� H8 �p �T���v���v���O����                   
;    �X�^�[�g�A�b�v���[�`��                                                   
;                                                                             
;                                   Copyright (C) 2003-2006 by Project HOS    
;                                   http://sourceforge.jp/projects/hos/       
; --------------------------------------------------------------------------- 

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
				.h8300hn
#else
				.h8300h
#endif

; -------------------------------------
;  �X�^�[�g�A�b�v���[�`��
; -------------------------------------
				.text
				.align 2
				.global _startup
_startup:
		; ----- �X�^�b�N������
				mov.w	#_stack,r7

		; ----- .data �Z�N�V�����R�s�[
				mov.w	#___dtors_end,r5
				mov.w	#___data,r6
				mov.w	#data_size,r4
copy_dsec:	eepmov.w
				mov.w	r4,r4
				bne	copy_dsec
				
		; ----- .bss �Z�N�V�����N���A
				mov.w	#_bss_start,r5
				mov.w	#_bss_start+1,r6
				mov.w	#bss_size,r4
				mov.b	#0,r0l
				mov.b	r0l,@er5
clr_bsec:		eepmov.w
				mov.w	r4,r4
				bne	clr_bsec

		; ----- ���������[�`���Ăяo��
				jsr	@_main
idle_loop:
				bra	idle_loop


				.global	_kernel_int_sp
				.section .rodata
				.align 2
_kernel_int_sp:
				.word	_stack		/* ���荞�ݎ��� er7 �ۑ��p */


				.end


; --------------------------------------------------------------------------- 
;  Copyright (C) 2003-2006 by Project HOS                                     
; --------------------------------------------------------------------------- 
