#include <LEDIndicator.h>




LED_Indicator my_led(5);

int counter=0;
long int current_time;

void program(){
    switch(counter){
      case 0:
        if (millis()-current_time>=5000){
          current_time=millis();
          counter++;  
        }else{
          if (!my_led.is_indicator_on()){
            Serial.println("Start LED");
            my_led.start();
          }
        }
        break;
      case 1:
        if (millis()-current_time>=5000){
          current_time=millis();
          counter++;
          Serial.println("Start blink");
          my_led.start_blink(4, 500);
        }else{
          if (my_led.is_indicator_on()){
            my_led.stop();
            Serial.println("STOP LED");
          }
        }
        break;
        
      case 2:
        if (millis()-current_time>=5000){
          current_time=millis();
          counter++;
          my_led.start();
          Serial.println("Start LED2");
        }
        break;
     
      case 3:
        if (millis()-current_time>=1000){
          current_time=millis();
          counter++;
          Serial.println("Start Blink2");
          my_led.start_blink(4, 500);
        }
        break;
      case 4:
        if (millis()-current_time>=7000){
          current_time=millis();
          counter++;
          my_led.stop();
          Serial.println("Stop LED2");
        }
        break;
      case 5:
        if (millis()-current_time>=2000){
          counter=0;
          current_time=millis();
          Serial.println("Next round");
        }
        break;
    }
}

void setup() {
  my_led.setup();
  current_time=millis();
  Serial.begin(115200);
}

void loop() {
  program();
  my_led.main();
}
