
//���ͷ�ļ������һЩ���ú�����GPIO�����Ķ���

#ifndef UTILITIES
#define UTILITIES

#include "stdint.h"
#include "stm32l0xx_hal.h"

//�������
void EmptyBuffer(uint8_t* a);

//�����¶ȵĺ���
uint16_t GetTemperature (ADC_HandleTypeDef *hadc);      //��ȡ�¶�
void    SetLatchTempHighAlarm(ADC_HandleTypeDef *hadc); //���ø��¾���
uint8_t GetLatchTempHighAlarm(void);                    //��ȡ���¾���
void    ClearLatchTempHighAlarm(void);                  //��ո��¾���

//����ModselL�ĺ���
uint8_t IsModSelL(void);                                //���ModSelL

//����IntL�ĺ���
void Assert_IntL(void);                                 //����IntL
void Deassert_IntL(void);                               //������IntL
void GetIntL(void);                                     //���IntL

//����Data_Not_Ready�ĺ���
void Data_Ready(void);                                  //����׼�����
void Data_Not_Ready(void);                              //����δ׼�����

//����LPMode�ĺ���
uint8_t IsLPMode(void);                                 //�Ƿ�͹���ģʽ
void LowPowerMode(void);                                //����͹���ģʽ
void NormalPowerMode(void);                             //������������ģʽ
uint8_t IsLPMode_Overriade(void);                       //LPMode�Ƿ񱻸���

//����pin TX-DISABLE �ĺ���
void Tx_Pin_Disable(void);                              //ʧ��Tx-dis pin
void Tx_Pin_Enable(void);                               //ʹ��Tx-dis pin
uint8_t GetTx_Pin_DIS(I2C_HandleTypeDef *hi2c);         //���Tx-dis pin

#endif
