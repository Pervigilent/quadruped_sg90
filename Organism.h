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
		bool clear(int jointNumber, bool isInitial);
		bool clear(bool isInitial);
		int getMovement(int jointNumber);
		void incrementTime();
		void incrementTime(int jointNumber);
		bool insertJoint(Joint input, int count); // To check joint numbering. Change approach.
		bool popSequence(int jointNumber, bool isInitial);
		bool popSequence(bool isInitial); // Pop a sequence from each joint
		bool pushSequence(int jointNumber, JointVelocity input, bool isInitial);
		bool replaceJoint(Joint input, int location);
		bool reset(int jointNumber, bool isInitial);
		bool reset(bool isInitial);
		bool restart(int jointNumber, bool isInitial);
		bool restart(bool isInitial); // Restart sequence from sequence number 0
		void transitionLoop();
 };
 
 #endif