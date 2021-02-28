// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    HOS_IDL_STK API �̏���                                                  
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "idlstk.h"
#include "analyze.h"


#define IDLSTK_STKSZ		0
#define IDLSTK_STK			1


// �R���X�g���N�^
CApiIdleStack::CApiIdleStack()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParams = 2;
}


// �f�X�g���N�^
CApiIdleStack::~CApiIdleStack()
{
}


// ����ID�ԍ����蓖��
int CApiIdleStack::AutoId(void)
{
	return CFG_ERR_OK;
}


// API�̉��
int CApiIdleStack::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "HOS_IDL_STK") == 0 )
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
void  CApiIdleStack::WriteCfgDef(FILE* fp)
{
	const char* pszSize;
	const char* pszStack;

	// �R�����g�o��
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*                 idle stack                 */\n"
		"/* ------------------------------------------ */\n\n"
		, fp);

	// �p�����[�^�ǂݏo��
	if ( m_iObjs > 0 )
	{
		pszSize  = m_pParamPacks[0]->GetParam(IDLSTK_STKSZ);
		pszStack = m_pParamPacks[0]->GetParam(IDLSTK_STK);
	}
	else
	{
		pszSize  = "128";		// �w�肪������΃f�t�H���g�T�C�Y
		pszStack = "NULL";		// �w�肪�������NULL(��������)
	}

	// �A�C�h�����[�v�p�X�^�b�N�o��
	if ( strcmp(pszStack, "NULL") == 0 )
	{
		fprintf(
			fp,
			"VP         mknl_idl_stkblk[((%s) + sizeof(VP) - 1) / sizeof(VP)];\t/* idle stack block*/\n"
			"const VP   mknl_idl_stk   = (VP)(mknl_idl_stkblk);\t/* idle stack */\n"
			"const SIZE mknl_idl_stksz = (SIZE)sizeof(mknl_idl_stkblk);\t/* idle stack size */\n",
			pszSize);
	}
	else
	{
		fprintf(
			fp,
			"const VP   mknl_idl_stk   = (VP)(%s);\t/* idle stack */\n"
			"const SIZE mknl_idl_stksz = (SIZE)(%s);\t/* idle stack */\n",
			pszStack,pszSize);
	}
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
