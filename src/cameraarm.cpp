#include "main.h"
#include <Servo.h>

#define PIN_SERVO_PAN  12
#define PIN_SERVO_TILT 14

enum servo_dir {
    SERVO_UP, SERVO_DOWN, SERVO_LEFT, SERVO_RIGHT, SERVO_RESET, SERVO_ULEFT, SERVO_URIGHT, SERVO_DLEFT, SERVO_DRIGHT
};

struct CamServo {

    void init(int pin, int default_angle = 80, int min_angle = 40, int max_angle = 140) {
        servo_.attach(pin, 500, 2500);
        servo_.write(default_angle);
        min_angle_ = min_angle;
        max_angle_ = max_angle;
        default_angle_ = default_angle;
    }

    void turnAbsolute(int angle) {
        int angle_ = angle;
        angle_ = min(max_angle_, angle);
        angle_ = max(min_angle_, angle_);
        servo_.write(angle_);
    }

    void turn(int direction, int angle_amount = 10) {
        int angle_ = servo_.read();
        int sign = 0;
        switch (direction)
        {
        case SERVO_LEFT: sign = 1; break;
        case SERVO_RIGHT: sign = -1; break;
        }
        angle_ = angle_ + angle_amount*sign;
        turnAbsolute(angle_);
    }

    void turning(int direction) {
        turning_direction_ = direction;
        switch (turning_direction_)
        {
        case SERVO_LEFT: target_angle_ = max_angle_; break;
        case SERVO_RIGHT: target_angle_ = min_angle_; break;
        }
        turning_ = true;
    }

    void update() {
        if (turning_) {
            long now = millis();
            if (now - last_turn_stamp_ > turn_duration_) {
                last_turn_stamp_ = now;
                turn(turning_direction_, 1); // only turn 1 degree of a time

                int current_angle = servo_.read();
                if (current_angle == target_angle_) {
                    turning_ = false;
                }
            }
        }
    }

    void stop() {
        turning_ = false;
        int current_angle = servo_.read();
        servo_.write(current_angle);
    }

    void reset() {
        turning_ = false;
        target_angle_ = default_angle_;
        servo_.write(default_angle_);
    }

    Servo servo_;
    int min_angle_, max_angle_;
    int default_angle_;

    int turning_direction_ = SERVO_LEFT;
    int target_angle_ = 0;
    bool turning_ = false;

    long last_turn_stamp_ = 0;
    long turn_duration_ = 5;
};

struct CamArmServo {

    void init() {
        servo_pan_.init(PIN_SERVO_PAN, 80);
        servo_tilt_.init(PIN_SERVO_TILT, 100);
    }

    void pan(int direction, int angle_amount = 10) {
        switch (direction)
        {
        case SERVO_LEFT: servo_pan_.turn(SERVO_LEFT, angle_amount); break;
        case SERVO_RIGHT: servo_pan_.turn(SERVO_RIGHT, angle_amount); break;
        }
    }

    void tilt(int direction, int angle_amount = 10) {
        switch (direction)
        {
        case SERVO_UP: servo_tilt_.turn(SERVO_RIGHT, angle_amount); break;
        case SERVO_DOWN: servo_tilt_.turn(SERVO_LEFT, angle_amount); break;
        }
    }

    void panning(int direction) {
        switch (direction)
        {
        case SERVO_LEFT: servo_pan_.turning(SERVO_LEFT); break;
        case SERVO_RIGHT: servo_pan_.turning(SERVO_RIGHT); break;
        }
    }

    void tilting(int direction) {
        switch (direction)
        {
        case SERVO_UP: servo_tilt_.turning(SERVO_RIGHT); break;
        case SERVO_DOWN: servo_tilt_.turning(SERVO_LEFT); break;
        }
    }

    void update() {
        servo_pan_.update();
        servo_tilt_.update();
    }

    void stop() {
        servo_pan_.stop();
        servo_tilt_.stop();
    }

    void reset() {
        servo_pan_.reset();
        servo_tilt_.reset();
    }

    CamServo servo_pan_;
    CamServo servo_tilt_;
};

CamArmServo cameraArm;

void initArmServos() {
  cameraArm.init();
}

void updateArmServors() {
    cameraArm.update(); // for panning & tilting update
}

void handleCamCmd(int dirCode) {
  switch (dirCode)
  {
  case SERVO_UP: cameraArm.tilting(SERVO_UP); break; // 0
  case SERVO_DOWN: cameraArm.tilting(SERVO_DOWN); break; // 1
  case SERVO_LEFT: cameraArm.panning(SERVO_LEFT); break; // 2
  case SERVO_RIGHT: cameraArm.panning(SERVO_RIGHT); break; // 3
  
  case SERVO_ULEFT: cameraArm.panning(SERVO_LEFT); cameraArm.tilting(SERVO_UP); break; // 5
  case SERVO_URIGHT: cameraArm.panning(SERVO_RIGHT); cameraArm.tilting(SERVO_UP); break; // 6
  case SERVO_DLEFT: cameraArm.panning(SERVO_LEFT); cameraArm.tilting(SERVO_DOWN); break; // 7
  case SERVO_DRIGHT: cameraArm.panning(SERVO_RIGHT); cameraArm.tilting(SERVO_DOWN); break; // 8

  case SERVO_RESET: cameraArm.reset(); break; // 4
  default: cameraArm.stop(); break;
  }
}