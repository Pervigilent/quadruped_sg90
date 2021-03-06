/*
 * File: spider_dynamic_01.cpp
 * Date: December 2, 2020
 * Author: Stewart Nash
 * Description: This file is a stand-in for the spider_dynamic_01.ino which
 *		Arduino uses. It is only meant for debugging the application in a
 *		standard C++ environment (non-arduino) such as Visual Studio.
 */
#define VISUAL_STUDIO_DEBUG
#include <iostream>
#include <Windows.h>

// spider_dynamic_01.cpp : Defines the entry point for the console application.

void setup(); // The initial Arduino routine
void loop(); // The main Arduino routine
void delay(int input); // Placeholder for Arduino delay
void cleanup();

const int SLEEP_MULTIPLE = 10;

int main(int argc, char *argv[]) {

	setup();
	while (true) {
		loop();
	}

	cleanup();

    return 0;
}

void delay(int input) {
	std::cout << "[INFO spider_dynamic_01.cpp delay(int input)]: Delay, " << input;
	std::cout << "." << std::endl;
	Sleep(input * SLEEP_MULTIPLE);
}

//--> Begin start of Arduino code
/*
* File: spider_dynamic_01.ino
* Date: November 22, 2020
* Description: Test prototype code for dynamic movement.
*/

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

const int SEQUENCE_PARAMETERS = 4;

const int SERVO_NUMBER = 6;
const int INITIAL_TICKS = 16;
const int LOOP_TICKS = 16;
const int SERVO_SPEED = 20;

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

/*
 * SEQUENCE_PARAMETERS:
 * (1) position - Position to move the joint to (next position from previous position)
 * (2) spacing - Number to increment position each cycle (after each pause)
 * (3) duration - Number of pauses that should elapse before incrementing the joint
 * (4) timing - Number of timer ticks in each pause
 */

int initialMovements[SERVO_NUMBER][3][SEQUENCE_PARAMETERS] = {
	{
		{ 0, 5, 1, 1 },
		{ 45, 5, 1, 1 },
		{ 90, 5, 1, 1 }
	}, {
		{ 0, 5, 1, 1 },
		{ 45, 5, 1, 1 },
		{ 90, 5, 1, 1 }
	}, {
		{ 0, 5, 1, 1 },
		{ 45, 5, 1, 1 },
		{ 90, 5, 1, 1 }
	}, {
		{ 0, 5, 1, 1 },
		{ 45, 5, 1, 1 },
		{ 90, 5, 1, 1 }
	}, {
		{ 0, 5, 1, 1 },
		{ 45, 5, 1, 1 },
		{ 90, 5, 1, 1 }
	}, {
		{ 0, 5, 1, 1 },
		{ 45, 5, 1, 1 },
		{ 90, 5, 1, 1 }
	}
};

int loopMovements[SERVO_NUMBER][3][SEQUENCE_PARAMETERS] = {
	{
		{ 90, 5, 1, 1 },
		{ 135, 5, 1, 1 },
		{ 180, 5, 1, 1 }
	},{
		{ 90, 5, 1, 1 },
		{ 135, 5, 1, 1 },
		{ 180, 5, 1, 1 }
	},{
		{ 90, 5, 1, 1 },
		{ 135, 5, 1, 1 },
		{ 180, 5, 1, 1 }
	},{
		{ 90, 5, 1, 1 },
		{ 135, 5, 1, 1 },
		{ 180, 5, 1, 1 }
	},{
		{ 90, 5, 1, 1 },
		{ 135, 5, 1, 1 },
		{ 180, 5, 1, 1 }
	},{
		{ 90, 5, 1, 1 },
		{ 135, 5, 1, 1 },
		{ 180, 5, 1, 1 }
	}
};

void populateSequences(
	int movements[][SEQUENCE_PARAMETERS],
	Organism output,
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
		populateSequences(initialMovements[i], myOrganism, 3, i, true);
		populateSequences(loopMovements[i], myOrganism, 3, i, false);
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
