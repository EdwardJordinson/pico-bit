#include <Engine/Engine_EFD.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_EntityObject.h>
#include <Engine/Engine_RenderObject.h>
#include <Engine/Engine_Coordinates.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_DUMPS 128

//Utter crap, needs rebuild, 
//Proper tree parsing
//Needs its own code folder
//Render objects need seperation from eachother, like with entities


void EFD_WriteFile(int argc, char** argv)
{
    //printf("%d",argc);
    if (argc < 3)
    {
        printf("Not Enough files provides for creation.\n");
        return;
    }

    char* outputFile = argv[1];
    int dumpCount = 1;
    EFD_Dump dumps[MAX_DUMPS];
    FILE* out = fopen(outputFile, "wb");

    EFD_Header header = {{'E','F','D','T'}, dumpCount, 0};
    fwrite(&header, sizeof(EFD_Header), 1, out);
    
    
    //Copying file
    char* fileName = argv[2];
    FILE* dumpFile = fopen(fileName, "rb");
    if (!dumpFile)
    {
        printf("Could not open input file %s\n", fileName);
        fclose(out);
        return;
    }

    fseek(dumpFile, 0, SEEK_END);
    int size = ftell(dumpFile);
    fseek(dumpFile, 0, SEEK_SET);

    dumps[0].FileOffset = ftell(out);
    dumps[0].FileSize = size;
    strncpy(dumps[0].Name, outputFile, 15);
    dumps[0].Name[15] = '\0';
    
    char* buffer = malloc(size);
    fread(buffer, 1, size, dumpFile);
    fwrite(buffer, 1, size, out);
    free(buffer);
    fclose(dumpFile);

    // Write lump directory
    header.DataOffset = ftell(out);
    for (int i = 0; i < dumpCount; ++i) {
        fwrite(&dumps[i], sizeof(EFD_Dump), 1, out);
    }

    // Rewrite header
    fseek(out, 0, SEEK_SET);
    fwrite(&header, sizeof(EFD_Header), 1, out);

    fclose(out);
    printf("EFD written to '%s'\n", outputFile);
    return;
};

EFD_File* EFD_LoadFile(char* fileName)
{
    FILE* file = fopen(fileName, "rb");
    if (!file) return NULL;

    EFD_Header header;
    fread(&header, sizeof(EFD_Header), 1, file);

    if (strncmp(header.name, "EFDT", 4) != 0) {
        fclose(file);
        return NULL;
    }

    EFD_Dump* dumps = malloc(sizeof(EFD_Dump) * header.DumpCount);
    fseek(file, header.DataOffset, SEEK_SET);
    fread(dumps, sizeof(EFD_Dump), header.DumpCount, file);

    EFD_File* efd = malloc(sizeof(EFD_File));
    efd->File = file;
    efd->DumpCount = header.DumpCount;
    efd->Dumps = dumps;
    return efd;
};

EFD_Dump* EFD_LoadDump(EFD_File* efdFile)
{

};

uint8_t* EFD_ReadDump(EFD_File* efdFile, EFD_Dump* dumpFile)
{
    uint8_t* buffer = malloc(dumpFile->FileSize);
    fseek(efdFile->File, dumpFile->FileOffset, SEEK_SET);
    fread(buffer, 1, dumpFile->FileSize, efdFile->File);
    return buffer;
};

void EFD_ParseData(Engine_Main* engine, char* text)
{

};

void EFD_ParseEntity(Engine_ObjectManager* gameManager, char* text)
{
    Engine_EntityObject* newEntityObject = ObjectManager_Allocate(gameManager)->Data;

    if (strncmp(text + 7, "Game", 4) == 0) //Change to rigid body at some point
    {
        newEntityObject->EntityType = 1;
        EFD_ParseGameEntity(&newEntityObject->Data.GameEntity, text);
    }
    else if (strncmp(text + 7, "Display", 7) == 0) //Create render pipeline for these objects in renderstate
    {
        newEntityObject->EntityType = 2;
        EFD_ParseDisplayEntity(&newEntityObject->Data.DisplayEntity, text);
    }
};

void EFD_ParseGameEntity(Engine_GameEntity* gameEntity, char* text)
{
    GameEntity_SetDefault(gameEntity);
    char* savePointer;
    char lineCopy[1024];
    strncpy(lineCopy, text, sizeof(lineCopy));
    lineCopy[sizeof(lineCopy) - 1] = '\0';

    char* token = strtok_r(lineCopy, ",", &savePointer);
    while (token)
    {
        if (strncmp(token + 7 + 5, "Position", 8) == 0)
        {
            float tempX = 0.0; float tempY = 0.0;
            sscanf(token + 8  + 7  + 5, "{%f|%f}", &tempX, &tempY);
            GameEntity_SetPositionXY(gameEntity, tempX, tempY);
        }
        if (strncmp(token, "Rotation", 8) == 0)
        {
            float tempRot = 0.0;
            sscanf(token + 8, "{%f}", &tempRot);
            GameEntity_SetRotationRad(gameEntity, tempRot);
        }
        else if (strncmp(token, "Force", 5) == 0)
        {
            float tempX = 0.0; float tempY = 0.0;
            sscanf(token + 5, "{%f|%f}", &tempX, &tempY);
            Physics_ApplyForce(&gameEntity->PhysicsBody, (Vector2){tempX, tempY});
        }
        else if (strncmp(token, "RenderID", 8) == 0)
        {
            int renderID = 0;
            sscanf(token + 8, "{%d}", &renderID);
            gameEntity->RenderID = renderID;
        }
        else if (strncmp(token, "Restitution", 11) == 0)
        {
            float tempRestitution = 1.0;
            sscanf(token + 11, "{%f}", &tempRestitution);
            gameEntity->PhysicsBody.Material.Restitution = tempRestitution;
        }
        else if (strncmp(token, "Mass", 4) == 0)
        {
            float tempMass = 1.0;
            sscanf(token + 4, "{%f}", &tempMass);
            GameEntity_SetMass(gameEntity, tempMass);
        }
        else if (strncmp(token, "CollisionShape", 14) == 0)
        {
           EFD_ParseCollisionShape(&gameEntity->PhysicsBody.CollisionShape, token, gameEntity->PhysicsBody.Transform2D);
        }
        token = strtok_r(NULL, ",", &savePointer);
    }     
};

void EFD_ParseCollisionShape(Engine_CollisionShape* collisionShape, char* text, Engine_Matrix3x2 transform)
{
    char* savePointer;
    char lineCopy[1024];
    strncpy(lineCopy, text, sizeof(lineCopy));
    lineCopy[sizeof(lineCopy) - 1] = '\0';

    char* token = strtok_r(lineCopy, ",", &savePointer);
    while (token)
    {
        if (strncmp(token + 14 + 1, "AABB", 4) == 0)
        {
            CollisionShape_SetShape(collisionShape, 0);
            CollisionShape_SetDefault(collisionShape);
            Engine_AABB *newAABB = collisionShape->GetData(collisionShape);
            Vector2 maxVector = Vector2_Initialise();
            Vector2 minVector = Vector2_Initialise();
            sscanf(token + 14, "{AABB{%f|%f|%f|%f}}", &maxVector.x, &maxVector.y, &minVector.x, &minVector.y);
            //AABB_SetMaxMin(newAABB, transform.Position, transform.Position); //This is awfull, not happy about this. 
            AABB_SetMaxMin(newAABB, maxVector, minVector);
        }
        else if (strncmp(token  + 14 + 1, "OBB", 3) == 0)
        {
            CollisionShape_SetShape(collisionShape, 1);
            CollisionShape_SetDefault(collisionShape);
            Engine_OBB *newOBB = collisionShape->GetData(collisionShape);
            float height = 0.0f;
            float width = 0.0f;
            sscanf(token + 14, "{OBB{%f|%f}}", &width, &height);
            //OBB_SetWidthHeight(newOBB, transform.Position.x, transform.Position.y);
            //Vector2 tempRot = Vector2_MultiplyMatrix2x2(transform.RotationMatrix, (Vector2){width,height});
            OBB_SetWidthHeight(newOBB, width, height);
        }
        else if (strncmp(token  + 14 + 1, "Circle", 6) == 0)
        {
            CollisionShape_SetShape(collisionShape, 2);
            CollisionShape_SetDefault(collisionShape);
            Engine_Circle *newCircle = collisionShape->GetData(collisionShape);
            float tempRadius = 0.0f;
            sscanf(token + 14, "{Circle{%f}}", &tempRadius);
            Circle_SetRadius(newCircle, tempRadius);
        }
        token = strtok_r(NULL, ",", &savePointer);
    }
    
};

void EFD_ParseDisplayEntity(Engine_DisplayEntity* displayEntity, char* text)
{

    char* savePointer;
    char lineCopy[1024];
    strncpy(lineCopy, text, sizeof(lineCopy));
    lineCopy[sizeof(lineCopy) - 1] = '\0';

    char* token = strtok_r(lineCopy, ",", &savePointer);
    while (token)
    {
        if (strncmp(token + 7 + 5, "Position", 8) == 0)
        {
            float tempX = 0.0; float tempY = 0.0;
            sscanf(token + 8  + 7  + 5, "{%f|%f}", &tempX, &tempY);
            displayEntity->Position.x = tempX; displayEntity->Position.y = tempY;
            //EntityObject_SetPositionXY(displayEntity, tempX, tempY);
        }
        else if (strncmp(token, "Width", 5) == 0)
        {
            float tempWidth = 0.0;
            sscanf(token + 5, "{%f}", &tempWidth);
            displayEntity->Width = tempWidth;
        }
        else if (strncmp(token, "Height", 6) == 0)
        {
            float tempHeight = 0.0;
            sscanf(token + 6, "{%f}", &tempHeight);
            displayEntity->Height = tempHeight;
        }
        else if (strncmp(token, "RenderID", 8) == 0)
        {
            int renderID = 0;
            sscanf(token + 8, "{%d}", &renderID);
            displayEntity->RenderID = renderID;
        }
        token = strtok_r(NULL, ",", &savePointer);
    }
};

void EFD_ParseRender(Engine_ObjectManager* renderManager, char* text)
{
    Engine_RenderObject* newRenderObject = ObjectManager_Allocate(renderManager)->Data;

    if (strncmp(text + 7, "Shape", 5) == 0)
    {
        EFD_ParseRenderShape(newRenderObject, text);
    }
    else if (strncmp(text + 7, "Text", 4) == 0)
    {
        newRenderObject->RenderType = 4;
        EFD_ParseRenderText(newRenderObject, text);
    }
};

void EFD_ParseRenderShape(Engine_RenderObject* objectData, char* text)
{
    char* savePointer;
    char lineCopy[1024];
    strncpy(lineCopy, text, sizeof(lineCopy));
    lineCopy[sizeof(lineCopy) - 1] = '\0';

    char* token = strtok_r(lineCopy, ",", &savePointer);
    while (token)
    {
        if (strncmp(token + 7 + 6, "Square", 6) == 0)
        {
            float tempX = 0.0; float tempY = 0.0;
            sscanf(token + 6  + 7, "{%f|%f}", &tempX, &tempY);
            objectData->PositionX = tempX;
            objectData->PositionY = tempY;
            objectData->RenderType = 1;
            EFD_ParseRenderSquare(objectData, text);
        }
        else if (strncmp(token + 7 + 6, "Circle", 6) == 0)
        {
            float tempX = 0.0; float tempY = 0.0;
            sscanf(token + 6  + 7, "{%f|%f}", &tempX, &tempY);
            objectData->PositionX = tempX;
            objectData->PositionY = tempY;
            objectData->RenderType = 2;
            EFD_ParseRenderCircle(objectData, text);
        }
        token = strtok_r(NULL, ",", &savePointer);
    }
};

void EFD_ParseRenderSquare(Engine_RenderObject* shapeData, char* text)
{
    RenderObject_Square *squareData = shapeData->GetData(shapeData);

    char* savePointer;
    char lineCopy[1024];
    strncpy(lineCopy, text, sizeof(lineCopy));
    lineCopy[sizeof(lineCopy) - 1] = '\0';

    char* token = strtok_r(lineCopy, ",", &savePointer);
    while (token)
    {
        if (strncmp(token, "Width", 5) == 0)
        {
            float tempWidth = 0.0;
            sscanf(token + 5, "{%f}", &tempWidth);
            squareData->Width = tempWidth;
        }
        else if (strncmp(token, "Height", 6) == 0)
        {
            float tempHeight = 0.0;
            sscanf(token + 6, "{%f}", &tempHeight);
            squareData->Height = tempHeight;
        }
        else if (strncmp(token, "Colour", 6) == 0)
        {
            int tempRed = 1; int tempGreen = 1; int tempBlue = 1; int tempAlpha = 1;
            sscanf(token + 6, "{%x|%x|%x|%x}", &tempRed, &tempGreen, &tempBlue, &tempAlpha);
            RenderObject_SetColour(shapeData, tempRed, tempBlue, tempGreen, tempAlpha);
        }
    token = strtok_r(NULL, ",", &savePointer);
    }
};

void EFD_ParseRenderCircle(Engine_RenderObject* shapeData, char* text)
{
    RenderObject_Circle *circleData = shapeData->GetData(shapeData);

    char* savePointer;
    char lineCopy[1024];
    strncpy(lineCopy, text, sizeof(lineCopy));
    lineCopy[sizeof(lineCopy) - 1] = '\0';

    char* token = strtok_r(lineCopy, ",", &savePointer);
    while (token)
    {
        if (strncmp(token, "Radius", 6) == 0)
        {
            float tempRadius = 0.0;
            sscanf(token + 6, "{%f}", &tempRadius);
            circleData->Radius = tempRadius;
        }
        else if (strncmp(token, "Colour", 6) == 0)
        {
            int tempRed = 1; int tempGreen = 1; int tempBlue = 1; int tempAlpha = 1;
            sscanf(token + 6, "{%x|%x|%x|%x}", &tempRed, &tempGreen, &tempBlue, &tempAlpha);
            RenderObject_SetColour(shapeData, tempRed, tempBlue, tempGreen, tempAlpha);
        }
    token = strtok_r(NULL, ",", &savePointer);
    }
};

void EFD_ParseRenderText(Engine_RenderObject* objectData, char* text)
{
    RenderObject_Text* textData = objectData->GetData(objectData);
    
    char* savePointer;
    char lineCopy[1024];
    strncpy(lineCopy, text, sizeof(lineCopy));
    lineCopy[sizeof(lineCopy) - 1] = '\0';

    char* token = strtok_r(lineCopy, ",", &savePointer);
    while (token)
    {
        if (strncmp(token + 7 + 5, "Position", 8) == 0)
        {
            float tempX = 0.0; float tempY = 0.0;
            sscanf(token + 8  + 7 + 5, "{%f|%f}", &tempX, &tempY);
            objectData->PositionX = tempX;
            objectData->PositionY = tempY;
        }
        else if (strncmp(token, "Width", 5) == 0)
        {
            float tempWidth = 0.0;
            sscanf(token + 5, "{%f}", &tempWidth);
            textData->Width = tempWidth;
        }
        else if (strncmp(token, "Height", 6) == 0)
        {
            float tempHeight = 0.0;
            sscanf(token + 6, "{%f}", &tempHeight);
            textData->Height = tempHeight;
        }
        else if (strncmp(token, "Text", 4) == 0)
        {
            char tempCharArray[32] = {0};
            sscanf(token + 4, "{%31s}", tempCharArray);
            strncpy(textData->Text, tempCharArray, sizeof(tempCharArray));
        }
        else if (strncmp(token, "Colour", 6) == 0)
        {
            int tempRed = 1; int tempGreen = 1; int tempBlue = 1; int tempAlpha = 1;
            sscanf(token + 6, "{%x|%x|%x|%x}", &tempRed, &tempGreen, &tempBlue, &tempAlpha);
            RenderObject_SetColour(objectData, tempRed, tempBlue, tempGreen, tempAlpha);
        }
        token = strtok_r(NULL, ",", &savePointer);
    }
};