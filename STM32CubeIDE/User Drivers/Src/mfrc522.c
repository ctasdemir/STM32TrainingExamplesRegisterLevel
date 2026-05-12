#include "stm32f0xx_hal.h"
#include "mfrc522.h"


#define MFRC522_CS_LOW 1
#define MFRC522_CS_HIGH 0

SPI_HandleTypeDef SpiHandle;

void mfrc522_antenna_on(void);
void mfrc522_antenna_off(void);
void mfrc522_write_reg(uint8_t addr, uint8_t val);
uint8_t mfrc522_read_reg(uint8_t addr);
void mfrc522_spi_init(void);
void mfrc522_reset(void);

void mfrc522_init(void) {
	//TM_MFRC522_InitPins();
	
	mfrc522_spi_init();

	mfrc522_reset();

	mfrc522_write_reg(MFRC522_REG_T_MODE, 0x8D);
	mfrc522_write_reg(MFRC522_REG_T_PRESCALER, 0x3E);
	mfrc522_write_reg(MFRC522_REG_T_RELOAD_L, 30);           
	mfrc522_write_reg(MFRC522_REG_T_RELOAD_H, 0);

	/* 48dB gain */
	mfrc522_write_reg(MFRC522_REG_RF_CFG, 0x70);
	
	mfrc522_write_reg(MFRC522_REG_TX_AUTO, 0x40);
	mfrc522_write_reg(MFRC522_REG_MODE, 0x3D);

	mfrc522_antenna_on();		//Open the antenna
}

void mfrc522_reset(void)
{
	mfrc522_write_reg(MFRC522_REG_COMMAND, PCD_RESETPHASE);
}

void mfrc522_write_reg(uint8_t addr, uint8_t val)
{
	uint8_t data[2] = {((addr<<1) & 0x7E),val};
	//CS low
	MFRC522_CS_LOW;
	//Send address
	
	HAL_SPI_Transmit(&SpiHandle,data,1,100);
//	TM_SPI_Send(MFRC522_SPI, (addr << 1) & 0x7E);
	//Send data	
	HAL_SPI_Transmit(&SpiHandle,&data[1],1,100);
//	TM_SPI_Send(MFRC522_SPI, val);
	//CS high
	MFRC522_CS_HIGH;
}

void mfrc522_set_bit(uint8_t reg, uint8_t mask)
{
	mfrc522_write_reg(reg, mfrc522_read_reg(reg) | mask);
}

void mfrc522_clear_bit(uint8_t reg, uint8_t mask)
{
	mfrc522_write_reg(reg, mfrc522_read_reg(reg) & (~mask));
} 

uint8_t mfrc522_read_reg(uint8_t addr) {
	uint8_t val;
	uint8_t data[2] = {((addr<<1) & 0x7E) | 0x80,val};
	//CS low
	MFRC522_CS_LOW;
  HAL_SPI_Transmit(&SpiHandle,data,1,100);
//	TM_SPI_Send(MFRC522_SPI, ((addr << 1) & 0x7E) | 0x80);	
	HAL_SPI_Receive(&SpiHandle,data,1,100);
	//val = TM_SPI_Send(MFRC522_SPI, MFRC522_DUMMY);
	//CS high
	MFRC522_CS_HIGH;

	return data[0];	
}

void mfrc522_antenna_on(void) {
	uint8_t temp;

	temp = mfrc522_read_reg(MFRC522_REG_TX_CONTROL);
	if (!(temp & 0x03)) {
		mfrc522_set_bit(MFRC522_REG_TX_CONTROL, 0x03);
	}
}

void mfrc522_antenna_off(void) {
	mfrc522_clear_bit(MFRC522_REG_TX_CONTROL, 0x03);
}





int32_t mfrc522_test_connection()
{
	return 0;
	
}

void mfrc522_spi_init(void)
{
/*##-1- Configure the SPI peripheral #######################################*/
  /* Set the SPI parameters */
  SpiHandle.Instance               = SPI1;

  SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
  SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  SpiHandle.Init.CRCPolynomial     = 7;
  SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
  SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SpiHandle.Init.NSS               = SPI_NSS_SOFT;
  SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
  SpiHandle.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
  SpiHandle.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;


  SpiHandle.Init.Mode = SPI_MODE_MASTER;


  if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
  {
    /* Initialization Error */
   //Error_Handler();
  }
		
}

