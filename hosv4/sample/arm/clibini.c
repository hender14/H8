/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �T���v���v���O����                                                     */
/*   ARM�p C���C�u�����p�֐�                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <stdio.h>
#include <rt_misc.h>


/* �Z�~�z�X�e�B���O�pSWI�ԍ���` */
#define SemiSWI		0x123456


/* �P�����o�́i�Z�~�z�X�e�B���O�j */
__swi(SemiSWI) void _WriteC(unsigned op, char *c);
#define WriteC(c) _WriteC (0x3,c)

/* exit�i�Z�~�z�X�e�B���O�j */
__swi(SemiSWI) void _Exit(unsigned op, unsigned except);
#define Exit() _Exit (0x18,0x20026)



/* �P�����o�� */
int fputc(int ch, FILE *f)
{
    char tmp = ch;

    WriteC(&tmp);

    return ch;
}


/* �t�@�C���G���[�擾 */
int ferror(FILE *f)
{
    return EOF;
}


/* �v���Z�X�I�� */
void _sys_exit(int return_code)
{
    Exit();
}


/* �^�[�~�i���o�� */
void _ttywrch(int ch)
{
}



static unsigned int heap_area[4096];	/* malloc �p�q�[�v�G���A */

/* �q�[�v�Ǘ��p�A�h���X�ݒ� */
__value_in_regs struct __initial_stackheap __user_initial_stackheap(
        unsigned R0, unsigned SP, unsigned R2, unsigned SL)
{
    struct __initial_stackheap config;
    
    config.heap_base  = (unsigned long)heap_area;
    config.heap_limit = (unsigned long)&heap_area[4096];
    config.stack_base = SP;

    return config;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
