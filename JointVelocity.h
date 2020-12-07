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
		int start; // Start position of the joint
		int stop; // End position of the joint
		int duration; // Amount of time in which the movement should be accomplished
		int multiplier; // Number of ticks in a unit of time
		
		JointVelocity();
		JointVelocity(int myStart, int myStop, int myDuration, int myMultiplier);
		JointVelocity(const JointVelocity &obj);
};
	
 #endif