#!/bin/bash
sudo dfu-programmer atmega16u2 erase
sudo dfu-programmer atmega16u2 flash Arduino-COMBINED-dfu-usbserial-atmega16u2-Uno-Rev3.hex
sudo dfu-programmer atmega16u2 reset