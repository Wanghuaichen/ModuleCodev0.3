
//���ͷ�ļ������һЩȫ�ֳ���

#ifndef CONSTANT
#define CONSTANT

#define PAGE_SIZE                             128                         //ҳ��С
#define PAGE_NUMBER                           2                           //ҳ����
#define MEMORY_MAP_SIZE                       PAGE_SIZE*PAGE_NUMBER       //����Ĵ�����С
#define RW_CHUNK_SIZE                         PAGE_SIZE * 2               //һ���Զ�ȡ/д���С

#define QSFP28_IDENTIFIER                     0X11                        //QSFP28ʶ����
#define IS_PAGED                              0x00<<2U                    //�Ƿ��ҳ

//���Ĵ�����ַ��������ο� SFF 8636
#define IDENTIFIER_ADDRESS                    0
#define STATUS                                1
#define INTERRUPT_FLAG                        3
#define FREE_SIDE_MONITORS                    22
#define CHANNEL_MONITORS                      34
#define CONTROL                               86
#define MODULE_AND_CHANNEL_MASKES             100
#define FREE_SIDE_DEVICE_PROPERTIES           108
#define PASSWORD_CHANGE_ENTRY_AREA            119
#define PASSWORD_ENTRY_AREA                   123
#define PAGE_SELECT_BYTE                      127

#define CLEAR_HIGHER_BIT                      0x00FF                      //���ʮ��λ�������λ

#endif
