// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    CRE_MPF API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2006 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_CreMpl_h__
#define __HOSV4CFG_CreMpl_h__


#include "apidef.h"
#include "parpack.h"


// CRE_MPL �p
class CApiCreMpl : public CApiDef
{
public:
	CApiCreMpl();		// �R���X�g���N�^
	~CApiCreMpl();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	void  WriteId(FILE* fp);					// ID ��`�t�@�C�������o��
	void  WriteCfgDef(FILE* fp);				// cfg�t�@�C����`�������o��
	void  WriteCfgIni(FILE* fp);				// cfg�t�@�C���������������o��
	void  WriteCfgStart(FILE* fp);				// cfg�t�@�C���N���������o��
};


#endif	// __HOSV4CFG_CreMpl_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2006 by Project HOS                                    
// ---------------------------------------------------------------------------
