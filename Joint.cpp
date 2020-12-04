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

	sizeInitialMovements = 0;
	sizeLoopMovements = 0;
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
	

	//if (isInitial) {
	//	if (initialSequenceCounter < MAXIMUM_SEQUENCE) {
	//		initialMovements[initialSequenceCounter++] = new JointVelocity(input);
	//		output = true;
	//	}
	//} else {
	//	if (loopSequenceCounter < MAXIMUM_SEQUENCE) {
	//		loopMovements[loopSequenceCounter++] = new JointVelocity(input);
	//		output = true;
	//	}
	//}

	movements[sequenceCounter++] = new JointVelocity(input);
	
	return output;
}
			
bool Joint::popSequence(bool isInitial) { // False output indicates no pop occurred
	bool output = false;
	
	
	//if (isInitial) {
	//	if (initialSequenceCounter > 0) {
	//		delete initialMovements[initialSequenceCounter--];
	//		output = true;
	//	}
	//} else {
	//	if (loopSequenceCounter > 0) {
	//		delete loopMovements[loopSequenceCounter--];
	//		output = true;
	//	}
	//}
	
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
		int space;

		/*
		* SEQUENCE_PARAMETERS:
		* (1) position - Position to move the joint to (next position from previous position)
		* (2) spacing - Number to increment position each cycle (after each pause)
		* (3) duration - Number of pauses that should elapse before incrementing the joint
		* (4) timing - Number of timer ticks in each pause
		*/

		space = movements[sequenceNumber]->spacing;
		divisions = movements[sequenceNumber]->timing;
		divisions *= movements[sequenceNumber]->duration;
		firstAngle = movements[sequenceNumber]->position;
		//secondAngle = movements[sequenceNumber + 1]->position;
		//angleIncrement = (secondAngle - firstAngle) / divisions;
		//angle = angle + angleIncrement;

		++internalTimer;
		if (internalTimer > divisions) {
			internalTimer = 0;
			angle += movements[sequenceNumber]->spacing;
		}

		if (angle > firstAngle && space > 0 || angle < firstAngle && space < 0) {
			angle = firstAngle;
			++sequenceNumber;
			if (sequenceNumber > sequenceCounter) {
				sequenceNumber = sequenceCounter;
			}
		}		
}
 
void Joint::transitionLoop() {
	//isLoop = true;
	movements = loopMovements;
	sequenceCounter = 0;
	internalTimer = 0;
	sequenceNumber = 0;
}