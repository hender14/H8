// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    CRE_CYC API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "crecyc.h"
#include "analyze.h"



#define CRECYC_CYCID		0
#define CRECYC_CYCATR		1
#define CRECYC_EXINF		2
#define CRECYC_CYCHDR		3
#define CRECYC_CYCTIM		4
#define CRECYC_CYCPHS		5



// �R���X�g���N�^
CApiCreCyc::CApiCreCyc()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParamSyntax[1] = 5;		// 5�p�����[�^�[�̃u���b�N
	m_iParams = 2;
}

// �f�X�g���N�^
CApiCreCyc::~CApiCreCyc()
{
}


// API�̉��
int CApiCreCyc::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "CRE_CYC") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_CYCID") == 0 )
	{
		int iId;

		if ( m_iMaxId > 0 )
		{
			return CFG_ERR_MULTIDEF;
		}

		if ( m_iResObj > 0 )
		{
			return CFG_ERR_DEF_CONFLICT;
		}

		if ( (iId = atoi(pszParams)) <= 0 )
		{
			return CFG_ERR_PARAM;
		}

		m_iMaxId = iId;

		return CFG_ERR_OK;
	}
	else if ( strcmp(pszApiName, "HOS_RES_CYCOBJ") == 0 )
	{
		int iId;

                if ( m_iMaxId > 0 )
		{
                        return CFG_ERR_DEF_CONFLICT;
		}

                if ( (iId = atoi(pszParams)) <= 0 )
		{
                        return CFG_ERR_PARAM;
		}

                m_iResObj += iId;

                return CFG_ERR_OK;
        }

	return CFG_ERR_NOPROC;
}


// ID ��`�t�@�C�������o��
void CApiCreCyc::WriteId(FILE* fp)
{
	int i;

	// ID ���ڎw��łȂ��I�u�W�F�N�g���݂邩�ǂ����T�[�`
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CRECYC_CYCID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* cyclic handler ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CRECYC_CYCID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CRECYC_CYCID),
				m_iId[i]);
		}
	}

	fprintf( fp,"\n#define TMAX_CYCID\t\t%d\n", m_iMaxId );
}


// cfg�t�@�C����`�������o��
void  CApiCreCyc::WriteCfgDef(FILE* fp)
{
	int  i, j;

	// �R�����g�o��
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*       create cyclic handler objects        */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* cyclic handler control block for rom area */\n"
			"const T_KERNEL_CYCCB_ROM kernel_cyccb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// �R���g���[���u���b�N(ROM��)�o��
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), (VP_INT)(%s), (FP)(%s), (RELTIM)(%s)},\n",
				m_pParamPacks[i]->GetParam(CRECYC_CYCATR),
				m_pParamPacks[i]->GetParam(CRECYC_EXINF),
				m_pParamPacks[i]->GetParam(CRECYC_CYCHDR),
				m_pParamPacks[i]->GetParam(CRECYC_CYCTIM));
		}
		fprintf(fp, "\t};\n");
	}

	// �R���g���[���u���b�N(RAM��)�o��
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* cyclic handler control block for ram area */\n"
			"T_KERNEL_CYCCB_RAM kernel_cyccb_ram[%d];\n",
			m_iObjs);
	}

	// �R���g���[���u���b�N�e�[�u���o��
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* cyclic handler control block table */\n"
			"T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[%d] =\n"
			"\t{\n",
			m_iMaxId);

		for ( i = 0; i < m_iMaxId; i++ )
		{
			// ID����
			for ( j = 0; j < m_iObjs; j++ )
			{
				if ( m_iId[j] == i + 1 )
				{
					break;
				}
			}
			if ( j < m_iObjs )
			{
				// �I�u�W�F�N�g�����݂����ꍇ
				fprintf(fp, "\t\t&kernel_cyccb_ram[%d],\n", j);
			}
			else
			{
				// �I�u�W�F�N�g�������ꍇ
				fputs("\t\tNULL,\n", fp);
			}
		}
		fputs("\t};\n", fp);
	}

	// �e�[�u���T�C�Y���o��
	fprintf(
		fp,
		"\n/* cyclic handler control block count */\n"
		"const INT kernel_cyccb_cnt = %d;\n",
		m_iMaxId);
}


// cfg�t�@�C���������������o��
void  CApiCreCyc::WriteCfgIni(FILE* fp)
{
	// �I�u�W�F�N�g���݃`�F�b�N
	if ( m_iObjs == 0 )
	{
		return;
	}

	// ���������o��
	fprintf(
		fp,
		"\t\n\t\n"
		"\t/* initialize cyclic handler control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_cyccb_ram[i].cyccb_rom = &kernel_cyccb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfg�t�@�C���N���������o��
void  CApiCreCyc::WriteCfgStart(FILE* fp)
{
	// �I�u�W�F�N�g���݃`�F�b�N
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_cyc();\t\t/* initialize cyclic handler */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
