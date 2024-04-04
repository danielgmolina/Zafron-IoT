#include "tof.h"

//ToF

// Instancia y puntero del dispositivo VL53L0X
VL53L0X_Dev_t myDevice;
VL53L0X_Dev_t *pMyDevice = &myDevice;


void inicializarToF(void);
void getDistancia(int *distancia);

int distancia;
uint16_t prueba;
uint8_t status;

void inicializarToF(void) {
    pMyDevice->I2cDevAddr = 0x29 << 1;
    pMyDevice->I2cHandle = &hi2c2;

    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    Status = VL53L0X_DataInit(pMyDevice);
    if (Status != VL53L0X_ERROR_NONE) return;

    Status = VL53L0X_StaticInit(pMyDevice);
    if (Status != VL53L0X_ERROR_NONE) return;

    // Configuraciones específicas para el perfil de largo alcance

    VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t)(0.1 * 65536));

    VL53L0X_SetLimitCheckValue(pMyDevice, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t)(60 * 65536));

    VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice, 33000);

    VL53L0X_SetVcselPulsePeriod(pMyDevice, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);

    VL53L0X_SetVcselPulsePeriod(pMyDevice, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);

    // Establece el modo de dispositivo a medición única
    VL53L0X_SetDeviceMode(pMyDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING);
}

void getDistancia(int *distancia) {

    VL53L0X_RangingMeasurementData_t RangingMeasurementData;

    VL53L0X_PerformSingleRangingMeasurement(pMyDevice, &RangingMeasurementData);

    *distancia = RangingMeasurementData.RangeMilliMeter;
    prueba = RangingMeasurementData.RangeMilliMeter;
    status =  RangingMeasurementData.RangeStatus;


    if (*distancia < 0) {
    		*distancia = 0;
    	}
    	if (*distancia > 2000) {
    		*distancia = 2000;
    	}
}
