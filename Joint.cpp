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
	isEnd = false;
	initialSequenceCounter = 0;
	loopSequenceCounter = 0;
	sequenceCounter = 0;
	internalTimer = 0;
	sequenceNumber = 0;
	movements = initialMovements;
}


Joint::Joint(int pinNumber) {
	pin = pinNumber;

	isLoop = false;
	isEnd = false;
	initialSequenceCounter = 0;
	loopSequenceCounter = 0;
	sequenceCounter = 0;
	internalTimer = 0;
	sequenceNumber = 0;
	movements = initialMovements;
}
 
int Joint::getMovement() {
	int output;
	
	/*
	if (isLoop) {
		if (!isEnd) {
			if (internalTimer < loopMovements[sequenceNumber]->duration) {
				
			}

		} else {
			
		}
	} else {
		if (!isEnd) {
			
		} else {
			
		}		
	}
	*/
	output = angle;
	
	return output;
}

bool Joint::pushSequence(JointVelocity input, bool isInitial) { // False output indicates value not pushed
	bool output = false;
	
	/*
	if (isInitial) {
		if (initialSequenceCounter < MAXIMUM_SEQUENCE) {
			initialMovements[initialSequenceCounter++] = new JointVelocity(input);
			output = true;
		}
	} else {
		if (loopSequenceCounter < MAXIMUM_SEQUENCE) {
			loopMovements[loopSequenceCounter++] = new JointVelocity(input);
			output = true;
		}
	}
	*/
	movements[sequenceCounter++] = new JointVelocity(input);
	
	return output;
}
			
bool Joint::popSequence(bool isInitial) { // False output indicates no pop occurred
	bool output = false;
	
	/*
	if (isInitial) {
		if (initialSequenceCounter > 0) {
			delete initialMovements[initialSequenceCounter--];
			output = true;
		}
	} else {
		if (loopSequenceCounter > 0) {
			delete loopMovements[loopSequenceCounter--];
			output = true;
		}
	}
	*/
	if (sequenceCounter > 0) {
		delete movements[sequenceCounter--];
	}
	
	return output;
}

void Joint::reset() {
	
}

void Joint::tickClock() {
		float angleIncrement;		
		float firstAngle, secondAngle;
		int divisions;
		
		divisions = movements[sequenceCounter]->timing;
		divisions *= movements[sequenceCounter]->duration;
		firstAngle = movements[sequenceCounter]->position;
		secondAngle = movements[sequenceCounter + 1]->position;
		angleIncrement = (secondAngle - firstAngle) / divisions;
		angle = angle + angleIncrement;		
}
 
void Joint::transitionLoop() {
	//isLoop = true;
	movements = loopMovements;
	sequenceCounter = 0;
	internalTimer = 0;
	sequenceNumber = 0;
}