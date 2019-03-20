#include <stdio.h>
#include "spi_lib.h"

#define SPI_NOP 0x00
#define SPI_INIT 0x01
#define SPI_SEND_BIT_INV 0x02
#define SPI_READ_REQ_BIT_INV 0x03
#define SPI_SET_LED 0x04
#define SPI_READ_REQ_LED 0x05

int main()
{
   spi_init();

   uint8_t no_param[3] = {0x0, 0x0, 0x0};
   uint8_t spi_status = 0;
   uint8_t data_read[3];
   uint8_t val_inv[3] = {0x38, 0xAE, 0x3B};
   uint8_t val_led_yellow[3] = {0x0, 0x0, 0x3};
   uint8_t val_led_blue[3] = {0x0, 0x0, 0x4};

   spi_send(SPI_INIT, no_param, NULL); // init

   usleep(2000);

   spi_send(SPI_SEND_BIT_INV, val_inv, &spi_status); // send values bit inversion
   printf("send inversion data, status: 0x%x\n", spi_status);

   usleep(2000);

   spi_send(SPI_READ_REQ_BIT_INV, no_param, NULL); //send read request
   usleep(2000);
   spi_read(data_read, &spi_status); // read data inversion

   for (size_t i = 0; i < 3; i++) {
      printf("bit inversion read idx %i: 0x%x, should be 0x%x\n", i, data_read[i], 0xFF&~val_inv[i]);
   }
   printf("status: 0x%x\n", spi_status);

   usleep(2000);

   spi_send(SPI_SET_LED, val_led_yellow, &spi_status); // led yellow
   printf("send yellow led, status: 0x%x\n", spi_status);

   usleep(2000);

   spi_send(SPI_READ_REQ_LED, no_param, NULL); //send led read request

   spi_read(data_read, &spi_status); // read led data
   printf("led_data read: 0x%x, 0x%x, 0x%x, status:0x%x\n", data_read[2], data_read[1], data_read[0], spi_status);

   //wait 2sec before setting led in blue
   usleep(2000*1000);

   spi_send(SPI_SET_LED, val_led_blue, &spi_status); // set led blue
   printf("send blue led, status: 0x%x\n", spi_status);

   return 0;
}
