# Mbed-os example application of a Zigbee on-off switch

This demo application shows how to create a Zigbee Home Automation device with mbed-os.

## requirements

STM32 NucleoF496ZG development board.

(any other board would require to override the TARGET PIN mapping)

## Wiring

![wiring f496zg](https://github.com/geoffrey-vl/mbed-os-zigbeehomeautomation-onoffswitch/blob/master/doc/wiring_stm32nucleof496zg.jpeg)

## from source
Compile using mbed tools and gcc:

    mbed compile --profile=mbed-os/tools/profiles/debug.json -t GCC_ARM -m NUCLEO_L496ZG
