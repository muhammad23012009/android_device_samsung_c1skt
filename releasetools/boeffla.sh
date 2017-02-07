# AnyKernel2 Script
#
# Original and credits: osm0sis @ xda-developers
#
# Modified by Lord Boeffla, 05.12.2016

############### AnyKernel setup start ############### 

# EDIFY properties
do.devicecheck=1
do.initd=0
do.modules=1
do.cleanup=1

# shell variables
block=/dev/block/mmcblk0p5;
add_seandroidenforce=0
supersu_exclusions=""
is_slot_device=0;

############### AnyKernel setup end ############### 

## AnyKernel methods (DO NOT CHANGE)
# import patching functions/variables - see for reference
. /system/bin/tools/boeffla-core.sh;

# dump current kernel
dump_boot;

############### Ramdisk customization start ###############

# AnyKernel permissions
chmod 775 $ramdisk/sbin
chmod 755 $ramdisk/sbin/busybox

chmod 775 $ramdisk/res
chmod -R 755 $ramdisk/res/bc
chmod -R 755 $ramdisk/res/misc

# ramdisk changes
backup_file default.prop;
replace_string default.prop "ro.adb.secure=0" "ro.adb.secure=1" "ro.adb.secure=0";
replace_string default.prop "ro.secure=0" "ro.secure=1" "ro.secure=0";

############### Ramdisk customization end ###############

# write new kernel
write_boot;
