/*************************************************************************************************/
/*!
 *  \file
 *
 *  \brief  Example GATT and GAP service implementations.
 *
 *  Copyright (c) 2009-2018 Arm Ltd. All Rights Reserved.
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

/* card10:
 * copied from lib/sdk/Libraries/BTLE/stack/ble-profiles/sources/services/svc_core.c
 */
#include "wsf_types.h"
#include "att_api.h"
#include "att_uuid.h"
#include "util/bstream.h"
#include "svc_core.h"
#include "svc_ch.h"
#include "svc_cfg.h"
#include "wsf_assert.h"

/**************************************************************************************************
  Macros
**************************************************************************************************/

/*! Characteristic read permissions */
#ifndef CORE_SEC_PERMIT_READ
#define CORE_SEC_PERMIT_READ SVC_SEC_PERMIT_READ
#endif

/*! Characteristic write permissions */
#ifndef CORE_SEC_PERMIT_WRITE
#define CORE_SEC_PERMIT_WRITE SVC_SEC_PERMIT_WRITE
#endif

/*! Default device name */
#define CORE_DEFAULT_DEV_NAME       "card10"

/*! Length of default device name */
#define CORE_DEFAULT_DEV_NAME_LEN   6

/**************************************************************************************************
 GAP group
**************************************************************************************************/

/* service */
static const uint8_t gapValSvc[] = {UINT16_TO_BYTES(ATT_UUID_GAP_SERVICE)};
static const uint16_t gapLenSvc = sizeof(gapValSvc);

/* device name characteristic */
static const uint8_t gapValDnCh[] = {ATT_PROP_READ | ATT_PROP_WRITE, UINT16_TO_BYTES(GAP_DN_HDL), UINT16_TO_BYTES(ATT_UUID_DEVICE_NAME)};
static const uint16_t gapLenDnCh = sizeof(gapValDnCh);

/* device name */
static uint8_t gapValDn[ATT_DEFAULT_PAYLOAD_LEN] = CORE_DEFAULT_DEV_NAME;
static uint16_t gapLenDn = CORE_DEFAULT_DEV_NAME_LEN;

/* appearance characteristic */
static const uint8_t gapValApCh[] = {ATT_PROP_READ, UINT16_TO_BYTES(GAP_AP_HDL), UINT16_TO_BYTES(ATT_UUID_APPEARANCE)};
static const uint16_t gapLenApCh = sizeof(gapValApCh);

/* appearance */
static uint8_t gapValAp[] = {UINT16_TO_BYTES(CH_APPEAR_UNKNOWN)};
static const uint16_t gapLenAp = sizeof(gapValAp);

/* central address resolution characteristic */
static const uint8_t gapValCarCh[] = {ATT_PROP_READ, UINT16_TO_BYTES(GAP_CAR_HDL), UINT16_TO_BYTES(ATT_UUID_CAR)};
static const uint16_t gapLenCarCh = sizeof(gapValCarCh);

/* central address resolution */
static uint8_t gapValCar[] = {FALSE};
static const uint16_t gapLenCar = sizeof(gapValCar);
#if 0
/* TODO card10:
 * Enable these if "privacy" is enabled. See svc_core.h lien 38 */

/* resolvable private address only characteristic */
static const uint8_t gapValRpaoCh[] = {ATT_PROP_READ, UINT16_TO_BYTES(GAP_RPAO_HDL), UINT16_TO_BYTES(ATT_UUID_RPAO)};
static const uint16_t gapLenRpaoCh = sizeof(gapValRpaoCh);

/* resolvable private address only */
static uint8_t gapValRpao[] = {0};
static const uint16_t gapLenRpao = sizeof(gapValRpao);
#endif

/* Attribute list for GAP group */
static const attsAttr_t gapList[] =
{
  {
    attPrimSvcUuid,
    (uint8_t *) gapValSvc,
    (uint16_t *) &gapLenSvc,
    sizeof(gapValSvc),
    0,
    ATTS_PERMIT_READ
  },
  {
    attChUuid,
    (uint8_t *) gapValDnCh,
    (uint16_t *) &gapLenDnCh,
    sizeof(gapValDnCh),
    0,
    ATTS_PERMIT_READ
  },
  {
    attDnChUuid,
    gapValDn,
    &gapLenDn,
    sizeof(gapValDn),
    (ATTS_SET_VARIABLE_LEN | ATTS_SET_WRITE_CBACK),
    (ATTS_PERMIT_READ | CORE_SEC_PERMIT_WRITE)
  },
  {
    attChUuid,
    (uint8_t *) gapValApCh,
    (uint16_t *) &gapLenApCh,
    sizeof(gapValApCh),
    0,
    ATTS_PERMIT_READ
  },
  {
    attApChUuid,
    gapValAp,
    (uint16_t *) &gapLenAp,
    sizeof(gapValAp),
    0,
    ATTS_PERMIT_READ
  },
  {
    attChUuid,
    (uint8_t *) gapValCarCh,
    (uint16_t *) &gapLenCarCh,
    sizeof(gapValCarCh),
    0,
    ATTS_PERMIT_READ
  },
  {
    attCarChUuid,
    gapValCar,
    (uint16_t *) &gapLenCar,
    sizeof(gapValCar),
    0,
    ATTS_PERMIT_READ
  },
#if 0
/* TODO card10:
 * Enable these if "privacy" is enabled. See svc_core.h lien 38 */
  {
    attChUuid,
    (uint8_t *) gapValRpaoCh,
    (uint16_t *) &gapLenRpaoCh,
    sizeof(gapValRpaoCh),
    0,
    ATTS_PERMIT_READ
  },
  {
    attRpaoChUuid,
    gapValRpao,
    (uint16_t *) &gapLenRpao,
    sizeof(gapValRpao),
    0,
    ATTS_PERMIT_READ
  }
#endif
};

/* GAP group structure */
static attsGroup_t svcGapGroup =
{
  NULL,
  (attsAttr_t *) gapList,
  NULL,
  NULL,
  GAP_START_HDL,
  GAP_END_HDL
};

WSF_CT_ASSERT(((sizeof(gapList) / sizeof(gapList[0])) == GAP_END_HDL - GAP_START_HDL + 1));
/**************************************************************************************************
 GATT group
**************************************************************************************************/

/* service */
static const uint8_t gattValSvc[] = {UINT16_TO_BYTES(ATT_UUID_GATT_SERVICE)};
static const uint16_t gattLenSvc = sizeof(gattValSvc);

/* service changed characteristic */
static const uint8_t gattValScCh[] = {ATT_PROP_INDICATE, UINT16_TO_BYTES(GATT_SC_HDL), UINT16_TO_BYTES(ATT_UUID_SERVICE_CHANGED)};
static const uint16_t gattLenScCh = sizeof(gattValScCh);

/* service changed */
static const uint8_t gattValSc[] = {UINT16_TO_BYTES(0x0001), UINT16_TO_BYTES(0xFFFF)};
static const uint16_t gattLenSc = sizeof(gattValSc);

/* service changed client characteristic configuration */
static uint8_t gattValScChCcc[] = {UINT16_TO_BYTES(0x0000)};
static const uint16_t gattLenScChCcc = sizeof(gattValScChCcc);

/* Attribute list for GATT group */
static const attsAttr_t gattList[] =
{
  {
    attPrimSvcUuid,
    (uint8_t *) gattValSvc,
    (uint16_t *) &gattLenSvc,
    sizeof(gattValSvc),
    0,
    ATTS_PERMIT_READ
  },
  {
    attChUuid,
    (uint8_t *) gattValScCh,
    (uint16_t *) &gattLenScCh,
    sizeof(gattValScCh),
    0,
    ATTS_PERMIT_READ
  },
  {
    attScChUuid,
    (uint8_t *) gattValSc,
    (uint16_t *) &gattLenSc,
    sizeof(gattValSc),
    0,
    0
  },
  {
    attCliChCfgUuid,
    gattValScChCcc,
    (uint16_t *) &gattLenScChCcc,
    sizeof(gattValScChCcc),
    ATTS_SET_CCC,
    (ATTS_PERMIT_READ | CORE_SEC_PERMIT_WRITE)
  },
};

/* GATT group structure */
static attsGroup_t svcGattGroup =
{
  NULL,
  (attsAttr_t *) gattList,
  NULL,
  NULL,
  GATT_START_HDL,
  GATT_END_HDL
};

WSF_CT_ASSERT(((sizeof(gattList) / sizeof(gattList[0])) == GATT_END_HDL - GATT_START_HDL + 1));

/*************************************************************************************************/
/*!
 *  \brief  Add the services to the attribute server.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SvcCoreAddGroup(void)
{
  AttsAddGroup(&svcGapGroup);
  AttsAddGroup(&svcGattGroup);
}

/*************************************************************************************************/
/*!
 *  \brief  Remove the services from the attribute server.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SvcCoreRemoveGroup(void)
{
  AttsRemoveGroup(GAP_START_HDL);
  AttsRemoveGroup(GATT_START_HDL);
}

/*************************************************************************************************/
/*!
 *  \brief  Register callbacks for the service.
 *
 *  \param  readCback   Read callback function.
 *  \param  writeCback  Write callback function.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SvcCoreGapCbackRegister(attsReadCback_t readCback, attsWriteCback_t writeCback)
{
  svcGapGroup.readCback = readCback;
  svcGapGroup.writeCback = writeCback;
}

/*************************************************************************************************/
/*!
 *  \brief  Register callbacks for the service.
 *
 *  \param  readCback   Read callback function.
 *  \param  writeCback  Write callback function.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SvcCoreGattCbackRegister(attsReadCback_t readCback, attsWriteCback_t writeCback)
{
  svcGattGroup.readCback = readCback;
  svcGattGroup.writeCback = writeCback;
}

/*************************************************************************************************/
/*!
 *  \brief  Update the central address resolution attribute value.
 *
 *  \param  value   New value.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SvcCoreGapCentAddrResUpdate(bool_t value)
{
  gapValCar[0] = value;
}

/*************************************************************************************************/
/*!
 *  \brief  Add the Resolvable Private Address Only (RPAO) characteristic to the GAP service.
 *          The RPAO characteristic should be added only when DM Privacy is enabled.
 *
 *  \return None.
 */
/*************************************************************************************************/
void SvcCoreGapAddRpaoCh(void)
{
  /* if RPAO characteristic not already in GAP service */
  if (svcGapGroup.endHandle < GAP_RPAO_HDL)
  {
    svcGapGroup.endHandle = GAP_RPAO_HDL;
  }
}
