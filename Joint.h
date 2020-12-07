/*
 * File: Joint.h
 * Date: November 22, 2020
 * Author: Stewart Nash
 * Description: This class contains the information for a joint.
 */
 
 #include "JointVelocity.h"
  
 #ifndef JOINT_H
 #define JOINT_H
	
const int MAXIMUM_SEQUENCE = 10;
	
class Joint {
	//bool isEnd;
	bool isLoop;
	int internalClock; // Counts increments of time
	int externalClock; // Counts number of ticks
	int initialCounter;
	int loopCounter;
	int *sequenceCounter;
	int sequenceNumber;
	float angle;
	
	public:
		int pin;
		JointVelocity *initialMovements [MAXIMUM_SEQUENCE];
		JointVelocity *loopMovements [MAXIMUM_SEQUENCE];
		//JointVelocity **movements;
		JointVelocity *(*movements)[MAXIMUM_SEQUENCE];
		
		Joint();
		Joint(int pinNumber);
		
		int getMovement(); // Return current desired angle, based on time
		bool popSequence(); // Pop (remove) a movement sequence from the initial or loop stack
		bool popSequence(bool isInitial); // Pop (remove) a movement sequence from the initial or loop stack
		bool pushSequence(JointVelocity input); // Push a movement sequence to either the initial or loop stack
		bool pushSequence(JointVelocity input, bool isInitial); // Push a movement sequence to either the initial or loop stack
		void reset();
		void tickClock();
		void transitionLoop();
};
	
 #endif
