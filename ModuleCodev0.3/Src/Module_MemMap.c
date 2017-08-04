
//���c�ļ����������Ĵ��������ݣ��ڲ������Լ����ֺ����ľ���ʵ��

#include "Module_MemMap.h"
#include "main.h"
#include "constant.h"
#include "stdlib.h"
#include "Module_Master_CDR.h"
#include "Module_MCU.h"
#include "Module_Master_Driver_I2C.h"

//v0.3 �� ֻ֧�� SFF8636�� ���������ܣ�Memory Map����256���ֽڡ�
//ֻ������
#define RO_START_ADDRESS_1    0
#define RO_STOP_ADDRESS_1    85
#define RO_START_ADDRESS_2  108
#define RO_STOP_ADDRESS_2   111
#define RO_START_ADDRESS_3  128
#define RO_STOP_ADDRESS_3   223
//���Ժ�����ֻ������Ļ��������

//�ڲ����ݽṹ
static uint8_t status_code = 0;                                       //�������
static uint8_t MemMap_Array[MEMORY_MAP_SIZE] = {0};                   //�ڲ��ڴ��ַ
extern I2C_HandleTypeDef hi2c2;                                       //�ⲿ��λ������I2C�ṹ��ַ

//�ڲ�����
//static int Address_Redirection(int Memory_Address);                 //����ʵ�ֶ�ҳ��MemMap��δ��ɣ�

uint8_t Read_MemMap(int Memory_Address)                               //�ⲿ������Ĵ���
{
	if( Memory_Address >= MEMORY_MAP_SIZE)                              //������Χ
	{
		status_code = 1;                                                  //���ô������
		return READ_ERR;                                                  //����������Ľ����FF���������
	}
	
	if(Memory_Address == STATUS+1)                                      //������IntL��Data_Not_Ready�Ĵ���
	{
		if((*(MemMap_Array + Memory_Address) & 0x01) == 0)                //���Data_Ready
		{
			if(WhetherIntL())                                               //�Ƿ���Է�����
      {
		     Deassert_IntL();                                             //������ IntL
      }
		}
	}
	else if (Memory_Address == (INTERRUPT_FLAG + 1))                    //������Tx_Fault�ļĴ���
	{
		*(MemMap_Array + Memory_Address) = GetLatchTxFault();             //��ȡ Tx_Fault
		 ClearLatchTxfault();                                             //��� Tx_Fault

	}
	else if(Memory_Address == (INTERRUPT_FLAG + 3))                     //������High_Temperature_Alarm
	{
	   *(MemMap_Array + Memory_Address) = GetLatchTempHighAlarm();      //��ȡ High_Temperature_Alarm
		 ClearLatchTempHighAlarm();                                       //��� High_Temperature_Alarm
		 if(WhetherIntL())                                                //�Ƿ���Է�����
     {
		     Deassert_IntL();                                             //������ IntL
     }
	}
  return *(MemMap_Array + Memory_Address);                            //����ֵ
}

uint8_t Write_MemMap(int Memory_Address, uint8_t value)               //�ⲿд����Ĵ���
{
	if(( Memory_Address >= MEMORY_MAP_SIZE)                                              ||    //������Χ  
		 ((Memory_Address >= RO_START_ADDRESS_1) && (Memory_Address <= RO_STOP_ADDRESS_1)) ||
		 ((Memory_Address >= RO_START_ADDRESS_2) && (Memory_Address <= RO_STOP_ADDRESS_2)) ||
	   ((Memory_Address >= RO_START_ADDRESS_3) && (Memory_Address <= RO_STOP_ADDRESS_3)))        
	   //������ֻ������Ļ��������
	{
		status_code = 1;                                                  //���ô������
		return WRITE_ERR;                                                 //����������Ľ����FF���������
	}
	else
	{
    *(MemMap_Array + Memory_Address) = value;                         //дֵ
		
		if(Memory_Address == CONTROL)                                     //дControlλ���һЩ������δ��ɣ�
		{
			/*
		  if((value &  0x08) != 0)                                        //����/����Tx3
			{
			  TxDisable(&hi2c2,Channel_3);
			}
			else
			{
				TxEnable(&hi2c2,Channel_3);
			}
		  if((value &  0x04) != 0)                                        //����/����Tx2
			{
			  TxDisable(&hi2c2,Channel_2);			  
			}
			else
			{
				TxEnable(&hi2c2,Channel_2);
			}
		  if((value &  0x02) != 0)                                        //����/����Tx1
			{
			  TxDisable(&hi2c2,Channel_1);			  
			}
			else
			{
				TxEnable(&hi2c2,Channel_1);
			}
      if((value &  0x01) != 0)                                        //����/����Tx0
			{
			  TxDisable(&hi2c2,Channel_0);			  
		  }
			else
			{
				TxEnable(&hi2c2,Channel_0);
			}
			*/
		}
		else if(Memory_Address == CONTROL + 7)                         //д���ʿ���λ
		{
			if((value & 0x01) == 0)                                      //���δ����
			{
				 if(IsLPMode() == 0)                                       //���Ϊ0
	       {
		       NormalPowerMode();                                      //����ģʽ
		     }
	       else                                                      //���Ϊ1
	       {
		       LowPowerMode();                                         //�͹���ģʽ
		     }
	    }
			else                                                         //����Ѹ���
			{
				if((value & 0x02) == 0)                                    //������LPModeλΪ0
				{
					NormalPowerMode();                                       //����ģʽ
				}
				else                                                       //������LPModeλΪ1
				{
					LowPowerMode();                                          //�͹���ģʽ
				}
			}
		}
	}
	return WRITE_NORMAL;                                               //д���� 0
}

uint8_t Internal_Write_MemMap(int Memory_Address, uint8_t value)     //�ڲ�д����Ĵ���
{
	if(Memory_Address >= MEMORY_MAP_SIZE)                              //������Χ
	{
		status_code = 1;                                                 //���ô������
		return WRITE_ERR;                                                //����������Ľ����FF���������
	}
  *(MemMap_Array + Memory_Address) = value;                          //дֵ
	return WRITE_NORMAL;                                               //д���� 0
}

uint8_t Internal_Read_MemMap(int Memory_Address)                     //�ڲ�������Ĵ���
{
	if( Memory_Address >= MEMORY_MAP_SIZE)                             //������Χ
	{
		status_code = 1;                                                 //���ô������
		return READ_ERR;                                                 //����������Ľ����FF���������
	}
  return *(MemMap_Array + Memory_Address);                           //��ֵ
}

uint8_t Is_MemMap_Error(void)                                        //���ش������
{ 
	uint8_t s = status_code;
	status_code = 0;                                                   //��մ������
	return s;                                       
}
