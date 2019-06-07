/**************************************************************************/
/**
  @file     Adafruit_MCP9600.h

  Author: K. Townsend (Adafruit Industries)
  License: BSD (see license.txt)

  This is a library for the Aadafruit MCP9600 I2C Thermocouple breakout board
  ----> http://www.adafruit.com/products/

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  v1.0  - First release
*/
/**************************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>

/** Default MCP9600 I2C address. */
#define MCP9600_I2CADDR_DEFAULT 0x67 ///< I2C address

#define MCP9600_HOTJUNCTION     0x00 ///< Hot junction temperature T_H
#define MCP9600_JUNCTIONDELTA   0x01 ///< Hot/Cold junction delta
#define MCP9600_COLDJUNCTION    0x02 ///< Hot junction temperature T_C
#define MCP9600_RAWDATAADC      0x03 ///< The 'raw' uV reading
#define MCP9600_STATUS          0x04 ///< Current device status
#define MCP9600_SENSORCONFIG    0x05 ///< Configuration for thermocouple type
#define MCP9600_DEVICECONFIG    0x06 ///< Device config like sleep mode
#define MCP9600_DEVICEID        0x20 ///< Device ID/Revision
#define MCP9600_ALERTCONFIG_1   0x08 ///< The first alert's config
#define MCP9600_ALERTHYST_1     0x0C ///< The first alert's hystersis
#define MCP9600_ALERTLIMIT_1    0x10 ///< the first alert's limitval
  
typedef enum _themotype {
  MCP9600_TYPE_K,
  MCP9600_TYPE_J,
  MCP9600_TYPE_T,
  MCP9600_TYPE_N,
  MCP9600_TYPE_S,
  MCP9600_TYPE_E,
  MCP9600_TYPE_B,
  MCP9600_TYPE_R,
} MCP9600_ThemocoupleType;

typedef enum _resolution {
  MCP9600_ADCRESOLUTION_18,
  MCP9600_ADCRESOLUTION_16,
  MCP9600_ADCRESOLUTION_14,
  MCP9600_ADCRESOLUTION_12,
} MCP9600_ADCResolution;



/**************************************************************************/
/*!
    @brief  MCP9600 driver.
*/
/**************************************************************************/
class Adafruit_MCP9600 {
    public:
        Adafruit_MCP9600();
        boolean begin(uint8_t i2c_addr = MCP9600_I2CADDR_DEFAULT, TwoWire *theWire = &Wire);;

	float readThermocouple(void);
	float readAmbient(void);

	void  enable(bool flag);
	bool  enabled(void);

	MCP9600_ThemocoupleType getThermocoupleType(void);
	void setThermocoupleType(MCP9600_ThemocoupleType);

	uint8_t getFilterCoefficient(void);
	void setFilterCoefficient(uint8_t);

	void  setADCresolution(MCP9600_ADCResolution resolution);
	MCP9600_ADCResolution getADCresolution(void);
	int32_t readADC(void);

	void setAlertTemperature(uint8_t alert, float temp);
	float getAlertTemperature(uint8_t alert);
	void configureAlert(uint8_t alert, bool enabled, bool rising, 
			    bool alertColdJunction=false,
			    bool activeHigh=false, 
			    bool interruptMode=false); 

    private:
        Adafruit_I2CDevice *i2c_dev;
	Adafruit_I2CRegister *_config_reg;
};
