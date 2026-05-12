#include "stm32f0xx_hal.h"
#include "adxl345.h"




#define I2C_DEFAULT_TIMEOUT_MS (100)

extern I2C_HandleTypeDef hi2c1;


uint8_t i2c_buffer[12];



int32_t adxl345_test_connection()
{
	// Read the Device ID register and check it matches the ADXL345 ID number
	HAL_I2C_Mem_Read(&hi2c1,ADXL345_ADDRESS,ADXL345_DEVID,1,i2c_buffer,1,I2C_DEFAULT_TIMEOUT_MS);
	
	if(i2c_buffer[0] == ADXL345_ID)
	{
		return ADXL_OK;
	}
	else
	{
		return ADXL_ERROR;
	}
	
}

int32_t adxl345_init()
{

  HAL_StatusTypeDef ret = HAL_ERROR;

  ret = HAL_I2C_Mem_Read(&hi2c1, ADXL345_ADDRESS, ADXL345_DEVID, 1, i2c_buffer, 1, I2C_DEFAULT_TIMEOUT_MS);
	
	if(ret == HAL_ERROR)
	{
		return ADXL_ERROR;
	}
	
	if(i2c_buffer[0] == ADXL345_ID)
	{
		i2c_buffer[0] = 0x0B;
		HAL_I2C_Mem_Write(&hi2c1,ADXL345_ADDRESS,ADXL345_DATA_FORMAT,1,i2c_buffer,1,I2C_DEFAULT_TIMEOUT_MS);
		i2c_buffer[0] = 0x08;
		HAL_I2C_Mem_Write(&hi2c1,ADXL345_ADDRESS,ADXL345_POWER_CTL,1,i2c_buffer,1,I2C_DEFAULT_TIMEOUT_MS);
	}
	
	return ADXL_OK;
}

int32_t adxl345_get_g_values(float *x, float *y, float *z)
{
	int16_t acc_x, acc_y, acc_z;
	HAL_StatusTypeDef ret = HAL_ERROR;

	ret = HAL_I2C_Mem_Read(&hi2c1, ADXL345_ADDRESS, ADXL345_DATAX0, 1, i2c_buffer, 6, I2C_DEFAULT_TIMEOUT_MS);
	if (ret == HAL_OK) {

		acc_x = ((int16_t) ((uint16_t) (i2c_buffer[1] << 8)	| (uint16_t) i2c_buffer[0]));
		acc_y = ((int16_t) ((uint16_t) (i2c_buffer[3] << 8)	| (uint16_t) i2c_buffer[2]));
		acc_z = ((int16_t) ((uint16_t) (i2c_buffer[5] << 8)	| (uint16_t) i2c_buffer[4]));

		*x = acc_x * ADXL345_SCALE_FACTOR;
		*y = acc_y * ADXL345_SCALE_FACTOR;
		*z = acc_z * ADXL345_SCALE_FACTOR;

		return ADXL_OK;
	} else {
		return ADXL_ERROR;
	}
}
	
int32_t adxl345_get_raw_values(int16_t *x, int16_t *y, int16_t *z)
{
	HAL_I2C_Mem_Read(&hi2c1,ADXL345_ADDRESS,ADXL345_DATAX0, 1, i2c_buffer, 6, I2C_DEFAULT_TIMEOUT_MS);
  
	*x = ((int16_t)((uint16_t)(i2c_buffer[1]<<8) | (uint16_t)i2c_buffer[0]));
	*y = ((int16_t)((uint16_t)(i2c_buffer[3]<<8) | (uint16_t)i2c_buffer[2]));
	*z = ((int16_t)((uint16_t)(i2c_buffer[5]<<8) | (uint16_t)i2c_buffer[4]));
	
	return ADXL_OK;
}


