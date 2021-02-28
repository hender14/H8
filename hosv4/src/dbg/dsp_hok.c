/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �f�o�b�O�x��  �f�B�X�p�b�`�t�b�N                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "dsp_hok.h"


/* �f�B�X�p�b�`�t�b�N���� */
struct {
	T_DBG_DSPINF *inf;
	INT          mask;
	INT          infcnt;
	INT          read;
	INT          tail;
} _hosdbg_dsphok;


/* �t�b�N���������� */
void _hosdbg_ini_dsphok(
		T_DBG_DSPINF dspinf[],
		INT          infcnt)
{
	_hosdbg_dsphok.inf    = dspinf;
	_hosdbg_dsphok.mask   = 0;
	_hosdbg_dsphok.infcnt = infcnt;
}


/* �t�b�N�����J�n */
void _hosdbg_sta_dsphok(INT mask)
{
	INT i;

	mknl_loc_sys();

	for ( i = 0; i < _hosdbg_dsphok.infcnt; i++ )
	{
		_hosdbg_dsphok.inf[i].type = 0;
	}

	_hosdbg_dsphok.tail = 0;
	_hosdbg_dsphok.mask = mask;

	mknl_unl_sys();
}


/* �t�b�N������~ */
void _hosdbg_stp_dsphok(void)
{
	mknl_loc_sys();

	_hosdbg_dsphok.mask = 0;

	mknl_unl_sys();
}


/* �ǂݏo���J�n */
T_DBG_DSPINF *_hosdbg_red_fst(void)
{
	/* �ǂݏo���J�n�ʒu�ݒ� */
	_hosdbg_dsphok.read = _hosdbg_dsphok.tail;

	do
	{
		_hosdbg_dsphok.read++;
		if ( _hosdbg_dsphok.read >= _hosdbg_dsphok.infcnt )
		{
			_hosdbg_dsphok.read = 0;
		}
		
		/* ��Ȃ�I�� */
		if ( _hosdbg_dsphok.read == _hosdbg_dsphok.tail )
		{
			return NULL;
		}
	} while ( _hosdbg_dsphok.inf[_hosdbg_dsphok.read].type == 0 );
	
	return &_hosdbg_dsphok.inf[_hosdbg_dsphok.read];
}


/* ����ǂݏo�� */
T_DBG_DSPINF *_hosdbg_red_nxt(void)
{
	/* ���̈ʒu�Ɉړ� */
	_hosdbg_dsphok.read++;
	if ( _hosdbg_dsphok.read >= _hosdbg_dsphok.infcnt )
	{
		_hosdbg_dsphok.read = 0;
	}
		
	/* ��Ȃ�I�� */
	if ( _hosdbg_dsphok.read == _hosdbg_dsphok.tail )
	{
		return NULL;
	}
	
	return &_hosdbg_dsphok.inf[_hosdbg_dsphok.read];
}


/* �^�X�N�f�B�X�p�b�`�t�b�N */
void _hos_tsw_hok(void)
{
	T_KERNEL_TCB_RAM*  tcb_ram;
	T_DBG_DSPINF *inf;

	/* �L���t���O�`�F�b�N */
	if ( !(_hosdbg_dsphok.mask & _HOS_HOKMSK_TSW) )
	{
		return;
	}

	tcb_ram = kernel_get_run_tsk();

	/* ���擾 */
	inf = &_hosdbg_dsphok.inf[_hosdbg_dsphok.tail];
	inf->time = _hosdbg_get_tim();
	inf->type = _HOS_DSPTYPE_TSKSWC;
	if ( tcb_ram != NULL )
	{
		inf->id = kernel_get_tid(tcb_ram);
	}
	else
	{
		inf->id = 0;
	}
	
	/* ���O�o�b�t�@�X�V */
	if ( _hosdbg_dsphok.tail + 1 < _hosdbg_dsphok.infcnt )
	{
		_hosdbg_dsphok.tail++;
	}
	else
	{
		_hosdbg_dsphok.tail = 0;
	}
}


/* ���荞�݊J�n �t�b�N */
void _hos_intsta_hok(INTNO intno)
{
}


/* ���荞�ݏI�� �t�b�N */
void _hos_intext_hok(INTNO intno)
{
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
