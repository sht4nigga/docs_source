/*******************************************************************************
 * @File: main.c
 * @Author: Milandr, L.
 * @Project: Sample 5.1
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92
 * @Date: 30.03.2017
 * @Purpose: ������� ������
 *******************************************************************************/

// ����������� ������������� �����
#include "main.h"

// �������� �������
int main(void)
{
  // ������������� ������� ������������ ����������������
  CPU_Init();

  // ������������� ��������������������� �������
  LCD_Init();

  // ������������� �����-����������� ���������������
  DAC_Init();

  // ������ ���� ��� ������ ����
  while(1);
}