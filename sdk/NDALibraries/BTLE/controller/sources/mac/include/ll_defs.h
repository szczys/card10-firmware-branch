/*************************************************************************************************/
/*!
 *  \file
 *
 *  \brief      Link layer constant definitions.
 *
 *  Copyright (c) 2013-2017 ARM Ltd. All Rights Reserved.
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

#ifndef LL_DEFS_H
#define LL_DEFS_H

#include "wsf_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************
  Constants
**************************************************************************************************/

/*** Version ***/

#define LL_VER_BT_CORE_SPEC_4_0     0x06    /*!< Bluetooth core specification 4.0 */
#define LL_VER_BT_CORE_SPEC_4_1     0x07    /*!< Bluetooth core specification 4.1 */
#define LL_VER_BT_CORE_SPEC_4_2     0x08    /*!< Bluetooth core specification 4.2 */
#define LL_VER_BT_CORE_SPEC_5_0     0x09    /*!< Bluetooth core specification 5.0 */

#define LL_COMP_ID_ARM              0x005F  /*!< ARM Ltd. company ID. */

/*** Common ***/

#define LL_RSSI_MIN                 -127    /*!< Minimum RSSI value. */
#define LL_RSSI_MAX                 20      /*!< Maximum RSSI value. */
#define LL_RSSI_NOT_AVAIL           127     /*!< RSSI is not available. */

#define LL_CRC_LEN                  3       /*!< CRC length. */
#define LL_AA_LEN                   4       /*!< Access address length. */
#define LL_PREAMBLE_LEN_1M          1       /*!< Preamble length (LE 1M PHY). */
#define LL_PREAMBLE_LEN_2M          2       /*!< Preamble length (LE 2M PHY). */
#define LL_PREAMBLE_LEN_CODED_BITS  10      /*!< Preamble length (LE Coded PHY). */
#define LL_CI_LEN_BITS              2       /*!< Coding indicator length (LE Coded PHY). */
#define LL_TERM1_LEN_BITS           3       /*!< TERM1 length (LE Coded PHY). */
#define LL_TERM2_LEN_BITS           3       /*!< TERM2 length (LE Coded PHY). */

#define LL_RAND_ADDR_TYPE_MASK      UINT64_C(0xC00000000000)    /*!< BD Random Address type mask. */
#define LL_RAND_ADDR_TYPE_STATIC    UINT64_C(0xC00000000000)    /*!< Static Random Address type. */
#define LL_RAND_ADDR_TYPE_RPA       UINT64_C(0x400000000000)    /*!< Resolvable Private Address type. */
#define LL_RAND_ADDR_TYPE_NRPA      UINT64_C(0x000000000000)    /*!< Non-Resolvable Private Address type. */

#define LL_MAX_NUM_PHYS             (3) /*!< \brief Maximum number of scanning or initiating PHYs */

/**
 * \brief PHY Definitions taken from LE Read PHY Commmand and LE Set PHY Command */
#define LL_PHY_LE_PREF_TX           (1) /*!< \brief Host preference for TX */
#define LL_PHY_LE_PREF_RX           (2) /*!< \brief Host preference for RX */

#define LL_PHY_LE_1M                (1) /*!< \brief LE 1M PHY */
#define LL_PHY_LE_2M                (2) /*!< \brief LE 2M PHY */
#define LL_PHY_LE_CODED             (3) /*!< \brief LE Coded PHY */
#define LL_PHY_LE_S8                (4) /*!< \brief LE Coded PHY S8 */
#define LL_PHY_LE_S2                (5) /*!< \brief LE Coded PHY S2 */

#define LL_PHY_LE_CODED_PREF_NONE   (0) /*!< \brief LE Coded PHY Options, no preference */
#define LL_PHY_LE_CODED_PREF_S2     (1) /*!< \brief LE Coded PHY Options, pefer S2 */
#define LL_PHY_LE_CODED_PREF_S8     (2) /*!< \brief LE Coded PHY Options, prefer S8 */

#define LL_PHY_LE_1M_BIT            (0x1) /*!< \brief LE 1M PHY bit mask */
#define LL_PHY_LE_2M_BIT            (0x2) /*!< \brief LE 2M PHY bit mask */
#define LL_PHY_LE_CODED_BIT         (0x4) /*!< \brief LE Coded PHY bit mask */

/**
 * \brief If defined, silently discards legacy advertisements. */
#undef LL_DISCARD_LEGACY_ADVERTISEMENTS /*!< \brief If defined, silently discards legacy advertisements. */

/*** Advertising PDU ***/

/*! \brief      Advertising channel PDU types. */
enum
{
  /* --- Core Spec 4.0 --- */
  LL_PDU_ADV_IND                = 0,    /*!< Connectable undirected advertising PDU. */
  LL_PDU_ADV_DIRECT_IND         = 1,    /*!< Connectable directed advertising PDU. */
  LL_PDU_ADV_NONCONN_IND        = 2,    /*!< Non-connectable undirected advertising PDU. */
  LL_PDU_SCAN_REQ               = 3,    /*!< Scan request PDU. */
  LL_PDU_SCAN_RSP               = 4,    /*!< Scan response PDU. */
  LL_PDU_CONNECT_IND            = 5,    /*!< Connect indication PDU. */
  LL_PDU_ADV_SCAN_IND           = 6,    /*!< Scannable undirected advertising PDU. */
  /* --- Core Spec 5.0 --- */
  LL_PDU_AUX_SCAN_REQ           = 3,    /*!< Auxiliary scan request PDU. */
  LL_PDU_AUX_CONNECT_REQ        = 5,    /*!< Auxiliary connect request PDU. */
  LL_PDU_ADV_EXT_IND            = 7,    /*!< Extended advertising PDU. */
  LL_PDU_AUX_ADV_IND            = 7,    /*!< Auxiliary advertising PDU. */
  LL_PDU_AUX_SCAN_RSP           = 7,    /*!< Auxiliary scan response PDU. */
  LL_PDU_AUX_SYNC_IND           = 7,    /*!< Auxiliary synchronize PDU. */
  LL_PDU_AUX_CHAIN_IND          = 7,    /*!< Auxiliary chain PDU. */
  LL_PDU_AUX_CONNECT_RSP        = 8,    /*!< Auxiliary connect response PDU. */
};

#define LL_SCAN_REQ_PDU_LEN     12      /*!< Size of a scan request PDU. */
#define LL_CONN_IND_PDU_LEN     34      /*!< Size of a connect indication PDU. */
#define LL_CONN_RSP_PDU_LEN     14      /*!< Size of an auxiliary connect response PDU. */

#define LL_CHAN_ADV_MIN_IDX     37      /*!< Minimum advertising channel index. */
#define LL_CHAN_ADV_MAX_IDX     39      /*!< Maximum advertising channel index. */
#define LL_NUM_CHAN_ADV         3       /*!< Total number of advertising channels. */

#define LL_ADVBU_MAX_LEN        31      /*!< Maximum advertising channel host data length. */
/***
 * Maximum advertising channel host data length.
 * \todo Need to readjust according to spec. */
#define LL_ADV_AUX_U_MAX_LEN    31

/*!
 * Maximum ACAD field length (63 less flags field).
 * \sa BLUETOOTH SPECIFICATION Version 5.0, Vol 6, Part B, Section 2.3.4 */
#define LL_ADVB_ACAD_MAX_LEN    (63-1)
#define LL_ADVB_MAX_LEN         39      /*!< Maximum advertising channel PDU length. */
#define LL_ADVB_MIN_LEN         (LL_ADVB_MAX_LEN - LL_ADVBU_MAX_LEN)    /*!< Minimum advertising channel packet length. */
#define LL_ADVB_MAX_TIME_1M     ((LL_BLE_US_PER_BYTE_1M * (LL_ADVB_MAX_LEN - LL_ADV_HDR_LEN)) + LL_MIN_PKT_TIME_US_1M)
                                        /*!< Maximum time for a 1M advertising channel PDU. */
#define LL_ADVB_MAX_TIME_2M     ((LL_BLE_US_PER_BYTE_2M * (LL_ADVB_MAX_LEN - LL_ADV_HDR_LEN)) + LL_MIN_PKT_TIME_US_2M)
                                        /*!< Maximum time for a 2M advertising channel PDU. */
#define LL_ADVB_MAX_TIME_S2     ((LL_BLE_US_PER_BYTE_CODED_S2 * (LL_ADVB_MAX_LEN - LL_ADV_HDR_LEN)) + LL_MIN_PKT_TIME_US_CODED_S2)
                                        /*!< Maximum time for a Coded S2 advertising channel PDU. */
#define LL_ADVB_MAX_TIME_S8     ((LL_BLE_US_PER_BYTE_CODED_S8 * (LL_ADVB_MAX_LEN - LL_ADV_HDR_LEN)) + LL_MIN_PKT_TIME_US_CODED_S8)
                                        /*!< Maximum time for a Coded S8 advertising channel PDU. */

#define LL_ADVB_PKT_MAX_USEC     LL_ADVB_MAX_TIME_1M /*!< Maximum time in microseconds for an advertising packet. */
/***
 * Maximum data channel PDU length.
 * \sa BLUETOOTH SPECIFICATION Version 5.0, Vol 6, Part B, Section 2.3 */
#define LL_ADV_AUX_MAX_LEN      258
#define LL_ADV_AUX_MIN_LEN      (LL_ADV_AUX_MAX_LEN - LL_ADV_AUX_U_MAX_LEN)    /*!< Minimum auxillary advertising packet length. */
#define LL_ADV_AUX_MAX_TIME_S8  (LL_BLE_US_PER_BYTE_CODED_S8 * LL_ADV_AUX_MAX_LEN)
#define LL_ADV_AUX_MIN_TIME_2M  (LL_BLE_US_PER_BYTE_2M * LL_ADV_AUX_MIN_LEN)
#define LL_ADV_AUX_PKT_MAX_USEC (LL_ADV_AUX_MAX_TIME_S8)  

#define LL_SCAN_REQ_MAX_USEC    ((8 * (LL_ADV_PREFIX_LEN + LL_SCAN_PREFIX_LEN)) + LL_MIN_PKT_TIME_US_1M)
                                                    /*!< Maximum time in microseconds for a scan request packet. */
#define LL_SCAN_RSP_MAX_USEC    LL_ADVB_MAX_TIME_1M /*!< Maximum time in microseconds for a scan response packet. */

#define LL_SCAN_MIN_TICKS       0x0004  /*! Minimum scan interval and window is 2.5 ms */
#define LL_SCAN_MAX_TICKS       0x4000  /*! Maximum scan interval and window is 10,240 ms */

/*! Time required to process aux ptr and reschedule a new BOD. */
#define LL_AUX_ADV_SCH_DELAY_USEC (0) /*< \todo Need to measure delay. */

/*! Minimum scan interval and window is 2.5 ms
 * \todo Determine minimum time for auxillary operation. */
#define LL_AUX_SCAN_MIN_TICKS   0x0004

/*! Maximum scan interval and window is 10,240 ms
 * \todo Determine maximum time for auxillary operation. */
#define LL_AUX_SCAN_MAX_TICKS   0x4000

#define LL_ADV_HDR_LEN          2       /*!< Advertising channel header length. */
#define LL_ADV_HDR_TYPE_OFFS    0       /*!< Advertising header type offset. */
#define LL_ADV_HDR_TYPE_MSK     0x0F    /*!< Advertising header type mask. */
#define LL_ADV_HDR_LEN_OFFS     1       /*!< Advertising header length offset. */
#define LL_ADV_HDR_LEN_MSK      0x3F    /*!< Advertising header length mask for 4.2. */
#define LL_ADV_EXT_HDR_LEN_MSK  0xFF    /*!< Advertising extension header length mask for 5.0. */
#define LL_ADV_PREFIX_LEN       6       /*!< Advertising PDU payload prefix length (AdvA). */
#define LL_SCAN_PREFIX_LEN      6       /*!< Scan request/response PDU payload prefix length (AdvA). */

#define LL_ADV_ACCESS_ADDR      UINT32_C(0x8E89BED6)    /*!< Advertising channel access address. */
#define LL_ADV_CRC_INIT         UINT32_C(0x555555)      /*!< Advertising CRC initial value. */

#define LL_DIR_ADV_INTER_TICKS  6       /*!< Advertising interval between directed advertising events (3.75 ms). */
#define LL_DIR_ADV_DUR_TICKS    2048    /*!< Maximum high duty cycle directed advertising duration (1.28 seconds). */

#define LL_ADV_EXT_HDR_MAX_LEN             (63)
#define LL_ADV_EXTHDRLEN_ADVMODE_LEN       (1)
#define LL_ADV_EXT_HDR_FLAGS_LEN           (1)
#define LL_ADV_EXT_HDR_ADVA_LEN            (6)
#define LL_ADV_EXT_HDR_TARGETA_LEN         (6)
#define LL_ADV_EXT_HDR_RFU_LEN             (1)
#define LL_ADV_EXT_HDR_ADI_LEN             (2)
#define LL_ADV_EXT_HDR_AUXPTR_LEN          (3)
#define LL_ADV_EXT_HDR_SYNCINFO_LEN        (18)
#define LL_ADV_EXT_HDR_TXPWR_LEN           (1)
#define LL_ADV_EXT_HDR_ACAD_MAX_LEN        (LL_ADV_EXT_HDR_MAX_LEN - LL_ADV_EXT_HDR_FLAGS_LEN)
#define LL_ADV_EXT_HDR_MINUS_ACAD_MAX_LEN  (38)
#define LL_ADV_DATA_MAX_LEN                (254)   /*!< Maximum AdvData length. */
#define LL_ADV_EXT_IND_MAX_LEN             (LL_ADV_HDR_LEN + LL_ADV_EXTHDRLEN_ADVMODE_LEN + LL_ADV_EXT_HDR_MINUS_ACAD_MAX_LEN - LL_ADV_EXT_HDR_SYNCINFO_LEN)   /*!< Maximum ADV_EXT_IND PDU length. */
#define LL_ADV_AUX_IND_MAX_LEN             (LL_ADV_HDR_LEN + LL_ADV_EXTHDRLEN_ADVMODE_LEN + LL_ADV_DATA_MAX_LEN)   /*!< Maximum AUX_ADV_IND or AUX_CHAIN_IND PDU length. */

#define LL_LLDATA_LEN                      (22)    /*!< LLData field structure length in CONNECT_IND and AUX_CONNECT_REQ PDU's payload. */

/*!< Extended advertising data operations */
#define LL_ADV_DATA_OP_FRAG_INTER          0x00    /*!< \brief Intermediate fragment */
#define LL_ADV_DATA_OP_FRAG_FIRST          0x01    /*!< \brief First fragment */
#define LL_ADV_DATA_OP_FRAG_LAST           0x02    /*!< \brief Last fragment */
#define LL_ADV_DATA_OP_COMP_FRAG           0x03    /*!< \brief Complete extended advertising data */
#define LL_ADV_DATA_OP_UNCHANGED_DATA      0x04    /*!< \brief Unchanged data (just update Advertising DID) */

/*!< Advertising data fragment preference */
#define LL_ADV_DATA_FRAG_PREF_FRAG         0x00    /*!< \brief Controller may fragment all Host advertising data */
#define LL_ADV_DATA_FRAG_PREF_NO_FRAG      0x01    /*!< \brief Controller should not fragment or minimize fragmentation of Host advertising data */

/*! \brief      Extended header bit definition. */
enum
{
  LL_EXT_HDR_ADV_ADDR_BIT   = (1 << 0), /*!< Extended header AdvA bit. */
  LL_EXT_HDR_TGT_ADDR_BIT   = (1 << 1), /*!< Extended header TargetA bit. */
  LL_EXT_HDR_SUPP_INFO_BIT  = (1 << 2), /*!< Extended header SuppInfo bit. */
  LL_EXT_HDR_ADI_BIT        = (1 << 3), /*!< Extended header AdvDataInfo bit. */
  LL_EXT_HDR_AUX_PTR_BIT    = (1 << 4), /*!< Extended header AuxPtr bit. */
  LL_EXT_HDR_SYNC_INFO_BIT  = (1 << 5), /*!< Extended header SyncInfo bit. */
  LL_EXT_HDR_TX_PWR_BIT     = (1 << 6), /*!< Extended header TxPower bit. */
};

/** \name Advertising event properties type bits
 *
 */
/**@{*/
#define LL_ADV_PROP_CONN_ADV_BIT                    (1<<0)  /*!< \brief Connectable advertising bit */
#define LL_ADV_PROP_SCAN_ADV_BIT                    (1<<1)  /*!< \brief Scannable advertising bit */
#define LL_ADV_PROP_DIRECT_ADV_BIT                  (1<<2)  /*!< \brief Directed advertising bit */
#define LL_ADV_PROP_CONN_DIRECT_ADV_BIT             (1<<3)  /*!< \brief High duty cycle connectable directed advertising bit */
#define LL_ADV_PROP_USE_LEG_PDU_BIT                 (1<<4)  /*!< \brief Use legacy advertising PDUs bit */
#define LL_ADV_PROP_OMIT_ADV_ADDR_BIT               (1<<5)  /*!< \brief Omit advertiser's address from all PDUs (anonymous advertising) bit */
#define LL_ADV_PROP_INC_TX_PWR_BIT                  (1<<6)  /*!< \brief Include TxPower in extended header of advertising PDU bit */
/**@}*/

/** \name Advertising event properties for legacy PDUs
 *
 */
/**@{*/
#define LL_ADV_PROP_LEG_CONN_UNDIRECT               0x13    /*!< \brief Connectable and scannable undirected advertising (00010011b) */
#define LL_ADV_PROP_LEG_CONN_DIRECT                 0x1D    /*!< \brief Connectable directed high duty cycle advertising (00011101b) */
#define LL_ADV_PROP_LEG_SCAN_UNDIRECT               0x12    /*!< \brief Scannable undirected advertising (00010010b) */
#define LL_ADV_PROP_LEG_NONCONN_UNDIRECT            0x10    /*!< \brief Non-connectable and non-scannable undirected advertising (00010000b) */
#define LL_ADV_PROP_LEG_CONN_DIRECT_LO_DUTY         0x15    /*!< \brief Connectable directed low duty cycle advertising (00010101b) */
/**@}*/

#define LL_MAX_ADV_HANDLE       0xEF    /*!< Maximum advertising handle. */
#define LL_MAX_ADV_SID          0x0F    /*!< Maximum advertising SID */

#define LL_EXT_ADV_HDR_MIN_LEN  1       /*!< Minimum extended advertising header length (ExtHdrLen and AdvMode fields). */
#define LL_EXT_ADV_HDR_MAX_LEN  64      /*!< Maximum extended advertising header length (ExtHdrLen, AdvMode fields and Extended header). */
#define LL_EXT_ADVBU_MAX_LEN    251     /*!< Maximum extended advertising channel PDU host data length. */
#define LL_EXT_ADVB_MAX_LEN     257     /*!< Maximum extended advertising channel PDU length. */

#define LL_EXT_ADVB_MAX_TIME_1M     ((LL_BLE_US_PER_BYTE_1M * (LL_EXT_ADVB_MAX_LEN - LL_ADV_HDR_LEN)) + LL_MIN_PKT_TIME_US_1M)
                                        /*!< Maximum time for a 1M advertising channel PDU. */
#define LL_EXT_ADVB_MAX_TIME_2M     ((LL_BLE_US_PER_BYTE_2M * (LL_EXT_ADVB_MAX_LEN - LL_ADV_HDR_LEN)) + LL_MIN_PKT_TIME_US_2M)
                                        /*!< Maximum time for a 2M advertising channel PDU. */
#define LL_EXT_ADVB_MAX_TIME_S2     ((LL_BLE_US_PER_BYTE_CODED_S2 * (LL_EXT_ADVB_MAX_LEN - LL_ADV_HDR_LEN)) + LL_MIN_PKT_TIME_US_CODED_S2)
                                        /*!< Maximum time for a Coded S2 advertising channel PDU. */
#define LL_EXT_ADVB_MAX_TIME_S8     ((LL_BLE_US_PER_BYTE_CODED_S8 * (LL_EXT_ADVB_MAX_LEN - LL_ADV_HDR_LEN)) + LL_MIN_PKT_TIME_US_CODED_S8)
                                        /*!< Maximum time for a Coded S8 advertising channel PDU. */

#define LL_AUX_PTR_MAX_USEC     2457600 /*!< Maximum AuxPtr offset value in microseconds. */

#define LL_SYNC_MIN_TIMEOUT     0x000A  /*!< Minimum synchronization timeout. */
#define LL_SYNC_MAX_TIMEOUT     0x4000  /*!< Maximum synchronization timeout. */
#define LL_SYNC_MAX_SKIP        0x01F3  /*!< Maximum synchronization skip. */
#define LL_SYNC_MAX_HANDLE      0x0EFF  /*!< Maximum synchronization handle. */

#define LL_PER_ADV_INT_MIN      0x0006  /*!< Minimum periodic advertising interval. */


/*** Data PDU ***/

/*! \brief      Data channel LL Control PDU types. */
enum
{
  /* --- Core Spec 4.0 --- */
  LL_PDU_CONN_UPDATE_IND        = 0x00, /*!< Connection update indication PDU. */
  LL_PDU_CHANNEL_MAP_IND        = 0x01, /*!< Channel map indication PDU. */
  LL_PDU_TERMINATE_IND          = 0x02, /*!< Terminate indication PDU. */
  LL_PDU_ENC_REQ                = 0x03, /*!< Encryption request PDU. */
  LL_PDU_ENC_RSP                = 0x04, /*!< Encryption response PDU. */
  LL_PDU_START_ENC_REQ          = 0x05, /*!< Start encryption request PDU. */
  LL_PDU_START_ENC_RSP          = 0x06, /*!< Start encryption response PDU. */
  LL_PDU_UNKNOWN_RSP            = 0x07, /*!< Unknown response PDU. */
  LL_PDU_FEATURE_REQ            = 0x08, /*!< Feature request PDU. */
  LL_PDU_FEATURE_RSP            = 0x09, /*!< Feature response PDU. */
  LL_PDU_PAUSE_ENC_REQ          = 0x0A, /*!< Pause encryption request PDU. */
  LL_PDU_PAUSE_ENC_RSP          = 0x0B, /*!< Pause encryption response PDU. */
  LL_PDU_VERSION_IND            = 0x0C, /*!< Version indication PDU. */
  LL_PDU_REJECT_IND             = 0x0D, /*!< Reject indication PDU. */
  /* --- Core Spec 4.2 --- */
  LL_PDU_SLV_FEATURE_REQ        = 0x0E, /*!< Slave feature request PDU. */
  LL_PDU_CONN_PARAM_REQ         = 0x0F, /*!< Connection parameter request PDU. */
  LL_PDU_CONN_PARAM_RSP         = 0x10, /*!< Connection parameter response PDU. */
  LL_PDU_REJECT_EXT_IND         = 0x11, /*!< Reject extended indication PDU. */
  LL_PDU_PING_REQ               = 0x12, /*!< Ping request PDU. */
  LL_PDU_PING_RSP               = 0x13, /*!< Ping response PDU. */
  LL_PDU_LENGTH_REQ             = 0x14, /*!< Data length request PDU. */
  LL_PDU_LENGTH_RSP             = 0x15, /*!< Data length response PDU. */
  /* --- Core Spec 5.0 --- */
  LL_PDU_PHY_REQ                = 0x16, /*!< PHY request PDU. */
  LL_PDU_PHY_RSP                = 0x17, /*!< PHY response PDU. */
  LL_PDU_PHY_UPDATE_IND         = 0x18, /*!< PHY update indication PDU. */
  LL_PDU_MIN_USED_CHAN_IND      = 0x19, /*!< Minimum used channels indication PDU. */
  LL_PDU_UNSPECIFIED            = 0xFF  /*!< Unspecified PDU. */
};

/* Data PDU length */
/* --- Core Spec 4.0 --- */
#define LL_CONN_UPD_IND_PDU_LEN       12      /*!< Connection update indication PDU length. */
#define LL_CHAN_MAP_IND_PDU_LEN       8       /*!< Channel map indication PDU length. */
#define LL_TERMINATE_IND_PDU_LEN      2       /*!< Terminate indication PDU length. */
#define LL_ENC_REQ_LEN                23      /*!< Encryption request PDU length. */
#define LL_ENC_RSP_LEN                13      /*!< Encryption response PDU length. */
#define LL_START_ENC_LEN              1       /*!< Start encryption request/response PDU length. */
#define LL_UNKNOWN_RSP_LEN            2       /*!< Unknown response PDU length. */
#define LL_FEATURE_PDU_LEN            9       /*!< Feature request/response PDU length. */
#define LL_PAUSE_ENC_LEN              1       /*!< Pause encryption request/response PDU length. */
#define LL_VERSION_IND_PDU_LEN        6       /*!< Version indication PDU length. */
#define LL_REJECT_IND_PDU_LEN         2       /*!< Reject indication PDU length. */
/* --- Core Spec 4.2 --- */
#define LL_CONN_PARAM_PDU_LEN         24      /*!< Connection parameter request or response PDU length. */
#define LL_REJECT_EXT_IND_PDU_LEN     3       /*!< Reject extended indication PDU length. */
#define LL_PING_PDU_LEN               1       /*!< Ping request/response PDU length. */
#define LL_DATA_LEN_PDU_LEN           9       /*!< Data length request or response PDU length. */
/* --- Core Spec 5.0 --- */
#define LL_PHY_PDU_LEN                3       /*!< PHY request/response PDU length. */
#define LL_PHY_UPD_IND_PDU_LEN        5       /*!< PHY update indication PDU length. */
#define LL_MIN_USED_CHAN_PDU_LEN      3       /*!< Minimum used channels indication PDU length. */

#define LL_EMPTY_PDU_LEN              2       /*!< Length of an empty data PDU. */

#define LL_DATA_HDR_LEN               2       /*!< Data channel header length. */
#define LL_DATA_MIC_LEN               4       /*!< Data channel PDU MIC length. */

#define LL_DATA_HDR_LLID_MSK          0x03    /*!< Data PDU LLID mask. */
#define LL_DATA_HDR_LEN_MSK           0xFF    /*!< Data header length mask. BLE 4.2 data len extension allows 8 bits. */

#define LL_MAX_NUM_CHAN_DATA          37      /*!< Maximum number of used data channels. */
#define LL_MIN_NUM_CHAN_DATA          2       /*!< Minimum number of used data channels. */

/*! \brief      Data PDU LLID types. */
enum
{
  LL_LLID_VS_PDU                = 0x00, /*!< Vendor specific PDU. */
  /* N.B. next two enumerations intentionally use identical values. */
  LL_LLID_EMPTY_PDU             = 0x01, /*!< Empty PDU. */
  LL_LLID_CONT_PDU              = 0x01, /*!< Data PDU: continuation fragment of an L2CAP message. */
  LL_LLID_START_PDU             = 0x02, /*!< Data PDU: start of an L2CAP message or a complete L2CAP message with no fragmentation. */
  LL_LLID_CTRL_PDU              = 0x03, /*!< Control PDU. */
};

/*** Encryption ***/

#define LL_ECC_KEY_LEN                32      /*!< ECC key length. */

#define LL_DEF_RES_ADDR_TO_SEC        900     /*!< Default resolvable address timeout in seconds. */

#define LL_RAND_LEN                   8       /*!< Length of random number */
#define LL_KEY_LEN                    16      /*!< Encryption key length. */
#define LL_SKD_LEN                    LL_KEY_LEN      /*!< Session key diversifier length. */
#define LL_IV_LEN                     8       /*!< Initialization vector length. */
#define LL_ENCRYPT_DATA_LEN           16      /*!< Number of bytes in the encryption block */

#define LL_DEF_AUTH_TO_MS             30000   /*!< Default authentication timeout in milliseconds. */

/*** LLCP ***/

#define LL_DATA_LEN_TO_TIME_1M(len)       ((LL_BLE_US_PER_BYTE_1M * ((len) + LL_DATA_MIC_LEN)) + LL_MIN_PKT_TIME_US_1M)
                                              /*!< Convert data length to time. */
#define LL_DATA_LEN_TO_TIME_2M(len)       ((LL_BLE_US_PER_BYTE_2M * ((len) + LL_DATA_MIC_LEN)) + LL_MIN_PKT_TIME_US_2M)
                                              /*!< Convert data length to time. */
#define LL_DATA_LEN_TO_TIME_CODED_S8(len) ((LL_BLE_US_PER_BYTE_CODED_S8 * ((len) + LL_DATA_MIC_LEN)) + LL_MIN_PKT_TIME_US_CODED_S8)
                                              /*!< Convert data length to time. */
#define LL_DATA_LEN_TO_TIME_CODED_S2(len) ((LL_BLE_US_PER_BYTE_CODED_S2 * ((len) + LL_DATA_MIC_LEN)) + LL_MIN_PKT_TIME_US_CODED_S2)
                                              /*!< Convert data length to time. */

#define LL_MIN_INSTANT                6       /*!< Minimum number of CE to apply a CONN_UPD or CHAN_MAP. */

#define LL_MAX_ADV_DATA_LEN           1650    /*!< Maximum advertising data length. */

#define LL_MAX_DATA_LEN_MIN           27      /*!< Minimum value for maximum Data PDU length */
#define LL_MAX_DATA_LEN_ABS_MAX       251     /*!< Absolute maximum limit for maximum Data PDU length */

#define LL_MAX_DATA_TIME_MIN          328     /*!< Minimum value for maximum Data PDU time */
#define LL_MAX_DATA_TIME_MIN_CODED    2704    /*!< Minimum value for maximum Data PDU time for the Coded PHY */
#define LL_MAX_DATA_TIME_ABS_MAX      17040   /*!< Absolute maximum limit for maximum Data PDU time */
#define LL_MAX_DATA_TIME_ABS_MAX_1M   2120    /*!< Absolute maximum limit for maximum Data PDU time (LE 1M PHY) */

#define LL_T_PRT_SEC                  40      /*!< LLCP procedure response timeout in seconds. */

#define LL_MAX_ADV_DLY_MS             10      /*!< Maximum advertising delay in milliseconds. */

#define LL_MIN_CONN_INTERVAL          6       /*!< Minimum value for connection interval. */
#define LL_MAX_CONN_INTERVAL          3200    /*!< Maximum value for connection interval. */

#define LL_MIN_TX_WIN_SIZE            1       /*!< Minimum value for transmit window size. */
#define LL_MAX_TX_WIN_SIZE            8       /*!< Maximum value for transmit window size. */

#define LL_MAX_CONN_LATENCY           499     /*!< Maximum value for connection slave latency. */

#define LL_MIN_SUP_TIMEOUT            10      /*!< Minimum value for connection supervision timeout. */
#define LL_MAX_SUP_TIMEOUT            3200    /*!< Maximum value for connection supervision timeout. */

#define LL_MIN_POWER_THRESHOLD        -128    /*!< Minimum value for power threshold. */
#define LL_MAX_POWER_THRESHOLD        127     /*!< Maximum value for power threshold. */

#define LL_MAX_PHYS                   3       /*!< Number of LE PHYs. */
#define LL_ALL_PHYS_MSK               0x7     /*!< All supported LE PHYs mask. */

/*** DTM ***/

#define LL_DTM_HDR_LEN                2                       /*!< Direct Test Mode PDU header length. */
#define LL_DTM_SYNC_WORD              UINT32_C(0x71764129)    /*!< Direct Test Mode sync word. */
#define LL_DTM_CRC_INIT               UINT32_C(0x555555)      /*!< Direct Test Mode CRC initial value. */
#define LL_DTM_MAX_INT_US             12500   /*!< Maximum time interval between packets in microseconds. */
#define LL_DTM_PDU_ABS_MAX_LEN        255     /*!< Absolute maximum DTM PDU length. */
#define LL_DTM_MAX_CHAN_IDX           39      /*!< Maximum channel index. */

/*** Baseband ***/

#define LL_CHAN_DATA_MIN_IDX          0       /*!< Minimum data channel index. */
#define LL_CHAN_DATA_MAX_IDX          36      /*!< Maximum data channel index. */
#define LL_CHAN_DATA_ALL              UINT64_C(0x0000001FFFFFFFFF)    /*!< Maximum data channel index. */

#define LL_BLE_BIT_PER_US             1       /*!< BLE PHY rate. */
#define LL_BLE_US_PER_BYTE_1M         8       /*!< BLE PHY speed (LE 1M PHY). */
#define LL_BLE_US_PER_BYTE_2M         4       /*!< BLE PHY speed (LE 2M PHY). */
#define LL_BLE_US_PER_BYTE_CODED_S8   64      /*!< BLE PHY speed (LE Coded PHY, S=8). */
#define LL_BLE_US_PER_BIT_CODED_S8    8       /*!< BLE PHY speed (LE Coded PHY, S=8). */
#define LL_BLE_US_PER_BYTE_CODED_S2   16      /*!< BLE PHY speed (LE Coded PHY, S=2). */
#define LL_BLE_US_PER_BIT_CODED_S2    2       /*!< BLE PHY speed (LE Coded PHY, S=2). */
#define LL_BLE_TIFS_US                150     /*!< BLE inter-frame space. */
#define LL_BLE_MAFS_US                300     /*!< BLE minimum AUX frame space. */
#define LL_BLE_US_PER_TICK            625     /*!< Microseconds per BLE tick. */

#define LL_MIN_PKT_TIME_US_1M         80      /*!< Minimum packet time (i.e. empty PDU) on LE 1M PHY. */
#define LL_MIN_PKT_TIME_US_2M         44      /*!< Minimum packet time (i.e. empty PDU) on LE 2M PHY. */
#define LL_MIN_PKT_TIME_US_CODED_S8   720     /*!< Minimum packet time (i.e. empty PDU) on LE Coded PHY, S=8. */
#define LL_MIN_PKT_TIME_US_CODED_S2   462     /*!< Minimum packet time (i.e. empty PDU) on LE Coded PHY, S=2. */

#define LL_MIN_ADV_TX_PWR_LVL         -20     /*!< Minimum Tx power level for advertising. */
#define LL_MAX_ADV_TX_PWR_LVL         10      /*!< Maximum Tx power level for advertising. */

#define LL_MIN_TX_PWR_LVL             -30     /*!< Minimum Tx power level for connections. */
#define LL_MAX_TX_PWR_LVL             20      /*!< Maximum Tx power level for connections. */

#define LL_MAX_TIFS_DEVIATION         2       /*!< Maximum TIFS deviation in microseconds. */

#define LL_MAX_CE_DEVIATION_USEC      16      /*!< Maximum connection event deviation in microseconds. */

#ifdef __cplusplus
};
#endif

#endif /* LL_DEFS_H */
