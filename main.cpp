#include <iostream>
#include "Devices.h"
#include <string>
#include <vector>
using namespace std;

void activateOrDeactivate(vector<Actuator*>& actuatorPtr);
void addDevice(vector<Sensor*>& sensorPtr, vector<Actuator*>& actuatorPtr);
void addThermostat(vector<Sensor*>& sensorPtr, vector<Actuator*>& actuatorPtr);
void addSecurityCamera(vector<Sensor*>& sensorPtr, const vector<Actuator*>& actuatorPtr);
void addSmartLight(const vector<Sensor*>& sensorPtr, vector<Actuator*>& actuatorPtr);
void printAllDevice(const vector<Sensor*>& sensorPtr, const vector<Actuator*>& actuatorPtr);
string checkName(const vector<Sensor*>& sensorPtr, const vector<Actuator*>& actuatorPtr);

int main()
{
	vector<Sensor*> sensorPtr;
	vector<Actuator*> actuatorPtr;
	int choice = 0;

	while (choice != 5)
	{
		cout << "Welcome to the menu." << endl;
		cout << "1. Add a device." << endl;
		cout << "2. View all devices." << endl;
		cout << "3. Read all sensors." << endl;
		cout << "4. Activate or deactivate all actuator." << endl;
		cout << "5. Quit." << endl;
		cout << "Please enter your choice:" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			addDevice(sensorPtr, actuatorPtr);
			cout << endl;
			break;
		case 2:
			printAllDevice(sensorPtr, actuatorPtr);
			cout << endl;
			break;
		case 3:
		{
			for (int i = 0; i < sensorPtr.size();i++)
			{
				cout << sensorPtr[i]->getName() << ": " << sensorPtr[i]->readValue() << endl;
			}
			cout << endl;
			break;
		}
		case 4:
			activateOrDeactivate(actuatorPtr);
			cout << endl;
			break;
		case 5:
			break;
		default:
			cout << "Invalid input! Please enter agnain" << endl;
		}
	}

	for (int i = 0; i < sensorPtr.size(); i++)
	{
		delete sensorPtr[i];
	}

	for (int i = 0; i < actuatorPtr.size(); i++)
	{
		bool alreadyDeleted = false;

		for (int j = 0; j < sensorPtr.size(); j++)
		{
			if (actuatorPtr[i]->getName() == sensorPtr[j]->getName())
			{
				alreadyDeleted = true;
				break;
			}
		}

		if (!alreadyDeleted)
		{
			delete actuatorPtr[i];
		}
	}

	return 0;
}

void addDevice(vector<Sensor*>& sensorPtr, vector<Actuator*>& actuatorPtr)
{
	int deviceChoice;

	cout << "Please enter the device you want to add:" << endl;
	cout << "1. Thermostat." << endl;
	cout << "2. Security Camera." << endl;
	cout << "3. Smart Light." << endl;
	cin >> deviceChoice;

	switch (deviceChoice)
	{
	case 1:
		addThermostat(sensorPtr, actuatorPtr);
		break;
	case 2:
		addSecurityCamera(sensorPtr, actuatorPtr);
		break;
	case 3:
		addSmartLight(sensorPtr, actuatorPtr);
		break;
	default:
		cout << "Invailrd input!" << endl;
	}
}

void addThermostat(vector<Sensor*>& sensorPtr, vector<Actuator*>& actuatorPtr)
{
	string name;
	double temp;

	name = checkName(sensorPtr, actuatorPtr);

	cout << "Enter the current temperature: ";
	cin >> temp;

	Thermostat* ptr = new Thermostat(temp, name);
	sensorPtr.push_back(ptr);
	actuatorPtr.push_back(ptr);
}

string checkName(const vector<Sensor*>& sensorPtr, const vector<Actuator*>& actuatorPtr)
{
	bool isRepeat;
	string name;

	do {
		isRepeat = false;
		cout << "Enter the name of this device: ";
		cin >> name;

		for (int i = 0; i < sensorPtr.size(); i++)
		{
			if (name == sensorPtr[i]->getName())
			{
				isRepeat = true;
				cout << "The name is used! Please enter a new one." << endl;
				break;
			}
		}

		for (int i = 0; i < actuatorPtr.size(); i++)
		{
			if (name == actuatorPtr[i]->getName())
			{
				isRepeat = true;
				cout << "The name is used! Please enter a new one." << endl;
				break;
			}
		}
	} while (isRepeat);

	return name;
}

void addSecurityCamera(vector<Sensor*>& sensorPtr, const vector<Actuator*>& actuatorPtr)
{
	string name;
	double motionLevel;

	name = checkName(sensorPtr, actuatorPtr);

	cout << "Enter the motion level:(between 0 - 100) ";
	cin >> motionLevel;

	SecurityCamera* ptr = new SecurityCamera(motionLevel, name);
	sensorPtr.push_back(ptr);
}

void addSmartLight(const vector<Sensor*>& sensorPtr, vector<Actuator*>& actuatorPtr)
{
	string name;
	
	name = checkName(sensorPtr, actuatorPtr);

	SmartLight* ptr = new SmartLight(name);
	actuatorPtr.push_back(ptr);
}

void printAllDevice(const vector<Sensor*>& sensorPtr, const vector<Actuator*>& actuatorPtr)
{
	for (int i = 0; i < sensorPtr.size();i++)
	{
		cout << "Device NO." << i << " :" << endl;
		sensorPtr[i]->print();
		cout << endl;
	}

	bool alreadyprinted;
	int count = 0;

	for (int i = 0; i < actuatorPtr.size(); i++)
	{
		alreadyprinted = false;

		for (int j = 0; j < sensorPtr.size(); j++)
		{
			if (actuatorPtr[i]->getName() == sensorPtr[j]->getName())
			{
				alreadyprinted = true;
				count++;
				break;
			}
		}

		if (!alreadyprinted)
		{
			cout << "Device NO." << i + sensorPtr.size() - count << " :" << endl;
			actuatorPtr[i]->print();
			cout << endl;
		}
	}
}

void activateOrDeactivate(vector<Actuator*>& actuatorPtr)
{
		int choice;
		string name;
		int ifActivate;
		bool found;

		cout << "Would you like to active or deactive all devices or a single device?" << endl;
		cout << "Please enter 0 for all device, and enter 1 for a single decive." << endl;
		cin >> choice;

		do
		{
			cout << "Would you like to active or deactive?" << endl;
			cout << "Pleasse enter 1 for active, and 0 for deactive" << endl;
			cin >> ifActivate;
			
			if (ifActivate != 0 && ifActivate != 1)
			{
				cout << "Invaild input!" << endl;
			}
		} while (ifActivate != 0 && ifActivate != 1);
	

		switch (choice)
		{
		case 0:
			if (ifActivate == 0)
			{
				for (int i = 0; i < actuatorPtr.size(); i++)
				{
					actuatorPtr[i]->deactivate();
				}
			}
			else
			{
				for (int i = 0; i < actuatorPtr.size(); i++)
				{
					actuatorPtr[i]->activate();
				}
			}
			break;
		case 1:
			cout << "Please enter the name of the device you want to avtive or deactive: " << endl;
			cin >> name;
			found = false;

			for (int i = 0; i < actuatorPtr.size(); i++)
			{
				if (actuatorPtr[i]->getName() == name)
				{
					found = true;
					if (ifActivate == 0)
					{
						actuatorPtr[i]->deactivate();
						cout << "Device successfully deactivated!" << endl;
					}
					else
					{
						actuatorPtr[i]->activate();
						cout << "Device successfully activated!" << endl;
					}
					break;
				}
			}

			if (!found)
				cout << "Device not found!" << endl;

			break;
		default:
			cout << "Invaild input!" << endl;
		}
}
