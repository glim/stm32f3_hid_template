stm32f3_hid_template
====================

Eclipse/OpenOCD template for the STM32F3DISCOVERY USB HID Example

The main goal is to set this up as a template to develop custom HID devices on the super cheap Cortex M4.

This is based on a combination of tutorials.

The Eclipse integration comes from Andrei Istodorescu at http://engineering-diy.blogspot.com/2012/11/stm32f3-discovery-eclipse-openocd.html

To add the STM32F3 USB stack, I followed the template at https://www.das-labor.org/trac/browser/microcontroller/src-stm32f4xx/serialUSB which was recommended by Andrei as an example using USB CDC Serial. 

What I liked about the das-labor template was that it was 'compilable' just by copying the Libraries and Utilities folders from the STM32F3DISCOVERY software straight from ST. Andrei's example worked great for integrating the ST32 Peripheral Library, but wasn't working for me when adding the USB Library which also depends on the Peripheral Lib. Learning Makefile syntax yesterday was quite frustrating. 

The Makefile also included targetes from flashing via OpenOCD. I am still exploring the appropriate compiler flags, as they vary from one example to the next. 

Coming from the PIC32 world, I'd like to get a working HID bootloader using a compatible structure to the PIC32 HID bootloader found at http://www.schmalzhaus.com/UBW32/ (highly recommended for getting started with microcontrollers). I have yet to scour the web for an open source HID bootloader, and I figured it'd be a good exercise for me to learn the STM32 with anyways.
