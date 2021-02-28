// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    �G���[�R�[�h�Ǘ�                                                        
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include "defercd.h"


static const char *szErrMsg[] =
	{
		"unanticipated EOF.",		// �\������EOF
		"illegal CR.",				// �s���ȉ��s
		"status too long.",			// �P�X�e�[�g����������
		"syntax error."	,			// �\���G���[
		"expect \')\' but found.",	// ()�̕s����
		"expect \'}\' but found.",	// {}�̕s����
		"expect \';\' but found.",	// �Z�~�R����������
		"illegal text.",			// �s���ȕ�����萔
		"conflict ID.",				// ID�Փ�
		"illegal parameter.",		 // �p�����[�^�[�s��
		"multiple definition.",		// �B��ł���ׂ�API��`������
		"conflict definition.",		 // ��`�Փ�
	};


// �G���[������擾
const char* GetErrMessage(int iErr)
{
	if ( iErr < 1 || iErr > (int)(sizeof(szErrMsg)/sizeof(char *)) )
	{
		return "unknown expression error.";
	}

	return szErrMsg[iErr - 1];
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
