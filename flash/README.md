# Flash reading from the iCE40 UltraPlus

The goal of this example is to read, from the ice40 ultraplus some data in the flash with SPI.

The flash_master folder contains the script and image to write in the flash at 1MB or 0x100000 offset

The FPGA will read the data in the flash starting from 0x100000 and display it on the LED.

flash chip: N25Q032A13ESC40F, datasheet can be found here: https://www.micron.com/-/media/client/global/documents/products/data-sheet/nor-flash/serial-nor/n25q/n25q_32mb_3v_65nm.pdf

minimal erase cycle: 100k

Needs ~833Kb for the fpga bitstream

The flash chip has 32Mb or 4MB

Write data starting from 0x100000 (1MB) using the flash_master/flash_program.sh
to leave space for the bitstream
