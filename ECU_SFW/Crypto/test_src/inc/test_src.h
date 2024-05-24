#ifndef _TEST_SOURCE_H_
#define _TEST_SOURCE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "fsl_debug_console.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libaursa.h"
#include "aursatype.h"
#include <assert.h>
#include "aesconfig.h"
#include "cipher.h"
#include "sample.h"


#ifdef _MSC_VER
#include <basetsd.h>
typedef UINT32 uint32_t;
#else
#include <inttypes.h>
#endif


//rsa 2048
#define KEY_LEN            256

/**
 *  
 * @brief   AES CTR 128 Enc/Dec Define
 * 
 */
#define MD_BUF_SZ          10240U //10240U
#define BLOCK_SIZE         MD_BUF_SZ
#define FIRST_LEN          16
#define SECOND_LEN         (MD_BUF_SZ - FIRST_LEN)
#define ENC_DEC_KEY_SIZE   32
#define ENC_DEC_IV_SIZE    16

/**
 *  
 * @brief   Sflash format Define
 * 
 */
#define META_INFO1         0x5A
#define META_INFO2         0x5A
#define SIG_INFO1          0x6A
#define SIG_INFO2          0x6A
#define META_RESERVED      0xAA
#define HEADER_LENGTH      16
#define MAC_SIZE	       32
#define SIGN_SIZE          256

/**
 *  
 * @brief   Secure Boot size Define
 * 
 */
#define TEST_BOOTLEN       512


#define HASH_CHECK      0
#define PARSING_TEST    1
#define UNIT_TEST       1
#define DBG_PRINT_USE   1

#define GEN_MESSAGE     1
#if GEN_MESSAGE
	#define GEN_ENCMSG         1
	#define GEN_DECMSG         0	
	#define GEN_SIGNMSG        1
    #define GEN_HMACMSG        1
	#define GEN_ENCKEY         0
	#define PARSING_ENC        1
#endif
#define FAIL            1
#define SUCCESS         0            

#if DBG_PRINT_USE
    #define dbg_printf DbgConsole_Printf
#else
    #define dbg_printf(fmt_s, ...)
#endif


/** 
 * 
 * @brief   SFLASH File Format struct
 * @details Header + Body + Signature \n
 *          Header Format struct
*/
typedef struct header_format {
	uint8_t  meta_inform[2]      ;
	uint16_t header_len          ;
	uint8_t  enc_key_index       ;
	uint8_t  hmac_key_index      ;
	uint32_t firm_version        ;
	uint32_t firm_size           ;
	uint8_t  reserve_use[2]      ;
} client_header;

/** 
 * 
 * @brief   SFLASH File Format struct
 * @details Header + Body + Signature \n
 *          Body (Block Format struct)
*/
typedef struct block_format {
	uint8_t  counter_data        ;
	uint8_t  hmac_data[MAC_SIZE] ;		//H-MAC 
	uint8_t  *app_data           ;  	//Encription Data
} block_body;

/** 
 * 
 * @brief   SFLASH File Format struct
 * @details Header + Body + Signature \n
 *          Body (Body Format struct)
*/
typedef struct body_format {
	uint8_t  total_counter       ;
	block_body block_no[2]       ;
	uint8_t  *total_app_data     ;  	//Total Encription Data	
} client_body;

/**
 * 
 * @brief   SFLASH File Format struct
 * @details Header + Body + Signature \n
 *          Signature (Signature Format struct)
*/
typedef struct sign_format {
	uint8_t  _inform[2]          ;	
	uint8_t  _data[SIGN_SIZE]    ;
} client_sign;


int Test_Fucntion_Operation(void);

int test_make_secureboot(uint8_t* enc_buf, int buf_length, uint8_t* sign_buf);
int test_check_secureboot(uint8_t* enc_buf, int buf_length, uint8_t* sign_buf);

#ifdef __cplusplus
}
#endif

#endif
