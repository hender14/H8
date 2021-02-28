; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  ���� H8 �p �T���v���v���O����                   
;    �X�^�[�g�A�b�v���[�`��                                                   
;                                                                             
;                                   Copyright (C) 1998-2002 by Project HOS    
;                                   http://sourceforge.jp/projects/hos/       
; --------------------------------------------------------------------------- 



				.h8300h

; -------------------------------------
;  �X�^�[�g�A�b�v���[�`��
; -------------------------------------
				.text
				.align 2
				.global _startup
_startup:
		; ----- �X�^�b�N������
				mov.l	#_stack,er7

		; ----- .data �Z�N�V�����R�s�[ �iDATA��64kbyte�ȉ��Ɖ���j
				mov.l	#___dtors_end,er5
				mov.l	#___data,er6
				mov.w	#data_size,r4
copy_dsec:	eepmov.w
				mov.w	r4,r4
				bne	copy_dsec
				
		; ----- .bss �Z�N�V�����N���A�iBSS��64kbyte�ȉ��Ɖ���j
				mov.l	#_bss_start,er5
				mov.l	#_bss_start+1,er6
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
				.long	_stack		/* ���荞�ݎ��� er7 �ۑ��p */


				.end



; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
