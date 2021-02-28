; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  �T���v���v���O����                              
;    ���荞�݃x�N�^�[�e�[�u��                                                 
;                                                                             
;                                   Copyright (C) 1998-2006 by Project HOS    
;                                   http://sourceforge.jp/projects/hos/       
; --------------------------------------------------------------------------- 

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
		.h8300hn
#else
		.h8300h
#endif

; -----------------------------------------------
;          ���荞�݃x�N�^�e�[�u��
; -----------------------------------------------
		.section	.vectors

		.word	_startup
		.word	0xffff			;_hos_vector001; 
		.word	0xffff			;_hos_vector002; 
		.word	0xffff			;_hos_vector003; 
		.word	0xffff			;_hos_vector004; 
		.word	0xffff			;_hos_vector005; 
		.word	0xffff			;_hos_vector006; 
		.word	_hos_vector007
		.word	_hos_vector008
		.word	_hos_vector009
		.word	_hos_vector010
		.word	_hos_vector011
		.word	_hos_vector012
		.word	_hos_vector013
		.word	_hos_vector014
		.word	_hos_vector015
		.word	_hos_vector016
		.word	_hos_vector017
		.word	_hos_vector018
		.word	_hos_vector019
		.word	0xffff			;_hos_vector020; 
		.word	_hos_vector021
		.word	_hos_vector022
		.word	_hos_vector023
		.word	_hos_vector024
		.word	_hos_vector025

		.end



; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2006 by Project HOS                                     
; --------------------------------------------------------------------------- 
