/*******************************************************************************
 * @File: main.c
 * @Author: Milandr, L.
 * @Project: Sample 6.4
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 18.07.2018
 * @Purpose: ������� ������
 *******************************************************************************/

// ����������� ������������� �����
#include "main.h"

// �������� �������
int main(void)
{
  // ������������� ������� ������������ ����������������
  CPU_Init();

  // ������������� �������-��������� ���������������
  ADC_Init();

  // ������������� ������� ������� � ������
  DMA_Init();

  // ������������� ��������������������� �������
  LCD_Init();

  // ������������� ������������ ������� ��������� �������
  RTOS_Init();
}