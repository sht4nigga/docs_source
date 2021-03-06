/*******************************************************************************
 * @File: main.c
 * @Author: Milandr, L.
 * @Project: Sample 10.1
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 19.05.2017
 * @Purpose: ������� ������
 *******************************************************************************/

// ����������� ������������� �����
#include "main.h"

// �������� �������
int main(void)
{
  // ������������� ������� ������������ ����������������
  CPU_Init();

  // ������������� ���������� SPI
  SPI_Init();

  // ������������� ��������������������� �������
  LCD_Init();

  // ������������� ������������ ������� ��������� �������
  RTOS_Init();
}
