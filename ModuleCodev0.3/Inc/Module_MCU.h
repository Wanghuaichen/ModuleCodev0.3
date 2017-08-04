
//���ͷ�ļ������һЩ���ú�����GPIO�����Ķ���

#ifndef UTILITIES
#define UTILITIES

#include "stdint.h"
#include "stm32l0xx_hal.h"

//�������
void EmptyBuffer(uint8_t* a);

//�����¶ȵĺ���
uint16_t GetTemperature(void);                                //��ȡ�¶�          ��δ��ɣ�Ҫ����8636���Ҫ�󷵻�ֵ��
void    SetLatchTempHighAlarm(ADC_HandleTypeDef *hadc);       //���ø��¾���      ��δ��ɣ�Ҫ�Զ���һ�����£�
uint8_t GetLatchTempHighAlarm(void);                          //��ȡ���¾���
void    ClearLatchTempHighAlarm(void);                        //��ո��¾���

//��ȡRSSI��ѹ�ĺ�����δ��ɣ���Ҫ�Ͳο���ѹ���Աȣ�
uint16_t  GetRSSI1(void);                                     //��ȡRSSI1         
uint16_t  GetRSSI2(void);                                     //��ȡRSSI2
uint16_t  GetRSSI3(void);                                     //��ȡRSSI3
uint16_t  GetRSSI4(void);                                     //��ȡRSSI4

//��ȡIBias��ѹ�ĺ�����δ��ɣ���Ҫ�Ͳο���ѹ���Աȣ�
uint16_t  GetIBias(void);

//����ModselL�ĺ���
uint8_t   IsModSelL(void);                              //���ModSelL

//����IntL�ĺ���
void Assert_IntL(void);                                 //����IntL
void Deassert_IntL(void);                               //������IntL
void GetIntL(void);                                     //���IntL
uint8_t WhetherIntL(void);                              //�Ƿ񷴶���IntL    ��δ��ɣ�

//����Data_Not_Ready�ĺ���
void Data_Ready(void);                                  //����׼�����
void Data_Not_Ready(void);                              //����δ׼�����

//����LPMode�ĺ���
uint8_t IsLPMode(void);                                 //�Ƿ�͹���ģʽ
void LowPowerMode(void);                                //����͹���ģʽ    ��δ��ɣ�
void NormalPowerMode(void);                             //������������ģʽ  ��δ��ɣ�
uint8_t IsLPMode_Overriade(void);                       //LPMode�Ƿ񱻸���

//����pin TX-DISABLE �ĺ���
void Tx_Pin_Disable(void);                              //ʧ��Tx-dis pin
void Tx_Pin_Enable(void);                               //ʹ��Tx-dis pin
uint8_t GetTx_Pin_DIS(I2C_HandleTypeDef *hi2c);         //���Tx-dis pin

//����ADC�ĺ���
void ADC_Update(void);                                  //��������ADC��ֵ

//����EEPROM�ĺ���
void Save_Data(uint8_t address, uint8_t word);          //��һ����λ����ֵд���Դ���EEPROM���ϵ粻�ᶪʧ��
uint8_t Load_Data(uint8_t address);                     //��EEPROM��һ����λ����ֵ
#endif
