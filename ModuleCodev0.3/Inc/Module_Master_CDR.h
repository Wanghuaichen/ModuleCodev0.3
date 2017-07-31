
//���ͷ�ļ������ʵ���� Tx/Rx CDR оƬͨ�ŵĺ���������

#ifndef MODULE_MASTER_CDR
#define MODULE_MASTER_CDR

#include "stdint.h"
#include "stm32l0xx_hal.h"

//ʹ�ܣ�ʧ��
#define VALUE_RESET 0
#define VALUE_SET   1

//���Կ���
#define PRECURSOR  0
#define POSTCURSOR 1

//оƬ����
#define GN2104_TX_I2C_ADDRESS                 0x24                                  //Tx CDR ��ַ
#define GN2104_RX_I2C_ADDRESS                 0x2C                                  //Rx CDR ��ַ
#define GN2104_ADDRESS_SIZE                   I2C_MEMADD_SIZE_16BIT                 //���ݴ�С


void SetLatchTxfault(void);                             //���� Tx Fault

uint8_t GetLatchTxFault(void);                          //��ȡ Tx Fault

void ClearLatchTxfault(void);                           //��� Tx Fault

//���º�����δʵ�֣������ڵ��Ե�ʱ��v0.3�����д���

void WakeUpTxCDR_DRIVER(void);                                                             //ʹTxCDR��Driver��resetģʽ��Ϊ��������ģʽ

void WakeUpRxCDR(void);                                                                    //ʹRxCDR��resetģʽ��Ϊ��������ģʽ

void DisableTxCDR_DRIVER(void);                                                            //��TxCDR��Driver����resetģʽ
	
void DisableRxCDR(void);                                                                   //��RxCDR����resetģʽ

void PowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel);                                    //�����ߺ�ģ���·��Դ

void PowerDown(I2C_HandleTypeDef *hi2c, uint8_t channel);                                  //�ر����ߺ�ģ���·��Դ

void LOSPowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel);                                 //�� LOS ���

void LOSPowerDown(I2C_HandleTypeDef *hi2c, uint8_t channel);                               //�ر� LOS ���

void CDRPowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel);                                 //��CDR
 
void CDRPowerDown(I2C_HandleTypeDef *hi2c, uint8_t channel);                               //�ر�CDR

void SetLosThres(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);                 //����LOS�ż�

void SetLosHyst(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);                  //����LOS�ͺ�

void CDRBypass(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t state);                   //����CDR

void SetEqulizer(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);                 //���ò�����

void SetDriverMute(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t state);               //����Driver��Ĭ

void SetDriverDeemp(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);              //����ȥ����

void SetDeempPrePostCursor(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t PreorPost);   //����ȥ����ǰ��

uint8_t GetTxLOSCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //��ȡTxLOS

uint8_t GetRxLOSCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //��ȡRxLOS

uint8_t GetTxLOLCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //��ȡTxLOL

uint8_t GetRxLOLCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //��ȡRxLOL

uint8_t GetRxLOLPin(void);                                                                 //��ȡRxLOL Pin

uint8_t GetRxLOSPin(void);                                                                 //��ȡRxLOS Pin

uint8_t GetTxLOSLOLPin(void);                                                              //��ȡTxLOSLOL Pin

void AssertRxLOL(void);                                                                    //�����������һ����ʧȥʱ�ӣ�Rx��

void AssertRxLOS(void);                                                                    //�����������һ����ʧȥ�źţ�Rx��

void AssertTxLOSLOL(void);                                                                 //�����������һ����ʧȥ�źŻ�ʱ�ӣ�Tx��



#endif
