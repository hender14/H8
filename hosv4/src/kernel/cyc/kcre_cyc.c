/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �����n���h��                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"
#include "knl_mem.h"



/* �����n���h���̐���(�J�[�l������) */
ER kernel_cre_cyc(
		ID           cycid,		/* �����Ώۂ̎����n���h��ID�ԍ� */
		const T_CCYC *pk_ccyc)	/* �����n���h������������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	T_KERNEL_CYCCB_ROM *cyccb_rom;
	SIZE memsize;
	UB   *memptr;
	
	/* �K�v�ȃ������T�C�Y���v�Z */
	memsize = sizeof(T_KERNEL_CYCCB_RAM) + sizeof(T_KERNEL_CYCCB_ROM);
	
	/* �������m�� */
	memptr = (UB *)kernel_alc_mem(memsize);
#ifdef HOS_ERCHK_E_NOMEM
	if ( memptr == NULL )
	{
		return E_NOMEM;		/* �������s�� */
	}
#endif

	/* �|�C���^�ݒ� */	
	cyccb_ram  = (T_KERNEL_CYCCB_RAM *)memptr;
	memptr  += sizeof(T_KERNEL_CYCCB_RAM);
	cyccb_rom  = (T_KERNEL_CYCCB_ROM *)memptr;

	/* �l�ݒ� */
	cyccb_ram->timobj.timhdr = kernel_cyc_hdr; /* �����n���h���o�^ */
	cyccb_ram->timobj.next   = NULL;            /* �^�C�}���X�g���ڑ� */
	cyccb_ram->cyccb_rom     = cyccb_rom;	/* �����n���h���R���g���[���u���b�NROM���ւ̃|�C���^ */
	cyccb_rom->cycatr  = pk_ccyc->cycatr;	/* �����n���h������ */
	cyccb_rom->exinf   = pk_ccyc->exinf;	/* �����n���h���̊g����� */
	cyccb_rom->cychdr  = pk_ccyc->cychdr;	/* �����n���h���̋N���Ԓn */
	cyccb_rom->cyctim  = pk_ccyc->cyctim;	/* �����n���h���̋N������ */
/*	cyccb_rom->cycphs  = pk_ccyc->cycphs;*/	/* �����n���h���̋N���ʑ� */

	/* �����n���h���R���g���[���u���b�N�e�[�u���ɓo�^ */
	KERNEL_CYCID_TO_CYCCB_RAM(cycid) = cyccb_ram;

	/* ���s�����Ȃ�ΊJ�n */
	if ( pk_ccyc->cycatr & TA_STA )
	{
		/* �^�C�}���X�g�ɒǉ� */
		cyccb_ram->lefttim = pk_ccyc->cyctim;
		kernel_add_tml((T_KERNEL_TIM *)cyccb_ram);
	}

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
