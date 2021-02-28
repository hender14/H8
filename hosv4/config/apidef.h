// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    API��`�N���X                                                           
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiDef_h__
#define __HOSV4CFG_ApiDef_h__


#include "parpack.h"


#define API_MAX_OBJS		1024		// �ő�I�u�W�F�N�g��
#define API_MAX_PARAM		4096		// �ő�p�����[�^������


// API��`�N���X
class CApiDef
{
public:
	CApiDef();				// �R���X�g���N�^
	virtual ~CApiDef();		// �f�X�g���N�^

	virtual int   AnalyzeApi(const char* pszApiName, const char* pszParams) = 0;	// API�̉��
	virtual int   AutoId(void);							// ����ID�ԍ����蓖��
	virtual void  WriteId(FILE* fp);					// ID ��`�t�@�C�������o��
	virtual void  WriteCfgDef(FILE* fp);				// cfg�t�@�C����`�������o��
	virtual void  WriteCfgIni(FILE* fp);				// cfg�t�@�C���������������o��
	virtual void  WriteCfgStart(FILE* fp);				// cfg�t�@�C���N���������o��

protected:
	virtual int   AddParams(const char* pszParams);		// �p�����[�^�[�ǉ�

	CParamPack* m_pParamPacks[API_MAX_OBJS];	// �p�����[�^�[���X�g
	int         m_iId[API_MAX_OBJS];			// ID�ԍ����X�g
	int         m_iObjs;		// �I�u�W�F�N�g��
	int         m_iResObj;		// �\��I�u�W�F�N�g��
	int         m_iMaxId;		// �ő� ID �ԍ�
	int         m_iParams;						// �p�����[�^�[��
	int         m_iParamSyntax[PARAMPACK_MAX];	// �p�����[�^�[�\��
};


#endif	// __HOSV4CFG_ApiDef_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
