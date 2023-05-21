#include "main.h"

#define PIN_RIGHT_SPEED 5
#define PIN_RIGHT_DIR   0 
#define PIN_LEFT_SPEED  4
#define PIN_LEFT_DIR    2

#define MAX_SPEED       512

enum motor_dir {
    MOTOR_FORWARD, MOTOR_BACKWARD, MOTOR_LEFT, MOTOR_RIGHT
};

struct Motor {
  void init(int pin_speed, int pin_dir, int max_speed = MAX_SPEED) {
    pin_speed_ = pin_speed;
    pin_dir_ = pin_dir;
    max_speed_ = max_speed;

    pinMode(pin_speed_, OUTPUT);
    pinMode(pin_dir_, OUTPUT);
    digitalWrite(pin_speed_, LOW);
    digitalWrite(pin_dir_, HIGH);
  }

  void move(int direction, float speed = 0.5f) {
    int speed_analog = int(speed*max_speed_);
    switch (direction)
    {
    case MOTOR_FORWARD: digitalWrite(pin_dir_, LOW); break;
    case MOTOR_BACKWARD: digitalWrite(pin_dir_, HIGH); break;
    default: return;
    }
    analogWrite(pin_speed_, speed_analog);
  }

  void stop() {
    analogWrite(pin_speed_, 0);
  }
  
  int pin_speed_, pin_dir_;
  int max_speed_;
};

struct RobotMotors {
  void init() {
    motorA_.init(PIN_RIGHT_SPEED, PIN_RIGHT_DIR);
    motorB_.init(PIN_LEFT_SPEED, PIN_LEFT_DIR);
  }

  void move(int direction, float speed = 0.5f) {
    switch (direction)
    {
    case MOTOR_FORWARD:
      motorA_.move(MOTOR_FORWARD, speed);
      motorB_.move(MOTOR_FORWARD, speed);
      break;
    case MOTOR_BACKWARD:
      motorA_.move(MOTOR_BACKWARD, speed);
      motorB_.move(MOTOR_BACKWARD, speed);
      break;
    case MOTOR_LEFT:
      motorA_.move(MOTOR_FORWARD, speed);
      motorB_.move(MOTOR_BACKWARD, speed);
      break;
    case MOTOR_RIGHT:
      motorA_.move(MOTOR_BACKWARD, speed);
      motorB_.move(MOTOR_FORWARD, speed);
      break;
    }
  }
  
  void stop() {
    motorA_.stop();
    motorB_.stop();
  }

  Motor motorA_, motorB_;
};

RobotMotors robot;

void initRobotMotors() {
  robot.init();
}

void updateRobotMotors() {

}

void handleRobotCmd(int dirCode) {
  switch (dirCode)
  {
  case MOTOR_FORWARD: robot.move(MOTOR_FORWARD); break;
  case MOTOR_BACKWARD: robot.move(MOTOR_BACKWARD); break;
  case MOTOR_LEFT: robot.move(MOTOR_LEFT); break;
  case MOTOR_RIGHT: robot.move(MOTOR_RIGHT); break;
  default: robot.stop(); break;
  }
}