// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    ATT_ISR API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_AttIsr_h__
#define __HOSV4CFG_AttIsr_h__


#include "apidef.h"
#include "parpack.h"


// ATT_ISR �p
class CApiAttIsr : public CApiDef
{
public:
	CApiAttIsr();		// �R���X�g���N�^
	~CApiAttIsr();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);
	void  WriteCfgDef(FILE* fp);	// cfg�t�@�C����`�������o��
	void  WriteCfgIni(FILE* fp);	// cfg�t�@�C���������������o��

protected:
	int m_iMaxIntNo;
	int m_iMinIntNo;
	int m_iMaxIsrId;
};


#endif	// __HOSV4CFG_AttIsr_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
