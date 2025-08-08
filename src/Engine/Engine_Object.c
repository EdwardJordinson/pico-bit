#include <Engine/Engine_Object.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Physics.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


void Object_Initialise(Engine_Object* object, int id)
{
	object->ObjectID = id;

};