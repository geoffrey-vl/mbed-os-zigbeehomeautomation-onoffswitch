/**
 * 
 * Notes:
 * Make sure to put zigbee nodes radio always on. Devices that are sleeping will also not respond to UART data
 */ 


#include "mbed.h"
#include "XBeeLib.h"
#if defined(ENABLE_LOGGING)
#include "DigiLoggerMbedSerial.h"
using namespace DigiLog;
#endif

DigitalOut ledGreen(LED1);
DigitalOut ledRed(LED3);
 

Serial* log_serial;

using namespace XBeeLib;

int main() {
    ledGreen = 1;

    // Open and configure a new serial port on the USB connected to the PC 
    log_serial = new Serial(STDIO_UART_TX, STDIO_UART_RX, MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE);
    log_serial->printf("#######################" XB_LIB_BANNER);
 
#if defined(ENABLE_LOGGING)
    // Create a DigiLogger object, tell it to use the opened serial port and initially set LogLevel to LogLevelDebug 
    DigiLoggerMbedSerial *logger = new DigiLoggerMbedSerial(log_serial, LogLevelDebug); 
#endif

    XBeeZB xbee = XBeeZB();
    RadioStatus initResult = xbee.init();
    if(initResult == Success) {
        xbee.set_DIO("D1", true);
        int16_t hwversion = xbee.get_hw_version();
        int16_t fwversion = xbee.get_fw_version();
        digi_log(LogLevelInfo, "Init done! HW=%d FW=%d\r\n", hwversion, fwversion);
    }
    else {
        ledRed = 1;
        digi_log(LogLevelError, "Init failed!\r\n");
        //exit(-1);
    }

    uint32_t val;
    AtCmdFrame::AtCmdResp cmdresp = xbee.get_param("MY", &val);
    // Print the value of the parameter if it was correctly read
    if (cmdresp == AtCmdFrame::AtCmdRespOk) {
        digi_log(LogLevelInfo, "MY=%lu\r\n", val);
    }
    else {
        ledRed = 1;
        digi_log(LogLevelError, "MY FAILED with %d\r\n", (int) cmdresp);
    } 
    ledGreen = 0;
    xbee.set_DIO("D1", false);
}

