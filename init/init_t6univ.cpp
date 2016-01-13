/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void common_properties()
{
    property_set("rild.libargs", "-d /dev/smd0");
    property_set("rild.libpath", "/system/lib/libril-qc-qmi-1.so");
}

void dualsim_properties(char const multisim_config[])
{
    property_set("persist.radio.multisim.config", multisim_config);
    property_set("persist.radio.dont_use_dsd", "true");
    property_set("ro.multisim.set_audio_params", "true");
    property_set("ro.telephony.ril.config", "simactivation,sim2gsmonly");
}

void cdma_properties(char const default_cdma_sub[], char const default_network[])
{
    property_set("ro.telephony.default_cdma_sub", default_cdma_sub);
    property_set("ro.telephony.default_network", default_network);

    property_set("telephony.lteOnCdmaDevice", "1");
    property_set("ro.ril.svdo", "true");
    property_set("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420");
    property_set("ro.ril.enable.sdr", "0");
    property_set("ro.ril.enable.gea3", "1");
    property_set("ro.ril.enable.a53", "1");
    property_set("ro.ril.enable.r8fd=1", "1");
    property_set("persist.radio.snapshot_enabled", "1");
    property_set("persist.radio.snapshot_timer", "22");
}

void gsm_properties(char const default_network[])
{
    property_set("ro.telephony.default_network", default_network);
    property_set("telephony.lteOnGsmDevice", "1");
}

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char bootmid[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || strncmp(platform, ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    property_get("ro.boot.mid", bootmid);

    if (strstr(bootmid, "0P3P10000")) {
        /* t6vzw (t6wl) */
        common_properties();
        cdma_properties("0", "10");
        property_set("ro.product.model", "HTC6600LVW");
        property_set("ro.build.fingerprint", "VERIZON/HTCOneMaxVZW/t6wl:4.4.2/KOT49H/333209.2:user/release-keys");
        property_set("ro.build.description", "3.09.605.2 CL333209 release-keys");
        property_set("ro.product.device", "t6wl");
        property_set("ro.build.product", "t6wl");
        property_set("ro.ril.vzw.feature", "1");
        property_set("ro.ril.oem.ecclist", "911,*911,#911");
        property_set("ro.ril.enable.a52", "0");
        property_set("ro.ril.att.feature", "0");
        property_set("ro.ril.enable.managed.roaming", "1");
        property_set("ro.ril.oem.show.act", "0");
        property_set("ro.ril.set.mtusize", "1428");
        property_set("ro.ril.wp.feature", "1");
        property_set("ro.cdma.data_retry_config", "max_retries=infinite,0,0,60000,120000,480000,900000");
        property_set("ro.gsm.data_retry_config", "max_retries=infinite,0,0,60000,120000,480000,900000");
        property_set("ro.gsm.2nd_data_retry_config", "max_retries=infinite,0,0,60000,120000,480000,900000");
        property_set("ro.config.svlte1x", "true");
        property_set("ro.ril.def.agps.mode", "6");
        property_set("ro.telephony.get_imsi_from_sim", "true");
    } else if (strstr(bootmid, "0P3P70000")) {
        /* t6spr (t6whl) */
        common_properties();
        cdma_properties("1", "8");
        property_set("ro.product.model", "HTC0P3P7");
        property_set("ro.build.fingerprint", "htc/sprint_wwe/t6whl:4.4.2/KOT49H/335898.5:user/release-keys");
        property_set("ro.build.description", "3.02.651.5 CL335898 release-keys");
        property_set("ro.product.device", "t6whl");
        property_set("ro.build.product", "t6whl");
        property_set("telephony.sms.pseudo_multipart", "1");
        property_set("persist.radio.mode_pref_nv10", "1");
        property_set("ro.ril.oem.ecclist", "911");
        property_set("ro.ril.set.mtusize", "1422");
    } else if (strstr(bootmid, "0P3P20000")) {
        /* t6dwg (dual sim) */
        common_properties();
        dualsim_properties("dsda");
        cdma_properties("0,1", "10");
        property_set("ro.product.model", "One Max");
        property_set("ro.build.fingerprint", "htc/htccn_chs_cu/t6dug:5.0.2/LRX22G/524896.8:user/release-keys");
        property_set("ro.build.description", "3.22.1402.8 CL524896 release-keys");
        property_set("ro.product.device", "t6dwg");
        property_set("ro.build.product", "t6dwg");
    } else if (strstr(bootmid, "0P3P30000")) {
        /* t6dug (dual sim) */
        common_properties();
        dualsim_properties("dsda");
        gsm_properties("9,1");
        property_set("ro.product.model", "One Max");
        property_set("ro.build.fingerprint", "htc/htccn_chs_cu/t6dug:5.0.2/LRX22G/524896.8:user/release-keys");
        property_set("ro.build.description", "3.22.1402.8 CL524896 release-keys");
        property_set("ro.product.device", "t6dug");
        property_set("ro.build.product", "t6dug");
    } else if (strstr(bootmid, "0P3P40000")) {
        /* t6tl (China) */
        common_properties();
        gsm_properties("9");
        property_set("ro.product.model", "HTC 8088");
        property_set("ro.build.fingerprint", "htc/htccn_chs_cmcc/t6tl:5.0.2/LRX22G/524896.8:user/release-keys");
        property_set("ro.build.description", "3.22.1403.8 CL524896 release-keys");
        property_set("ro.product.device", "t6tl");
        property_set("ro.build.product", "t6tl");
        property_set("persist.radio.tdscdma_present", "2");
    } else {
        common_properties();
        gsm_properties("9");
        property_set("ro.product.model", "One Max");
        property_set("ro.build.fingerprint", "htc/htc_europe/t6ul:5.0.2/LRX22G/525693.7:user/release-keys");
        property_set("ro.build.description", "4.13.401.7 CL525693 release-keys");
        property_set("ro.product.device", "t6");
        property_set("ro.build.product", "t6");
    }

    property_get("ro.product.device", device);
    ERROR("Found bootmid %s setting build properties for %s device\n", bootmid, device);
}
