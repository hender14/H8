// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    ATT_ISR API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "attisr.h"
#include "analyze.h"


#define ATTISR_ISRATR		0
#define ATTISR_EXINF		1
#define ATTISR_INTNO		2
#define ATTISR_ISR			3


// �R���X�g���N�^
CApiAttIsr::CApiAttIsr()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 4;		// 4�̃p�����[�^�[�u���b�N
	m_iParams = 1;

	m_iMaxIntNo = 0;
	m_iMinIntNo = 0;
	m_iMaxIsrId = 0;
}

// �f�X�g���N�^
CApiAttIsr::~CApiAttIsr()
{
}


// ����ID�ԍ����蓖��
int CApiAttIsr::AutoId(void)
{
	return CFG_ERR_OK;
}


// API�̉��
int CApiAttIsr::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	static bool blExMax = false;
	static bool blExMin = false;
	static bool blExMid = false;

	if ( strcmp(pszApiName, "ATT_ISR") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_INTNO") == 0 )
	{
		int iIntNo;

		if ( blExMax == true )
		{
			return CFG_ERR_MULTIDEF;
		}

		blExMax = true;

		if ( (iIntNo = atoi(pszParams)) < 0 )
		{
			return CFG_ERR_PARAM;
		}

		m_iMaxIntNo = iIntNo;

		return CFG_ERR_OK;
	}
	else if ( strcmp(pszApiName, "HOS_MIN_INTNO") == 0 )
	{
		int iIntNo;

		if ( blExMin == true )
		{
			return CFG_ERR_MULTIDEF;
		}

		blExMin = true;

		if ( (iIntNo = atoi(pszParams)) < 0 )
		{
			return CFG_ERR_PARAM;
		}

		m_iMinIntNo = iIntNo;

		return CFG_ERR_OK;
	}
	else if ( strcmp(pszApiName, "HOS_MAX_ISRID") == 0 )
	{
		int iId;

		if ( blExMid == true )
		{
			return CFG_ERR_MULTIDEF;
		}

		blExMid = true;

		if ( (iId = atoi(pszParams)) < 0 )
		{
			return CFG_ERR_PARAM;
		}
		if ( iId > m_iMaxIsrId )
		{
			m_iMaxIsrId = iId;
		}
		return CFG_ERR_OK;
	}

	return CFG_ERR_NOPROC;
}


// cfg�t�@�C����`�������o��
void  CApiAttIsr::WriteCfgDef(FILE* fp)
{
	int i,j;

	// �ő劄�荞�ݔԍ����m�F
	if ( m_iMaxIntNo == 0 )
	{
		for ( i = 0; i < m_iObjs; i++ )
			if (( j = atoi( m_pParamPacks[i]->GetParam(ATTISR_INTNO))) > m_iMaxIntNo )
				m_iMaxIntNo = j;
	}

	// �R�����g�o��
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*        interrupt control objects           */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// ���荞�݊Ǘ��e�[�u������
	fprintf(
		fp,
		"\n"
		"/* interrupt control */\n"
		"T_KERNEL_INTCB kernel_intcb_tbl[%d];\t\t/* interrupt control block table */\n"
		"const INT      kernel_intcb_cnt = %d;\t\t/* interrupt control block count */\n"
		"const INTNO    kernel_min_intno = %d;\t\t/* minimum intrrupt number */\n",
		m_iMaxIntNo - m_iMinIntNo + 1,
		m_iMaxIntNo - m_iMinIntNo + 1,
		m_iMinIntNo);
	
	// ISR�R���g���[���e�[�u������
	if ( m_iMaxIsrId > 0 )
	{
		fprintf(
			fp,
			"\n"
			"/* interrupt service routine control */\n"
			"T_KERNEL_ISRCB kernel_isrcb_tbl[%d];\t\t/* ISR control block table */\n"
			"const INT      kernel_isrcb_cnt = %d;\t\t/* ISR control block count */\n",
			m_iMaxIsrId,
			m_iMaxIsrId);
	}
	else
	{
		fprintf(
			fp,
			"\n"
			"/* interrupt service routine control */\n"
			"const INT      kernel_isrcb_cnt = %d;\t\t/* ISR control block count */\n",
			m_iMaxIsrId);
	}
}


// cfg�t�@�C���������������o��
void  CApiAttIsr::WriteCfgIni(FILE* fp)
{
	int i;

	// �I�u�W�F�N�g���݃`�F�b�N
	if ( m_iObjs == 0 )
	{
		return;
	}

	// �R�����g�o��
	fputs("\n\t/* initialize interrupt table */\n", fp);
	
	// ���������o��
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( m_iMinIntNo )
		{
			fprintf(
				fp,
				"\tkernel_intcb_tbl[%s-%d].exinf = (VP_INT)(%s);\n"
				"\tkernel_intcb_tbl[%s-%d].isr   = (FP)(%s);\n",
				m_pParamPacks[i]->GetParam(ATTISR_INTNO),
				m_iMinIntNo,
				m_pParamPacks[i]->GetParam(ATTISR_EXINF),
				m_pParamPacks[i]->GetParam(ATTISR_INTNO),
				m_iMinIntNo,
				m_pParamPacks[i]->GetParam(ATTISR_ISR));
		}
		else
		{
			fprintf(
				fp,
				"\tkernel_intcb_tbl[%s].exinf = (VP_INT)(%s);\n"
				"\tkernel_intcb_tbl[%s].isr   = (FP)(%s);\n",
				m_pParamPacks[i]->GetParam(ATTISR_INTNO),
				m_pParamPacks[i]->GetParam(ATTISR_EXINF),
				m_pParamPacks[i]->GetParam(ATTISR_INTNO),
				m_pParamPacks[i]->GetParam(ATTISR_ISR));
		}
	}
}



// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
