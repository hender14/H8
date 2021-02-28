// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    ATT_INI API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiAttIni_h__
#define __HOSV4CFG_ApiAttIni_h__


#include "apidef.h"
#include "parpack.h"


// ATT_INI �p
class CApiAttIni : public CApiDef
{
public:
	CApiAttIni();		// �R���X�g���N�^
	~CApiAttIni();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);							// ����ID�ԍ����蓖��
	void  WriteCfgStart(FILE* fp);				// cfg�t�@�C����`�������o��
};


#endif	// __HOSV4CFG_ApiAttIni_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
