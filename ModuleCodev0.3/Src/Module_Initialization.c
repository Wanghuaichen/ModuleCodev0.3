
//���c�ļ�����˹���ģ���ʼ���ľ���ʵ��

#include "Module_MemMap.h"
#include "Module_Initialization.h"
#include "utilities.h"
#include "constant.h"
#include "Module_Master_CDR.h"

void Module_Init_Hardware(void)                             //��ʼ������Ӳ��
{
	//�򿪲����� Tx Driver������Ƿ���������
	
  //�򿪲����� Tx CDR������Ƿ���������
	
  //�򿪲����� Rx CDR������Ƿ���������
}


void Module_Init_Register(void)                             //��ʼ��ģ��

{
	extern ADC_HandleTypeDef hadc;                  //��ȡ�ⲿ�����hadc1

	Data_Not_Ready();                                //����δ׼����
	
//00h �ϰ���	
	Internal_Write_MemMap(0,0x11);                   //ʶ����   QSFP28
	Internal_Write_MemMap(1,0x00);                   //�汾δע������ӦΪ2.9���°棩
	Internal_Write_MemMap(2,0x07);                   //�޶� Page��IntL �ߣ� Data Not Ready ��
	//��MASTERI2C����MASTERMONITER����Ҫ��Щ������
	//3       LOS Flag                          ����ѡ��
	SetLatchTxfault();                               //4 TX Fault Flag                     
  //5       LOL Flag                          ����ѡ��
  //6       �¶�Ԥ������ѡ��
	//7       ��ѹԤ������ѡ��
	//8       ����
	//9-10    ����Ԥ�� ����ѡ��
	//11-12   TXƫ�õ���Ԥ�� ����ѡ�� 
	//13-14   TX PWR Ԥ�� ����ѡ�� 
	//15-18   ����λ
	//19-21   ����
	//��utilities����Ҫ��Щ����
	uint16_t temperature = GetTemperature(&hadc);
	Internal_Write_MemMap(22,((uint8_t)(temperature/256)));
	Internal_Write_MemMap(23,((uint8_t)(temperature & CLEAR_HIGHER_BIT)));
  //22-23   ��ȡ�¶Ⱦ���
	//24-25   ����λ
	//26-27   ��ȡ�ṩ��ѹ����ѡ��
	//28-29   ����λ
	//30-33   ���� 
	//34-41   ��ȡ���ն˹���  ����ѡ��
	//42-49   ��ȡƫ�õ���    ����ѡ��
	//50-57   ��ȡ���Ͷ˹���  ����ѡ��
	//58-65   ����λ
	//66-81   ����
	//82-85   ����λ
	Internal_Write_MemMap(86,0x00);     //86 Txʧ��
  //87      ѡ�� Rx ������ ����ѡ��
  //88      ѡ�� Tx ������ ����ѡ��
  //89-92 Rx Software Application ѡ�� ����ѡ�� 
	Internal_Write_MemMap(93,0x00);     //93 �͹���ģʽ,  ���LPMode�ޣ� ʧ��LPMode����
	//94-97 Tx Software Application ѡ�� ����ѡ��
	//98      CDR����  ����ѡ��
	//99      ����λ
	//100     LOS ����
	Internal_Write_MemMap(101,0x00);    //101 Txʧ������
	//102     LOL ����
	//103     �¶�����
	//104     �ṩ��ѹ����
	//105-106 ����
	//107     ����λ
	//108-109 �����ӳ� ����ѡ��
	//110     �߼��͹���ģʽ/Զ��Ϊ��ͬ/��С������ѹ ����ѡ��
	//111     ����λ
	//112-118  ����λ
	//119-126 ����λ  ����ѡ��
	//127     ҳ��ѡ��     ����ѡ��
	
//00h �°���
  //128-191 Ӳ�����ݣ�1��
	//192 �ӳ�����̫����׼��
	//193 �Ƿ�֧��һЩӲ�����ܣ�1��
	//194 �Ƿ�֧��һЩӲ�����ܣ�2��
	//195 �Ƿ�֧��һЩӲ�����ܣ�3��
	//196-220 Ӳ�����ݣ�2��
	//221 �Ƿ�֧��һЩӲ�����ܣ�4��
	//222 ������
	//223 �����
	//224-255 ����
	Data_Ready();                                  //������׼����
	Assert_IntL();                                 //����IntL
}

