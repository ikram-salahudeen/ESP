#include "mbed.h"
#include "wheel.h"
#include "pins.h"
#include "C12832.h"



constexpr float TURNING_RADIUS = 100;
constexpr float FORWARD_POWER = 0.5;
constexpr float TURNING_POWER = 0.2;



Wheel L(MOTOR_L_PWM, MOTOR_L_DIR, MOTOR_L_BIPOLAR, ENCODER_L_A, ENCODER_L_B, PWM_FREQUENCY);
Wheel R(MOTOR_R_PWM, MOTOR_R_DIR, MOTOR_R_BIPOLAR, ENCODER_R_A, ENCODER_R_B, PWM_FREQUENCY);

//C12832 lcd(D11, D13, D12, D7, D10);


void test() {

    printf("Enc");
    while(true) {
         printf("%i %i\n", (int) L.encoder.getPulses(), (int) R.encoder.getPulses());
         wait(1);
    };
}

void turn(int dir /* 1 right, -1 left */) {
    constexpr float distance = (3.14f / 2) * TURNING_RADIUS;

    L.setPower(-0.2 * dir);
    R.setPower( 0.2 * dir);

    int pulses = distance * (256.0f / (WHEEL_DIAMETER * 3.14f));
    int targetL = L.encoder.getPulses() - dir * pulses;
    int targetR = R.encoder.getPulses() + dir * pulses;

    while (dir * L.encoder.getPulses() > dir * targetL || dir * R.encoder.getPulses() < dir * targetR) {
        if (dir * L.encoder.getPulses() <= dir * targetL ) L.setPower(0);
        if (dir * R.encoder.getPulses() >= dir * targetR ) R.setPower(0);
    }
    wait(0.2);
}

void forward(float distance /* in mm */) {
    L.setPower(0.4);
    R.setPower(0.4);

    int pulses = distance * (256.0f / (WHEEL_DIAMETER * 3.14f));
    int targetL = L.encoder.getPulses() + pulses;
    int targetR = R.encoder.getPulses() + pulses;

    while (L.encoder.getPulses() < targetL || R.encoder.getPulses() < targetR) {
        if (L.encoder.getPulses() >= targetL ) L.setPower(0);
        if (R.encoder.getPulses() >= targetR ) R.setPower(0);
    }

    wait(0.2);
}

void square() {
    wait(2);

    forward(100);
    turn(1);
    
    forward(100);
    turn(1);
    
    forward(100);
    turn(1);

    forward(100);
    turn(1);

}



int main()
{
    
    DigitalOut en (ENABLE);
    en.write(1);

    L.setMode(Bipolar);
    L.setPower(0);
    R.setMode(Bipolar);
    R.setPower(0);



    wait(5);
   
    
        square();
        // square();
        //lcd.locate(8,20);
        //lcd.printf("L Pulses: %02.1d   R Pulses: %02.1d", L.encoder.getPulses(), R.encoder.getPulses());
    

}
