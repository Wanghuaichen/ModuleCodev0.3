
//���c�ļ�����˹�������λ����ͨ��I2C�ĳ�ʼ���жϣ��ر��жϺ��жϺ����ľ���ʵ�ֺ�һЩ�ڲ������Լ��ڲ����ݽṹ��

#include "Module_Slave_I2C.h"
#include "main.h"
#include "constant.h"
#include "Module_MemMap.h"
#include "utilities.h"

#define TXRXBUFFER_SIZE     RW_CHUNK_SIZE+1                            //��������С
#define USER_I2C_NO_OPTION_FRAME     (0xFFFF0000U)                     //��FRAME

//�ڲ����ݽṹ
static uint8_t TxRxBuffer[TXRXBUFFER_SIZE] = {0};                      //���ݷ��ͽ��ջ�����
static uint8_t Buffer_Internal_Address = 0;                            //��������ַ

//�ڲ�����
static HAL_StatusTypeDef User_I2C_Slave_ISR_IT(I2C_HandleTypeDef *hi2c, uint32_t ITFlags, uint32_t ITSources);    //�¼��жϴ���

void I2C_Slave_Transreceiver_IT_Initialize(I2C_HandleTypeDef *hi2c)    //��ʼ���ж�
{ 
	  //���Ի�����æ״̬����I2C�ṹ
    hi2c->State = HAL_I2C_STATE_BUSY;
    hi2c->Mode = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
 
    //ʹ����Ӧ
    hi2c->Instance->CR2 &= ~I2C_CR2_NACK;

	  //���������ͻ����С����I2C�ṹ
    hi2c->pBuffPtr = TxRxBuffer;
    hi2c->XferSize = TXRXBUFFER_SIZE;
    hi2c->XferCount = TXRXBUFFER_SIZE;
    hi2c->XferOptions = USER_I2C_NO_OPTION_FRAME;
    hi2c->XferISR     = User_I2C_Slave_ISR_IT;

    //ʹ���ж�
    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_ERRI|I2C_IT_TCI|
	                            I2C_IT_STOPI|I2C_IT_NACKI|I2C_IT_ADDRI|
	                            I2C_IT_RXI|I2C_IT_TXI);
}

void I2C_Slave_Transreceiver_IT_Deinitialize(I2C_HandleTypeDef *hi2c)   //�ر��ж�
{
	 //��ջ�����
	  EmptyBuffer(TxRxBuffer);
	 
	  //ʧ���ж�
    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_ERRI|I2C_IT_TCI|
	                            I2C_IT_STOPI|I2C_IT_NACKI|I2C_IT_ADDRI|
	                            I2C_IT_RXI|I2C_IT_TXI);
	  
	  //ʧ����Ӧ
	  hi2c->Instance->CR2 |= I2C_CR2_NACK;
	
	  //״̬Ϊ����
	  hi2c->State = HAL_I2C_STATE_READY;
	  
	  //ģʽΪû��
    hi2c->Mode = HAL_I2C_MODE_NONE;
}

void User_Slave_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c)      //�¼��жϴ���
{
  //��ȡ�жϱ�ʶ���ն�Ե��
  uint32_t itflags   = READ_REG(hi2c->Instance->ISR);
  uint32_t itsources = READ_REG(hi2c->Instance->CR1);

  //I2C�жϴ���
  if(hi2c->XferISR != NULL)
  {
    hi2c->XferISR(hi2c, itflags, itsources);
  }
}

static HAL_StatusTypeDef User_I2C_Slave_ISR_IT(struct __I2C_HandleTypeDef *hi2c, uint32_t ITFlags, uint32_t ITSources)    //�¼��жϴ���
{
  if(((ITFlags & I2C_FLAG_AF) != RESET) && ((ITSources & I2C_IT_NACKI) != RESET))       //����ӦFlag
  {
     __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);                                           //��� AF Flag
     EmptyBuffer(TxRxBuffer);                                                           //��ջ�����
     hi2c->pBuffPtr = TxRxBuffer;                                                       //���û�����ָ��
     hi2c->XferCount = TXRXBUFFER_SIZE;                                                 //���û�������С
  }
  else if(((ITFlags & I2C_FLAG_RXNE) != RESET) && ((ITSources & I2C_IT_RXI) != RESET))  //���������ѿ�Flag
  {
		 if(hi2c->XferCount != 0)
     {
       (*hi2c->pBuffPtr++) = hi2c->Instance->RXDR;                                      //�ӽ��ܴ洢��д������
       hi2c->XferCount--;
     }
  }
  else if(((ITFlags & I2C_FLAG_ADDR) != RESET) && ((ITSources & I2C_IT_ADDRI) != RESET))//��ַƥ��Flag
  {
	  if(((ITFlags & I2C_FLAG_DIR) != RESET) && (hi2c->XferCount < hi2c->XferSize))       //�Ƿ�Ϊ�����˵�ַ�ķ���ģʽ
	  {
		  int i = 0;
		  Buffer_Internal_Address = (*((hi2c->pBuffPtr)-1));                                 //���õ�ַ
	    for(i = 0; i < RW_CHUNK_SIZE; i++)                                                 //������д�뻺����
	    {
		    *((hi2c->pBuffPtr)+i) = Read_MemMap(Buffer_Internal_Address + i); 
	    }
    }
    else if (((ITFlags & I2C_FLAG_DIR) != RESET) && (hi2c->XferCount == hi2c->XferSize)) //�Ƿ�Ϊδ���յ�ַ�ķ���ģʽ
	  {
		  int j = 0;
		  for(j = 0; j < RW_CHUNK_SIZE; j++)                                                 //������д�뻺����
	    {
		    *((hi2c->pBuffPtr)+j) = Read_MemMap(Buffer_Internal_Address + j); 
	    }
	  }
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ADDR);                                         //���ADDR Flag
  }
  else if(((ITFlags & I2C_FLAG_TXIS) != RESET) && ((ITSources & I2C_IT_TXI) != RESET))   //��������δ��Flag
  {
	  if(hi2c->XferCount != 0)
    {
      hi2c->Instance->TXDR = (*hi2c->pBuffPtr++);                                        //������д����ܴ洢��
      hi2c->XferCount--;
    }
  }
  if(((ITFlags & I2C_FLAG_STOPF) != RESET) && ((ITSources & I2C_IT_STOPI) != RESET))     //ֹͣFlag
  {
     __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_STOPF);                                         //��� STOPF Flag      
     int m = 0;
     int n = TXRXBUFFER_SIZE - hi2c->XferCount;        
	   if(n >0)                                                                            //������ܵ�������
	   {
       Buffer_Internal_Address = TxRxBuffer[0];                                          //���õ�ַ
	   }
	   while(m+1<n)                                                                        //�����˵�ַ��������ʱ
	   {
		   Write_MemMap(Buffer_Internal_Address+m, TxRxBuffer[m+1]);                         //������������д������Ĵ���
		   m++;
	   }
	   EmptyBuffer(TxRxBuffer);                                                            //��ջ�����
	   hi2c->pBuffPtr = TxRxBuffer;                                                        //���û�����ָ��
     hi2c->XferCount = TXRXBUFFER_SIZE;                                                  //���û�������С
  }
	return HAL_OK;
}
