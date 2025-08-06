#include <Engine/Engine_EFD.h>
#include <Engine/Engine_Globals.h>
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