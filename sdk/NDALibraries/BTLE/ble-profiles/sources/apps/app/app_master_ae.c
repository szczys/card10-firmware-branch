/*************************************************************************************************/
/*!
 *  \file
 *
 *  \brief  Application framework module for extended master.
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

#include "wsf_types.h"
#include "wsf_trace.h"
#include "dm_api.h"
#include "app_api.h"
#include "app_main.h"

/*************************************************************************************************/
/*!
 *  \brief  Check if current scanning mode is extended scanning.
 *
 *  \return TRUE if extended scanning mode. FALSE, otherwise.
 */
/*************************************************************************************************/
static bool_t appMasterExtScanMode(void)
{
  /* if DM extended scanning */
  if (DmScanModeExt())
  {
    /* if first time since last power-on or reset */
    if (appMasterCb.scanMode == APP_SCAN_MODE_NONE)
    {
      /* set scanning mode to extended */
      appMasterCb.scanMode = APP_SCAN_MODE_EXT;

      return TRUE;
    }
  }

  if (appMasterCb.scanMode == APP_SCAN_MODE_EXT)
  {
    return TRUE;
  }

  APP_TRACE_WARN0("Invalid DM scanning mode; mode configured as legacy");

  return FALSE;
}

/*************************************************************************************************/
/*!
 *  \brief  Start scanning.   A scan is performed using the given scanner PHYs, discoverability
 *          mode, scan type, duration, and period.
 *
 *  \param  scanPhys  Scanner PHYs.
 *  \param  mode      Discoverability mode.
 *  \param  pScanType Scan type array.
 *  \param  duration  The scan duration, in milliseconds.  If set to zero or both duration and
 *                    period set to non-zero, scanning will continue until DmExtScanStop() is
 *                    called.
 *  \param  period    The scan period, in 1.28 sec units.  Set to zero to disable periodic scanning.
 *
 *  \return None.
*/
/*************************************************************************************************/
void AppExtScanStart(uint8_t scanPhys, uint8_t mode, const uint8_t *pScanType, uint16_t duration,
                     uint16_t period)
{
  uint8_t  i;                         /* scanPhy bit position */
  uint8_t  idx;                       /* array index */
  uint16_t scanInterval[DM_NUM_PHYS];
  uint16_t scanWindow[DM_NUM_PHYS];
  uint8_t  scanType[DM_NUM_PHYS];

  if (appMasterExtScanMode())
  {
    for (i = 0, idx = 0; (i < 8) && (idx < DM_NUM_PHYS); i++)
    {
      if (scanPhys & (1 << i))
      {
        scanInterval[idx] = pAppExtMasterCfg->scanInterval[i];
        scanWindow[idx] = pAppExtMasterCfg->scanWindow[i];
        scanType[idx] = pScanType[i];
        idx++;
      }
    }

    DmScanSetInterval(scanPhys, scanInterval, scanWindow);

    DmScanStart(scanPhys, mode, scanType, TRUE, duration, period);
  }
}

/*************************************************************************************************/
/*!
 *  \brief  Stop scanning.
 *
 *  \return None.
 */
/*************************************************************************************************/
void AppExtScanStop(void)
{
  if (appMasterExtScanMode())
  {
    /* stop address resolution */
    appMasterCb.inProgress = FALSE;

    DmScanStop();
  }
}

/*************************************************************************************************/
/*!
 *  \brief  Synchronize with periodic advertising from the given advertiser, and start receiving
 *          periodic advertising packets.
 *
 *  \param  advSid        Advertising SID.
 *  \param  advAddrType   Advertiser address type.
 *  \param  pAdvAddr      Advertiser address.
 *  \param  skip          Number of periodic advertising packets that can be skipped after
 *                        successful receive.
 *  \param  syncTimeout   Synchronization timeout.
 *
 *  \return Sync identifier.
 */
/*************************************************************************************************/
dmSyncId_t AppSyncStart(uint8_t advSid, uint8_t advAddrType, const uint8_t *pAdvAddr, uint16_t skip,
                        uint16_t syncTimeout)
{
  if (appMasterExtScanMode())
  {
    return DmSyncStart(advSid, advAddrType, pAdvAddr, skip, syncTimeout);
  }

  /* wrong scan mode */
  return DM_SYNC_ID_NONE;
}

/*************************************************************************************************/
/*!
 *  \brief  Stop reception of the periodic advertising identified by the given sync identifier.
 *
 *  \param  syncId        Sync identifier.
 *
 *  \return None.
 */
/*************************************************************************************************/
void AppSyncStop(dmSyncId_t syncId)
{
  if (appMasterExtScanMode())
  {
    DmSyncStop(syncId);
  }
}

/*************************************************************************************************/
/*!
 *  \brief  Open a connection to a peer device with the given address.
 *
 *  \param  initPhys  Initiator PHYs.
 *  \param  addrType  Address type.
 *  \param  pAddr     Peer device address.
 *  \param  dbHdl     Device database handle.
 *
 *  \return Connection identifier.
 */
/*************************************************************************************************/
dmConnId_t AppExtConnOpen(uint8_t initPhys, uint8_t addrType, uint8_t *pAddr, appDbHdl_t dbHdl)
{
  if (appMasterExtScanMode())
  {
    return appConnOpen(initPhys, addrType, pAddr, dbHdl);
  }

  /* wrong connect mode */
  return DM_CONN_ID_NONE;
}
