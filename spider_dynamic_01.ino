//--> Begin start of Arduino code
/*
* File: spider_dynamic_01.ino
* Date: November 22, 2020
* Description: Test prototype code for dynamic movement.
*/
#include "Sequences.h"
#include "Organism.h"
#ifndef VISUAL_STUDIO_DEBUG
#include <Servo.h>
#else
#include "Servo.h"
#endif // !VISUAL_STUDIO_DEBUG

enum joints {
	right_front_tibia = 0,
	right_front_femur = 1,
	right_front_coxa = 2,
	left_front_tibia = 3,
	left_front_femur = 4,
	left_front_coxa = 5,
	right_back_tibia = 6,
	right_back_femur = 7,
	right_back_coxa = 8,
	left_back_tibia = 9,
	left_back_femur = 10,
	left_back_coxa = 11
};

const int INITIAL_DURATION = 100;
const int LOOP_DURATION = 100;

const int INITIAL_TICKS = INITIAL_DURATION * INITIAL_COUNT;
const int LOOP_TICKS = LOOP_DURATION * LOOP_COUNT;
const int SERVO_SPEED = 10;

const int RIGHT_TIBIA_SERVO = 11;
const int RIGHT_FEMUR_SERVO = 10;
const int RIGHT_COXA_SERVO = 9;

const int LEFT_TIBIA_SERVO = 6;
const int LEFT_FEMUR_SERVO = 5;
const int LEFT_COXA_SERVO = 3;

const int RT_FINAL_ANGLE = 135;
const int RF_FINAL_ANGLE = 30;
const int RC_FINAL_ANGLE = 90;

const int LT_FINAL_ANGLE = 45;
const int LF_FINAL_ANGLE = 150;
const int LC_FINAL_ANGLE = 90;

Organism myOrganism;
Servo *servoList[SERVO_NUMBER];
Joint *jointList[SERVO_NUMBER];

void populateSequences(
	int movements[][SEQUENCE_PARAMETERS],
	Organism &output,
	int count,
	int jointNumber,
	bool isInitial) {

	for (int i = 0; i < count; i++) {
		JointVelocity temporary(movements[i][0], movements[i][1], movements[i][2], movements[i][3]);
		output.pushSequence(jointNumber, temporary, isInitial);
	}
}

void setup() {
	servoList[right_front_tibia] = new Servo();
	servoList[right_front_femur] = new Servo();
	servoList[right_front_coxa] = new Servo();
	servoList[left_front_tibia] = new Servo();
	servoList[left_front_femur] = new Servo();
	servoList[left_front_coxa] = new Servo();

	servoList[right_front_tibia]->attach(RIGHT_TIBIA_SERVO);
	servoList[right_front_femur]->attach(RIGHT_FEMUR_SERVO);
	servoList[right_front_coxa]->attach(RIGHT_COXA_SERVO);
	servoList[left_front_tibia]->attach(LEFT_TIBIA_SERVO);
	servoList[left_front_femur]->attach(LEFT_FEMUR_SERVO);
	servoList[left_front_coxa]->attach(LEFT_COXA_SERVO);

	jointList[right_front_tibia] = new Joint(RIGHT_TIBIA_SERVO);
	jointList[right_front_femur] = new Joint(RIGHT_FEMUR_SERVO);
	jointList[right_front_coxa] = new Joint(RIGHT_COXA_SERVO);
	jointList[left_front_tibia] = new Joint(LEFT_TIBIA_SERVO);
	jointList[left_front_femur] = new Joint(LEFT_FEMUR_SERVO);
	jointList[left_front_coxa] = new Joint(LEFT_COXA_SERVO);

	myOrganism.insertJoint(*jointList[right_front_tibia], right_front_tibia);
	myOrganism.insertJoint(*jointList[right_front_femur], right_front_femur);
	myOrganism.insertJoint(*jointList[right_front_coxa], right_front_coxa);
	myOrganism.insertJoint(*jointList[left_front_tibia], left_front_tibia);
	myOrganism.insertJoint(*jointList[left_front_femur], left_front_femur);
	myOrganism.insertJoint(*jointList[left_front_coxa], left_front_coxa);

	for (int i = 0; i < SERVO_NUMBER; i++) {
		populateSequences(initialMovements[i], myOrganism, INITIAL_COUNT, i, true);
		populateSequences(loopMovements[i], myOrganism, LOOP_COUNT, i, false);
	}

	for (int i = 0; i < INITIAL_TICKS; i++) {
		for (int j = 0; j < SERVO_NUMBER; j++) {
			servoList[j]->write(myOrganism.getMovement(j));
		}
		myOrganism.incrementTime();
		delay(SERVO_SPEED);
	}
	myOrganism.transitionLoop(); // Transition to loop functionality
}

void loop() {
	for (int i = 0; i < LOOP_TICKS; i++) {
		for (int j = 0; j < SERVO_NUMBER; j++) {
			servoList[j]->write(myOrganism.getMovement(j));
		}
		myOrganism.incrementTime();
		delay(SERVO_SPEED);
	}
}

void cleanup() {
	delete servoList[right_front_tibia];
	delete servoList[right_front_femur];
	delete servoList[right_front_coxa];
	delete servoList[left_front_tibia];
	delete servoList[left_front_femur];
	delete servoList[left_front_coxa];

	delete jointList[right_front_tibia];
	delete jointList[right_front_femur];
	delete jointList[right_front_coxa];
	delete jointList[left_front_tibia];
	delete jointList[left_front_femur];
	delete jointList[left_front_coxa];
}

/*
* Appendix
*
* Joint 1 (right tibia): FINAL_ANGLE = 135, (flexion, extension) = (180, 0)
* Joint 2 (right femur): FINAL_ANGLE = 30, (flexion, extension) = (0, 180)
* Joint 3 (right coxa): FINAL_ANGLE = 90, (flexion, extension) = (0, 135)
*
* Joint 4 (left tibia): FINAL_ANGLE = 45, (flexion, extension) = (0, 180)
* Joint 5 (left femur): FINAL_ANGLE = 150, (flexion, extension) = (180, 0)
* Joint 6 (left coxa): FINAL_ANGLE = 90, (flexion, extension) = (180, 45)
*
* Joint 1 = Pin 11
* Joint 2 = Pin 10
* Joint 3 = Pin 9
*
* Joint 4 = Pin 6
* Joint 5 = Pin 5
* Joint 6 = Pin 3
*
* SG90 Servo:
* Orange = PWM
* Red = VCC (+5V)
* Brown = GND (Ground)
*/