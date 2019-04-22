/*************************************************************************************************/
/*!
 *  \file
 *
 *  \brief  Stack configuration.
 *
 *  Copyright (c) 2009-2018 Arm Ltd. All Rights Reserved.
 *  Arm Ltd. confidential and proprietary.
 *
 *  IMPORTANT.  Your use of this file is governed by a Software License Agreement
 *  ("Agreement") that must be accepted in order to download or otherwise receive a
 *  copy of this file.  You may not use or copy this file for any purpose other than
 *  as described in the Agreement.  If you do not agree to all of the terms of the
 *  Agreement do not use this file and delete all copies in your possession or control;
 *  if you do not have a copy of the Agreement, you must contact Arm Ltd. prior
 *  to any use, copying or further distribution of this software.
 */
/*************************************************************************************************/
#ifndef CFG_STACK_H
#define CFG_STACK_H


#ifdef __cplusplus
extern "C" {
#endif

/*! \addtogroup STACK_INIT
 *  \{ */

/**************************************************************************************************
  STACK VERSION
**************************************************************************************************/

/*! \brief Stack release version number */
#define STACK_VERSION         ((const char *)"r2p3-02rel0\n")

/**************************************************************************************************
  HCI
**************************************************************************************************/

/** \name HCI Vendor Specific targets
 *
 */
/**@{*/
#define HCI_VS_GENERIC        0
#define HCI_VS_EMM            1

/*! \brief Vendor specific target configuration */
#ifndef HCI_VS_TARGET
#define HCI_VS_TARGET HCI_VS_GENERIC
#endif
/**@}*/

/** \name HCI Tx Data Tailroom
 * Extra byte allocation required for LL operations (i.e. MIC) in single-chip implementation
 */
/**@{*/
#ifndef HCI_TX_DATA_TAILROOM
/*! \brief Tx data tailroom. */
#define HCI_TX_DATA_TAILROOM  0
#endif
/**@}*/

/**************************************************************************************************
  DM
**************************************************************************************************/

/** \name DM Configuration
 *  DM build-time configuration parameters
 */
/**@{*/
/*! \brief Maximum number of connections */
#ifndef DM_CONN_MAX
#define DM_CONN_MAX           3
#endif

/*! \brief Maximum number of periodic advertising synchronizations */
#ifndef DM_SYNC_MAX
#define DM_SYNC_MAX           1
#endif

/*! \brief Number of supported advertising sets: must be set to 1 for legacy advertising */
#ifndef DM_NUM_ADV_SETS
#define DM_NUM_ADV_SETS       1
#endif

/*! \brief Number of scanner and initiator PHYs (LE 1M, LE 2M and LE Coded): must be set to 1 for
    legacy scanner and initiator */
#ifndef DM_NUM_PHYS
#define DM_NUM_PHYS           1
#endif
/**@}*/

/**************************************************************************************************
  L2C
**************************************************************************************************/

/** \name L2CAP Configuration
 * L2CAP build-time configuration parameters
 */
/**@{*/
/*! \brief Maximum number of connection oriented channels */
#ifndef L2C_COC_CHAN_MAX
#define L2C_COC_CHAN_MAX      8
#endif

/*! \brief Maximum number of connection oriented channel registered clients */
#ifndef L2C_COC_REG_MAX
#define L2C_COC_REG_MAX       4
#endif
/**@}*/

/**************************************************************************************************
  ATT
**************************************************************************************************/

/** \name ATT Configuration
 * ATT build-time configuration parameters
 */
/**@{*/
/*! \brief Maximum number of simultanous ATT notifications */
#ifndef ATT_NUM_SIMUL_NTF
#define ATT_NUM_SIMUL_NTF     1
#endif
/**@}*/

/**************************************************************************************************
  SMP
**************************************************************************************************/


/*************************************************************************************************/
/*!
*  \brief  Get Stack version number.
*
*  \param  pVersion  output parameter for version number.
*
*  \return None.
*/
/*************************************************************************************************/
void StackGetVersionNumber(const char **pVersion);

/*! \} */    /* STACK_INIT */

#ifdef __cplusplus
};
#endif

#endif /* CFG_STACK_H */
