/*
 Keyboard Controller Example

 Shows the output of a USB Keyboard connected to
 the Native USB port on an Arduino Due Board.

 created 8 Oct 2012
 by Cristian Maglie

 http://www.arduino.cc/en/Tutorial/KeyboardController

 This sample code is part of the public domain.
 */


// Require keyboard control library
#include <KeyboardController.h>

// Initialize USB Controller
USBHost usb;

// Attach keyboard controller to USB
KeyboardController keyboard(usb);

// This function intercepts key press
void keyPressed() {
}

// This function intercepts key release
void keyReleased() {
}

void loop() {
  static uint32_t counter = 1;
  if (counter == 1) {
      defaultBuf.Button |= SWITCH_L;
      defaultBuf.Button |= SWITCH_R;
      memcpy(&buffer, &defaultBuf, sizeof(USB_JoystickReport_Input_t));
  }
  else if (counter == 200000) {
      defaultBuf.Button = 0;
      memcpy(&buffer, &defaultBuf, sizeof(USB_JoystickReport_Input_t));
  }
  else if (counter == 400000) {
      counter = 0;
  }
  counter++;

  // We need to run our task to process and deliver data for our IN and OUT endpoints.
  HID_Task();
  // We also need to run the main USB management task.
  USB_USBTask();
  // Process USB tasks
  usb.Task();
}

void main() {
  // We also need to initialize the initial input reports.
  memset(&defaultBuf, 0, sizeof(USB_JoystickReport_Input_t));
  defaultBuf.LX = STICK_CENTER;
  defaultBuf.LY = STICK_CENTER;
  defaultBuf.RX = STICK_CENTER;
  defaultBuf.RY = STICK_CENTER;
  defaultBuf.HAT = HAT_CENTER;
  defaultBuf.Button |= 0x10;
  defaultBuf.Button |= 0x20;
  memcpy(&buffer, &defaultBuf, sizeof(USB_JoystickReport_Input_t));

  memset(&usbInput, 0, sizeof(USB_Input_Packet_t));

  // We'll start by performing hardware and peripheral setup.
  SetupHardware();
  // We'll then enable global interrupts for our use.
  GlobalInterruptEnable();

  while (true) {
    loop();
  }
}