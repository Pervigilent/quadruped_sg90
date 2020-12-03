/*
 * File: Organism.cpp
 * Date: November 22, 2020
 * Author: Stewart Nash
 * Description: (See corresponding header file.)
 */
#include "Organism.h"
 
Organism::Organism() {
	isLoop = false;
	jointCount = 0;
}
 
/*
int Organism::popInitialMovement(int jointNumber) {
	jointList[jointNumber]->popSequence(true);
}

int Organism::popLoopMovement(int jointNumber) {
	jointList[jointNumber]->popSequence(false);
}
*/

bool Organism::addJoint(Joint input) {
	bool output;

	output = false;
	if (jointCount < MAXIMUM_JOINTS) {
		jointList[jointCount++] = input;
		output = true;
	}

	return output;
}

bool Organism::insertJoint(Joint input, int location) {
	bool output;

	output = false;
	if (jointCount == location - 1) {
		output = addJoint(input);
	}

	return output;
}

bool Organism::replaceJoint(Joint input, int location) {
	bool output;

	output = false;
	if (location <= jointCount) {
		jointList[location] = input;
		output = true;
	}

	return output;
}

int Organism::getMovement(int jointNumber) {
	return jointList[jointNumber].getMovement();
}

void Organism::incrementTime() {
	for (int i = 0; i < jointCount; i++) {
		jointList[i].tickClock();
	}
}

bool Organism::popSequence(int jointNumber, bool isInitial) {
	return jointList[jointNumber].popSequence(isInitial);
}

bool Organism::pushSequence(int jointNumber, JointVelocity input, bool isInitial) {
	return jointList[jointNumber].pushSequence(input, isInitial);
}
 
void Organism::transitionLoop() {
	isLoop = true; 
}