#ifndef _INPUT_DEVICE_H
#define _INPUT_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __INLINE
#    define __INLINE static __inline 
#endif

/* ���������豸��ʼ�������ṹ */
typedef struct
{
	/* ��ʾʵ����� */
	int iIndex;

	/* Deadband�豸���� */
	float fDeadband;
	
	/* Gain�豸���� */
	float fGain;

	/* Offsetģ���豸ƫ�� */
	float fOffset;

}INPUTDEVICE_CreateParams;

typedef INPUTDEVICE_CreateParams VirtualDevice_CreateParams;
typedef INPUTDEVICE_CreateParams AnalogDevice_CreateParams;

/**
    ����������Ĭ�ϲ���

    ������pPrm������� ����

	���أ���
*/
__INLINE void InputDevice_CreateParams_Init(VirtualDevice_CreateParams *pPrm)
{
	memset(pPrm, 0, sizeof(VirtualDevice_CreateParams));
	pPrm->fGain = 1.0f;
}

#ifdef __cplusplus
}
#endif

#endif