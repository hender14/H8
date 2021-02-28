// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    �G���[�R�[�h�Ǘ�                                                        
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_DefErrorCode_h__
#define __HOSV4CFG_DefErrorCode_h__


// ����n�G���[�R�[�h��` */
#define CFG_ERR_NOPROC			(-2)	// ������
#define CFG_ERR_COMPLETE		(-1)	// ����
#define CFG_ERR_OK				0		// ����

// �ُ�n�G���[�R�[�h��`
#define CFG_ERR_EOF				1		// �\������EOF
#define CFG_ERR_CR				2		// �s���ȉ��s
#define CFG_ERR_STATE_LEN		3		// �P�X�e�[�g����������
#define CFG_ERR_SYNTAX			4		// �\���G���[
#define CFG_ERR_PAREN			5		// ()�̕s����
#define CFG_ERR_BRACE			6		// {}�̕s����
#define CFG_ERR_SEMICOLON		7		// �Z�~�R����������
#define CFG_ERR_TEXT			8		// �s���ȕ�����萔
#define CFG_ERR_ID_CONFLICT		9		// ID�Փ�
#define CFG_ERR_PARAM			10		// �p�����[�^�[�s��
#define CFG_ERR_MULTIDEF		11		// �B��ł���ׂ���`������
#define CFG_ERR_DEF_CONFLICT		12		// ID�Փ�


const char* GetErrMessage(int iErr);


#endif	// __HOSV4CFG_DefErrorCode_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
