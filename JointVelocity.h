/*
 * File: JointVelocity.h
 * Date: November 22, 2020
 * Author: Stewart Nash
 * Description: This class contains the basic timing and position information
 *	needed in order to dynamically move a joint.
 */
 
 #ifndef JOINTVELOCITY_H
 #define JOINTVELOCITY_H
 
class JointVelocity {
	public:		
		int position; // Position to move the joint to (next position from previous position)
		int spacing; // Number to increment position each cycle (after each pause)
		int duration; // Number of pauses that should elapse before incrementing the joint
		int timing; // Number of timer ticks in each pause
		
		JointVelocity();
		JointVelocity(int myPosition, int mySpacing, int myDuration, int myTiming);
		JointVelocity(const JointVelocity &obj);
};
	
 #endif