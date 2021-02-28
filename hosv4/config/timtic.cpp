// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_TIM_TIC API �̏���                                                  
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "timtic.h"
#include "analyze.h"


#define TIMTIC_NUME		0
#define TIMTIC_DENO		1


// �R���X�g���N�^
CApiTimTic::CApiTimTic()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParamSyntax[1] = 0;		// �P�ƃp�����[�^�[
	m_iParams         = 2;

	m_iNume = 1;
	m_iDeno = 1;
}


// �f�X�g���N�^
CApiTimTic::~CApiTimTic()
{
}



// API�̉��
int CApiTimTic::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	int iNume;
	int iDeno;
	int iErr;

	// API���`�F�b�N
	if ( strcmp(pszApiName, "HOS_TIM_TIC") == 0 )
	{
		if ( m_iObjs > 0 )
		{
			return CFG_ERR_MULTIDEF;
		}

		iErr = AddParams(pszParams);
		if ( iErr != CFG_ERR_OK )
		{
			return iErr;
		}
	
		iNume = atoi(m_pParamPacks[m_iObjs - 1]->GetParam(TIMTIC_NUME));
		iDeno = atoi(m_pParamPacks[m_iObjs - 1]->GetParam(TIMTIC_DENO));
		if ( iNume <= 0 || iDeno <= 0 )
		{
			return CFG_ERR_PARAM;
		}

		m_iNume = iNume;
		m_iDeno = iDeno;
		
		return CFG_ERR_OK;
	}

	return CFG_ERR_NOPROC;
}


// �������W�J
int CApiTimTic::AutoId(void)
{
	return CFG_ERR_OK;
}


// ID ��`�t�@�C�������o��
void CApiTimTic::WriteId(FILE* fp)
{
	fprintf(
		fp,
		"\n\n"
		"/* time tic */\n"
		"#define TIC_NUME\t\t%d\n"
		"#define TIC_DENO\t\t%d\n",
		m_iNume,
		m_iDeno);
}


// cfg�t�@�C����`�������o��
void  CApiTimTic::WriteCfgDef(FILE* fp)
{
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*               set time tic                 */\n"
		"/* ------------------------------------------ */\n"
		"\n"
		"const UW kernel_tic_deno = TIC_DENO;\n"
		"const UW kernel_tic_div  = TIC_NUME / TIC_DENO;\n"
		"const UW kernel_tic_mod  = TIC_NUME % TIC_DENO;\n",
		fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
