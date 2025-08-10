#include <Engine/Engine_EFD.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_RenderObject.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_DUMPS 128


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

void EFD_ParseGame(Engine_ObjectManager* renderManager, char* text)
{

};

void EFD_ParseGameObject(Engine_GameObject* gameObject, char* text)
{

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
        EFD_ParseRenderText(newRenderObject, text);
    }
};

void EFD_ParseRenderShape(Engine_RenderObject* objectData, char* text)
{
    RenderObject_Shape* shapeData = &objectData->RenderData.ShapeData;
    objectData->RenderObjectType = 1;

    char* savePointer;
    char lineCopy[1024];
    strncpy(lineCopy, text, sizeof(lineCopy));
    lineCopy[sizeof(lineCopy) - 1] = '\0';

    char* token = strtok_r(lineCopy, ",", &savePointer);
    while (token)
    {
        if (strncmp(token + 7 + 6, "Position", 8) == 0)
        {
            float tempX = 0.0; float tempY = 0.0;
            sscanf(token + 8  + 7, "{%f|%f}", &tempX, &tempY);
            objectData->PositionX = tempX;
            objectData->PositionY = tempY;
        }
        else if (strncmp(token, "Width", 5) == 0)
        {
            float tempWidth = 0.0;
            sscanf(token + 5, "{%f}", &tempWidth);
            shapeData->Width = tempWidth;
        }
        else if (strncmp(token, "Height", 6) == 0)
        {
            float tempHeight = 0.0;
            sscanf(token + 6, "{%f}", &tempHeight);
            shapeData->Height = tempHeight;
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

void EFD_ParseRenderText(Engine_RenderObject* objectData, char* text)
{
    RenderObject_Text* textData = &objectData->RenderData.TextData;
    objectData->RenderObjectType = 2;

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