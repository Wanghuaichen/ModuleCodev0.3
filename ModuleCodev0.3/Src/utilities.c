
//���c�ļ�����˳��溯���ľ���ʵ��

#include "utilities.h"
#include "constant.h"
#include "stdint.h"
#include "stm32l0xx_hal.h"
#include "main.h"
#include "Module_MemMap.h"

//�����¶�ת���ĳ���
#define Vadc          3.3                
#define V25           1774.0
#define AVG_SLOPE     0.0043
#define TEMP_ALARM_VALUE 0xFFFF                         //�����¶�

//����Ԥ��λ
static uint8_t latch_temp_high_alarm = 0;

//��ջ�����
void EmptyBuffer(uint8_t* a)
{
	int i = 0;
	for(i =0; i<= PAGE_SIZE+1;i++)
	{
		a[i] = 0;
  }
}

//��ȡ�¶�
uint16_t GetTemperature (ADC_HandleTypeDef *hadc)
{
	uint32_t TemBuffer = 0x00000000;
	HAL_ADC_Start(hadc);
	HAL_Delay(500);
	TemBuffer = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);
  return ((uint16_t)(TemBuffer & 0x0000FFFF));
	//�¶�ת����δУ׼��
	//double Measured_Temperature = ((V25 - (double)TemBuffer)*(Vadc/4095.0))/(AVG_SLOPE)-25.0;
	//uint16_t temp = ((uint16_t)(Measured_Temperature*256.0));
	//return temp;
}

//���ø��¾���
void SetLatchTempHighAlarm(ADC_HandleTypeDef *hadc)
{
	/*if(GetTemperature(hadc) > TEMP_ALARM_VALUE )
	{
	   latch_temp_high_alarm = 0x80;
	}*/
	return;
}

//��ȡ���¾���
uint8_t GetLatchTempHighAlarm(void)
{
  return latch_temp_high_alarm;
}

//��ո��¾���
void    ClearLatchTempHighAlarm(void)
{
	latch_temp_high_alarm = 0;
}

//���ModSelL
uint8_t IsModSelL(void)                //1���������ݣ�0��������
{
	return HAL_GPIO_ReadPin(ModSelL_GPIO_Port, ModSelL_Pin);
}

//����IntL
void Assert_IntL(void)                 //�͵�ƽ
{
	HAL_GPIO_WritePin(IntL_GPIO_Port, IntL_Pin, GPIO_PIN_RESET);
	uint8_t u = Internal_Read_MemMap(2);
	u = u & 0xFD;
	Internal_Write_MemMap(2,u);
}

//������IntL
void Deassert_IntL(void)               //�ߵ�ƽ
{
	HAL_GPIO_WritePin(IntL_GPIO_Port, IntL_Pin, GPIO_PIN_SET);
	uint8_t u = Internal_Read_MemMap(2);
	u = u | 0x02;
	Internal_Write_MemMap(2,u);
}

//���IntL
void GetIntL(void)
{
	HAL_GPIO_ReadPin(IntL_GPIO_Port, IntL_Pin);
}

//����׼�����
void Data_Ready(void)
{
	uint8_t u = Internal_Read_MemMap(2);
	u = u & 0xFE;
	Internal_Write_MemMap(2,u);
}

//����δ׼�����
void Data_Not_Ready(void)
{
	uint8_t u = Internal_Read_MemMap(2);
	u = u | 0x01;
	Internal_Write_MemMap(2,u);
}

//�Ƿ�͹���ģʽpinΪ��
uint8_t IsLPMode(void)
{
	return HAL_GPIO_ReadPin(LPMode_GPIO_Port, LPMode_Pin);
}

//����͹���ģʽ
void LowPowerMode(void)
{
	//��δ��ɣ�
}

//������������ģʽ
void NormalPowerMode(void)
{
	//��δ��ɣ�
}

//LPMode�Ƿ񱻸���
uint8_t IsLPMode_Overriade(void)
{
	return (Internal_Read_MemMap(93) & 0x01);
}

//ʧ��Tx-dis pin
void Tx_Pin_Disable(void)
{
   HAL_GPIO_WritePin(TxDSBL_GPIO_Port, TxDSBL_Pin, GPIO_PIN_SET);
}

//ʹ��Tx-dis pin
void Tx_Pin_Enable(void)
{
   HAL_GPIO_WritePin(TxDSBL_GPIO_Port, TxDSBL_Pin, GPIO_PIN_RESET);
}

//���Tx-dis pin
uint8_t GetTx_Pin_DIS(I2C_HandleTypeDef *hi2c)
{
  return HAL_GPIO_ReadPin(TxDSBL_GPIO_Port, TxDSBL_Pin);
}
