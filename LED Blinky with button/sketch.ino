#define PERIPH_BASE     0x40000000
#define AHBPERIPH_BASE (PERIPH_BASE + 0x00020000)
#define RCC_BASE       (AHBPERIPH_BASE + 0x00001000)
#define IOPORT_BASE    (PERIPH_BASE + 0x10000000)
#define GPIOA_BASE     (IOPORT_BASE + 0x00000000)
#define GPIOB_BASE     (IOPORT_BASE + 0x00000400)

#define RCC_IOPENR      (*(volatile unsigned int *)(RCC_BASE + 0x34))
#define GPIOA_MODER     (*(volatile unsigned int *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x14))
#define GPIOA_IDR       (*(volatile unsigned int *)(GPIOA_BASE + 0x10))

#define GPIOB_MODER     (*(volatile unsigned int *)(GPIOB_BASE + 0x00))
#define GPIOB_ODR       (*(volatile unsigned int *)(GPIOB_BASE + 0x14))
#define GPIOB_IDR       (*(volatile unsigned int *)(GPIOB_BASE + 0x10))

#define LED_PIN        5      // Pin A5
#define BTN_PIN        2      // Pin B2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, STM32!");

  // Enable clock 
  RCC_IOPENR |= 1 << 0;    // it is the 0th bit for LED in Port A
  RCC_IOPENR |= 1 << 1;    // it is the 1st bit for BTN in Port B

  // Mode for PA5
  GPIOA_MODER &= ~(0b11 << (LED_PIN * 2));  // 00 at the particular bits, and 1s for rest, to clear the particular bits and keep the rest as it is
  GPIOA_MODER |= (0b01 << (LED_PIN * 2)); // output = 01 on bits 19,18

  // Mode for PB2
  GPIOB_MODER &= ~(0b11 << (BTN_PIN * 2));  // 00 at the particular bits, and 1s for rest, to clear the particular bits and keep the rest as it is
  GPIOB_MODER |= (0b00 << (BTN_PIN * 2)); // input = 00 on bits 3,2
}

void loop() {
  do {    // check for button bounce and to assure if the button is actually pressed
    if (((GPIOB_IDR & (1 << BTN_PIN)) >> BTN_PIN) == 1) { // active HIGH logic
      delay(20);
      if (((GPIOB_IDR & (1 << BTN_PIN)) >> BTN_PIN) == 1)
        break;
    }
  } while(1);
  
  GPIOA_ODR ^= (1 << LED_PIN);

  int pin_state = (GPIOA_ODR & (1 << LED_PIN)) >> LED_PIN;
  if (pin_state == 1)
    Serial.println("LED ON");
  else
    Serial.println("LED OFF");

  // Wait for button release to avoid multiple toggles
  do {
    if (((GPIOB_IDR & (1 << BTN_PIN)) >> BTN_PIN) == 0) {
      delay(20);
      if (((GPIOB_IDR & (1 << BTN_PIN)) >> BTN_PIN) == 0)
        break;
    }
  } while (1);
}
