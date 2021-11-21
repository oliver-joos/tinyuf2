CFLAGS += \
  -DSTM32F412Zx \
  -DHSE_VALUE=8000000U

SRC_S += \
	$(ST_CMSIS)/Source/Templates/gcc/startup_stm32f412zx.s

# For flash-jlink target
JLINK_DEVICE = stm32f412zg

flash: flash-dfu-util
erase: erase-jlink
