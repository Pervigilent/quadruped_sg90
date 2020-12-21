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
	movements = initialMovements;
	//movements = &initialMovements;
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
	movements = initialMovements;
	//movements = &initialMovements;
}

void Joint::clear(bool isInitial) {

}
 
int Joint::getMovement() {
	int output;

	output = static_cast<int>(angle);
	
	return output;
}

bool Joint::popSequence() {
	bool output;

	output = false;
	if (*sequenceCounter > 0) {
		delete movements[(*sequenceCounter)--];
		//delete (*movements)[(*sequenceCounter)--];
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
		movements[(*sequenceCounter)++] = new JointVelocity(input);
		//(*movements)[(*sequenceCounter)++] = new JointVelocity(input);
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

void Joint::reset(bool isInitial) {
	
}

void Joint::restart(bool isInitial) {
	internalClock = 0;
	externalClock = 0;
	sequenceNumber = 0;
	if (isInitial) {
		//TODO: Should we transition here?
	}
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
			movements = loopMovements;
			//movements = &loopMovements;
		} else {
			sequenceCounter = &initialCounter;
			movements = initialMovements;
			//movements = &initialMovements;
		}

		if (*sequenceCounter > 0) {
			if (sequenceNumber == *sequenceCounter) {
				return;
				// This can only occur if it is an initial sequence because of identical code to the
				// commented code found below. Therefore, return and do nothing for the remaining time
				// if the end of the initial sequence has been reached.

				//if (isLoop) {
				//	sequenceNumber = 0;
				//} else {
				//	return;
				//}
			}
			multiplier = movements[sequenceNumber]->multiplier;
			//multiplier = (*movements)[sequenceNumber]->multiplier;
			duration = movements[sequenceNumber]->duration;
			//duration = (*movements)[sequenceNumber]->duration;
			if (sequenceNumber == 0 && externalClock == 0 && internalClock == 0) {
				++externalClock;
				firstAngle = static_cast<float>(movements[sequenceNumber]->start);
				//firstAngle = (*movements)[sequenceNumber]->start;
				angle = firstAngle;
				if (externalClock > multiplier) {
					externalClock = 0;
					++internalClock;
				}
				if (internalClock == duration) {
					++sequenceNumber;
					internalClock = 0;
					firstAngle = static_cast<float>(movements[sequenceNumber]->start);
					//firstAngle = (*movements)[sequenceNumber]->start;
					angle = firstAngle;
				}
				secondAngle = static_cast<float>(movements[sequenceNumber]->stop);
				//secondAngle = (*movements)[sequenceNumber]->stop;
				divisions = movements[sequenceNumber]->multiplier;
				//divisions = (*movements)[sequenceNumber]->multiplier;
				divisions *= movements[sequenceNumber]->duration;
				//divisions *= (*movements)[sequenceNumber]->duration;
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
						if (sequenceNumber == *sequenceCounter) {
							if (isLoop) {
								sequenceNumber = 0;
							} else {
								return;
							}
						}
						firstAngle = static_cast<float>(movements[sequenceNumber]->start);
						//firstAngle = (*movements)[sequenceNumber]->start;
						angle = firstAngle;
					} else {
						secondAngle = static_cast<float>(movements[sequenceNumber]->stop);
						//secondAngle = (*movements)[sequenceNumber]->stop;
						firstAngle = static_cast<float>(movements[sequenceNumber]->start);
						//firstAngle = (*movements)[sequenceNumber]->start;
						divisions = movements[sequenceNumber]->multiplier;
						//divisions = (*movements)[sequenceNumber]->multiplier;
						divisions *= movements[sequenceNumber]->duration;
						//divisions *= (*movements)[sequenceNumber]->duration;
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
	movements = loopMovements;
	//movements = &loopMovements;
	sequenceCounter = &loopCounter;
	internalClock = 0;
	externalClock = 0;
	sequenceNumber = 0;
}