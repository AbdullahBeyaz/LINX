/****************************************************************************************
**  LINX Devices
**
**
**
****************************************************************************************/

#include "LINX_Config.h"

/****************************************************************************************
**  DIGILENT
****************************************************************************************/

/*----------------------------------------- UNO32 --------------------------------------*/
#ifdef CHIPKIT_UNO32
  //Device ID
  #define DEVICE_FAMILY 1
  #define DEVICE_ID 0
  //Enable Peripheral
  #define LINX_DIGITAL_ENABLED 1
  #define LINX_I2C_ENABLED 1
  //#define LINX_ANALOG_OUTPUT_ENABLED 1
  #define LINX_PWM_ENABLED 1
  #define LINX_SPI_ENABLED 1
  //#define LINX_UART_ENABLED 1
  #define LINX_NVS_ENABLED 1
  
  //Describe Peripherals  
  #define NUMDIOCHANS 44
  unsigned char DIOChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43};
  #define NUMAICHANS 12
  unsigned char AIChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  #define AI_RESOLUTION 10
  #define AI_REFERENCE 3.3
  #define NUMAOCHANS 0
  unsigned char AOChans[] = {};
  #define NUMPWMCHANS 5
  unsigned char PWMChans[] = {3, 5, 6, 9, 10};
  #define NUMQECHANS 0
  unsigned char QEChans[] = {};
  #define NUMUARTCHANS 2
  unsigned char UARTChans[] = {0, 1};
  #define NUMI2CCHANS 1
  unsigned char I2CChans[] = {0};
  #define NUMSPICHANS 1
  unsigned char SPIChans[] = {0};
  #define NUMCANCHANS 0
  unsigned char CANChans[] = {};
#endif //CHIPKIT_UNO32

/*---------------------------------------- UC32 --------------------------------------*/
#ifdef CHIPKIT_UC32
  //Device ID
  #define DEVICE_FAMILY 1
  #define DEVICE_ID 1   
  
  //Enable Peripheral
  #define LINX_DIGITAL_ENABLED 1  
  #define LINX_I2C_ENABLED 1
  #define LINX_ANALOG_INPUT_ENABLED 1  
  //#define LINX_ANALOG_OUTPUT_ENABLED 1
  #define LINX_PWM_ENABLED 1
  #define LINX_SPI_ENABLED 1
  //#define LINX_UART_ENABLED 1
  #define LINX_NVS_ENABLED 1
  
  //Describe Peripherals  
  #define NUMDIOCHANS 47
  unsigned char DIOChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46};
  #define NUMAICHANS 12
  unsigned char AIChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  #define AI_RESOLUTION 10
  #define AI_REFERENCE 3.3
  #define NUMAOCHANS 0
  unsigned char AOChans[] = {};
  #define NUMPWMCHANS 5
  unsigned char PWMChans[] = {3, 5, 6, 9, 10};
  #define NUMQECHANS 0
  unsigned char QEChans[] = {};
  #define NUMUARTCHANS 2
  unsigned char UARTChans[] = {0, 1};
  #define NUMI2CCHANS 1
  unsigned char I2CChans[] = {0};
  #define NUMSPICHANS 1
  unsigned char SPIChans[] = {0};
  #define NUMCANCHANS 0
  unsigned char CANChans[] = {};
#endif //CHIPKIT_UC32

/*---------------------------------------- MAX32 --------------------------------------*/
#ifdef CHIPKIT_MAX32
  //Device ID
  #define DEVICE_FAMILY 1
  #define DEVICE_ID 2
  //Enable Peripheral
  #define LINX_DIGITAL_ENABLED 1
  #define LINX_I2C_ENABLED 1
  #define LINX_ANALOG_INPUT_ENABLED 1
  //#define LINX_ANALOG_OUTPUT_ENABLED 1
  #define LINX_PWM_ENABLED 1
  #define LINX_SPI_ENABLED 1
  #define LINX_UART_ENABLED 1
  #define LINX_NVS_ENABLED 1
  
  //Describe Peripherals  
  #define NUMDIOCHANS 86
  unsigned char DIOChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85};
  #define NUMAICHANS 16
  unsigned char AIChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  #define AI_RESOLUTION 10
  #define AI_REFERENCE 3.3
  #define NUMAOCHANS 0
  unsigned char AOChans[] = {};
  #define NUMPWMCHANS 5
  unsigned char PWMChans[] = {3, 5, 6, 9, 10};
  #define NUMQECHANS 0
  unsigned char QEChans[] = {};
  #define NUMUARTCHANS 3
  unsigned char UARTChans[] = {0, 1, 2, 3};
  #define NUMI2CCHANS 1
  unsigned char I2CChans[] = {0};
  #define NUMSPICHANS 1
  unsigned char SPIChans[] = {0};
  #define NUMCANCHANS 0
  unsigned char CANChans[] = {};
  
#endif //CHIPKIT_MAX32

/*----------------------------------------- WF32 --------------------------------------*/
#ifdef CHIPKIT_WF32
  //Device ID
  #define DEVICE_FAMILY 1
  #define DEVICE_ID 3
  //Peripheral
  #define LINX_DIGITAL_ENABLED 1
  #define LINX_I2C_ENABLED 1
  #define LINX_ANALOG_INPUT_ENABLED 1
   //#define LINX_ANALOG_OUTPUT_ENABLED 1
  #define LINX_PWM_ENABLED 1
  #define LINX_SPI_ENABLED 1
  //#define LINX_UART_ENABLED 1
  #define LINX_NVS_ENABLED 1
  
  //Describe Peripherals  
  #define NUMDIOCHANS 74
  unsigned char DIOChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73};
  #define NUMAICHANS 12
  unsigned char AIChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  #define AI_RESOLUTION 10
  #define AI_REFERENCE 3.3
  #define NUMAOCHANS 0
  unsigned char AOChans[] = {};
  #define NUMPWMCHANS 5
  unsigned char PWMChans[] = {3, 5, 6, 9, 10};
  #define NUMQECHANS 0
  unsigned char QEChans[] = {};
  #define NUMUARTCHANS 2
  unsigned char UARTChans[] = {0, 1};
  #define NUMI2CCHANS 1
  unsigned char I2CChans[] = {0};
  #define NUMSPICHANS 1
  unsigned char SPIChans[] = {0};
  #define NUMCANCHANS 0
  unsigned char CANChans[] = {};
#endif //CHIPKIT_WF32


/****************************************************************************************
**  ARDUINO
****************************************************************************************/

/*----------------------------------------- UNO --------------------------------------*/
#ifdef ARDUINO_UNO
  //Device ID
  #define DEVICE_FAMILY 2
  #define DEVICE_ID 0
  //Peripheral
  #define LINX_DIGITAL_ENABLED 1
  #define LINX_I2C_ENABLED 1
  #define LINX_ANALOG_INPUT_ENABLED 1
  //#define LINX_ANALOG_OUTPUT_ENABLED 1
  #define LINX_PWM_ENABLED 1
  #define LINX_SPI_ENABLED 1
  //#define LINX_UART_ENABLED 1
  #define LINX_NVS_ENABLED 1
  
  //Describe Peripherals  
  #define NUMDIOCHANS 14
  unsigned char DIOChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  #define NUMAICHANS 6
  unsigned char AIChans[] = {0, 1, 2, 3, 4, 5};
  #define AI_RESOLUTION 10
  #define AI_REFERENCE 5
  #define NUMAOCHANS 0
  unsigned char AOChans[] = {};
  #define NUMPWMCHANS 6
  unsigned char PWMChans[] = {3, 5, 6, 9, 10, 11};
  #define NUMQECHANS 0
  unsigned char QEChans[] = {};
  #define NUMUARTCHANS 1
  unsigned char UARTChans[] = {0};
  #define NUMI2CCHANS 1
  unsigned char I2CChans[] = {0};
  #define NUMSPICHANS 1
  unsigned char SPIChans[] = {0};
  #define NUMCANCHANS 0
  unsigned char CANChans[] = {};
#endif //ARDUINO_UNO

/*---------------------------------------- MEGA2560 --------------------------------------*/
#ifdef ARDUINO_MEGA2560
  //Device ID
  #define DEVICE_FAMILY 2
  #define DEVICE_ID 1
  //Peripheral
  #define LINX_DIGITAL_ENABLED 1
  #define LINX_I2C_ENABLED 1
  #define LINX_ANALOG_INPUT_ENABLED 1
  //#define LINX_ANALOG_OUTPUT_ENABLED 1
  #define LINX_PWM_ENABLED 1
  #define LINX_SPI_ENABLED 1
  #define LINX_UART_ENABLED 1
  #define LINX_NVS_ENABLED 1
  
  //Describe Peripherals  
  #define NUMDIOCHANS 54
  unsigned char DIOChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53};
  #define NUMAICHANS 16
  unsigned char AIChans[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  #define AI_RESOLUTION 10
  #define AI_REFERENCE 5
  #define NUMAOCHANS 0
  unsigned char AOChans[] = {};
  #define NUMPWMCHANS 15
  unsigned char PWMChans[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 44, 45, 46};
  #define NUMQECHANS 0
  unsigned char QEChans[] = {};
  #define NUMUARTCHANS 4
  unsigned char UARTChans[] = {0, 1, 2, 3, 4};
  #define NUMI2CCHANS 1
  unsigned char I2CChans[] = {0};
  #define NUMSPICHANS 1
  unsigned char SPIChans[] = {0};
  #define NUMCANCHANS 0
  unsigned char CANChans[] = {};
#endif //CHIPKIT_MAX32
