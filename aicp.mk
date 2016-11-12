# Release name
PRODUCT_RELEASE_NAME := c1skt

# Inherit device configuration
$(call inherit-product, device/samsung/smdk4412-common/common.mk)
$(call inherit-product, device/samsung/c1skt/c1skt.mk)

# Inherit from the common Open Source product configuration
$(call inherit-product, $(SRC_TARGET_DIR)/product/aosp_base_telephony.mk)

# Boot animation
TARGET_SCREEN_HEIGHT := 1280
TARGET_SCREEN_WIDTH := 720

# Inherit some common AICP stuff.
$(call inherit-product, vendor/aicp/configs/common.mk)

# Device identifier. This must come after all inclusions
PRODUCT_DEVICE := c1skt
PRODUCT_NAME := aicp_c1skt
PRODUCT_BRAND := samsung
PRODUCT_MODEL := SHV-E210S
PRODUCT_MANUFACTURER := samsung

# Set build fingerprint / ID / Product Name etc.
PRODUCT_BUILD_PROP_OVERRIDES += \
		PRODUCT_NAME=c1skt \
		TARGET_DEVICE=c1skt \
		BUILD_FINGERPRINT="samsung/c1skt/c1skt:4.4.4/KTU84P/E210SKSUKOL2:user/release-keys" \
		PRIVATE_BUILD_DESC="c1skt-user 4.4.4 KTU84P E210SKSUKOL2 release-keys"
		
# AICP Device Maintainers
PRODUCT_BUILD_PROP_OVERRIDES += \
	DEVICE_MAINTAINERS="Trafalgar Square"

# Boot animation
TARGET_SCREEN_HEIGHT := 1280
TARGET_SCREEN_WIDTH := 720
-include vendor/aicp/configs/bootanimation.mk