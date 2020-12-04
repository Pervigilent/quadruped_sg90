/*
 * Description: Accompaniment stand-in for Servo.h in absence of
 *		Arduino libraries.
 */
#include "Servo.h"
#include <iostream>

int Servo::servo_count = 0;

Servo::Servo() {
	servo_number = servo_count++;
}

uint8_t Servo::attach(int pin) {
	uint8_t output;

	output = pin;
	std::cout << "[INFO Servo::attach(int pin)]: Attach pin, " << pin;
	std::cout << ", Servo, " << servo_number << "." << std::endl;

	return output;
}

uint8_t Servo::attach(int pin, int min, int max) {
	uint8_t output;

	output = pin;
	std::cout << "[INFO Servo::attach(int pin)]: Attach pin, " << pin;
	std::cout << ", min, " << min << ", max, " << max;
	std::cout << ", Servo, " << servo_number << "." << std::endl;

	return output;
}

void Servo::detach() {
	std::cout << "[INFO Servo::detach(int pin)]: ";
	std::cout << ", Servo, " << servo_number << "." << std::endl;
}

void Servo::write(int value) {
	std::cout << "[INFO Servo::write(int value)]: Write value, " << value;
	std::cout << ", Servo, " << servo_number << "." << std::endl;
}

void Servo::writeMicroseconds(int value) {
	std::cout << "[INFO Servo::writeMicroseconds(int value)]: Write value, " << value;
	std::cout << ", Servo, " << servo_number << "." << std::endl;
}

int Servo::read() {
	int output;

	output = 0;
	std::cout << "[INFO Servo::read()]: ";
	std::cout << ", Servo, " << servo_number << "." << std::endl;

	return output;
}

int Servo::readMicroseconds() {
	int output;

	output = 0;
	std::cout << "[INFO Servo::readMicroseconds()]: ";
	std::cout << ", Servo, " << servo_number << "." << std::endl;

	return output;
}

bool Servo::attached() {
	bool output;

	output = false;
	std::cout << "[INFO Servo::attached()]: ";
	std::cout << ", Servo, " << servo_number << "." << std::endl;

	return output;
}