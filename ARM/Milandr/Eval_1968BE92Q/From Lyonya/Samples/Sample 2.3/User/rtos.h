/*******************************************************************************
 * @File: rtos.h
 * @Author: Milandr, L.
 * @Project: Sample 2.3
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 11.05.2017
 * @Purpose: ���������� ������������ �������� ��������� �������
 *******************************************************************************/

#ifndef RTOS_H
#define RTOS_H

// ����������� ������������ ������ ������� �������
#include "link.h"

// ������������� ��������
extern osMutexId_t MutexId_Display;

// ��������� �������
void RTOS_Init(void);  // ������������� ������������ ������� ��������� �������

#endif
