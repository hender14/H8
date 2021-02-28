// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_KERNEL_HEAP API �̏���                                              
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "knlheap.h"
#include "analyze.h"



// �R���X�g���N�^
CApiKernelHeap::CApiKernelHeap()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParams = 1;
}


// �f�X�g���N�^
CApiKernelHeap::~CApiKernelHeap()
{
}


// ����ID�ԍ����蓖��
int CApiKernelHeap::AutoId(void)
{
	return CFG_ERR_OK;
}


// API�̉��
int CApiKernelHeap::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "HOS_KERNEL_HEAP") == 0 )
	{
		if ( m_iObjs > 0 )
	  	{
			return CFG_ERR_MULTIDEF;
	  	}

		return AddParams(pszParams);
	}

	return CFG_ERR_NOPROC;
}


// cfg�t�@�C����`�������o��
void  CApiKernelHeap::WriteCfgDef(FILE* fp)
{
	if ( m_iObjs <= 0 )
	{
		return;
	}

	if ( strcmp(m_pParamPacks[0]->GetParam(0), "0") == 0 )
	{
		return;
	}

	// �R�����g�o��
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*                kernel heap                 */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// �q�[�v�̈搶��
	fprintf(
		fp,
		"\n"
		"VP kernel_heap_mem[((%s) + sizeof(VP) - 1) / sizeof(VP)];\t/* kernel heap */\n",
		m_pParamPacks[0]->GetParam(0));
}


// cfg�t�@�C���N���������o��
void  CApiKernelHeap::WriteCfgStart(FILE* fp)
{
	if ( m_iObjs <= 0 )
	{
		return;
	}
	
	if ( strcmp(m_pParamPacks[0]->GetParam(0), "0") == 0 )
	{
		return;
	}
	
	fputs("\tkernel_ini_mem(kernel_heap_mem, sizeof(kernel_heap_mem));\t\t/* initialize kernel heap */\n\n", fp);
}



// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
