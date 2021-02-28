// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    ATT_INI API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "attini.h"
#include "analyze.h"

#define ATTINI_INIATR		0
#define ATTINI_EXINF		1
#define ATTINI_INIRTN		2


// �R���X�g���N�^
CApiAttIni::CApiAttIni()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 3;		// �P�ƃp�����[�^�[
	m_iParams         = 1;
}


// �f�X�g���N�^
CApiAttIni::~CApiAttIni()
{
}



// API�̉��
int CApiAttIni::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "ATT_INI") == 0 )
	{
		return AddParams(pszParams);
	}

	return CFG_ERR_NOPROC;
}


// �������W�J
int CApiAttIni::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfg�t�@�C����`�������o��
void  CApiAttIni::WriteCfgStart(FILE* fp)
{
	int i;

	if ( m_iObjs == 0)
	{
		return;
	}

	fputs("\n\t/* call initialize routine*/\n", fp);

	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(
			fp,
			"\t((FP)(%s))((VP_INT)(%s));\n",
			m_pParamPacks[i]->GetParam(ATTINI_INIRTN),
			m_pParamPacks[i]->GetParam(ATTINI_EXINF)
			);
	}
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
