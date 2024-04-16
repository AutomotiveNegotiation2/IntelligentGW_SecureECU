///****************************************************************************/
///*  aeabi_ctype.asm v#####                                                  */
///*  Copyright (c) 2006@%%%%  Texas Instruments Incorporated                 */
///****************************************************************************/
///****************************************************************************/
///* ARM's CLIB ABI (GENC-003539) requires that a conforming toolset to       */
///* supply the following ctype table.                                        */
///****************************************************************************/
	.global	__aeabi_ctype_table_
	.global	__aeabi_ctype_table_C
	.section ".rodata","a",%progbits
	.align	4
__aeabi_ctype_table_:
__aeabi_ctype_table_C:
	.byte  	0		//  -1   EOF   :  0
	.byte  	128		// 0x00  NUL   : _ABI_C
	.byte  	128		// 0x01  SOH   : _ABI_C
	.byte  	128		// 0x02  STX   : _ABI_C
	.byte  	128		// 0x03  ETX   : _ABI_C
	.byte  	128		// 0x04  EOT   : _ABI_C
	.byte  	128		// 0x05  ENQ   : _ABI_C
	.byte  	128		// 0x06  ACK   : _ABI_C
	.byte  	128		// 0x07  BEL   : _ABI_C
	.byte  	128		// 0x08  BS    : _ABI_C
	.byte  	144		// 0x09  HT    : _ABI_C | _ABI_S
	.byte  	144		// 0x0A  LF    : _ABI_C | _ABI_S
	.byte  	144		// 0x0B  VT    : _ABI_C | _ABI_S
	.byte  	144		// 0x0C  FF    : _ABI_C | _ABI_S
	.byte  	144		// 0x0D  CR    : _ABI_C | _ABI_S
	.byte  	128		// 0x0E  SO    : _ABI_C
	.byte  	128		// 0x0F  SI    : _ABI_C
	.byte  	128		// 0x10  DLE   : _ABI_C
	.byte  	128		// 0x11  DC1   : _ABI_C
	.byte  	128		// 0x12  DC2   : _ABI_C
	.byte  	128		// 0x13  DC3   : _ABI_C
	.byte  	128		// 0x14  DC4   : _ABI_C
	.byte  	128		// 0x15  NAK   : _ABI_C
	.byte  	128		// 0x16  SYN   : _ABI_C
	.byte  	128		// 0x17  ETB   : _ABI_C
	.byte  	128		// 0x18  CAN   : _ABI_C
	.byte  	128		// 0x19  EM    : _ABI_C
	.byte  	128		// 0x1A  SUB   : _ABI_C
	.byte  	128		// 0x1B  ESC   : _ABI_C
	.byte  	128		// 0x1C  FS    : _ABI_C
	.byte  	128		// 0x1D  GS    : _ABI_C
	.byte  	128		// 0x1E  RS    : _ABI_C
	.byte  	128		// 0x1F  US    : _ABI_C
	.byte  	24		// 0x20  ' '   : _ABI_S | _ABI_B
	.byte  	4		// 0x21  '!'   : _ABI_P
	.byte  	4		// 0x22  '"'   : _ABI_P
	.byte  	4		// 0x23  '#'   : _ABI_P
	.byte  	4		// 0x24  '$'   : _ABI_P
	.byte  	4		// 0x25  '%'   : _ABI_P
	.byte  	4		// 0x26  '&'   : _ABI_P
	.byte  	4		// 0x27  '''   : _ABI_P
	.byte  	4		// 0x28  '('   : _ABI_P
	.byte  	4		// 0x29  ')'   : _ABI_P
	.byte  	4		// 0x2A  '*'   : _ABI_P
	.byte  	4		// 0x2B  '+'   : _ABI_P
	.byte  	4		// 0x2C  ','   : _ABI_P
	.byte  	4		// 0x2D  '-'   : _ABI_P
	.byte  	4		// 0x2E  '.'   : _ABI_P
	.byte  	4		// 0x2F  '/'   : _ABI_P
	.byte  	2		// 0x30  '0'   : _ABI_X
	.byte  	2		// 0x31  '1'   : _ABI_X
	.byte  	2		// 0x32  '2'   : _ABI_X
	.byte  	2		// 0x33  '3'   : _ABI_X
	.byte  	2		// 0x34  '4'   : _ABI_X
	.byte  	2		// 0x35  '5'   : _ABI_X
	.byte  	2		// 0x36  '6'   : _ABI_X
	.byte  	2		// 0x37  '7'   : _ABI_X
	.byte  	2		// 0x38  '8'   : _ABI_X
	.byte  	2		// 0x39  '9'   : _ABI_X
	.byte  	4		// 0x3A  ':'   : _ABI_P
	.byte  	4		// 0x3B  '//'   : _ABI_P
	.byte  	4		// 0x3C  '<'   : _ABI_P
	.byte  	4		// 0x3D  '='   : _ABI_P
	.byte  	4		// 0x3E  '>'   : _ABI_P
	.byte  	4		// 0x3F  '?'   : _ABI_P
	.byte  	4		// 0x40  '@'   : _ABI_P
	.byte  	67		// 0x41  'A'   : _ABI_U | _ABI_X
	.byte  	67		// 0x42  'B'   : _ABI_U | _ABI_X
	.byte  	67		// 0x43  'C'   : _ABI_U | _ABI_X
	.byte  	67		// 0x44  'D'   : _ABI_U | _ABI_X
	.byte  	67		// 0x45  'E'   : _ABI_U | _ABI_X
	.byte  	67		// 0x46  'F'   : _ABI_U | _ABI_X
	.byte  	65		// 0x47  'G'   : _ABI_U
	.byte  	65		// 0x48  'H'   : _ABI_U
	.byte  	65		// 0x49  'I'   : _ABI_U
	.byte  	65		// 0x4A  'J'   : _ABI_U
	.byte  	65		// 0x4B  'K'   : _ABI_U
	.byte  	65		// 0x4C  'L'   : _ABI_U
	.byte  	65		// 0x4D  'M'   : _ABI_U
	.byte  	65		// 0x4E  'N'   : _ABI_U
	.byte  	65		// 0x4F  'O'   : _ABI_U
	.byte  	65		// 0x50  'P'   : _ABI_U
	.byte  	65		// 0x51  'Q'   : _ABI_U
	.byte  	65		// 0x52  'R'   : _ABI_U
	.byte  	65		// 0x53  'S'   : _ABI_U
	.byte  	65		// 0x54  'T'   : _ABI_U
	.byte  	65		// 0x55  'U'   : _ABI_U
	.byte  	65		// 0x56  'V'   : _ABI_U
	.byte  	65		// 0x57  'W'   : _ABI_U
	.byte  	65		// 0x58  'X'   : _ABI_U
	.byte  	65		// 0x59  'Y'   : _ABI_U
	.byte  	65		// 0x5A  'Z'   : _ABI_U
	.byte  	4		// 0x5B  '['   : _ABI_P
	.byte  	4		// 0x5C  '\'   : _ABI_P
	.byte  	4		// 0x5D  ']'   : _ABI_P
	.byte  	4		// 0x5E  '^'   : _ABI_P
	.byte  	4		// 0x5F  '_'   : _ABI_P
	.byte  	4		// 0x60  '`'   : _ABI_P
	.byte  	35		// 0x61  'a'   : _ABI_L | _ABI_X
	.byte  	35		// 0x62  'b'   : _ABI_L | _ABI_X
	.byte  	35		// 0x63  'c'   : _ABI_L | _ABI_X
	.byte  	35		// 0x64  'd'   : _ABI_L | _ABI_X
	.byte  	35		// 0x65  'e'   : _ABI_L | _ABI_X
	.byte  	35		// 0x66  'f'   : _ABI_L | _ABI_X
	.byte  	33		// 0x67  'g'   : _ABI_L
	.byte  	33		// 0x68  'h'   : _ABI_L
	.byte  	33		// 0x69  'i'   : _ABI_L
	.byte  	33		// 0x6A  'j'   : _ABI_L
	.byte  	33		// 0x6B  'k'   : _ABI_L
	.byte  	33		// 0x6C  'l'   : _ABI_L
	.byte  	33		// 0x6D  'm'   : _ABI_L
	.byte  	33		// 0x6E  'n'   : _ABI_L
	.byte  	33		// 0x6F  'o'   : _ABI_L
	.byte  	33		// 0x70  'p'   : _ABI_L
	.byte  	33		// 0x71  'q'   : _ABI_L
	.byte  	33		// 0x72  'r'   : _ABI_L
	.byte  	33		// 0x73  's'   : _ABI_L
	.byte  	33		// 0x74  't'   : _ABI_L
	.byte  	33		// 0x75  'u'   : _ABI_L
	.byte  	33		// 0x76  'v'   : _ABI_L
	.byte  	33		// 0x77  'w'   : _ABI_L
	.byte  	33		// 0x78  'x'   : _ABI_L
	.byte  	33		// 0x79  'y'   : _ABI_L
	.byte  	33		// 0x7A  'z'   : _ABI_L
	.byte  	4		// 0x7B  '{'   : _ABI_P
	.byte  	4		// 0x7C  '|'   : _ABI_P
	.byte  	4		// 0x7D  '}'   : _ABI_P
	.byte  	4		// 0x7E  '~'   : _ABI_P
	.byte  	128		// 0x7F  DEL   : _ABI_C
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
	.byte  	0		//
