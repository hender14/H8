// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_MAX_TPRI API �̏���                                                 
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "maxtpri.h"
#include "analyze.h"



// �R���X�g���N�^
CApiMaxTpri::CApiMaxTpri()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParams         = 1;

	m_iMaxPri = 0;
}


// �f�X�g���N�^
CApiMaxTpri::~CApiMaxTpri()
{
}



// API�̉��
int CApiMaxTpri::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	// API���`�F�b�N
	if ( strcmp(pszApiName, "HOS_MAX_TPRI") != 0 )
	{
		return CFG_ERR_NOPROC;
	}

	// ���d��`�`�F�b�N
	if ( m_iMaxPri > 0 )
	{
		return CFG_ERR_MULTIDEF;
	}

	if ( atoi(pszParams) <= 0 )
	{
		return CFG_ERR_PARAM;
	}
	m_iMaxPri = atoi(pszParams);

	return CFG_ERR_OK;
}


// �������W�J
int CApiMaxTpri::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfg�t�@�C����`�������o��
void  CApiMaxTpri::WriteCfgDef(FILE* fp)
{
	if ( m_iMaxPri == 0 )
	{
		m_iMaxPri = DEFAULT_MAXTPRI;

	}

	fprintf(
		fp,
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*           create ready queue               */\n"
		"/* ------------------------------------------ */\n"
		"\n"
		"T_MKNL_QUE mknl_rdq_tbl[%d];\n"
		"const INT  mknl_rdq_cnt = %d;\n",
		m_iMaxPri,
		m_iMaxPri);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
