#ifndef _RAINSENSOR_INTERFACE_H_
#define _RAINSENSOR_INTERFACE_H_


#include "ErrTypes.h"
#include "GPIO_Interface.h"
#include "rainSensor_Config.h"


ERRORS_t rainSensorvInit(void);
ERRORS_t rainSensoru8ReadStatus(PinValue_t *PinValue);
#endif
