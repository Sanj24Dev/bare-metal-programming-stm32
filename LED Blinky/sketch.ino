#define PERIPH_BASE     0x40000000
#define AHBPERIPH_BASE (PERIPH_BASE + 0x00020000)
#define RCC_BASE       (AHBPERIPH_BASE + 0x00001000)
#define IOPORT_BASE    (PERIPH_BASE + 0x10000000)
#define GPIOA_BASE     (IOPORT_BASE + 0x00000000)

#define RCC_IOPENR      (*(volatile unsigned int *)(RCC_BASE + 0x34))
#define GPIOA_MODER     (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x14))
#define GPIOA_IDR       (*(volatile unsigned int *)(GPIOA_BASE + 0x10))

#define LED_PIN        5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, STM32!");

  // Enable clock for LED
  RCC_IOPENR |= 1 << 0;    // it is the 0th bit
  // Mode for PA5
  GPIOA_MODER &= ~(0b11 << (LED_PIN * 2));  // 00 at the particular bits, and 1s for rest, to clear the particular bits and keep the rest as it is
  GPIOA_MODER |= (0b01 << (LED_PIN * 2)); // output = 01 on bits 19,18
}

void loop() {
  // put your main code here, to run repeatedly:
  GPIOA_ODR ^= (1 << LED_PIN);
  int pin_state = (GPIOA_ODR & (1 << LED_PIN)) >> LED_PIN;
  if (pin_state == 1)
    Serial.println("LED ON");
  else
    Serial.println("LED OFF");
  delay(2000); 
}
