// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_MAX_TPRI API �̏���                                                 
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiMaxTpri_h__
#define __HOSV4CFG_ApiMaxTpri_h__


#include "apidef.h"
#include "parpack.h"


// HOS_MAX_TPRI �p
class CApiMaxTpri : public CApiDef
{
public:
	CApiMaxTpri();		// �R���X�g���N�^
	~CApiMaxTpri();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);							// ����ID�ԍ����蓖��
	void  WriteCfgDef(FILE* fp);				// cfg�t�@�C����`�������o��

protected:
	int m_iMaxPri;
};


#define DEFAULT_MAXTPRI	16


#endif	// __HOSV4CFG_ApiMaxTpri_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------

