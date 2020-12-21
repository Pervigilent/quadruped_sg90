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

bool Organism::clear(int jointNumber, bool isInitial) {
	bool output;

	output = false;
	if (jointNumber < jointCount) {
		jointList[jointNumber].clear(isInitial);
	}

	return output;
}

bool Organism::clear(bool isInitial) {
	bool output;

	output = true;
	for (int i = 0; i < jointCount; i++) {
		clear(i, isInitial);
	}

	return output;
}

int Organism::getMovement(int jointNumber) {
	return jointList[jointNumber].getMovement();
}

void Organism::incrementTime(int jointNumber) {
	jointList[jointNumber].tickClock();
}

void Organism::incrementTime() {
	for (int i = 0; i <= jointCount; i++) {
		jointList[i].tickClock();
	}
}

bool Organism::insertJoint(Joint input, int location) {
	bool output;

	output = false;
	if (jointCount == location - 1) {
		output = addJoint(input);
	}

	return output;
}

bool Organism::popSequence(int jointNumber, bool isInitial) {
	return jointList[jointNumber].popSequence(isInitial);
}

bool Organism::popSequence(bool isInitial) {
	bool output;

	output = false;

	return output;
}

bool Organism::pushSequence(int jointNumber, JointVelocity input, bool isInitial) {
	return jointList[jointNumber].pushSequence(input, isInitial);
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

bool Organism::reset(int jointNumber, bool isInitial) {
	bool output;

	output = false;
	if (jointNumber < jointCount) {
		jointList[jointNumber].reset(isInitial);
		output = true;
	}


	return output;
}

bool Organism::reset(bool isInitial) {
	bool output;

	output = true;
	//for (int i = 0; i < jointCount; i++) {
	//	jointList[i].reset(isInitial);
	//}
	for (int i = 0; i < jointCount; i++) {
		//if (!reset(i, isInitial)) { // Always evaluates to true
		//	output = false;
		//}
		reset(i, isInitial);
	}

	return output;
}

bool Organism::restart(int jointNumber, bool isInitial) {
	bool output;

	output = false;
	if (jointNumber < jointCount) {
		jointList[jointNumber].restart(isInitial);
		output = true;
	}

	return output;
}

bool Organism::restart(bool isInitial) {
	bool output;
	
	output = true;
	for (int i = 0; i < jointCount; i++) {
		restart(i, isInitial);
	}

	return output;
}
 
void Organism::transitionLoop() {
	isLoop = true; 
	for (int i = 0; i < jointCount; i++) {
		jointList[i].transitionLoop();
	}
}