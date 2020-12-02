/*
 * File: Organism.cpp
 * Date: November 22, 2020
 * Author: Stewart Nash
 * Description: (See corresponding header file.)
 */
 #include "Organism.h"
 
 Organism::Organism() {
	isLoop = false;
 }
 
 /*
int Organism::popInitialMovement(int jointNumber) {
	jointList[jointNumber]->popSequence(true);
}

int Organism::popLoopMovement(int jointNumber) {
	jointList[jointNumber]->popSequence(false);
}
*/

int Organism::getMovement(int jointNumber) {
	return jointList[jointNumber]->getMovement();
}

void Organism::incrementTime() {
	for (int i = 0; i < jointCount; i++) {
		jointList[i]->tickClock();
	}
}

bool Organism::popSequence(int jointNumber, bool isInitial) {
	return jointList[jointNumber]->popSequence(isInitial);
}

bool Organism::pushSequence(int jointNumber, JointVelocity input, bool isInitial) {
	return jointList[jointNumber]->pushSequence(input, isInitial);
}
 
 void Organism::transitionLoop() {
	isLoop = true; 
 }