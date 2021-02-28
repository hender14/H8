// ---------------------------------------------------------------------------
//  Hyper Operating System V4  �R���t�B�M�����[�^�[                           
//    ���C�����[�`��                                                          
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "read.h"
#include "analyze.h"
#include "apiinc.h"
#include "idlstk.h"
#include "intstk.h"
#include "knlheap.h"
#include "timtic.h"
#include "maxtpri.h"
#include "cretsk.h"
#include "deftex.h"
#include "cresem.h"
#include "creflg.h"
#include "credtq.h"
#include "crembx.h"
#include "crembf.h"
#include "crempf.h"
#include "crempl.h"
#include "crecyc.h"
#include "crealm.h"
#include "attisr.h"
#include "attini.h"
#include "defexc.h"


#define DEFAULT_INPUTFILE		"system.i"
#define DEFAULT_IDFILE			"kernel_id.h"
#define DEFAULT_CFGFILE			"kernel_cfg.c"


int  ReadConfigFile(FILE* fpConfig);	// �R���t�B�M�����[�V�����t�@�C���ǂݍ���
void WriteIdFile(FILE* fp);				// ID ��`�w�b�_�t�@�C���o��
void WriteCfgFile(FILE* fp);			// C ����\�[�X�o��
void PrintUsage(void);


CApiInclude    g_ApiInclude;
CApiIdleStack  g_ApiIdleStack;
CApiMaxTpri    g_ApiMaxTpri;
CApiIntStack   g_IntStack;
CApiKernelHeap g_ApiKernelHeap;
CApiTimTic     g_ApiTimTic;
CApiCreTsk     g_ApiCreTsk;
CApiDefTex     g_ApiDefTex;
CApiCreSem     g_ApiCreSem;
CApiCreFlg     g_ApiCreFlg;
CApiCreDtq     g_ApiCreDtq;
CApiCreMbx     g_ApiCreMbx;
CApiCreMbf     g_ApiCreMbf;
CApiCreMpf     g_ApiCreMpf;
CApiCreMpl     g_ApiCreMpl;
CApiCreCyc     g_ApiCreCyc;
CApiCreAlm     g_ApiCreAlm;
CApiAttIsr     g_ApiAttIsr;
CApiAttIni     g_ApiAttIni;
CApiDefExc     g_ApiDefExc;

static const char *s_szPhysicalInputFile  = NULL;
static const char *s_szIdFile             = DEFAULT_IDFILE;
static const char *s_szCfgFile            = DEFAULT_CFGFILE;

// API��`���X�g
static CApiDef* g_ApiList[] =
	{
		&g_ApiInclude,
		&g_ApiIdleStack,
		&g_ApiMaxTpri,
		&g_IntStack,
		&g_ApiKernelHeap,
		&g_ApiTimTic,
		&g_ApiCreTsk,
		&g_ApiDefTex,
		&g_ApiCreSem,
		&g_ApiCreFlg,
		&g_ApiCreDtq,
		&g_ApiCreMbx,
		&g_ApiCreMbf,
		&g_ApiCreMpf,
		&g_ApiCreMpl,
		&g_ApiCreCyc,
		&g_ApiCreAlm,
		&g_ApiAttIsr,
		&g_ApiAttIni,
		&g_ApiDefExc,
	};

#define API_COUNT	(sizeof(g_ApiList) / sizeof(CApiDef*))		// API��




// ���C���֐�
int main(int argc, char *argv[])
{
	FILE* fpInput;
	FILE* fpCfg;
	FILE* fpId;
	int  iErr;
	int  i;

	// �R�}���h���C�����
	for ( i = 1; i < argc; i++ )
	{
		if ( strcmp(argv[i], "-c") == 0 )
		{
			i++;
			if ( i >= argc )
			{
				fprintf(stderr, "option error \"-c\"\n");
                               PrintUsage();
				return 1;
			}
			s_szCfgFile = argv[i];
		}
		else if ( strcmp(argv[i], "-i") == 0 )
		{
			i++;
			if ( i >= argc )
			{
				fprintf(stderr, "option error \"-i\"\n");
                               PrintUsage();
				return 1;
			}
			s_szIdFile = argv[i];
		}
               else if ( strcmp(argv[i], "-help") == 0 )
               {
                       PrintUsage();
                       return 0;
               }
               else if ( argv[i][0] == '-' && argv[i][1] != '\0' )
               {
                       fprintf(stderr, "unknown option \"%s\"\n", argv[i]);
                       PrintUsage();
                       return 1;
               }
		else
		{
			if ( s_szPhysicalInputFile != NULL )
			{
				fprintf(stderr, "too many input files\n");
				PrintUsage();
				return 1;
			}
			s_szPhysicalInputFile = argv[i];
		}
	}

	// ���̓t�@�C���ȗ����̃f�t�H���g�ݒ�
	if ( s_szPhysicalInputFile == NULL )
	{
		s_szPhysicalInputFile = DEFAULT_INPUTFILE;
	}

	// ���̓t�@�C���I�[�v��
	if ( strcmp(s_szPhysicalInputFile, "-") == 0) {
		s_szPhysicalInputFile = "stdin";
		fpInput = stdin;
	}
	else if ( (fpInput = fopen(s_szPhysicalInputFile, "r")) == NULL )
	{
               fprintf(stderr, "could not open file \"%s\"\n", s_szPhysicalInputFile);
		return 1;
	}
	
	// �R���t�B�M�����[�V�����t�@�C���ǂݍ���
	iErr = ReadConfigFile(fpInput) != 0;
	fclose(fpInput);
	if ( iErr != 0 )
	{
		return 1;
	}

	// ����ID�ԍ����蓖��
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->AutoId();
	}

	// ID ��`�t�@�C���I�[�v��
	if ( (fpId = fopen(s_szIdFile, "w")) == NULL )
	{
               fprintf(stderr, "could not open file \"%s\"\n", s_szIdFile);
		return 1;
	}

	WriteIdFile(fpId);

	fclose(fpId);


	// Cfg�t�@�C���I�[�v��
	if ( (fpCfg = fopen(s_szCfgFile, "w")) == NULL )
	{
               fprintf(stderr, "could not open file \"%s\"\n", s_szCfgFile);
		return 1;
	}

	WriteCfgFile(fpCfg);

	fclose(fpCfg);

	return 0;
}


// �R���t�B�M�����[�V�����t�@�C���ǂݍ���
int ReadConfigFile(FILE* fpConfig)
{
	char szState[READ_MAX_STATE];
	char szApiName[READ_MAX_STATE];
	char szParams[READ_MAX_STATE];
	int  iErr;
	int  i;

	CRead read(fpConfig, s_szPhysicalInputFile);	// �ǂݏo���I�u�W�F�N�g����

	// �ǂݍ���
	while (	(iErr = read.ReadState(szState)) != CFG_ERR_COMPLETE )
	{
		// �ǂݍ��݃G���[�`�F�b�N
		if ( iErr != CFG_ERR_OK )
		{
                       fprintf(stderr, "%s line(%d) : %s\n",
					read.GetLogicalInputFile(),
					read.GetLogicalLineNum(), GetErrMessage(iErr));
			return 1;
		}

		// �\�����
		iErr = CAnalyze::SplitState(szApiName, szParams, szState);
		if ( iErr != CFG_ERR_OK )
		{
                       fprintf(stderr, "%s line(%d) : %s\n",
					read.GetLogicalInputFile(),
					read.GetLogicalLineNum(), GetErrMessage(iErr));
			return 1;
		}
		CAnalyze::SpaceCut(szApiName);
		CAnalyze::SpaceCut(szParams);

		// API����
		iErr = CFG_ERR_SYNTAX;
		for ( i = 0; i < API_COUNT; i++ )
		{
			iErr = g_ApiList[i]->AnalyzeApi(szApiName, szParams);
			if ( iErr != CFG_ERR_NOPROC )
			{
				break;
			}
		}
		if ( iErr != CFG_ERR_OK )
		{
                       fprintf(stderr, "%s line(%d) : %s\n",
					read.GetLogicalInputFile(),
					read.GetLogicalLineNum(), GetErrMessage(iErr));
			return 1;
		}
	}

	return 0;
}


// ID��`�w�b�_�t�@�C���o��
void WriteIdFile(FILE* fp)
{
	int i;

	/* �w�b�_�o�� */
	fputs(
		"/* ------------------------------------------------------------------------ */\n"
		"/*  HOS-V4  kernel configuration                                            */\n"
		"/*    kernel object ID definition                                           */\n"
		"/*                                                                          */\n"
		"/* ------------------------------------------------------------------------ */\n"
		"\n\n"
		"#ifndef __HOS_V4__kernel_cfg_h__\n"
		"#define __HOS_V4__kernel_cfg_h__\n"
		"\n"
		, fp);

	// ID ��`�t�@�C���o��
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteId(fp);
	}

	// �t�b�^�o��
	fputs(
		"\n\n\n"
		"#endif\t/* __HOS_V4__kernel_cfg_h__ */\n"
		"\n\n"
		"/* ------------------------------------------------------------------------ */\n"
		"/*  End of file                                                             */\n"
		"/* ------------------------------------------------------------------------ */\n"
		, fp);
}


// C ����\�[�X�o��
void WriteCfgFile(FILE* fp)
{
	int i;

	/* �w�b�_�o�� */
	fprintf(
		fp,
		"/* ------------------------------------------------------------------------ */\n"
		"/*  HOS-V4  kernel configuration                                            */\n"
		"/*    kernel object create and initialize                                   */\n"
		"/*                                                                          */\n"
		"/* ------------------------------------------------------------------------ */\n"
		"\n\n"
		"#include \"kernel.h\"\n"
		"#include \"%s\"\n"
		, s_szIdFile);

	// ID ��`�t�@�C���o��
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteCfgDef(fp);
	}

	// �������֐��R�����g�o��
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*          initialize functions              */\n"
		"/* ------------------------------------------ */\n",
		fp);

	// �������֐��o��
	fputs(
		"\n/* object initialize */\n"
		"void kernel_cfg_init(void)\n"
		"{\n"
		"\tint i;\n",
		fp);
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteCfgIni(fp);
	}
	fputs("}\n", fp);

	// �������֐��o��
	fputs(
		"\n/* start up */\n"
		"void kernel_cfg_start(void)\n"
		"{\n",
		fp);
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteCfgStart(fp);
	}
	fputs("}\n", fp);

	// �t�b�^�o��
	fputs(
		"\n\n"
		"/* ------------------------------------------------------------------------ */\n"
		"/*  End of file                                                             */\n"
		"/* ------------------------------------------------------------------------ */\n"
		, fp);
}

// �g�����\��
void PrintUsage(void)
{
       fprintf(stderr,
               "usage: hos4cfg [options] [input-file]\n"
               "options are:\n"
               "   -i FILE    specify auto-assginment headerfile (default: " DEFAULT_IDFILE ")\n"
               "   -c FILE    specify kernel configuration file  (default: " DEFAULT_CFGFILE ")\n"
               "   -help      show this help\n"
               "\n"
               "input-file (default: " DEFAULT_INPUTFILE ")\n");
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
