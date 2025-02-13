#include "mbed.h"
#include "motor.h"
#include "platform/mbed_thread.h"
#include "pins.h"


constexpr int PWM_FREQUENCY = 30000;



int main()
{
    Motor L(MOTOR_L_PWM, MOTOR_L_DIR, MOTOR_L_BIPOLAR, ENCODER_L_A, ENCODER_L_B, NC, PWM_FREQUENCY);
    Motor R(MOTOR_R_PWM, MOTOR_R_DIR, MOTOR_R_BIPOLAR, ENCODER_R_A, ENCODER_R_B, NC, PWM_FREQUENCY);

    DigitalOut en (ENABLE);
    en.write(1);

    
    L.direction.write(1);
    L.bipolar.write(1);
    L.pwm.write(0.5f);
    R.direction.write(1);
    R.bipolar.write(1);
    R.pwm.write(0.5f);

    printf("Enc");
    while(true) {
         printf("%i %i\n", (int) L.encoder.getPulses(), (int) R.encoder.getPulses());
         wait(1);
    };

   


    while (L.encoder.getPulses() < 100 || R.encoder.getPulses() < 100) {
        if (L.encoder.getPulses() >= 100 ) R.stop();
        if (L.encoder.getPulses() >= 100 ) R.setPower(0);

    }
}
