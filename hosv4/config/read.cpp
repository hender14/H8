// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    �f�[�^�ǂݍ��݃N���X                                                    
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "defercd.h"
#include "read.h"


// �R���X�g���N�^
CRead::CRead(FILE *fp, const char *name)
{
	m_fpRead    = fp;
	m_iPhysicalLineNum = m_iLogicalLineNum = 1;
	m_blLineTop = true;
	strncpy(m_szLogicalInputFile, name, READ_MAX_PATH - 1);
	m_szLogicalInputFile[READ_MAX_PATH - 1] = '\0';
}


// �f�X�g���N�^
CRead::~CRead()
{
}


// �P�X�e�[�g�ǂݍ���
int CRead::ReadState(char *szState)
{
	bool blEsc   = false;
	bool blSpace = true;	// true �Ŏn�߂Đ擪�̋󔒂�ǂݔ�΂�
	int  iCount = 0;
	int  iErr;
	int  c;

	for ( ; ; )
	{
		// �P�����ǂݍ���
		if ( (c = fgetc(m_fpRead)) == EOF )
		{
			if ( blEsc || iCount != 0 )
			{
				iErr = CFG_ERR_EOF;	// �\������EOF
			}
			else
			{
				iErr = CFG_ERR_COMPLETE;	// ����
			}
			break;
		}

		// �T�C�Y�`�F�b�N
		if ( iCount >= READ_MAX_STATE - 1 )
		{
			iErr = CFG_ERR_STATE_LEN;
			break;
		}

		// �s���� # �Ȃ�X�L�b�v
		if ( m_blLineTop && c == '#' )
		{
                       iErr = SkipPreProcessorLine(szState, iCount);
			if ( iErr != CFG_ERR_OK )
			{
				break;
			}
			continue;
		}

		// ���s�����̏���
		if ( c == '\n' )
		{
			m_iPhysicalLineNum++;
			m_iLogicalLineNum++;
			m_blLineTop = true;
		}
		else
		{
			m_blLineTop = false;
		}

		// �󔒕����̃X�L�b�v
		if ( isspace(c) || c == '\n' )
		{
			if ( !blSpace )
			{
				szState[iCount++] = ' ';
				blSpace = true;
			}
			continue;
		}
		blSpace = false;

		// ������̏���
		if ( c == '\"' || c == '\'' )
		{
			szState[iCount++] = c;
			iErr = ReadString(c, szState, iCount);
			if ( iErr != CFG_ERR_OK )
			{
				break;
			}
			continue;
		}

		// �X�e�[�g���������Ȃ�
		if ( c == ';' )
		{
			iErr = CFG_ERR_OK;
			break;
		}

		// �����̓ǂݍ���
		szState[iCount++] = c;
	}

	// �����̋󔒕����폜
	if ( iCount > 0 && szState[iCount - 1] == ' ' )
	{
		iCount--;
	}

	szState[iCount] = '\0';

	return iErr;
}


// �v���v���Z�b�T���C���̃X�L�b�v
int CRead::SkipPreProcessorLine(char* szText, int iCountOrg)
{
	int  c;
	int iCount = iCountOrg;
	long tmpLineNum;
	char *p1, *p2;

	for ( ; ; )
	{
		// �P�����ǂݍ���
		if ( (c = fgetc(m_fpRead)) == EOF )
		{
			return CFG_ERR_OK;
		}

		// �T�C�Y�`�F�b�N
		if ( iCount >= READ_MAX_STATE - 1 )
		{
			return CFG_ERR_STATE_LEN;
		}

		// �s���̃`�F�b�N
		if ( c == '\n' )
		{
			m_iPhysicalLineNum++;
			m_iLogicalLineNum++;

			szText[iCount] = '\0';

			// #line 123 "filename"
			// # 123 "filename"
			// �̌`���̂ǂ���ł��󂯕t����
			if (strncmp(&szText[iCountOrg], "line", 4) == 0)
				iCountOrg += 4;

			// #line123
			// #12
			// �Ȃǂ�r��
			if (!isspace(szText[iCountOrg]))
				return CFG_ERR_OK;

			// �s�ԍ��ǂݍ���
			tmpLineNum = strtol(&szText[iCountOrg], &p1, 10);
			if (p1 == &szText[iCountOrg])
				return CFG_ERR_OK;

			// # 123a
			// �ȂǍs�ԍ��̌��ɗ]���Ȃ��̂����Ă���ꍇ��r��
			if (!isspace(*p1) && *p1 != '\0')
				return CFG_ERR_OK;

			// �ǂݍ��񂾍s�ԍ��𔽉f
			m_iLogicalLineNum = tmpLineNum;

			// �t�@�C������T��
			while (isspace(*p1))
				p1++;
			if (*p1 != '\"')
				return CFG_ERR_OK;
			p1++;
			p2 = strchr(p1, '\"');
			if (p2 == NULL)
				return CFG_ERR_OK;
			*p2 = '\0';

			// �t�@�C�����𔽉f
			strncpy(m_szLogicalInputFile, p1, READ_MAX_PATH - 1);
			m_szLogicalInputFile[READ_MAX_PATH - 1] = '\0';

			return CFG_ERR_OK;
		}

		// �����̓ǂݍ���
		szText[iCount++] = c;
	}
}


// ������ǂݍ���
int CRead::ReadString(int cDelimiter, char* szText, int& iCount)
{
	bool blEsc  = false;
	int c;

	for ( ; ; )
	{
		// �P�����ǂݍ���
		if ( (c = fgetc(m_fpRead)) == EOF )
		{
			return CFG_ERR_EOF;	// �\������EOF
		}

		// �T�C�Y�`�F�b�N
		if ( iCount >= READ_MAX_STATE - 1 )
		{
			return CFG_ERR_STATE_LEN;
		}

		// ���s�`�F�b�N
		if ( c == '\n' )
		{
			return CFG_ERR_CR;		// �s���ȉ��s
		}

		// �����̐ݒ�
		szText[iCount++] = c;

		// \ �̎��͖������ɃX�L�b�v
		if ( blEsc )
		{
			blEsc  = false;
			continue;
		}

		// \ �̃`�F�b�N
		if ( c == '\\' )
		{
			blEsc  = true;
			continue;
		}

		blEsc  = false;

		// �f���~�^�����Ȃ犮��
		if ( c == cDelimiter )
		{
			return CFG_ERR_OK;
		}
	}
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
