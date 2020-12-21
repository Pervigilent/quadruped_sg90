#ifndef MESSAGING_H
#define MESSAGING_H
/*
 * File: Messaging.h
 * Author: Stewart Nash
 * Date: December 7, 2020
 * Description: This file is intended to coordinate the i2c communications between
 * Arduinos and themselves or the Raspberry Pi 
 */


/*
 * Message Packet: (5 bytes)
 * [instruction, start, stop, duration, timing] = [1 byte, 1 byte, 1 byte, 1 byte, 1 byte]
 * INSTRUCTIONS:
 *
 * 1-16) PUSH INITIAL sequence for joints 1 to 16
 * 17-32) PUSH LOOP sequence for joints 1 to 16
 * 33-48) POP INITIAL sequence from joints 1 to 16
 * 49-64) POP LOOP sequence from joints 1 to 16
 * 65-80) CLEAR INITIAL sequence of joints 1 to 16
 * 81-96) CLEAR LOOP sequence of joint 1 to 16
 * 97-112) RESET INITIAL sequence of joints 1 to 16
 * 113-128) RESET LOOP sequence of joints 1 to 16
 * 129-144) RESTART INITIAL sequence of joints 1 to 16
 * 145-160) RESTART LOOP sequence of joints 1 to 16
 * 161) PUSH ALL INITIAL
 * 162) PUSH ALL LOOP
 * 163) POP ALL INITIAL
 * 164) POP ALL LOOP
 * 165) CLEAR ALL INITIAL
 * 166) CLEAR ALL LOOP
 * 167) RESET ALL INITIAL
 * 168) RESET ALL LOOP
 * 169) RESTART ALL INITIAL
 * 170) RESTART ALL LOOP
 *
 * -->8 joint version<--
 *
 * 1-8) PUSH INITIAL sequence for joints 1 to 8
 * 9-16) PUSH LOOP sequence for joints 1 to 8
 * 17-24) POP INITIAL sequence from joints 1 to 8
 * 25-32) POP LOOP sequence from joints 1 to 8
 * 33-40) CLEAR INITIAL sequence of joints 1 to 8
 * 41-48) CLEAR LOOP sequence of joint 1 to 8
 * 49-56) RESET INITIAL sequence of joints 1 to 8
 * 57-64) RESET LOOP sequence of joints 1 to 8
 * 65-72) RESTART INITIAL sequence of joints 1 to 8
 * 73-80) RESTART LOOP sequence of joints 1 to 8
 *
 * PUSH - Push a sequence onto the queue
 * POP - Pop a sequence from the queue
 * CLEAR - Clear all sequences from the queue and reset the counter
 * RESET - TBD
 * RESTART - Restart counter to 0 and start sequence
 */
#include "Organism.h"

//const int NUMBER_OF_JOINTS = MAXIMUM_JOINTS;
const int NUMBER_OF_JOINTS = 16;

enum message_codes {
	RESTART_LOOP = NUMBER_OF_JOINTS * 10,
	PUSH_ALL_INITIAL,
	PUSH_ALL_LOOP,
	POP_ALL_INITIAL,
	POP_ALL_LOOP,
	CLEAR_ALL_INITIAL,
	CLEAR_ALL_LOOP,
	RESET_ALL_INITIAL,
	RESET_ALL_LOOP,
	RESTART_ALL_INITIAL,
	RESTART_ALL_LOOP
};

void receiveEvent(int count) {

}

void translateMessage(int code,
	int start,
	int stop,
	int duration,
	int ticks,
	Organism &myOrganism) {
	int jointNumber;

	if (code > RESTART_LOOP) {
		jointNumber = code % 16;

	} else {
		switch (code) {
		case PUSH_ALL_INITIAL:
			//TODO: Create JointVelocity from inputs
			break;
		case PUSH_ALL_LOOP:
			//TODO: Create JointVelocity from inputs
			break;
		case POP_ALL_INITIAL:
			myOrganism.popSequence(true);
			break;
		case POP_ALL_LOOP:
			myOrganism.popSequence(false);
			break;
		case CLEAR_ALL_INITIAL:
			myOrganism.clear(true);
			break;
		case CLEAR_ALL_LOOP:
			myOrganism.clear(false);
			break;
		case RESET_ALL_INITIAL:
			myOrganism.reset(true);
			break;
		case RESET_ALL_LOOP:
			myOrganism.reset(false);
			break;
		case RESTART_ALL_INITIAL:
			myOrganism.restart(true);
			break;
		case RESTART_ALL_LOOP:
			myOrganism.restart(false);
			break;
		}
	}
}

#endif // !MESSAGING_H

