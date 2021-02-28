// ---------------------------------------------------------------------------
//  HOS V4 �R���t�B�M�����[�^�[ Ver 1.00                                      
//    �f�[�^�ǂݍ��݃N���X                                                    
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------



#ifndef __HOSV4CFG_Read_h__
#define __HOSV4CFG_Read_h__


#define READ_MAX_PATH		1024	// �ő�p�X��
#define READ_MAX_STATE		4096	// �P�X�e�[�g�̍ő啶����


// �f�[�^�ǂݍ��݃N���X
class CRead
{
public:
	CRead(FILE *fp, const char *name);			// �R���X�g���N�^
	~CRead();						// �f�X�g���N�^

	int ReadState(char *szState);	// �P�X�e�[�g�ǂݍ���
	int GetPhysicalLineNum(void)	// ���ۂɓǂݍ��ݒ��̃t�@�C���̍s�ԍ��擾
	{ return m_iPhysicalLineNum; }
	int GetLogicalLineNum(void)	// cpp��ʂ��O�̃t�@�C���̍s�ԍ��擾
	{ return m_iLogicalLineNum; }
	const char *GetLogicalInputFile(void)
	{ return m_szLogicalInputFile; }

protected:
       int SkipPreProcessorLine(char* szText, int iCount);     // �v���v���Z�b�T���C���̃X�L�b�v
	int ReadString(int cDelimiter, char* szText, int& iCount);	// ������ǂݍ���

	FILE *m_fpRead;					// �ǂݍ��ݗp�t�@�C���|�C���^
	int  m_iPhysicalLineNum;			// ���ۂɓǂݍ��ݒ��̃t�@�C���̍s�ԍ�
	int  m_iLogicalLineNum;				// cpp��ʂ��O�̃t�@�C���̍s�ԍ�
	bool m_blLineTop;				// �s�̐擪
	char m_szLogicalInputFile[READ_MAX_PATH];	// cpp��ʂ��O�̃t�@�C����
};


#endif	// __HOSV4CFG_Read_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
