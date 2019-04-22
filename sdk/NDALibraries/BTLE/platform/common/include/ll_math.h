/*************************************************************************************************/
/*!
 *  \file
 *
 *  \brief  Link Layer math utilities.
 *
 *  Copyright (c) 2013-2018 Arm Ltd. All Rights Reserved.
 *  ARM Ltd. confidential and proprietary.
 *
 *  IMPORTANT.  Your use of this file is governed by a Software License Agreement
 *  ("Agreement") that must be accepted in order to download or otherwise receive a
 *  copy of this file.  You may not use or copy this file for any purpose other than
 *  as described in the Agreement.  If you do not agree to all of the terms of the
 *  Agreement do not use this file and delete all copies in your possession or control;
 *  if you do not have a copy of the Agreement, you must contact ARM Ltd. prior
 *  to any use, copying or further distribution of this software.
 */
/*************************************************************************************************/
#ifndef LL_MATH_H
#define LL_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "wsf_types.h"

/**************************************************************************************************
  Macros
**************************************************************************************************/

/*! \brief      Binary divide with 1,000 divisor (n[max]=7,999). */
#define LL_MATH_DIV_10E3(n)     (((n) * UINT32_C(536871)) >> 29)

/*! \brief      Binary divide with 1,000,000 divisor (n[max]=0xFFFFFFFF). */
#define LL_MATH_DIV_10E6(n)     ((uint32_t)(((uint64_t)(n) * UINT64_C(4295)) >> 32))

/*! \brief      Binary divide with 10 divisor (n[max]=0xFFFFFFFF). */
#define LL_MATH_DIV_10(n)       ((uint32_t)(((uint64_t)(n) * UINT64_C(419431)) >> 22))

/*! \brief      Binary divide with 27 divisor (n[max]=55,295). */
#define LL_MATH_DIV_27(n)       (((n) * UINT32_C(77673)) >> 21)

/*! \brief      Binary divide with 37 divisor (n[max]=75,776). */
#define LL_MATH_DIV_37(n)       (((n) * UINT32_C(56680)) >> 21)

/*! \brief      Binary modulo 37. */
#define LL_MATH_MOD_37(n)       ((n) - (LL_MATH_DIV_37(n) * 37))

/*! \brief      Binary divide with 1250 divisor (n[max]=0xFFFFFFFF). */
#define LL_MATH_DIV_1250(n)     ((uint32_t)(((uint64_t)(n) * UINT64_C(1717987)) >> 31))

/*! \brief      Binary divide with 625 divisor (n[max]=0xFFFFFFFF). */
#define LL_MATH_DIV_625(n)      ((uint32_t)(((uint64_t)(n) * UINT64_C(1717987)) >> 30))

/*! \brief      Binary divide with 30 divisor (n[max]=0xFFFFFFFF). */
#define LL_MATH_DIV_30(n)       ((uint32_t)(((uint64_t)(n) * UINT64_C(286331154)) >> 33))

/*! \brief      Binary divide with 300 divisor (n[max]=0x3FFFFFFF). */
#define LL_MATH_DIV_300(n)      ((uint32_t)(((uint64_t)(n) * UINT64_C(14660155038)) >> 42))

/*! \brief      Returns the ceiling of a divide. */
#define LL_MATH_CEIL(n,d)       ((((n) + (d) - 1)) / (d))

/*! \brief      Returns the floor of a divide. */
#define LL_MATH_FLOOR(n,d)      ((n) / (d))

/**************************************************************************************************
  Data Types
**************************************************************************************************/

/*! \brief      ECC service callback. */
typedef void (*LlMathEccServiceCback_t)(uint8_t op);

/*! \brief      ECC operations. */
enum
{
  LL_MATH_ECC_OP_GENERATE_P256_KEY_PAIR,   /*!< Generate P-256 key pair. */
  LL_MATH_ECC_OP_GENERATE_DH_KEY           /*!< Generate Diffie-Hellman key. */
};

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/

/*************************************************************************************************/
/*!
 *  \brief  Generate random number.
 *
 *  \return 32-bit random number.
 */
/*************************************************************************************************/
uint32_t LlMathRandNum(void);

/*************************************************************************************************/
/*!
 *  \brief  Calculate AES ECB.
 *
 *  \param  pKey        Encryption key.
 *  \param  pOut        Output data.
 *  \param  pIn         Input data.
 *
 *  \return None.
 */
/*************************************************************************************************/
void LlMathAesEcb(const uint8_t *pKey, uint8_t *pOut, const uint8_t *pIn);

/*************************************************************************************************/
/*!
 *  \brief  Set service callback for ECC generation.
 *
 *  \param  cback   Callback to invoke when driver needs servicing.
 *
 *  \return None.
 */
/*************************************************************************************************/
void LlMathEccSetServiceCback(LlMathEccServiceCback_t cback);

/*************************************************************************************************/
/*!
 *  \brief  Generate a P-256 public key pair.
 *
 *  \param  pPrivKey    Return pointer for private key.
 *  \param  pPubKey     Return pointer for public key.
 *
 *  \return None.
 */
/*************************************************************************************************/
void LlMathEccGenerateP256KeyPair(uint8_t *pPrivKey, uint8_t *pPubKey);

/*************************************************************************************************/
/*!
 *  \brief  Start generating P-256 key pair.
 *
 *  \return None.
 */
/*************************************************************************************************/
void LlMathEccGenerateP256KeyPairStart(void);

/*************************************************************************************************/
/*!
 *  \brief  Start generating P-256 public key with a specified private key.
 *
 *  \param  pPrivKey      Private key.
 *
 *  \return None.
 */
/*************************************************************************************************/
void LlMathEccGenerateP256PublicKeyStart(const uint8_t *pPrivKey);

/*************************************************************************************************/
/*!
 *  \brief  Continue generating P-256 key pair.
 *
 *  \return TRUE if key generation complete.
 */
/*************************************************************************************************/
bool_t LlMathEccGenerateP256KeyPairContinue(void);

/*************************************************************************************************/
/*!
 *  \brief  Get results from generating P-256 key pair.
 *
 *  \param  pPubKey     Storage for public key.
 *  \param  pPrivKey    Storage for private key.
 *
 *  \return None.
 */
/*************************************************************************************************/
void LlMathEccGenerateP256KeyPairComplete(uint8_t *pPubKey, uint8_t *pPrivKey);

/*************************************************************************************************/
/*!
 *  \brief  Generate a Diffie-Hellman key.
 *
 *  \param  pPubKey     Public key.
 *  \param  pPrivKey    Private key.
 *  \param  pDhKey      Return pointer for computed DH Key.
 *
 *  \return False if there is an error with the public key, True if success.
 */
/*************************************************************************************************/
bool_t LlMathEccGenerateDhKey(const uint8_t *pPubKey, const uint8_t *pPrivKey, uint8_t *pDhKey);

/*************************************************************************************************/
/*!
 *  \brief  Start generating Diffie-Hellman key.
 *
 *  \param  pPubKey     Public key.
 *  \param  pPrivKey    Private key.
 *
 *  \return None.
 */
/*************************************************************************************************/
void LlMathEccGenerateDhKeyStart(const uint8_t *pPubKey, const uint8_t *pPrivKey);

/*************************************************************************************************/
/*!
 *  \brief  Continue generating Diffie-Hellman key.
 *
 *  \return TRUE if Diffie-Hellman key generation complete.
 */
/*************************************************************************************************/
bool_t LlMathEccGenerateDhKeyContinue(void);

/*************************************************************************************************/
/*!
 *  \brief  Get results from generating Diffie-Hellman key.
 *
 *  \param  pDhKey      Storage for Diffie-Hellman key.
 *
 *  \return None.
 */
/*************************************************************************************************/
void LlMathEccGenerateDhKeyComplete(uint8_t *pDhKey);

/*************************************************************************************************/
/*!
 *  \brief  Return the number of bits which are set.
 *
 *  \param  num   Input parameter.
 *
 *  \return Number of bits which are set.
 */
/*************************************************************************************************/
uint8_t LlMathGetNumBitsSet(uint64_t num);

/*************************************************************************************************/
/*!
 *  \brief  Return result of a division.
 *
 *  \param  nu32        Numerator of size 32 bits.
 *  \param  de32        Denominator of size 32 bits.
 *
 *  \return Result of a division.
 */
/*************************************************************************************************/
uint32_t LlMathDivideUint32(uint32_t nu32, uint32_t de32);

#ifdef __cplusplus
};
#endif

#endif /* LL_API_H */
