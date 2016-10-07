include .env

PROGRAM=ac_remote
PROGRAM_EXTRA_SRC_FILES= ./config/ssid.h ./config/client.c
EXTRA_COMPONENTS = extras/paho_mqtt_c extras/mbedtls lib/ir_remote
SHELL := env PATH=$(ESP_OPEN_SDK_BIN):$(PATH) $(SHELL)

include $(OPEN_RTOS_PATH)/common.mk
