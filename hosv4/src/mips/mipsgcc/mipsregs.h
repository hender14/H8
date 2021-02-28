/*******************************************************************************
 *
 *  MIPS�v���Z�b�T���W�X�^��`
 *
 *                                  Copyright (C) 1998-2002 by Project HOS
 *                                  http://sourceforge.jp/projects/hos/
 *******************************************************************************/

/**
 *  CPU�R�A�̂̃��W�X�^�ԍ���`
 */
#define zero    $00
#define at      $01
#define v0      $02
#define v1      $03
#define a0      $04
#define a1      $05
#define a2      $06
#define a3      $07

#define t0      $08
#define t1      $09
#define t2      $10
#define t3      $11
#define t4      $12
#define t5      $13
#define t6      $14
#define t7      $15

#define s0      $16
#define s1      $17
#define s2      $18
#define s3      $19
#define s4      $20
#define s5      $21
#define s6      $22
#define s7      $23

#define t8      $24
#define t9      $25
#define k0      $26
#define k1      $27
#define gp      $28
#define sp      $29
#define fp      $30
#define ra      $31

/**
 *  �R�v���Z�b�T0�̃��W�X�^�ԍ���`
 */
#define CP0_INDEX       $0
#define CP0_RANDOM      $1
#define CP0_ENTRYLO0    $2
#define CP0_ENTRYLO1    $3
#define CP0_CONF        $3
#define CP0_CONTEXT     $4
#define CP0_PAGEMASK    $5
#define CP0_WIRED       $6
#define CP0_INFO        $7
#define CP0_BADVADDR    $8
#define CP0_COUNT       $9
#define CP0_ENTRYHI     $10
#define CP0_COMPARE     $11
#define CP0_STATUS      $12
#define CP0_CAUSE       $13
#define CP0_EPC         $14
#define CP0_PRID        $15
#define CP0_CONFIG      $16
#define CP0_LLADDR      $17
#define CP0_WATCHLO     $18
#define CP0_WATCHHI     $19
#define CP0_XCONTEXT    $20
#define CP0_FRAMEMASK   $21
#define CP0_DIAGNOSTIC  $22
#define CP0_DEBUG       $23
#define CP0_DEPC        $24
#define CP0_PERFORMANCE $25
#define CP0_ECC         $26
#define CP0_CACHEERR    $27
#define CP0_TAGLO       $28
#define CP0_TAGHI       $29
#define CP0_ERROREPC    $30
#define CP0_DESAVE      $31
