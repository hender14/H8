// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[
//    API��`�N���X
//
//                                    Copyright (C) 1998-2003 by Project HOS
//                                    http://sourceforge.jp/projects/hos/
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include "defercd.h"
#include "apidef.h"
#include "analyze.h"



// �R���X�g���N�^
CApiDef::CApiDef()
{
	int i;

	m_iMaxId = 0;
	m_iObjs  = 0;
	m_iResObj = 0;
	for ( i = 0; i < API_MAX_OBJS; i++ )
	{
		m_pParamPacks[i] = NULL;
		m_iId[i]         = 0;
	}
}


// �f�X�g���N�^
CApiDef::~CApiDef()
{
	int i;

	for ( i = 0; i < API_MAX_OBJS; i++ )
	{
		delete m_pParamPacks[i];
	}
}


// �p�����[�^�[�ǉ��i���蔲���j
int CApiDef::AddParams(const char* pszParams)
{
	char szParamBlock[API_MAX_PARAM];
	char szParam[API_MAX_PARAM];
	int  iErr;
	int  iIndex = 0;
	int  i, j;

	// �p�����[�^�i�[�p�I�u�W�F�N�g����
	m_pParamPacks[m_iObjs] = new CParamPack();

	for ( i = 0; i < m_iParams; i++ )
	{
		if ( m_iParamSyntax[i] == 0 )
		{
			// �P�ƃp�����[�^�[�؂�o��
			iErr = CAnalyze::GetParameter(szParam, pszParams);
			if ( iErr != CFG_ERR_OK )
			{
				break;
			}

			// �p�����[�^�[�ǉ�
			CAnalyze::SpaceCut(szParam);
			m_pParamPacks[m_iObjs]->SetParam(iIndex++, szParam);
		}
		else
		{
			// �󔒓ǂݔ�΂�
			while ( *pszParams == ' ' )
			{
				pszParams++;
			}

			// �u���b�N�J�n�`�F�b�N
			if ( *pszParams++ != '{' )
			{
				iErr = CFG_ERR_SYNTAX;
				break;
			}
			
			// �u���b�N�؂�o��
			iErr = CAnalyze::SearchChar(szParamBlock, pszParams, '}');
			if ( iErr != CFG_ERR_OK )
			{
				break;
			}

			// �u���b�N���ǂݏo��
			const char* pszParamBlock = szParamBlock;
			for ( j = 0; j < m_iParamSyntax[i] + 1; j++ )
			{
				// �P�ƃp�����[�^�[�؂�o��
				iErr = CAnalyze::GetParameter(szParam, pszParamBlock);
				if ( iErr != CFG_ERR_OK )
				{
					break;
				}

				// �p�����[�^�[�ǉ�
				CAnalyze::SpaceCut(szParam);
				if ( szParam[0] == '\0')
				{
					break;
				}
				m_pParamPacks[m_iObjs]->SetParam(iIndex++, szParam);
			}
			if ( iErr != CFG_ERR_OK )
			{
				iErr = CFG_ERR_SYNTAX;
				break;
			}
			if ( j != m_iParamSyntax[i] )
			{
				iErr = CFG_ERR_PARAM;
				break;
			}
		}
	}

	if ( iErr == CFG_ERR_OK )
	{
		m_iObjs++;
	}

	return iErr;
}


// ����ID�ԍ����蓖��
int CApiDef::AutoId(void)
{
	bool blUsedId[255];
	int iId;
	int i;

	// �ϐ�������
	for ( i = 0; i < 255; i++ )
	{
		blUsedId[i] = false;
	}

	// �Œ�l�w���ID���T�[�`
	for ( i = 0; i < m_iObjs; i++ )
	{
		iId = atoi(m_pParamPacks[i]->GetParam(0));
		if ( iId > 0 )
		{
			if ( m_iId[i] != 0 )
			{
				return CFG_ERR_ID_CONFLICT;		// ID�Փ�
			}
			m_iId[i] = iId;
			blUsedId[iId - 1] = true;
			if ( iId > m_iMaxId )
			{
				m_iMaxId = iId;
			}
		}
	}

	// ID ��������
	iId = 1;
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( m_iId[i] == 0 )
		{
			// �g�p�ς�ID�̃X�L�b�v
			while ( blUsedId[iId - 1] )
			{
				iId++;
			}
			m_iId[i] = iId++;
		}
	}
	iId--;

	if ( iId > m_iMaxId )
	{
		m_iMaxId = iId;
	}

	// �ő�ID�ԍ���\��I�u�W�F�N�g��������
	if ( m_iMaxId < m_iObjs + m_iResObj )
	{
		m_iMaxId = m_iObjs + m_iResObj;
	}

	return 0;
}


// ID ��`�t�@�C�������o��
void CApiDef::WriteId(FILE* fpId)
{
}


// cfg�t�@�C����`�������o��
void CApiDef::WriteCfgDef(FILE* fpCfg)
{
}

// cfg�t�@�C���������������o��
void CApiDef::WriteCfgIni(FILE* fpCfg)
{
}

// cfg�t�@�C���N���������o��
void CApiDef::WriteCfgStart(FILE* fpCfg)
{
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS
// ---------------------------------------------------------------------------
