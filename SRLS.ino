#include <OLED_I2C.h>

OLED  screen(SDA, SCL, 8);

extern uint8_t SmallFont[];
extern uint8_t TinyFont[];

extern unsigned char formulas[];
extern unsigned char seconds[];
extern unsigned char remote[];
extern unsigned char assault[];
extern unsigned char clicker[];

extern unsigned char elec[];
extern unsigned char grav[];

int timer = 0;
int scene = 0;
int menu = 1;
int gallery = 1;
int clicker_value = 0;
int menu_list[] = {"", "Formulas", "Seconds", "Clicker", "Remote", ""};
int menu_logos[] = {formulas, seconds, clicker, remote};
int gallery_content[] = {elec, grav};

void setup() {
  pinMode(11, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  screen.begin();
  screen.setFont(SmallFont);
  
  Serial.println("Setup Complete!");
}



void loop() {
  bool button1 = !digitalRead(11);
  bool button2 = !digitalRead(8);
  bool button3 = !digitalRead(5);
  
  screen.clrScr();

  switch (scene) {
    case 0:
      if (button1 == true) menu--;
      if (button2 == true) scene = menu;
      if (button3 == true) menu++;
      if (menu < 1) menu = 4;
      if (menu > 4) menu = 1;

      screen.drawBitmap(65, cos(timer)*1.5+2, menu_logos[menu-1], 60, 60);
      screen.drawRect(0, 0, 127, 63);
      screen.drawRoundRect(7, 28, 60, 44);
      screen.setFont(SmallFont);
      screen.print(menu_list[0+menu], 10, 32);
      screen.setFont(TinyFont);
      screen.print(menu_list[-1+menu], 5, 12);
      screen.print(menu_list[1+menu], 5, 52);
      
      break;
      
    case 1:
      if (button1 == true) scene = 0;
      if (button2 == true) gallery--;
      if (button3 == true) gallery++;
      if (gallery < 1) gallery = 2;
      if (gallery > 2) gallery = 1;
      screen.drawBitmap(0, 0, gallery_content[gallery-1], 128, 64);
      break;

    case 2:
      if (button1 == true) scene = 0;
      screen.setFont(SmallFont);
      screen.print("Second Counter", 0, 10);
      screen.print(String(timer), 0, 20);
      screen.print("Press button 2 to return", 0, 40);
      break;

    case 3:
      if (button1 == true) scene = 0;
      if (button2 == true) clicker_value++;
      if (button3 == true) clicker_value--;
      screen.setFont(SmallFont);
      screen.print("Button2 = +1", 0, 10);
      screen.print("Button3 = -1", 0, 20);
      screen.print("value: " + String(clicker_value), 0, 30);
      break;

    case 4:
      if (button1 == true) scene = 0;
      screen.setFont(SmallFont);
      screen.print("Remote Control unavailable", 0, 20);
      screen.print("Press button 2 to return", 0, 30);
      break;
      
  }

  timer++;
  screen.update();
  delay(80);
}
