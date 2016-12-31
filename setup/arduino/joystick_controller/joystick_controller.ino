/*
  Arduino ROS node for Jetson Car
  MIT License
*/

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include <WProgram.h>
#endif

#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

///////////////////////////////DEFAULT PINS/////////////////////////////////////////
#define RC_ESC_PIN     7       // PWM PIN 7 for RC ESC Servo
#define RC_STEER_PIN   8       // PWM PIN 13 for RC Steer Servo
///////////////////////////////DEFAULT SERVO VALUES////////////////////////////////
//Constant ESC SERVO values
#define MAX_FORWARD    1600 //120     //MAX SPEED signal         (pulse = 2000ms)
#define NEUTRAL        1500 //95      //NEUTRAL signal           (pulse = 1500ms)
#define MAX_REVERSE    1400 //60      //MAX REVERSE SPEED signal (pulse = 1000ms)

//Constant STEERING SERVO values
#define MAX_LEFT       125
#define MIDDLE         95
#define MAX_RIGHT      60
//////////////////////////////GLOBAL VARIABLES/////////////////////////////////////
Servo STEER_SERVO;         // steering servo of my RC car [RedCat Volcano EPX]
Servo ESC;                 // Electric Speed Control for RC

int   current_speed;       // current speed value
int   current_pos;         // current position of the wheel

// Set up ROS nodes
ros::NodeHandle nh_;
std_msgs::String str_msg;
ros::Publisher chatter("arduino_publisher", &str_msg);
ros::Subscriber<geometry_msgs::Twist> driveSubscriber("/jetson_teleop_joystick/cmd_vel", &driveCallback) ;

//////////////////////////FUNCTION PROTOTYPES///////////////////////////////////////
void drive_callback(const geometery::geometry_msgs::Twist& signal){
    control_steering(signal);
    control_esc(signal);
}
int control_steering(const geometery::geometry_msgs::Twist);
int control_esc(const geometery::geometry_msgs::Twist);
int convert_signal(double, double, double, double , double);

void setup(){
    nh_.initNode();
    nh.advertise(chatter);
    nh.subsribe(driveSubscriber);

    current_speed = NEUTRAL;
    current_pos = MIDDLE;
    // Connect ESC and Steering Servo to PIN 7 and 8 respectively
    ESC.attach(RC_ESC_PIN);
    STEER_SERVO.attach(RC_STEER_PIN);

    // Set everything to neutral
    ESC.write(NEUTRAL);
    STEER_SERVO.write(MIDDLE);

    //Set up Serial library at 9600 bps (how many bytes can send in a second)
    Serial.begin(9600);
    Serial.println("Arduino starting");
}

void loop(){
    str_msg.data = "First Test";
    chatter.publis(str_msg);
    nh_.spinOnce();
    delay(1000);
}

int control_steering(const geometery::geometry_msgs::Twist  signal){
    int steer_angle = convert_signal()
}
int convert_signal(double toMap, double in_min, double in_max, double out_min, double out_max){
    return (toMap - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}