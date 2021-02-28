// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    �p�����[�^�[�i�[�N���X                                                  
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <string.h>
#include "parpack.h"


// �R���X�g���N�^
CParamPack::CParamPack()
{
	int i;

	for ( i = 0; i < PARAMPACK_MAX; i++ )
	{
		m_pszParam[i] = NULL;
	}
}


// �f�X�g���N�^
CParamPack::~CParamPack()
{
	int i;

	for ( i = 0; i < PARAMPACK_MAX; i++ )
	{
		delete[] m_pszParam[i];
	}
}


// �p�����[�^�[�ݒ�
void CParamPack::SetParam(int iIndex, const char *pszParam)
{
	if ( iIndex < 0 || iIndex >= PARAMPACK_MAX )
	{
		return;
	}

	delete[] m_pszParam[iIndex];

	m_pszParam[iIndex] = new char[strlen(pszParam) + 1];
	strcpy(m_pszParam[iIndex], pszParam);
}


// �p�����[�^�[�擾
const char* CParamPack::GetParam(int iIndex)
{
	if ( iIndex < 0 || iIndex >= PARAMPACK_MAX )
	{
		return NULL;
	}

	return m_pszParam[iIndex];
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
