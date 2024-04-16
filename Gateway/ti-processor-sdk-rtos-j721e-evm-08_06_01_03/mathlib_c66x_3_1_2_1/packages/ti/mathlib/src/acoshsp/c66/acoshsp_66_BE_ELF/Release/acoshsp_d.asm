;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Tue May 17 02:32:31 2016                                *
;******************************************************************************
	.compiler_opts --abi=eabi --c64p_l1d_workaround=off --endian=big --hll_source=on --long_precision_bits=32 --mem_model:code=near --mem_model:const=data --mem_model:data=far --object_format=elf --silicon_version=6600 --symdebug:none 

;******************************************************************************
;* GLOBAL FILE PARAMETERS                                                     *
;*                                                                            *
;*   Architecture      : TMS320C66xx                                          *
;*   Optimization      : Enabled at level 3                                   *
;*   Optimizing for    : Speed                                                *
;*                       Based on options: -o3, no -ms                        *
;*   Endian            : Big                                                  *
;*   Interrupt Thrshld : Disabled                                             *
;*   Data Access Model : Far                                                  *
;*   Pipelining        : Enabled                                              *
;*   Speculate Loads   : Enabled with threshold = 0                           *
;*   Memory Aliases    : Presume are aliases (pessimistic)                    *
;*   Debug Info        : No Debug Info                                        *
;*                                                                            *
;******************************************************************************

	.asg	A15, FP
	.asg	B14, DP
	.asg	B15, SP
	.global	$bss

	.global	a
	.sect	".fardata:a", RW
	.clink
	.align	8
	.elfsym	a,SYM_SIZE(804)
a:
	.word	04957871bh		; a[0] @ 0
	.word	04908cbd1h		; a[1] @ 32
	.word	047eecb43h		; a[2] @ 64
	.word	048ee9b46h		; a[3] @ 96
	.word	04769c16dh		; a[4] @ 128
	.word	0490eab2dh		; a[5] @ 160
	.word	048b6ed1ah		; a[6] @ 192
	.word	0495ea9a7h		; a[7] @ 224
	.word	0494dc1fdh		; a[8] @ 256
	.word	04898b6a0h		; a[9] @ 288
	.word	04930b6dfh		; a[10] @ 320
	.word	04944ccfah		; a[11] @ 352
	.word	047f88b18h		; a[12] @ 384
	.word	04963d7dah		; a[13] @ 416
	.word	048b938b1h		; a[14] @ 448
	.word	048139381h		; a[15] @ 480
	.word	048cbaa02h		; a[16] @ 512
	.word	04849ed94h		; a[17] @ 544
	.word	048045b00h		; a[18] @ 576
	.word	048f63ebbh		; a[19] @ 608
	.word	04941aaadh		; a[20] @ 640
	.word	048f564dfh		; a[21] @ 672
	.word	048b757c2h		; a[22] @ 704
	.word	0473703c5h		; a[23] @ 736
	.word	0496a808ah		; a[24] @ 768
	.word	0493e1256h		; a[25] @ 800
	.word	047b88105h		; a[26] @ 832
	.word	048fc9eeeh		; a[27] @ 864
	.word	04834bea7h		; a[28] @ 896
	.word	04911c0d2h		; a[29] @ 928
	.word	049513659h		; a[30] @ 960
	.word	048860d4ah		; a[31] @ 992
	.word	048a89e0ah		; a[32] @ 1024
	.word	047be1956h		; a[33] @ 1056
	.word	0494deeddh		; a[34] @ 1088
	.word	0487faa44h		; a[35] @ 1120
	.word	0495cd230h		; a[36] @ 1152
	.word	046b547c8h		; a[37] @ 1184
	.word	049462ceeh		; a[38] @ 1216
	.word	046b4a24ah		; a[39] @ 1248
	.word	04963162fh		; a[40] @ 1280
	.word	0492bad91h		; a[41] @ 1312
	.word	047f16f7bh		; a[42] @ 1344
	.word	04925e39eh		; a[43] @ 1376
	.word	04792067ah		; a[44] @ 1408
	.word	047986297h		; a[45] @ 1440
	.word	049313b6ah		; a[46] @ 1472
	.word	0496a6642h		; a[47] @ 1504
	.word	049105773h		; a[48] @ 1536
	.word	04921834ah		; a[49] @ 1568
	.word	04825efa4h		; a[50] @ 1600
	.word	0483683e5h		; a[51] @ 1632
	.word	04898ffaah		; a[52] @ 1664
	.word	0490ab25ch		; a[53] @ 1696
	.word	049106a3ch		; a[54] @ 1728
	.word	048804359h		; a[55] @ 1760
	.word	04926cf68h		; a[56] @ 1792
	.word	048fa39aah		; a[57] @ 1824
	.word	049318d2bh		; a[58] @ 1856
	.word	0492d6a0bh		; a[59] @ 1888
	.word	04931b46ch		; a[60] @ 1920
	.word	04941e5f9h		; a[61] @ 1952
	.word	0495d3faeh		; a[62] @ 1984
	.word	04916d9e3h		; a[63] @ 2016
	.word	04791cabbh		; a[64] @ 2048
	.word	0489911deh		; a[65] @ 2080
	.word	047169421h		; a[66] @ 2112
	.word	049276bcdh		; a[67] @ 2144
	.word	049656cbdh		; a[68] @ 2176
	.word	04909736bh		; a[69] @ 2208
	.word	0491dd177h		; a[70] @ 2240
	.word	0484260c2h		; a[71] @ 2272
	.word	04800c84dh		; a[72] @ 2304
	.word	0491866b7h		; a[73] @ 2336
	.word	0494c5549h		; a[74] @ 2368
	.word	0470af778h		; a[75] @ 2400
	.word	0476bf3cch		; a[76] @ 2432
	.word	0482b19f3h		; a[77] @ 2464
	.word	0489935fah		; a[78] @ 2496
	.word	049256990h		; a[79] @ 2528
	.word	0492fa1f6h		; a[80] @ 2560
	.word	048ed9ea6h		; a[81] @ 2592
	.word	048b44df1h		; a[82] @ 2624
	.word	0483b6845h		; a[83] @ 2656
	.word	0492bbdfbh		; a[84] @ 2688
	.word	048d1ce69h		; a[85] @ 2720
	.word	04959df7fh		; a[86] @ 2752
	.word	04868ceedh		; a[87] @ 2784
	.word	0484319cah		; a[88] @ 2816
	.word	048e0c3c8h		; a[89] @ 2848
	.word	048b5ecb1h		; a[90] @ 2880
	.word	0479e3e23h		; a[91] @ 2912
	.word	049723aa5h		; a[92] @ 2944
	.word	0491a135ah		; a[93] @ 2976
	.word	04955eaf1h		; a[94] @ 3008
	.word	04908ebf4h		; a[95] @ 3040
	.word	048d97097h		; a[96] @ 3072
	.word	0491145cdh		; a[97] @ 3104
	.word	047a7b105h		; a[98] @ 3136
	.word	047f86b73h		; a[99] @ 3168
	.word	04901f0eah		; a[100] @ 3200
	.word	0490f1638h		; a[101] @ 3232
	.word	0487b1acdh		; a[102] @ 3264
	.word	04946cb74h		; a[103] @ 3296
	.word	04946e2f5h		; a[104] @ 3328
	.word	048d817e1h		; a[105] @ 3360
	.word	0487435e6h		; a[106] @ 3392
	.word	0487e8188h		; a[107] @ 3424
	.word	048da3d4eh		; a[108] @ 3456
	.word	049115d7eh		; a[109] @ 3488
	.word	048fc9925h		; a[110] @ 3520
	.word	04927689ah		; a[111] @ 3552
	.word	0482c0ac6h		; a[112] @ 3584
	.word	0476c3f9dh		; a[113] @ 3616
	.word	047d330b5h		; a[114] @ 3648
	.word	0495e0b86h		; a[115] @ 3680
	.word	048aad192h		; a[116] @ 3712
	.word	048df9681h		; a[117] @ 3744
	.word	049204a29h		; a[118] @ 3776
	.word	048a8415bh		; a[119] @ 3808
	.word	0495ad583h		; a[120] @ 3840
	.word	0497352c7h		; a[121] @ 3872
	.word	048c1e600h		; a[122] @ 3904
	.word	042c07aefh		; a[123] @ 3936
	.word	048aa2d46h		; a[124] @ 3968
	.word	048eb6cd4h		; a[125] @ 4000
	.word	048194c2fh		; a[126] @ 4032
	.word	048e76e3dh		; a[127] @ 4064
	.word	0494c096ah		; a[128] @ 4096
	.word	04894d14ah		; a[129] @ 4128
	.word	048afbbd2h		; a[130] @ 4160
	.word	0496b7cfeh		; a[131] @ 4192
	.word	047855ba7h		; a[132] @ 4224
	.word	048e403ffh		; a[133] @ 4256
	.word	04661ba32h		; a[134] @ 4288
	.word	048754124h		; a[135] @ 4320
	.word	048b02c69h		; a[136] @ 4352
	.word	04903f5d3h		; a[137] @ 4384
	.word	0493316fch		; a[138] @ 4416
	.word	04930195fh		; a[139] @ 4448
	.word	0491785d5h		; a[140] @ 4480
	.word	0492e1bb1h		; a[141] @ 4512
	.word	0492e9093h		; a[142] @ 4544
	.word	048ad76f3h		; a[143] @ 4576
	.word	048a4146ah		; a[144] @ 4608
	.word	04938f2c1h		; a[145] @ 4640
	.word	04939c9d5h		; a[146] @ 4672
	.word	0492d6871h		; a[147] @ 4704
	.word	049163462h		; a[148] @ 4736
	.word	046f3bdb2h		; a[149] @ 4768
	.word	0487895cbh		; a[150] @ 4800
	.word	0496956ech		; a[151] @ 4832
	.word	048048994h		; a[152] @ 4864
	.word	048f41007h		; a[153] @ 4896
	.word	04832e271h		; a[154] @ 4928
	.word	0494e8b25h		; a[155] @ 4960
	.word	0482f1064h		; a[156] @ 4992
	.word	0492f4a61h		; a[157] @ 5024
	.word	047e8aafah		; a[158] @ 5056
	.word	049339fd7h		; a[159] @ 5088
	.word	049158ec5h		; a[160] @ 5120
	.word	049496a4fh		; a[161] @ 5152
	.word	04865afa3h		; a[162] @ 5184
	.word	0490ac894h		; a[163] @ 5216
	.word	0495e5082h		; a[164] @ 5248
	.word	0490cb1fch		; a[165] @ 5280
	.word	04892d18dh		; a[166] @ 5312
	.word	04955f3fdh		; a[167] @ 5344
	.word	04805d05dh		; a[168] @ 5376
	.word	0488edb8ch		; a[169] @ 5408
	.word	049219af7h		; a[170] @ 5440
	.word	049434d13h		; a[171] @ 5472
	.word	0496688a9h		; a[172] @ 5504
	.word	0495d6498h		; a[173] @ 5536
	.word	0488962aeh		; a[174] @ 5568
	.word	0474e9466h		; a[175] @ 5600
	.word	0490dedffh		; a[176] @ 5632
	.word	049678fb4h		; a[177] @ 5664
	.word	0492c6e8bh		; a[178] @ 5696
	.word	0496b8d3dh		; a[179] @ 5728
	.word	049584b5ch		; a[180] @ 5760
	.word	048fdfb29h		; a[181] @ 5792
	.word	0477d5cfdh		; a[182] @ 5824
	.word	048d81506h		; a[183] @ 5856
	.word	04890af8dh		; a[184] @ 5888
	.word	048a64596h		; a[185] @ 5920
	.word	047c603f8h		; a[186] @ 5952
	.word	049727d74h		; a[187] @ 5984
	.word	0494ed6edh		; a[188] @ 6016
	.word	0492e1b84h		; a[189] @ 6048
	.word	048022fbdh		; a[190] @ 6080
	.word	04930e498h		; a[191] @ 6112
	.word	0481a83d0h		; a[192] @ 6144
	.word	04902690ah		; a[193] @ 6176
	.word	047a8837bh		; a[194] @ 6208
	.word	0489aed95h		; a[195] @ 6240
	.word	048d9850dh		; a[196] @ 6272
	.word	0488ec95ah		; a[197] @ 6304
	.word	048e9b849h		; a[198] @ 6336
	.word	0478d102dh		; a[199] @ 6368
	.word	04901495eh		; a[200] @ 6400

;	C:\MATHLIB_Tools\CCSV5_5_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\Users\\gtbldadm\\AppData\\Local\\Temp\\008484 C:\\Users\\gtbldadm\\AppData\\Local\\Temp\\008486 
;**	Parameter deleted: req_flags == 1;
;**	Parameter deleted: tol == 1e-06;
	.sect	".text"
	.clink

;******************************************************************************
;* FUNCTION NAME: allequal                                                    *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,B0,B1, *
;*                           B2,B3,B4,B5,B6,B7,B8,B9,SP,A16,A17,A18,A19,A20,  *
;*                           A21,A22,A23,A24,A25,A26,A27,A28,A29,A30,A31,B16, *
;*                           B17,B18,B19,B20,B21,B22,B23,B24,B25,B26,B27,B28, *
;*                           B29,B30,B31                                      *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,B0,B1, *
;*                           B2,B3,B4,B5,B6,B7,B8,B9,DP,SP,A16,A17,A18,A19,   *
;*                           A20,A21,A22,A23,A24,A25,A26,A27,A28,A29,A30,A31, *
;*                           B16,B17,B18,B19,B20,B21,B22,B23,B24,B25,B26,B27, *
;*                           B28,B29,B30,B31                                  *
;*   Local Frame Size  : 0 Args + 0 Auto + 24 Save = 24 byte                  *
;******************************************************************************
allequal:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STW     .D2T1   A11,*SP--(8)      ; |63| 
||         MVKL    .S2     0xa0b5ed8d,B6

           STDW    .D2T1   A13:A12,*SP--     ; |63| 
||         MVKL    .S1     output,A11
||         MVKL    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     output,A11
||         MVKH    .S2     0xa0b5ed8d,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 
||         MVKH    .S2     0x3eb0c6f7,B7
||         MVK     .S1     0x1,A8            ; |66| 

           MV      .L1X    B3,A13            ; |63| 
||         CALLP   .S2     isequal,B3
||         MV      .S1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 

$C$RL0:    ; CALL OCCURS {isequal} {0}       ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A12
||         MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A12
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL2:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6

           STW     .D1T1   A4,*+A12(12)      ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1     A11,A3            ; |66| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |69| 
||         MV      .L1     A10,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL3:    ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L2X    4,A12,B4
           LDW     .D2T1   *B4,A0            ; |72| 
           STW     .D1T1   A4,*+A12(16)      ; |69| 
           ADD     .L2X    8,A12,B4
           NOP             2

   [!A0]   BNOP    .S1     $C$L1,5           ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 
|| [ A0]   ADD     .L2     4,B4,B4

           ; BRANCHCC OCCURS {$C$L1}         ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVKL    .S1     all_pass,A3

   [ A0]   B       .S2     $C$L2             ; |72| 
||         MVKH    .S1     all_pass,A3
|| [ A0]   MV      .L2X    A13,B3            ; |74| 

   [ A0]   STW     .D1T1   A4,*A3            ; |72| 
   [ A0]   LDW     .D2T1   *++SP(8),A10      ; |74| 

   [ A0]   RET     .S2     B3                ; |74| 
|| [ A0]   LDDW    .D2T1   *++SP,A13:A12     ; |74| 

   [ A0]   LDW     .D2T1   *++SP(8),A11      ; |74| 
           NOP             1
           ; BRANCHCC OCCURS {$C$L2}         ; |72| 
;** --------------------------------------------------------------------------*
$C$L1:    
;          EXCLUSIVE CPU CYCLES: 7
           MVKL    .S1     all_pass,A3

           MVKH    .S1     all_pass,A3
||         ZERO    .L1     A4                ; |72| 

           STW     .D1T1   A4,*A3            ; |72| 

           LDW     .D2T1   *++SP(8),A10      ; |74| 
||         MV      .L2X    A13,B3            ; |74| 

           LDDW    .D2T1   *++SP,A13:A12     ; |74| 
||         RET     .S2     B3                ; |74| 

           LDW     .D2T1   *++SP(8),A11      ; |74| 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L2:    
;          EXCLUSIVE CPU CYCLES: 3
           NOP             3
           ; BRANCH OCCURS {B3}              ; |74| 
	.sect	".text"
	.clink
	.global	main

;******************************************************************************
;* FUNCTION NAME: main                                                        *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,   *
;*                           A15,B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,   *
;*                           B13,SP,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,  *
;*                           A26,A27,A28,A29,A30,A31,B16,B17,B18,B19,B20,B21, *
;*                           B22,B23,B24,B25,B26,B27,B28,B29,B30,B31          *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,   *
;*                           A15,B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,   *
;*                           B13,DP,SP,A16,A17,A18,A19,A20,A21,A22,A23,A24,   *
;*                           A25,A26,A27,A28,A29,A30,A31,B16,B17,B18,B19,B20, *
;*                           B21,B22,B23,B24,B25,B26,B27,B28,B29,B30,B31      *
;*   Local Frame Size  : 8 Args + 92 Auto + 56 Save = 156 byte                *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |143| 
           STW     .D2T1   A10,*SP--(8)      ; |143| 
           STDW    .D2T2   B13:B12,*SP--     ; |143| 
           STDW    .D2T2   B11:B10,*SP--     ; |143| 
           STDW    .D2T1   A15:A14,*SP--     ; |143| 

           STDW    .D2T1   A13:A12,*SP--     ; |143| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(112)     ; |143| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {driver_init} {0}   ; |151| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .S2     0xc9,B4
||         MVKL    .S1     a,A11

           MVKH    .S1     a,A11

           CALL    .S1     acoshf            ; |160| 
||         MV      .L1     A11,A12
||         MV      .D1X    B4,A10
||         ZERO    .L2     B10

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A12++,A4         ; |160| 
           ADDKPC  .S2     $C$RL5,B3,3       ; |160| 
$C$RL5:    ; CALL OCCURS {acoshf} {0}        ; |160| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9

           MVKL    .S2     output,B4
||         SUB     .L1     A10,1,A0          ; |159| 
||         SUB     .S1     A10,1,A10         ; |159| 

           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |160| 
   [ A0]   BNOP    .S1     $C$L3,3           ; |159| 

           ADD     .L2     B10,B4,B4         ; |160| 
||         ADD     .S2     4,B10,B10         ; |159| 

   [ A0]   CALL    .S1     acoshf            ; |160| 
||         STW     .D2T1   A4,*B4            ; |160| 
|| [!A0]   MVKL    .S2     output,B4

           ; BRANCHCC OCCURS {$C$L3}         ; |159| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

           ZERO    .L2     B10
||         MVKH    .S2     output,B4

           ADD     .L2     4,B4,B11
||         MVK     .S2     0xc9,B4

           MV      .L1     A11,A15

           MV      .L1X    B4,A10
||         CALL    .S1     acoshsp           ; |163| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |163| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |163| 
$C$RL6:    ; CALL OCCURS {acoshsp} {0}       ; |163| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |163| 
||         SUB     .L1     A10,1,A0          ; |162| 
||         SUB     .S1     A10,1,A10         ; |162| 

   [ A0]   BNOP    .S1     $C$L4,3           ; |162| 

           ADD     .L2     B10,B4,B4         ; |163| 
||         ADD     .S2     4,B10,B10         ; |162| 

   [ A0]   CALL    .S1     acoshsp           ; |163| 
||         STW     .D2T1   A4,*B4            ; |163| 
|| [!A0]   MVK     .S2     0xc9,B4

           ; BRANCHCC OCCURS {$C$L4}         ; |162| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2

           ZERO    .L2     B10
||         MV      .L1     A15,A11
||         ADD     .S2     4,B11,B11

           MV      .L1X    B4,A10
||         CALL    .S1     acoshsp_c         ; |166| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D1T1   *A11++,A4         ; |166| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |166| 
$C$RL7:    ; CALL OCCURS {acoshsp_c} {0}     ; |166| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |166| 
||         SUB     .L1     A10,1,A0          ; |165| 
||         SUB     .S1     A10,1,A10         ; |165| 

   [ A0]   BNOP    .S1     $C$L5,3           ; |165| 
|| [!A0]   ADD     .L2     4,B11,B6

           ADD     .L2     B10,B4,B4         ; |166| 
||         ADD     .S2     4,B10,B10         ; |165| 

   [ A0]   CALL    .S1     acoshsp_c         ; |166| 
||         STW     .D2T1   A4,*B4            ; |166| 

           ; BRANCHCC OCCURS {$C$L5}         ; |165| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 19

           STW     .D2T2   B6,*+SP(44)
||         MVKL    .S1     0x3f317218,A4
||         MVKL    .S2     ti_math_logtable,B16
||         ZERO    .L2     B30
||         ZERO    .L1     A18
||         ZERO    .D1     A3

           LDW     .D2T2   *B6,B20
||         ZERO    .L2     B6
||         MVKL    .S2     0xfefa39ec,B31
||         MVKL    .S1     0xbe804d66,A5
||         ZERO    .L1     A19               ; |95| 
||         MV      .D1     A15,A8

           SET     .S2     B6,0x0,0x1e,B17
||         MVKL    .S1     0xbe6bd0fc,A6
||         ZERO    .L2     B6
||         ZERO    .D2     B8                ; |95| 

           MVKL    .S2     0x3fe62e42,B7
||         MVKL    .S1     0x3eaaa872,A7
||         MV      .L2     B17,B21

           MVKL    .S2     0x3e436581,B5
||         MVKH    .S1     0x3f317218,A4

           MVKL    .S2     0x7f7fffff,B11
||         MVKH    .S1     0xbe804d66,A5
||         STW     .D2T1   A4,*+SP(12)

           SET     .S2     B6,0x17,0x1d,B18
||         MVKH    .S1     0xbe6bd0fc,A6
||         STW     .D2T1   A5,*+SP(20)
||         MV      .L2X    A4,B26

           MVKH    .S2     ti_math_logtable,B16
||         MVKH    .S1     0x3eaaa872,A7
||         STW     .D2T1   A6,*+SP(16)

           MVKH    .S2     0xfefa39ec,B31
||         SET     .S1     A18,0x18,0x1d,A5
||         MV      .L1     A5,A18
||         STW     .D2T1   A7,*+SP(28)
||         MV      .D1X    B18,A22
||         MV      .L2X    A6,B25

           MVKH    .S2     0x3fe62e42,B7
||         STW     .D2T2   B31,*+SP(52)      ; |95| 
||         MVK     .S1     0xfffffc01,A16
||         MV      .L1X    B16,A9
||         MV      .D1     A5,A21
||         MV      .L2X    A7,B24

           MVKH    .S2     0x3e436581,B5
||         STW     .D2T2   B7,*+SP(56)       ; |95| 
||         SET     .S1     A3,0x16,0x1d,A20
||         ZERO    .L1     A3                ; |95| 

           MVKH    .S2     0x7f7fffff,B11
||         LDW     .D2T2   *+SP(52),B6

           MVKL    .S2     0x42b17218,B4
||         LDW     .D2T2   *+SP(56),B7
||         MV      .L1X    B5,A17

           MVKL    .S2     0xbf000003,B12
||         MV      .L1X    B11,A26
||         STW     .D2T2   B5,*+SP(24)

           MVKH    .S2     0x42b17218,B4
||         STW     .D2T1   A16,*+SP(32)

           MVKH    .S2     0xbf000003,B12
||         STW     .D2T2   B4,*+SP(36)
||         MV      .L2     B4,B22

           SET     .S2     B30,0x14,0x1d,B9
||         MV      .L2     B12,B23

           MVK     .S2     0xc9,B19
||         STW     .D2T2   B9,*+SP(48)       ; |95| 

           SUB     .L2     B19,1,B0
||         DINT                              ; interrupts off

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop found in file               : C:/nightlybuilds/mathlib/ti/mathlib/src/acoshsp/acoshsp_d.c
;*      Loop source line                 : 168
;*      Loop opening brace source line   : 168
;*      Loop closing brace source line   : 170
;*      Known Minimum Trip Count         : 201                    
;*      Known Maximum Trip Count         : 201                    
;*      Known Max Trip Count Factor      : 201
;*      Loop Carried Dependency Bound(^) : 109
;*      Unpartitioned Resource Bound     : 12
;*      Partitioned Resource Bound(*)    : 12
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     3        1     
;*      .S units                     5        8     
;*      .D units                     2        1     
;*      .M units                    12*      10     
;*      .X cross paths              10       12*    
;*      .T address paths             2        1     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           9        5     (.L or .S unit)
;*      Addition ops (.LSD)          6        6     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             9        7     
;*      Bound(.L .S .D .LS .LSD)     9        7     
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 109 Schedule found with 1 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |   *    **      *******   *     |*     ****          *******     |
;*       1: |   *    **      *******   *     |*     ****          *******     |
;*       2: |   *    **      *******   *     |*     ****          *******     |
;*       3: |   *    **      *******   *     |*     ****          *******     |
;*       4: |   *    **      *******   *     |*     ****          *******     |
;*       5: |   *  * **      *******   *     |*     ****          *******     |
;*       6: |   *  * **      *******   *     |*     ****          *******     |
;*       7: |   *  * **      *******   *     |*     ****          *******     |
;*       8: |   *  * **      *******   *     |*     ****          *******     |
;*       9: |   *  * **      ********  *     |*     ****          *******     |
;*      10: |   *  * **      ******** **     |*     ****          *******     |
;*      11: |   *  * **      ******** **     |*     ****          *******     |
;*      12: |   ** * **      ******** **     |*     ****          *******     |
;*      13: |   ** * **      ******** **     |*     ****          *******     |
;*      14: |   ** * **      ******** **     |*     ****          *******     |
;*      15: |   ** * **      ******** **     |*     ****          *******     |
;*      16: |   ** ****      ***********     |*     ****          *******     |
;*      17: |   ** ****      ***********     |*     ****          *******     |
;*      18: |   ** ****      ***********     |*     ****          *******     |
;*      19: |   ** ****      ***********     |*     ****          *******     |
;*      20: |   *******      ***********     |*     ****          *******     |
;*      21: |   ** ****      ***********     |*     ****          *******     |
;*      22: |   ** ****      ***********     |*     ****          *******     |
;*      23: |   ** ****      ***********     |*     ****          *******     |
;*      24: |   *******      ***********     |*     ****          *******     |
;*      25: |   ** ****      ***********     |*     ****          *******     |
;*      26: |   ** ****      ***********     |*     ****          *******     |
;*      27: |   *******      ***********     |*     ****          *******     |
;*      28: |   ** * **      ***********     |*     ****          *******     |
;*      29: |   ** * **      ***********     |*     ****          *******     |
;*      30: |   ** * **      ***********     |*     ****          *******     |
;*      31: |   ** ****      ***********     |*     ****          *******     |
;*      32: |   ** ****      ***********     |*     ****          *******     |
;*      33: |   ** ****      ***********     |*     ****          *******     |
;*      34: |   ** ****      ***********     |*     ****          *******     |
;*      35: |   *******      ***********     |*     ****          *******     |
;*      36: |   ** ****      ******** **     |*     ****          *******     |
;*      37: |   ** ****      ******** **     |*     ****          *******     |
;*      38: |   ** ****      ******** **     |*     ****          *******     |
;*      39: |   *******      ******** **     |*     ****          *******     |
;*      40: |   ** ****      ******** **     |*     ****          *******     |
;*      41: |   ** ****      ******** **     |*     ****          *******     |
;*      42: |   *******      ******** **     |*     ****          *******     |
;*      43: |   ** * **      ******** **     |*     ****          *******     |
;*      44: |   ** * **      ******** **     |*     ****          *******     |
;*      45: |   ** * **      ******** **     |*     ****          *******     |
;*      46: |*  **** **      *******  **     |*     ****          *******     |
;*      47: |   ** ****      *******  **     |*     ****          *******     |
;*      48: |   ** ****      *******  **     |*     ****          *******     |
;*      49: |   ** ****      *******  **     |*     ****          *******     |
;*      50: |*  *  ****      *******  **     |*     ****          *******     |
;*      51: |   ** ****      *******  **     |*     ****          *******     |
;*      52: |   *  ****      *******  **     |*     ****          *******     |
;*      53: |   *  ****      *******  **     |*     ****          *******     |
;*      54: |   *  ****      *******  **     |*     ****          *******     |
;*      55: |   ** ****      *******  **     |*     ****          *******     |
;*      56: |   *  ****      *******   *     |*     ****          *******     |
;*      57: |   *  ****      *******   *     |*     ****          *******     |
;*      58: |   *  ****      *******  **     |*     ****          *******     |
;*      59: |   *  ****      *******  **     |*     ****          *******     |
;*      60: |   *******      *******  **     |*     ****          *******     |
;*      61: |   *  ****      *******  **     |*     ****          *******     |
;*      62: |   * *****      *******  **     |*     ****          *******     |
;*      63: |   *  ****      ******* ***     |*     ****          *******     |
;*      64: |   *******      ***********     |*     ****          *******     |
;*      65: |   *******      ********* *     |*     ****         ********     |
;*      66: |   *******      ********* *     |*     ****         ********     |
;*      67: |   *  ****      ********* *     |*     ****         ********     |
;*      68: |   *  ****      ********* *     |*     ****         ********     |
;*      69: |   *  ****      ********* *     |*     ****         ********     |
;*      70: |   *  ****      ********* *     |*     ****         ********     |
;*      71: |   *  ****      ********* *     |*     ****         ********     |
;*      72: |   *  ****      ********* *     |*   ******         ********     |
;*      73: |   *  ****      ********* *     |*     ****         ********     |
;*      74: |   *  ****      ********* *     |*     ****         ********     |
;*      75: |   *  ****      ********* *     |*     ****      ** ********     |
;*      76: |   *  ****      ********* *     |*     ****      ** ********     |
;*      77: |   *  ****      ********* *     |*     ****      ** ********     |
;*      78: |   *  ****      ********* *     |*     ****      ** ********     |
;*      79: |   *  ****      ********* *     |*   * ****      ** ********     |
;*      80: |   *  ****      ******* * *     |*   * ****      ** ********     |
;*      81: |   *  ****      ******* * *     |*   * ****      ** ********     |
;*      82: |   *  ****      ******* * *     |*   * ****      ** ********     |
;*      83: |   *  ****      ******* * *     |*   * ****      ** ********     |
;*      84: |   *******      ********* *     |*   ******      ** ********     |
;*      85: |   *******      ******* * *     |*   ******      ** ********     |
;*      86: |   *  ****      *******   *     |*   ******      ** ********     |
;*      87: |   ** ****      *******   *     |*    *****      ** ********     |
;*      88: |   ** ****      *******   *     |*   ******      ** ********     |
;*      89: |   *  ****      *******   *     |*   ******      ** ********     |
;*      90: |   *******      *******   *     |*   ******      ***********     |
;*      91: |   *  ****      *******   *     |*   ******      ** ********     |
;*      92: |   *  ****      *******   *     |*     ****      ***********     |
;*      93: |   *******      *******   *     |*     ****      ***********     |
;*      94: |   *******      *******   *     |*   * ****      ***********     |
;*      95: |   *  ****      *******   *     |*   ******        *********     |
;*      96: |   *  ****      *******   *     |*     ****        *********     |
;*      97: |   *  ****      *******   *     |*   ******        *********     |
;*      98: |   *  ****      *******   *     |*   * ****        *********     |
;*      99: |   *  ****      *******   *     |*     ****         ********     |
;*      100: |   *  ****      *******   *     |*     ****         ********     |
;*      101: |   *  ****      *******   *     |*   ******         ********     |
;*      102: |   *  ****      *******   *     |*     ****         ********     |
;*      103: |   *  ****      *******   *     |**    ****          *******     |
;*      104: |   *  ****      *******   *     |**  ******          *******     |
;*      105: |*  *   ***      *******   *     |*   * ****          *******     |
;*      106: |   *   ***      *******   *     |*   ******          *******     |
;*      107: |   *   ***      *******   *     |*   ******          *******     |
;*      108: |   *   ***      *******   *     |*   ******          *******     |
;*          +-----------------------------------------------------------------+
;*
;*      Done
;*
;*      Collapsed epilog stages       : 0
;*      Collapsed prolog stages       : 0
;*
;*      Minimum safe trip count       : 1
;*
;*
;*      Mem bank conflicts/iter(est.) : { min 0.000, est 0.000, max 0.000 }
;*      Mem bank perf. penalty (est.) : 0.0%
;*
;*
;*      Total cycles (est.)         : 0 + min_trip_cnt * 109 = 21909        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             B0,1,B0
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C104:
;*   0              LDW     .D1T1   *A8++,A6          ; |128|  ^ 
;*   1              NOP             4
;*   5              MPYSP   .M1     A6,A6,A23         ; |128|  ^ 
;*   6              MPYSP   .M1     A21,A6,A25        ; |128| 
;*   7              NOP             2
;*   9              FSUBSP  .L1     A23,A22,A4        ; |128|  ^ 
;*  10              NOP             2
;*  12              MPYSP   .M1     A21,A4,A24        ; |128|  ^ 
;*  13              NOP             2
;*  15              RSQRSP  .S1     A4,A7             ; |128| 
;*  16              MPYSP   .M1     A7,A24,A5         ; |128|  ^ 
;*  17              NOP             3
;*  20              MPYSP   .M1     A7,A5,A5          ; |128|  ^ 
;*  21              NOP             3
;*  24              FSUBSP  .L1     A20,A5,A5         ; |128|  ^ 
;*  25              NOP             2
;*  27              MPYSP   .M1     A7,A5,A7          ; |128|  ^ 
;*  28              NOP             3
;*  31              MPYSP   .M1     A7,A7,A5          ; |128|  ^ 
;*  32              NOP             3
;*  35              MPYSP   .M1     A24,A5,A5         ; |128|  ^ 
;*  36              NOP             3
;*  39              FSUBSP  .L1     A20,A5,A5         ; |128|  ^ 
;*  40              NOP             2
;*  42              MPYSP   .M1     A7,A5,A5          ; |128|  ^ 
;*  43              NOP             2
;*  45              CMPEQSP .S1     A4,A23,A0         ; |128| 
;*  46      [ A0]   MV      .L1     A6,A7             ; |128| 
;*     ||   [!A0]   MPYSP   .M1     A4,A5,A7          ; |128|  ^ 
;*  47              NOP             2
;*  49              CMPEQSP .S1     A4,A19,A0         ; |128| 
;*  50      [!A0]   MV      .S1     A7,A4             ; |128|  ^ 
;*     ||   [ A0]   MV      .L1     A19,A4            ; |128| 
;*  51              MPYSP   .M1     A21,A4,A4         ; |128|  ^ 
;*  52              NOP             3
;*  55              FADDSP  .L1     A25,A4,A25        ; |128|  ^ 
;*  56              NOP             2
;*  58              SPDP    .S1     A25,A5:A4         ; |95|  ^ 
;*  59              NOP             1
;*  60              RCPDP   .S1     A5:A4,A5:A4       ; |95|  ^ 
;*  61              NOP             1
;*  62              CLR     .S1     A5,0,16,A24       ; |95|  ^ 
;*  63              MV      .D1     A24,A5            ; |95|  ^ 
;*     ||           MV      .L1     A3,A4             ; |95| 
;*     ||           EXTU    .S1     A24,1,21,A23      ; |95| 
;*  64              MV      .L2X    A25,B19           ; |128| Define a twin register
;*     ||           ADD     .L1     A16,A23,A23       ; |95| 
;*     ||           EXTU    .S1     A24,12,29,A24     ; |95| 
;*  65              MPYSPDP .M2X    B19,A5:A4,B5:B4   ; |95|  ^ 
;*  66              NOP             6
;*  72              FSUBDP  .L2     B5:B4,B9:B8,B17:B16 ; |95|  ^ 
;*  73              NOP             2
;*  75              DPSP    .L2     B17:B16,B4        ; |95|  ^ 
;*  76              NOP             3
;*  79              INTDP   .L1     A23,A5:A4         ; |95| 
;*  80              MPYSP   .M2     B4,B4,B5          ; |95| 
;*     ||           MPYSP   .M1X    A17,B4,A23        ; |95|  ^ 
;*  81              NOP             3
;*  84              FADDSP  .L1     A18,A23,A4        ; |95|  ^ 
;*     ||           MPYSP   .M2     B25,B5,B4         ; |95| 
;*  85              FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |95| 
;*     ||           LDDW    .D1T1   *+A9[A24],A5:A4   ; |95| 
;*  86              MPYSP   .M2     B5,B4,B18         ; |95| 
;*  87              MPYSP   .M2     B5,B5,B5          ; |95| 
;*  88              FADDSP  .L2X    B4,A4,B4          ; |95|  ^ 
;*     ||           MPYSP   .M2     B23,B5,B18        ; |95| 
;*  89              NOP             1
;*  90              FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |95| 
;*     ||           MPYSP   .M2     B24,B18,B4        ; |95| 
;*  91              MPYSP   .M2     B5,B4,B5          ; |95|  ^ 
;*  92              NOP             2
;*  94              FADDDP  .L2X    A5:A4,B17:B16,B5:B4 ; |95| 
;*  95              FADDSP  .L2     B5,B4,B4          ; |95|  ^ 
;*  96              NOP             1
;*  97              DPSP    .L2     B5:B4,B4          ; |95| 
;*  98              FADDSP  .S2     B4,B18,B5         ; |95|  ^ 
;*  99              NOP             2
;*  101              FADDSP  .L2     B5,B4,B5          ; |95|  ^ 
;*  102              CMPGTSP .S2X    B19,A26,B1        ; |95| 
;*  103      [ B1]   MV      .D2     B22,B4            ; |95| 
;*     ||   [ B0]   BDEC    .S2     $C$C104,B0        ; |168| 
;*  104      [!B1]   MV      .L2     B5,B4             ; |95|  ^ 
;*     ||           CMPLTSP .S1     A6,A22,A0         ; |95| 
;*  105      [ A0]   MV      .S2     B21,B5            ; |95| 
;*     ||   [!A0]   FADDSP  .L2     B26,B4,B5         ; |95|  ^ 
;*  106              NOP             2
;*  108              STW     .D2T2   B5,*B20++         ; |95|  ^ 
;*  109              ; BRANCHCC OCCURS {$C$C104}       ; |168| 
;*----------------------------------------------------------------------------*
$C$L6:    ; PIPED LOOP PROLOG
;** --------------------------------------------------------------------------*
$C$L7:    ; PIPED LOOP KERNEL
;          EXCLUSIVE CPU CYCLES: 109
           LDW     .D1T1   *A8++,A6          ; |128| <0,0>  ^ 
           NOP             4
           MPYSP   .M1     A6,A6,A23         ; |128| <0,5>  ^ 
           MPYSP   .M1     A21,A6,A25        ; |128| <0,6> 
           NOP             2
           FSUBSP  .L1     A23,A22,A4        ; |128| <0,9>  ^ 
           NOP             2
           MPYSP   .M1     A21,A4,A24        ; |128| <0,12>  ^ 
           NOP             2
           RSQRSP  .S1     A4,A7             ; |128| <0,15> 
           MPYSP   .M1     A7,A24,A5         ; |128| <0,16>  ^ 
           NOP             3
           MPYSP   .M1     A7,A5,A5          ; |128| <0,20>  ^ 
           NOP             3
           FSUBSP  .L1     A20,A5,A5         ; |128| <0,24>  ^ 
           NOP             2
           MPYSP   .M1     A7,A5,A7          ; |128| <0,27>  ^ 
           NOP             3
           MPYSP   .M1     A7,A7,A5          ; |128| <0,31>  ^ 
           NOP             3
           MPYSP   .M1     A24,A5,A5         ; |128| <0,35>  ^ 
           NOP             3
           FSUBSP  .L1     A20,A5,A5         ; |128| <0,39>  ^ 
           NOP             2
           MPYSP   .M1     A7,A5,A5          ; |128| <0,42>  ^ 
           NOP             2
           CMPEQSP .S1     A4,A23,A0         ; |128| <0,45> 

   [ A0]   MV      .L1     A6,A7             ; |128| <0,46> 
|| [!A0]   MPYSP   .M1     A4,A5,A7          ; |128| <0,46>  ^ 

           NOP             2
           CMPEQSP .S1     A4,A19,A0         ; |128| <0,49> 

   [ A0]   MV      .L1     A19,A4            ; |128| <0,50> 
|| [!A0]   MV      .S1     A7,A4             ; |128| <0,50>  ^ 

           MPYSP   .M1     A21,A4,A4         ; |128| <0,51>  ^ 
           NOP             3
           FADDSP  .L1     A25,A4,A25        ; |128| <0,55>  ^ 
           NOP             2
           SPDP    .S1     A25,A5:A4         ; |95| <0,58>  ^ 
           NOP             1
           RCPDP   .S1     A5:A4,A5:A4       ; |95| <0,60>  ^ 
           NOP             1
           CLR     .S1     A5,0,16,A24       ; |95| <0,62>  ^ 

           MV      .L1     A3,A4             ; |95| <0,63> 
||         EXTU    .S1     A24,1,21,A23      ; |95| <0,63> 
||         MV      .D1     A24,A5            ; |95| <0,63>  ^ 

           EXTU    .S1     A24,12,29,A24     ; |95| <0,64> 
||         ADD     .L1     A16,A23,A23       ; |95| <0,64> 
||         MV      .L2X    A25,B19           ; |128| <0,64> Define a twin register

           MPYSPDP .M2X    B19,A5:A4,B5:B4   ; |95| <0,65>  ^ 
           NOP             6
           FSUBDP  .L2     B5:B4,B9:B8,B17:B16 ; |95| <0,72>  ^ 
           NOP             2
           DPSP    .L2     B17:B16,B4        ; |95| <0,75>  ^ 
           NOP             3
           INTDP   .L1     A23,A5:A4         ; |95| <0,79> 

           MPYSP   .M2     B4,B4,B5          ; |95| <0,80> 
||         MPYSP   .M1X    A17,B4,A23        ; |95| <0,80>  ^ 

           NOP             3

           MPYSP   .M2     B25,B5,B4         ; |95| <0,84> 
||         FADDSP  .L1     A18,A23,A4        ; |95| <0,84>  ^ 

           LDDW    .D1T1   *+A9[A24],A5:A4   ; |95| <0,85> 
||         FMPYDP  .M2X    B7:B6,A5:A4,B5:B4 ; |95| <0,85> 

           MPYSP   .M2     B5,B4,B18         ; |95| <0,86> 
           MPYSP   .M2     B5,B5,B5          ; |95| <0,87> 

           MPYSP   .M2     B23,B5,B18        ; |95| <0,88> 
||         FADDSP  .L2X    B4,A4,B4          ; |95| <0,88>  ^ 

           NOP             1

           MPYSP   .M2     B24,B18,B4        ; |95| <0,90> 
||         FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |95| <0,90> 

           MPYSP   .M2     B5,B4,B5          ; |95| <0,91>  ^ 
           NOP             2
           FADDDP  .L2X    A5:A4,B17:B16,B5:B4 ; |95| <0,94> 
           FADDSP  .L2     B5,B4,B4          ; |95| <0,95>  ^ 
           NOP             1
           DPSP    .L2     B5:B4,B4          ; |95| <0,97> 
           FADDSP  .S2     B4,B18,B5         ; |95| <0,98>  ^ 
           NOP             2
           FADDSP  .L2     B5,B4,B5          ; |95| <0,101>  ^ 
           CMPGTSP .S2X    B19,A26,B1        ; |95| <0,102> 

   [ B1]   MV      .D2     B22,B4            ; |95| <0,103> 
|| [ B0]   BDEC    .S2     $C$L7,B0          ; |168| <0,103> 

           CMPLTSP .S1     A6,A22,A0         ; |95| <0,104> 
|| [!B1]   MV      .L2     B5,B4             ; |95| <0,104>  ^ 

   [ A0]   MV      .S2     B21,B5            ; |95| <0,105> 
|| [!A0]   FADDSP  .L2     B26,B4,B5         ; |95| <0,105>  ^ 

           NOP             2
           STW     .D2T2   B5,*B20++         ; |95| <0,108>  ^ 
;** --------------------------------------------------------------------------*
$C$L8:    ; PIPED LOOP EPILOG
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T2   *+SP(44),B13
           STW     .D2T2   B24,*+SP(28)
           STW     .D2T2   B22,*+SP(36)
           STW     .D2T1   A18,*+SP(20)
           STW     .D2T1   A17,*+SP(24)
           STW     .D2T1   A16,*+SP(32)
           STW     .D2T2   B9,*+SP(48)
           STW     .D2T2   B7,*+SP(56)
           STW     .D2T2   B6,*+SP(52)

           RINT                              ; interrupts on
||         MV      .L1     A9,A14
||         MV      .D1     A19,A13
||         STW     .D2T2   B25,*+SP(16)
||         MVK     .S1     0xc9,A6           ; |171| 

           ADD     .L1X    4,B13,A3
||         MV      .S1     A20,A12
||         MV      .L2X    A26,B11
||         MV      .S2     B21,B10
||         STW     .D2T2   B26,*+SP(12)
||         MV      .D1     A15,A4            ; |171| 

           CALLP   .S2     acoshsp_v,B3
||         LDW     .D1T2   *A3,B4            ; |171| 
||         STW     .D2T1   A3,*+SP(60)
||         MV      .L1     A21,A10
||         MV      .S1     A22,A11
||         MV      .L2     B23,B12

$C$RL8:    ; CALL OCCURS {acoshsp_v} {0}     ; |171| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0xc9,A4           ; |174| 

$C$RL9:    ; CALL OCCURS {allequal} {0}      ; |174| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x1,A4            ; |175| 

$C$RL10:   ; CALL OCCURS {print_test_results} {0}  ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           ZERO    .L2     B6

           MVKH    .S2     0xbf800000,B6
||         STW     .D2T1   A11,*+SP(80)      ; |187| 

           STW     .D2T2   B6,*+SP(84)       ; |187| 
           LDW     .D2T1   *+SP(56),A3       ; |95| 
           LDW     .D2T1   *+SP(48),A30      ; |95| 
           LDW     .D2T1   *+SP(52),A31      ; |95| 

           MVKL    .S2     a_sc,B7
||         MVK     .L2     0x8,B30
||         STW     .D2T2   B13,*+SP(64)      ; |95| 

           MVKH    .S2     a_sc,B7
||         MV      .L2     B10,B5            ; |189| 
||         ZERO    .L1     A29               ; |95| 
||         STW     .D2T2   B30,*+SP(40)      ; |185| 

           MV      .L2     B7,B6             ; |183| 
||         MVK     .S2     -1,B4             ; |189| 
||         STW     .D2T1   A29,*+SP(92)      ; |185| 

           STDW    .D2T2   B5:B4,*+B6(24)    ; |189| 
||         MV      .L2     B6,B4
||         ADD     .L1X    1,B10,A6
||         MV      .S1     A13,A7            ; |183| 

           STDW    .D2T1   A7:A6,*B4         ; |183| 
           LDDW    .D2T2   *+SP(80),B5:B4    ; |183| 
           STW     .D2T1   A3,*+SP(96)       ; |95| 

           ZERO    .L1     A4
||         STW     .D2T1   A30,*+SP(88)      ; |95| 

           MV      .L2     B6,B31
||         MVKH    .S1     0xff800000,A4
||         ADD     .L1X    1,B11,A5
||         STW     .D2T1   A31,*+SP(100)     ; |95| 

           STDW    .D2T1   A5:A4,*+B31(8)    ; |185| 

           STDW    .D2T2   B5:B4,*+B6(16)    ; |187| 
||         MV      .L1X    B7,A15            ; |183| 
||         CALL    .S1     acoshf            ; |192| 

           LDW     .D1T1   *A15,A4           ; |192| 
           ZERO    .L2     B13               ; |95| 
           NOP             1
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 2
           ADDKPC  .S2     $C$RL11,B3,1      ; |192| 
$C$RL11:   ; CALL OCCURS {acoshf} {0}        ; |192| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |192| 
           NOP             4
           ADD     .L2     B13,B4,B4         ; |192| 
           STW     .D2T1   A4,*B4            ; |192| 

           CALLP   .S2     acoshsp,B3
||         LDW     .D1T1   *A15,A4           ; |193| 

$C$RL12:   ; CALL OCCURS {acoshsp} {0}       ; |193| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |193| 
           NOP             4
           ADD     .L2     B13,B4,B4         ; |193| 
           STW     .D2T1   A4,*B4            ; |193| 

           CALLP   .S2     acoshsp_c,B3
||         LDW     .D1T1   *A15,A4           ; |194| 

$C$RL13:   ; CALL OCCURS {acoshsp_c} {0}     ; |194| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 123
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |194| 
           LDW     .D2T1   *+SP(32),A29      ; |95| 
           LDW     .D2T2   *+SP(24),B31
           LDW     .D2T1   *+SP(16),A28
           LDW     .D2T2   *+SP(20),B30      ; |95| 
           ADD     .L2     B13,B4,B4         ; |194| 
           STW     .D2T1   A4,*B4            ; |194| 
           LDW     .D1T1   *A15++,A3         ; |195| 
           LDW     .D2T1   *+SP(28),A25
           LDW     .D2T2   *+SP(64),B28      ; |95| 
           LDW     .D2T2   *+SP(12),B27      ; |98| 
           NOP             1
           MPYSP   .M1     A3,A3,A6          ; |164| 
           MPYSP   .M1     A10,A3,A31        ; |95| 
           LDW     .D2T2   *B28,B6           ; |195| 
           CMPLTSP .S1     A3,A11,A2         ; |168| 
           FSUBSP  .L1     A6,A11,A5         ; |164| 
           NOP             2
           MPYSP   .M1     A10,A5,A7         ; |128| 
           RSQRSP  .S1     A5,A4             ; |128| 
           CMPEQSP .S1     A5,A6,A1          ; |130| 
           CMPEQSP .S1     A5,A13,A0         ; |134| 
           MPYSP   .M1     A4,A7,A8          ; |128| 
           ADD     .L2     B13,B6,B6         ; |195| 
           ADD     .L2     4,B13,B13         ; |191| 
           NOP             1
           MPYSP   .M1     A4,A8,A8          ; |128| 
           NOP             3
           FSUBSP  .L1     A12,A8,A8         ; |128| 
           NOP             2
           MPYSP   .M1     A4,A8,A4          ; |128| 
           NOP             3
           MPYSP   .M1     A4,A4,A8          ; |128| 
           NOP             3
           MPYSP   .M1     A7,A8,A7          ; |128| 
           NOP             3
           FSUBSP  .L1     A12,A7,A7         ; |128| 
           NOP             2
           MPYSP   .M1     A4,A7,A4          ; |128| 
           LDDW    .D2T1   *+SP(88),A7:A6
           NOP             2
           MPYSP   .M1     A5,A4,A4          ; |128| 
           NOP             3
   [ A1]   MV      .L1     A3,A4             ; |131| 
   [ A0]   MV      .L1     A13,A4            ; |135| 
           MPYSP   .M1     A10,A4,A4         ; |95| 
           NOP             3
           FADDSP  .L1     A31,A4,A16        ; |95| 
           NOP             2
           SPDP    .S1     A16,A5:A4         ; |95| 
           CMPGTSP .S2X    A16,B11,B0        ; |97| 
           RCPDP   .S1     A5:A4,A5:A4       ; |95| 
           NOP             1

           CLR     .S1     A5,0,16,A19       ; |95| 
||         ZERO    .L1     A4                ; |95| 

           MV      .L1     A19,A5            ; |95| 
           MPYSPDP .M1     A16,A5:A4,A5:A4   ; |95| 
           EXTU    .S1     A19,1,21,A30      ; |95| 
           EXTU    .S1     A19,12,29,A27     ; |95| 
           NOP             4

           FSUBDP  .L1     A5:A4,A7:A6,A9:A8 ; |95| 
||         ADD     .S1     A29,A30,A4        ; |95| 

           INTDP   .L1     A4,A5:A4          ; |95| 
           LDDW    .D2T1   *+SP(96),A7:A6    ; |95| 
           DPSP    .L1     A9:A8,A18         ; |95| 
           NOP             3
           MPYSP   .M1     A18,A18,A17       ; |95| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |95| 
           MPYSP   .M2X    B31,A18,B5        ; |95| 
           LDDW    .D1T1   *+A14[A27],A7:A6  ; |95| 
           MPYSP   .M1     A28,A17,A20       ; |95| 
           MPYSP   .M1     A17,A18,A18       ; |95| 
           FADDSP  .L2     B30,B5,B4         ; |95| 
           MPYSP   .M1     A17,A17,A26       ; |95| 
           FSUBDP  .L1     A7:A6,A5:A4,A5:A4 ; |95| 
           FADDSP  .L2X    A20,B4,B4         ; |95| 
           MPYSP   .M1     A25,A18,A24       ; |95| 
           FADDDP  .L1     A5:A4,A9:A8,A5:A4 ; |95| 
           MPYSP   .M2X    A26,B4,B5         ; |95| 
           MPYSP   .M2X    B12,A17,B29       ; |95| 
           DPSP    .L1     A5:A4,A4          ; |95| 
           NOP             1
           FADDSP  .L2X    B5,A24,B5         ; |95| 
           NOP             2
           FADDSP  .L2     B5,B29,B4         ; |95| 
           NOP             2

           FADDSP  .L2X    B4,A4,B5          ; |95| 
|| [ B0]   LDW     .D2T2   *+SP(36),B5       ; |97| 

           LDW     .D2T2   *+SP(40),B4       ; |169| 
           NOP             3
           FADDSP  .L2     B27,B5,B5         ; |166| 

           SUB     .L1X    B4,1,A0           ; |191| 
||         SUB     .L2     B4,1,B4           ; |191| 

   [ A0]   B       .S1     $C$L9             ; |191| 
|| [!A0]   MVKL    .S2     output,B13
||         STW     .D2T2   B4,*+SP(40)       ; |195| 

   [ A2]   MV      .L2     B10,B5            ; |169| 
|| [!A0]   MVKH    .S2     output,B13

   [ A0]   CALL    .S1     acoshf            ; |192| 
||         STW     .D2T2   B5,*B6            ; |195| 

   [!A0]   CALL    .S1     acoshsp_v         ; |197| 
|| [ A0]   LDW     .D1T1   *A15,A4           ; |192| 

   [!A0]   LDW     .D2T2   *+B13(16),B4      ; |197| 
   [!A0]   MVKL    .S1     a_sc,A4
           ; BRANCHCC OCCURS {$C$L9}         ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
           MVK     .L1     0x8,A6            ; |197| 
           ADDKPC  .S2     $C$RL14,B3,0      ; |197| 
           MVKH    .S1     a_sc,A4
$C$RL14:   ; CALL OCCURS {acoshsp_v} {0}     ; |197| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 42
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D2T1   *B13,A4           ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MVK     .L1     0x8,A6            ; |66| 
||         MVK     .S1     0x1,A8            ; |66| 

$C$RL15:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0x3eb0c6f7,B7

           MVKL    .S1     fcn_pass,A3
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKH    .S1     fcn_pass,A3
||         MVKH    .S2     0x3eb0c6f7,B7

           STW     .D1T1   A4,*+A3(4)        ; |66| 
||         LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .L1     0x8,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL16:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3eb0c6f7,B7

           MVKL    .S1     fcn_pass,A5
||         MVKL    .S2     0xa0b5ed8d,B6

           MVKH    .S1     fcn_pass,A5
||         MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1X    B13,A3            ; |67| 
||         STW     .D1T1   A4,*+A5(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B13(12),B4      ; |68| 
||         MVK     .L1     0x8,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL17:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T1   *+SP(60),A3       ; |68| 
           MVKL    .S1     fcn_pass,A6
           MVKL    .S2     0xa0b5ed8d,B6

           MVKH    .S1     fcn_pass,A6
||         MVKL    .S2     0x3eb0c6f7,B7

           STW     .D1T1   A4,*+A6(12)       ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           MV      .L2X    A3,B4             ; |66| 
||         MV      .L1X    B13,A5            ; |68| 
||         STW     .D2T1   A3,*+SP(64)       ; |68| 
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *B4,B4            ; |69| 
||         LDW     .D1T1   *A5,A4            ; |69| 
||         MVK     .L1     0x8,A6            ; |69| 
||         MVK     .S1     0x1,A8            ; |69| 

$C$RL18:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           LDW     .D2T1   *+SP(84),A3
||         MVKL    .S2     fcn_pass,B4

           MVKH    .S2     fcn_pass,B4
           ADD     .L2     4,B4,B4
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D2T2   B4,*+SP(68)

           STW     .D2T1   A3,*+SP(40)       ; |69| 
||         MVKL    .S1     fcn_pass,A3

           MVKH    .S1     fcn_pass,A3
           STW     .D1T1   A4,*+A3(16)       ; |69| 

   [!B0]   B       .S2     $C$L10            ; |72| 
||         ADD     .L2X    8,A3,B4
|| [!B0]   MVKL    .S1     all_pass,A3
|| [!B0]   ZERO    .L1     A4                ; |72| 
||         MV      .D2     B0,B1             ; guard predicate rewrite

   [!B0]   CALL    .S2     print_test_results ; |201| 
|| [!B0]   MVKH    .S1     all_pass,A3
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

           STW     .D2T2   B4,*+SP(72)       ; |69| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             2
           ; BRANCHCC OCCURS {$C$L10}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [!A0]   ZERO    .L1     A4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |201| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             2
;** --------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x3,A4            ; |201| 
||         ADDKPC  .S2     $C$RL19,B3,0      ; |201| 

$C$RL19:   ; CALL OCCURS {print_test_results} {0}  ; |201| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T1   *+SP(44),A3       ; |210| 
           LDW     .D2T1   *+SP(56),A31      ; |95| 

           LDW     .D2T1   *+SP(52),A30      ; |95| 
||         MVK     .S2     0x77,B29

           LDW     .D2T1   *+SP(48),A29      ; |95| 
||         MVKL    .S2     0x4000cccc,B4
||         ZERO    .L1     A28               ; |95| 

           MVKL    .S2     0xcccccccd,B31
||         STW     .D2T1   A28,*+SP(84)      ; |204| 

           MVKH    .S2     0x4000cccc,B4
||         STW     .D2T2   B29,*+SP(44)      ; |204| 

           MVKH    .S2     0xcccccccd,B31
||         STW     .D2T2   B4,*+SP(96)       ; |210| 

           MVKL    .S2     a_ext,B5
||         STW     .D2T2   B31,*+SP(100)     ; |210| 

           MVKH    .S2     a_ext,B5
||         STW     .D2T1   A31,*+SP(88)      ; |95| 

           MV      .L2     B5,B30            ; |204| 
||         STW     .D2T1   A30,*+SP(92)      ; |95| 

           STW     .D2T1   A11,*B30          ; |204| 
           STW     .D2T1   A29,*+SP(80)      ; |95| 

           STW     .D2T1   A3,*+SP(76)       ; |95| 
||         MV      .L1X    B5,A15            ; |204| 
||         CALL    .S1     acoshf            ; |206| 

           LDW     .D1T1   *A15,A4           ; |206| 
           ZERO    .L2     B13               ; |95| 
           NOP             2
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL20,B3,0      ; |206| 
$C$RL20:   ; CALL OCCURS {acoshf} {0}        ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *B4,B4            ; |206| 
           NOP             4
           ADD     .L2     B13,B4,B4         ; |206| 
           STW     .D2T1   A4,*B4            ; |206| 

           CALLP   .S2     acoshsp,B3
||         LDW     .D1T1   *A15,A4           ; |207| 

$C$RL21:   ; CALL OCCURS {acoshsp} {0}       ; |207| 
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(4),B4        ; |207| 
           NOP             4
           ADD     .L2     B13,B4,B4         ; |207| 
           STW     .D2T1   A4,*B4            ; |207| 

           CALLP   .S2     acoshsp_c,B3
||         LDW     .D1T1   *A15,A4           ; |208| 

$C$RL22:   ; CALL OCCURS {acoshsp_c} {0}     ; |208| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 145
           MVKL    .S2     output,B4
           MVKH    .S2     output,B4
           LDW     .D2T2   *+B4(8),B4        ; |208| 
           LDW     .D2T1   *+SP(32),A29      ; |95| 
           LDW     .D2T2   *+SP(24),B31
           LDW     .D2T1   *+SP(16),A28
           LDW     .D2T2   *+SP(20),B5       ; |95| 
           ADD     .L2     B13,B4,B4         ; |208| 
           STW     .D2T1   A4,*B4            ; |208| 
           LDW     .D1T1   *A15,A3           ; |209| 
           LDW     .D2T1   *+SP(28),A25
           LDW     .D2T2   *+SP(76),B29      ; |95| 
           LDW     .D2T2   *+SP(12),B28      ; |98| 
           NOP             1
           MPYSP   .M1     A3,A3,A6          ; |164| 
           MPYSP   .M1     A10,A3,A31        ; |95| 
           LDW     .D2T2   *B29,B6           ; |209| 
           CMPLTSP .S1     A3,A11,A2         ; |168| 
           FSUBSP  .L1     A6,A11,A5         ; |164| 
           NOP             2
           MPYSP   .M1     A10,A5,A7         ; |128| 
           RSQRSP  .S1     A5,A4             ; |128| 
           CMPEQSP .S1     A5,A6,A1          ; |130| 
           CMPEQSP .S1     A5,A13,A0         ; |134| 
           MPYSP   .M1     A4,A7,A8          ; |128| 
           NOP             3
           MPYSP   .M1     A4,A8,A8          ; |128| 
           NOP             3
           FSUBSP  .L1     A12,A8,A8         ; |128| 
           NOP             2
           MPYSP   .M1     A4,A8,A4          ; |128| 
           NOP             3
           MPYSP   .M1     A4,A4,A8          ; |128| 
           NOP             3
           MPYSP   .M1     A7,A8,A7          ; |128| 
           LDDW    .D2T1   *+SP(88),A9:A8    ; |95| 
           NOP             2
           FSUBSP  .L1     A12,A7,A7         ; |128| 
           NOP             2
           MPYSP   .M1     A4,A7,A4          ; |128| 
           NOP             3
           MPYSP   .M1     A5,A4,A4          ; |128| 
           NOP             3
   [ A1]   MV      .L1     A3,A4             ; |131| 
   [ A0]   MV      .L1     A13,A4            ; |135| 
           MPYSP   .M1     A10,A4,A4         ; |95| 
           NOP             3
           FADDSP  .L1     A31,A4,A16        ; |95| 
           NOP             2
           SPDP    .S1     A16,A5:A4         ; |95| 
           CMPGTSP .S2X    A16,B11,B0        ; |97| 
           RCPDP   .S1     A5:A4,A5:A4       ; |95| 
           NOP             1

           CLR     .S1     A5,0,16,A19       ; |95| 
||         ZERO    .L1     A4                ; |95| 

           MV      .L1     A19,A5            ; |95| 
           MPYSPDP .M1     A16,A5:A4,A7:A6   ; |95| 
           LDDW    .D2T1   *+SP(80),A5:A4
           EXTU    .S1     A19,1,21,A30      ; |95| 
           EXTU    .S1     A19,12,29,A27     ; |95| 
           NOP             3

           FSUBDP  .L1     A7:A6,A5:A4,A7:A6 ; |95| 
||         ADD     .S1     A29,A30,A4        ; |95| 

           INTDP   .L1     A4,A5:A4          ; |95| 
           NOP             1
           DPSP    .L1     A7:A6,A18         ; |95| 
           NOP             3
           MPYSP   .M1     A18,A18,A17       ; |95| 
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |95| 
           MPYSP   .M2X    B31,A18,B4        ; |95| 
           LDDW    .D1T1   *+A14[A27],A9:A8  ; |95| 
           MPYSP   .M1     A28,A17,A20       ; |95| 
           MPYSP   .M1     A17,A18,A18       ; |95| 
           FADDSP  .L2     B5,B4,B4          ; |95| 
           MPYSP   .M1     A17,A17,A26       ; |95| 
           FSUBDP  .L1     A9:A8,A5:A4,A5:A4 ; |95| 
           FADDSP  .L2X    A20,B4,B4         ; |95| 
           MPYSP   .M1     A25,A18,A24       ; |95| 
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |95| 
           MPYSP   .M2X    A26,B4,B5         ; |95| 
           MPYSP   .M2X    B12,A17,B30       ; |95| 
           DPSP    .L1     A5:A4,A4          ; |95| 
           NOP             1
           FADDSP  .L2X    B5,A24,B5         ; |95| 
           NOP             2
           FADDSP  .L2     B5,B30,B4         ; |95| 
           NOP             2

           FADDSP  .L2X    B4,A4,B5          ; |95| 
|| [ B0]   LDW     .D2T2   *+SP(36),B5       ; |97| 

           NOP             4
           FADDSP  .L2     B28,B5,B4         ; |166| 
           ADD     .L2     B13,B6,B5         ; |209| 
           ADD     .S2     4,B13,B13         ; |205| 
   [ A2]   MV      .L2     B10,B4            ; |169| 
           STW     .D2T2   B4,*B5            ; |209| 
           LDW     .D1T2   *A15,B6           ; |210| 
           LDDW    .D2T2   *+SP(96),B5:B4
           NOP             4
           MPYSPDP .M2     B6,B5:B4,B5:B4    ; |210| 
           NOP             6

           DPSP    .L2     B5:B4,B5          ; |210| 
||         LDW     .D2T2   *+SP(44),B4

           NOP             3
           STW     .D1T2   B5,*++A15         ; |210| 

           SUB     .L1X    B4,1,A0           ; |205| 
||         SUB     .L2     B4,1,B4           ; |205| 

   [ A0]   B       .S1     $C$L11            ; |205| 
|| [!A0]   MVKL    .S2     output,B13
|| [ A0]   LDW     .D1T1   *A15,A4           ; |206| 
||         STW     .D2T2   B4,*+SP(44)       ; |210| 

   [ A0]   CALL    .S1     acoshf            ; |206| 
|| [!A0]   MVKH    .S2     output,B13

   [!A0]   CALL    .S1     acoshsp_v         ; |212| 
   [!A0]   LDW     .D2T2   *+B13(16),B4      ; |212| 
   [!A0]   MVKL    .S1     a_ext,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L11}        ; |205| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
           MVKH    .S1     a_ext,A4

           MVK     .S1     0x77,A6           ; |212| 
||         ADDKPC  .S2     $C$RL23,B3,0      ; |212| 

$C$RL23:   ; CALL OCCURS {acoshsp_v} {0}     ; |212| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 46
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D2T1   *B13,A4           ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *+B13(4),B4       ; |66| 
||         MVK     .S1     0x77,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL24:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKH    .S2     fcn_pass,B5
           MVKL    .S2     0xa0b5ed8d,B6

           LDW     .D2T2   *+B13(8),B4       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           STW     .D2T1   A4,*+B5(4)        ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T1   *B13,A4           ; |67| 
||         MVK     .S1     0x77,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL25:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     fcn_pass,B5
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B5
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L1X    B13,A3            ; |67| 
||         STW     .D2T1   A4,*+B5(8)        ; |67| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A3,A4            ; |68| 
||         LDW     .D2T2   *+B13(12),B4      ; |68| 
||         MVK     .S1     0x77,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL26:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     fcn_pass,B4

           LDW     .D2T1   *+SP(60),A3       ; |68| 
||         MVKL    .S2     0x3eb0c6f7,B7

           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     fcn_pass,B4
           MVKH    .S2     0x3eb0c6f7,B7

           MV      .L2     B13,B5            ; |68| 
||         STW     .D2T1   A4,*+B4(12)       ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *A3,B4            ; |69| 
||         LDW     .D2T1   *B5,A4            ; |69| 
||         MVK     .S1     0x77,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL27:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T1   *+SP(68),A3       ; |69| 
           LDW     .D2T2   *+SP(72),B4
           MVKL    .S2     fcn_pass,B5
           MVKH    .S2     fcn_pass,B5
           STW     .D2T1   A4,*+B5(16)       ; |69| 
           LDW     .D1T1   *A3,A0            ; |72| 
           NOP             4

   [ A0]   ADD     .L2     4,B4,B4
|| [!A0]   B       .S1     $C$L12            ; |72| 
|| [ A0]   LDW     .D2T2   *B4,B0            ; |72| 

   [!A0]   CALL    .S1     print_test_results ; |218| 
   [!A0]   MVKL    .S1     all_pass,A3
   [!A0]   MVKH    .S1     all_pass,A3
   [!A0]   ZERO    .L2     B4                ; |72| 
   [!A0]   MV      .L2X    A3,B5
           ; BRANCHCC OCCURS {$C$L12}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
   [!B0]   ZERO    .L1     A0                ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1

   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
||         MVK     .L2     0x1,B4            ; |72| 

   [!A0]   ZERO    .L2     B4                ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |218| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           NOP             1
           MV      .L2X    A3,B5
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 1

           MVK     .L1     0x4,A4            ; |218| 
||         STW     .D2T2   B4,*B5            ; |72| 
||         ADDKPC  .S2     $C$RL28,B3,0      ; |218| 

$C$RL28:   ; CALL OCCURS {print_test_results} {0}  ; |218| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20
           ZERO    .L1     A4                ; |114| 

           ZERO    .L1     A3                ; |114| 
||         STW     .D2T1   A4,*+SP(84)       ; |114| 

           STW     .D2T1   A3,*+SP(80)       ; |114| 
           LDDW    .D2T1   *+SP(80),A5:A4    ; |114| 
           MVKL    .S1     cycle_counts+24,A6
           MVKH    .S1     cycle_counts+24,A6
           ZERO    .L2     B4                ; |114| 
           NOP             1

           STDW    .D1T1   A5:A4,*A6         ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           STDW    .D1T2   B7:B6,*A3         ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B4,B6,B5:B4       ; |117| 
||         MVK     .S1     0x80,A3

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 
||         MVKL    .S1     t_offset,A4

           ADD     .L2     B31,B6,B5         ; |117| 
||         MVKH    .S1     t_offset,A4

           STDW    .D1T2   B5:B4,*A4         ; |117| 
||         MVKL    .S1     0x49742410,A4

           MVKH    .S1     0x49742410,A4
||         STW     .D2T1   A3,*+SP(44)       ; |117| 
||         ZERO    .L2     B13
||         CALL    .S2     gimme_random      ; |228| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *+SP(40),B4       ; |228| 
           ADDKPC  .S2     $C$RL29,B3,3      ; |228| 
$C$RL29:   ; CALL OCCURS {gimme_random} {0}  ; |228| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 131
           MVKL    .S2     input,B4
           MVKH    .S2     input,B4
           LDW     .D2T2   *B4,B4            ; |228| 
           NOP             4
           ADD     .L2     B13,B4,B4         ; |228| 

           STW     .D2T1   A4,*B4            ; |228| 
||         MVC     .S2     TSCL,B4           ; |122| 

           MVC     .S2     TSCH,B5           ; |122| 
           MPYSP   .M1     A4,A4,A7          ; |164| 
           MPYSP   .M1     A10,A4,A31        ; |95| 
           MVKL    .S1     0x3fe62e42,A17
           LDW     .D2T1   *+SP(32),A30      ; |95| 
           FSUBSP  .L1     A7,A11,A5         ; |164| 
           MVKL    .S1     0xfefa39ec,A16
           ZERO    .L2     B6                ; |95| 
           MPYSP   .M1     A10,A5,A6         ; |125| 
           RSQRSP  .S1     A5,A3             ; |125| 
           CMPEQSP .S1     A5,A7,A1          ; |130| 
           CMPEQSP .S1     A5,A13,A0         ; |134| 
           MPYSP   .M1     A3,A6,A8          ; |125| 
           ZERO    .L2     B7
           LDW     .D2T2   *+SP(24),B31      ; |95| 
           SET     .S2     B7,0x14,0x1d,B7
           MPYSP   .M1     A3,A8,A8          ; |125| 
           MVKH    .S1     0x3fe62e42,A17
           MVKH    .S1     0xfefa39ec,A16
           LDW     .D2T1   *+SP(16),A19      ; |95| 
           FSUBSP  .L1     A12,A8,A8         ; |125| 
           LDW     .D2T2   *+SP(20),B30      ; |95| 
           LDW     .D2T1   *+SP(28),A28
           MPYSP   .M1     A3,A8,A3          ; |125| 
           MVKL    .S2     output+12,B9
           MVKH    .S2     output+12,B9
           LDW     .D2T2   *+SP(12),B28      ; |98| 
           MPYSP   .M1     A3,A3,A8          ; |128| 
           MVKL    .S2     t_start,B8
           LDW     .D2T2   *B9,B9            ; |232| 
           CMPLTSP .S1     A4,A11,A2         ; |168| 
           MPYSP   .M1     A6,A8,A6          ; |128| 
           MVKH    .S2     t_start,B8
           STDW    .D2T2   B5:B4,*B8
           ADD     .L2     B13,B9,B27        ; |232| 
           FSUBSP  .L1     A12,A6,A6         ; |128| 
           NOP             2
           MPYSP   .M1     A3,A6,A3          ; |128| 
           NOP             3
           MPYSP   .M1     A5,A3,A3          ; |128| 
           NOP             3
   [ A1]   MV      .L1     A4,A3             ; |232| 
   [ A0]   MV      .L1     A13,A3            ; |135| 
           MPYSP   .M1     A10,A3,A3         ; |95| 
           NOP             3
           FADDSP  .L1     A31,A3,A3         ; |95| 
           NOP             2
           SPDP    .S1     A3,A7:A6          ; |95| 
           CMPGTSP .S2X    A3,B11,B0         ; |97| 
           RCPDP   .S1     A7:A6,A7:A6       ; |95| 
           NOP             1

           CLR     .S1     A7,0,16,A20       ; |95| 
||         ZERO    .L1     A6                ; |95| 

           MV      .L1     A20,A7            ; |95| 
           MPYSPDP .M1     A3,A7:A6,A7:A6    ; |95| 
           EXTU    .S1     A20,1,21,A5       ; |95| 
           ADD     .L1     A30,A5,A5         ; |95| 
           EXTU    .S1     A20,12,29,A29     ; |95| 
           NOP             3
           FSUBDP  .L1X    A7:A6,B7:B6,A9:A8 ; |95| 
           INTDP   .L1     A5,A7:A6          ; |95| 
           NOP             1
           DPSP    .L1     A9:A8,A18         ; |95| 
           NOP             3
           MPYSP   .M1     A18,A18,A5        ; |95| 
           FMPYDP  .M1     A17:A16,A7:A6,A7:A6 ; |95| 
           MPYSP   .M2X    B31,A18,B7        ; |95| 
           LDDW    .D1T1   *+A14[A29],A17:A16 ; |95| 
           MPYSP   .M1     A19,A5,A19        ; |95| 
           MPYSP   .M1     A5,A18,A21        ; |95| 
           FADDSP  .L2     B30,B7,B6         ; |95| 
           MPYSP   .M1     A5,A5,A20         ; |95| 
           FSUBDP  .L1     A17:A16,A7:A6,A7:A6 ; |95| 
           FADDSP  .L2X    A19,B6,B6         ; |95| 
           MPYSP   .M1     A28,A21,A27       ; |95| 
           FADDDP  .L1     A7:A6,A9:A8,A7:A6 ; |95| 
           MPYSP   .M2X    A20,B6,B7         ; |95| 
           MPYSP   .M2X    B12,A5,B29        ; |95| 
           DPSP    .L1     A7:A6,A5          ; |95| 
           NOP             1
           FADDSP  .L2X    B7,A27,B7         ; |95| 
           NOP             2
           FADDSP  .L2     B7,B29,B6         ; |95| 
           NOP             2

           FADDSP  .L2X    B6,A5,B6          ; |95| 
|| [ B0]   LDW     .D2T2   *+SP(36),B6       ; |97| 

           NOP             4
           FADDSP  .L2     B28,B6,B6         ; |166| 
           NOP             2
   [ A2]   MV      .L2     B10,B6            ; |169| 

           STW     .D2T2   B6,*B27           ; |232| 
||         MVC     .S2     TSCL,B6           ; |128| 

           MVC     .S2     TSCH,B7           ; |128| 

           MVKL    .S2     t_offset,B8
||         LDW     .D2T1   *+SP(44),A25      ; |128| 
||         MVKL    .S1     cycle_counts+24,A3
||         ADD     .L2     4,B13,B13         ; |226| 

           MVKH    .S2     t_offset,B8
||         MVKH    .S1     cycle_counts+24,A3

           LDDW    .D2T2   *B8,B9:B8         ; |130| 
||         LDDW    .D1T1   *A3,A5:A4         ; |130| 
||         MVKL    .S1     t_stop,A26

           MVKL    .S1     cycle_counts+24,A15
           MVKH    .S1     t_stop,A26

           SUB     .L1     A25,1,A0          ; |226| 
||         MVKH    .S1     cycle_counts+24,A15
||         STDW    .D1T2   B7:B6,*A26        ; |128| 

           STW     .D2T1   A0,*+SP(44)       ; |130| 
           ADDU    .L2     B8,B4,B17:B16     ; |130| 

           ADD     .S2     B17,B9,B4         ; |130| 
|| [ A0]   B       .S1     $C$L13            ; |226| 
||         SUBU    .L2     B6,B16,B9:B8      ; |130| 

           ADD     .L2     B4,B5,B4          ; |130| 
||         EXT     .S2     B9,24,24,B9       ; |130| 

           ADDU    .L2X    A4,B8,B5:B4       ; |130| 
||         SUB     .S2     B7,B4,B8          ; |130| 
|| [ A0]   MVKL    .S1     0x49742410,A4

           ADD     .L2X    B5,A5,B8          ; |130| 
||         ADD     .S2     B8,B9,B5          ; |130| 
|| [ A0]   MVKH    .S1     0x49742410,A4

           ADD     .L2     B8,B5,B5          ; |130| 

   [ A0]   CALL    .S1     gimme_random      ; |228| 
||         STDW    .D1T2   B5:B4,*A15        ; |130| 

           ; BRANCHCC OCCURS {$C$L13}        ; |226| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     __c6xabi_fltllif  ; |135| 
           LDDW    .D1T1   *A15,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL30,B3,3      ; |135| 
$C$RL30:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A10
           SET     .S1     A10,0x1a,0x1d,A10
           MPYSP   .M1     A10,A4,A3         ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           ZERO    .L1     A12               ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL31:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           LDDW    .D2T1   *+SP(80),A7:A6
           MV      .L2X    A15,B4
           SUBAW   .D1     A15,6,A3
           MV      .L2X    A12,B5            ; |114| 
           STDW    .D2T1   A5:A4,*B4         ; |135| 

           STDW    .D1T1   A7:A6,*A3         ; |114| 
||         MVC     .S2     B5,TSCL           ; |115| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 

           SUBU    .L2     B5,B4,B5:B4       ; |117| 
||         MVKL    .S2     t_offset,B7

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B6,B5          ; |117| 

           ADD     .L2     B5,B6,B5          ; |117| 
||         MVKH    .S2     t_offset,B7

           STDW    .D2T2   B5:B4,*B7         ; |117| 
||         MVK     .S1     0x80,A14

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |241| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |241| 
||         CALL    .S1     acoshf            ; |241| 

           LDW     .D1T1   *A3,A4            ; |241| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |241| 
$C$RL32:   ; CALL OCCURS {acoshf} {0}        ; |241| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output,B13
           MVKH    .S2     output,B13
           LDW     .D2T2   *B13,B4           ; |241| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |241| 

           STW     .D1T1   A4,*A3            ; |241| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A11
||         MVKL    .S2     t_start,B5
||         SUBAW   .D1     A15,6,A3
||         SUB     .L1     A14,1,A0          ; |239| 
||         MV      .L2     B4,B17            ; |128| 

           MVKH    .S1     t_offset,A11
||         MVKH    .S2     t_start,B5
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         SUB     .L1     A14,1,A14         ; |239| 

           LDDW    .D1T1   *A11,A5:A4        ; |130| 
||         LDDW    .D2T2   *B5,B7:B6         ; |130| 
||         MVK     .S2     24,B4
||         MVKL    .S1     t_stop,A31
||         ADD     .L1     4,A12,A12         ; |239| 

           MVKH    .S1     t_stop,A31
           SUB     .L2X    A15,B4,B4
           STDW    .D1T2   B17:B16,*A31      ; |128| 
   [!A0]   MV      .L1X    B4,A15
           ADDU    .L2X    A4,B6,B9:B8       ; |130| 

           ADD     .S2X    B9,A5,B5          ; |130| 
|| [ A0]   B       .S1     $C$L14            ; |239| 
||         SUBU    .L2     B16,B8,B9:B8      ; |130| 

           ADD     .D2     B5,B7,B5          ; |130| 
||         ADDU    .L2X    A6,B8,B7:B6       ; |130| 
||         EXT     .S2     B9,24,24,B8       ; |130| 

           SUB     .L2     B17,B5,B5         ; |130| 

           ADD     .L2X    B7,A7,B5          ; |130| 
||         ADD     .S2     B5,B8,B7          ; |130| 

           ADD     .L2     B5,B7,B7          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B7:B6,*B4         ; |130| 

           ; BRANCHCC OCCURS {$C$L14}        ; |239| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A15,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL33,B3,3      ; |135| 
$C$RL33:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MPYSP   .M1     A10,A4,A3         ; |135| 
           ZERO    .L1     A12               ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           LDDW    .D2T1   *+SP(80),A7:A6    ; |135| 
           MV      .L2X    A12,B4            ; |114| 
           STDW    .D1T1   A5:A4,*A15        ; |135| 
           NOP             2

           STDW    .D1T1   A7:A6,*+A15(16)   ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B9           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         SUB     .L2     B9,B4,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 
||         MV      .S2X    A11,B8            ; |117| 

           STDW    .D2T2   B7:B6,*B8         ; |117| 
||         MV      .L1     A12,A11           ; |117| 
||         MVK     .S1     0x80,A12

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |250| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A11,A3,A3         ; |250| 
||         CALL    .S1     acoshsp_c         ; |250| 

           LDW     .D1T1   *A3,A4            ; |250| 
           ADDKPC  .S2     $C$RL35,B3,3      ; |250| 
$C$RL35:   ; CALL OCCURS {acoshsp_c} {0}     ; |250| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           ADDAD   .D2     B13,1,B4
           LDW     .D2T2   *B4,B4            ; |250| 
           NOP             4
           ADD     .L1X    A11,B4,A3         ; |250| 

           STW     .D1T1   A4,*A3            ; |250| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A10
||         MVKL    .S2     t_start,B5
||         ADDAD   .D1     A15,2,A3
||         SUB     .L1     A12,1,A0          ; |248| 
||         MV      .L2     B4,B17            ; |128| 

           MVKH    .S1     t_offset,A10
||         MVKH    .S2     t_start,B5
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         SUB     .L1     A12,1,A12         ; |248| 

           MVKL    .S1     t_stop,A31
||         ADD     .L1     4,A11,A11         ; |248| 
||         LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         LDDW    .D2T2   *B5,B9:B8         ; |130| 

           MVK     .S2     16,B10
           MVKH    .S1     t_stop,A31
           ADD     .L2X    A15,B10,B10
           STDW    .D1T2   B17:B16,*A31      ; |128| 
           ADDU    .L2X    A4,B8,B7:B6       ; |130| 

   [ A0]   B       .S1     $C$L15            ; |248| 
||         SUBU    .L2     B16,B6,B5:B4      ; |130| 
||         ADD     .S2X    B7,A5,B6          ; |130| 

           ADD     .D2     B6,B9,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B6,B6         ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B10        ; |130| 

           ; BRANCHCC OCCURS {$C$L15}        ; |248| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A15(16),A5:A4   ; |135| 
           ADDKPC  .S2     $C$RL36,B3,3      ; |135| 
$C$RL36:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A12               ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           LDDW    .D2T1   *+SP(80),A7:A6    ; |135| 
           MV      .L2X    A12,B4            ; |114| 
           STDW    .D2T1   A5:A4,*B10        ; |135| 
           NOP             2

           STDW    .D1T1   A7:A6,*+A15(8)    ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B6           ; |117| 
           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B6,B5,B7:B6       ; |117| 

           EXT     .S2     B7,24,24,B5       ; |117| 
||         MVK     .S1     0x80,A3
||         SUB     .L2     B8,B4,B4          ; |117| 

           ADD     .L2     B4,B5,B7          ; |117| 

           STDW    .D1T2   B7:B6,*A10        ; |117| 
||         MV      .L2X    A3,B11            ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A14
           MVKH    .S1     input,A14
           LDW     .D1T1   *A14,A3           ; |259| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |259| 
||         CALL    .S1     acoshsp           ; |259| 

           LDW     .D1T1   *A3,A4            ; |259| 
           ADDKPC  .S2     $C$RL38,B3,3      ; |259| 
$C$RL38:   ; CALL OCCURS {acoshsp} {0}       ; |259| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 23
           ADD     .L2     4,B13,B4
           LDW     .D2T2   *B4,B4            ; |259| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |259| 

           STW     .D1T1   A4,*A3            ; |259| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S2     t_start,B10
||         LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         SUB     .L1X    B11,1,A0          ; |257| 
||         MV      .L2     B6,B17            ; |128| 
||         MVKL    .S1     t_stop,A11
||         SUB     .D2     B11,1,B11         ; |257| 

           MVKH    .S1     t_stop,A11
||         ADD     .L1     4,A12,A12         ; |257| 
||         MVKH    .S2     t_start,B10

           LDDW    .D2T2   *B10,B9:B8        ; |130| 
           ADDAD   .D1     A15,1,A3
           LDDW    .D1T1   *A3,A7:A6         ; |130| 
           STDW    .D1T2   B17:B16,*A11      ; |128| 
           MV      .L2X    A3,B12            ; |128| 
           ADDU    .L2X    A4,B8,B5:B4       ; |130| 

   [ A0]   B       .S1     $C$L16            ; |257| 
||         ADD     .S2X    B5,A5,B6          ; |130| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 

           ADD     .D2     B6,B9,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B17,B6,B6         ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B12        ; |130| 

           ; BRANCHCC OCCURS {$C$L16}        ; |257| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A15(8),A5:A4    ; |135| 
           ADDKPC  .S2     $C$RL39,B3,3      ; |135| 
$C$RL39:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 110
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A12               ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL40:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
           LDDW    .D2T1   *+SP(80),A7:A6    ; |135| 
           MV      .L1X    B12,A12           ; |135| 
           ZERO    .L2     B4                ; |115| 
           STDW    .D1T1   A5:A4,*A12        ; |135| 
           NOP             1

           STDW    .D1T1   A7:A6,*+A15(32)   ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B6           ; |116| 
           MVC     .S2     TSCH,B7           ; |116| 

           STDW    .D2T2   B7:B6,*B10        ; |116| 
||         MVC     .S2     TSCL,B4           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 
           SUBU    .L2     B4,B6,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B8,B7,B31         ; |117| 

           ADD     .L2     B31,B6,B5         ; |117| 

           MV      .L2X    A14,B9            ; |266| 
||         MV      .L1X    B13,A15           ; |117| 
||         STDW    .D1T2   B5:B4,*A10        ; |117| 

           CALLP   .S2     acoshsp_v,B3
||         LDW     .D1T2   *+A15(16),B4      ; |266| 
||         LDW     .D2T1   *B9,A4            ; |266| 
||         MVK     .S1     0x80,A6           ; |266| 

$C$RL41:   ; CALL OCCURS {acoshsp_v} {0}     ; |266| 
           MVC     .S2     TSCL,B8           ; |128| 
           MVC     .S2     TSCH,B4           ; |128| 

           LDDW    .D1T1   *A10,A5:A4        ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 
||         MVK     .S2     24,B10

           ADD     .L2X    A12,B10,B10

           MV      .L2     B4,B9             ; |128| 
||         LDDW    .D2T2   *B10,B5:B4        ; |130| 

           NOP             2
           ADDU    .L1X    A4,B6,A7:A6       ; |130| 

           ADD     .S1     A7,A5,A3          ; |130| 
||         SUBU    .L1X    B8,A6,A5:A4       ; |130| 

           ADDU    .L1X    B4,A4,A7:A6       ; |130| 

           ADD     .L2X    A3,B7,B4          ; |130| 
||         EXT     .S1     A5,24,24,A3       ; |130| 

           SUB     .L2     B9,B4,B7          ; |130| 
||         ADD     .S2X    A7,B5,B5          ; |130| 

           ADD     .L2X    B7,A3,B7          ; |130| 

           ADD     .L2     B5,B7,B5          ; |130| 
||         MV      .S2X    A6,B4             ; |130| 

           MV      .L2X    A11,B6            ; |128| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |130| 
||         STDW    .D2T2   B9:B8,*B6         ; |128| 

$C$RL42:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           ZERO    .L1     A12               ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL43:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           STDW    .D2T1   A5:A4,*B10        ; |130| 
||         LDW     .D1T2   *+A15(4),B4       ; |66| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 
||         MVK     .S1     0x80,A6           ; |66| 

$C$RL44:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0xa0b5ed8d,B6
           MVKL    .S2     0x3eb0c6f7,B7

           LDW     .D1T2   *+A15(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A10
||         MVKH    .S2     0xa0b5ed8d,B6

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A15,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A10
||         MVKH    .S2     0x3eb0c6f7,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A10(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL45:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6

           STW     .D1T1   A4,*+A10(8)       ; |67| 
||         MVKH    .S2     0x3eb0c6f7,B7

           LDW     .D1T2   *+A15(12),B4      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A15,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL46:   ; CALL OCCURS {isequal} {0}       ; |68| 
           LDW     .D2T2   *+SP(64),B4       ; |68| 
           MVKL    .S2     0x3eb0c6f7,B7
           MVKL    .S2     0xa0b5ed8d,B6
           MVKH    .S2     0x3eb0c6f7,B7

           STW     .D1T1   A4,*+A10(12)      ; |68| 
||         MVKH    .S2     0xa0b5ed8d,B6

           CALLP   .S2     isequal,B3
||         LDW     .D2T2   *B4,B4            ; |69| 
||         LDW     .D1T1   *A15,A4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL47:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           LDW     .D2T2   *+SP(68),B4       ; |69| 
           STW     .D1T1   A4,*+A10(16)      ; |69| 
           NOP             3
           LDW     .D2T2   *B4,B0            ; |72| 
           LDW     .D2T2   *+SP(72),B4
           NOP             3

   [!B0]   B       .S1     $C$L17            ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite

   [ B0]   LDW     .D2T2   *B4,B0            ; |72| 
   [ B1]   ADD     .L2     4,B4,B4
           NOP             3
           ; BRANCHCC OCCURS {$C$L17}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   MV      .L1     A12,A0            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           NOP             1
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L18            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |272| 
           MVK     .L1     0x1,A3            ; |72| 
   [ A0]   MVKL    .S1     all_pass,A4
   [ A0]   MVKH    .S1     all_pass,A4
           NOP             1
           ; BRANCHCC OCCURS {$C$L18}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |272| 
           MVKL    .S1     all_pass,A4
           MVKH    .S1     all_pass,A4
           MV      .L1     A12,A3
           NOP             1
;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A3,*A4            ; |72| 
||         MVK     .L1     0x2,A4            ; |272| 
||         ADDKPC  .S2     $C$RL48,B3,0      ; |272| 

$C$RL48:   ; CALL OCCURS {print_test_results} {0}  ; |272| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |273| 

$C$RL49:   ; CALL OCCURS {printf} {0}        ; |273| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |273| 

$C$RL50:   ; CALL OCCURS {printf} {0}        ; |273| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |280| 

$C$RL51:   ; CALL OCCURS {print_profile_results} {0}  ; |280| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |283| 

$C$RL52:   ; CALL OCCURS {print_memory_results} {0}  ; |283| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(112),B3     ; |284| 
           LDDW    .D2T1   *++SP,A13:A12     ; |284| 
           LDDW    .D2T1   *++SP,A15:A14     ; |284| 
           LDDW    .D2T2   *++SP,B11:B10     ; |284| 
           LDDW    .D2T2   *++SP,B13:B12     ; |284| 

           LDW     .D2T1   *++SP(8),A10      ; |284| 
||         RET     .S2     B3                ; |284| 

           LDW     .D2T1   *++SP(8),A11      ; |284| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |284| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"acoshSP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	acoshf
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	acoshsp_c
	.global	acoshsp
	.global	acoshsp_v
	.global	ti_math_logtable
	.global	t_start
	.global	t_stop
	.global	t_offset
	.global	cycle_counts
	.global	fcn_pass
	.global	all_pass
	.global	a_ext
	.global	a_sc
	.global	output
	.global	input
	.global	__c6xabi_fltllif
	.global	__c6xabi_fixdlli

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "TI", Tag_File, 1, Tag_Long_Precision_Bits(2)
	.battr "TI", Tag_File, 1, Tag_Bitfield_layout(2)
	.battr "TI", Tag_File, 1, Tag_ABI_enum_size(3)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_wchar_t(1)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_array_object_alignment(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_array_object_align_expected(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_PIC(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_PID(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_DSBT(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_stack_align_needed(0)
	.battr "c6xabi", Tag_File, 1, Tag_ABI_stack_align_preserved(0)
	.battr "TI", Tag_File, 1, Tag_Tramps_Use_SOC(1)
