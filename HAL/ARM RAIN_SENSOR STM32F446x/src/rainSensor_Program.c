#include "rainSensor_Interface.h"
//#include "ErrTypes.h"

ERRORS_t rainSensorvInit(void)
{
	ERRORS_t error= NOK;

	GPIO_PinConfig_t rainSensorConfig ={RAIN_STATUS_PIN,RAIN_STATUS_GPIO,RAIN_STATUS_MODE,RAIN_STATUS_SPEED,RAIN_STATUS_OutputType,RAIN_STATUS_PULLTYPE,RAIN_STATUS_AF};
	if(RAIN_STATUS_GPIO>PORTH||RAIN_STATUS_GPIO<PORTA||RAIN_STATUS_PIN>PIN15||RAIN_STATUS_PIN<PIN0)
	{
		error=NOK;
	}
	else
	{
		error=GPIO_u8PinInit((const GPIO_PinConfig_t*)&rainSensorConfig);
	}
	return error;
}

ERRORS_t rainSensoru8ReadStatus(PinValue_t *PinValue)
{
	ERRORS_t error=NOK;
	error =GPIO_u8ReadPinValue(RAIN_STATUS_GPIO, RAIN_STATUS_PIN, PinValue);
	return error;
}
