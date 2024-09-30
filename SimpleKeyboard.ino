#include <LiquidCrystal_I2C.h>

const int LCD_I2C_ADDRESS = 0x27;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// Button pins
const short upButtonPin = 6;
const short downButtonPin = 5;
const short leftButtonPin = 4;
const short rightButtonPin = 3;
const short confirmButtonPin = 2;

// Alphabet configuration
const short alphabetLength = 7;
const short alphabetHeight = 4;
const char alphabetAndSymbols[alphabetHeight][alphabetLength] = {
  {'a', 'b', 'c', 'd', 'e', 'f', 'g'},
  {'h', 'i', 'j', 'k', 'l', 'm', 'n'},
  {'o', 'p', 'q', 'r', 's', 't', 'u'},
  {'v', 'w', 'x', 'y', 'z', ' ', ','}
};

// State variables
String lcdText = "";
int stringSize = 0;
short alphabetPositionX = 0;
short alphabetPositionY = 0;

void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(confirmButtonPin, INPUT_PULLUP);
}

void loop() {
  handleButtonInput();
  updateLCDText();
  printPosition();
  delay(250);
}

void handleButtonInput() {
  if (!digitalRead(upButtonPin)) {
    alphabetPositionY = max(alphabetPositionY - 1, 0);
  } else if (!digitalRead(downButtonPin)) {
    alphabetPositionY = min(alphabetPositionY + 1, alphabetHeight - 1);
  }

  if (!digitalRead(leftButtonPin)) {
    alphabetPositionX = max(alphabetPositionX - 1, 0);
  } else if (!digitalRead(rightButtonPin)) {
    alphabetPositionX = min(alphabetPositionX + 1, alphabetLength - 1);
  }

  if (!digitalRead(confirmButtonPin)) {
    addNewCharacter();
    handleLCDTextOverflow();
  }
}

void addNewCharacter() {
  char selectedChar = alphabetAndSymbols[alphabetPositionY][alphabetPositionX];
  lcdText.concat(selectedChar);
}

void handleLCDTextOverflow() {
  if (lcdText.length() > LCD_COLUMNS) {
      lcd.clear();
      lcdText = "";
    }
}

void updateLCDText() {
  lcd.setCursor(0, 0);
  lcd.print(lcdText);
}

void printPosition() {
  lcd.setCursor(0, 1);
  lcd.print("X: ");
  lcd.print(alphabetPositionX + 1);
  lcd.print("  Y: ");
  lcd.print(alphabetPositionY + 1);
}
