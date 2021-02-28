// ---------------------------------------------------------------------------
//  HOS V4 �R���t�B�M�����[�^�[                                               
//    �\����̓N���X                                                          
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG__Analyze_h__
#define __HOSV4CFG__Analyze_h__



// �\����̓N���X
class CAnalyze
{
public:
	static int  SplitState(char* pszApiName, char* pszParams, const char *pszState);	// �X�e�[�g�����g��API���ƃp�����[�^�[�ɕ���
	static int  SearchChar(char* pszBuf, const char* &pszText, char c);		// ���蕶���̂܂ł̐؂�o��
	static int  GetParameter(char* pszBuf, const char* &pszText);			// �p�����[�^�[�̐؂�o��
	static int  DecodeText(char *pszBuf, const char* pszText);				// ������萔��W�J����
	static void SpaceCut(char* pszText);			// �O��̋󔒂��폜����
};


#endif	// __HOSV4CFG__Analyze_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
