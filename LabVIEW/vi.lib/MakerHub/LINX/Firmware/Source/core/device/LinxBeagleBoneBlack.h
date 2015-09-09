/****************************************************************************************
**  LINX header for BeagleBone Black
**
**  For more information see:           www.labviewmakerhub.com/linx
**  For support visit the forums at:    www.labviewmakerhub.com/forums/linx
**  
**  Written By Sam Kristoff
**
** BSD2 License.
****************************************************************************************/	

#ifndef LINX_BEAGLEBONEBLACK_H
#define LINX_BEAGLEBONEBLACK_H


/****************************************************************************************
**  Defines
****************************************************************************************/	
#define DEVICE_NAME_LEN 17

#define NUM_AI_CHANS 8
#define AI_RES_BITS 12
#define AI_REFV 1800000
#define NUM_AI_INT_REFS 0

#define NUM_DIGITAL_CHANS 65

#define NUM_PWM_CHANS 4

#define NUM_SPI_CHANS 2
#define NUM_SPI_SPEEDS 13

#define NUM_I2C_CHANS 3

#define NUM_UART_CHANS 6
#define NUM_UART_SPEEDS 19

#define NUM_SERVO_CHANS 0

/****************************************************************************************
**  Includes
****************************************************************************************/	
#include "utility/LinxDevice.h"
#include "utility/LinxBeagleBone.h"
#include <map>

using namespace std;
	
class LinxBeagleBoneBlack : public LinxBeagleBone
{
	public:	
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		//System
		static const unsigned char m_DeviceName[DEVICE_NAME_LEN];
		
		//AI
		static const unsigned char m_AiChans[NUM_AI_CHANS];
		static const unsigned long m_AiRefIntVals[NUM_AI_INT_REFS];
		static const int m_AiRefCodes[NUM_AI_INT_REFS];		
		static int m_AiHandles[NUM_AI_CHANS];		
		static const char m_AiPaths[NUM_AI_CHANS][AI_PATH_LEN];
		
		//AO
		//None
		
		//DIGITAL
		static const unsigned char m_DigitalChans[NUM_DIGITAL_CHANS];
		
		//PWM
		static const unsigned char m_PwmChans[NUM_PWM_CHANS];
		static const char m_PwmDirPaths[NUM_PWM_CHANS][PWM_PATH_LEN];
		static const char m_PwmDtoNames[NUM_PWM_CHANS][PWM_DTO_NAME_LEN];
		
		//SPI
		static const unsigned char m_SpiChans[NUM_SPI_CHANS];
		//static const char m_SpiPaths[NUM_SPI_CHANS][SPI_PATH_LEN];
		static unsigned long m_SpiSupportedSpeeds[NUM_SPI_SPEEDS];
		static int m_SpiSpeedCodes[NUM_SPI_SPEEDS];
		static int m_SpiHandles[NUM_SPI_CHANS];
		
		//I2C
		static unsigned char m_I2cChans[NUM_I2C_CHANS];
		static unsigned char m_I2cRefCount[NUM_I2C_CHANS];	
	    static int m_I2cHandles[NUM_I2C_CHANS];		
		static const char m_I2cPaths[NUM_I2C_CHANS][I2C_PATH_LEN];
		
		//UART
		static unsigned char m_UartChans[NUM_UART_CHANS];
		static unsigned long m_UartSupportedSpeeds[NUM_UART_SPEEDS];
		static unsigned long m_UartSupportedSpeedsCodes[NUM_UART_SPEEDS];
		static int m_UartHandles[NUM_UART_CHANS];
		static const char m_UartPaths[NUM_UART_CHANS][UART_PATH_LEN];

		
		//Servo		
		//static const unsigned char m_ServoChans[NUM_SERVO_CHANS];
		//static Servo* m_Servos[NUM_SERVO_CHANS];
		
		/****************************************************************************************
		**  Constructors /  Destructor
		****************************************************************************************/
		LinxBeagleBoneBlack();
		~LinxBeagleBoneBlack();

		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
	private:
		/****************************************************************************************
		**  Variables
		****************************************************************************************/		
		const char* overlaySlotsPath;		//The overlay slot export path
		
		/****************************************************************************************
		**  Functions
		****************************************************************************************/
		
		
};


#endif //LINX_BEAGLEBONEBLACK_H