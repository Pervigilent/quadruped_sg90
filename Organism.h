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
		Joint jointList [MAXIMUM_JOINTS];
		int jointCount;
		
		bool addJoint(Joint input);
		void incrementTime();
		int getMovement(int jointNumber);
		bool popSequence(int jointNumber, bool isInitial);
		bool pushSequence(int jointNumber, JointVelocity input, bool isInitial);
		//void pushInitialSequence(int jointNumber, JointVelocity input);
		//void pushLoopSequence(int jointNumber, JointVelocity input);
		void transitionLoop();
 }
 
 #endif