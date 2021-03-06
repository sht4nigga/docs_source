/*******************************************************************************
 * @File: main.c
 * @Author: Milandr, L.
 * @Project: Sample 2.3
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 05.04.2017
 * @Purpose: ������� ������
 *******************************************************************************/

// ����������� ������������� �����
#include "main.h"

// �������� �������
int main(void)
{
  // ������������� ����� ��� ������ �� ������������
  LED_Init();

  // ������������� ������ ��� ������ � ��������
  BTN_Init();

  // ������������� ��������������������� �������
  LCD_Init();

  // ����������� ����
  LCD_MenuInit();

  // ������������� ������������ ������� ��������� �������
  RTOS_Init();
}
