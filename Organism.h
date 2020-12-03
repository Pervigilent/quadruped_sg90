/*
 * File: Organism.h
 * Date: November 22, 2020
 * Author: Stewart Nash
 * Description: This class holds both the joint configurations and the
 *	sequence of movements for the entire robot.
 */
 #include "Joint.h" 
 #include "JointVelocity.h"
 
 #ifndef ORGANISM_H
 #define ORGANISM_H
 
 const int MAXIMUM_JOINTS = 8;
 
 class Organism {
	 bool isLoop;
	 
	 public:
		Organism();
		Joint jointList[MAXIMUM_JOINTS];
		int jointCount;
		
		bool addJoint(Joint input);
		bool insertJoint(Joint input, int count); // To check joint numbering. Change approach.
		bool replaceJoint(Joint input, int location);
		void incrementTime();
		int getMovement(int jointNumber);
		bool popSequence(int jointNumber, bool isInitial);
		bool pushSequence(int jointNumber, JointVelocity input, bool isInitial);
		void transitionLoop();
 };
 
 #endif