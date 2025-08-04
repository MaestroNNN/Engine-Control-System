// ========= ������������� ���������������� =========
static __INLINE void main_init() {
// ����� ����������� ��������, 2 ����� �������� ��� FLASH, ��. PM0075
FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;
RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // HCLK = SYSCLK
RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // PCLK1 = SYSCLK / 2 (APB1)
RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // PCLK2 = SYSCLK (APB2)
RCC->CFGR |= RCC_CFGR_SW_PLL; // �������� ������ �� PLL
RCC->CFGR |= RCC_CFGR_PLLMULL9; // SYSCLK = 72 MHz
RCC->CFGR |= RCC_CFGR_PLLSRC_HSE; // ������������ PLL �� ������
RCC->CR |= RCC_CR_HSEON; //��������� ��������� HSE
while (!(RCC->CR & RCC_CR_HSERDY)) {};
RCC->CR |= RCC_CR_PLLON; // ��������� PLL
while ((RCC->CR & RCC_CR_PLLRDY) == 0) {};
// ������� ����� PLL ������ ���������� ������������
while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {};
//RCC->CR &= ~RCC_CR_HSION; // ��������� ���������� RC-���������

//====================== DWT ======================
SCB_DEMCR |= 0x01000000; // ��������� ������������ �������
DWT_CYCCNT = 0; // �������� �������� �������� ��������
DWT_CONTROL |= 1; // ��������� �������  

//====================== ����� ======================  
RCC->APB2ENR = RCC_APB2ENR_IOPAEN; // �������� ������������ ����� PORTA 
// pin 3 ������ �� �����
GPIOA->CRL &= ~GPIO_CRL_MODE3; // ����� �������� MODE
// ��������� ������:  ����. ����, ������� ����������� �� 10 ���
GPIOA->CRL &= ~GPIO_CRL_CNF3; // ����� �������� CNF
// ��������� ������: ����. ���� - Input floating 
GPIOA->CRL |= GPIO_CRL_CNF3_1; 
//================= ������ ������ "B" ===========================
RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // �������� ������������ ����� GPIO "C"
// pin 13 ������� ��������� �� �����
GPIOB->CRL &= ~GPIO_CRL_MODE0; // ����� �������� MODE
// ��������� ������: ����. �����, ������� ����������� �� 10 ���
GPIOB->CRL |= GPIO_CRL_MODE0; 
// ��������� ������: ����. ����� - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF0;

GPIOB->CRL &= ~GPIO_CRL_MODE1; // ����� �������� MODE
// ��������� ������: ����. �����, ������� ����������� �� 10 ���
GPIOB->CRL |= GPIO_CRL_MODE1; 
// ��������� ������: ����. ����� - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF1;

GPIOB->CRL &= ~GPIO_CRL_MODE5; // ����� �������� MODE
// ��������� ������: ����. �����, ������� ����������� �� 10 ���
GPIOB->CRL |= GPIO_CRL_MODE5; 
// ��������� ������: ����. ����� - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF5;

GPIOB->CRL &= ~GPIO_CRL_MODE6; // ����� �������� MODE
// ��������� ������: ����. �����, ������� ����������� �� 10 ���
GPIOB->CRL |= GPIO_CRL_MODE6; 
// ��������� ������: ����. ����� - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF6;

GPIOB->CRL &= ~GPIO_CRL_MODE7; // ����� �������� MODE
// ��������� ������: ����. �����, ������� ����������� �� 10 ���
GPIOB->CRL |= GPIO_CRL_MODE7; 
// ��������� ������: ����. ����� - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF7;

GPIOB->CRH &= ~GPIO_CRH_MODE8; // ����� �������� MODE
// ��������� ������: ����. �����, ������� ����������� �� 10 ���
GPIOB->CRH |= GPIO_CRH_MODE8; 
// ��������� ������: ����. ����� - Push-pull
GPIOB->CRH &= ~GPIO_CRH_CNF8;

//================= ������ ������ "C" ===========================
RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // �������� ������������ ����� GPIO "C"
// pin 13 ������� ��������� �� �����
GPIOC->CRH &= ~GPIO_CRH_MODE13; // ����� �������� MODE
// ��������� ������: ����. �����, ������� ����������� �� 10 ���
GPIOC->CRH |= GPIO_CRH_MODE13; 
// ��������� ������: ����. ����� - Push-pull
GPIOC->CRH &= ~GPIO_CRH_CNF13;

//======================== ��� ========================
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // �������� ������������ ����� PORTA 
GPIOA->CRL &= ~GPIO_CRL_MODE0; // PA0 = ���� 
GPIOA->CRL &= ~GPIO_CRL_MODE1; // PA1 = ���� 
GPIOA->CRL &= ~GPIO_CRL_CNF0; // PA0 = ����������
GPIOA->CRL &= ~GPIO_CRL_CNF1; // PA1 = ����������

RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8; // ������������ PCLK2 / 8 = 9 MHz
RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // ��������� ������������ ADC1	  
RCC->APB2RSTR |= RCC_APB2RSTR_ADC1RST; // ����� ADC1
RCC->APB2RSTR &= ~RCC_APB2RSTR_ADC1RST; // ����� ������ ADC1  

ADC1->CR1 &= ~ADC_CR1_DUALMOD; // ����������� ����� ������
ADC1->CR1 &= ~ADC_CR1_SCAN; // ����� ��� ������������	 

ADC1->CR2 &= ~ADC_CR2_CONT; // ����� ������������ ��������������
// �������������� �� ������� ��������� � ��� SWSTART
ADC1->CR2 |= ADC_CR2_EXTTRIG | ADC_CR2_EXTSEL; 

// ����� ������� ������ 239,5 �����
ADC1->SMPR2 |= ADC_SMPR2_SMP0;
 
ADC1->CR2 |= ADC_CR2_ADON; // �������� ADC1 
ADC1->CR2 |= ADC_CR2_RSTCAL; delay_us(10); // ��������� ����� ��������� ���������� 
while (ADC1->CR2 & ADC_CR2_RSTCAL) {}; // ��� ��������� ������	��������� 
ADC1->CR2 |= ADC_CR2_CAL; // ��������� ����������	   
while (ADC1->CR2 & ADC_CR2_CAL) {}; // ��� ��������� ����������


//====================== USART1 ====================== 
// �������� ������������ ����� GPIOA � ����� �������������� �������
RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN); 
RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // �������� ������������ USART1
// PA9 (TX1) AFIO Push-Pull, 10MHz. PA10 (RX1) HiZ, 10MHz
// ������� ������������� ���� ��� � "00", ��� ������ ����������� !
GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9 | GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
// ����� ������ ���� ������������� � '1'
GPIOA->CRH |= (GPIO_CRH_MODE9_0 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_0); 
USART1->BRR = 7500; // PCLK2 / Baud = 72000000 / 9600 ���
// �������� USART, ���������� � ��������
USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
USART1->CR1 |= USART_CR1_RXNEIE; // ��������� ���������� �� ����� RX
// ��������� �� ���������: 8 ���. ���, 1 �������� ���, �������� �������� ���
// ��������� ���������� UART1 � ����������� ����������
NVIC_EnableIRQ(USART1_IRQn);

// ======================== TIM2 =======================
// ��������� ������������, PCLK1 = 12 ���, TIM2 ���������� x 2 = 24 ���
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
TIM2->SMCR &= ~TIM_SMCR_SMS; // �������� ���������� ������������
TIM2->PSC = 72 - 1; // ��� (�����) ����� 1 ���, 1 MHz
TIM2->ARR = 100 - 1; // ������������ ����� 100 ���
TIM2->DIER |= TIM_DIER_UIE; // ��������� ���������� �� ������������ �������
NVIC_EnableIRQ(TIM2_IRQn); // ��������� ���������� � ����������� ����������
TIM2->CR1 = TIM_CR1_CEN; // ��������� ����
}  
// �����