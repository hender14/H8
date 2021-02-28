// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    DEF_TEX API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "deftex.h"
#include "analyze.h"


#define DEFTEX_TSKID		0
#define DEFTEX_TEXATR		1
#define DEFTEX_TEXRTN		2



// �R���X�g���N�^
CApiDefTex::CApiDefTex()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParamSyntax[1] = 2;		// 2�p�����[�^�[�̃u���b�N
	m_iParams = 2;
}

// �f�X�g���N�^
CApiDefTex::~CApiDefTex()
{
}


// API�̉��
int CApiDefTex::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "DEF_TEX") == 0 )
	{
		return AddParams(pszParams);
	}

	return CFG_ERR_NOPROC;
}


// ����ID�ԍ����蓖��
int CApiDefTex::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfg�t�@�C����`�������o��
void  CApiDefTex::WriteCfgDef(FILE* fp)
{
	int  i;

	if ( m_iObjs <= 0 )
	{
		return;
	}

	// �R�����g�o��
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*          task exception objects            */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	fprintf(
		fp,
		"\n/* task exception control block */\n"
		"const T_KERNEL_TEXCB_RAM kernel_texcb_ram[%d] =\n"
		"\t{\n",
		m_iObjs);

	// �R���g���[���u���b�N(ROM��)�o��
	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(
			fp,
			"\t\t{0, (FP)(%s)},\n",
			m_pParamPacks[i]->GetParam(DEFTEX_TEXRTN));
	}
	fprintf(fp, "\t};\n");
}


// cfg�t�@�C���������������o��
void  CApiDefTex::WriteCfgIni(FILE* fp)
{
	int i;

	// �I�u�W�F�N�g���݃`�F�b�N
	if ( m_iObjs == 0 )
	{
		return;
	}

	// ���������o��
	fputs(
		"\t\n\t\n"
		"\t/* initialize task exception handler */\n",
		fp);

	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(
			fp,
			"\tkernel_tcb_ram_tbl[(%s) - TMIN_TSKID]->texcb = &kernel_texcb_rom[%d];\n",
			m_pParamPacks[i]->GetParam(DEFTEX_TSKID),
			i);
	}
}



// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
