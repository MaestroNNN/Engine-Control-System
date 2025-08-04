// ========= Инициализация микроконтроллера =========
static __INLINE void main_init() {
// Буфер предвыборки разрешён, 2 цикла задержки для FLASH, см. PM0075
FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;
RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // HCLK = SYSCLK
RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // PCLK1 = SYSCLK / 2 (APB1)
RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // PCLK2 = SYSCLK (APB2)
RCC->CFGR |= RCC_CFGR_SW_PLL; // Выбираем работу от PLL
RCC->CFGR |= RCC_CFGR_PLLMULL9; // SYSCLK = 72 MHz
RCC->CFGR |= RCC_CFGR_PLLSRC_HSE; // Тактирования PLL от кварца
RCC->CR |= RCC_CR_HSEON; //Запускаем генератор HSE
while (!(RCC->CR & RCC_CR_HSERDY)) {};
RCC->CR |= RCC_CR_PLLON; // Запускаем PLL
while ((RCC->CR & RCC_CR_PLLRDY) == 0) {};
// Ожидаем когда PLL станет источником тактирования
while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {};
//RCC->CR &= ~RCC_CR_HSION; // Отключаем внутренний RC-генератор

//====================== DWT ======================
SCB_DEMCR |= 0x01000000; // разрешаем использовать счётчик
DWT_CYCCNT = 0; // обнуляем значение счётного регистра
DWT_CONTROL |= 1; // запускаем счётчик  

//====================== ПОРТЫ ======================  
RCC->APB2ENR = RCC_APB2ENR_IOPAEN; // Включить тактирование порта PORTA 
// pin 3 кнопка на плате
GPIOA->CRL &= ~GPIO_CRL_MODE3; // Сброс настроек MODE
// Настройка вывода:  Цифр. вход, Частота перключений до 10 МГц
GPIOA->CRL &= ~GPIO_CRL_CNF3; // Сброс настроек CNF
// Настройка вывода: Цифр. вход - Input floating 
GPIOA->CRL |= GPIO_CRL_CNF3_1; 
//================= Группа портов "B" ===========================
RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Включаем тактирование порта GPIO "C"
// pin 13 зеленый светодиод на плате
GPIOB->CRL &= ~GPIO_CRL_MODE0; // Сброс настроек MODE
// Настройка вывода: Цифр. выход, Частота перключений до 10 МГц
GPIOB->CRL |= GPIO_CRL_MODE0; 
// Настройка вывода: Цифр. выход - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF0;

GPIOB->CRL &= ~GPIO_CRL_MODE1; // Сброс настроек MODE
// Настройка вывода: Цифр. выход, Частота перключений до 10 МГц
GPIOB->CRL |= GPIO_CRL_MODE1; 
// Настройка вывода: Цифр. выход - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF1;

GPIOB->CRL &= ~GPIO_CRL_MODE5; // Сброс настроек MODE
// Настройка вывода: Цифр. выход, Частота перключений до 10 МГц
GPIOB->CRL |= GPIO_CRL_MODE5; 
// Настройка вывода: Цифр. выход - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF5;

GPIOB->CRL &= ~GPIO_CRL_MODE6; // Сброс настроек MODE
// Настройка вывода: Цифр. выход, Частота перключений до 10 МГц
GPIOB->CRL |= GPIO_CRL_MODE6; 
// Настройка вывода: Цифр. выход - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF6;

GPIOB->CRL &= ~GPIO_CRL_MODE7; // Сброс настроек MODE
// Настройка вывода: Цифр. выход, Частота перключений до 10 МГц
GPIOB->CRL |= GPIO_CRL_MODE7; 
// Настройка вывода: Цифр. выход - Push-pull
GPIOB->CRL &= ~GPIO_CRL_CNF7;

GPIOB->CRH &= ~GPIO_CRH_MODE8; // Сброс настроек MODE
// Настройка вывода: Цифр. выход, Частота перключений до 10 МГц
GPIOB->CRH |= GPIO_CRH_MODE8; 
// Настройка вывода: Цифр. выход - Push-pull
GPIOB->CRH &= ~GPIO_CRH_CNF8;

//================= Группа портов "C" ===========================
RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Включаем тактирование порта GPIO "C"
// pin 13 зеленый светодиод на плате
GPIOC->CRH &= ~GPIO_CRH_MODE13; // Сброс настроек MODE
// Настройка вывода: Цифр. выход, Частота перключений до 10 МГц
GPIOC->CRH |= GPIO_CRH_MODE13; 
// Настройка вывода: Цифр. выход - Push-pull
GPIOC->CRH &= ~GPIO_CRH_CNF13;

//======================== АЦП ========================
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Включить тактирование порта PORTA 
GPIOA->CRL &= ~GPIO_CRL_MODE0; // PA0 = вход 
GPIOA->CRL &= ~GPIO_CRL_MODE1; // PA1 = вход 
GPIOA->CRL &= ~GPIO_CRL_CNF0; // PA0 = аналоговый
GPIOA->CRL &= ~GPIO_CRL_CNF1; // PA1 = аналоговый

RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8; // Тактирование PCLK2 / 8 = 9 MHz
RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Разрешить тактирование ADC1	  
RCC->APB2RSTR |= RCC_APB2RSTR_ADC1RST; // Сброс ADC1
RCC->APB2RSTR &= ~RCC_APB2RSTR_ADC1RST; // Конец сброса ADC1  

ADC1->CR1 &= ~ADC_CR1_DUALMOD; // Независимый режим работы
ADC1->CR1 &= ~ADC_CR1_SCAN; // Режим без сканирования	 

ADC1->CR2 &= ~ADC_CR2_CONT; // Режим однократного преобразования
// Преобразование по событию разрешено и это SWSTART
ADC1->CR2 |= ADC_CR2_EXTTRIG | ADC_CR2_EXTSEL; 

// Время выборки канала 239,5 цикла
ADC1->SMPR2 |= ADC_SMPR2_SMP0;
 
ADC1->CR2 |= ADC_CR2_ADON; // Включить ADC1 
ADC1->CR2 |= ADC_CR2_RSTCAL; delay_us(10); // Разрешаем сброс регистров калибровки 
while (ADC1->CR2 & ADC_CR2_RSTCAL) {}; // Ждём окончание сброса	регистров 
ADC1->CR2 |= ADC_CR2_CAL; // Разрешаем калибровку	   
while (ADC1->CR2 & ADC_CR2_CAL) {}; // Ждём окончание калибровки


//====================== USART1 ====================== 
// Включаем тактирование порта GPIOA и блока альтернативных функций
RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN); 
RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Включаем тактирование USART1
// PA9 (TX1) AFIO Push-Pull, 10MHz. PA10 (RX1) HiZ, 10MHz
// Вначале устанавливаем пары бит в "00", это делать обязательно !
GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9 | GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
// Потом нужные биты устанавливаем в '1'
GPIOA->CRH |= (GPIO_CRH_MODE9_0 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_0); 
USART1->BRR = 7500; // PCLK2 / Baud = 72000000 / 9600 бод
// Включаем USART, передатчик и приемник
USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
USART1->CR1 |= USART_CR1_RXNEIE; // Разрешаем прерывание по приёму RX
// Настройки по умолчанию: 8 инф. бит, 1 стоповый бит, контроля чётности нет
// Разрешаем прерывания UART1 в контроллере прерываний
NVIC_EnableIRQ(USART1_IRQn);

// ======================== TIM2 =======================
// Разрешаем тактирование, PCLK1 = 12 МГц, TIM2 получается x 2 = 24 МГц
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
TIM2->SMCR &= ~TIM_SMCR_SMS; // Выбираем внутреннее тактирование
TIM2->PSC = 72 - 1; // Шаг (квант) счёта 1 мкс, 1 MHz
TIM2->ARR = 100 - 1; // Переполнение через 100 мкс
TIM2->DIER |= TIM_DIER_UIE; // Разрешаем прерывание по переполнению таймера
NVIC_EnableIRQ(TIM2_IRQn); // Разрешаем прерывание в контроллере прерываний
TIM2->CR1 = TIM_CR1_CEN; // Разрешаем счёт
}  
// КОНЕЦ