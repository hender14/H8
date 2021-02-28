// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    CRE_ALM API �̏���                                                      
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "crealm.h"
#include "analyze.h"


#define CREALM_ALMID		0
#define CREALM_ALMATR		1
#define CREALM_EXINF		2
#define CREALM_ALMHDR		3



// �R���X�g���N�^
CApiCreAlm::CApiCreAlm()
{
	// �p�����[�^�[�\���ݒ�
	m_iParamSyntax[0] = 0;		// �P�ƃp�����[�^�[
	m_iParamSyntax[1] = 3;		// 3�p�����[�^�[�̃u���b�N
	m_iParams = 2;
}


// �f�X�g���N�^
CApiCreAlm::~CApiCreAlm()
{
}


// API�̉��
int CApiCreAlm::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "CRE_ALM") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_ALMID") == 0 )
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
	else if ( strcmp(pszApiName, "HOS_RES_ALMOBJ") == 0 )
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
void CApiCreAlm::WriteId(FILE* fp)
{
	int i;

	// ID ���ڎw��łȂ��I�u�W�F�N�g���݂邩�ǂ����T�[�`
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREALM_ALMID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* alarm handler ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREALM_ALMID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CREALM_ALMID),
				m_iId[i]);
		}
	}

	fprintf( fp,"\n#define TMAX_ALMID\t\t%d\n", m_iMaxId );
}


// cfg�t�@�C����`�������o��
void  CApiCreAlm::WriteCfgDef(FILE* fp)
{
	int  i, j;

	// �R�����g�o��
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*       create alarm handler objects         */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* alarm handler control block for rom area */\n"
			"const T_KERNEL_ALMCB_ROM kernel_almcb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// �R���g���[���u���b�N(ROM��)�o��
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), (VP_INT)(%s), (FP)(%s)},\n",
				m_pParamPacks[i]->GetParam(CREALM_ALMATR),
				m_pParamPacks[i]->GetParam(CREALM_EXINF),
				m_pParamPacks[i]->GetParam(CREALM_ALMHDR));
		}
		fprintf(fp, "\t};\n");
	}

	// �R���g���[���u���b�N(RAM��)�o��
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* alarm handler control block for ram area */\n"
			"T_KERNEL_ALMCB_RAM kernel_almcb_ram[%d];\n",
			m_iObjs);
	}

	// �R���g���[���u���b�N�e�[�u���o��
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* alarm handler control block table */\n"
			"T_KERNEL_ALMCB_RAM *kernel_almcb_ram_tbl[%d] =\n"
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
				fprintf(fp, "\t\t&kernel_almcb_ram[%d],\n", j);
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
		"\n/* alarm handler control block count */\n"
		"const INT kernel_almcb_cnt = %d;\n",
		m_iMaxId);
}


// cfg�t�@�C���������������o��
void  CApiCreAlm::WriteCfgIni(FILE* fp)
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
		"\t/* initialize alarm handler control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_almcb_ram[i].almcb_rom = &kernel_almcb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfg�t�@�C���N���������o��
void  CApiCreAlm::WriteCfgStart(FILE* fp)
{
	// �I�u�W�F�N�g���݃`�F�b�N
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_alm();\t\t/* initialize alarm handler */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
