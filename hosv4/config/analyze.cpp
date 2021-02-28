// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    �\����̓N���X                                                          
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defercd.h"
#include "analyze.h"



// �X�e�[�g�����g��API���ƃp�����[�^�[�ɕ���
int CAnalyze::SplitState(char* pszApiName, char* pszParams, const char *pszState)
{
	int iErr;

	// �R�}���h���̐؂�o��
	while ( *pszState != '(' )
	{
		if ( *pszState == '\0' )
		{
			return CFG_ERR_SYNTAX;
		}
		*pszApiName++ = *pszState++;
	}
	*pszApiName = '\0';
	pszState++;

	// �p�����[�^�[���̐؂�o��
	iErr = SearchChar(pszParams, pszState, ')');
	if ( iErr != CFG_ERR_OK )
	{
		return iErr;
	}

	// �㑱�`�F�b�N
	if ( *pszState != '\0' )
	{
		return CFG_ERR_SEMICOLON;
	}

	return CFG_ERR_OK;
}


// ���蕶���̂܂ł̐؂�o��
int CAnalyze::SearchChar(char* pszBuf, const char* &pszText, char c)
{
	char cDelimiter;
	bool blText = false;
	bool blEsc  = false;
	int  iErr;

	for ( ; ; )
	{
		// �I�[�`�F�b�N
		if ( *pszText == '\0' )
		{
			iErr = CFG_ERR_SYNTAX;
			break;
		}

		// �����`�F�b�N
		if ( *pszText == c )
		{
			pszText++;
			iErr = CFG_ERR_OK;
			break;
		}

		// '\' �̎��̕����͖������ɃG�X�P�[�v
		if ( blEsc )
		{
			*pszBuf++ = *pszText++;
			blEsc = false;
			continue;
		}
		blEsc = false;

		// '\' �`�F�b�N
		if ( *pszBuf == '\\' )
		{
			*pszBuf++ = *pszText++;
			blEsc = true;
			continue;
		}

		// ������J�n�`�F�b�N
		if ( !blText && *pszText == '\"' || *pszText == '\'' )
		{
			cDelimiter = *pszText;
			*pszBuf++ = *pszText++;
			blText = true;
			continue;
		}

		// ���������
		if ( blText )
		{
			if ( *pszText == cDelimiter )
			{
				*pszBuf++ = *pszText++;
				blText = false;
			}
			else
			{
				*pszBuf++ = *pszText++;
			}
			continue;
		}

		// '{' �`�F�b�N
		if ( *pszText == '{' )
		{
			*pszBuf++ = *pszText++;
			iErr = SearchChar(pszBuf, pszText, '}');
			if ( iErr != CFG_ERR_OK )
			{
				iErr = CFG_ERR_BRACE;
			}
			pszBuf  += strlen(pszBuf);
			*pszBuf++ = '}';
			continue;
		}

		// '(' �`�F�b�N
		if ( *pszText == '(' )
		{
			*pszBuf++ = *pszText++;
			iErr = SearchChar(pszBuf, pszText, ')');
			if ( iErr != CFG_ERR_OK )
			{
				iErr = CFG_ERR_PAREN;
			}
			pszBuf  += strlen(pszBuf);
			*pszBuf++ = ')';
			continue;
		}

		*pszBuf++ = *pszText++;
	}

	*pszBuf = '\0';

	return iErr;
}


// �p�����[�^�[�̐؂�o��
int CAnalyze::GetParameter(char* pszBuf, const char* &pszText)
{
	int iErr;

	// �R���}�܂Ő؂�o��
	iErr = SearchChar(pszBuf, pszText, ',');
	if ( iErr == CFG_ERR_SYNTAX )
	{
		// ���ʑΉ�OK�ŏI�[�Ȃ�R���}��������Ȃ��Ă���
		iErr = CFG_ERR_OK;
	}

	return iErr;
}


// ������萔��W�J����
int CAnalyze::DecodeText(char *pszBuf, const char* pszText)
{
	bool blEsc = false;

	if ( *pszText++ != '\"') 
	{
		return CFG_ERR_TEXT;
	}

	for ( ; ; )
	{
		if ( *pszText == '\0' )
		{
			return CFG_ERR_TEXT;
		}

		// �O�̕����� '\' �Ȃ�ǂݔ�΂�
		if ( blEsc )
		{
			*pszBuf++ = *pszText++;
			blEsc = false;
			continue;
		}

		// �G�X�P�[�v�����`�F�b�N
		if ( *pszText == '\\' )
		{
			pszText++;
			blEsc = true;
			continue;
		}

		// �I�[�`�F�b�N
		if ( *pszText == '\"' )
		{
			pszText++;
			break;
		}

		*pszBuf++ = *pszText++;
	}

	// �������Ă��Ȃ���΃G���[
	if ( *pszText != '\0' )
	{
			return CFG_ERR_TEXT;
	}

	*pszBuf = '\0';

	return CFG_ERR_OK;
}


// �O��̋󔒂��폜����
void CAnalyze::SpaceCut(char* pszText)
{
	char *pszTmp;
	int  i = 0;

	pszTmp = pszText;

	// �擪�̋󔒂�ǂݔ�΂�
	while ( *pszTmp == ' ' )
	{
		pszTmp++;
	}

	// �R�s�[
	while ( *pszTmp != '\0' )
	{
		pszText[i++] = *pszTmp++;
	}

	// �����̋󔒂��폜
	while ( i > 0 && pszText[i - 1] == ' ' )
	{
		i--;
	}

	pszText[i] = '\0';
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
