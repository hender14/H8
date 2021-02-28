// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_IDL_STK API �̏���                                                  
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_IdleStack_h__
#define __HOSV4CFG_IdleStack_h__


#include "apidef.h"
#include "parpack.h"


// HOS_KERNEL_HEAP �p
class CApiIdleStack : public CApiDef
{
public:
	CApiIdleStack();		// �R���X�g���N�^
	~CApiIdleStack();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);
	void  WriteCfgDef(FILE* fp);		// cfg�t�@�C����`�������o��
};


#endif	// __HOSV4CFG_IdleStack_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
