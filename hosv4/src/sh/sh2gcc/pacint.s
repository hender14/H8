/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (���� SH2�p)                           */
/*    ���荞�݃n���h��                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



				.global	_hos_vecter004
				.global	_hos_vecter005
				.global	_hos_vecter006
				.global	_hos_vecter007
				.global	_hos_vecter008
				.global	_hos_vecter009
				.global	_hos_vecter010
				.global	_hos_vecter011
				.global	_hos_vecter012
				.global	_hos_vecter013
				.global	_hos_vecter014
				.global	_hos_vecter015
				.global	_hos_vecter016
				.global	_hos_vecter017
				.global	_hos_vecter018
				.global	_hos_vecter019
				.global	_hos_vecter020
				.global	_hos_vecter021
				.global	_hos_vecter022
				.global	_hos_vecter023
				.global	_hos_vecter024
				.global	_hos_vecter025
				.global	_hos_vecter026
				.global	_hos_vecter027
				.global	_hos_vecter028
				.global	_hos_vecter029
				.global	_hos_vecter030
				.global	_hos_vecter031
				.global	_hos_vecter032
				.global	_hos_vecter033
				.global	_hos_vecter034
				.global	_hos_vecter035
				.global	_hos_vecter036
				.global	_hos_vecter037
				.global	_hos_vecter038
				.global	_hos_vecter039
				.global	_hos_vecter040
				.global	_hos_vecter041
				.global	_hos_vecter042
				.global	_hos_vecter043
				.global	_hos_vecter044
				.global	_hos_vecter045
				.global	_hos_vecter046
				.global	_hos_vecter047
				.global	_hos_vecter048
				.global	_hos_vecter049
				.global	_hos_vecter050
				.global	_hos_vecter051
				.global	_hos_vecter052
				.global	_hos_vecter053
				.global	_hos_vecter054
				.global	_hos_vecter055
				.global	_hos_vecter056
				.global	_hos_vecter057
				.global	_hos_vecter058
				.global	_hos_vecter059
				.global	_hos_vecter060
				.global	_hos_vecter061
				.global	_hos_vecter062
				.global	_hos_vecter063
				.global	_hos_vecter064
				.global	_hos_vecter065
				.global	_hos_vecter066
				.global	_hos_vecter067
				.global	_hos_vecter068
				.global	_hos_vecter069
				.global	_hos_vecter070
				.global	_hos_vecter071
				.global	_hos_vecter072
				.global	_hos_vecter073
				.global	_hos_vecter074
				.global	_hos_vecter075
				.global	_hos_vecter076
				.global	_hos_vecter077
				.global	_hos_vecter078
				.global	_hos_vecter079
				.global	_hos_vecter080
				.global	_hos_vecter081
				.global	_hos_vecter082
				.global	_hos_vecter083
				.global	_hos_vecter084
				.global	_hos_vecter085
				.global	_hos_vecter086
				.global	_hos_vecter087
				.global	_hos_vecter088
				.global	_hos_vecter089
				.global	_hos_vecter090
				.global	_hos_vecter091
				.global	_hos_vecter092
				.global	_hos_vecter093
				.global	_hos_vecter094
				.global	_hos_vecter095
				.global	_hos_vecter096
				.global	_hos_vecter097
				.global	_hos_vecter098
				.global	_hos_vecter099
				.global	_hos_vecter100
				.global	_hos_vecter101
				.global	_hos_vecter102
				.global	_hos_vecter103
				.global	_hos_vecter104
				.global	_hos_vecter105
				.global	_hos_vecter106
				.global	_hos_vecter107
				.global	_hos_vecter108
				.global	_hos_vecter109
				.global	_hos_vecter110
				.global	_hos_vecter111
				.global	_hos_vecter112
				.global	_hos_vecter113
				.global	_hos_vecter114
				.global	_hos_vecter115
				.global	_hos_vecter116
				.global	_hos_vecter117
				.global	_hos_vecter118
				.global	_hos_vecter119
				.global	_hos_vecter120
				.global	_hos_vecter121
				.global	_hos_vecter122
				.global	_hos_vecter123
				.global	_hos_vecter124
				.global	_hos_vecter125
				.global	_hos_vecter126
				.global	_hos_vecter127
				.global	_hos_vecter128
				.global	_hos_vecter129
				.global	_hos_vecter130
				.global	_hos_vecter131
				.global	_hos_vecter132
				.global	_hos_vecter133
				.global	_hos_vecter134
				.global	_hos_vecter135
				.global	_hos_vecter136
				.global	_hos_vecter137
				.global	_hos_vecter138
				.global	_hos_vecter139
				.global	_hos_vecter140
				.global	_hos_vecter141
				.global	_hos_vecter142
				.global	_hos_vecter143
				.global	_hos_vecter144
				.global	_hos_vecter145
				.global	_hos_vecter146
				.global	_hos_vecter147
				.global	_hos_vecter148
				.global	_hos_vecter149
				.global	_hos_vecter150
				.global	_hos_vecter151
				.global	_hos_vecter152
				.global	_hos_vecter153
				.global	_hos_vecter154
				.global	_hos_vecter155
				.global	_hos_vecter156


				.text


/************************************************
  ���荞�݃n���h��
************************************************/
_hos_vecter004:	mov.l	r4, @-r15
				bra		int_handler
				mov		#4, r4

_hos_vecter005:	mov.l	r4, @-r15
				bra		int_handler
				mov		#5, r4

_hos_vecter006:	mov.l	r4, @-r15
				bra		int_handler
				mov		#6, r4

_hos_vecter007:	mov.l	r4, @-r15
				bra		int_handler
				mov		#7, r4

_hos_vecter008:	mov.l	r4, @-r15
				bra		int_handler
				mov		#8, r4

_hos_vecter009:	mov.l	r4, @-r15
				bra		int_handler
				mov		#9, r4

_hos_vecter010:	mov.l	r4, @-r15
				bra		int_handler
				mov		#10, r4

_hos_vecter011:	mov.l	r4, @-r15
				bra		int_handler
				mov		#11, r4

_hos_vecter012:	mov.l	r4, @-r15
				bra		int_handler
				mov		#12, r4

_hos_vecter013:	mov.l	r4, @-r15
				bra		int_handler
				mov		#13, r4

_hos_vecter014:	mov.l	r4, @-r15
				bra		int_handler
				mov		#14, r4

_hos_vecter015:	mov.l	r4, @-r15
				bra		int_handler
				mov		#15, r4

_hos_vecter016:	mov.l	r4, @-r15
				bra		int_handler
				mov		#16, r4

_hos_vecter017:	mov.l	r4, @-r15
				bra		int_handler
				mov		#17, r4

_hos_vecter018:	mov.l	r4, @-r15
				bra		int_handler
				mov		#18, r4

_hos_vecter019:	mov.l	r4, @-r15
				bra		int_handler
				mov		#19, r4

_hos_vecter020:	mov.l	r4, @-r15
				bra		int_handler
				mov		#20, r4

_hos_vecter021:	mov.l	r4, @-r15
				bra		int_handler
				mov		#21, r4

_hos_vecter022:	mov.l	r4, @-r15
				bra		int_handler
				mov		#22, r4

_hos_vecter023:	mov.l	r4, @-r15
				bra		int_handler
				mov		#23, r4

_hos_vecter024:	mov.l	r4, @-r15
				bra		int_handler
				mov		#24, r4

_hos_vecter025:	mov.l	r4, @-r15
				bra		int_handler
				mov		#25, r4

_hos_vecter026:	mov.l	r4, @-r15
				bra		int_handler
				mov		#26, r4

_hos_vecter027:	mov.l	r4, @-r15
				bra		int_handler
				mov		#27, r4

_hos_vecter028:	mov.l	r4, @-r15
				bra		int_handler
				mov		#28, r4

_hos_vecter029:	mov.l	r4, @-r15
				bra		int_handler
				mov		#29, r4

_hos_vecter030:	mov.l	r4, @-r15
				bra		int_handler
				mov		#30, r4

_hos_vecter031:	mov.l	r4, @-r15
				bra		int_handler
				mov		#31, r4

_hos_vecter032:	mov.l	r4, @-r15
				bra		int_handler
				mov		#32, r4

_hos_vecter033:	mov.l	r4, @-r15
				bra		int_handler
				mov		#33, r4

_hos_vecter034:	mov.l	r4, @-r15
				bra		int_handler
				mov		#34, r4

_hos_vecter035:	mov.l	r4, @-r15
				bra		int_handler
				mov		#35, r4

_hos_vecter036:	mov.l	r4, @-r15
				bra		int_handler
				mov		#36, r4

_hos_vecter037:	mov.l	r4, @-r15
				bra		int_handler
				mov		#37, r4

_hos_vecter038:	mov.l	r4, @-r15
				bra		int_handler
				mov		#38, r4

_hos_vecter039:	mov.l	r4, @-r15
				bra		int_handler
				mov		#39, r4

_hos_vecter040:	mov.l	r4, @-r15
				bra		int_handler
				mov		#40, r4

_hos_vecter041:	mov.l	r4, @-r15
				bra		int_handler
				mov		#41, r4

_hos_vecter042:	mov.l	r4, @-r15
				bra		int_handler
				mov		#42, r4

_hos_vecter043:	mov.l	r4, @-r15
				bra		int_handler
				mov		#43, r4

_hos_vecter044:	mov.l	r4, @-r15
				bra		int_handler
				mov		#44, r4

_hos_vecter045:	mov.l	r4, @-r15
				bra		int_handler
				mov		#45, r4

_hos_vecter046:	mov.l	r4, @-r15
				bra		int_handler
				mov		#46, r4

_hos_vecter047:	mov.l	r4, @-r15
				bra		int_handler
				mov		#47, r4

_hos_vecter048:	mov.l	r4, @-r15
				bra		int_handler
				mov		#48, r4

_hos_vecter049:	mov.l	r4, @-r15
				bra		int_handler
				mov		#49, r4

_hos_vecter050:	mov.l	r4, @-r15
				bra		int_handler
				mov		#50, r4

_hos_vecter051:	mov.l	r4, @-r15
				bra		int_handler
				mov		#51, r4

_hos_vecter052:	mov.l	r4, @-r15
				bra		int_handler
				mov		#52, r4

_hos_vecter053:	mov.l	r4, @-r15
				bra		int_handler
				mov		#53, r4

_hos_vecter054:	mov.l	r4, @-r15
				bra		int_handler
				mov		#54, r4

_hos_vecter055:	mov.l	r4, @-r15
				bra		int_handler
				mov		#55, r4

_hos_vecter056:	mov.l	r4, @-r15
				bra		int_handler
				mov		#56, r4

_hos_vecter057:	mov.l	r4, @-r15
				bra		int_handler
				mov		#57, r4

_hos_vecter058:	mov.l	r4, @-r15
				bra		int_handler
				mov		#58, r4

_hos_vecter059:	mov.l	r4, @-r15
				bra		int_handler
				mov		#59, r4

_hos_vecter060:	mov.l	r4, @-r15
				bra		int_handler
				mov		#60, r4

_hos_vecter061:	mov.l	r4, @-r15
				bra		int_handler
				mov		#61, r4

_hos_vecter062:	mov.l	r4, @-r15
				bra		int_handler
				mov		#62, r4

_hos_vecter063:	mov.l	r4, @-r15
				bra		int_handler
				mov		#63, r4

_hos_vecter064:	mov.l	r4, @-r15
				bra		int_handler
				mov		#64, r4

_hos_vecter065:	mov.l	r4, @-r15
				bra		int_handler
				mov		#65, r4

_hos_vecter066:	mov.l	r4, @-r15
				bra		int_handler
				mov		#66, r4

_hos_vecter067:	mov.l	r4, @-r15
				bra		int_handler
				mov		#67, r4

_hos_vecter068:	mov.l	r4, @-r15
				bra		int_handler
				mov		#68, r4

_hos_vecter069:	mov.l	r4, @-r15
				bra		int_handler
				mov		#69, r4

_hos_vecter070:	mov.l	r4, @-r15
				bra		int_handler
				mov		#70, r4

_hos_vecter071:	mov.l	r4, @-r15
				bra		int_handler
				mov		#71, r4

_hos_vecter072:	mov.l	r4, @-r15
				bra		int_handler
				mov		#72, r4

_hos_vecter073:	mov.l	r4, @-r15
				bra		int_handler
				mov		#73, r4

_hos_vecter074:	mov.l	r4, @-r15
				bra		int_handler
				mov		#74, r4

_hos_vecter075:	mov.l	r4, @-r15
				bra		int_handler
				mov		#75, r4

_hos_vecter076:	mov.l	r4, @-r15
				bra		int_handler
				mov		#76, r4

_hos_vecter077:	mov.l	r4, @-r15
				bra		int_handler
				mov		#77, r4

_hos_vecter078:	mov.l	r4, @-r15
				bra		int_handler
				mov		#78, r4

_hos_vecter079:	mov.l	r4, @-r15
				bra		int_handler
				mov		#79, r4

_hos_vecter080:	mov.l	r4, @-r15
				bra		int_handler
				mov		#80, r4

_hos_vecter081:	mov.l	r4, @-r15
				bra		int_handler
				mov		#81, r4

_hos_vecter082:	mov.l	r4, @-r15
				bra		int_handler
				mov		#82, r4

_hos_vecter083:	mov.l	r4, @-r15
				bra		int_handler
				mov		#83, r4

_hos_vecter084:	mov.l	r4, @-r15
				bra		int_handler
				mov		#84, r4

_hos_vecter085:	mov.l	r4, @-r15
				bra		int_handler
				mov		#85, r4

_hos_vecter086:	mov.l	r4, @-r15
				bra		int_handler
				mov		#86, r4

_hos_vecter087:	mov.l	r4, @-r15
				bra		int_handler
				mov		#87, r4

_hos_vecter088:	mov.l	r4, @-r15
				bra		int_handler
				mov		#88, r4

_hos_vecter089:	mov.l	r4, @-r15
				bra		int_handler
				mov		#89, r4

_hos_vecter090:	mov.l	r4, @-r15
				bra		int_handler
				mov		#90, r4

_hos_vecter091:	mov.l	r4, @-r15
				bra		int_handler
				mov		#91, r4

_hos_vecter092:	mov.l	r4, @-r15
				bra		int_handler
				mov		#92, r4

_hos_vecter093:	mov.l	r4, @-r15
				bra		int_handler
				mov		#93, r4

_hos_vecter094:	mov.l	r4, @-r15
				bra		int_handler
				mov		#94, r4

_hos_vecter095:	mov.l	r4, @-r15
				bra		int_handler
				mov		#95, r4

_hos_vecter096:	mov.l	r4, @-r15
				bra		int_handler
				mov		#96, r4

_hos_vecter097:	mov.l	r4, @-r15
				bra		int_handler
				mov		#97, r4

_hos_vecter098:	mov.l	r4, @-r15
				bra		int_handler
				mov		#98, r4

_hos_vecter099:	mov.l	r4, @-r15
				bra		int_handler
				mov		#99, r4

_hos_vecter100:	mov.l	r4, @-r15
				bra		int_handler
				mov		#100, r4

_hos_vecter101:	mov.l	r4, @-r15
				bra		int_handler
				mov		#101, r4

_hos_vecter102:	mov.l	r4, @-r15
				bra		int_handler
				mov		#102, r4

_hos_vecter103:	mov.l	r4, @-r15
				bra		int_handler
				mov		#103, r4

_hos_vecter104:	mov.l	r4, @-r15
				bra		int_handler
				mov		#104, r4

_hos_vecter105:	mov.l	r4, @-r15
				bra		int_handler
				mov		#105, r4

_hos_vecter106:	mov.l	r4, @-r15
				bra		int_handler
				mov		#106, r4

_hos_vecter107:	mov.l	r4, @-r15
				bra		int_handler
				mov		#107, r4

_hos_vecter108:	mov.l	r4, @-r15
				bra		int_handler
				mov		#108, r4

_hos_vecter109:	mov.l	r4, @-r15
				bra		int_handler
				mov		#109, r4

_hos_vecter110:	mov.l	r4, @-r15
				bra		int_handler
				mov		#110, r4

_hos_vecter111:	mov.l	r4, @-r15
				bra		int_handler
				mov		#111, r4

_hos_vecter112:	mov.l	r4, @-r15
				bra		int_handler
				mov		#112, r4

_hos_vecter113:	mov.l	r4, @-r15
				bra		int_handler
				mov		#113, r4

_hos_vecter114:	mov.l	r4, @-r15
				bra		int_handler
				mov		#114, r4

_hos_vecter115:	mov.l	r4, @-r15
				bra		int_handler
				mov		#115, r4

_hos_vecter116:	mov.l	r4, @-r15
				bra		int_handler
				mov		#116, r4

_hos_vecter117:	mov.l	r4, @-r15
				bra		int_handler
				mov		#117, r4

_hos_vecter118:	mov.l	r4, @-r15
				bra		int_handler
				mov		#118, r4

_hos_vecter119:	mov.l	r4, @-r15
				bra		int_handler
				mov		#119, r4

_hos_vecter120:	mov.l	r4, @-r15
				bra		int_handler
				mov		#120, r4

_hos_vecter121:	mov.l	r4, @-r15
				bra		int_handler
				mov		#121, r4

_hos_vecter122:	mov.l	r4, @-r15
				bra		int_handler
				mov		#122, r4

_hos_vecter123:	mov.l	r4, @-r15
				bra		int_handler
				mov		#123, r4

_hos_vecter124:	mov.l	r4, @-r15
				bra		int_handler
				mov		#124, r4

_hos_vecter125:	mov.l	r4, @-r15
				bra		int_handler
				mov		#125, r4

_hos_vecter126:	mov.l	r4, @-r15
				bra		int_handler
				mov		#126, r4

_hos_vecter127:	mov.l	r4, @-r15
				bra		int_handler
				mov		#127, r4

_hos_vecter128:	mov.l	r4, @-r15
				bra		int_handler
				mov		#128, r4

_hos_vecter129:	mov.l	r4, @-r15
				bra		int_handler
				mov		#129, r4

_hos_vecter130:	mov.l	r4, @-r15
				bra		int_handler
				mov		#130, r4

_hos_vecter131:	mov.l	r4, @-r15
				bra		int_handler
				mov		#131, r4

_hos_vecter132:	mov.l	r4, @-r15
				bra		int_handler
				mov		#132, r4

_hos_vecter133:	mov.l	r4, @-r15
				bra		int_handler
				mov		#133, r4

_hos_vecter134:	mov.l	r4, @-r15
				bra		int_handler
				mov		#134, r4

_hos_vecter135:	mov.l	r4, @-r15
				bra		int_handler
				mov		#135, r4

_hos_vecter136:	mov.l	r4, @-r15
				bra		int_handler
				mov		#136, r4

_hos_vecter137:	mov.l	r4, @-r15
				bra		int_handler
				mov		#137, r4

_hos_vecter138:	mov.l	r4, @-r15
				bra		int_handler
				mov		#138, r4

_hos_vecter139:	mov.l	r4, @-r15
				bra		int_handler
				mov		#139, r4

_hos_vecter140:	mov.l	r4, @-r15
				bra		int_handler
				mov		#140, r4

_hos_vecter141:	mov.l	r4, @-r15
				bra		int_handler
				mov		#141, r4

_hos_vecter142:	mov.l	r4, @-r15
				bra		int_handler
				mov		#142, r4

_hos_vecter143:	mov.l	r4, @-r15
				bra		int_handler
				mov		#143, r4

_hos_vecter144:	mov.l	r4, @-r15
				bra		int_handler
				mov		#144, r4

_hos_vecter145:	mov.l	r4, @-r15
				bra		int_handler
				mov		#145, r4

_hos_vecter146:	mov.l	r4, @-r15
				bra		int_handler
				mov		#146, r4

_hos_vecter147:	mov.l	r4, @-r15
				bra		int_handler
				mov		#147, r4

_hos_vecter148:	mov.l	r4, @-r15
				bra		int_handler
				mov		#148, r4

_hos_vecter149:	mov.l	r4, @-r15
				bra		int_handler
				mov		#149, r4

_hos_vecter150:	mov.l	r4, @-r15
				bra		int_handler
				mov		#150, r4

_hos_vecter151:	mov.l	r4, @-r15
				bra		int_handler
				mov		#151, r4

_hos_vecter152:	mov.l	r4, @-r15
				bra		int_handler
				mov		#152, r4

_hos_vecter153:	mov.l	r4, @-r15
				bra		int_handler
				mov		#153, r4

_hos_vecter154:	mov.l	r4, @-r15
				bra		int_handler
				mov		#154, r4

_hos_vecter155:	mov.l	r4, @-r15
				bra		int_handler
				mov		#155, r4

_hos_vecter156:	mov.l	r4, @-r15
				bra		int_handler
				mov		#156, r4



/************************************************
  ���荞�݃n���h��

  r4���X�^�b�N�ɐς񂾌�Ar4�Ɋ��荞�ݔԍ���
  �i�[���Ă����ɕ��򂷂���̂Ƃ���
************************************************/
				.align	2
int_handler:	
				/* ���W�X�^�ޔ�(r0-r1) */
				mov.l	r0, @-r15
				mov.l	r1, @-r15
				
				/* ���荞�݃}�X�N�ݒ� */
				stc		sr, r0
				mov		r0, r1
				or		#0xf0, r0	/* ���荞�ݑS�}�X�N�ݒ� */
				ldc		r0, sr
				
				/* ���荞�݃}�X�N�̕ۑ� */
				mov		r1, r0
				and		#0xf0, r0
				mov.l	imsk_addr, r1
				mov.l	r0, @r1
				
				/* ���荞�ݔԍ��̕����g�����N���A */
				extu.b	r4, r4
				
				/* ���W�X�^�ۑ�(r2-r7,mach,macl,pr) */
				mov.l	r2, @-r15
				mov.l	r3, @-r15
				mov.l	r5, @-r15
				mov.l	r6, @-r15
				mov.l	r7, @-r15
				sts.l	mach, @-r15
				sts.l	macl, @-r15
				sts.l	pr, @-r15
				
				/* ���d���荞�ݔ��� */
				mov.l	int_cnt_addr, r1
				mov.l	@r1, r0
				cmp/eq	#0, r0
				bf/s	int_multi
				add		#1, r0
				
				/* �P�Ɗ��荞�ݎ� */
				mov.l	r0, @r1				/* ���荞�݃l�X�g�l��ݒ� */
				
				/* �X�^�b�N����ւ� */
				mov.l	save_sp_addr, r0
				mov.l	r15, @r0			/* ���݂̃X�^�b�N��ޔ� */
				mov.l	int_sp_addr, r0
				mov.l	@r0, r15			/* ���荞�ݗp�X�^�b�N��ݒ� */
				
				mov.l	r4, @-r15			/* ���荞�ݔԍ���ޔ� */
				
				/* ���荞�݊J�n�����Ăяo�� */
				mov.l	sta_int_addr, r1
				jsr		@r1
				nop
				
				/* ���荞�ݎ��s�����Ăяo�� */
				mov.l	exe_int_addr, r1
				jsr		@r1
				mov.l	@r15+, r4			/* ���荞�ݔԍ��������Ƃ��� */
				
				/* �X�^�b�N�̕��A */
				mov.l	save_sp_addr, r0
				mov.l	@r0, r15
				
				/* ���荞�݃J�E���^�̃N���A */
				mov.l	int_cnt_addr, r1
				xor		r0, r0
				mov.l	r0, @r1
				
				/* �x�[�X�}�X�N�l�ɖ߂� */
				mov.l	imsk_base_addr, r0
				mov.l	@r0, r1
				mov.l	imsk_addr, r0
				mov.l	r1, @r0
				
				/* ���荞�ݏI�������Ăяo�� */
				mov.l	end_int_addr, r1
				jsr		@r1
				nop
				
				/* ���W�X�^���A */
				lds.l	@r15+, pr
				lds.l	@r15+, macl
				lds.l	@r15+, mach
				mov.l	@r15+, r7
				mov.l	@r15+, r6
				mov.l	@r15+, r5
				mov.l	@r15+, r3
				mov.l	@r15+, r2
				mov.l	@r15+, r1
				
				/* ���A�����荞�݃}�X�N�̐ݒ� */
				mov.l	imsk_addr, r4
				mov.l	@r4, r4					/* �}�X�N�l�擾 */
				mov.l	@(8, r15), r0
				or		r4, r0
				mov.l	r0, @(8, r15)			/* ���A��SR�̃}�X�N�ݒ� */
				
				mov.l	@r15+, r0
				mov.l	@r15+, r4
				rte
				nop

				/* ���d���荞�ݏ��� */
int_multi:		
				mov.l	r0, @r1				/* ���荞�݃l�X�g�l��ݒ� */
				
				/* ���荞�ݎ��s�����Ăяo�� */
				mov.l	exe_int_addr, r1
				jsr		@r1			/* ���荞�ݔԍ��������Ƃ��� */
				nop
				
				/* ���荞�݃J�E���^�̌��Z */
				mov.l	int_cnt_addr, r1
				mov.l	@r1, r0
				add		#-1, r0
				mov.l	r0, @r1
				
				/* ���W�X�^���A */
				lds.l	@r15+, pr
				lds.l	@r15+, macl
				lds.l	@r15+, mach
				mov.l	@r15+, r7
				mov.l	@r15+, r6
				mov.l	@r15+, r5
				mov.l	@r15+, r3
				mov.l	@r15+, r2
				mov.l	@r15+, r1
				mov.l	@r15+, r0
				mov.l	@r15+, r4
				rte
				nop


				.align	2
imsk_addr:
				.long	_hospac_sh_imsk			/* ���荞�݃}�X�N */
imsk_base_addr:
				.long	_hospac_sh_imsk_base	/* ���荞�݃}�X�N�x�[�X�l */
int_cnt_addr:
				.long	_kernel_int_cnt			/* ���荞�݃l�X�g�� */
save_sp_addr:
				.long	_kernel_int_ssp			/* ���荞�ݗp�X�^�b�N�|�C���^�ޔ� */
int_sp_addr:
				.long	_kernel_int_sp			/* ���荞�ݗp�X�^�b�N�|�C���^ */
sta_int_addr:
				.long	_kernel_sta_int			/* ���荞�݊J�n���� */
end_int_addr:
				.long	_kernel_end_int			/* ���荞�ݏI������ */
exe_int_addr:
				.long	_kernel_exe_int			/* ���荞�ݎ��s���� */



				.end


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
