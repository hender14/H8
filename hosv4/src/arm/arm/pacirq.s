; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                     
;    �v���Z�b�T���ۉ��R���|�[�l���g (ARM�p)                                   
;    IRQ��O�n���h��                                                          
;                                                                             
;                                     Copyright (C) 1998-2002 by Project HOS  
;                                     http://sourceforge.jp/projects/hos/     
; --------------------------------------------------------------------------- 


				INCLUDE	pacarm.inc



				AREA	inthdr_code, CODE, READONLY
				CODE32

				EXPORT	_HOS_IrqHandler

; ----------------------------------------------
;  IRQ �n���h��
; ----------------------------------------------
				IMPORT	hos_arm_sta_irq				; IRQ�̏���������
				IMPORT	hos_arm_end_irq				; IRQ�̏I������
				IMPORT	kernel_sta_int				; ���荞�݊J�n����
				IMPORT	kernel_end_int				; ���荞�ݏI������
				IMPORT	kernel_exe_int				; ���荞�ݏ����̎��s
				IMPORT	kernel_int_sp				; ���荞�ݗp�X�^�b�N�A�h���X
				IMPORT	kernel_int_cnt				; ���荞�݃l�X�g��
				IMPORT	kernel_int_ssp				; ���荞�ݎ��X�^�b�N�ޔ�
				
_HOS_IrqHandler
				sub		lr, lr, #4					; ���^�[���A�h���X�Z�o
			
			; ---- System���[�h�Ɉڍs���ă��W�X�^�ޔ�
				mov		r13, #I_Bit:OR:F_Bit:OR:Mode_SYS
				msr		cpsr_csxf, r13
				stmfd	sp!, {r1-r3, ip, lr}		; �ėp���W�X�^�ޔ�

			; ---- IRQ���[�h�ɖ߂���spsr�ۑ�				
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_IRQ
				msr		cpsr_c, r1
				mrs		r1, spsr					; spsr ���o��
				mov		r2, lr						; ���荞�ݕ��A��ۑ�
				
			; ---- USR���[�h�Ɉڍs
				mov		r3, #I_Bit:OR:F_Bit:OR:Mode_USR
				msr		cpsr_c, r3
				
			; ---- ���W�X�^�ޔ�
				stmfd	sp!, {r0-r2}				; a1, spsr_irq, lr_irq �ۑ�
				
			; ---- ���d���荞�݃`�F�b�N
				ldr		r0, =kernel_int_cnt
				ldr		r1, [r0]					; ���荞�݃l�X�g�J�E���^�擾
				cmp		r1, #0
				add		r1, r1, #1					; ���荞�݃l�X�g�J�E���^�C���N�������g
				str		r1, [r0]
				bne		MultipleInt					; ���d���荞�݂Ȃ番��
				
			; ---- �X�^�b�N�̓���ւ�
				ldr		r0, =kernel_int_ssp
				str		sp, [r0]					; �X�^�b�N�|�C���^��ޔ�
				ldr		r0, =kernel_int_sp
				ldr		sp, [r0]					; ���荞�ݗp�X�^�b�N��ݒ�

			; ---- ���荞�ݏ����̊J�n
				bl		kernel_sta_int
				
			; ---- ���荞�ݏ���
				bl      hos_arm_sta_irq				; IRQ�J�n����(�����ݔԍ��擾)
				bl		kernel_exe_int				; ���荞�ݏ������s
				bl		hos_arm_end_irq				; IRQ�I������
			
			; ---- �X�^�b�N�̕��A
				ldr		r0, =kernel_int_ssp
				ldr		sp, [r0]					; �X�^�b�N�|�C���^�𕜋A
			
			; ---- ���荞�݃l�X�g�J�E���g�f�N�������g
				ldr		r0, =kernel_int_cnt
				mov		r1, #0
				str		r1, [r0]					; ���荞�݃l�X�g�J�E���^�N���A
			
			; ---- �x���f�B�X�p�b�`���s
				bl		kernel_end_int				; �x���f�B�X�p�b�`���s
			
			; ---- ���荞�݂���̕��A
ReturnInt		
				IMPORT	pac_arm_swi_ret
				ldmfd	sp!, {r0-r2}
				ldr		r3, =pac_arm_swi_ret
				stmia	r3, {r0-r2}					; ���荞�ݕ��A�f�[�^�ݒ�
				ldmfd	sp!, {r1-r3, ip, lr}		; ���W�X�^���A
				mov		a1, #2
				swi		0x10


			;---- ���d���荞�ݏ���
MultipleInt
			; ---- ���荞�ݏ���
				bl      hos_arm_sta_irq				; IRQ�J�n����(�����ݔԍ��擾)
				bl		kernel_exe_int				; ���荞�ݏ������s
				bl		hos_arm_end_irq				; IRQ�I������

			; ---- ���荞�݃l�X�g�J�E���g�f�N�������g
				ldr		r0, =kernel_int_cnt
				ldr		r1, [r0]
				sub		r1, r1, #1
				str		r1, [r0]

				b		ReturnInt



				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
