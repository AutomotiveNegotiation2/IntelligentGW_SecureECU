;******************************************************************************
;* TMS320C6x C/C++ Codegen                                          PC v7.4.2 *
;* Date/Time created: Tue May 17 03:32:34 2016                                *
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
	.elfsym	a,SYM_SIZE(1608)
a:
	.word	0bf768183h,055e8f352h		; a[0] @ 0
	.word	03fb83988h,00bfd8f37h		; a[1] @ 64
	.word	0bf90e115h,003475d37h		; a[2] @ 128
	.word	03f96816fh,0564f1714h		; a[3] @ 192
	.word	0bf9c21c8h,0fd8a59e1h		; a[4] @ 256
	.word	03fa0e111h,0a84909dfh		; a[5] @ 320
	.word	0bfa3b13eh,0d1cce6ceh		; a[6] @ 384
	.word	03fa6816bh,0a56a8834h		; a[7] @ 448
	.word	0bfa95198h,0ceee6523h		; a[8] @ 512
	.word	03fac21c5h,0f8724212h		; a[9] @ 576
	.word	0bfaef1f2h,0cc0fe378h		; a[10] @ 640
	.word	03fb0e10fh,0fac9e033h		; a[11] @ 704
	.word	0bfb24926h,08f8bceabh		; a[12] @ 768
	.word	03fb3b13ch,0f95a9f5eh		; a[13] @ 832
	.word	0bfb51953h,08e1c8dd5h		; a[14] @ 896
	.word	03fb68169h,0f7eb5e88h		; a[15] @ 960
	.word	0bfb7e980h,08cad4d00h		; a[16] @ 1024
	.word	03fb95197h,0216f3b77h		; a[17] @ 1088
	.word	0bfbab9adh,03557d0a1h		; a[18] @ 1152
	.word	03fbc21c3h,09f26a154h		; a[19] @ 1216
	.word	0bfbd89dah,008f57208h		; a[20] @ 1280
	.word	03fbef1f0h,072c442bbh		; a[21] @ 1344
	.word	0bfc02d04h,045091e8dh		; a[22] @ 1408
	.word	03fc0e10fh,079f086e6h		; a[23] @ 1472
	.word	0bfc1951ah,0aed7ef40h		; a[24] @ 1536
	.word	03fc24925h,0e3bf5799h		; a[25] @ 1600
	.word	0bfc2fd31h,018a6bff3h		; a[26] @ 1664
	.word	03fc3b13ch,04d8e284ch		; a[27] @ 1728
	.word	0bfc46547h,0827590a6h		; a[28] @ 1792
	.word	03fc51952h,0b75cf8ffh		; a[29] @ 1856
	.word	0bfc5cd5dh,0ec446159h		; a[30] @ 1920
	.word	03fc68169h,0212bc9b2h		; a[31] @ 1984
	.word	0bfc73574h,05613320ch		; a[32] @ 2048
	.word	03fc7e97fh,08afa9a65h		; a[33] @ 2112
	.word	0bfc89d8ah,0bfe202bfh		; a[34] @ 2176
	.word	03fc95195h,0f4c96b18h		; a[35] @ 2240
	.word	0bfca05a1h,029b0d372h		; a[36] @ 2304
	.word	03fcab9ach,05e983bcch		; a[37] @ 2368
	.word	0bfcb6db8h,06a3f38fbh		; a[38] @ 2432
	.word	03fcc21c3h,09f26a154h		; a[39] @ 2496
	.word	0bfccd5ceh,0d40e09aeh		; a[40] @ 2560
	.word	03fcd89dah,008f57208h		; a[41] @ 2624
	.word	0bfce3de5h,03ddcda61h		; a[42] @ 2688
	.word	03fcef1f0h,072c442bbh		; a[43] @ 2752
	.word	0bfcfa5fbh,0a7abab14h		; a[44] @ 2816
	.word	03fd02d03h,06e4989b7h		; a[45] @ 2880
	.word	0bfd08709h,008bd3de4h		; a[46] @ 2944
	.word	03fd0e10eh,0a330f210h		; a[47] @ 3008
	.word	0bfd13b14h,03da4a63dh		; a[48] @ 3072
	.word	03fd19519h,0d8185a6ah		; a[49] @ 3136
	.word	0bfd1ef1fh,0728c0e97h		; a[50] @ 3200
	.word	03fd24925h,00cffc2c3h		; a[51] @ 3264
	.word	0bfd2a32bh,012d3415bh		; a[52] @ 3328
	.word	03fd2fd30h,0ad46f588h		; a[53] @ 3392
	.word	0bfd35736h,047baa9b5h		; a[54] @ 3456
	.word	03fd3b13bh,0e22e5de1h		; a[55] @ 3520
	.word	0bfd40b41h,07ca2120eh		; a[56] @ 3584
	.word	03fd46547h,01715c63bh		; a[57] @ 3648
	.word	0bfd4bf4ch,0b1897a68h		; a[58] @ 3712
	.word	03fd51952h,04bfd2e94h		; a[59] @ 3776
	.word	0bfd57357h,0e670e2c1h		; a[60] @ 3840
	.word	03fd5cd5dh,080e496eeh		; a[61] @ 3904
	.word	0bfd62763h,01b584b1bh		; a[62] @ 3968
	.word	03fd68168h,0b5cbff47h		; a[63] @ 4032
	.word	0bfd6db6eh,0503fb374h		; a[64] @ 4096
	.word	03fd73573h,0eab367a1h		; a[65] @ 4160
	.word	0bfd78f79h,0f086e639h		; a[66] @ 4224
	.word	03fd7e97fh,08afa9a65h		; a[67] @ 4288
	.word	0bfd84385h,0256e4e92h		; a[68] @ 4352
	.word	03fd89d8ah,0bfe202bfh		; a[69] @ 4416
	.word	0bfd8f790h,05a55b6ech		; a[70] @ 4480
	.word	03fd95195h,0f4c96b18h		; a[71] @ 4544
	.word	0bfd9ab9bh,08f3d1f45h		; a[72] @ 4608
	.word	03fda05a1h,029b0d372h		; a[73] @ 4672
	.word	0bfda5fa6h,0c424879fh		; a[74] @ 4736
	.word	03fdab9ach,05e983bcch		; a[75] @ 4800
	.word	0bfdb13b1h,0f90beff8h		; a[76] @ 4864
	.word	03fdb6db7h,0937fa425h		; a[77] @ 4928
	.word	0bfdbc7bdh,02df35852h		; a[78] @ 4992
	.word	03fdc21c2h,0c8670c7fh		; a[79] @ 5056
	.word	0bfdc7bc8h,062dac0abh		; a[80] @ 5120
	.word	03fdcd5cdh,0fd4e74d8h		; a[81] @ 5184
	.word	0bfdd2fd3h,097c22905h		; a[82] @ 5248
	.word	03fdd89d9h,03235dd32h		; a[83] @ 5312
	.word	0bfdde3deh,0cca9915eh		; a[84] @ 5376
	.word	03fde3de4h,0d27d0ff6h		; a[85] @ 5440
	.word	0bfde97eah,06cf0c423h		; a[86] @ 5504
	.word	03fdef1f0h,007647850h		; a[87] @ 5568
	.word	0bfdf4bf5h,0a1d82c7ch		; a[88] @ 5632
	.word	03fdfa5fbh,03c4be0a9h		; a[89] @ 5696
	.word	0bfe00000h,000000000h		; a[90] @ 5760
	.word	03fe59f22h,0a5467606h		; a[91] @ 5824
	.word	0bfeb3e45h,04a8cec0ch		; a[92] @ 5888
	.word	03ff06eb3h,0dd11be6eh		; a[93] @ 5952
	.word	0bff33e45h,0803cd142h		; a[94] @ 6016
	.word	03ff60dd6h,016f86a0ah		; a[95] @ 6080
	.word	0bff8dd67h,0ba237cddh		; a[96] @ 6144
	.word	03ffbacf9h,05d4e8fb0h		; a[97] @ 6208
	.word	0bffe7c89h,0f40a2878h		; a[98] @ 6272
	.word	04000a60dh,0cb9a9da6h		; a[99] @ 6336
	.word	0c0020dd6h,09d30270fh		; a[100] @ 6400
	.word	04003759eh,0e88df373h		; a[101] @ 6464
	.word	0c004dd67h,0ba237cddh		; a[102] @ 6528
	.word	040064530h,08bb90646h		; a[103] @ 6592
	.word	0c007acf9h,05d4e8fb0h		; a[104] @ 6656
	.word	0400914c1h,0a8ac5c14h		; a[105] @ 6720
	.word	0c00a7c8ah,07a41e57eh		; a[106] @ 6784
	.word	0400be452h,0c59fb1e2h		; a[107] @ 6848
	.word	0c00d4c1bh,097353b4bh		; a[108] @ 6912
	.word	0400eb3e4h,068cac4b5h		; a[109] @ 6976
	.word	0c0100dd6h,09d30270fh		; a[110] @ 7040
	.word	04010c1bah,0c2df0d41h		; a[111] @ 7104
	.word	0c011759fh,02ba9d1f6h		; a[112] @ 7168
	.word	040122983h,0947496abh		; a[113] @ 7232
	.word	0c012dd67h,0ba237cddh		; a[114] @ 7296
	.word	04013914ch,022ee4192h		; a[115] @ 7360
	.word	0c0144530h,0489d27c4h		; a[116] @ 7424
	.word	04014f914h,0b167ec78h		; a[117] @ 7488
	.word	0c015acf9h,01a32b12dh		; a[118] @ 7552
	.word	0401660ddh,03fe1975fh		; a[119] @ 7616
	.word	0c01714c1h,0a8ac5c14h		; a[120] @ 7680
	.word	04017c8a6h,0117720c9h		; a[121] @ 7744
	.word	0c0187c8ah,07a41e57eh		; a[122] @ 7808
	.word	04019306eh,09ff0cbb0h		; a[123] @ 7872
	.word	0c019e453h,008bb9064h		; a[124] @ 7936
	.word	0401a9837h,071865519h		; a[125] @ 8000
	.word	0c01b4c1bh,097353b4bh		; a[126] @ 8064
	.word	0401c0000h,000000000h		; a[127] @ 8128
	.word	0c01cb3e4h,068cac4b5h		; a[128] @ 8192
	.word	0401d67c8h,08e79aae7h		; a[129] @ 8256
	.word	0c01e1bach,0f7446f9ch		; a[130] @ 8320
	.word	0401ecf91h,0600f3450h		; a[131] @ 8384
	.word	0c01f8375h,085be1a82h		; a[132] @ 8448
	.word	040201bach,0f7446f9ch		; a[133] @ 8512
	.word	0c020759fh,02ba9d1f6h		; a[134] @ 8576
	.word	04020cf91h,03e81450fh		; a[135] @ 8640
	.word	0c0212983h,072e6a769h		; a[136] @ 8704
	.word	040218375h,0a74c09c4h		; a[137] @ 8768
	.word	0c021dd67h,0ba237cddh		; a[138] @ 8832
	.word	04022375ah,01016ce79h		; a[139] @ 8896
	.word	0c022914ch,022ee4192h		; a[140] @ 8960
	.word	04022eb3eh,035c5b4abh		; a[141] @ 9024
	.word	0c0234530h,06a2b1705h		; a[142] @ 9088
	.word	040239f22h,09e90795fh		; a[143] @ 9152
	.word	0c023f914h,0b167ec78h		; a[144] @ 9216
	.word	040245306h,0a2b17050h		; a[145] @ 9280
	.word	0c024acf9h,05d4e8fb0h		; a[146] @ 9344
	.word	0402506eah,0c8605682h		; a[147] @ 9408
	.word	0c02560ddh,082fd75e2h		; a[148] @ 9472
	.word	04025bad0h,03d9a9542h		; a[149] @ 9536
	.word	0c02614c1h,0a8ac5c14h		; a[150] @ 9600
	.word	040266eb4h,063497b74h		; a[151] @ 9664
	.word	0c026c8a5h,0ce5b4246h		; a[152] @ 9728
	.word	040272298h,088f861a6h		; a[153] @ 9792
	.word	0c0277c89h,0f40a2878h		; a[154] @ 9856
	.word	04027d67ch,0aea747d8h		; a[155] @ 9920
	.word	0c028306eh,019b90eaah		; a[156] @ 9984
	.word	040288a60h,0d4562e0ah		; a[157] @ 10048
	.word	0c028e453h,08ef34d6ah		; a[158] @ 10112
	.word	040293e44h,0fa05143ch		; a[159] @ 10176
	.word	0c0299837h,0b4a2339ch		; a[160] @ 10240
	.word	04029f229h,01fb3fa6eh		; a[161] @ 10304
	.word	0c02a4c1bh,0da5119ceh		; a[162] @ 10368
	.word	0402aa60dh,04562e0a0h		; a[163] @ 10432
	.word	0c02b0000h,000000000h		; a[164] @ 10496
	.word	0402b59f2h,0ba9d1f60h		; a[165] @ 10560
	.word	0c02bb3e4h,025aee632h		; a[166] @ 10624
	.word	0402c0dd6h,0e04c0592h		; a[167] @ 10688
	.word	0c02c67c8h,04b5dcc64h		; a[168] @ 10752
	.word	0402cc1bbh,005faebc4h		; a[169] @ 10816
	.word	0c02d1bach,0710cb296h		; a[170] @ 10880
	.word	0402d759fh,02ba9d1f6h		; a[171] @ 10944
	.word	0c02dcf91h,0e646f156h		; a[172] @ 11008
	.word	0402e2983h,05158b828h		; a[173] @ 11072
	.word	0c02e8376h,00bf5d788h		; a[174] @ 11136
	.word	0402edd67h,077079e5ah		; a[175] @ 11200
	.word	0c02f375ah,031a4bdbah		; a[176] @ 11264
	.word	0402f914bh,09cb6848ch		; a[177] @ 11328
	.word	0c02feb3eh,05753a3ech		; a[178] @ 11392
	.word	040302298h,088f861a6h		; a[179] @ 11456
	.word	0c0304f91h,03e81450fh		; a[180] @ 11520
	.word	040307c8ah,09bcfd4bfh		; a[181] @ 11584
	.word	0c030a983h,05158b828h		; a[182] @ 11648
	.word	04030d67ch,0aea747d8h		; a[183] @ 11712
	.word	0c0310375h,064302b41h		; a[184] @ 11776
	.word	04031306eh,0c17ebaf1h		; a[185] @ 11840
	.word	0c0315d67h,077079e5ah		; a[186] @ 11904
	.word	040318a60h,0d4562e0ah		; a[187] @ 11968
	.word	0c031b75ah,031a4bdbah		; a[188] @ 12032
	.word	04031e452h,0e72da123h		; a[189] @ 12096
	.word	0c032114ch,0447c30d3h		; a[190] @ 12160
	.word	040323e44h,0fa05143ch		; a[191] @ 12224
	.word	0c0326b3eh,05753a3ech		; a[192] @ 12288
	.word	040329837h,00cdc8755h		; a[193] @ 12352
	.word	0c032c530h,06a2b1705h		; a[194] @ 12416
	.word	04032f229h,0c779a6b5h		; a[195] @ 12480
	.word	0c0331f22h,07d028a1eh		; a[196] @ 12544
	.word	040334c1bh,0da5119ceh		; a[197] @ 12608
	.word	0c0337914h,08fd9fd37h		; a[198] @ 12672
	.word	04033a60dh,0ed288ce7h		; a[199] @ 12736
	.word	0c033d306h,0a2b17050h		; a[200] @ 12800

;	C:\MATHLIB_Tools\CCSV5_5_0\ccsv5\tools\compiler\c6000_7.4.2\bin\opt6x.exe C:\\Users\\gtbldadm\\AppData\\Local\\Temp\\028884 C:\\Users\\gtbldadm\\AppData\\Local\\Temp\\028886 
;**	Parameter deleted: req_flags == 1;
;**	Parameter deleted: tol == 1e-10;
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
||         MVKL    .S2     0xd9d7bdbb,B6

           STDW    .D2T1   A13:A12,*SP--     ; |63| 
||         MVKL    .S1     output,A11
||         MVKL    .S2     0x3ddb7cdf,B7

           STW     .D2T1   A10,*SP--(8)      ; |63| 
||         MVKH    .S1     output,A11
||         MVKH    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A11(4),B4       ; |66| 
||         MV      .L1     A4,A6             ; |63| 
||         MVKH    .S2     0x3ddb7cdf,B7
||         MVK     .S1     0x1,A8            ; |66| 

           MV      .L1X    B3,A13            ; |63| 
||         CALLP   .S2     isequal,B3
||         MV      .S1     A4,A10            ; |63| 
||         LDW     .D1T1   *A11,A4           ; |66| 

$C$RL0:    ; CALL OCCURS {isequal} {0}       ; |66| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           LDW     .D1T2   *+A11(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A12
||         MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1     A4,A3             ; |66| 
||         LDW     .D1T1   *A11,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A12
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(4)       ; |66| 
||         MV      .L1     A10,A6            ; |67| 
||         MVK     .S1     0x1,A8            ; |67| 

$C$RL1:    ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           LDW     .D1T2   *+A11(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A3             ; |67| 
||         LDW     .D1T1   *A11,A4           ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A3,*+A12(8)       ; |67| 
||         MV      .L1     A10,A6            ; |68| 
||         MVK     .S1     0x1,A8            ; |68| 

$C$RL2:    ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           STW     .D1T1   A4,*+A12(12)      ; |68| 
||         MVKH    .S2     0x3ddb7cdf,B7

           MV      .L1     A11,A3            ; |66| 
||         LDW     .D1T2   *+A11(16),B4      ; |69| 
||         MVKH    .S2     0xd9d7bdbb,B6

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
;*   Local Frame Size  : 8 Args + 0 Auto + 56 Save = 64 byte                  *
;******************************************************************************
main:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           STW     .D2T1   A11,*SP--(8)      ; |124| 
           STW     .D2T1   A10,*SP--(8)      ; |124| 
           STDW    .D2T2   B13:B12,*SP--     ; |124| 
           STDW    .D2T2   B11:B10,*SP--     ; |124| 
           STDW    .D2T1   A15:A14,*SP--     ; |124| 

           STDW    .D2T1   A13:A12,*SP--     ; |124| 
||         MVKL    .S1     $C$SL1+0,A4

           STW     .D2T2   B3,*SP--(16)      ; |124| 
||         CALLP   .S2     driver_init,B3
||         MVKH    .S1     $C$SL1+0,A4

$C$RL4:    ; CALL OCCURS {driver_init} {0}   ; |132| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     a,A12
||         MVKL    .S2     output,B10

           MVKH    .S1     a,A12
||         MVKH    .S2     output,B10

           MV      .L1     A12,A13
||         CALL    .S1     tanh              ; |141| 
||         LDW     .D2T1   *B10,A11

           LDDW    .D1T1   *A13++,A5:A4      ; |141| 
           MVK     .S2     0xc9,B4
           NOP             1
           MV      .L1X    B4,A10
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L3:    
;          EXCLUSIVE CPU CYCLES: 1
           ADDKPC  .S2     $C$RL5,B3,0       ; |141| 
$C$RL5:    ; CALL OCCURS {tanh} {0}          ; |141| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L1     A10,1,A0          ; |140| 
||         STDW    .D1T1   A5:A4,*A11++      ; |141| 
||         SUB     .S1     A10,1,A10         ; |140| 

   [ A0]   B       .S1     $C$L3             ; |140| 
|| [ A0]   LDDW    .D1T1   *A13++,A5:A4      ; |141| 
|| [!A0]   ADD     .L2     4,B10,B11

   [ A0]   CALL    .S1     tanh              ; |141| 
   [!A0]   MV      .L1     A12,A10
   [!A0]   ZERO    .L2     B10
   [!A0]   MVK     .S1     0xc9,A3
   [!A0]   MV      .L1     A3,A11
           ; BRANCHCC OCCURS {$C$L3}         ; |140| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     tanhdp            ; |144| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L4:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A12++,A5:A4      ; |144| 
           ADDKPC  .S2     $C$RL6,B3,3       ; |144| 
$C$RL6:    ; CALL OCCURS {tanhdp} {0}        ; |144| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |144| 
||         SUB     .L1     A11,1,A0          ; |143| 
||         SUB     .S1     A11,1,A11         ; |143| 

   [ A0]   BNOP    .S2     $C$L4,2           ; |143| 
|| [!A0]   MVK     .S1     0xc9,A3
|| [!A0]   ADD     .L2     4,B11,B11
|| [!A0]   MV      .L1     A10,A11

   [!A0]   MV      .L1     A3,A12

           ADD     .L2     B10,B4,B4         ; |144| 
||         ADD     .S2     8,B10,B10         ; |143| 

   [ A0]   CALL    .S1     tanhdp            ; |144| 
|| [!A0]   ZERO    .L2     B10
||         STDW    .D2T1   A5:A4,*B4         ; |144| 

           ; BRANCHCC OCCURS {$C$L4}         ; |143| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           CALL    .S1     tanhdp_c          ; |147| 
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A11++,A5:A4      ; |147| 
           ADDKPC  .S2     $C$RL7,B3,3       ; |147| 
$C$RL7:    ; CALL OCCURS {tanhdp_c} {0}      ; |147| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T2   *B11,B4           ; |147| 
||         SUB     .L1     A12,1,A0          ; |146| 
||         SUB     .S1     A12,1,A12         ; |146| 

   [ A0]   BNOP    .S1     $C$L5,3           ; |146| 
|| [!A0]   ADD     .L2     4,B11,B16

           ADD     .L2     B10,B4,B4         ; |147| 
||         ADD     .S2     8,B10,B10         ; |146| 

   [ A0]   CALL    .S1     tanhdp_c          ; |147| 
||         STDW    .D2T1   A5:A4,*B4         ; |147| 

           ; BRANCHCC OCCURS {$C$L5}         ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

           MVKL    .S1     0x3fd33333,A17
||         SUB     .L1     A10,8,A3
||         ZERO    .L2     B5:B4             ; |203| 
||         MVK     .S2     1022,B30          ; |69| 
||         LDW     .D2T1   *B16,A18
||         ZERO    .D1     A31

           MVKL    .S1     0x33333333,A16
||         LDDW    .D1T1   *++A3,A9:A8       ; |200| 
||         MVK     .S2     0xc9,B1
||         ZERO    .L2     B31
||         ZERO    .D2     B28

           MVKH    .S1     0x3fd33333,A17
||         ZERO    .L2     B20               ; |69| 

           MVKH    .S1     0x33333333,A16
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 14
           NOP             4

           ABSDP   .S1     A9:A8,A7:A6       ; |200| 
||         CMPLTDP .S2X    A9:A8,B5:B4,B0    ; |203| 

           ZERO    .L1     A9

           CMPLTDP .S1     A7:A6,A17:A16,A0  ; |206| 
||         FMPYDP  .M1     A7:A6,A7:A6,A21:A20 ; |124| 

   [!B0]   ZERO    .L1     A17
|| [ B0]   ZERO    .D1     A17

   [!A0]   ZERO    .L1     A8                ; |209| 
|| [ A0]   B       .S2     $C$L7             ; |206| 
||         MVKH    .S1     0x40330000,A9
||         MV      .D1     A0,A1             ; guard predicate rewrite

           MV      .L1     A0,A2             ; branch predicate copy
||         CMPGTDP .S1     A7:A6,A9:A8,A0    ; |209| 
|| [ B0]   ZERO    .D1     A16               ; |203| 

           FMPYDP  .M1     A21:A20,A21:A20,A23:A22 ; |124| 
|| [!B0]   ZERO    .L1     A16               ; |203| 

   [ A0]   ZERO    .L1     A5
|| [ A0]   MV      .D1     A8,A4             ; |214| 
|| [!B0]   SET     .S1     A17,0x14,0x1d,A17

   [ A0]   SET     .S1     A5,0x14,0x1d,A5
|| [ A1]   ZERO    .L1     A0                ; |214| nullify predicate

   [ A0]   B       .S2     $C$L9             ; |214| 
|| [ B0]   MVKH    .S1     0xbff00000,A17

           ; BRANCHCC OCCURS {$C$L7}         ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

   [!A0]   ZERO    .L1     A5
|| [!A0]   MV      .S1     A8,A4             ; |159| 
|| [!A0]   MVKL    .S2     0x3ff71547,B5
|| [ A0]   SUB     .L2     B1,1,B1           ; |149| 

   [!A0]   MVKH    .S1     0xc0000000,A5
|| [!A0]   MVKL    .S2     0x652b82fe,B4

   [!A0]   FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |159| 
   [!A0]   MVKH    .S2     0x3ff71547,B5
   [!A0]   MVKH    .S2     0x652b82fe,B4
           ; BRANCHCC OCCURS {$C$L9}         ; |214| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 148
           ZERO    .L2     B8                ; |159| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |159| 
           ZERO    .L2     B9
           MVKL    .S2     0x5c610ca8,B6
           MV      .L1     A8,A6             ; |159| 
           DPINT   .L2     B5:B4,B17         ; |159| 
           MVKL    .S1     0x3fe63000,A7
           MVKL    .S2     0xbf2bd010,B7
           MVKH    .S1     0x3fe63000,A7
           INTDP   .L2     B17,B5:B4         ; |159| 
           MVKL    .S1     0x6f58dc1c,A8
           MVKH    .S2     0x5c610ca8,B6
           MVKL    .S1     0x3ef152a4,A9
           MVKH    .S2     0xbf2bd010,B7
           MVKH    .S1     0x6f58dc1c,A8
           FMPYDP  .M1X    A7:A6,B5:B4,A7:A6 ; |159| 
           MVKH    .S1     0x3ef152a4,A9
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |159| 
           MVKL    .S1     0x6fb3f6e0,A20
           FSUBDP  .L1     A5:A4,A7:A6,A5:A4 ; |159| 
           MVKL    .S1     0x3f7c70e4,A21
           MVKH    .S1     0x6fb3f6e0,A20
           FSUBDP  .L1X    A5:A4,B5:B4,A7:A6 ; |159| 
           MVKH    .S1     0x3f7c70e4,A21
           MVKL    .S1     0x714251b3,A22
           FMPYDP  .M1     A7:A6,A7:A6,A5:A4 ; |159| 
           MVKL    .S1     0x3fac718e,A23
           MVKL    .S2     0x6fde3809,B4
           MVKL    .S2     0x3f403f99,B5
           FMPYDP  .M1     A9:A8,A5:A4,A9:A8 ; |159| 
           MVKH    .S2     0x6fde3809,B4
           MVKH    .S2     0x3f403f99,B5
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |160| 
           FADDDP  .L1     A21:A20,A9:A8,A9:A8 ; |159| 
           MVKH    .S1     0x714251b3,A22
           MVKH    .S1     0x3fac718e,A23
           FMPYDP  .M1     A5:A4,A9:A8,A9:A8 ; |159| 
           FADDDP  .L2X    A23:A22,B5:B4,B5:B4 ; |160| 
           ZERO    .L2     B18               ; |160| 
           MVKH    .S2     0x3fd00000,B9
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |160| 
           FADDDP  .L2X    B9:B8,A9:A8,B5:B4 ; |159| 
           ZERO    .L2     B19
           SET     .S2     B19,0x15,0x1d,B19
           FMPYDP  .M2X    A7:A6,B5:B4,B9:B8 ; |159| 
           FADDDP  .L2     B19:B18,B7:B6,B5:B4 ; |160| 
           ZERO    .L2     B21
           SET     .S2     B21,0x1e,0x1e,B21
           FSUBDP  .L2     B5:B4,B9:B8,B7:B6 ; |160| 
           ZERO    .L1     A4                ; |69| 
           MV      .L1X    B21,A5            ; |69| 
           RCPDP   .S2     B7:B6,B5:B4       ; |69| 
           ZERO    .L1     A8                ; |69| 
           FMPYDP  .M2     B7:B6,B5:B4,B19:B18 ; |69| 
           MV      .L1X    B21,A9            ; |69| 
           ADD     .L2     B30,B17,B29       ; |69| 
           NOP             1
           FSUBDP  .L2     B21:B20,B19:B18,B19:B18 ; |69| 
           NOP             2
           FMPYDP  .M2     B5:B4,B19:B18,B5:B4 ; |69| 
           NOP             3
           FMPYDP  .M2     B7:B6,B5:B4,B19:B18 ; |69| 
           NOP             4
           FSUBDP  .L1X    A5:A4,B19:B18,A5:A4 ; |69| 
           NOP             2
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |69| 
           ZERO    .L2     B5:B4             ; |69| 
           CMPEQDP .S2     B9:B8,B5:B4,B0    ; |69| 
           MV      .L2     B20,B4            ; |69| 
           FMPYDP  .M1X    B7:B6,A5:A4,A7:A6 ; |69| 
           SET     .S2     B31,0x15,0x1d,B5
           NOP             2
           FSUBDP  .L1     A9:A8,A7:A6,A7:A6 ; |69| 
           NOP             2
           FMPYDP  .M1     A5:A4,A7:A6,A5:A4 ; |69| 
           NOP             3
   [!B0]   FMPYDP  .M1X    B9:B8,A5:A4,A5:A4 ; |69| 
   [ B0]   ZERO    .L1     A5:A4             ; |69| 
           NOP             2

           MV      .L2     B20,B4            ; |69| 
||         FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |69| 

           SHL     .S2     B29,20,B5         ; |69| 
           NOP             1
           FMPYDP  .M1X    B5:B4,A5:A4,A7:A6 ; |69| 
           MV      .L1     A8,A4             ; |69| 
           ZERO    .L1     A5
           MVKH    .S1     0x40100000,A5
           FMPYDP  .M1     A5:A4,A7:A6,A7:A6 ; |69| 
           SET     .S1     A31,0x14,0x1d,A5
           MV      .L2     B21,B5            ; |212| 
           NOP             1
           FADDDP  .L1     A5:A4,A7:A6,A5:A4 ; |69| 
           NOP             2
           RCPDP   .S1     A5:A4,A7:A6       ; |212| 
           NOP             1
           FMPYDP  .M1     A5:A4,A7:A6,A9:A8 ; |212| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |212| 
           NOP             2
           FMPYDP  .M2X    A7:A6,B5:B4,B5:B4 ; |212| 
           MV      .L1X    B21,A7            ; |212| 
           MV      .L1X    B20,A6            ; |212| 
           NOP             1
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |212| 
           NOP             4
           FSUBDP  .L1X    A7:A6,B7:B6,A7:A6 ; |212| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A7:A6,B5:B4 ; |212| 
           NOP             3
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |212| 
           MV      .L1X    B21,A5            ; |212| 
           MV      .L1X    B20,A4            ; |212| 
           NOP             2
           FSUBDP  .L1X    A5:A4,B7:B6,A5:A4 ; |212| 
           NOP             2
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |212| 
           MV      .L2     B20,B4            ; |212| 
           BNOP    .S1     $C$L8,1           ; |213| 
           FADDDP  .L1     A5:A4,A5:A4,A5:A4 ; |212| 
           SET     .S2     B28,0x14,0x1d,B5
           NOP             1
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |212| 
           ; BRANCH OCCURS {$C$L8}           ; |213| 
;** --------------------------------------------------------------------------*
$C$L7:    
;          EXCLUSIVE CPU CYCLES: 32

           MVKL    .S2     0x3f9666af,B5
||         FMPYDP  .M1     A23:A22,A21:A20,A9:A8 ; |124| 
||         MVKL    .S1     0x903de2ef,A26

           MVKL    .S2     0x84e8ae0f,B4
||         MVKL    .S1     0x3f6e11ce,A27

           MVKH    .S2     0x3f9666af,B5
||         MVKH    .S1     0x903de2ef,A26

           MVKH    .S2     0x84e8ae0f,B4
||         MVKH    .S1     0x3f6e11ce,A27

           FMPYDP  .M2X    B5:B4,A21:A20,B5:B4 ; |124| 
||         MVKL    .S2     0x53b8707d,B6
||         MVKL    .S1     0x3f7f105d,A4

           MVKL    .S2     0xbfd55555,B7
||         MVKL    .S1     0xbfaba1e4,A5

           MVKH    .S2     0x53b8707d,B6
||         MVKH    .S1     0x3f7f105d,A4

           MVKH    .S2     0xbfd55555,B7
||         MVKH    .S1     0xbfaba1e4,A5

           MVKL    .S2     0xbf822997,B9
||         FMPYDP  .M2X    B7:B6,A21:A20,B7:B6 ; |124| 
||         FMPYDP  .M1     A27:A26,A9:A8,A21:A20 ; |124| 
||         MVKL    .S1     0x3fc11111,A25

           MVKL    .S2     0xe912d40f,B8
||         MVKL    .S1     0x49fb127b,A24
||         FADDDP  .L2X    A5:A4,B5:B4,B5:B4 ; |124| 

           MVKH    .S2     0xbf822997,B9
||         MVKH    .S1     0x3fc11111,A25

           MVKH    .S2     0xe912d40f,B8
           FMPYDP  .M2X    B9:B8,A23:A22,B9:B8 ; |124| 
           MVKH    .S1     0x49fb127b,A24
           FMPYDP  .M1     A25:A24,A23:A22,A5:A4 ; |124| 
           NOP             1
           FADDDP  .L2X    A21:A20,B9:B8,B9:B8 ; |124| 
           FMPYDP  .M1X    A9:A8,B5:B4,A21:A20 ; |124| 
           FADDDP  .L1X    B7:B6,A5:A4,A5:A4 ; |124| 
           FMPYDP  .M2X    A9:A8,B9:B8,B5:B4 ; |124| 
           NOP             1
           FADDDP  .L1     A5:A4,A21:A20,A5:A4 ; |124| 
           NOP             2
           FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |124| 
           NOP             2
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |124| 
           NOP             3
           FADDDP  .L1     A7:A6,A5:A4,A5:A4 ; |124| 
;** --------------------------------------------------------------------------*
$C$L8:    
;          EXCLUSIVE CPU CYCLES: 2
           SUB     .L2     B1,1,B1           ; |149| 
           NOP             1
;** --------------------------------------------------------------------------*
$C$L9:    
;          EXCLUSIVE CPU CYCLES: 6

           FMPYDP  .M1     A17:A16,A5:A4,A7:A6 ; |150| 
|| [ B1]   ZERO    .L2     B5:B4             ; |203| 
|| [ B1]   B       .S2     $C$L6             ; |149| 
|| [ B1]   MVKL    .S1     0x33333333,A16
|| [!B1]   ADD     .D2     4,B16,B11

   [ B1]   MVKL    .S1     0x3fd33333,A17
   [ B1]   MVKH    .S1     0x33333333,A16
   [ B1]   MVKH    .S1     0x3fd33333,A17

           STDW    .D1T1   A7:A6,*A18++      ; |150| 
|| [!B1]   CALL    .S1     tanhdp_v          ; |152| 

   [ B1]   LDDW    .D1T1   *++A3,A9:A8       ; |200| 
|| [!B1]   LDW     .D2T2   *B11,B4           ; |152| 

           ; BRANCHCC OCCURS {$C$L6}         ; |149| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVK     .S1     0xc9,A6           ; |152| 
           ADDKPC  .S2     $C$RL8,B3,1       ; |152| 
           MV      .L1     A10,A4            ; |152| 
$C$RL8:    ; CALL OCCURS {tanhdp_v} {0}      ; |152| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0xc9,A4           ; |157| 

$C$RL9:    ; CALL OCCURS {allequal} {0}      ; |157| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x1,A4            ; |158| 

$C$RL10:   ; CALL OCCURS {print_test_results} {0}  ; |158| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           MVKL    .S2     a_sc,B4
           MVKH    .S2     a_sc,B4
           MVK     .L1     0xffffffff,A17    ; |172| 

           MV      .L1X    B4,A10            ; |165| 
||         MV      .S1     A17,A16           ; |172| 

           STDW    .D1T1   A17:A16,*+A10(56) ; |172| 
||         ZERO    .S2     B9
||         ZERO    .L2     B7:B6             ; |165| 

           STDW    .D1T2   B7:B6,*A10        ; |165| 
||         MVKH    .S2     0xbff00000,B9
||         ZERO    .L1     A7
||         ZERO    .L2     B8                ; |170| 

           STDW    .D1T2   B9:B8,*+A10(40)   ; |170| 
||         SET     .S1     A7,0x14,0x1d,A7
||         ZERO    .L2     B17
||         ZERO    .L1     A6                ; |170| 

           STDW    .D1T1   A7:A6,*+A10(32)   ; |169| 
||         MVKH    .S2     0xfff00000,B17
||         ZERO    .L1     A8                ; |170| 
||         ZERO    .S1     A9
||         ZERO    .L2     B16               ; |170| 

           STDW    .D1T2   B17:B16,*+A10(24) ; |168| 
||         SET     .S1     A9,0x14,0x1e,A9
||         ZERO    .L1     A5

           STDW    .D1T1   A9:A8,*+A10(16)   ; |167| 
||         MVK     .L2     0x8,B4
||         SUB     .S2     B4,8,B10
||         MVKH    .S1     0x80000000,A5
||         ZERO    .L1     A4                ; |170| 

           ADD     .L1     -1,A5,A17
||         STDW    .D1T1   A5:A4,*+A10(8)    ; |166| 

           STDW    .D1T1   A17:A16,*+A10(48) ; |171| 
||         MV      .L1X    B4,A11            ; |166| 
||         ZERO    .S1     A12               ; |170| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L10:    
;          EXCLUSIVE CPU CYCLES: 6

           LDDW    .D2T2   *++B10,B5:B4      ; |175| 
||         CALL    .S1     tanh              ; |175| 

           ADDKPC  .S2     $C$RL11,B3,3      ; |175| 
           DADD    .L1X    0,B5:B4,A5:A4     ; |175| 
$C$RL11:   ; CALL OCCURS {tanh} {0}          ; |175| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 34
           MVKL    .S1     output,A3
           MVKH    .S1     output,A3
           MV      .L1     A3,A13            ; |175| 
           LDW     .D1T2   *A13,B4           ; |175| 
           NOP             4
           ADD     .L2X    A12,B4,B4         ; |175| 
           STDW    .D2T1   A5:A4,*B4         ; |175| 

           CALLP   .S2     tanhdp,B3
||         LDDW    .D2T1   *B10,A5:A4        ; |176| 

$C$RL12:   ; CALL OCCURS {tanhdp} {0}        ; |176| 
           LDW     .D1T2   *+A13(4),B4       ; |176| 
           NOP             4
           ADD     .L2X    A12,B4,B4         ; |176| 
           STDW    .D2T1   A5:A4,*B4         ; |176| 
           LDDW    .D2T2   *B10,B5:B4        ; |177| 
           NOP             4

           CALLP   .S2     tanhdp_c,B3
||         DADD    .L1X    0,B5:B4,A5:A4     ; |177| 

$C$RL13:   ; CALL OCCURS {tanhdp_c} {0}      ; |177| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           LDW     .D1T1   *+A13(8),A3       ; |177| 
           MVKL    .S2     0x3fd33333,B9
           MVKL    .S2     0x33333333,B8
           MVKH    .S2     0x3fd33333,B9
           MVKH    .S2     0x33333333,B8
           ADD     .L1     A12,A3,A3         ; |177| 
           STDW    .D1T1   A5:A4,*A3         ; |177| 
           LDDW    .D2T2   *B10,B5:B4        ; |200| 
           ZERO    .L1     A5:A4             ; |203| 
           NOP             3

           ABSDP   .S2     B5:B4,B7:B6       ; |200| 
||         CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |203| 

           ZERO    .L2     B5

           FMPYDP  .M2     B7:B6,B7:B6,B17:B16 ; |124| 
||         CMPLTDP .S2     B7:B6,B9:B8,B0    ; |206| 
|| [ A0]   ZERO    .L1     A7
|| [!A0]   ZERO    .S1     A7
|| [ A0]   ZERO    .D1     A6                ; |203| 

   [!A0]   SET     .S1     A7,0x14,0x1d,A7
|| [!A0]   ZERO    .L1     A6                ; |203| 

   [ B0]   B       .S1     $C$L12            ; |206| 
|| [!B0]   ZERO    .L2     B4                ; |209| 
||         MVKH    .S2     0x40330000,B5
||         MV      .D2     B0,B1             ; guard predicate rewrite

           MV      .L2     B0,B2             ; branch predicate copy
||         CMPGTDP .S2     B7:B6,B5:B4,B0    ; |209| 
|| [ A0]   MVKH    .S1     0xbff00000,A7

           FMPYDP  .M2     B17:B16,B17:B16,B21:B20 ; |124| 
|| [ B2]   MVKL    .S1     0x3f9666af,A5

   [ B1]   ZERO    .L2     B0                ; |209| nullify predicate
|| [ B2]   MVKL    .S1     0x84e8ae0f,A4

   [ B2]   MVKH    .S1     0x3f9666af,A5

   [ B0]   B       .S2     $C$L11            ; |209| 
|| [ B2]   MVKH    .S1     0x84e8ae0f,A4

           ; BRANCHCC OCCURS {$C$L12}        ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5

   [!B0]   ZERO    .L2     B5
|| [!B0]   MVKL    .S1     0x3ff71547,A5
|| [ B0]   B       .S2     $C$L14            ; |214| 
|| [ B0]   ZERO    .L1     A5
|| [ B0]   MV      .D1X    B4,A4             ; |214| 

   [!B0]   MVKH    .S2     0xc0000000,B5
|| [!B0]   MVKL    .S1     0x652b82fe,A4

   [!B0]   FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |153| 
|| [!B0]   MVKH    .S1     0x3ff71547,A5

   [!B0]   MVKH    .S1     0x652b82fe,A4
   [ B0]   SET     .S1     A5,0x14,0x1d,A5
           ; BRANCHCC OCCURS {$C$L11}        ; |209| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 148
           MVKL    .S1     0x5c610ca8,A8
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |153| 
           ZERO    .L2     B6                ; |159| 
           MVKL    .S2     0x3fe63000,B7
           MVKL    .S1     0xbf2bd010,A9
           DPINT   .L1     A5:A4,A22         ; |153| 
           MVKH    .S2     0x3fe63000,B7
           MVKL    .S2     0x3ef152a4,B9
           MVKH    .S1     0x5c610ca8,A8
           INTDP   .L1     A22,A5:A4         ; |159| 
           MVKL    .S2     0x6f58dc1c,B8
           MVKH    .S1     0xbf2bd010,A9
           MVKH    .S2     0x3ef152a4,B9
           MVKH    .S2     0x6f58dc1c,B8
           MVKL    .S2     0x6fb3f6e0,B18
           FMPYDP  .M2X    B7:B6,A5:A4,B7:B6 ; |159| 
           MVKL    .S2     0x3f7c70e4,B19
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |159| 
           MVKH    .S2     0x6fb3f6e0,B18
           FSUBDP  .L2     B5:B4,B7:B6,B5:B4 ; |159| 
           MVKH    .S2     0x3f7c70e4,B19
           MVKL    .S2     0x714251b3,B16
           FSUBDP  .L2X    B5:B4,A5:A4,B7:B6 ; |159| 
           MVKL    .S2     0x3fac718e,B17
           MVKH    .S2     0x714251b3,B16
           FMPYDP  .M2     B7:B6,B7:B6,B5:B4 ; |159| 
           MVKL    .S1     0x6fde3809,A4
           MVKL    .S1     0x3f403f99,A5
           MVKH    .S1     0x6fde3809,A4
           FMPYDP  .M2     B9:B8,B5:B4,B9:B8 ; |159| 
           MVKH    .S1     0x3f403f99,A5
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |160| 
           MVKH    .S2     0x3fac718e,B17
           FADDDP  .L2     B19:B18,B9:B8,B9:B8 ; |159| 
           ZERO    .L1     A16               ; |160| 
           FADDDP  .S1X    B17:B16,A5:A4,A9:A8 ; |160| 
           FMPYDP  .M2     B5:B4,B9:B8,B9:B8 ; |159| 
           ZERO    .L1     A4                ; |159| 
           ZERO    .L1     A5
           MVKH    .S1     0x3fd00000,A5
           FMPYDP  .M1X    B5:B4,A9:A8,A9:A8 ; |160| 
           FADDDP  .L1X    A5:A4,B9:B8,A5:A4 ; |159| 
           ZERO    .L1     A17
           SET     .S1     A17,0x15,0x1d,A17
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |159| 
           FADDDP  .L1     A17:A16,A9:A8,A9:A8 ; |160| 
           ZERO    .L1     A20               ; |69| 
           ZERO    .S1     A21
           FSUBDP  .L1     A9:A8,A5:A4,A9:A8 ; |160| 
           SET     .S1     A21,0x1e,0x1e,A21
           ZERO    .L2     B4                ; |69| 
           RCPDP   .S1     A9:A8,A17:A16     ; |69| 
           MV      .L2X    A21,B5            ; |69| 
           FMPYDP  .M1     A9:A8,A17:A16,A19:A18 ; |69| 
           ZERO    .L2     B8                ; |69| 
           MV      .L2X    A21,B9            ; |69| 
           ZERO    .L1     A31
           FSUBDP  .L1     A21:A20,A19:A18,A19:A18 ; |69| 
           MVK     .S1     0x3fe,A3
           ADD     .S1     A3,A22,A3         ; |67| 
           FMPYDP  .M1     A17:A16,A19:A18,A17:A16 ; |69| 
           ZERO    .L2     B31
           ZERO    .L2     B30
           NOP             1
           FMPYDP  .M1     A9:A8,A17:A16,A19:A18 ; |69| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A19:A18,B5:B4 ; |69| 
           NOP             2
           FMPYDP  .M2X    A17:A16,B5:B4,B5:B4 ; |69| 
           SET     .S1     A31,0x15,0x1d,A17
           MV      .L1     A20,A16           ; |71| 
           NOP             1
           FMPYDP  .M2X    A9:A8,B5:B4,B7:B6 ; |69| 
           ZERO    .L1     A9:A8             ; |71| 
           CMPEQDP .S1     A5:A4,A9:A8,A0    ; |71| 
           NOP             1
           FSUBDP  .L2     B9:B8,B7:B6,B7:B6 ; |69| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |69| 
           MV      .L2     B8,B6             ; |67| 
           ZERO    .L2     B7
           MVKH    .S2     0x40100000,B7
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |69| 
           MV      .L1     A20,A4            ; |71| 
           SHL     .S1     A3,20,A5          ; |67| 
           NOP             1
   [ A0]   ZERO    .L2     B5:B4             ; |72| 
           FADDDP  .L2X    A17:A16,B5:B4,B5:B4 ; |67| 
           MV      .L1     A21,A17           ; |212| 
           NOP             1
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |67| 
           MV      .L1     A21,A5            ; |67| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |67| 
           SET     .S2     B31,0x14,0x1d,B7
           NOP             2
           FADDDP  .L2     B7:B6,B5:B4,B7:B6 ; |67| 
           NOP             2
           RCPDP   .S2     B7:B6,B5:B4       ; |67| 
           NOP             1
           FMPYDP  .M2     B5:B4,B7:B6,B9:B8 ; |67| 
           NOP             4
           FSUBDP  .L1X    A5:A4,B9:B8,A5:A4 ; |67| 
           NOP             2
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |67| 
           MV      .L2X    A21,B5            ; |67| 
           MV      .L2X    A20,B4            ; |67| 
           NOP             1
           FMPYDP  .M1X    A5:A4,B7:B6,A9:A8 ; |67| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A9:A8,B5:B4 ; |67| 
           NOP             3
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |67| 
           SET     .S2     B30,0x14,0x1d,B5
           MV      .L2X    A20,B4            ; |212| 
           NOP             1
           FMPYDP  .M1X    A5:A4,B7:B6,A9:A8 ; |212| 
           NOP             3
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |212| 
           NOP             2
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |212| 
           NOP             1
           BNOP    .S1     $C$L13,1          ; |213| 
           FADDDP  .L1     A5:A4,A5:A4,A5:A4 ; |212| 
           NOP             2
           FSUBDP  .L1X    A5:A4,B5:B4,A5:A4 ; |212| 
           ; BRANCH OCCURS {$C$L13}          ; |213| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1

           ADDAW   .D1     A13,3,A3
||         SUB     .L1     A11,1,A0          ; |174| 
||         FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |178| 
||         SUB     .S1     A11,1,A11         ; |174| 

           ; BRANCH OCCURS {$C$L14}          ; |214| 
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 31

           FMPYDP  .M2     B21:B20,B17:B16,B19:B18 ; |124| 
||         FMPYDP  .M1X    A5:A4,B17:B16,A5:A4 ; |124| 
||         MVKL    .S2     0xbfaba1e4,B5
||         MVKL    .S1     0xbfd55555,A9

           MVKL    .S2     0x3f7f105d,B4
||         MVKL    .S1     0x53b8707d,A8

           MVKH    .S2     0xbfaba1e4,B5
||         MVKH    .S1     0xbfd55555,A9

           MVKH    .S2     0x3f7f105d,B4
||         MVKH    .S1     0x53b8707d,A8

           MVKL    .S2     0x903de2ef,B22
||         MVKL    .S1     0xe912d40f,A16
||         FMPYDP  .M1X    A9:A8,B17:B16,A9:A8 ; |124| 

           MVKL    .S2     0x3f6e11ce,B23
||         MVKL    .S1     0xbf822997,A17
||         FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |124| 

           MVKH    .S2     0x903de2ef,B22
||         MVKH    .S1     0xe912d40f,A16

           MVKH    .S2     0x3f6e11ce,B23
||         MVKH    .S1     0xbf822997,A17

           MVKL    .S2     0x49fb127b,B8
||         FMPYDP  .M2     B23:B22,B19:B18,B17:B16 ; |124| 
||         FMPYDP  .M1X    A17:A16,B21:B20,A17:A16 ; |124| 

           MVKL    .S2     0x3fc11111,B9
           MVKH    .S2     0x49fb127b,B8
           MVKH    .S2     0x3fc11111,B9
           FMPYDP  .M2     B9:B8,B21:B20,B9:B8 ; |124| 
           FMPYDP  .M2X    B19:B18,A5:A4,B5:B4 ; |124| 
           FADDDP  .L1X    B17:B16,A17:A16,A5:A4 ; |124| 
           NOP             1
           FADDDP  .L2X    A9:A8,B9:B8,B9:B8 ; |124| 
           FMPYDP  .M1X    B19:B18,A5:A4,A5:A4 ; |124| 
           NOP             1
           FADDDP  .L2     B9:B8,B5:B4,B5:B4 ; |124| 
           NOP             3
           FADDDP  .L1X    A5:A4,B5:B4,A5:A4 ; |124| 
           NOP             2
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |124| 
           NOP             3
           FADDDP  .L1X    B7:B6,A5:A4,A5:A4 ; |124| 
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 3

           ADDAW   .D1     A13,3,A3
||         SUB     .L1     A11,1,A0          ; |174| 

           SUB     .S1     A11,1,A11         ; |174| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |178| 
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 7
           LDW     .D1T1   *A3,A3            ; |178| 
   [ A0]   BNOP    .S1     $C$L10,3          ; |174| 

           ADD     .L1     A12,A3,A3         ; |178| 
||         ADD     .S1     8,A12,A12         ; |174| 

   [!A0]   CALL    .S1     tanhdp_v          ; |180| 
||         STDW    .D1T1   A5:A4,*A3         ; |178| 

           ; BRANCHCC OCCURS {$C$L10}        ; |174| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDW     .D2T2   *B11,B4           ; |180| 
           MV      .L1     A10,A4
           ADDKPC  .S2     $C$RL14,B3,1      ; |180| 
           MVK     .L1     0x8,A6            ; |180| 
$C$RL14:   ; CALL OCCURS {tanhdp_v} {0}      ; |180| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .L1     0x8,A4            ; |183| 

$C$RL15:   ; CALL OCCURS {allequal} {0}      ; |183| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x3,A4            ; |184| 

$C$RL16:   ; CALL OCCURS {print_test_results} {0}  ; |184| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4
           MVKL    .S1     a_ext,A12

           MVK     .S1     0x777,A3
||         ZERO    .L2     B5

           SET     .S2     B5,0x14,0x14,B5
||         MVKH    .S1     a_ext,A12
||         MV      .L1     A13,A14           ; |189| 
||         ZERO    .L2     B4                ; |187| 

           CALL    .S2     tanh              ; |189| 
||         STDW    .D1T2   B5:B4,*A12        ; |187| 
||         MV      .L1     A12,A10           ; |187| 
||         MV      .S1     A3,A11            ; |187| 
||         ZERO    .L2     B10               ; |187| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A10,A5:A4        ; |189| 
           ADDKPC  .S2     $C$RL17,B3,3      ; |189| 
$C$RL17:   ; CALL OCCURS {tanh} {0}          ; |189| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 26
           LDW     .D1T1   *A14,A3           ; |189| 
           NOP             4
           ADD     .L1X    B10,A3,A3         ; |189| 
           STDW    .D1T1   A5:A4,*A3         ; |189| 

           CALLP   .S2     tanhdp,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |190| 

$C$RL18:   ; CALL OCCURS {tanhdp} {0}        ; |190| 
           LDW     .D1T1   *+A14(4),A3       ; |190| 
           NOP             4
           ADD     .L1X    B10,A3,A3         ; |190| 
           STDW    .D1T1   A5:A4,*A3         ; |190| 

           CALLP   .S2     tanhdp_c,B3
||         LDDW    .D1T1   *A10,A5:A4        ; |191| 

$C$RL19:   ; CALL OCCURS {tanhdp_c} {0}      ; |191| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 22
           LDW     .D1T1   *+A14(8),A3       ; |191| 
           MVKL    .S2     0x33333333,B8
           MVKL    .S2     0x3fd33333,B9
           MVKH    .S2     0x33333333,B8
           MVKH    .S2     0x3fd33333,B9
           ADD     .L2X    B10,A3,B4         ; |191| 
           STDW    .D2T1   A5:A4,*B4         ; |191| 
           LDDW    .D1T2   *A10,B5:B4        ; |200| 
           ZERO    .L1     A5:A4             ; |203| 
           NOP             3

           ABSDP   .S2     B5:B4,B7:B6       ; |200| 
||         CMPLTDP .S1X    B5:B4,A5:A4,A0    ; |203| 

           ZERO    .L2     B5

           FMPYDP  .M2     B7:B6,B7:B6,B21:B20 ; |124| 
||         CMPLTDP .S2     B7:B6,B9:B8,B0    ; |206| 

   [ A0]   ZERO    .L2     B9
|| [!A0]   ZERO    .D2     B9

   [ B0]   B       .S1     $C$L17            ; |206| 
|| [!B0]   ZERO    .L2     B4                ; |209| 
||         MVKH    .S2     0x40330000,B5
||         MV      .D2     B0,B1             ; guard predicate rewrite

           MV      .L2     B0,B2             ; branch predicate copy
||         CMPGTDP .S2     B7:B6,B5:B4,B0    ; |209| 
|| [ A0]   ZERO    .D2     B8                ; |203| 

           FMPYDP  .M2     B21:B20,B21:B20,B23:B22 ; |124| 
|| [!A0]   ZERO    .L2     B8                ; |203| 

   [ B1]   ZERO    .L2     B0                ; |209| nullify predicate
|| [!A0]   SET     .S2     B9,0x14,0x1d,B9

   [ B0]   BNOP    .S1     $C$L16,1          ; |209| 
|| [ A0]   MVKH    .S2     0xbff00000,B9

           ; BRANCHCC OCCURS {$C$L17}        ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

   [!B0]   ZERO    .L2     B5
|| [!B0]   MVKL    .S1     0x3ff71547,A5
|| [ B0]   B       .S2     $C$L19            ; |214| 
|| [ B0]   ZERO    .D2     B5

   [!B0]   MVKH    .S2     0xc0000000,B5
|| [!B0]   MVKL    .S1     0x652b82fe,A4

   [!B0]   FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |153| 
|| [!B0]   MVKH    .S1     0x3ff71547,A5
|| [ B0]   SET     .S2     B5,0x14,0x1d,B5

   [!B0]   MVKH    .S1     0x652b82fe,A4
           ; BRANCHCC OCCURS {$C$L16}        ; |209| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 150
           MVKL    .S1     0x5c610ca8,A6
           ZERO    .L2     B6                ; |159| 
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |153| 
           MVKL    .S2     0x3fe63000,B7
           ZERO    .L1     A8                ; |159| 
           MVKL    .S1     0xbf2bd010,A7
           DPINT   .L1     A5:A4,A16         ; |153| 
           MVKH    .S2     0x3fe63000,B7
           MVKL    .S2     0x3ef152a4,B17
           MVKH    .S1     0x5c610ca8,A6
           INTDP   .L1     A16,A5:A4         ; |159| 
           MVKL    .S2     0x6f58dc1c,B16
           MVKH    .S1     0xbf2bd010,A7
           MVKH    .S2     0x3ef152a4,B17
           MVKH    .S2     0x6f58dc1c,B16
           MVKL    .S2     0x6fb3f6e0,B20
           FMPYDP  .M2X    B7:B6,A5:A4,B7:B6 ; |159| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |159| 
           MVKL    .S2     0x3f7c70e4,B21
           MVKH    .S2     0x6fb3f6e0,B20
           FSUBDP  .L2     B5:B4,B7:B6,B5:B4 ; |159| 
           MVKH    .S2     0x3f7c70e4,B21
           MVKL    .S2     0x714251b3,B18
           FSUBDP  .L2X    B5:B4,A5:A4,B7:B6 ; |159| 
           MVKL    .S2     0x3fac718e,B19
           MVKL    .S1     0x6fde3809,A4
           FMPYDP  .M2     B7:B6,B7:B6,B5:B4 ; |159| 
           MVKL    .S1     0x3f403f99,A5
           MVKH    .S1     0x6fde3809,A4
           MVKH    .S1     0x3f403f99,A5
           FMPYDP  .M2     B17:B16,B5:B4,B17:B16 ; |159| 
           FMPYDP  .M1X    A5:A4,B5:B4,A5:A4 ; |160| 
           MVKH    .S2     0x714251b3,B18
           MVKH    .S2     0x3fac718e,B19
           FADDDP  .L2     B21:B20,B17:B16,B17:B16 ; |159| 
           FADDDP  .L1X    B19:B18,A5:A4,A5:A4 ; |160| 
           ZERO    .L1     A9
           FMPYDP  .M2     B5:B4,B17:B16,B17:B16 ; |159| 
           MVKH    .S1     0x3fd00000,A9
           FMPYDP  .M1X    B5:B4,A5:A4,A7:A6 ; |160| 
           ZERO    .L1     A31
           ZERO    .L1     A21
           FADDDP  .L1X    A9:A8,B17:B16,A5:A4 ; |159| 
           SET     .S1     A31,0x15,0x1d,A9
           FADDDP  .L1     A9:A8,A7:A6,A7:A6 ; |160| 
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |159| 
           ZERO    .S1     A20               ; |69| 
           SET     .S1     A21,0x1e,0x1e,A21
           ZERO    .L2     B4                ; |69| 
           FSUBDP  .L1     A7:A6,A5:A4,A7:A6 ; |160| 
           MV      .L2X    A21,B5            ; |69| 
           ZERO    .L2     B16               ; |69| 
           RCPDP   .S1     A7:A6,A9:A8       ; |69| 
           MV      .L2X    A21,B17           ; |69| 
           FMPYDP  .M1     A7:A6,A9:A8,A19:A18 ; |69| 
           ZERO    .L1     A30
           MVK     .S1     0x3fe,A3
           ADD     .L1     A3,A16,A3         ; |67| 
           FSUBDP  .L1     A21:A20,A19:A18,A19:A18 ; |69| 
           ZERO    .L2     B31
           ZERO    .S1     A29
           FMPYDP  .M1     A9:A8,A19:A18,A9:A8 ; |69| 
           NOP             3
           FMPYDP  .M1     A7:A6,A9:A8,A19:A18 ; |69| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A19:A18,B5:B4 ; |69| 
           NOP             2
           FMPYDP  .M2X    A9:A8,B5:B4,B5:B4 ; |69| 
           SET     .S1     A30,0x15,0x1d,A9
           MV      .L1     A20,A8            ; |71| 
           NOP             1
           FMPYDP  .M2X    A7:A6,B5:B4,B7:B6 ; |69| 
           ZERO    .L1     A7:A6             ; |71| 
           CMPEQDP .S1     A5:A4,A7:A6,A0    ; |71| 
           NOP             1
           FSUBDP  .L2     B17:B16,B7:B6,B7:B6 ; |69| 
           NOP             2
           FMPYDP  .M2     B5:B4,B7:B6,B5:B4 ; |69| 
           NOP             3
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |69| 
           MV      .L1     A20,A4            ; |71| 
           SHL     .S1     A3,20,A5          ; |67| 
           NOP             1
   [ A0]   ZERO    .L2     B5:B4             ; |72| 
           FADDDP  .L2X    A9:A8,B5:B4,B5:B4 ; |67| 
           NOP             2
           FMPYDP  .M2X    A5:A4,B5:B4,B7:B6 ; |67| 
           MV      .L2     B16,B4            ; |67| 
           ZERO    .L2     B5
           MVKH    .S2     0x40100000,B5
           FMPYDP  .M2     B5:B4,B7:B6,B7:B6 ; |67| 
           SET     .S2     B31,0x14,0x1d,B5
           MV      .L1     A21,A5            ; |67| 
           NOP             1
           FADDDP  .L2     B5:B4,B7:B6,B5:B4 ; |67| 
           NOP             2
           RCPDP   .S2     B5:B4,B7:B6       ; |67| 
           NOP             1
           FMPYDP  .M2     B7:B6,B5:B4,B17:B16 ; |67| 
           NOP             4
           FSUBDP  .L1X    A5:A4,B17:B16,A5:A4 ; |67| 
           NOP             2
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |67| 
           MV      .L2X    A21,B7            ; |67| 
           MV      .L2X    A20,B6            ; |67| 
           NOP             1
           FMPYDP  .M1X    A5:A4,B5:B4,A7:A6 ; |67| 
           NOP             4
           FSUBDP  .L2X    B7:B6,A7:A6,B7:B6 ; |67| 
           NOP             3
           FMPYDP  .M1X    A5:A4,B7:B6,A5:A4 ; |67| 
           NOP             3
           FMPYDP  .M1X    A5:A4,B5:B4,A7:A6 ; |212| 
           MV      .L2X    A21,B5            ; |212| 
           MV      .L2X    A20,B4            ; |212| 
           NOP             2
           FSUBDP  .L2X    B5:B4,A7:A6,B5:B4 ; |212| 
           NOP             2
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |212| 
           SET     .S1     A29,0x14,0x1d,A5
           BNOP    .S1     $C$L18,1          ; |213| 
           FADDDP  .L2     B5:B4,B5:B4,B5:B4 ; |212| 
           MV      .L1     A8,A4             ; |212| 
           NOP             1
           FSUBDP  .L2X    B5:B4,A5:A4,B5:B4 ; |212| 
           ; BRANCH OCCURS {$C$L18}          ; |213| 
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 2

           MVK     .S2     12,B6
||         FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |192| 
||         MVKL    .S1     0xcccccccd,A6
||         SUB     .L1     A11,1,A0          ; |188| 
||         SUB     .D1     A11,1,A11         ; |188| 

           ADD     .L2X    A13,B6,B6
||         MVKL    .S1     0xc000cccc,A7

           ; BRANCH OCCURS {$C$L19}          ; |214| 
;** --------------------------------------------------------------------------*
$C$L17:    
;          EXCLUSIVE CPU CYCLES: 32

           MVKL    .S1     0x3f9666af,A5
||         FMPYDP  .M2     B23:B22,B21:B20,B17:B16 ; |124| 
||         MVKL    .S2     0x903de2ef,B24

           MVKL    .S1     0x84e8ae0f,A4
||         MVKL    .S2     0x3f6e11ce,B25

           MVKH    .S1     0x3f9666af,A5
||         MVKH    .S2     0x903de2ef,B24

           MVKH    .S1     0x84e8ae0f,A4
||         MVKH    .S2     0x3f6e11ce,B25

           FMPYDP  .M1X    A5:A4,B21:B20,A5:A4 ; |124| 
||         MVKL    .S1     0x53b8707d,A6
||         MVKL    .S2     0xbfaba1e4,B5

           MVKL    .S1     0xbfd55555,A7
||         MVKL    .S2     0x3f7f105d,B4

           MVKH    .S1     0x53b8707d,A6
||         MVKH    .S2     0xbfaba1e4,B5

           MVKH    .S1     0xbfd55555,A7
||         MVKH    .S2     0x3f7f105d,B4

           MVKL    .S1     0xbf822997,A17
||         FMPYDP  .M1X    A7:A6,B21:B20,A9:A8 ; |124| 
||         FMPYDP  .M2     B25:B24,B17:B16,B21:B20 ; |124| 
||         MVKL    .S2     0x3fc11111,B19

           MVKL    .S1     0xe912d40f,A16
||         MVKL    .S2     0x49fb127b,B18
||         FADDDP  .L1X    B5:B4,A5:A4,A5:A4 ; |124| 

           MVKH    .S1     0xbf822997,A17
||         MVKH    .S2     0x3fc11111,B19

           MVKH    .S1     0xe912d40f,A16
           FMPYDP  .M1X    A17:A16,B23:B22,A7:A6 ; |124| 
           MVKH    .S2     0x49fb127b,B18
           FMPYDP  .M2     B19:B18,B23:B22,B19:B18 ; |124| 
           FMPYDP  .M2X    B17:B16,A5:A4,B5:B4 ; |124| 
           FADDDP  .L1X    B21:B20,A7:A6,A7:A6 ; |124| 
           NOP             1
           FADDDP  .L2X    A9:A8,B19:B18,B19:B18 ; |124| 
           FMPYDP  .M1X    B17:B16,A7:A6,A5:A4 ; |124| 
           NOP             1
           FADDDP  .L2     B19:B18,B5:B4,B5:B4 ; |124| 
           NOP             2
           FADDDP  .L2X    A5:A4,B5:B4,B5:B4 ; |124| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |124| 
           NOP             3
           FADDDP  .L2     B7:B6,B5:B4,B5:B4 ; |124| 
;** --------------------------------------------------------------------------*
$C$L18:    
;          EXCLUSIVE CPU CYCLES: 3

           MVK     .S2     12,B6
||         MVKL    .S1     0xcccccccd,A6
||         SUB     .L1     A11,1,A0          ; |188| 
||         SUB     .D1     A11,1,A11         ; |188| 

           ADD     .S2X    A13,B6,B6
||         MVKL    .S1     0xc000cccc,A7

           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |192| 
;** --------------------------------------------------------------------------*
$C$L19:    
;          EXCLUSIVE CPU CYCLES: 17
           LDW     .D2T2   *B6,B6            ; |192| 
           MVKH    .S1     0xcccccccd,A6
           MVKH    .S1     0xc000cccc,A7
           NOP             2
           ADD     .L2     B10,B6,B6         ; |192| 
           STDW    .D2T2   B5:B4,*B6         ; |192| 
           LDDW    .D1T1   *A10,A5:A4        ; |193| 
           ADD     .L2     8,B10,B10         ; |188| 
           NOP             2
   [ A0]   B       .S1     $C$L15            ; |188| 
           FMPYDP  .M1     A7:A6,A5:A4,A5:A4 ; |193| 
           NOP             3

   [ A0]   CALL    .S1     tanh              ; |189| 
||         STDW    .D1T1   A5:A4,*++A10      ; |193| 

           ; BRANCHCC OCCURS {$C$L15}        ; |188| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 6
           CALL    .S1     tanhdp_v          ; |195| 
           LDW     .D2T2   *B11,B4           ; |195| 
           ADDKPC  .S2     $C$RL20,B3,2      ; |195| 

           MV      .L1     A12,A4
||         MVK     .S1     0x777,A6          ; |195| 

$C$RL20:   ; CALL OCCURS {tanhdp_v} {0}      ; |195| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12

           CALLP   .S2     allequal,B3
||         MVK     .S1     0x777,A4          ; |198| 

$C$RL21:   ; CALL OCCURS {allequal} {0}      ; |198| 

           CALLP   .S2     print_test_results,B3
||         MVK     .L1     0x4,A4            ; |199| 

$C$RL22:   ; CALL OCCURS {print_test_results} {0}  ; |199| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVKL    .S1     cycle_counts+24,A3

           MVKH    .S1     cycle_counts+24,A3
||         ZERO    .L2     B4                ; |114| 
||         ZERO    .L1     A10               ; |114| 
||         ZERO    .D1     A11               ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*A3       ; |114| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B5           ; |116| 
           MVKL    .S1     t_start,A3
           MVKH    .S1     t_start,A3

           MVC     .S2     TSCL,B6           ; |117| 
||         STDW    .D1T2   B5:B4,*A3         ; |116| 

           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B6,B4,B9:B8       ; |117| 

           EXT     .S2     B9,24,24,B6       ; |117| 
||         SUB     .L2     B7,B5,B5          ; |117| 
||         MVKL    .S1     t_offset,A3

           ADD     .L2     B5,B6,B5          ; |117| 
||         MV      .S2     B8,B4             ; |117| 
||         MVKH    .S1     t_offset,A3

           MVKL    .S1     input,A3
||         STDW    .D1T2   B5:B4,*A3         ; |117| 

           CALL    .S2     gimme_random      ; |208| 
||         MVKH    .S1     input,A3

           LDW     .D1T1   *A3,A13           ; |208| 

           MV      .L2X    A11,B12           ; |117| 
||         MVK     .S1     0x80,A12
||         ZERO    .L1     A5

           MV      .L2X    A11,B4            ; |208| 
||         ZERO    .S2     B5
||         MVKH    .S1     0x40440000,A5
||         MV      .L1     A10,A4            ; |208| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains control code
;*----------------------------------------------------------------------------*
$C$L20:    
;          EXCLUSIVE CPU CYCLES: 2
           MVKH    .S2     0xc0340000,B5
           ADDKPC  .S2     $C$RL23,B3,0      ; |208| 
$C$RL23:   ; CALL OCCURS {gimme_random} {0}  ; |208| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 16
           ADD     .L1X    A13,B12,A3        ; |208| 

           STDW    .D1T1   A5:A4,*A3         ; |208| 
||         MVC     .S2     TSCL,B4           ; |122| 

           NOP             1

           MV      .L1X    B4,A6             ; |122| Define a twin register
||         MVC     .S2     TSCH,B4           ; |122| 

           ABSDP   .S1     A5:A4,A5:A4       ; |200| 
||         ADD     .L2X    A13,B12,B5        ; |202| 
||         MVKL    .S2     0x3fd33333,B7
||         ZERO    .L1     A9

           MVKL    .S2     0x33333333,B6
||         LDDW    .D2T2   *B5,B9:B8         ; |202| 
||         MV      .L1X    B4,A7             ; |122| 
||         MV      .L2X    A13,B10           ; |202| 

           MVKH    .S2     0x3fd33333,B7
||         MVKH    .S1     0x40330000,A9

           MVKH    .S2     0x33333333,B6
           CMPLTDP .S2X    A5:A4,B7:B6,B1    ; |206| 
           ZERO    .L2     B7:B6             ; |202| 

   [ B1]   B       .S1     $C$L22            ; |206| 
|| [!B1]   ZERO    .L1     A8                ; |209| 
||         CMPLTDP .S2     B9:B8,B7:B6,B0    ; |202| 

           CMPGTDP .S1     A5:A4,A9:A8,A0    ; |209| 
||         FMPYDP  .M1     A5:A4,A5:A4,A9:A8 ; |124| 

   [!B0]   ZERO    .L2     B9
|| [ B0]   ZERO    .D2     B9
|| [ B1]   MVKL    .S2     0x3f9666af,B7

   [ B1]   ZERO    .L1     A0                ; |209| nullify predicate
|| [ B0]   ZERO    .L2     B8                ; |203| 
|| [!B0]   ZERO    .D2     B8                ; |197| 
|| [ B1]   MVKL    .S2     0x84e8ae0f,B6

   [ A0]   B       .S1     $C$L21            ; |209| 
|| [!B0]   SET     .S2     B9,0x14,0x1d,B9

           FMPYDP  .M1     A9:A8,A9:A8,A17:A16 ; |124| 
|| [ B0]   MVKH    .S2     0xbff00000,B9

           ; BRANCHCC OCCURS {$C$L22}        ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 4

   [!A0]   ZERO    .L1     A9
|| [!A0]   ZERO    .D1     A8                ; |153| 
|| [!A0]   MVKL    .S2     0x3ff71547,B5
|| [ A0]   B       .S1     $C$L24            ; |214| 
|| [ A0]   ZERO    .L2     B5

   [!A0]   MVKH    .S1     0xc0000000,A9
|| [!A0]   MVKL    .S2     0x652b82fe,B4

   [!A0]   FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |153| 
|| [!A0]   MVKH    .S2     0x3ff71547,B5

   [!A0]   MVKH    .S2     0x652b82fe,B4
           ; BRANCHCC OCCURS {$C$L21}        ; |209| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 149
           MVKL    .S2     0x5c610ca8,B6
           ZERO    .L1     A8                ; |159| 
           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |153| 
           MVKL    .S1     0x3fe63000,A9
           MVKL    .S2     0xbf2bd010,B7
           MVKH    .S1     0x3fe63000,A9
           DPINT   .L2     B5:B4,B20         ; |153| 
           MVKL    .S1     0x3ef152a4,A17
           MVKH    .S2     0x5c610ca8,B6
           MVKL    .S1     0x6f58dc1c,A16
           INTDP   .L2     B20,B5:B4         ; |159| 
           MVKH    .S2     0xbf2bd010,B7
           MVKH    .S1     0x3ef152a4,A17
           MVKH    .S1     0x6f58dc1c,A16
           MVKL    .S1     0x6fb3f6e0,A20
           MVKL    .S1     0x3f7c70e4,A21
           FMPYDP  .M1X    A9:A8,B5:B4,A9:A8 ; |159| 
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |159| 
           MVKH    .S1     0x6fb3f6e0,A20
           MVKH    .S1     0x3f7c70e4,A21
           FSUBDP  .L1     A5:A4,A9:A8,A5:A4 ; |159| 
           ZERO    .L2     B16               ; |160| 
           ZERO    .L2     B17
           FSUBDP  .L1X    A5:A4,B5:B4,A9:A8 ; |159| 
           MVKL    .S2     0x6fde3809,B4
           MVKL    .S2     0x3f403f99,B5
           FMPYDP  .M1     A9:A8,A9:A8,A5:A4 ; |159| 
           MVKH    .S2     0x6fde3809,B4
           MVKH    .S2     0x3f403f99,B5
           SET     .S2     B17,0x15,0x1d,B17

           FMPYDP  .M1     A17:A16,A5:A4,A19:A18 ; |159| 
||         MVKL    .S1     0x3fac718e,A17

           FMPYDP  .M2X    B5:B4,A5:A4,B5:B4 ; |160| 
||         MVKL    .S1     0x714251b3,A16

           MVKH    .S1     0x3fac718e,A17
           MVKH    .S1     0x714251b3,A16
           FADDDP  .L1     A21:A20,A19:A18,A19:A18 ; |159| 
           FADDDP  .L2X    A17:A16,B5:B4,B7:B6 ; |160| 
           ZERO    .L2     B4                ; |159| 
           FMPYDP  .M1     A5:A4,A19:A18,A19:A18 ; |159| 
           ZERO    .L2     B5
           MVKH    .S2     0x3fd00000,B5
           FMPYDP  .M2X    A5:A4,B7:B6,B19:B18 ; |160| 
           ZERO    .L2     B22               ; |69| 
           FADDDP  .L2X    B5:B4,A19:A18,B5:B4 ; |159| 
           ZERO    .L2     B23
           SET     .S2     B23,0x1e,0x1e,B23
           FMPYDP  .M2X    A9:A8,B5:B4,B7:B6 ; |159| 
           FADDDP  .L2     B17:B16,B19:B18,B5:B4 ; |160| 
           ZERO    .L1     A4                ; |69| 
           MV      .L1X    B23,A5            ; |69| 
           FSUBDP  .L2     B5:B4,B7:B6,B17:B16 ; |160| 
           MV      .L1X    B23,A17           ; |69| 
           ZERO    .L1     A16               ; |69| 
           RCPDP   .S2     B17:B16,B5:B4     ; |69| 
           ZERO    .L2     B31
           FMPYDP  .M2     B17:B16,B5:B4,B19:B18 ; |69| 
           MVK     .S2     0x3fe,B30
           ZERO    .L1     A31
           ZERO    .L1     A30
           FSUBDP  .L2     B23:B22,B19:B18,B19:B18 ; |69| 
           NOP             2
           FMPYDP  .M2     B5:B4,B19:B18,B5:B4 ; |69| 
           NOP             3
           FMPYDP  .M2     B17:B16,B5:B4,B19:B18 ; |69| 
           NOP             4
           FSUBDP  .L1X    A5:A4,B19:B18,A5:A4 ; |69| 
           NOP             2
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |69| 
           ZERO    .L2     B5:B4             ; |71| 
           CMPEQDP .S2     B7:B6,B5:B4,B0    ; |71| 
           ADD     .L2     B30,B20,B4        ; |67| 
           FMPYDP  .M1X    B17:B16,A5:A4,A9:A8 ; |69| 
           SHL     .S2     B4,20,B5          ; |67| 
           ZERO    .L2     B16               ; |67| 
           SET     .S2     B31,0x15,0x1d,B17
           FSUBDP  .L1     A17:A16,A9:A8,A9:A8 ; |69| 
           ZERO    .L2     B4                ; |67| 
           NOP             1
           FMPYDP  .M1     A5:A4,A9:A8,A5:A4 ; |69| 
           ZERO    .L1     A8                ; |67| 
           ZERO    .L1     A9
           MVKH    .S1     0x40100000,A9
           FMPYDP  .M1X    B7:B6,A5:A4,A5:A4 ; |69| 
           NOP             3
   [ B0]   ZERO    .L1     A5:A4             ; |72| 
           FADDDP  .L1X    B17:B16,A5:A4,A5:A4 ; |67| 
           ZERO    .L2     B16               ; |212| 
           MV      .L2     B23,B17           ; |212| 
           FMPYDP  .M1X    B5:B4,A5:A4,A5:A4 ; |67| 
           ZERO    .L2     B4                ; |67| 
           MV      .L2     B23,B5            ; |67| 
           NOP             1
           FMPYDP  .M1     A9:A8,A5:A4,A5:A4 ; |67| 
           ZERO    .L1     A8                ; |67| 
           SET     .S1     A31,0x14,0x1d,A9
           NOP             1
           FADDDP  .L1     A9:A8,A5:A4,A9:A8 ; |67| 
           NOP             2
           RCPDP   .S1     A9:A8,A5:A4       ; |67| 
           NOP             1
           FMPYDP  .M1     A5:A4,A9:A8,A17:A16 ; |67| 
           NOP             4
           FSUBDP  .L2X    B5:B4,A17:A16,B5:B4 ; |67| 
           NOP             2
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |67| 
           ZERO    .L1     A4                ; |67| 
           MV      .L1X    B23,A5            ; |67| 
           NOP             1
           FMPYDP  .M2X    B5:B4,A9:A8,B7:B6 ; |67| 
           NOP             4
           FSUBDP  .L1X    A5:A4,B7:B6,A5:A4 ; |67| 
           NOP             3
           FMPYDP  .M2X    B5:B4,A5:A4,B7:B6 ; |67| 
           ZERO    .L1     A4                ; |212| 
           SET     .S1     A30,0x14,0x1d,A5
           NOP             1
           FMPYDP  .M2X    B7:B6,A9:A8,B5:B4 ; |212| 
           NOP             3
           FSUBDP  .L2     B17:B16,B5:B4,B5:B4 ; |212| 
           NOP             2
           FMPYDP  .M2     B7:B6,B5:B4,B5:B4 ; |212| 
           NOP             1
           BNOP    .S1     $C$L23,1          ; |213| 
           FADDDP  .L2     B5:B4,B5:B4,B5:B4 ; |212| 
           NOP             2
           FSUBDP  .L2X    B5:B4,A5:A4,B5:B4 ; |212| 
           ; BRANCH OCCURS {$C$L23}          ; |213| 
;** --------------------------------------------------------------------------*
$C$L21:    
;          EXCLUSIVE CPU CYCLES: 2

           MVK     .S2     12,B6
||         ZERO    .L2     B4                ; |214| 
||         MVKL    .S1     t_start,A3

           ADD     .L2X    A14,B6,B6
||         SET     .S2     B5,0x14,0x1d,B5
||         MVKH    .S1     t_start,A3

           ; BRANCH OCCURS {$C$L24}          ; |214| 
;** --------------------------------------------------------------------------*
$C$L22:    
;          EXCLUSIVE CPU CYCLES: 31

           MVKH    .S2     0x84e8ae0f,B6
||         MVKL    .S1     0x3f7f105d,A18

           MVKH    .S2     0x3f9666af,B7
||         MVKL    .S1     0xbfaba1e4,A19

           FMPYDP  .M2X    B7:B6,A9:A8,B7:B6 ; |124| 
||         MVKH    .S1     0x3f7f105d,A18
||         MVKL    .S2     0xbfd55555,B5

           FMPYDP  .M1     A17:A16,A9:A8,A21:A20 ; |124| 
||         MVKH    .S1     0xbfaba1e4,A19
||         MVKL    .S2     0x53b8707d,B4

           MVKL    .S1     0x903de2ef,A24
||         MVKH    .S2     0xbfd55555,B5

           MVKL    .S1     0x3f6e11ce,A25
||         MVKH    .S2     0x53b8707d,B4

           MVKH    .S1     0x903de2ef,A24
||         MVKL    .S2     0xe912d40f,B18
||         FMPYDP  .M2X    B5:B4,A9:A8,B17:B16 ; |124| 

           MVKH    .S1     0x3f6e11ce,A25
||         MVKL    .S2     0xbf822997,B19
||         FADDDP  .L2X    A19:A18,B7:B6,B7:B6 ; |124| 

           MVKL    .S1     0x49fb127b,A22
||         FMPYDP  .M1     A25:A24,A21:A20,A19:A18 ; |124| 
||         MVKH    .S2     0xe912d40f,B18

           MVKL    .S1     0x3fc11111,A23
||         MVKH    .S2     0xbf822997,B19

           MVKH    .S1     0x49fb127b,A22
||         FMPYDP  .M2X    B19:B18,A17:A16,B5:B4 ; |124| 

           MVKH    .S1     0x3fc11111,A23
           FMPYDP  .M1     A23:A22,A17:A16,A17:A16 ; |124| 
           FMPYDP  .M1X    A21:A20,B7:B6,A9:A8 ; |124| 
           FADDDP  .L2X    A19:A18,B5:B4,B5:B4 ; |124| 
           NOP             1
           FADDDP  .L1X    B17:B16,A17:A16,A17:A16 ; |124| 
           FMPYDP  .M2X    A21:A20,B5:B4,B5:B4 ; |124| 
           NOP             1
           FADDDP  .L1     A17:A16,A9:A8,A9:A8 ; |124| 
           NOP             3
           FADDDP  .L2X    B5:B4,A9:A8,B5:B4 ; |124| 
           NOP             2
           FMPYDP  .M2X    A5:A4,B5:B4,B5:B4 ; |124| 
           NOP             3
           FADDDP  .L2X    A5:A4,B5:B4,B5:B4 ; |124| 
;** --------------------------------------------------------------------------*
$C$L23:    
;          EXCLUSIVE CPU CYCLES: 2

           MVK     .S2     12,B6
||         MVKL    .S1     t_start,A3

           ADD     .S2X    A14,B6,B6
||         MVKH    .S1     t_start,A3

;** --------------------------------------------------------------------------*
$C$L24:    
;          EXCLUSIVE CPU CYCLES: 23
           LDW     .D2T2   *B6,B6            ; |212| 
           FMPYDP  .M2     B9:B8,B5:B4,B5:B4 ; |212| 
           STDW    .D1T1   A7:A6,*A3
           NOP             2
           ADD     .L2     B12,B6,B6         ; |212| 

           STDW    .D2T2   B5:B4,*B6         ; |212| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_offset,A3
||         MVKL    .S2     cycle_counts+24,B5
||         SUB     .L1     A12,1,A0          ; |206| 
||         MV      .L2     B4,B9             ; |128| 
||         ADD     .D2     8,B12,B12         ; |206| 
||         SUB     .D1     A12,1,A12         ; |206| 

           MVKH    .S1     t_offset,A3
||         MVKH    .S2     cycle_counts+24,B5

           LDDW    .D1T1   *A3,A9:A8         ; |130| 
||         LDDW    .D2T2   *B5,B7:B6         ; |130| 
|| [ A0]   MVKL    .S1     input,A3

           MV      .L1X    B5,A15            ; |130| 
|| [ A0]   MVKH    .S1     input,A3

   [ A0]   LDW     .D1T1   *A3,A13           ; |208| 
||         MVKL    .S1     t_stop,A31

           MVKH    .S1     t_stop,A31
           STDW    .D1T2   B9:B8,*A31        ; |128| 
           ADDU    .L1     A8,A6,A5:A4       ; |130| 
           ADD     .L1     A5,A9,A5          ; |130| 

   [ A0]   B       .S1     $C$L20            ; |206| 
||         SUBU    .L2X    B8,A4,B5:B4       ; |130| 
||         ADD     .L1     A5,A7,A4          ; |130| 
|| [ A0]   ZERO    .D1     A5

           EXT     .S2     B5,24,24,B16      ; |130| 
||         ADDU    .L2     B6,B4,B5:B4       ; |130| 
|| [ A0]   MVKH    .S1     0x40440000,A5

   [ A0]   CALL    .S1     gimme_random      ; |208| 
||         SUB     .L2X    B9,A4,B6          ; |130| 
||         ADD     .S2     B5,B7,B5          ; |130| 
|| [ A0]   MV      .L1     A10,A4            ; |208| 

           ADD     .L2     B6,B16,B6         ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D1T2   B5:B4,*A15        ; |130| 
|| [ A0]   ZERO    .L2     B5
|| [ A0]   MV      .S2X    A11,B4            ; |208| 

           ; BRANCHCC OCCURS {$C$L20}        ; |206| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A15,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL24,B3,3      ; |135| 
$C$RL24:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           ZERO    .L1     A13
           SET     .S1     A13,0x15,0x1d,A13
           MV      .L1     A10,A12           ; |135| 
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             2

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL25:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MV      .L2X    A15,B4
           STDW    .D2T1   A5:A4,*B4         ; |135| 

           SUBAW   .D2     B4,6,B5
||         MV      .L2X    A11,B31           ; |114| 

           MVC     .S2     B31,TSCL          ; |115| 
||         STDW    .D2T1   A11:A10,*B5       ; |114| 

           MVC     .S2     TSCL,B5           ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MVC     .S2     TSCL,B7           ; |117| 
           MVC     .S2     TSCH,B6           ; |117| 
           MVKL    .S1     t_offset,A3
           MVK     .S1     0x80,A31

           SUBU    .L2     B7,B5,B9:B8       ; |117| 
||         MVKL    .S1     output,A4

           EXT     .S2     B9,24,24,B5       ; |117| 
||         MVKH    .S1     output,A4
||         SUB     .L2     B6,B4,B4          ; |117| 

           ADD     .L2     B4,B5,B9          ; |117| 
||         LDW     .D1T1   *A4,A12
||         MVKH    .S1     t_offset,A3

           STDW    .D1T2   B9:B8,*A3         ; |117| 
||         MV      .L1     A31,A15           ; |117| 
||         MV      .S1X    B10,A14

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L25:    
;          EXCLUSIVE CPU CYCLES: 8
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           CALL    .S1     tanh              ; |221| 
           LDDW    .D1T1   *A14++,A5:A4      ; |221| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           ADDKPC  .S2     $C$RL26,B3,0      ; |221| 
$C$RL26:   ; CALL OCCURS {tanh} {0}          ; |221| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 20

           STDW    .D1T1   A5:A4,*A12++      ; |221| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B4           ; |128| 

           MVKL    .S1     t_start,A3
||         MVKL    .S2     t_offset,B10
||         MV      .L2     B4,B9             ; |128| 
||         SUB     .L1     A15,1,A0          ; |219| 
||         SUB     .D1     A15,1,A15         ; |219| 

           MVKH    .S1     t_start,A3
||         MVKH    .S2     t_offset,B10

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         LDDW    .D2T2   *B10,B7:B6        ; |130| 
||         MVKL    .S1     cycle_counts,A31

           MVKH    .S1     cycle_counts,A31
           MVKL    .S1     t_stop,A30
           MVKH    .S1     t_stop,A30
           STDW    .D1T2   B9:B8,*A30        ; |128| 

           ADDU    .L1X    B6,A6,A5:A4       ; |130| 
||         MVKL    .S2     cycle_counts,B6

           ADD     .L1X    A5,B7,A6          ; |130| 
||         MVKH    .S2     cycle_counts,B6

           SUBU    .L2X    B8,A4,B5:B4       ; |130| 
||         LDDW    .D1T1   *A31,A5:A4        ; |130| 
||         ADD     .L1     A6,A7,A6          ; |130| 

           EXT     .S2     B5,24,24,B7       ; |130| 
|| [!A0]   MV      .L1X    B6,A14

           SUB     .L2X    B9,A6,B5          ; |130| 

   [ A0]   BNOP    .S1     $C$L25,1          ; |219| 
||         ADD     .L2     B5,B7,B7          ; |130| 

           ADDU    .L2X    A4,B4,B17:B16     ; |130| 

           ADD     .L2X    B17,A5,B5         ; |130| 
||         MV      .S2     B16,B4            ; |130| 

           ADD     .L2     B5,B7,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B6         ; |130| 

           ; BRANCHCC OCCURS {$C$L25}        ; |219| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *A14,A5:A4        ; |135| 
           ADDKPC  .S2     $C$RL27,B3,3      ; |135| 
$C$RL27:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A10,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL28:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           STDW    .D1T1   A11:A10,*+A14(16) ; |114| 
||         MV      .L2X    A11,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A5:A4,*A14        ; |135| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B5,B4,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B7,B6,B5          ; |117| 
||         MVK     .S1     0x80,A3

           ADD     .L2     B5,B6,B5          ; |117| 

           MV      .L2X    A3,B10            ; |117| 
||         STDW    .D2T2   B5:B4,*B10        ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L26:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |230| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |230| 
||         CALL    .S1     tanhdp_c          ; |230| 

           LDDW    .D1T1   *A3,A5:A4         ; |230| 
           ADDKPC  .S2     $C$RL29,B3,3      ; |230| 
$C$RL29:   ; CALL OCCURS {tanhdp_c} {0}      ; |230| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+8,B4
           MVKH    .S2     output+8,B4
           LDW     .D2T2   *B4,B4            ; |230| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |230| 

           STDW    .D1T1   A5:A4,*A3         ; |230| 
||         MVC     .S2     TSCL,B16          ; |128| 

           MVC     .S2     TSCH,B8           ; |128| 

           MVKL    .S1     t_offset,A15
||         MVKL    .S2     t_start,B4
||         ADDAD   .D1     A14,2,A3
||         SUB     .L1X    B10,1,A0          ; |228| 
||         MV      .L2     B8,B17            ; |128| 
||         SUB     .D2     B10,1,B10         ; |228| 

           MVKH    .S1     t_offset,A15
||         MVKH    .S2     t_start,B4
||         LDDW    .D1T1   *A3,A7:A6         ; |130| 
|| [!A0]   MV      .L1     A14,A3

           MVK     .S2     16,B12
||         LDDW    .D1T1   *A15,A5:A4        ; |130| 
||         LDDW    .D2T2   *B4,B7:B6         ; |130| 

           MVKL    .S1     t_stop,A31
           MVKH    .S1     t_stop,A31
           ADD     .L2X    A14,B12,B12
           STDW    .D1T2   B17:B16,*A31      ; |128| 
           ADDU    .L2X    A4,B6,B5:B4       ; |130| 

           ADD     .S2X    B5,A5,B6          ; |130| 
|| [ A0]   B       .S1     $C$L26            ; |228| 
||         SUBU    .L2     B16,B4,B5:B4      ; |130| 

           ADD     .D2     B6,B7,B6          ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B8,B6,B6          ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B12        ; |130| 
||         ADD     .L1     8,A12,A12         ; |228| 

           ; BRANCHCC OCCURS {$C$L26}        ; |228| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(16),A5:A4    ; |135| 
           ADDKPC  .S2     $C$RL30,B3,3      ; |135| 
$C$RL30:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A10,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL31:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10

           MV      .L1     A14,A3            ; |135| 
||         STDW    .D2T1   A5:A4,*B12        ; |135| 
||         MV      .L2X    A11,B4            ; |114| 

           MVC     .S2     B4,TSCL           ; |115| 
||         STDW    .D1T1   A11:A10,*+A3(8)   ; |114| 

           MVC     .S2     TSCL,B4           ; |116| 
           MVC     .S2     TSCH,B6           ; |116| 
           MVC     .S2     TSCL,B5           ; |117| 
           MVC     .S2     TSCH,B7           ; |117| 
           SUBU    .L2     B5,B4,B5:B4       ; |117| 

           EXT     .S2     B5,24,24,B6       ; |117| 
||         SUB     .L2     B7,B6,B5          ; |117| 
||         MVK     .S1     0x80,A3

           ADD     .L2     B5,B6,B5          ; |117| 

           STDW    .D1T2   B5:B4,*A15        ; |117| 
||         MV      .L2X    A3,B10            ; |117| 

;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains a call
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*      Disqualified loop: Loop contains non-pipelinable instructions
;*----------------------------------------------------------------------------*
$C$L27:    
;          EXCLUSIVE CPU CYCLES: 15
           MVC     .S2     TSCL,B4           ; |122| 
           MVC     .S2     TSCH,B5           ; |122| 
           MVKL    .S1     input,A3
           MVKH    .S1     input,A3
           LDW     .D1T1   *A3,A3            ; |239| 
           MVKL    .S2     t_start,B6
           MVKH    .S2     t_start,B6
           STDW    .D2T2   B5:B4,*B6         ; |122| 
           NOP             1

           ADD     .L1     A12,A3,A3         ; |239| 
||         CALL    .S1     tanhdp            ; |239| 

           LDDW    .D1T1   *A3,A5:A4         ; |239| 
           ADDKPC  .S2     $C$RL32,B3,3      ; |239| 
$C$RL32:   ; CALL OCCURS {tanhdp} {0}        ; |239| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 24
           MVKL    .S2     output+4,B4
           MVKH    .S2     output+4,B4
           LDW     .D2T2   *B4,B4            ; |239| 
           NOP             4
           ADD     .L1X    A12,B4,A3         ; |239| 

           STDW    .D1T1   A5:A4,*A3         ; |239| 
||         MVC     .S2     TSCL,B8           ; |128| 

           MVC     .S2     TSCH,B6           ; |128| 

           MVKL    .S2     t_start,B12
||         MVKL    .S1     t_offset,A14
||         SUB     .L1X    B10,1,A0          ; |237| 
||         MV      .L2     B6,B9             ; |128| 
||         ADD     .D1     8,A12,A12         ; |237| 
||         SUB     .D2     B10,1,B10         ; |237| 

           MVKH    .S2     t_start,B12
||         MVKH    .S1     t_offset,A14

           LDDW    .D1T1   *A14,A5:A4        ; |130| 
||         LDDW    .D2T2   *B12,B17:B16      ; |130| 
||         MVKL    .S1     cycle_counts+8,A3

           MVKH    .S1     cycle_counts+8,A3

           LDDW    .D1T1   *A3,A7:A6         ; |130| 
||         MVKL    .S1     t_stop,A15

           MV      .L2X    A3,B13            ; |128| 
||         MVKH    .S1     t_stop,A15

   [!A0]   MVKL    .S1     cycle_counts,A3
||         STDW    .D1T2   B9:B8,*A15        ; |128| 

           ADDU    .L2X    A4,B16,B5:B4      ; |130| 
|| [!A0]   MVKH    .S1     cycle_counts,A3

   [ A0]   B       .S1     $C$L27            ; |237| 
||         ADD     .S2X    B5,A5,B6          ; |130| 
||         SUBU    .L2     B8,B4,B5:B4       ; |130| 

           ADD     .D2     B6,B17,B6         ; |130| 
||         EXT     .S2     B5,24,24,B7       ; |130| 
||         ADDU    .L2X    A6,B4,B5:B4       ; |130| 

           SUB     .L2     B9,B6,B6          ; |130| 
||         ADD     .S2X    B5,A7,B5          ; |130| 

           ADD     .L2     B6,B7,B6          ; |130| 
           ADD     .L2     B5,B6,B5          ; |130| 

   [!A0]   CALL    .S1     __c6xabi_fltllif  ; |135| 
||         STDW    .D2T2   B5:B4,*B13        ; |130| 

           ; BRANCHCC OCCURS {$C$L27}        ; |237| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           LDDW    .D1T1   *+A3(8),A5:A4     ; |135| 
           ADDKPC  .S2     $C$RL33,B3,3      ; |135| 
$C$RL33:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |135| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 109
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |135| 
           MV      .L1     A10,A12           ; |135| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |135| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |135| 

$C$RL34:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |135| 
           MV      .L1X    B13,A12           ; |135| 
           SUBAW   .D1     A12,2,A3

           MV      .L2X    A11,B4            ; |114| 
||         STDW    .D1T1   A5:A4,*A12        ; |135| 

           STDW    .D1T1   A11:A10,*+A3(32)  ; |114| 
||         MVC     .S2     B4,TSCL           ; |115| 

           MVC     .S2     TSCL,B16          ; |116| 
           MVC     .S2     TSCH,B4           ; |116| 
           MV      .L2     B4,B17            ; |116| 

           STDW    .D2T2   B17:B16,*B12      ; |116| 
||         MVC     .S2     TSCL,B5           ; |117| 

           MVC     .S2     TSCH,B8           ; |117| 

           MVKL    .S1     input,A3
||         SUBU    .L2     B5,B16,B7:B6      ; |117| 

           MVKH    .S1     input,A3
||         EXT     .S2     B7,24,24,B7       ; |117| 
||         SUB     .L2     B8,B17,B5         ; |117| 

           MVKL    .S1     output,A10
||         ADD     .L2     B5,B7,B7          ; |117| 

           MV      .L2X    A3,B4             ; |247| 
||         MVKH    .S1     output,A10
||         STDW    .D1T2   B7:B6,*A14        ; |117| 

           CALLP   .S2     tanhdp_v,B3
||         LDW     .D2T1   *B4,A4            ; |247| 
||         LDW     .D1T2   *+A10(16),B4      ; |247| 
||         MVK     .S1     0x80,A6           ; |247| 

$C$RL35:   ; CALL OCCURS {tanhdp_v} {0}      ; |247| 
           MVC     .S2     TSCL,B16          ; |128| 
           MVC     .S2     TSCH,B6           ; |128| 

           LDDW    .D1T1   *A14,A7:A6        ; |130| 
||         LDDW    .D2T2   *B12,B5:B4        ; |130| 

           MVK     .S2     24,B10
           ADD     .L2X    A12,B10,B10
           MV      .L2     B6,B17            ; |128| 
           LDDW    .D2T2   *B10,B7:B6        ; |130| 
           ADDU    .L1X    A6,B4,A5:A4       ; |130| 
           ADD     .L1     A5,A7,A3          ; |130| 
           SUBU    .L1X    B16,A4,A5:A4      ; |130| 

           ADD     .L2X    A3,B5,B4          ; |130| 
||         EXT     .S1     A5,24,24,A3       ; |130| 

           ADDU    .L1X    B6,A4,A7:A6       ; |130| 
||         SUB     .L2     B17,B4,B4         ; |130| 

           ADD     .L2X    B4,A3,B5          ; |130| 
           ADD     .L2X    A7,B7,B4          ; |130| 

           ADD     .L2     B4,B5,B7          ; |130| 
||         MV      .S2X    A6,B6             ; |130| 

           MV      .L2X    A15,B8            ; |128| 

           CALLP   .S2     __c6xabi_fltllif,B3
||         DADD    .L1X    0,B7:B6,A5:A4     ; |130| 
||         STDW    .D2T2   B17:B16,*B8       ; |128| 

$C$RL36:   ; CALL OCCURS {__c6xabi_fltllif} {0}  ; |130| 
           ZERO    .L1     A3
           SET     .S1     A3,0x1a,0x1d,A3
           MPYSP   .M1     A3,A4,A3          ; |130| 
           MV      .L1     A11,A12           ; |130| 
           NOP             2
           SPDP    .S1     A3,A5:A4          ; |130| 
           NOP             1

           CALLP   .S2     __c6xabi_fixdlli,B3
||         FADDDP  .L1     A13:A12,A5:A4,A5:A4 ; |130| 

$C$RL37:   ; CALL OCCURS {__c6xabi_fixdlli} {0}  ; |130| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7
           MVKH    .S2     0xd9d7bdbb,B6

           DADD    .L1     0,A5:A4,A7:A6     ; |130| 
||         LDW     .D1T1   *A10,A4           ; |66| 
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         LDW     .D1T2   *+A10(4),B4       ; |66| 
||         STDW    .D2T1   A7:A6,*B10        ; |130| 
||         MVK     .S1     0x80,A6           ; |66| 
||         MVK     .L1     0x1,A8            ; |66| 

$C$RL38:   ; CALL OCCURS {isequal} {0}       ; |66| 
           MVKL    .S2     0xd9d7bdbb,B6
           MVKL    .S2     0x3ddb7cdf,B7

           LDW     .D1T2   *+A10(8),B4       ; |67| 
||         MVKL    .S1     fcn_pass,A11
||         MVKH    .S2     0xd9d7bdbb,B6

           MV      .L1     A4,A5             ; |66| 
||         LDW     .D1T1   *A10,A4           ; |67| 
||         MVKH    .S1     fcn_pass,A11
||         MVKH    .S2     0x3ddb7cdf,B7

           CALLP   .S2     isequal,B3
||         STW     .D1T1   A5,*+A11(4)       ; |66| 
||         MVK     .S1     0x80,A6           ; |67| 
||         MVK     .L1     0x1,A8            ; |67| 

$C$RL39:   ; CALL OCCURS {isequal} {0}       ; |67| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6

           STW     .D1T1   A4,*+A11(8)       ; |67| 
||         MVKH    .S2     0x3ddb7cdf,B7

           LDW     .D1T2   *+A10(12),B4      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |68| 
||         MVK     .S1     0x80,A6           ; |68| 
||         MVK     .L1     0x1,A8            ; |68| 

$C$RL40:   ; CALL OCCURS {isequal} {0}       ; |68| 
           MVKL    .S2     0x3ddb7cdf,B7
           MVKL    .S2     0xd9d7bdbb,B6
           MVKH    .S2     0x3ddb7cdf,B7

           STW     .D1T1   A4,*+A11(12)      ; |68| 
||         MVKH    .S2     0xd9d7bdbb,B6

           CALLP   .S2     isequal,B3
||         LDW     .D1T1   *A10,A4           ; |69| 
||         LDW     .D2T2   *B11,B4           ; |69| 
||         MVK     .S1     0x80,A6           ; |69| 
||         MVK     .L1     0x1,A8            ; |69| 

$C$RL41:   ; CALL OCCURS {isequal} {0}       ; |69| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           ADD     .L2X    4,A11,B4
           LDW     .D2T2   *B4,B0            ; |72| 
           STW     .D1T1   A4,*+A11(16)      ; |69| 
           ADD     .L2X    8,A11,B4
           NOP             2

   [!B0]   BNOP    .S1     $C$L28,4          ; |72| 
||         MV      .L2     B0,B1             ; guard predicate rewrite
|| [ B0]   LDW     .D2T2   *B4,B0            ; |72| 

   [ B1]   ADD     .L2     4,B4,B4
           ; BRANCHCC OCCURS {$C$L28}        ; |72| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 15
   [ B0]   LDW     .D2T2   *B4,B4            ; |72| 
   [!B0]   MV      .L1     A12,A0            ; |72| 
           CMPEQ   .L1     A4,0,A3           ; |72| 
           XOR     .L1     1,A3,A3           ; |72| 
           MVK     .L1     0x1,A4            ; |72| 
   [ B0]   CMPEQ   .L2     B4,0,B4           ; |72| 
   [ B0]   XOR     .L2     1,B4,B4           ; |72| 
           NOP             1
   [ B0]   AND     .L1X    A3,B4,A0          ; |72| 
   [ A0]   B       .S1     $C$L29            ; |72| 
   [ A0]   CALL    .S1     print_test_results ; |253| 
   [ A0]   MVKL    .S1     all_pass,A3
   [ A0]   MVKH    .S1     all_pass,A3
           NOP             2
           ; BRANCHCC OCCURS {$C$L29}        ; |72| 
;** --------------------------------------------------------------------------*
$C$L28:    
;          EXCLUSIVE CPU CYCLES: 5
           CALL    .S1     print_test_results ; |253| 
           MVKL    .S1     all_pass,A3
           MVKH    .S1     all_pass,A3
           MV      .L1     A12,A4
           NOP             1
;** --------------------------------------------------------------------------*
$C$L29:    
;          EXCLUSIVE CPU CYCLES: 1

           STW     .D1T1   A4,*A3            ; |72| 
||         MVK     .L1     0x2,A4            ; |253| 
||         ADDKPC  .S2     $C$RL42,B3,0      ; |253| 

$C$RL42:   ; CALL OCCURS {print_test_results} {0}  ; |253| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 30
           MVKL    .S2     $C$SL2+0,B4
           MVKH    .S2     $C$SL2+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |254| 

$C$RL43:   ; CALL OCCURS {printf} {0}        ; |254| 
           MVKL    .S2     $C$SL3+0,B4
           MVKH    .S2     $C$SL3+0,B4

           CALLP   .S2     printf,B3
||         STW     .D2T2   B4,*+SP(4)        ; |254| 

$C$RL44:   ; CALL OCCURS {printf} {0}        ; |254| 
           MVKL    .S1     $C$SL1+0,A10
           MVKH    .S1     $C$SL1+0,A10

           CALLP   .S2     print_profile_results,B3
||         MV      .L1     A10,A4            ; |261| 

$C$RL45:   ; CALL OCCURS {print_profile_results} {0}  ; |261| 

           CALLP   .S2     print_memory_results,B3
||         MV      .L1     A10,A4            ; |264| 

$C$RL46:   ; CALL OCCURS {print_memory_results} {0}  ; |264| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 11
           LDW     .D2T2   *++SP(16),B3      ; |265| 
           LDDW    .D2T1   *++SP,A13:A12     ; |265| 
           LDDW    .D2T1   *++SP,A15:A14     ; |265| 
           LDDW    .D2T2   *++SP,B11:B10     ; |265| 
           LDDW    .D2T2   *++SP,B13:B12     ; |265| 

           LDW     .D2T1   *++SP(8),A10      ; |265| 
||         RET     .S2     B3                ; |265| 

           LDW     .D2T1   *++SP(8),A11      ; |265| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |265| 
;******************************************************************************
;* STRINGS                                                                    *
;******************************************************************************
	.sect	".const:.string"
$C$SL1:	.string	"tanhDP",0
$C$SL2:	.string	"----------------------------------------",0
$C$SL3:	.string	"----------------------------------------",10,0
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	printf
	.global	tanh
	.global	driver_init
	.global	print_profile_results
	.global	print_memory_results
	.global	print_test_results
	.global	gimme_random
	.global	isequal
	.global	tanhdp_c
	.global	tanhdp
	.global	tanhdp_v
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
