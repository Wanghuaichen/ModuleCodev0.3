
//���ͷ�ļ������ʵ���� Tx Driver оƬͨ�ŵĺ���������

#ifndef MODULE_MASTER_DRIVER_I2C
#define MODULE_MASTER_DRIVER_I2C

#include "stm32l0xx_hal.h"


//һЩ��tx-driver��صĳ���
#define GN1185_ADDRESS               0xA6            //��ַ
#define I_Mod                        0               //���Ƶ���
#define I_Bias                       1               //ƫ�õ���
#define Mon_Disable                  2               //��ֹMonitor
#define Channel_0                    0               //tx0
#define Channel_1                    1               //tx1
#define Channel_2                    2               //tx2
#define Channel_3                    3               //tx3
#define Channel_All                  4               //����ͨ��
#define MAX_IBIAS_CUR                70.0            //���ƫ�õ���
#define MAX_IMOD_CUR                 55.0            //�����Ƶ���
#define MAX_CRO_POI                  65.0            //��󽻲��
#define MIN_CRO_POI                  35.0            //��С�����

void SetTxModulationCurrent(double modulationCurrent, I2C_HandleTypeDef *hi2c, uint8_t channel);   //���õ��Ƶ���

void SetTxBiasSinkCurrent(double biasSinkCurrent, I2C_HandleTypeDef *hi2c, uint8_t channel);       //����ƫ�õ���

void TxEnable(I2C_HandleTypeDef *hi2c, uint8_t channel);                                           //ʧ��Tx_Dis

void TxDisable(I2C_HandleTypeDef *hi2c, uint8_t channel);                                          //ʹ��Tx_Dis

uint8_t GetTxStatus(I2C_HandleTypeDef *hi2c, uint8_t channel);                                     //��ȡTx״̬

void SetCurrentMonitor(I2C_HandleTypeDef *hi2c,uint8_t currentType, uint8_t channel);              //���õ���������

void SetLDD_EYE_OPT(uint8_t value, I2C_HandleTypeDef *hi2c, uint8_t channel);                      //������ͼ�Ż�

void SetEqulizationMag(uint8_t value, I2C_HandleTypeDef *hi2c, uint8_t channel);                   //����ƽ���С
	
void SetEqulizationPhase(uint8_t phase, I2C_HandleTypeDef *hi2c, uint8_t channel);                 //����ƽ��Ƕ�
	
void EnableEqulizer(I2C_HandleTypeDef *hi2c, uint8_t channel);                                     //ʹ��ƽ��
	
void DisableEqulizer(I2C_HandleTypeDef *hi2c, uint8_t channel);                                    //ʧ��ƽ��

void SetCrossingPointAdj(uint8_t value, I2C_HandleTypeDef *hi2c, uint8_t channel);                 //���ý����

void EnableCrossingPointAdj(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //ʹ�ܽ����
	
void DisableCrossingPointAdj(I2C_HandleTypeDef *hi2c, uint8_t channel);                            //ʧ�ܽ����

#endif
