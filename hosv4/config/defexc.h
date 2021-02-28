// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    DEF_EXC API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_DefExc_h__
#define __HOSV4CFG_DefExc_h__


#include "apidef.h"
#include "parpack.h"


// DEF_EXC �p
class CApiDefExc : public CApiDef
{
public:
	CApiDefExc();		// �R���X�g���N�^
	~CApiDefExc();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);
	void  WriteCfgDef(FILE* fp);	// cfg�t�@�C����`�������o��
	void  WriteCfgIni(FILE* fp);	// cfg�t�@�C���������������o��

protected:
	int m_iMaxExcNo;
	int m_iMinExcNo;
};


#endif	// __HOSV4CFG_DefExc_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
