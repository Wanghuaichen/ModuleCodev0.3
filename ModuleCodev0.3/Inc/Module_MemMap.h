
//���ͷ�ļ�����˹�������Ĵ����ĺ����ͳ����Ķ��塣

#ifndef MODULE_MEMMAP_H
#define MODULE_MEMMAP_H

#include "main.h"
#include "stdint.h"

#define WRITE_ERR     0xFF                    //����ֵ��д���ִ���
#define WRITE_NORMAL  0x00                    //����ֵ��д����
#define READ_ERR      0xFF                    //����ֵ�������ִ���

uint8_t Read_MemMap(int internal_address);                                              //�ⲿ������Ĵ���

uint8_t Write_MemMap(int internal_address, uint8_t value);                              //�ⲿд����Ĵ���

uint8_t Internal_Write_MemMap(int internal_address, uint8_t value);                     //�ڲ�������Ĵ���

uint8_t Internal_Read_MemMap(int Memory_Address);                                       //�ڲ�д����Ĵ���

uint8_t Is_MemMap_Error(void);                                                                 //������

#endif
