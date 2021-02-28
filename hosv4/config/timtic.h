// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_TIM_TIC API �̏���                                                  
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiTimTic_h__
#define __HOSV4CFG_ApiTimTic_h__


#include "apidef.h"
#include "parpack.h"


// HOS_TIM_TIC �p
class CApiTimTic : public CApiDef
{
public:
	CApiTimTic();		// �R���X�g���N�^
	~CApiTimTic();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);							// ID ��`�t�@�C�������o��
	void  WriteId(FILE* fp);					// cfg�t�@�C����`�������o��
	void  WriteCfgDef(FILE* fp);				// cfg�t�@�C����`�������o��

protected:
	int m_iNume;	// �^�C���e�B�b�N�̎����̕��q
	int m_iDeno;	// �^�C���e�B�b�N�̎����̕���
};


#endif	// __HOSV4CFG_ApiTimTic_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
