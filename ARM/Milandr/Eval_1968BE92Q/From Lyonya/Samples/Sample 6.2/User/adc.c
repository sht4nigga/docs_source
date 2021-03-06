/*******************************************************************************
 * @File: adc.c
 * @Author: Milandr, L.
 * @Project: Sample 6.2
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 28.03.2017
 * @Purpose: ���������� �������-�������� ����������������
 *******************************************************************************/

// ����������� ������������� �����
#include "adc.h"

// ����� ��� �������� ����������� ��������������
volatile uint16_t sample[ADC_SAMPLE_SIZE];

// ��������������� �������-�������� ����������������
void ADC_Reset(void)
{
  // ��������������� ������� ���
  MDR_ADC->ADC1_CFG     = 0;
  MDR_ADC->ADC1_H_LEVEL = 0;
  MDR_ADC->ADC1_L_LEVEL = 0;
  MDR_ADC->ADC1_RESULT;
  MDR_ADC->ADC1_STATUS  = 0;
  MDR_ADC->ADC1_CHSEL   = 0;

  // ��������������� ������� ���
  MDR_ADC->ADC2_CFG     = 0;
  MDR_ADC->ADC2_H_LEVEL = 0;
  MDR_ADC->ADC2_L_LEVEL = 0;
  MDR_ADC->ADC2_RESULT;
  MDR_ADC->ADC2_STATUS  = 0;
  MDR_ADC->ADC2_CHSEL   = 0;
}

// ������������ ����� ��� ������ ���
void ADC_PortCfg(void)
{
  // ��������� ������������ ��������� ����� D
  MDR_RST_CLK->PER_CLOCK |= (1 << RST_CLK_PCLK_PORTD_Pos);

  // ������������ ����� PD6
  MDR_PORTD->OE     &= ~(1 << 6);
  MDR_PORTD->FUNC   &= ~(3 << 12);
  MDR_PORTD->ANALOG &= ~(1 << 6);   // ����� ������ ����� (����������)
  MDR_PORTD->PULL   &= ~(1 << 6);   // �������� �������� � ���� ������� (��������)
  MDR_PORTD->PULL   &= ~(1 << 22);  // �������� �������� � ����� (��������)
  MDR_PORTD->PD     &= ~(1 << 6);
  MDR_PORTD->PD     &= ~(1 << 22);
  MDR_PORTD->PWR    &= ~(3 << 12);
  MDR_PORTD->GFEN   &= ~(1 << 6);
}

// ������������� �������-��������� ���������������
void ADC_Init(void)
{
  // ��������� ������������ ���
  MDR_RST_CLK->PER_CLOCK |= (1 << RST_CLK_PCLK_ADC_Pos);

  // ��������������� ���
  ADC_Reset();

  // ������������ ����� ��� ������ ���
  ADC_PortCfg();

  // ������������ ���
  MDR_ADC->ADC1_CFG = (0 << ADC1_CFG_REG_ADON_Pos)     // ������ ��� (���� ��������)
                    | (0 << ADC1_CFG_REG_CLKS_Pos)     // �������� ������������ ��� (CPU)
                    | (1 << ADC1_CFG_REG_SAMPLE_Pos)   // ������ ������� ��� (�����������)
                    | (6 << ADC1_CFG_REG_CHS_Pos)      // ������� ����� ��������������� (ADC6)
                    | (0 << ADC1_CFG_REG_CHCH_Pos)     // ����� ����������������� ������������ ������� (��������)
                    | (0 << ADC1_CFG_REG_RNGC_Pos)     // �������� ������ �������������� (��������)
                    | (0 << ADC1_CFG_M_REF_Pos)        // �������� �������� ���������� (����������)
                    | (3 << ADC1_CFG_REG_DIVCLK_Pos)   // �������� �������� ������� ��� (2^3 = 8)
                    | (0 << ADC1_CFG_SYNC_CONVER_Pos)  // ����� ������� ���� ��� (�����������)

  // ...������������ ������� ����������� � ����������� ��������� ���������� 1.23 �
                    | (0 << ADC1_CFG_TS_EN_Pos)        // ������ ����� ������� ����������� � ����������� ��������� ���������� 1.23 � (��������)
                    | (0 << ADC1_CFG_TS_BUF_EN_Pos)    // ������ ��������� ��� ������� ����������� � ����������� ��������� ���������� 1.23 � (��������)
                    | (0 << ADC1_CFG_SEL_TS_Pos)       // �������������� ������� � ������� ����������� (��������)
                    | (0 << ADC1_CFG_SEL_VREF_Pos)     // �������������� ������� � ����������� ��������� ���������� 1.23 � (���������)
                    | (0 << ADC1_CFG_TR_Pos)           // ���������� ���������� ����������� ��������� 1.23 �

  // ...��������� �������� ��� ��������������
                    | (0 << ADC1_CFG_DELAY_GO_Pos)     // �������������� �������� ��� ������ ������ ��� ������ ���������� ������� (1 ���� ����)
                    | (0 << ADC1_CFG_DELAY_ADC_Pos);   // �������� ��� ����� ������� ���������������� (�� ������������)
}

// ����� �������-�������� ��������������
void Thread_ADC(void *argument)
{
  uint32_t digit;             // �������� �������-��������� ��������������
  float temperature;          // ��������� �������� �����������
  char message[LCD_STR_LEN];  // ���������, ������������ �� �������
  uint32_t i;

  // �������� ����
  while (1)
  {
    // ��������� �������-��������� ���������������
    MDR_ADC->ADC1_CFG |= (1 << ADC1_CFG_REG_ADON_Pos);

    // �������� ���������� ����� �������-�������� ��������������
    osEventFlagsWait(EventId_ADC, EVENT_ADC_EOC, osFlagsWaitAny, osWaitForever);

    // �������� ��������� ������� ��������������
    for (i = 0, digit = 0; i < ADC_SAMPLE_SIZE; i++)
      digit += sample[i] & ADC_RESULT_Msk;

    // ���������� ����������
    digit /= ADC_SAMPLE_SIZE;

    // ���������� ����������� �� ������ ����������� ��������������
    temperature = TEMPERATURE(digit);

    // ����������� ���������� ��������� ����������� �� ������� (� �������� �������)
    snprintf(message, LCD_STR_LEN, "    T = %.1f�C", temperature);
    LCD_PutString(message, 3);

    // ����������� ���������� �������-��������� �������������� �� �������
    snprintf(message, LCD_STR_LEN, "    D = %u", digit);
    LCD_PutString(message, 5);

    // �������� ����� ������� ��������� ��������
    osDelay(250);
  }
}
