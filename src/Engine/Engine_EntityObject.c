#include <Engine/Engine_EntityObject.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Physics.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


Engine_EntityObject EntityObject_Initialise()
{
	return (Engine_EntityObject){
		.EntityType = 0,
		.GetData = EntityObject_GetData
		};
};

void EntityObject_SetDefault(Engine_EntityObject* entityObject)
{
        switch (entityObject->EntityType)
        {
        case 1:
			GameEntity_SetDefault(&entityObject->Data.GameEntity);
            break;
        case 2:
            
            break;
        default:
            break;
        }
};

void EntityObject_SetConfiguration(Engine_EntityObject* entityObject, Engine_EntityObject configObject)
{
	*entityObject = configObject;
};

void* EntityObject_GetData(Engine_EntityObject* entityObject)
{
	switch (entityObject->EntityType)
	{
	case 1:
		return &entityObject->Data.GameEntity;
		break;
	case 2:
		return &entityObject->Data.DisplayEntity;
		break;
	}
};

