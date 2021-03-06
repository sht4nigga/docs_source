/*******************************************************************************
 * @File: led.c
 * @Author: Milandr, L.
 * @Project: Sample 2.1
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 04.04.2017
 * @Purpose: ������������ ����� �����-������ ��� ������ �� ������������
 *******************************************************************************/

// ����������� ������������� �����
#include "led.h"

// ������������� ����� ��� ������ �� ������������
void LED_Init(void)
{
  // ��������� ������������ ����� B
  MDR_RST_CLK->PER_CLOCK |= (1 << RST_CLK_PCLK_PORTB_Pos);

  // ������������ ����� PB0...PB3 ��� ������ �� ������������
  MDR_PORTB->OE     |=  ((1 << 0)  | (1 << 1)  | (1 << 2)  | (1 << 3));   // ����������� ������ (�����)
  MDR_PORTB->PULL   &= ~((1 << 0)  | (1 << 1)  | (1 << 2)  | (1 << 3));   // �������� � ����� (���������)
  MDR_PORTB->PULL   &= ~((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19));  // �������� � ������� (���������)
  MDR_PORTB->ANALOG |=  ((1 << 0)  | (1 << 1)  | (1 << 2)  | (1 << 3));   // ����� ������ ����� (��������)
  MDR_PORTB->FUNC   &= ~((3 << 0)  | (3 << 2)  | (3 << 4)  | (3 << 6));   // ������� ����� (����-�����)
  MDR_PORTB->PD     &= ~((1 << 0)  | (1 << 1)  | (1 << 2)  | (1 << 3));   // ���������� ������� (�������)
  MDR_PORTB->PD     &= ~((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19));  // ������� ������ (�� ������������)
  MDR_PORTB->PWR    &= ~((3 << 0)  | (3 << 2)  | (3 << 4)  | (3 << 6));   // C���� ����� �������� PWR
  MDR_PORTB->PWR    |=  ((1 << 0)  | (1 << 2)  | (1 << 4)  | (1 << 6));   // �������� ������� (������)
  MDR_PORTB->GFEN   &= ~((1 << 0)  | (1 << 1)  | (1 << 2)  | (1 << 3));   // �������� ������ (�� ������������)
}

// ���������� ��������� �������
void LED_ImplementState(uint8_t state)
{
  // ���������� ���� �����������
  MDR_PORTB->RXTX &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));

  // ��������� �������
  switch (state)
  {
    // ��������� ���������� �������� ����������
    case RED:
      MDR_PORTB->RXTX |= (1 << 0);
      break;

    // ��������� ���������� ������� ����������
    case YELLOW:
      MDR_PORTB->RXTX |= (1 << 1);
      break;

    // ��������� ���������� �������� ����������
    case GREEN:
      MDR_PORTB->RXTX |= (1 << 2);
      break;

    // ��������� ���������� ������ ����������
    case BLUE:
      MDR_PORTB->RXTX |= (1 << 3);
      break;

    // ��������� ������������ � ��������� �������
    default:
      MDR_PORTB->RXTX &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));
      break;
  }
}
