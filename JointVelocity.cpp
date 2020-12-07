/*
 * File: JointVelocity.cpp
 * Date: November 23, 2020
 * Author: Stewart Nash
 * Description: (see corresponding header file)
 */

#include "JointVelocity.h"
 
JointVelocity::JointVelocity() {

}

JointVelocity::JointVelocity(int myStart, int myStop, int myDuration, int myMultiplier) {
	start = myStart;
	stop = myStop;
	duration = myDuration;
	multiplier = myMultiplier;
}

JointVelocity::JointVelocity(const JointVelocity &obj) {
	start = obj.start;
	stop = obj.stop;
	duration = obj.duration;
	multiplier = obj.multiplier;
}