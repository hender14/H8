; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                     
;    �v���Z�b�T���ۉ��R���|�[�l���g (ARM�p)                                   
;    ��O�n���h��                                                             
;                                                                             
;                                     Copyright (C) 1998-2002 by Project HOS  
;                                     http://sourceforge.jp/projects/hos/     
; --------------------------------------------------------------------------- 


				INCLUDE	pacarm.inc


				AREA	inthdr_code, CODE, READONLY
				CODE32

				EXPORT	_HOS_UndefinedHandler
				EXPORT  _HOS_SwiHandler
				EXPORT	_HOS_PrefetchHandler
				EXPORT	_HOS_AbortHandler


; ----------------------------------------------
;  Undefined �n���h��
; ----------------------------------------------
_HOS_UndefinedHandler
				b		_HOS_UndefinedHandler



; ----------------------------------------------
;  SWI �n���h��
; ----------------------------------------------
				IMPORT	hospac_arm_imsk
_HOS_SwiHandler
			; ---- SWI�ԍ��ǂݏo��
				ldr		r13, [lr, #-4]
				bic		r13, r13, #0xff000000

				teq 	r13, #0x10		; �J�[�l���R�[���� #10 �Ƃ���
				bne 	swi_ret

			; ---- �p�����[�^�[�𔻒�
				cmp		a1, #3
				and		a1, a1, #0x03
				addls	pc, pc, a1, lsl #2
				b		swi_ret
				b		swi_dis_int
				b		swi_ena_int

			; ---- IRQ/FIQ����̕��A (a1 = 2)
				ldr		r13, =pac_arm_swi_ret
				ldmia	r13, {a1, r13, lr}
				msr		spsr_csxf, r13
				subs	pc, lr, #0

			; ---- ���荞�݋֎~(a1 = 0)
swi_dis_int
				mov		r13, #Mode_USR:OR:I_Bit:OR:F_Bit
				msr 	spsr_cf, r13
				subs	pc, lr, #0

			; ---- ���荞�݋���(a1 = 1)
swi_ena_int
				ldr		r13, =hospac_arm_imsk
				ldr		r13, [r13]
				msr 	spsr_cf, r13

swi_ret
			; ---- ���������ɗ�O�����@�\ 
				subs	pc, lr, #0


; ----------------------------------------------
;  Prefetch �n���h��
; ----------------------------------------------
_HOS_PrefetchHandler
				b		_HOS_PrefetchHandler



; ----------------------------------------------
;  Abort �n���h��
; ----------------------------------------------
_HOS_AbortHandler
				b		_HOS_AbortHandler



; ----------------------------------------------
;  �O���[�o���ϐ�
; ----------------------------------------------
				AREA	inthdr_bss, NOINIT

				EXPORT	pac_arm_swi_ret
pac_arm_swi_ret	%		12		; a1, cpsr, lr �̒l�n���p


				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
