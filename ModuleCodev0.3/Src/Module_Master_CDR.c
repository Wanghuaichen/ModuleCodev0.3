
//���c�ļ�������� Tx/Rx CDR оƬͨ�ŵĺ����ľ���ʵ��

#include "Module_Master_CDR.h"
#include "stm32l0xx_hal.h"
#include "Module_MCU.h"
#include "constant.h"
#include "Module_MemMap.h"

static uint8_t Latch_Tx1_Fault = 0;
static uint8_t Latch_Tx2_Fault = 0;
static uint8_t Latch_Tx3_Fault = 0;
static uint8_t Latch_Tx4_Fault = 0;
static uint8_t temp_reg = 0x00;

extern I2C_HandleTypeDef hi2c2;

void SetLatchTxfault(void)         //���� Tx Fault
{
	//��⵽������Ͱ����������ŵ�һ��
	if(0)              //Tx4 Fault ����
	{
		Latch_Tx4_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x08) == 0)
		{
		  Assert_IntL();
		}
	}
	if(0)              //Tx3 Fault ����
	{
		Latch_Tx3_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x04) == 0)
		{
		  Assert_IntL();
		}
	}
	if(0)              //Tx2 Fault ����
	{
		Latch_Tx2_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x02) == 0)
		{
		  Assert_IntL();
		}
	}
	if(0)              //Tx1 Fault ����
	{
	  Latch_Tx1_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x01) == 0)
		{
		  Assert_IntL();
		}
	}
}

uint8_t GetLatchTxFault(void)     //��ȡ Tx Fault
{
  return 0x00 | (Latch_Tx4_Fault << 3) | (Latch_Tx3_Fault << 2) | (Latch_Tx2_Fault << 1) | (Latch_Tx1_Fault);   //����һ������sff-8636Э��İ�λ�ַ�
}

void ClearLatchTxfault(void)                         //��� Tx Fault
{
  Latch_Tx1_Fault = 0;
  Latch_Tx2_Fault = 0;
  Latch_Tx3_Fault = 0;
  Latch_Tx4_Fault = 0;
}

void WakeUpTxCDR_DRIVER(void)                                                             //ʹTxCDR��Driver��resetģʽ��Ϊ��������ģʽ
{
	HAL_GPIO_WritePin(Tx_Reset_GPIO_Port, Tx_Reset_Pin, GPIO_PIN_SET);
}

void WakeUpRxCDR(void)                                                                    //ʹRxCDR��resetģʽ��Ϊ��������ģʽ
{
	HAL_GPIO_WritePin(Rx_Reset_GPIO_Port, Rx_Reset_Pin, GPIO_PIN_SET);
}

void DisableTxCDR_DRIVER(void)                                                            //��TxCDR��Driver����resetģʽ
{
	HAL_GPIO_WritePin(Tx_Reset_GPIO_Port, Tx_Reset_Pin, GPIO_PIN_RESET);
}
	
void DisableRxCDR(void)                                                                   //��RxCDR����resetģʽ
{
	HAL_GPIO_WritePin(Rx_Reset_GPIO_Port, Rx_Reset_Pin, GPIO_PIN_RESET);
}

uint8_t GetRxLOLPin(void)                                                                 //��ȡRxLOL Pin
{
	return HAL_GPIO_ReadPin(Rx_LOL_GPIO_Port,Rx_LOL_Pin);
}

uint8_t GetRxLOSPin(void)                                                                 //��ȡRxLOS Pin
{
	return HAL_GPIO_ReadPin(Rx_LOS_GPIO_Port,Rx_LOS_Pin);
}

uint8_t GetTxLOSLOLPin(void)                                                              //��ȡTxLOSLOL Pin
{
	return HAL_GPIO_ReadPin(Tx_LOS_LOL_GPIO_Port,Tx_LOS_LOL_Pin);
}

void AssertRxLOL(void)                                                                    //�����������һ����ʧȥʱ�ӣ�Rx��
{
	
}

void AssertRxLOS(void)                                                                    //�����������һ����ʧȥ�źţ�Rx��
{
	
} 

void AssertTxLOSLOL(void)                                                                 //�����������һ����ʧȥ�źŻ�ʱ�ӣ�Tx��
{
	
}

void PowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel)                                    //�����ߺ�ģ���·��Դ
{
	temp_reg = 0x00;
	HAL_I2C_Mem_Write(hi2c, GN2104_TX_I2C_ADDRESS, 1142, GN2104_ADDRESS_SIZE, &temp_reg,1,I2C_WAIT_TIME);
	HAL_I2C_Mem_Write(hi2c, GN2104_RX_I2C_ADDRESS, 1142, GN2104_ADDRESS_SIZE, &temp_reg,1,I2C_WAIT_TIME);
	temp_reg = 0x00;
}

void LOSPowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel)                                 //�� LOS ���
{
	temp_reg = 0x01;
	HAL_I2C_Mem_Write(hi2c, GN2104_TX_I2C_ADDRESS, 1028, GN2104_ADDRESS_SIZE, &temp_reg,1,I2C_WAIT_TIME);
	HAL_I2C_Mem_Write(hi2c, GN2104_RX_I2C_ADDRESS, 1028, GN2104_ADDRESS_SIZE, &temp_reg,1,I2C_WAIT_TIME);
	temp_reg = 0x00;
}
