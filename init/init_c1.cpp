/*
   Copyright (c) 2016, The CyanogenMod Project

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

#include <stdio.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <android-base/properties.h>
#include <android-base/logging.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "vendor_init.h"
#include "property_service.h"

#include "init_c1.h"

using android::base::GetProperty;
using android::init::property_set;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void init_target_properties()
{
    std::string platform = GetProperty("ro.board.platform", "");
    if (platform != ANDROID_TARGET)
        return;

    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("E210K") == 0) {
        /* c1ktt - KT Corp (formerly Korea Telecom) */
        property_override("ro.build.fingerprint", "samsung/c1ktt/c1ktt:4.4.4/KTU84P/E210KKTUKPJ2:user/release-keys");
        property_override("ro.build.description", "c1ktt-user 4.4.4 KTU84P E210KKTUKPJ2 release-keys");
        property_override("ro.product.model", "SHV-E210K");
        property_override("ro.product.device", "c1ktt");
    } else if (bootloader.find("E210L") == 0) {
        /* c1lgt - LG Uplus */
        property_override("ro.build.fingerprint", "samsung/c1lgt/c1lgt:4.4.4/KTU84P/E210LKLUKPJ2:user/release-keys");
        property_override("ro.build.description", "c1lgt-user 4.4.4 KTU84P E210LKLUKPJ2 release-keys");
        property_override("ro.product.model", "SHV-E210L");
        property_override("ro.product.device", "c1lgt");
    } else if (bootloader.find("E210S") == 0) {
        /* c1skt - SK Telecom */
        property_override("ro.build.fingerprint", "samsung/c1skt/c1skt:4.4.4/KTU84P/E210SKSUKPJ2:user/release-keys");
        property_override("ro.build.description", "c1skt-user 4.4.4 KTU84P E210SKSUKPJ2 release-keys");
        property_override("ro.product.model", "SHV-E210S");
        property_override("ro.product.device", "c1skt");
    } else {
        /* DEFAULT */
        property_override("ro.build.fingerprint", "samsung/c1skt/c1skt:4.4.4/KTU84P/E210SKSUKPJ2:user/release-keys");
        property_override("ro.build.description", "c1skt-user 4.4.4 KTU84P E210SKSUKPJ2 release-keys");
        property_override("ro.product.model", "SHV-E210S");
        property_override("ro.product.device", "c1skt");
    }
}

static int read_file2(const char *fname, char *data, int max_size)
{
    int fd, rc;

    if (max_size < 1)
        return 0;

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        LOG(INFO) << "failed to open " << fname << std::endl;
        return 0;
    }

    rc = read(fd, data, max_size - 1);
    if ((rc > 0) && (rc < max_size))
        data[rc] = '\0';
    else
        data[0] = '\0';
    close(fd);

    return 1;
}

static void init_alarm_boot_properties()
{
    char const *alarm_file = "/proc/sys/kernel/boot_reason";
    char buf[64];

    if (read_file2(alarm_file, buf, sizeof(buf))) {
        /*
         * Setup ro.alarm_boot value to true when it is RTC triggered boot up
         * For existing PMIC chips, the following mapping applies
         * for the value of boot_reason:
         *
         * 0 -> unknown
         * 1 -> hard reset
         * 2 -> sudden momentary power loss (SMPL)
         * 3 -> real time clock (RTC)
         * 4 -> DC charger inserted
         * 5 -> USB charger insertd
         * 6 -> PON1 pin toggled (for secondary PMICs)
         * 7 -> CBLPWR_N pin toggled (for external power supply)
         * 8 -> KPDPWR_N pin toggled (power key pressed)
         */
        if (buf[0] == '3')
            property_set("ro.alarm_boot", "true");
        else
            property_set("ro.alarm_boot", "false");
    }
}

void vendor_load_properties()
{
    init_target_properties();
    init_alarm_boot_properties();
}
