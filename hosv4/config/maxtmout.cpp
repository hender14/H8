// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_MAX_TIMOUT API �̏���                                               
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "maxtmout.h"
#include "analyze.h"



// �R���X�g���N�^
CApiMaxTimout::CApiMaxTimout()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParams         = 1;

	m_iMaxTimout = 0;
}


// �f�X�g���N�^
CApiMaxTimout::~CApiMaxTimout()
{
}



// API�̉��
int CApiMaxTimout::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	// API���`�F�b�N
	if ( strcmp(pszApiName, "HOS_MAX_TIMOUT") != 0 )
	{
		return CFG_ERR_NOPROC;
	}

	if ( m_iMaxTimout > 0 )
	{
		return CFG_ERR_MULTIDEF;
	}

	if ( atoi(pszParams) <= 0 )
	{
		return CFG_ERR_PARAM;
	}
	m_iMaxTimout = atoi(pszParams);

	return CFG_ERR_OK;
}


// �������W�J
int CApiMaxTimout::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfg�t�@�C����`�������o��
void  CApiMaxTimout::WriteCfgDef(FILE* fp)
{
	if ( m_iMaxTimout == 0 )
	{
		m_iMaxTimout = DEFAULT_MAXTIMOUT;
	}

	fprintf(
		fp,
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*          create time-out queue             */\n"
		"/* ------------------------------------------ */\n"
		"\n"
		"T_MKNL_TIMOUT mknl_timout[%d];\n"
		"const INT     mknl_timout_size = %d;\n",
		m_iMaxTimout,
		m_iMaxTimout);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
