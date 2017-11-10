//object.h

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
#include "position.h"
#include "event.h"

//Object Solidness defintions
#define HARD 0     //Objects cause collisions and impede
#define SOFT 1    //Objects cause collisions but don't impede
#define SPECTRAL 2  //Objects don't cause collisions 

using std::string;

class Object {

private:
	int event_count;
	string event_name[MAX_EVENTS];

protected:
	Position pos; //position in game world
	string type; //user defined identification
	int altitude; //level of "depth" for an object

	double x_velocity; //x velocity
	double x_vcountdown; //x velocity countdown

	double y_velocity; //y velocity
	double y_vcountdown; //y velocity countdown

	char sprite; //Character displayed for object

public:
	Object();

	virtual ~Object();

	int addToWorld();

	//Register interest for event
	//Keep track of manager and event
	//Return 0 for success, else -1
	int registerInterest(string event);

	//Unregister interest in an event
	int unregisterInterest(string event);

	//set object type
	void setType(string new_type);
	//get object type
	string getType();

	//set object sprite
	void setSprite(char sp);
	//get object srptie
	char getSprite();

	typedef int Solidness;
	Solidness solidness;  //Aceepts HARD, SOFT, or SPECTRAL

	//return true for SOFT or HARD, else false
	bool isSolid();

	//set object solidness. Return 0 for success, else -1
	int setSolidness(Solidness new_solid);

	//return object solidness
	Solidness getSolidness();

	int getAltitude();
	void setAltitude(int alt);

	//functions to get and set object's x and y velocities
	double getXVelocity();
	void setXVelocity(double xv);
	double getYVelocity();
	void setYVelocity(double yv);

	//Determine spaces to step in worldmanager update
	int velocityStep(double* velocity, double* countdown);
	//get X and Y velocity steps
	int getXVelocityStep();
	int getYVelocityStep();

	//set object position at a new position
	void setPosition(Position new_pos);

	//Event Handler. Return 0 if ignored.
	//1 for everything else
	virtual int eventHandler(Event *p_event);

	//virtual method for drawing object's character
	virtual void draw();

	//get object position
	Position getPosition();

};

#endif
