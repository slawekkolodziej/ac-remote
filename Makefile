PROGRAM=ac_remote
EXTRA_COMPONENTS = extras/paho_mqtt_c extras/mbedtls
PROGRAM_EXTRA_SRC_FILES= ./config/ssid.h ./config/client.c

include .env
include $(OPEN_RTOS_PATH)/common.mk
