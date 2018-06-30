#ifndef _DEVICE_USER_H
#define _DEVICE_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __INLINE
#    define __INLINE static __inline 
#endif

/* �����豸�û���� */
typedef void * HDEVUSR;

typedef enum {
	DEVUSER_InputSrcType_User = 0,
	DEVUSER_InputSrcType_Analog,
	DEVUSER_InputSrcType_Virtual
}eDEVUSER_InputSrcType;

typedef enum {
	DEVUSER_InputMethod_Absolute = 0,
	DEVUSER_InputMethod_Incremental
}eDEVUSER_InputMethod;

typedef enum {
	DEVUSER_GainType_Universal = 0,
	DEVUSER_GainType_Incremental
}eDEVUSER_GainType;

/* �����豸�û���ʼ�������ṹ */
typedef struct
{
	/* ��ʾʵ����� */
	int iIndex;

	/* ����Դ���� */
	eDEVUSER_InputSrcType inputSrcType;

	/* ����Դ��� */
	int iInputSrcNum;

	/* ���뷽ʽ */
	eDEVUSER_InputMethod inputMethod;

	/* ����ϵ�� */
	float fGain;

	/* �������� */
	eDEVUSER_GainType gainType;

}DeviceUser_CreateParams;

/**
    ����������Ĭ�ϲ���

    ������pPrm������� ����

	���أ���
*/
__INLINE void DeviceUser_CreateParams_Init(DeviceUser_CreateParams *pPrm)
{
	memset(pPrm, 0, sizeof(DeviceUser_CreateParams));
	pPrm->fGain = 1.0f;
	pPrm->gainType = DEVUSER_GainType_Incremental;
}

/* ���ģ���ʾ��ţ����أ�ģ���ʾ��� */
int DeviceUser_GetIndex(HDEVUSR hDevUsr);

/* ����ģ��ʵ�������أ�ʵ����� */
HDEVUSR DeviceUser_Create(DeviceUser_CreateParams *pPrm, void *pUser);

/* ����ģ��ʵ�� */
void DeviceUser_Delete(HDEVUSR hDevUsr);

/* ���� */
void DeviceUser_Reset(HDEVUSR hDevUsr);

/* ��õ�ǰֵ */
float DeviceUser_Get(HDEVUSR hDevUsr);

/* ��̬���ò��� */
int DeviceUser_SetParam(HDEVUSR hDevUsr, DeviceUser_CreateParams *pPrm);

#ifdef __cplusplus
}
#endif

#endif