; --------------------------------------------------------------------------- 
;  HOS-V4                                                                     
;    �v���Z�b�T���ۉ��R���|�[�l���g (LSI-C86 �X���[�����f���p)                
;                                                                             
;                                     Copyright (C) 1998-2002 by Project HOS  
;                                     http://sourceforge.jp/projects/hos/     
; --------------------------------------------------------------------------- 


TEXT			CSEG

; -----------------------------------------------
;  ���荞�݋֎~
;  void hospac_dis_int(void)
; -----------------------------------------------
hospac_dis_int_::
				cli					; ���荞�݋֎~
				ret


; -----------------------------------------------
;  ���荞�݋���
;  void hospac_ena_int(void)
; -----------------------------------------------
hospac_ena_int_::
				sti					; ���荞�݋���
				ret


; -----------------------------------------------
;  ���s�R���e�L�X�g�G���g���[�A�h���X
; -----------------------------------------------
ctx_entry:		
				mov		ax, dx		; ���s���p�����[�^��������ɐݒ�
				jmp		cx			; ���s�A�h���X�ɕ���


; -----------------------------------------------
;  ���s�R���e�L�X�g�̍쐬
;  void hospac_cre_ctx_asm(
;		T_HOSPAC_CTXINF *pk_ctxinf,	/* �쐬����R���e�L�X�g */
;		VP     sp,					/* �X�^�b�N�|�C���^ */
;		void   (*task)(VP_INT),		/* ���s�A�h���X */
;		VP_INT exinf				/* ���s���p�����[�^ */
;		)
; -----------------------------------------------
hospac_cre_ctx_asm_::
				sub		bx, 2
				mov		[bx].w, ctx_entry
				sub		bx, 8
				mov		[bx], dx
				sub		bx, 2
				mov		[bx], cx
				
				xchg	ax, bx
				mov		[bx], ax
				ret


; -----------------------------------------------
;  ���s�R���e�L�X�g�̐ؑ�
;  void hospac_swi_ctx(
;		T_HOSPAC_CTXINF *pk_pre_ctxinf,	/* ���݂̃R���e�L�X�g�̕ۑ��� */
;		T_HOSPAC_CTXINF *pk_nxt_ctxinf	/* �؂�ւ���R���e�L�X�g */
;		)
; -----------------------------------------------
hospac_swi_ctx_::
				push	bp
				push	di
				push	si
				push	dx
				push	cx
				xchg	ax, bx
				mov		[bx], sp
				mov		bx, ax
				mov		sp, [bx]
				pop		cx
				pop		dx
				pop		si
				pop		di
				pop		bp
				ret


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
