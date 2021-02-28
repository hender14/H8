// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    INCLUDE API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "apiinc.h"
#include "analyze.h"



// �R���X�g���N�^
CApiInclude::CApiInclude()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParams         = 1;
}


// �f�X�g���N�^
CApiInclude::~CApiInclude()
{
}



// API�̉��
int CApiInclude::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	char szBuf[4096];
	int  iErr;
	
	// API���`�F�b�N
	if ( strcmp(pszApiName, "INCLUDE") != 0 )
	{
		return CFG_ERR_NOPROC;
	}

	// �p�����[�^�[�ǉ�
	iErr = AddParams(pszParams);
	if ( iErr != CFG_ERR_OK )
	{
		return iErr;
	}

	// ������̓W�J
	iErr = CAnalyze::DecodeText(szBuf, m_pParamPacks[m_iObjs - 1]->GetParam(0));
	if ( iErr != CFG_ERR_OK )
	{
		return iErr;
	}
	m_pParamPacks[m_iObjs - 1]->SetParam(0, szBuf);

	return CFG_ERR_OK;
}


// �������W�J
int CApiInclude::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfg�t�@�C����`�������o��
void  CApiInclude::WriteCfgDef(FILE* fp)
{
	int i;

	if ( m_iObjs == 0)
	{
		return;
	}

	fputs("\n", fp);

	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(fp, "#include %s\n", m_pParamPacks[i]->GetParam(0));
	}
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
