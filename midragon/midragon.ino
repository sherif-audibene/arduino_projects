#include <Wire.h>
#include <U8g2lib.h>

// Initialize the display
U8G2_ST7567_OS12864_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA); 

// Joystick pins
const int VRx = A0;  // X-axis
const int VRy = A1;  // Y-axis
const int SW = 4;    // Button switch

// Variables to store joystick values
int xValue, yValue;
bool buttonState;

void setup() {
  // Initialize display
  u8g2.setI2CAddress(0x3F * 2);  // Use the I2C address of your display (0x3F)
  u8g2.begin();

  // Set joystick pin modes
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);  // Use internal pull-up resistor for the switch
}

void loop() {
  // Read joystick values
  xValue = analogRead(VRx);  // Read X-axis (0-1023)
  yValue = analogRead(VRy);  // Read Y-axis (0-1023)
  buttonState = !digitalRead(SW);  // Read switch state (LOW when pressed)

  // Determine joystick direction based on threshold values
  String direction;
  if (xValue < 400) {
    direction = "Left";
  } else if (xValue > 600) {
    direction = "Right";
  } else if (yValue < 400) {
    direction = "Up";
  } else if (yValue > 600) {
    direction = "Down";
  } else {
    direction = "Center";
  }

  // Display joystick values on the screen
  u8g2.clearBuffer();  // Clear the internal buffer
  u8g2.setFont(u8g2_font_ncenB08_tr);  // Choose a font
  u8g2.drawStr(0, 10, "Joystick Values:");
  u8g2.setCursor(0, 30);
  u8g2.print("X: ");
  u8g2.print(xValue);
  u8g2.setCursor(0, 40);
  u8g2.print("Y: ");
  u8g2.print(yValue);
  u8g2.setCursor(0, 50);
  u8g2.print("Button: ");
  u8g2.print(buttonState ? "Pressed" : "Not Pressed");
  u8g2.setCursor(0, 60);
  u8g2.print("Direction: ");
  u8g2.print(direction);

  u8g2.sendBuffer();  // Transfer buffer content to the display

  delay(200);  // Small delay to make display easier to read
}
