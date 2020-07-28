#define LED_PORT PORTA
#define SEG_PORT PORTC

void LED_ON(unsigned char pin);
void LED_OFF(unsigned char pin);

void SEG_ON(unsigned char PORT, unsigned char data);
void SEG_ON_two_numbers_all_in_one(unsigned int data);

void IO_init();
