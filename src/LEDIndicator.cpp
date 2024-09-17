#include "LEDIndicator.h"
#include "Arduino.h"
#include "HardwareSerial.h"


LED_Indicator::LED_Indicator(int LED_PIN_in)
{   
    PIN_LED=LED_PIN_in;

}

LED_Indicator::~LED_Indicator()
{
    //dtor
}


void LED_Indicator::start_blink(unsigned int number, int time_interval){
    blink_number=number;
    blink_interval=time_interval;
    blink_on=true;
    current_time=millis();
    if (!start_led){
      led_start();
    }
}

void LED_Indicator::setup(){
  pinMode(PIN_LED,OUTPUT);
}

void LED_Indicator::check_time(){
    if (blink_on){
        if(millis()-current_time>=blink_interval){
            time_passed=true;
            current_time=millis();
        }
    }
}

void LED_Indicator::led_start(){
    if (!led_on){
        digitalWrite(PIN_LED,HIGH);
        led_on=true;
    }
}

void LED_Indicator::led_stop(){
    if (led_on){
        digitalWrite(PIN_LED,LOW);
        led_on=false;
    }
}

void LED_Indicator::main(){
    if (start_led && !blink_on){
        led_start();
    }else if (!start_led && !blink_on){
        led_stop();
    }
    if (blink_on){
      check_time();
      if (time_passed){
          time_passed=false;
          if(led_on){
              led_stop();
              if (!start_led){
                blink_number--;
              }
          }else{
              if (start_led){
                blink_number--;
              }
              led_start();
          }
          if(blink_number==0){
              blink_on=false;
          }
      }
    }
}

/*
void LED_Indicator::enable_serial(HardwareSerial * Serial_in){
    Serial=Serial_in;
    serial_enabled=true;
}

*/
/*
int LED_Indicator::process_command(String *input_command){
    if (serial_enabled){
        Serial->println("Action received!");
        if (input_command->substring(input_command->indexOf("_")+1,input_command->indexOf("_")+5)=="init"){
            float spd=input_command->substring(input_command->indexOf("S")+1,input_command->indexOf("A")).toFloat();
            float accl=input_command->substring(input_command->indexOf("A")+1,input_command->indexOf("T")).toFloat();
            float trn=input_command->substring(input_command->indexOf("T")+1).toFloat();
            if (input_command->substring(input_command->indexOf("D")+1,input_command->indexOf("S"))=="CW"){
                set_parameters(CW,spd,accl,trn);            
            }else if (input_command->substring(input_command->indexOf("D")+1,input_command->indexOf("S"))=="CCW"){
                set_parameters(CCW,spd,accl,trn);
            }
            return 0;
        }else if (input_command->substring(input_command->indexOf("_")+1,input_command->indexOf("_")+3)=="CW"){
            update_direction(CW);
            return 0;
        }else if (input_command->substring(input_command->indexOf("_")+1,input_command->indexOf("_")+4)=="CCW"){
            update_direction(CCW);
            return 0;
        }else if (input_command->substring(input_command->indexOf("_")+1,input_command->indexOf("_")+4)=="off"){
            stop();
            return 0;
        }else if (input_command->substring(input_command->indexOf("_")+1,input_command->indexOf("_")+3)=="on"){
            start();
            return 0;
        }else if (input_command->substring(input_command->indexOf("_")+1,input_command->indexOf("_")+3)=="D?"){
            Serial->println(get_direction());
            return 0;
        }else if (input_command->substring(input_command->indexOf("_")+1,input_command->indexOf("_")+3)=="S?"){
            Serial->println(get_speed());
            return 0;
        }else if (input_command->substring(input_command->indexOf("_")+1,input_command->indexOf("_")+3)=="A?"){
            Serial->println(get_accl());
            return 0;
        }else if (input_command->substring(input_command->indexOf("_")+1,input_command->indexOf("_")+3)=="T?"){
            Serial->println(get_turns());
            return 0;
        }else if (input_command->substring(input_command->indexOf("S")+1,input_command->indexOf("S")+5)=="NULL"){           
            update_speed(NULL);
            return 0;
        }else if (input_command->substring(input_command->indexOf("A")+1,input_command->indexOf("A")+5)=="NULL"){
            update_accl(NULL);        
            return 0;
        }else if (input_command->indexOf("S")>0){
            if (input_command->substring(input_command->indexOf("S")+1).toFloat()<=0){         
                return 1;
            }else {           
                update_speed(input_command->substring(input_command->indexOf("S")+1).toFloat());
                return 0;
            }
        }else if (input_command->indexOf("A")>0){
            if (input_command->substring(input_command->indexOf("A")+1).toFloat()<=0){          
                return 1;
            }else if (input_command->substring(input_command->indexOf("A")+1).toFloat()>0){
                update_accl(input_command->substring(input_command->indexOf("A")+1).toFloat());        
                return 0;
            }
        }else{
            return 1;
        }
    }
}
*/
