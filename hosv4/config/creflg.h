// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    CRE_FLG API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_CreFlg_h__
#define __HOSV4CFG_CreFlg_h__


#include "apidef.h"
#include "parpack.h"


// CRE_FLG �p
class CApiCreFlg : public CApiDef
{
public:
	CApiCreFlg();		// �R���X�g���N�^
	~CApiCreFlg();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	void  WriteId(FILE* fp);					// ID ��`�t�@�C�������o��
	void  WriteCfgDef(FILE* fp);				// cfg�t�@�C����`�������o��
	void  WriteCfgIni(FILE* fp);				// cfg�t�@�C���������������o��
	void  WriteCfgStart(FILE* fp);				// cfg�t�@�C���N���������o��
};


#endif	// __HOSV4CFG_CreFlg_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
