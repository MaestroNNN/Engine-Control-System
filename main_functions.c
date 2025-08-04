/*DWT � ��� ���������� ������� ������ ���������� � STM32,
 ������� ����� ������������ ��� ��������� ������� � ������� ���������.*/
#define    DWT_CYCCNT    *(volatile uint32_t *)0xE0001004
#define    DWT_CONTROL   *(volatile uint32_t *)0xE0001000
#define    SCB_DEMCR     *(volatile uint32_t *)0xE000EDFC

// ������� ��� ������������� ����������� �������� � �������������� DWT
// �� ���������, ��� ������ ���������� ���� ������ ������� ������� �������

// ������� �������� � ��� (����� �� 1 ���). ��������: �������� + 1 ���.
static __INLINE  void delay_us(uint32_t us) {
static volatile uint32_t n;
n =  us * 24; // SystemCoreClock/1000000 = 24
DWT_CYCCNT = 0; while (DWT_CYCCNT < n) ;
}

// ������� �������� � �� �� 1 �� �� 59 ���. (������ ������������)
static __INLINE void delay_ms(uint32_t ms) {
static volatile uint32_t n;
n =  ms * 24000; DWT_CYCCNT = 0; while (DWT_CYCCNT < n) ;
}

// ������� �������������� ������������ 16 ������� ����� � ������
void Uint16ToStr(uint16_t Number, uint8_t *pStr) {
static int8_t i;
for(i = 4; i != -1; i--) { pStr[i] = (Number % 10) + 0x30; Number /= 10; }
pStr[5] = 0; // ����� ������
}

// ������� �������������� ��������� 16 ������� ����� � ������
void Int16ToStr(int16_t Number, uint8_t *pStr) {
static int8_t i;
if (Number >=0) pStr[0] = '+'; 
  else { pStr[0] = '-'; Number = -Number; }
for(i = 5; i != 0; i--) { pStr[i] = (Number % 10) + 0x30; Number /= 10; }
pStr[6] = 0; // ����� ������
}

// ������� �������������� ������������ 32 ������� ����� � ������
// 0 .. 4 294 967 295  <CR> = 13, <LF> = 10
void Uint32ToStr(uint32_t Number, uint8_t *pStr) {
static int8_t i;
for(i = 9; i != -1; i--) { pStr[i] = (Number % 10) + 0x30; Number /= 10; }
pStr[10] = 0;
}

// ������� �������� ������� �� USART1 �� ����������
void Tx1(uint8_t Symbol) {
while ((USART1->SR & USART_SR_TXE) == 0) {};
USART1->DR = Symbol;
}

// ������� �������� � ����� ������� �� USART1
uint8_t Rx1() {
while ((USART1->SR & USART_SR_RXNE) == 0) {};
return USART1->DR;
}

// ������� �������� ������� �������� (������) �� USART1
// ���� �� ���������� "0" ����
void Tx1Str(uint8_t *pStr) {
static uint8_t i;
i = 0; do Tx1( pStr[i++] ); while (pStr[i] != 0);
}

// ������� �������� ������� �������� (������) CONST �� USART1
// ���� �� ���������� "0" ����
void Tx1StrConst(const uint8_t *pStr) {
static uint8_t i;
i = 0; do Tx1( pStr[i++] ); while (pStr[i] != 0);
}

// �����
