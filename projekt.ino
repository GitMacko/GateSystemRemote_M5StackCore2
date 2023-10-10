#include <M5Core2.h>



int panel = 0;
int led = 1;
int msg = 0;
int16_t hw = M5.Lcd.width()/2;
int16_t hh = M5.Lcd.height()/4;

Gesture swipeRight("swipe right", 160, DIR_RIGHT, 30, true);
Gesture swipeDown("swipe down", 120, DIR_DOWN, 30, true);
Gesture swipeLeft("swipe left", 160, DIR_LEFT, 30, true);
Gesture swipeUp("swipe up", 120, DIR_UP, 30, true);

ButtonColors on_clrs = {YELLOW, WHITE, WHITE};
ButtonColors off_clrs = {BLACK, WHITE, WHITE};
Button swiatlo(0, 0, 0, 0, false ,"Swiatlo", off_clrs, on_clrs, TL_DATUM);
Button paneldotykowy(0, 0, 0, 0, false ,"Panel dotykowy", off_clrs, on_clrs, TL_DATUM);

void doRotation(Event& e) {
    M5.Lcd.println("Witaj w systemie obslugi podjazdu"); 
}

void przyciski() {
  swiatlo.set(0, 120, hw - 20, hh - 20);
  M5.Buttons.draw();
  swiatlo.setLabel("Swiatlo");
}

void przyciski2() {
  paneldotykowy.set(15, 80, hw + 160 , hh + 80 );
  M5.Buttons.draw();
  paneldotykowy.setLabel("Panel dotykowy");
}

void WyborPanelu(int panel){
  if(panel==1){
    M5.Lcd.clearDisplay();
    PanelPoczatkowy();
  } else if (panel == 2) {
    M5.Lcd.clearDisplay();
    PanelGlowny();
  } else if (panel == 3) {
    M5.Lcd.clearDisplay();
    PanelAlarmu();
  }
}

void PanelPoczatkowy(){
  M5.Lcd.clearDisplay();
  paneldotykowy.set(hw * 5, 2 * hh, hw - 5, hh - 5);
  M5.Lcd.setTextColor(
      GREEN);  
  M5.Lcd.setTextSize(1);  
  M5.Lcd.setCursor(25, 12);  
  M5.Lcd.println("Witaj w systemie obslugi podjazdu"); 
  M5.Lcd.setCursor(1000, 12); 
  M5.Lcd.println("samochodowego!");  
  M5.Lcd.setCursor(3, 55);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.println("");
  M5.Lcd.setCursor(3, 75);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.println("Przycisk B - bramy");
  M5.Lcd.setCursor(3, 95);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.println("Przycisk C - panel glowny");
  M5.Lcd.setTextColor(WHITE);
  przyciski(); 
}

void PanelGlowny(){
  swiatlo.setLabel("");
  swiatlo.set(hw * 5, 2 * hh, hw - 5, hh - 5);
  paneldotykowy.set(20, 120, hw , hh);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(1,15);
  M5.Lcd.setTextColor(WHITE);
    M5.Lcd.print("Stan bramy wjazdowej: ");
    if(msg%2==0){
    M5.Lcd.setTextColor(RED);
    M5.Lcd.println("0");
    M5.Lcd.setTextColor(WHITE);
    }
  else  {
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println("1");
    M5.Lcd.setTextColor(WHITE);
    }
    M5.Lcd.print("Stan bramy garazowej: ");
    if(msg%2==0){
    M5.Lcd.setTextColor(RED);
    M5.Lcd.println("0");
    M5.Lcd.setTextColor(WHITE);
    }
  else  {
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println("1");
    M5.Lcd.setTextColor(WHITE);
    }
    

  if(led%2==0){
    M5.Lcd.print("Stan oswietlenia: ");
    M5.Lcd.setTextColor(RED);
    M5.Lcd.println("0");
    }
  else  {
    M5.Lcd.print("Stan oswietlenia: ");
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.println("1");
    }
    przyciski2();
}

void PanelAlarmu(){
  swiatlo.setLabel("");
  swiatlo.set(hw * 5, 2 * hh, hw - 5, hh - 5);
  paneldotykowy.set(hw * 5, 2 * hh, hw - 5, hh - 5);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(1,15);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.println("STAN ALARMU: 0");
  M5.Lcd.println("POWIADOMIENIA O ALARMIE: 0");
  M5.Lcd.println("OSWIETLENIE OSTRZEGAWCZE:0");
  M5.Lcd.println("AUTO ALARM: 0");
}





void setup() {
  M5.begin();
  M5.Buttons.addHandler(doRotation, E_GESTURE);
  PanelPoczatkowy();
}

void loop() {
  M5.update(); 
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
    panel = panel - 1;
    WyborPanelu(panel);
  } else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
    msg = msg + 1;
    M5.Lcd.setCursor(100,150+msg*12);
    if(msg%2==0)
    M5.Lcd.println("Zamykanie bram!");  
    else M5.Lcd.println("Otwieranie bram!");
    M5.Axp.SetLDOEnable(3, true);  
    delay(1000);
    M5.Axp.SetLDOEnable(3, false);  
  } else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) {
    panel = panel + 1 ;
    WyborPanelu(panel);
  } else if (swiatlo.wasReleased() || swiatlo.pressedFor(1000, 200)) {
    led = led + 1;
    if(led%2 == 0) {
    M5.Axp.SetLed(0);
    } else M5.Axp.SetLed(1);
  }
}
