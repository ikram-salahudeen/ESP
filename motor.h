#include "mbed.h"
#include "QEI.h"

enum Mode {
    Bipolar,
    Unipolar
};


class Motor {
    /*
    power = -1.00 (max power in reverse)
    power = 0.00 (no power)
    power = 1.00 (max power forward)
    */
    float power = 0;
    Mode mode = Bipolar;
    float frequency = 10000;
    
    
   

public:

PwmOut pwm;
    DigitalOut direction;
    DigitalOut bipolar;

     QEI encoder;

    Motor (
        PinName pwmPin, PinName directionPin, PinName bipolarPin,
        PinName encoder1, PinName encoder2, PinName encoderIdx,
        float frequency = 10000):
        pwm(pwmPin), direction(directionPin), bipolar(bipolarPin), frequency(frequency),
        encoder(encoder1, encoder2, encoderIdx, 256, QEI::X4_ENCODING) {
        pwm.period(1/frequency);
    };

    
    void setPower(float newPower) {
        if (newPower != power) {
            power = newPower;

        }
    }
    float getPower() { return power; };

    void setMode(Mode newMode){
        if (newMode != mode) {
            mode = newMode;

        }
    }
    Mode getMode() { return mode;};

    void setFrequency(float newFreq) {
        if (newFreq != frequency) {
            frequency = newFreq;
            pwm.period(1/frequency);
        }
    }
    float getFrequncy() { return frequency; };

    void stop() {
        pwm.suspend();
    }

    void setSpeed(float speed) {
        
    }

private:
    void update() {
        if (mode == Bipolar) {
            bipolar.write(1);
            pwm.write(0.5*power + 0.5);
        } else {
            bipolar.write(0);
            direction.write(power > 0 ? 1 : 0);
            pwm.write(abs(power));
        }

    }
};