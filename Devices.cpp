#include "Devices.h"

void Sensor::print() const
{
	cout << "The name of this device is " << name << endl;
}

Sensor::~Sensor()
{ }

string Sensor::getName() const
{
	return name;
}

void Actuator::print() const
{
	cout << "The name of this device is " << name << endl;
}

Actuator::~Actuator()
{ }

string Actuator::getName() const
{
	return name;
}

Thermostat::Thermostat(double temp, string n)
	:Sensor(n), Actuator(n)
{
	currentTemp = temp;
	systemOn = false;
}

double Thermostat::readValue()
{
	return currentTemp;
}

void Thermostat::activate()
{
	systemOn = true;
}

void Thermostat::deactivate()
{
	systemOn = false;
}

void Thermostat::print() const
{ 
	Sensor::print();
	cout << "Th device is a thermostat." << endl;
	cout << "The current temperature is " << currentTemp << endl;
	cout << "System on: ";
	if (systemOn)
		cout << "Yes." << endl;
	else
		cout << "No." << endl;
}

SecurityCamera::SecurityCamera(double mLevel, string name)
	:Sensor(name)
{
	if (mLevel > 100 || mLevel < 0)
	{
		motionLevel = 0;
	}
	else
	{
		motionLevel = mLevel;
	}
}

double SecurityCamera::readValue()
{
	return motionLevel;
}

void SecurityCamera::print() const
{
	Sensor::print();
	cout << "This device is a security camera." << endl;
	cout << "The motion level is " << motionLevel << endl;
}

void SmartLight::activate()
{
	isOn = true;
}

void SmartLight::deactivate()
{
	isOn = false;
}

void SmartLight::print() const
{
	Actuator::print();

	cout << "This device is a smart light." << endl;
	cout << "The open status is ";

	if (isOn)
	{
		cout << "On." << endl;
	}
	else
	{
		cout << "Off. " << endl;
	}
}
