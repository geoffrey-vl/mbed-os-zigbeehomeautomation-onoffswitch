#include "mbed.h"
#include "XBeeLib.h"
#if defined(ENABLE_LOGGING)
#include "DigiLoggerMbedSerial.h"
using namespace DigiLog;
#endif

DigitalOut ledOk(LED1);
DigitalOut ledErr(LED3);
 

Serial* log_serial;

using namespace XBeeLib;

int main() {
    ledOk = 1;
    /* Open and configure a new serial port on the USB connected to the PC */
    log_serial = new Serial(STDIO_UART_TX, STDIO_UART_RX, MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE);
    log_serial->printf("#######################" XB_LIB_BANNER);
 
#if defined(ENABLE_LOGGING)
    /* Create a DigiLogger object, tell it to use the opened serial port and initially set LogLevel to LogLevelDebug */
    DigiLoggerMbedSerial *logger = new DigiLoggerMbedSerial(log_serial, LogLevelDebug); 
#endif

    XBeeZB xbee = XBeeZB();
    RadioStatus initResult = xbee.init();
    if(initResult == Success) {
        digi_log(LogLevelInfo, "Init done!\r\n");
    }
    else {
        ledErr = 1;
        digi_log(LogLevelError, "Init failed!\r\n");
    }

    uint32_t val;
    AtCmdFrame::AtCmdResp cmdresp = xbee.get_param("MY", &val);
    // Print the value of the parameter if it was correctly read
    if (cmdresp == AtCmdFrame::AtCmdRespOk) {
        digi_log(LogLevelInfo, "MY=%lu\r\n", val);
    }
    else {
        ledErr = 1;
        digi_log(LogLevelError, "MY FAILED with %d\r\n", (int) cmdresp);
    } 
    ledOk = 0;
}