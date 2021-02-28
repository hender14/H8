// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_INT_STK API �̏���                                                  
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_IntStack_h__
#define __HOSV4CFG_IntStack_h__


#include "apidef.h"
#include "parpack.h"


// HOS_KERNEL_HEAP �p
class CApiIntStack : public CApiDef
{
public:
	CApiIntStack();		// �R���X�g���N�^
	~CApiIntStack();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);
	void  WriteCfgDef(FILE* fp);		// cfg�t�@�C����`�������o��

protected:
	char  m_szStackPointer[API_MAX_PARAM];
};


#endif	// __HOSV4CFG_IntStack_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
