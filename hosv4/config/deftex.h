// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    DEF_TEX API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_DefTex_h__
#define __HOSV4CFG_DefTex_h__


#include "apidef.h"
#include "parpack.h"


// DEF_TEX �p
class CApiDefTex : public CApiDef
{
public:
	CApiDefTex();		// �R���X�g���N�^
	~CApiDefTex();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);							// ����ID�ԍ����蓖��
	void  WriteCfgDef(FILE* fp);				// cfg�t�@�C����`�������o��
	void  WriteCfgIni(FILE* fp);				// cfg�t�@�C���������������o��
};


#endif	// __HOSV4CFG_DefTex_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
