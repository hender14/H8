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

				EXPORT	_HOS_CpuExceptionHandler

; ----------------------------------------------
;  CPU��O�n���h��
; ----------------------------------------------
				IMPORT	kernel_sta_exc				; CPU��O�n���h���J�n����
				IMPORT	kernel_end_exc				; CPU��O�n���h���I������
				IMPORT	kernel_exe_exc				; CPU��O�n���h���̎��s
				IMPORT	kernel_int_sp				; ���荞�ݗp�X�^�b�N�A�h���X
				IMPORT	_HOS_int_cnt				; ���荞�݃l�X�g��
				IMPORT	_HOS_int_sp					; ���荞�ݎ��X�^�b�N�ޔ�
				
_HOS_CpuExceptionHandler
			; ---- System���[�h�Ɉڍs���ă��W�X�^�ޔ�
				mov		r13, #I_Bit:OR:F_Bit:OR:Mode_SYS
				msr		cpsr_csxf, r13
				stmfd	sp!, {r1-r3, ip, lr}		; �ėp���W�X�^�ޔ�

			; ---- ���̃��[�h�ɖ߂���spsr�ۑ�
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_UND
				msr		cpsr_c, r1
				mrs		r1, spsr					; spsr ���o��
				mov		r2, lr						; ���荞�ݕ��A��ۑ�
				
			; ---- USR���[�h�Ɉڍs
				mov		r3, #I_Bit:OR:F_Bit:OR:Mode_USR
				msr		cpsr_c, r3
				
			; ---- ���W�X�^�ޔ�
				stmfd	sp!, {r0-r2}				; a1, spsr_irq, lr_irq �ۑ�
				
			; ---- ���d���荞�݃`�F�b�N
				ldr		r0, =_HOS_int_cnt
				ldr		r1, [r0]					; ���荞�݃l�X�g�J�E���^�擾
				cmp		r1, #0
				add		r1, r1, #1					; ���荞�݃l�X�g�J�E���^�C���N�������g
				str		r1, [r0]
				bne		MultipleInt					; ���荞�ݒ��Ȃ番��
				
			; ---- �X�^�b�N�̓���ւ�
				ldr		r0, =_HOS_int_sp
				str		sp, [r0]					; �X�^�b�N�|�C���^��ޔ�
				ldr		r0, =kernel_int_sp
				ldr		sp, [r0]					; ���荞�ݗp�X�^�b�N��ݒ�

			; ---- CPU��O�n���h�������̊J�n
				bl		kernel_sta_exc				; CPU��O�n���h���J�n����
				bl		kernel_exe_exc				; ���荞�ݏ������s
			
			; ---- �X�^�b�N�̕��A
				ldr		r0, =_HOS_int_sp
				ldr		sp, [r0]					; �X�^�b�N�|�C���^�𕜋A
			
			; ---- ���荞�݃l�X�g�J�E���g�f�N�������g
				ldr		r0, =_HOS_int_cnt
				mov		r1, #0
				str		r1, [r0]					; ���荞�݃l�X�g�J�E���^�N���A
			
			; ---- �x���f�B�X�p�b�`���s
				bl		kernel_end_exc				; �x���f�B�X�p�b�`���s
			
			; ---- CPU��O�n���h������̕��A
ReturnExc		
				IMPORT	_HOS_swi_ret
				ldmfd	sp!, {r0-r2}
				ldr		r3, =_HOS_swi_ret
				stmia	r3, {r0-r2}					; ���荞�ݕ��A�f�[�^�ݒ�
				ldmfd	sp!, {r1-r3, ip, lr}		; ���W�X�^���A
				mov		a1, #2
				swi		0x10


			;---- ���荞�ݒ��̏���
MultipleInt
			; ---- ���荞�ݏ���
				bl		kernel_sta_exc				; CPU��O�n���h���J�n����

			; ---- ���荞�݃l�X�g�J�E���g�f�N�������g
				ldr		r0, =_HOS_int_sp
				ldr		r1, [r0]
				add		r1, r1, #1
				str		r1, [r0]

				b		ReturnExc



				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
