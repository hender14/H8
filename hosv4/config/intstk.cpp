// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_INT_STK API �̏���                                                  
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "intstk.h"
#include "analyze.h"


#define INTSTK_STKSZ		0
#define INTSTK_STK			1


// �R���X�g���N�^
CApiIntStack::CApiIntStack()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParams = 2;

	// �X�^�b�N�|�C���^
	m_szStackPointer[0] = '\0';
}


// �f�X�g���N�^
CApiIntStack::~CApiIntStack()
{
}


// ����ID�ԍ����蓖��
int CApiIntStack::AutoId(void)
{
	return CFG_ERR_OK;
}


// API�̉��
int CApiIntStack::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "HOS_INT_STK") == 0 )
	{
		if ( m_iObjs > 0 )
		{
			return CFG_ERR_MULTIDEF;
		}

		if ( m_szStackPointer[0] != '\0' )
		{
			return CFG_ERR_DEF_CONFLICT;
		}

		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_INT_SP") == 0 )
	{
		if ( m_iObjs > 0 )
		{
			return CFG_ERR_DEF_CONFLICT;
		}

		if ( m_szStackPointer[0] != '\0' )
		{
			return CFG_ERR_MULTIDEF;
		}

		strcpy(m_szStackPointer, pszParams);
		return CFG_ERR_OK;
	}

	return CFG_ERR_NOPROC;
}


// cfg�t�@�C����`�������o��
void  CApiIntStack::WriteCfgDef(FILE* fp)
{
	const char* pszSize;
	const char* pszStack;

	// �p�����[�^�ǂݏo��
	if ( m_iObjs <= 0 && m_szStackPointer[0] == '\0' )
	{
		return ;
	}

	// �R�����g�o��
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*             interrupt stack                */\n"
		"/* ------------------------------------------ */\n\n"
		, fp);

	// ���荞�ݗp�X�^�b�N�|�C���^�o��
	if ( m_szStackPointer[0] != '\0' )
	{
		fprintf(
			fp,
			"const VP kernel_int_sp = (VP)(%s);\t/* interrupt stack pointer */\n",
			m_szStackPointer);
	}
	else
	{
		pszSize  = m_pParamPacks[0]->GetParam(INTSTK_STKSZ);
		pszStack = m_pParamPacks[0]->GetParam(INTSTK_STK);

		if ( strcmp(pszStack, "NULL") == 0 )
		{
			fprintf(
				fp,
				"VP         kernel_int_stkblk[((%s) + sizeof(VP) - 1) / sizeof(VP)];\t/* interrupt stack block*/\n"
				"const VP   kernel_int_sp  = &kernel_int_stkblk[sizeof(kernel_int_stkblk) / sizeof(VP)];\t/* interrupt stack pointer */\n",
				pszSize);
		}
		else
		{
			fprintf(
				fp,
				"const VP kernel_int_sp = (VP)((UB *)(%s) + (%s));\t/* interrupt stack pointer */\n",
				pszStack, pszSize);
		}
	}
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
