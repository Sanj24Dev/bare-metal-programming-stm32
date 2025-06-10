#define PERIPH_BASE     0x40000000
#define AHBPERIPH_BASE (PERIPH_BASE + 0x00020000)
#define APBPERIPH_BASE (PERIPH_BASE + 0x00000000)

#define RCC_BASE       (AHBPERIPH_BASE + 0x00001000)
#define SYSCFG_BASE    (APBPERIPH_BASE + 0x00010000)
#define EXTI_BASE      (AHBPERIPH_BASE + 0x00001800)

#define IOPORT_BASE    (PERIPH_BASE + 0x10000000)
#define GPIOA_BASE     (IOPORT_BASE + 0x00000000)
#define GPIOC_BASE     (IOPORT_BASE + 0x00000800)

#define RCC_IOPENR      (*(volatile unsigned int *)(RCC_BASE + 0x34))
#define RCC_APBENR2     (*(volatile unsigned int *)(RCC_BASE + 0x40))

#define GPIOA_MODER     (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x14))
#define GPIOA_IDR       (*(volatile unsigned int *)(GPIOA_BASE + 0x10))

#define GPIOC_MODER     (*(volatile unsigned int *)(GPIOC_BASE + 0x00))
#define GPIOC_PUPDR     (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))
#define GPIOC_ODR       (*(volatile unsigned int *)(GPIOC_BASE + 0x14))
#define GPIOC_IDR       (*(volatile unsigned int *)(GPIOC_BASE + 0x10))

#define SYSCFG_EXTICR2  (*(volatile unsigned int *)(SYSCFG_BASE + 0x0C))
#define EXTI_IMR1       (*(volatile unsigned int *)(EXTI_BASE + 0x08))
#define EXTI_RTSR1      (*(volatile unsigned int *)(EXTI_BASE + 0x00))
#define EXTI_PR1        (*(volatile unsigned int *)(EXTI_BASE + 0x0C))

#define NVIC_ISER0      (*(volatile unsigned int *)0xE000E100)

#define LED_PIN        5      // Pin A5
#define BTN_PIN        7      // Pin C7 - D9 on the board

volatile bool led_toggle = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, STM32!");

  // Enable clock 
  RCC_IOPENR |= 1 << 0;    // it is the 0th bit for LED in Port A
  RCC_IOPENR |= 1 << 2;    // it is the 2nd bit for BTN in Port C
  RCC_APBENR2 |= 1 << 0;   // it is the 0th bit for SYSCFGEN for the EXTI => Enabling IRQ clock

  // Mode for PA5
  GPIOA_MODER &= ~(0b11 << (LED_PIN * 2));  // 00 at the particular bits, and 1s for rest, to clear the particular bits and keep the rest as it is
  GPIOA_MODER |= (0b01 << (LED_PIN * 2)); // output = 01 on bits 19,18

  // Mode for PC7
  GPIOC_MODER &= ~(0b11 << (BTN_PIN * 2));  // 00 at the particular bits, and 1s for rest, to clear the particular bits and keep the rest as it is
  GPIOC_MODER |= (0b00 << (BTN_PIN * 2)); // input = 00 on bits 3,2
  
  // Set EXTI7 source to GPIOC (0x2), so:
  SYSCFG_EXTICR2 &= ~(0xF << 0);  // EXTI7 is in EXTICR2, bits 3:0
  SYSCFG_EXTICR2 |= (0x2 << 0);   // 0x2 = GPIOC
  
  EXTI_IMR1 &= ~(1 << BTN_PIN);
  EXTI_IMR1 |= (1 << BTN_PIN);

  EXTI_RTSR1 &= ~(1 << BTN_PIN);
  EXTI_RTSR1 |= (1 << BTN_PIN);

  __disable_irq();
  NVIC_ISER0 |= (1 << 7);
  __enable_irq();

  // Since I am using online simulator and do not have access to the library files, I need to use the Arduino API to attach the interrupt handler
  attachInterrupt(digitalPinToInterrupt(9), EXTI_IRQHandler, RISING);
}

void loop() {
  if (led_toggle) {
    GPIOA_ODR ^= (1 << LED_PIN);
    led_toggle = false;

    int pin_state = (GPIOA_ODR & (1 << LED_PIN)) >> LED_PIN;
    if (pin_state == 1)
      Serial.println("LED ON");
    else
      Serial.println("LED OFF");
  }
}


// Interrupt Service Routine should be written this way, but since I am using Arduino API to attach the ISR, i need to name it differently
// extern "C" void EXTI4_15_IRQHandler(void) {
void EXTI_IRQHandler(void) {
  // the handling of this if condition and the clearing of the bit is done by the arduino API
  // if (EXTI_PR1 & (1 << BTN_PIN)) {
    // EXTI_PR1 |= (1 << BTN_PIN); // Clear pending bit
    led_toggle = true;
    Serial.println("Toggled");
  // }
}