/*************************************************************************************************/
/*!
 *  \file
 *
 *  \brief      Baseband driver interface file.
 *
 *  Copyright (c) 2016-2018 Arm Ltd. All Rights Reserved.
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

#ifndef BB_DRV_H
#define BB_DRV_H

#include "wsf_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/

/*! \addtogroup BB_DRV_INIT
 *  \{
 *  This section contains driver routines which initialize as well as enable the sleep mode
 *  of the BB hardware.
 */

/*************************************************************************************************/
/*!
 *  \brief      Initialize the baseband driver.
 *
 *  \return     None.
 *
 *  One-time initialization of baseband resources. This routine can be used to setup baseband
 *  resources, load RF trim parameters and execute RF calibrations and seed the random number
 *  generator.
 *
 *  This routine should block until the BB hardware is completely initialized.
 */
/*************************************************************************************************/
void BbDrvInit(void);

/*************************************************************************************************/
/*!
 *  \brief      Enable the BB hardware.
 *
 *  \return     None.
 *
 *  This routine brings the BB hardware out of low power (enable power and clocks) just before a
 *  first BB operation is executed.
 */
/*************************************************************************************************/
void BbDrvEnable(void);

/*************************************************************************************************/
/*!
 *  \brief      Disable the BB hardware.
 *
 *  \return     None.
 *
 *  This routine signals the BB hardware to go into low power (disable power and clocks) after all
 *  BB operations have been disabled.
 */
/*************************************************************************************************/
void BbDrvDisable(void);

/*************************************************************************************************/
/*!
 *  \brief      Get version codes.
 *
 *  \param      pBbVer      If non-NULL, return BB hardware version.
 *  \param      pPhyVer     If non-NULL, return PHY hardware version.
 *
 *  \return     None.
 *
 *  Interrogate the HW for version codes.
 */
/*************************************************************************************************/
void BbDrvGetVersions(uint32_t *pBbVer, uint32_t *pPhyVer);

/*! \} */    /* BB_DRV_INIT */

/*! \addtogroup BB_DRV_CLOCK
 *  \{
 *  This section contains driver routines related to the BB clock.
 */

/*************************************************************************************************/
/*!
 *  \brief      Get the current BB clock value.
 *
 *  \return     Current BB clock value.
 *
 *  This routine reads the current value from the BB clock and returns its value.  The clock should
 *  increment at the rate BB_CLK_RATE_HZ (wrapping as appropriate) whenever the BB is enabled.
 */
/*************************************************************************************************/
uint32_t BbDrvGetCurrentTime(void);

/*************************************************************************************************/
/*!
 *  \brief      Get the current FRC time.
 *
 *  \param      pTime   Pointer to return the current time.
 *
 *  \return     TRUE if time is valid, FALSE otherwise.
 *
 *  Get the current FRC time.
 *
 *  \note       FRC is limited to the same bit-width as the BB clock. Return value is available
 *              only when the BB is active.
 */
/*************************************************************************************************/
bool_t BbDrvGetTimestamp(uint32_t *pTime);

uint16_t BbDrvGetSleepClockAccuracy(void);
uint32_t BbDrvGetStartTimestamp(void);
uint32_t BbDrvGetEndTimestamp(void);
uint32_t BbDrvConvertUsToTicks(uint32_t us);
uint32_t BbDrvConvertTicksToUs(uint32_t ticks);

/*! \} */    /* BB_DRV_CLOCK */

#ifdef __cplusplus
};
#endif

#endif /* BB_DRV_H */
