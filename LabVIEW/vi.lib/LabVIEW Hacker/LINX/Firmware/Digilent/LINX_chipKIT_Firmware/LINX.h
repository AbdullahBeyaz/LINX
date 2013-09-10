//Prevent Multiple Includes
#ifndef LINX_H
#define LINX_H

/****************************************************************************************
**  Includes
****************************************************************************************/
#include "LINX_Config.h"

/****************************************************************************************
**  Variables
****************************************************************************************/
#ifdef LINX_SERIAL_INTERFACE_ENABLED
  //LINX Serial Packet Send / Receive Buffers
  unsigned char serialCommandBuffer[64];
  unsigned char serialResponseBuffer[64];
#endif


/****************************************************************************************
**  Functions
****************************************************************************************/


/****************************************************************************************
**
**--------------------------- COMMON ---------------------------------------------------- 
**
****************************************************************************************/


/****************************************************************************************
**  checksumPassed
**
**  Check the specified packet buffer to see if the checksum passes
**
**  Input:  packetBuffer - pointer to a packet buffer
**  Output: True if the checksum passes, false otherwise
****************************************************************************************/
bool checksumPassed(unsigned char* packetBuffer); 

  
/****************************************************************************************
**  computeChecksum
**
**  Compute the checksum for the user specified packet buffer.
**
**  Input:  packetBuffer - Pointer to a packet buffer
**  Output: The checksum value
****************************************************************************************/
unsigned char computeChecksum(unsigned char* packetBuffer);


/****************************************************************************************
**  getDeviceID
**
**  Return the device family and device ID.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: None
****************************************************************************************/
void getDeviceID(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  getMaxBaudRate
**
**  Generate a resposne packet containing the device's maximum supported baud rate.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: None
****************************************************************************************/
void getMaxBaudRate(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  processCommand
**
**  Process a LINX command packet and generate a response packet
**
**  Input:  packetBuffer - pointer to a packet buffer
**  Output: True if the checksum passes, false otherwise 
****************************************************************************************/
void processCommand(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  setupLINX
**
**  Setup the LINX device
**
**  Input:  none
**  Output: non
****************************************************************************************/
void setupLINX();

/****************************************************************************************
**  statusResponse
**
**  Build a basic response packet with the specified status.
**
**  Input:  none
**  Output: non
****************************************************************************************/
void statusResponse(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer, unsigned char linxStatus);


/****************************************************************************************
**
**--------------------------- SERIAL INTERFACE ------------------------------------------ 
**
****************************************************************************************/
#ifdef LINX_SERIAL_INTERFACE_ENABLED

/****************************************************************************************
**  checkForSerialPacket
**
**  Check Serial Buffer For LINX Command Packet.  If Full Packet Exists And Checksum 
**  Passes Process The Command.
**
**  Input:  None
**  Output: None
****************************************************************************************/
void checkForSerialPacket();


/****************************************************************************************
**  setupSerial
**
**  Initialize The Serial Port For LINX Communication To The Host.
**
**  Input:  None
**  Output: None
****************************************************************************************/
void setupSerial();


/****************************************************************************************
**  setBaudRate
**
**  Sets the serial baud rate that the LINX device uses to talk to the host.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: None
****************************************************************************************/
void setBaudRate(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);
#endif  //LINX_SERIAL_INTERFACE_ENABLED


/****************************************************************************************
**
**--------------------------- DIGITAL IO ------------------------------------------------ 
**
****************************************************************************************/
#ifdef LINX_DIGITAL_ENABLED

/****************************************************************************************
**  linxDigitalWrite
**
**  Write Digital Values Based On Digital Write Command Packet
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxDigitalWrite(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxDigitalRead
**
**  Read Digital Values Based On Digital Read Command Packet
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxDigitalRead(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxSetDigtalPinMode
**
**  Set The Digital Pin Mode Based On The Set Digital Pin Mode Packet
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxSetDigtalPinMode(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);
#endif  //LINX_DIGITAL_ENABLED


/****************************************************************************************
**
**--------------------------- I2C ------------------------------------------------------- 
**
****************************************************************************************/
#ifdef LINX_I2C_ENABLED


/****************************************************************************************
**  linxI2CClose
**
**  Close the specified I2C channel.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxI2CClose(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxI2COpenMaster
**
**  Open the specified I2C channel and join as master.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxI2COpenMaster(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxI2CWrite
**
**  Write bytes to the specified I2C channel
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxI2CWrite(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);
#endif  //LINX_I2C_ENABLED



/****************************************************************************************
**
**--------------------------- ANALOG INPUT ---------------------------------------------- 
**
****************************************************************************************/
#ifdef LINX_ANALOG_INPUT_ENABLED


/****************************************************************************************
**  linxAnalogRead
**
**  Read values from the specified AI pins
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxAnalogRead(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


#endif  //LINX_ANALOG_INPUT_ENABLED


/****************************************************************************************
**
**--------------------------- PWM ------------------------------------------------------ 
**
****************************************************************************************/
#ifdef LINX_PWM_ENABLED

/****************************************************************************************
**  linxPWMSetDutyCycle
**
**  Set the duty cycle of the specified PWM channels
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxPWMSetDutyCycle(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);

#endif  //LINX_PWM_ENABLED


/****************************************************************************************
**
**--------------------------- SPI ------------------------------------------------------ 
**
****************************************************************************************/

#ifdef LINX_SPI_ENABLED

/****************************************************************************************
**  linxSPIOpenMaster
**
**  Open the specfified SPI channel as master.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxSPIOpenMaster(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxSPISetBitOrder
**
**  Set the bit order of the specified SPI Channel.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxSPISetBitOrder(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);

/****************************************************************************************
**  .: TODO :.
**  linxSPISetClockRate
**
**  Set the clock rate of the specified SPI channel.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxSPISetBaudRate(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxSPISetMode
**
**  Set the data mode of the specified SPI Channel.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxSPISetMode(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxSPISetFrameSize
**
**  Set the frame size in bytes for the specified SPI Channel.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxSPISetFrameSize(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);

/****************************************************************************************
**  linxSPIWriteRead
**
**  Write/Read the specified SPI channel.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxSPIWriteRead(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


#endif  //LINX_SPI_ENABLED


/****************************************************************************************
**
**--------------------------- UART ------------------------------------------------------ 
**
****************************************************************************************/

#ifdef LINX_UART_ENABLED

/****************************************************************************************
**  linxUARTOpen
**
**  Open the UART channel with the specified baud rate.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxUARTOpen(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxUARTSetBaudRate
**
**  Set the buad rate of the specified UART channel.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxUARTSetBaudRate(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxUARTGetBytesAvailable
**
**  Get the number of bytes available in the specified UART channel receive buffer.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxUARTGetBytesAvailable(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxUARTRead
**
**  Read the specified number of bytes from the specified UART channel's receive buffer.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxUARTRead(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxUARTWrite
**
**  Transmit data using the specified UART channel.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxUARTWrite(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


/****************************************************************************************
**  linxUARTClose
**
**  Close the specified UART channel.
**
**  Input:  commandPacketBuffer - The buffer containing the command packet
**          responsePacketBuffer - The buffer used build the response packet.
**  Output: none
****************************************************************************************/
void linxUARTClose(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer);


#endif //LINX_UART_ENABLED

#endif //LINX_H

