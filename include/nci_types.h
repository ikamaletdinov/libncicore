/*
 * Copyright (C) 2018-2020 Jolla Ltd.
 * Copyright (C) 2018-2020 Slava Monich <slava.monich@jolla.com>
 *
 * You may use this file under the terms of BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *   3. Neither the names of the copyright holders nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NCI_TYPES_H
#define NCI_TYPES_H

#include <gutil_types.h>

G_BEGIN_DECLS

/* Types */

typedef struct nci_core NciCore;
typedef struct nci_hal_client NciHalClient;
typedef struct nci_hal_io NciHalIo;

/* Table 4: Conn ID
 * 0: Static RF Connection between the DH and a Remote NFC Endpoint */
#define NCI_STATIC_RF_CONN_ID (0x00)

/* Table 94: Status Codes */
typedef enum nci_status {
    NCI_STATUS_OK = 0x00,
    NCI_STATUS_REJECTED = 0x01,
    NCI_STATUS_RF_FRAME_CORRUPTED = 0x02,
    NCI_STATUS_FAILED = 0x03,
    NCI_STATUS_NOT_INITIALIZED = 0x04,
    NCI_STATUS_SYNTAX_ERROR = 0x05,
    NCI_STATUS_SEMANTIC_ERROR = 0x06,
    NCI_STATUS_INVALID_PARAM = 0x09,
    NCI_STATUS_MESSAGE_SIZE_EXCEEDED = 0x0A,
    NCI_STATUS_DISCOVERY_ALREADY_STARTED = 0xA0,
    NCI_STATUS_DISCOVERY_TARGET_ACTIVATION_FAILED = 0xA1,
    NCI_STATUS_DISCOVERY_TEAR_DOWN = 0xA2,
    NCI_STATUS_RF_TRANSMISSION_ERROR = 0xB0,
    NCI_STATUS_RF_PROTOCOL_ERROR = 0xB1,
    NCI_STATUS_RF_TIMEOUT_ERROR = 0xB2,
    NCI_STATUS_NFCEE_INTERFACE_ACTIVATION_FAILED = 0xC0,
    NCI_STATUS_NFCEE_TRANSMISSION_ERROR = 0xC1,
    NCI_STATUS_NFCEE_PROTOCOL_ERROR = 0xC2,
    NCI_STATUS_NFCEE_TIMEOUT_ERROR = 0xC3
} NCI_STATUS;

/* Table 96: RF Technology and Mode */
typedef enum nci_mode {
    NCI_MODE_PASSIVE_POLL_A = 0x00,
    NCI_MODE_PASSIVE_POLL_B = 0x01,
    NCI_MODE_PASSIVE_POLL_F = 0x02,
    NCI_MODE_ACTIVE_POLL_A = 0x03,
    NCI_MODE_ACTIVE_POLL_F = 0x05,
    NCI_MODE_PASSIVE_POLL_15693 = 0x06,
    NCI_MODE_PASSIVE_LISTEN_A = 0x80,
    NCI_MODE_PASSIVE_LISTEN_B = 0x81,
    NCI_MODE_PASSIVE_LISTEN_F = 0x82,
    NCI_MODE_ACTIVE_LISTEN_A = 0x83,
    NCI_MODE_ACTIVE_LISTEN_F = 0x85,
    NCI_MODE_PASSIVE_LISTEN_15693 = 0x86
} NCI_MODE;

/* Table 97: Bit Rates */
typedef enum nci_bit_rate {
    NFC_BIT_RATE_106 = 0x00, /* 106 Kbit/s */
    NFC_BIT_RATE_212 = 0x01, /* 212 Kbit/s */
    NFC_BIT_RATE_424 = 0x02, /* 424 Kbit/s */
    NFC_BIT_RATE_848 = 0x03, /* 848 Kbit/s */
    NFC_BIT_RATE_1695 = 0x04, /* 1695 Kbit/s */
    NFC_BIT_RATE_3390 = 0x05, /* 3390 Kbit/s */
    NFC_BIT_RATE_6780 = 0x06  /* 6780 Kbit/s */
} NFC_BIT_RATE;

/* Table 98: RF Protocols */
typedef enum nci_protocol {
    NCI_PROTOCOL_UNDETERMINED = 0x00,
    NCI_PROTOCOL_T1T = 0x01,
    NCI_PROTOCOL_T2T = 0x02,
    NCI_PROTOCOL_T3T = 0x03,
    NCI_PROTOCOL_ISO_DEP = 0x04,
    NCI_PROTOCOL_NFC_DEP = 0x05,
    NCI_PROTOCOL_PROPRIETARY = 0x80 /* Since 1.0.6 */
} NCI_PROTOCOL;

/* Table 99: RF Interfaces */
typedef enum nci_rf_interface {
    NCI_RF_INTERFACE_NFCEE_DIRECT = 0x00,
    NCI_RF_INTERFACE_FRAME = 0x01,
    NCI_RF_INTERFACE_ISO_DEP = 0x02,
    NCI_RF_INTERFACE_NFC_DEP = 0x03,
    NCI_RF_INTERFACE_PROPRIETARY = 0x80 /* Since 1.0.6 */
} NCI_RF_INTERFACE;

/* See Table 54: Specific Parameters for NFC-A Poll Mode */
typedef struct nci_mode_param_poll_a {
    guint8 sens_res[2];
    guint8 nfcid1_len;
    guint8 nfcid1[10];
    guint8 sel_res_len;
    guint8 sel_res;
} NciModeParamPollA;

/* Table 56: Specific Parameters for NFC-B Poll Mode */
typedef struct nci_mode_param_poll_b {
    guint8 nfcid0[4];
    guint fsc;  /* FSCI converted to bytes */
    /* Since 1.1.5 */
    guint8 app_data[4];
    GUtilData prot_info;
} NciModeParamPollB;

/* Table 58: Specific Parameters for NFC-F Poll Mode */
typedef struct nci_mode_param_poll_f {
    guint8 bitrate;   /* 1 = 212 kbps, 2 = 424 kbps */
    guint8 nfcid2[8]; /* Bytes 2-9 of SENSF_RES */
} NciModeParamPollF;  /* Since 1.0.8 */

/* Table 59: Specific Parameters for NFC-F Listen Mode */
typedef struct nci_mode_param_listen_f {
    GUtilData nfcid2; /* NFCID2 generated by the Local NFCC */
} NciModeParamListenF; /* Since 1.1.2 */

typedef union nci_mode_param {
    NciModeParamPollA poll_a;
    NciModeParamPollB poll_b;
    NciModeParamPollF poll_f;     /* Since 1.0.8 */
    NciModeParamListenF listen_f; /* Since 1.1.2 */
} NciModeParam;

/* Table 76: Activation Parameters for NFC-A/ISO-DEP Poll Mode */
typedef struct nci_activation_param_iso_dep_poll_a {
    guint fsc;     /* FSC (FSCI converted to bytes) */
    GUtilData t1;  /* T1 to Tk (otherwise called historical bytes) */
} NciActivationParamIsoDepPollA;

/* Table 75: Activation Parameters for NFC-B/ISO-DEP Poll Mode */
typedef struct nci_activation_param_iso_dep_poll_b {
    guint mbli;     /* Maximum buffer length index */
    guint did;      /* Device ID */
    GUtilData hilr; /* Higher Layer Response */
} NciActivationParamIsoDepPollB; /* Since 1.1.5 */

/* Table 82: Activation Parameters for NFC-DEP Poll Mode */
typedef struct nci_activation_param_nfc_dep_poll {
    /* ATR_RES starting from and including Byte 3 */
    guint8 nfcid3[10];
    guint8 did;
    guint8 bs;
    guint8 br;
    guint8 to;
    guint8 pp;
    GUtilData g;
} NciActivationParamNfcDepPoll; /* Since 1.0.8 */

/* Table 83: Activation Parameters for NFC-DEP Listen Mode */
typedef struct nci_activation_param_nfc_dep_listen {
    /* ATR_REQ starting from and including Byte 3 */
    guint8 nfcid3[10];
    guint8 did;
    guint8 bs;
    guint8 br;
    guint8 pp;
    GUtilData g;
} NciActivationParamNfcDepListen; /* Since 1.0.8 */

typedef union nci_activation_param {
    NciActivationParamIsoDepPollA iso_dep_poll_a;
    NciActivationParamIsoDepPollB iso_dep_poll_b;  /* Since 1.1.5 */
    NciActivationParamNfcDepPoll nfc_dep_poll;     /* Since 1.0.8 */
    NciActivationParamNfcDepListen nfc_dep_listen; /* Since 1.0.8 */
} NciActivationParam;

/* See Table 61: Notification for RF Interface activation */
typedef struct nci_intf_activated_ntf {
    guint8 discovery_id;
    NCI_RF_INTERFACE rf_intf;
    NCI_PROTOCOL protocol;
    NCI_MODE mode;
    guint8 max_data_packet_size;
    guint8 num_credits;
    guint8 mode_param_len;
    const void* mode_param_bytes;
    const NciModeParam* mode_param;
    NCI_MODE data_exchange_mode;
    NFC_BIT_RATE transmit_rate;
    NFC_BIT_RATE receive_rate;
    guint8 activation_param_len;
    const void* activation_param_bytes;
    const NciActivationParam* activation_param;
} NciIntfActivationNtf;

/* Table 52: Control Messages to Start Discovery */
typedef struct nci_discovery_ntf {
    guint8 discovery_id;
    NCI_PROTOCOL protocol;
    NCI_MODE mode;
    guint8 param_len;
    const void* param_bytes;
    const NciModeParam* param;
    gboolean last;
} NciDiscoveryNtf;

/* NCI states */

typedef enum nci_state_id {
    NCI_STATE_INIT,
    NCI_STATE_ERROR,
    NCI_STATE_STOP,
    /* RFST states are taken from the NCI spec */
    NCI_RFST_IDLE,
    NCI_RFST_DISCOVERY,
    NCI_RFST_W4_ALL_DISCOVERIES,
    NCI_RFST_W4_HOST_SELECT,
    NCI_RFST_POLL_ACTIVE,
    NCI_RFST_LISTEN_ACTIVE,
    NCI_RFST_LISTEN_SLEEP,
    NCI_CORE_STATES
} NCI_STATE;

/*
 * Operation modes
 *
 * The relationship between op mode bits goes like this:
 *
 * +----------------+---------------------+----------------+
 * | NFC R/W Modes  |   NFC Peer Modes    | NFC CE Mode    |
 * | NFC_OP_MODE_RW |   NFC_OP_MODE_PEER  | NFC_OP_MODE_CE |
 * +------+---------+-----------+---------+----------------+
 * | Tags | ISO-DEP | NFC-DEP   | NFC-DEP | ISO-DEP        |
 * | 1-3  |         | Initiator | Target  |                |
 * +------+---------+-----------+---------+----------------+
 * |      Poll side             |     Listen side          |
 * |      NFC_OP_MODE_POLL      |     NFC_OP_MODE_LISTEN   |
 * +----------------------------+--------------------------+
 *
 * That hopefully explains why certain combinations don't make
 * sense, specifically (NFC_OP_MODE_RW | NFC_OP_MODE_LISTEN)
 * and (NFC_OP_MODE_CE | NFC_OP_MODE_POLL).
 */

typedef enum nci_op_mode {
    NFC_OP_MODE_NONE = 0x00,
    NFC_OP_MODE_RW = 0x01,      /* Reader/Writer (requires POLL) */
    NFC_OP_MODE_PEER = 0x02,    /* Peer NFC-DEP (POLL and/or LISTEN) */
    NFC_OP_MODE_CE = 0x04,      /* Card Emulation (requires LISTEN) */
    /* The next two are kind of orthogonal, see the diagram above */
    NFC_OP_MODE_POLL = 0x08,    /* Poll side/Initiator */
    NFC_OP_MODE_LISTEN = 0x10   /* Listen side/Target */
} NCI_OP_MODE; /* Since 1.1.0 */

/* Logging */

#define NCI_LOG_MODULE nci_log
extern GLogModule NCI_LOG_MODULE;

G_END_DECLS

#endif /* NFC_TYPES_H */

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
