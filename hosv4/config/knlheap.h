// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_KERNEL_HEAP API �̏���                                              
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_KernelHeap_h__
#define __HOSV4CFG_KernelHeap_h__


#include "apidef.h"
#include "parpack.h"


// HOS_KERNEL_HEAP �p
class CApiKernelHeap : public CApiDef
{
public:
	CApiKernelHeap();		// �R���X�g���N�^
	~CApiKernelHeap();		// �f�X�g���N�^

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// API�̉��
	int   AutoId(void);
	void  WriteCfgDef(FILE* fp);		// cfg�t�@�C����`�������o��
	void  WriteCfgStart(FILE* fp);		// cfg�t�@�C���N���������o��
};


#endif	// __HOSV4CFG_KernelHeap_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
