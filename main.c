#include <stdio.h>

#define RESET_BASE        0x4000c000
#define RESET_DONE_OFFSET 0x08
#define IO_BANK_BASE      0x40014000
#define GPIO_CNTL_OFFSET  0xcc
#define SIO_BASE          0xd0000000
#define GPIO_OE_SET       0x24
#define GPIO_XOR          0x1c
#define LED_MASK          (1U << 25)

#define RESET_RESET       ((volatile unsigned int*)(RESET_BASE + 0x00))
#define RESET_DONE        ((volatile unsigned int*)(RESET_BASE + RESET_DONE_OFFSET))
#define GPIO25_CNTL       ((volatile unsigned int*)(IO_BANK_BASE + GPIO_CNTL_OFFSET ))
#define SIO_GPIO_OE_SET   ((volatile unsigned int*)(SIO_BASE + GPIO_OE_SET))
#define SIO_GPIO_XOR      ((volatile unsigned int*)(SIO_BASE + GPIO_XOR))
	
void delay(volatile int count);
void delay(volatile int count) {
    while(count > 0) {
        count--;
    }
}

int main(void) {
    // Clear reset bit for IO_BANK0
    *RESET_RESET &= ~(1U << 5);
    
    // Wait for hardware block to stabilize
    while((*RESET_DONE & (1U << 5)) == 0) {
        // Do nothing
    }
    
    // Configure GPIO25 function select to SIO
    *GPIO25_CNTL = 5;
    
    // Set GPIO25 to output mode
    *SIO_GPIO_OE_SET = LED_MASK;
    
    // Infinite blinking loop
    while(1) {
        *SIO_GPIO_XOR = LED_MASK;
        delay(100000);
    }
}