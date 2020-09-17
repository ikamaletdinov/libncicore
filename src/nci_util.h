/*
 * Copyright (C) 2019-2020 Jolla Ltd.
 * Copyright (C) 2019-2020 Slava Monich <slava.monich@jolla.com>
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

#ifndef NCI_UTIL_H
#define NCI_UTIL_H

#include "nci_types_p.h"

gboolean
nci_listen_mode(
    NCI_MODE mode)
    NCI_INTERNAL;

const NciModeParam*
nci_parse_mode_param(
    NciModeParam* param,
    NCI_MODE mode,
    const guint8* bytes,
    guint len)
    NCI_INTERNAL;

gboolean
nci_parse_discover_ntf(
    NciDiscoveryNtf* ntf,
    NciModeParam* param,
    const guint8* bytes,
    guint len)
    NCI_INTERNAL;

gboolean
nci_parse_intf_activated_ntf(
    NciIntfActivationNtf* ntf,
    NciModeParam* mode_param,
    NciActivationParam* activation_param,
    const guint8* pkt,
    guint len)
    NCI_INTERNAL;

NciDiscoveryNtf*
nci_discovery_ntf_copy_array(
    const NciDiscoveryNtf* const* ntfs,
    guint count)
    NCI_INTERNAL;

NciDiscoveryNtf*
nci_discovery_ntf_copy(
    const NciDiscoveryNtf* ntf)
    NCI_INTERNAL;

NciModeParam*
nci_mode_param_copy(
    const NciModeParam* param,
    NCI_MODE mode)
    NCI_INTERNAL;

NciActivationParam*
nci_activation_param_copy(
    const NciActivationParam* param,
    NCI_RF_INTERFACE intf,
    NCI_MODE mode)
    NCI_INTERNAL;

#endif /* NCI_UTIL_H */

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
