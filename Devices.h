#pragma once
#include <iostream>
using namespace std;
class Sensor
{
protected:
	string name;
public:
	Sensor(string n)
		:name(n) { }
	virtual double readValue() = 0;
	virtual void print() const;
	virtual ~Sensor();
	string getName() const;
};

class Actuator
{
protected:
	string name;
public:
	Actuator(string n)
		:name(n) { }
	virtual void activate() = 0;
	virtual void deactivate() = 0;
	virtual void print() const;
	virtual ~Actuator();
	string getName() const;
};

class Thermostat : public Sensor, public Actuator
{
private:
	double currentTemp;
	bool systemOn;
public:
	Thermostat(double temp, string n);
	double readValue() override;
	void activate() override;
	void deactivate() override;
	void print() const override;
};

class SecurityCamera : public Sensor
{
private:
	double motionLevel;
public:
	SecurityCamera(double mLevel, string name);
	double readValue() override;
	void print() const override;
};

class SmartLight : public Actuator
{
private:
	bool isOn;
public:
	SmartLight(string name)
		:Actuator(name) 
	{
		isOn = false;
	}
	void activate() override;
	void deactivate() override;
	void print() const override;
};
