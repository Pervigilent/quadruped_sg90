/*
 * File: Joint.cpp
 * Date: November 22, 2020
 * Author: Stewart Nash
 * Description: (see corresponding header)
 */
#include "Joint.h"

Joint::Joint() {
	pin = 0;

	isLoop = false;
	//isEnd = false;
	internalClock = 0;
	externalClock = 0;
	initialCounter = 0;
	loopCounter = 0;
	sequenceCounter = &initialCounter;
	sequenceNumber = 0;
	movements = &initialMovements;
}


Joint::Joint(int pinNumber) {
	pin = pinNumber;

	isLoop = false;
	//isEnd = false;
	internalClock = 0;
	externalClock = 0;
	initialCounter = 0;
	loopCounter = 0;
	sequenceCounter = &initialCounter;
	sequenceNumber = 0;
	movements = &initialMovements;
}
 
int Joint::getMovement() {
	int output;

	output = angle;
	
	return output;
}

bool Joint::popSequence() {
	bool output;

	output = false;
	if (*sequenceCounter > 0) {
		delete (*movements)[(*sequenceCounter)--];
		output = true;
	}

	return output;
}
			
bool Joint::popSequence(bool isInitial) { // False output indicates no pop occurred
	bool output = false;

	if (isInitial) {
		if (initialCounter > 0) {
			delete initialMovements[initialCounter--];
			output = true;
		}
	} else {
		if (loopCounter > 0) {
			delete loopMovements[loopCounter--];
			output = true;
		}
	}
	
	return output;
}

bool Joint::pushSequence(JointVelocity input) { // False output indicates value not pushed
	bool output;

	output = false;
	if (*sequenceCounter < MAXIMUM_SEQUENCE) {
		(*movements)[(*sequenceCounter)++] = new JointVelocity(input);
		output = true;
	}

	return output;
}

bool Joint::pushSequence(JointVelocity input, bool isInitial) { // False output indicates value not pushed
	bool output;

	output = false;
	if (isInitial) {
		if (initialCounter < MAXIMUM_SEQUENCE) {
			initialMovements[initialCounter++] = new JointVelocity(input);
			output = true;
		}
	} else {
		if (loopCounter < MAXIMUM_SEQUENCE) {
			loopMovements[loopCounter++] = new JointVelocity(input);
			output = true;
		}
	}

	return output;
}

void Joint::reset() {
	
}

void Joint::tickClock() {
		float increment;		
		float firstAngle, secondAngle;
		int divisions;
		int multiplier;
		int duration;

		/*
		 * SEQUENCE_PARAMETERS:
		 * (1) start - Start position of the joint
		 * (2) stop - End position of the joint
		 * (3) duration - Amount of time in which the movement should be accomplished
		 * (4) multiplier - Number of ticks in a unit of time
		 */

		if (isLoop) { //TODO: Remove this. There is a bug somewhere.
			sequenceCounter = &loopCounter;
			movements = &loopMovements;
		} else {
			sequenceCounter = &initialCounter;
			movements = &initialMovements;
		}
		if (*sequenceCounter > 0) {
			multiplier = (*movements)[sequenceNumber]->multiplier;
			duration = (*movements)[sequenceNumber]->duration;
			if (sequenceNumber == 0 && externalClock == 0 && internalClock == 0) {
				++externalClock;
				firstAngle = (*movements)[sequenceNumber]->start;
				angle = firstAngle;
				if (externalClock > multiplier) {
					externalClock = 0;
					++internalClock;
				}
				if (internalClock == duration) {
					++sequenceNumber;
					internalClock = 0;
					firstAngle = (*movements)[sequenceNumber]->start;
					angle = firstAngle;
				}
				secondAngle = (*movements)[sequenceNumber]->stop;
				divisions = (*movements)[sequenceNumber]->multiplier;
				divisions *= (*movements)[sequenceNumber]->duration;
				increment = secondAngle - firstAngle;
				increment /= divisions;
				angle += increment;
			} else {
				if (sequenceNumber < *sequenceCounter || internalClock < duration) {
					++externalClock;
					if (externalClock > multiplier) {
						externalClock = 0;
						++internalClock;
					}
					if (internalClock == duration) {
						++sequenceNumber;
						internalClock = 0;
						firstAngle = (*movements)[sequenceNumber]->start;
						angle = firstAngle;
					} else {
						secondAngle = (*movements)[sequenceNumber]->stop;
						firstAngle = (*movements)[sequenceNumber]->start;
						divisions = (*movements)[sequenceNumber]->multiplier;
						divisions *= (*movements)[sequenceNumber]->duration;
						increment = secondAngle - firstAngle;
						increment /= divisions;
						angle += increment;
					}
				}
			}

		}
}
 
void Joint::transitionLoop() {
	isLoop = true;
	movements = &loopMovements;
	sequenceCounter = &loopCounter;
	internalClock = 0;
	externalClock = 0;
	sequenceNumber = 0;
}