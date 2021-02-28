// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    �p�����[�^�[�i�[�N���X                                                  
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG__ParamPack_h__
#define __HOSV4CFG__ParamPack_h__


#define PARAMPACK_MAX	16


// �p�����[�^�[�i�[�N���X
class CParamPack
{
public:
	CParamPack();		// �R���X�g���N�^
	~CParamPack();		// �f�X�g���N�^

	void        SetParam(int iIndex, const char *pszParam);	// �p�����[�^�[�ݒ�
	const char* GetParam(int iIndex);						// �p�����[�^�[�擾

protected:
	char *m_pszParam[PARAMPACK_MAX];
};


#endif	// __HOSV4CFG__ParamPack_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
