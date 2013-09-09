/****************************************************************************************
**  Includes
****************************************************************************************/
#include "LINX.h"

#ifdef LINX_I2C_ENABLED
  #include <Wire.h>
#endif //LINX_I2C_ENABLED

#ifdef LINX_SPI_ENABLED
  #include <SPI.h>
#endif //LINX_SPI_ENABLED

/****************************************************************************************
**  Functions
****************************************************************************************/

/****************************************************************************************
**
**--------------------------- COMMON ---------------------------------------------------- 
**
****************************************************************************************/

//--------------------------- setupLINX -----------------------------------------------//
void setupLINX()
{
  // Setup Serial Port For LINX
  #ifdef LINX_SERIAL_INTERFACE_ENABLED
    setupSerial();
  #endif
  
  //Ethernet Setup
  #ifdef LINX_ETHERNET_INTERFACE_ENABLED
    // TODO
  #endif
  
  //WIFI Setup
  #ifdef LINX_WIFI_INTERFACE_ENABLED
    // TODO
  #endif

  //Debugging
  #ifdef DEBUG_ENABLED
    Serial1.begin(115200);
    Serial1.println("Booting Up...");
  #endif  
}


//--------------------------- getDeviceID ---------------------------------------------//
void getDeviceID(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x08;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  #ifdef DEVICE_FAMILY
    responsePacketBuffer[5] = DEVICE_FAMILY;                         //Device Family
  #else
    responsePacketBuffer[5] = 0x00;                                 
  #endif
  #ifdef DEVICE_ID
    responsePacketBuffer[6] = DEVICE_ID;                             //Device ID
  #else
    responsePacketBuffer[6] = 0x00;    
  #endif  
  responsePacketBuffer[7] = computeChecksum(responsePacketBuffer);   //CHECKSUM 
}


//--------------------------- processCommand ------------------------------------------//
void processCommand(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  //Store Some Local Values For Convenience
  unsigned char commandLength = commandPacketBuffer[1];
  unsigned int command = commandPacketBuffer[4] << 8 | commandPacketBuffer[5];
  
  #ifdef DEBUG_ENABLED
    Serial1.print("Processing Packet       ..::");
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
    /************************************************************************************
    * SYSTEM COMMANDS
    ************************************************************************************/
    case 0x0000: // Sync Packet        
      responsePacketBuffer[0] = 0xFF;                                    //SoF
      responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
      responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
      responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
      responsePacketBuffer[4] = 0x00;                                    //STATUS
      responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM         
      break;
      
    case 0x0003: // Get Device ID     
      getDeviceID(commandPacketBuffer, responsePacketBuffer);
      break;
      
    case 0x0005: // Get Max Baud Rate      
      getMaxBaudRate(commandPacketBuffer, responsePacketBuffer);
      break;
      
    case 0x0006: // Set Baud Rate      
      setBaudRate(commandPacketBuffer, responsePacketBuffer);
      break;
      
    /************************************************************************************
    * DIGITAL I/O
    ************************************************************************************/     
    #ifdef LINX_DIGITAL_ENABLED
    case 0x0040: // Set Digital Pin Mode
      linxSetDigtalPinMode(commandPacketBuffer, responsePacketBuffer);      
      break;
      
    case 0x0041: // Digital Write
      linxDigitalWrite(commandPacketBuffer, responsePacketBuffer);      
      break;
      
    case 0x0042: // Digital Read
      linxDigitalRead(commandPacketBuffer, responsePacketBuffer);      
      break;
      
    #endif //LINX_DIGITAL_ENABLED


    /************************************************************************************
    **  Analog I/O
    ************************************************************************************/    
    #ifdef LINX_ANALOG_INPUT_ENABLED
    case 0x0064:  //Analog Read
      linxAnalogRead(commandPacketBuffer, responsePacketBuffer);      
      break;
      
    #endif //LINX_ANALOG_INPUT_ENABLED


    /************************************************************************************
    **  I2C
    ************************************************************************************/     
    #ifdef LINX_I2C_ENABLED
    case 0x00E0: // I2C Open - Master
      linxI2COpenMaster(commandPacketBuffer, responsePacketBuffer);      
      break;
    case 0x00E2: // I2C Write
      linxI2CWrite(commandPacketBuffer, responsePacketBuffer);      
      break;
      
    #endif  //LINX_I2C_ENABLED

    /************************************************************************************
    **  PWM
    ************************************************************************************/     
    #ifdef LINX_PWM_ENABLED
    case 0x0083: // PWM Set Duty Cycle
      linxPWMSetDutyCycle(commandPacketBuffer, responsePacketBuffer);      
      break;
      
    #endif  //LINX_PWM_ENABLED
    
    /************************************************************************************
    **  SPI
    ************************************************************************************/     
    #ifdef LINX_SPI_ENABLED
    case 0x0100: // SPI Open Master
      linxSPIOpenMaster(commandPacketBuffer, responsePacketBuffer);      
      break;
    case 0x0101: // SPI Set Bit Order
      linxSPISetBitOrder(commandPacketBuffer, responsePacketBuffer);      
      break;
    case 0x0103: // SPI Set Mode
      linxSPISetMode(commandPacketBuffer, responsePacketBuffer);      
      break;
    case 0x0104: // SPI Set Frame Size
      //Removed This Command    
      break;
    case 0x0105: // SPI Set CS Logic Level
      //Removed This Command         
      break;
     case 0x0106: // SPI Set CS Pin
      //Removed This Command        
      break;      
    case 0x0107: // SPI Write/Read
      linxSPIWriteRead(commandPacketBuffer, responsePacketBuffer);      
      break;
      
    #endif  //LINX_SPI_ENABLED
      
    default:  //Default Case
       responsePacketBuffer[0] = 0xFF;                                    //SoF
       responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
       responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
       responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
       responsePacketBuffer[4] = 0x01;                                    //STATUS
       responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM     
       break; 
   }
   
   //If Debugging Enabled Print Response Packet
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

//--------------------------- checksumPassed ------------------------------------------//
bool checksumPassed(unsigned char* packetBuffer)
{
  return (computeChecksum(packetBuffer) == packetBuffer[packetBuffer[1]-1]);
}
 
//--------------------------- computeChecksum -----------------------------------------//
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
**
**--------------------------- SERIAL INTERFACE ------------------------------------------ 
**
****************************************************************************************/
#ifdef LINX_SERIAL_INTERFACE_ENABLED

//--------------------------- checkForSerialPacket ------------------------------------//
void checkForSerialPacket()
{ 
  //Check for SoF and Packet Size
  if(Serial.available() >= 2)
  {
    #ifdef DEBUG_ENABLED 
    Serial1.println("SoF and PacketSize Rec..."); 
    #endif
    //Check for valid SoF
    if(Serial.read() == 0xFF)
    {
       //SoF is valid.  Check Packet Size And Copy Packet Data Into Buffer
       //Copy SoF Into Packet Buffer
       #ifdef DEBUG_ENABLED 
       Serial1.println("SoF Passed..."); 
       #endif
       serialCommandBuffer[0] = 0xFF;
       
       serialCommandBuffer[1] = (unsigned char) Serial.read();
       unsigned char packetBytesRemaining = serialCommandBuffer[1] - 2;    
       
       #ifdef DEBUG_ENABLED 
       Serial1.print("Waiting For "); 
       Serial1.print(packetBytesRemaining, DEC);
       Serial1.println(" more bytes..."); 
       #endif
       
       //Wait for the remaining bytes
       while(Serial.available() < packetBytesRemaining);
       
       #ifdef DEBUG_ENABLED
       Serial1.println("Rest Of Packet Received...");
       #endif
       
       //Copy Data From Serial Buffer Into Packet Buffer.
       for(int i=0; i<packetBytesRemaining; i++)
       {
         serialCommandBuffer[i+2] = Serial.read();
       }
       
       #ifdef DEBUG_ENABLED
       Serial1.println("Computing Checksum...");
       #endif
       
       //Full Packet Received - Compute Checksum - Process Packet If Checksum Passes
       if(checksumPassed(serialCommandBuffer))
       {
         #ifdef DEBUG_ENABLED
         Serial1.println("Checksum Passed...");
         #endif
         //Process Packet
         processCommand(serialCommandBuffer, serialResponseBuffer);
        
         //Send Response Packet         
         Serial.write(serialResponseBuffer, serialResponseBuffer[1]);   
       }
       else
       {         
         //Checksum Failed
         #ifdef DEBUG_ENABLED
         Serial1.println("Checksum Failed...");
         #endif         
         Serial.flush();
       }  
    }
    else
    {
      //SoF Incorrect - Corrupt Packet - Flush Buffer.
      #ifdef DEBUG_ENABLED 
      Serial1.println("SoF Failed..."); 
      #endif
      Serial.flush();      
    }   
  }
}

//--------------------------- setupSerial ---------------------------------------------//
void setupSerial()
{
  //Serial Setup  
  Serial.begin(9600);
}

//--------------------------- setBaudRate ---------------------------------------------//
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

//--------------------------- getMaxBaudRate ------------------------------------------//
void getMaxBaudRate(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  
  #ifdef MAX_BAUD_RATE
  unsigned long baudRate = MAX_BAUD_RATE;
  #else
  unsigned long baudRate = 9600;
  #endif
  
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
#endif  //LINX_SERIAL_INTERFACE_ENABLED



/****************************************************************************************
**
**--------------------------- DIGITAL IO ------------------------------------------------ 
**
****************************************************************************************/
#ifdef LINX_DIGITAL_ENABLED

//--------------------------- linxDigitalWrite ----------------------------------------//
void linxDigitalWrite(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{  
  int dirBit = 0;
  int dirByte = 0;
  int pinOffset = 0;
  
  while(pinOffset < commandPacketBuffer[6])
  {
    
    unsigned char digitalPin = (commandPacketBuffer[7 + pinOffset]);
    unsigned char digitalVal = ( ( commandPacketBuffer[( (commandPacketBuffer[6] + 7) + dirByte)] >> dirBit) & 0x01);
    
    #ifdef DEBUG_ENABLED          
      Serial1.print("digitalWrite(");
      Serial1.print(digitalPin, DEC);
      Serial1.print(", ");
      Serial1.print(digitalVal, DEC);
      Serial1.println(")");
    #endif       
    
    pinMode(digitalPin, OUTPUT);
    digitalWrite(digitalPin, digitalVal);
    
    //Increment Counters
    if(dirBit < 7)
    {
      dirBit++; 
    }
    else
    {
      dirBit = 0; 
      dirByte++;
    }
    pinOffset++;
  }
  
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM   
}


//--------------------------- linxDigitalRead -----------------------------------------//
void linxDigitalRead(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  
  unsigned char bitOffset = 8;
  unsigned char byteOffset = 5;
  unsigned char retVal = 0;
  
  //Loop Over Pins To Read
  for(int i=0; i<commandPacketBuffer[1]-7; i++)
  {
    //Increment Offsets
    if(bitOffset == 0)
    {
      //Insert retVal Into Response Buffer
      responsePacketBuffer[byteOffset] = retVal;
      retVal = 0x00;
      byteOffset++;
      bitOffset = 7;      
    }
    else
    {
      bitOffset--;      
    } 
    
    unsigned char pinNumber = commandPacketBuffer[6+i];
    
    //Set Pin As Input (Might Make This Configurable)    
    pinMode(pinNumber, INPUT);
    
    //Read Pin And Insert Value Into retVal
    retVal = retVal | (digitalRead(pinNumber) << bitOffset);
  }
  responsePacketBuffer[byteOffset] = retVal;
  
  //Fill In The Rest Of The Response Packet
  responsePacketBuffer[0] = 0xFF;                                                //SoF
  responsePacketBuffer[1] = byteOffset + 2;                                      //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                              //PACKET NUM 
  responsePacketBuffer[3] = commandPacketBuffer[3];                              //PACKET NUM 
  responsePacketBuffer[4] = 0x00;                                                //STATUS
  responsePacketBuffer[byteOffset + 1] = computeChecksum(responsePacketBuffer);  //CHECKSUM   
}


//--------------------------- linxSetDigitalPinMode -----------------------------------//
void linxSetDigtalPinMode(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  int dirBit = 0;
  int dirByte = 0;
  int pinOffset = 0;
  
  while(pinOffset < commandPacketBuffer[6])
  {
    
    unsigned char digitalPin = (commandPacketBuffer[7 + pinOffset]);
    unsigned char digitalVal = ( ( commandPacketBuffer[( (commandPacketBuffer[6] + 7) + dirByte)] >> dirBit) & 0x01);
    
    #ifdef DEBUG_ENABLED          
      Serial1.print("pinMode(");
      Serial1.print(digitalPin, DEC);
      Serial1.print(", ");
      Serial1.print(digitalVal, DEC);
      Serial1.println(")");
    #endif       
    
    pinMode(digitalPin, digitalVal);
    
    //Increment Counters
    if(dirBit < 7)
    {
      dirBit++; 
    }
    else
    {
      dirBit = 0; 
      dirByte++;
    }
    pinOffset++;
  }
  
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM   
}
#endif  //LINX_DIGITAL_ENABLED


/****************************************************************************************
**
**--------------------------- I2C ------------------------------------------------------- 
**
****************************************************************************************/
#ifdef LINX_I2C_ENABLED

//--------------------------- linxI2CClose --------------------------------------------//
void linxI2CClose(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  //Nothing To Do Here....   
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM  
   
}

 
//--------------------------- linxI2COpenMaster ---------------------------------------//
void linxI2COpenMaster(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  Wire.begin();
    
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM  
}
 
 
//--------------------------- linxI2CWrite --------------------------------------------//
void linxI2CWrite(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  Wire.beginTransmission(commandPacketBuffer[7]);
  for(int i=0; i<(commandPacketBuffer[1] - 8); i++)
  {
    Wire.send(commandPacketBuffer[i+7]);
  }
  Wire.endTransmission();
  
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM  
}

#endif  //LINX_I2C_ENABLED

/****************************************************************************************
**
**--------------------------- ANALOG INPUT ---------------------------------------------- 
**
****************************************************************************************/
#ifdef LINX_ANALOG_INPUT_ENABLED

//--------------------------- linxAnalogRead ------------------------------------------//
void linxAnalogRead(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  //Prep Response Packet
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = AI_RESOLUTION;                           //RESOLUTION 
  
  unsigned int analogValue = 0;
  unsigned char currentResponseOffset = 6;
  unsigned char responseBitsRemaining = 8; 
  unsigned char dataBitsRemaining = AI_RESOLUTION;
  
  responsePacketBuffer[currentResponseOffset] = 0x00;    //Clear Next Response Byte   
  
  //Loop Over All AI Pins In Command Packet
  for(int i=0; i<(commandPacketBuffer[1]-7); i++)
  {
    analogValue = analogRead(commandPacketBuffer[i+6]);
    //analogValue = 0x03BD;  //0b1110111101
    
    #ifdef DEBUG_ENABLED
      Serial1.print("AI");
      Serial1.print(commandPacketBuffer[i+6], DEC);
      Serial1.print(" Value = ");
      Serial1.println(analogValue, HEX);
    #endif
    
    dataBitsRemaining = AI_RESOLUTION;
    
    //Byte Packet AI Values In Response Packet
    while(dataBitsRemaining > 0)
    {
      responsePacketBuffer[currentResponseOffset] |= ( (analogValue>>(AI_RESOLUTION - dataBitsRemaining)) << (8 - responseBitsRemaining) );
       
      if(responseBitsRemaining > dataBitsRemaining)
      {
        //Current Byte Still Has Empty Bits
        responseBitsRemaining -= dataBitsRemaining;
        dataBitsRemaining = 0;
      }
      else
      {
        //Current Byte Full
        dataBitsRemaining = dataBitsRemaining - responseBitsRemaining;
        currentResponseOffset++;
        responseBitsRemaining = 8;
        responsePacketBuffer[currentResponseOffset] = 0x00;    //Clear Next Response Byte     
      } 
    } 
  }
  
  //Complete Response Packet
  if(responseBitsRemaining == 8)
  {
    responsePacketBuffer[1] = currentResponseOffset+1;                                       //PACKET SIZE
    responsePacketBuffer[currentResponseOffset] = computeChecksum(responsePacketBuffer);     //CHECKSUM    
  }
  else
  {     
    responsePacketBuffer[1] = currentResponseOffset+2;                                       //PACKET SIZE
    responsePacketBuffer[currentResponseOffset+1] = computeChecksum(responsePacketBuffer);   //CHECKSUM 
  }  
}

#endif  //LINX_ANALOG_INPUT_ENABLED


/****************************************************************************************
**
**--------------------------- PWM ------------------------------------------------------ 
**
****************************************************************************************/


#ifdef LINX_PWM_ENABLED

//--------------------------- linxPWMSetDutyCycle -------------------------------------//
void linxPWMSetDutyCycle(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  //Loop Over All PWM Pins To Set
  for(int i=0; i<commandPacketBuffer[6]; i++)
  {
    //Config PWM Pin As Output
    pinMode(commandPacketBuffer[i+7], OUTPUT);
    
    //Set Duty Cycle
    analogWrite(commandPacketBuffer[i+7], commandPacketBuffer[i+7+commandPacketBuffer[6]]);
  }  
  
  //Build Response Packet
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM  
}


#endif  //LINX_PWM_ENABLED

/****************************************************************************************
**
**--------------------------- SPI ------------------------------------------------------ 
**
****************************************************************************************/
#ifdef LINX_SPI_ENABLED

//--------------------------- linxSPIO ------------------------------------------------//
void linxSPIOpenMaster(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  SPI.begin();
  
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM  
}


//--------------------------- linxSPISetBitOrder --------------------------------------//
void linxSPISetBitOrder(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  SPI.setBitOrder(commandPacketBuffer[7]);
  
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM    
}


//--------------------------- linxSPISetMode ------------------------------------------//
void linxSPISetMode(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  SPI.setDataMode(commandPacketBuffer[7]);
  
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = 0x06;                                    //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  responsePacketBuffer[5] = computeChecksum(responsePacketBuffer);   //CHECKSUM    
}

//--------------------------- linxSPIWriteRead ----------------------------------------//
void linxSPIWriteRead(unsigned char* commandPacketBuffer, unsigned char* responsePacketBuffer)
{
  unsigned char numDataBytes = commandPacketBuffer[1] - 11;
  unsigned char frameSize = commandPacketBuffer[7];
  unsigned char SPI_csPin = commandPacketBuffer[8];
  unsigned char SPI_csActiveHigh = commandPacketBuffer[9];
  unsigned char byteCounter = 0;
  
  
  //Prep responsePacketBuffer
  responsePacketBuffer[0] = 0xFF;                                    //SoF
  responsePacketBuffer[1] = numDataBytes + 6;                        //PACKET SIZE
  responsePacketBuffer[2] = commandPacketBuffer[2];                  //PACKET NUM (MSB)
  responsePacketBuffer[3] = commandPacketBuffer[3];                  //PACKET NUM (LSB)
  responsePacketBuffer[4] = 0x00;                                    //STATUS
  
  //Set CS Pin As DO
  pinMode(SPI_csPin, OUTPUT);
  
  //Set CS Pin Before Starting SPI Transfer
  digitalWrite(SPI_csPin, (SPI_csActiveHigh ^ 0x01));  
  
  //Loop Over Data To Send, Send And Build Response
  for(int i=0; i<numDataBytes; i++)
  {
    if(byteCounter == 0)
    {
      //Start Frame
      digitalWrite(SPI_csPin, SPI_csActiveHigh);      
    }   
    
    responsePacketBuffer[i+5] = SPI.transfer(commandPacketBuffer[i+10]);
    byteCounter++;
   
    if(byteCounter == frameSize)
    {
      //End Of Frame
      digitalWrite(SPI_csPin, (SPI_csActiveHigh ^ 0x01));
      byteCounter = 0; 
      //May Need A Delay Here Depending On SPI Device      
    }   
  }
  
  //Add Response Packet Checksum
  responsePacketBuffer[numDataBytes + 5] = computeChecksum(responsePacketBuffer);   //CHECKSUM    
}

#endif  //LINX_SPI_ENABLED


