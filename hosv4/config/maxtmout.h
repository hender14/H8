// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_MAX_TPRI API �̏���                                                 
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiMaxTimout_h__
#define __HOSV4CFG_ApiMaxTimout_h__


#include "apidef.h"
#include "parpack.h"


// HOS_MAX_TIMOUT �p
class CApiMaxTimout : public CApiDef
{
public:
	CApiMaxTimout();		// �R���X�g���N�^
	~CApiMaxTimout();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);							// ����ID�ԍ����蓖��
	void  WriteCfgDef(FILE* fp);				// cfg�t�@�C����`�������o��

protected:
	int m_iMaxTimout;
};


#define DEFAULT_MAXTIMOUT	16

#endif	// HOSV4CFG_ApiMaxTimout


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
