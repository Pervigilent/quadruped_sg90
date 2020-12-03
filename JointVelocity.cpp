/*
 * File: JointVelocity.cpp
 * Date: November 23, 2020
 * Author: Stewart Nash
 * Description: (see corresponding header file)
 */

#include "JointVelocity.h"
 
JointVelocity::JointVelocity() {

}

JointVelocity::JointVelocity(int myPosition, int mySpacing, int myDuration, int myTiming) {
	position = myPosition;
	spacing = mySpacing;
	duration = myDuration;
	timing = myTiming;
}

JointVelocity::JointVelocity(const JointVelocity &obj) {
		position = obj.position;
		spacing = obj.spacing;
		duration = obj.duration;
		timing = obj.timing;
}