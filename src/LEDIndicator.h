#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H
#include "HardwareSerial.h"


class LED_Indicator
{
    public:
        LED_Indicator(int LED_PIN_in);
        virtual ~LED_Indicator();
        void start(){start_led=true;};
        void stop(){start_led=false;};
        void main();
        void setup();
        bool is_indicator_on(){return start_led;};
        bool is_blink_on(){return blink_on;};
        //void enable_serial(HardwareSerial * Serial);
        int process_command(String * input_command);
        void start_blink(unsigned int number, int time_interval);       
    protected:

    private:
        void check_time();
        void led_start();
        void led_stop();
        unsigned int PIN_LED;
        //bool serial_enabled=false;
        unsigned long current_time;
        bool start_led=false;
        bool led_on=false;//led state
        bool blink_on=false;
        bool time_passed=false;
        unsigned int blink_number;
        unsigned int blink_interval;
        //HardwareSerial * Serial=NULL;
};

#endif // LEDINDICATOR_H
