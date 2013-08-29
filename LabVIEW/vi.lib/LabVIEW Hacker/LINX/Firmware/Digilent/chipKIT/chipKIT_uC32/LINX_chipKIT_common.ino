/*********************************************************************************
 **
 **  LINX_chipKIT_Common - chipKIT LINX fimrware common functions
 **
 **  Written By:    Sam K
 **  Written On:    August 2013
 **  Last Updated:  August 2013 - Sam K
 **
 **  This File May Be Modified And Re-Distributed Freely. Original File Content
 **  Written By Sam K And Available At www.github.com/labviewhacker/LVH-LINX
 **
 *********************************************************************************/
 
 
/*********************************************************************************
**  computeChecksum - Compute the checksum for the user specified packet buffer.
*********************************************************************************/
unsigned char computeChecksum(unsigned char* packetBuffer)
{  
  unsigned char checksum = 0;
  
  //Sum All Bytes In The Packet Except The Last (Checksum Byte)
  for(int i=0; i<(packetBuffer[1] - 1); i++)
  {
    checksum += packetBuffer[i];
  }  
  return checksum; 
}

/****************************************************************************************
**  checksumPassed - Check the user specified packet buffer to see if the checksum passes
*****************************************************************************************/
//  
bool checksumPassed(unsigned char* packetBuffer)
{
  return (computeChecksum(packetBuffer) == packetBuffer[packetBuffer[1]-1]);
}

/****************************************************************************************
**  Generate a resposne packet containing the device's maximum supported baud rate.
*****************************************************************************************/
void gatMaxBaudRate(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  
  unsigned long baudRate = 115200;
  
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x0A;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = (baudRate >> 24) & 0xFF;                 //Baud Rate MSB
  responsePacketBuffer[6] = (baudRate >> 16) & 0xFF;      
  responsePacketBuffer[7] = (baudRate >> 8) & 0xFF;   
  responsePacketBuffer[8] = (baudRate) & 0xFF;                       //Baud Rate LSB
  responsePacketBuffer[9] = computeChecksum(responsePacketBuffer);   //CHECKSUM 
}

/****************************************************************************************
**  processCommand - Process a LINX command packet and generate a response packet
*****************************************************************************************/
void processCommand(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  //Store Some Local Values For Convenience
  unsigned char commandLength = commandPacketBuffer[1];
  unsigned int command = commandPacketBuffer[4] << 8 | commandPacketBuffer[5];
  
  #ifdef DEBUG_ENABLED
    Serial1.print("Processing Packet ..::");
    for(int i=0; i<commandLength; i++)
    {
      Serial1.print("[");
      Serial1.print(commandPacketBuffer[i], HEX);
      Serial1.print("]");
    }
    Serial1.println("::..");
  #endif
  
  //Process Command
  
  switch(command)
  {
    /****************************************************************************************
    * SYSTEM COMMANDS
    ****************************************************************************************/
    case 0x0000: // Sync Packet        
      responsePacketBuffer[0] = 0xFF;                                    //SoF
      responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
      responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
      responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
      responsePacketBuffer[4] = 0x00;                                    //STATUS
      responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM         
      break;
      
    case 0x0005: // Get Max Baud Rate      
      gatMaxBaudRate(commandPacketBuffer, responsePacketBuffer);
      break;
      
    case 0x0006: // Set Baud Rate      
      setBaudRate(commandPacketBuffer, responsePacketBuffer);
      break;
      
    /****************************************************************************************
    * Digital I/O
    ****************************************************************************************/     
    case 0x0040: // Set Digital Pin Mode
      linxSetDigtalPinMode(commandPacketBuffer, responsePacketBuffer);      
      break;
    case 0x0041: // Digital Write
      linxDigitalWrite(commandPacketBuffer, responsePacketBuffer);      
      break;
      
    default:  //Default Case
       responsePacketBuffer[0] = 0xFF;                                    //SoF
       responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
       responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
       responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
       responsePacketBuffer[4] = 0x01;                                    //STATUS
       responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM     
       break; 
   }
  
  //Send Response Packet
  #ifdef DEBUG_ENABLED 
    Serial1.print("Sending Response Packet ..::"); 
    for(int i=0; i<responsePacketBuffer[1]; i++)
    {  
      Serial1.print("[");
      Serial1.print(responsePacketBuffer[i], HEX);
      Serial1.print("]");      
    }
    Serial1.println("::..");
  #endif  
}

/****************************************************************************************
**  Sets the serial baud rate that the LINX device uses to talk to the host.
*****************************************************************************************/
void setBaudRate(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
       Serial.end();
       Serial.begin( (commandPacketBuffer[6]<<24) + (commandPacketBuffer[7]<<16) + (commandPacketBuffer[8]<<8) + (commandPacketBuffer[9]));
       delay(1000);   //Give Host Time To Update Serial Baud Rate 
       
       responsePacketBuffer[0] = 0xFF;                                    //SoF
       responsePacketBuffer[1] = 0x08;                                    //PACKET SIZE
       responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
       responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
       responsePacketBuffer[4] = 0x00;                                    //STATUS
       responsePacketBuffer[5] = 0x13;                                    //Delay MSB (ms)
       responsePacketBuffer[6] = 0x88;                                    //Delay LSB (ms)
       responsePacketBuffer[7] = computeChecksum(responsePacketBuffer);   //CHECKSUM  
}

/****************************************************************************************
**  setupLINX - Enable the user specified interface for LINX communication
*****************************************************************************************/
void setupLINX()
{
  // Setup Serial Port For LINX
  #ifdef SERIAL_ENABLED
    setupSerial();
  #endif
  
  //Ethernet Setup
  #ifdef ETHERNET_ENABLED
    // TODO
  #endif
  
  //WIFI Setup
  #ifdef WIFI_ENABLED
    // TODO
  #endif

  //Debugging
  #ifdef DEBUG_ENABLED
    Serial1.begin(115200);
    Serial1.println("Booting Up...");
  #endif  
}
