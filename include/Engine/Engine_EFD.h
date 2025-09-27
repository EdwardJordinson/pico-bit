#ifndef Engine_EFD_H
#define Engine_EFD_H

//Structure information of the Engine/Eddie's Form Data(EFD) file.

#include <inttypes.h>
#include <stdio.h>

typedef struct Engine_Main Engine_Main;
typedef struct Engine_EntityObject Engine_EntityObject;
typedef struct Engine_ObjectManager Engine_ObjectManager;
typedef struct Engine_RenderObject Engine_RenderObject;
typedef struct Engine_GameEntity Engine_GameEntity;
typedef struct Engine_DisplayEntity Engine_DisplayEntity;


typedef struct EFD_Header
{
    char name[4]; 
    uint32_t DumpCount; // Number of files
    uint32_t DataOffset; // Offset of data start

} EFD_Header;

typedef struct EFD_Dump
{
    uint32_t FileOffset;
    uint32_t FileSize;
    uint32_t FileType;
    char Name[16];

} EFD_Dump;

typedef struct EFD_File
{
    FILE* File;
    int DumpCount;
    EFD_Dump* Dumps;

} EFD_File;

typedef enum EFD_ObjectGame
{
    POSITION,
    VELOCITY,
    RENDERID,
    COLLISIONSHAPE,
    RESTITUTION,
    MASS
};


void EFD_WriteFile(int argc, char** argv);
EFD_File* EFD_LoadFile(char* fileName);
EFD_Dump* EFD_LoadDump(EFD_File* efdFile);
uint8_t* EFD_ReadDump(EFD_File* efdFile, EFD_Dump* dumpFile);
void EFD_ParseData(Engine_Main* engine, char* text);
void EFD_ParseEntity(Engine_ObjectManager* renderManager, char* text);
void EFD_ParseGameEntity(Engine_GameEntity* gameObject, char* text);
void EFD_ParseDisplayEntity(Engine_DisplayEntity* gameObject, char* text);
void EFD_ParseRender(Engine_ObjectManager* renderManager, char* text);
void EFD_ParseRenderShape(Engine_RenderObject* shapeData, char* text);
void EFD_ParseRenderText(Engine_RenderObject* textData, char* text);

#endif //Engine_EFD_H