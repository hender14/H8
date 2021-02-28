// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    INCLUDE API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiInclude_h__
#define __HOSV4CFG_ApiInclude_h__


#include "apidef.h"
#include "parpack.h"


// INCLUDE �p
class CApiInclude : public CApiDef
{
public:
	CApiInclude();		// �R���X�g���N�^
	~CApiInclude();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);							// ����ID�ԍ����蓖��
	void  WriteCfgDef(FILE* fp);				// cfg�t�@�C����`�������o��
};


#endif	// __HOSV4CFG_ApiInclude_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
