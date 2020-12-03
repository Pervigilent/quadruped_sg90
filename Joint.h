/*
 * File: Joint.h
 * Date: November 22, 2020
 * Author: Stewart Nash
 * Description: This class contains the information for a joint.
 */
 
 #include "JointVelocity.h"
  
 #ifndef JOINT_H
 #define JOINT_H
	
const int MAXIMUM_SEQUENCE = 16;
	
class Joint {
	bool isLoop;
	bool isEnd;
	int internalTimer;
	int sequenceNumber;
	int initialSequenceCounter;
	int loopSequenceCounter;
	int sequenceCounter;
	float angle;
	
	public:
		int pin;
		JointVelocity *initialMovements [MAXIMUM_SEQUENCE];
		JointVelocity *loopMovements [MAXIMUM_SEQUENCE];
		JointVelocity **movements;
		
		Joint();
		Joint(int pinNumber);
		
		int getMovement(); // Return current desired angle, based on time
		bool pushSequence(JointVelocity input, bool isInitial); // Push a movement sequence to either the initial or loop stack
		bool popSequence(bool isInitial); // Pop (remove) a movement sequence from the initial or loop stack
		void reset();
		void tickClock();
		void transitionLoop();
};
	
 #endif