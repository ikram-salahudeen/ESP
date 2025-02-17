#include "mbed.h"
#include "QEI.h"

constexpr int PWM_FREQUENCY = 30000;
constexpr float WHEEL_DIAMETER = 50; // mm

enum Mode {
    Bipolar,
    Unipolar
};

constexpr float Kp = 1;
constexpr float Ki = 1;




class Wheel {
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

    Wheel (
        PinName pwmPin, PinName directionPin, PinName bipolarPin,
        PinName encoder1, PinName encoder2, PinName encoderIdx,
        float frequency = 10000):
        pwm(pwmPin), direction(directionPin), bipolar(bipolarPin), frequency(frequency),
        encoder(encoder1, encoder2, encoderIdx, 256, QEI::X4_ENCODING) {
        pwm.period(1/frequency);
        speedTicker.attach(callback(this, &Wheel::speedControlISR), 0.1);
        pwm.suspend();
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
        isMoving = false;
    }

    void start() {
        pwm.resume();
        isMoving = true;
    }

    void speedControlISR() {
        if (!isMoving) return;

        static int previousPulses = 0;
        static float previousTime = 0;
        float newTime = 0;//timer.read();
        int newPulses = encoder.getPulses();
        //float calculatedSpeed = (newPulses - previousPulses) (newTime - previousTime)

        //float error = targetSpeed;
    }

    void setSpeed(float speed) {
        targetSpeed = speed;
    }

private:
    float targetSpeed = 0;
    Ticker speedTicker;
    bool isMoving = false;

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