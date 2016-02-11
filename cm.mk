# Release name
PRODUCT_RELEASE_NAME := c1skt

# Boot animation
TARGET_SCREEN_HEIGHT := 1280
TARGET_SCREEN_WIDTH := 720

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/samsung/c1skt/full_c1skt.mk)

# Device identifier. This must come after all inclusions
PRODUCT_DEVICE := c1skt
PRODUCT_NAME := cm_c1skt
PRODUCT_BRAND := samsung
PRODUCT_MODEL := SHV-E210S
PRODUCT_MANUFACTURER := samsung

# Set build fingerprint / ID / Product Name ect.
PRODUCT_BUILD_PROP_OVERRIDES += PRODUCT_NAME=c1skt TARGET_DEVICE=c1skt BUILD_FINGERPRINT="samsung/m0xx/m0:4.3/JSS15J/I9300XXUGMJ9:user/release-keys" PRIVATE_BUILD_DESC="m0xx-user 4.3 JSS15J I9300XXUGMJ9 release-keys"
