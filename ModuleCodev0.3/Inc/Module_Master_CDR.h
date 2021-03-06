
//这个头文件存放了实现与 Tx/Rx CDR 芯片通信的函数的声明

#ifndef MODULE_MASTER_CDR
#define MODULE_MASTER_CDR

#include "stdint.h"
#include "stm32l0xx_hal.h"

//使能，失能
#define VALUE_RESET 0
#define VALUE_SET   1

//调试控制
#define PRECURSOR  0
#define POSTCURSOR 1

//芯片常量
#define GN2104_TX_I2C_ADDRESS                 0x24                                  //Tx CDR 地址
#define GN2104_RX_I2C_ADDRESS                 0x2C                                  //Rx CDR 地址
#define GN2104_ADDRESS_SIZE                   I2C_MEMADD_SIZE_16BIT                 //数据大小


void SetLatchTxfault(void);                             //设置 Tx Fault              （未完成）

uint8_t GetLatchTxFault(void);                          //获取 Tx Fault

void ClearLatchTxfault(void);                           //清空 Tx Fault

void WakeUpTxCDR_DRIVER(void);                                                             //使TxCDR和Driver从reset模式变为正常工作模式

void WakeUpRxCDR(void);                                                                    //使RxCDR从reset模式变为正常工作模式

void DisableTxCDR_DRIVER(void);                                                            //让TxCDR和Driver进入reset模式
	
void DisableRxCDR(void);                                                                   //让RxCDR进入reset模式

//以下函数还未完成，按需添加
void PowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel);                                    //打开总线和模拟电路电源

void PowerDown(I2C_HandleTypeDef *hi2c, uint8_t channel);                                  //关闭总线和模拟电路电源

void LOSPowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel);                                 //打开 LOS 检测

void LOSPowerDown(I2C_HandleTypeDef *hi2c, uint8_t channel);                               //关闭 LOS 检测

void CDRPowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel);                                 //打开CDR
 
void CDRPowerDown(I2C_HandleTypeDef *hi2c, uint8_t channel);                               //关闭CDR

void SetLosThres(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);                 //设置LOS门槛

void SetLosHyst(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);                  //设置LOS滞后

void CDRBypass(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t state);                   //跳过CDR

void SetEqulizer(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);                 //设置补偿器

void SetDriverMute(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t state);               //设置Driver沉默

void SetDriverDeemp(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);              //设置去加重

void SetDeempPrePostCursor(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t PreorPost);   //设置去加重前后

uint8_t GetTxLOSCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //读取TxLOS

uint8_t GetRxLOSCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //读取RxLOS

uint8_t GetTxLOLCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //读取TxLOL

uint8_t GetRxLOLCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //读取RxLOL

uint8_t GetRxLOLPin(void);                                                                 //读取RxLOL Pin

uint8_t GetRxLOSPin(void);                                                                 //读取RxLOS Pin

uint8_t GetTxLOSLOLPin(void);                                                              //读取TxLOSLOL Pin

void AssertRxLOL(void);                                                                    //调查具体是哪一条线失去时钟（Rx）

void AssertRxLOS(void);                                                                    //调查具体是那一条线失去信号（Rx）

void AssertTxLOSLOL(void);                                                                 //调查具体是那一条线失去信号或时钟（Tx）



#endif
