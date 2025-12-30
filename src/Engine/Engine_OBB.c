#include <Engine/Engine_CollisionShape.h>
#include <Engine/Engine_Physics.h>
#include <math.h>




Engine_OBB OBB_Initialise()
{
    return (Engine_OBB){Vector2_Initialise()};
};

void OBB_SetDefault(Engine_OBB* obb)
{
    obb->sizeVector = (Vector2){0.0f,0.0f};
};

void OBB_SetConfiguration(Engine_OBB* obb, Engine_OBB configOBB)
{
    *obb = configOBB;
};

void OBB_SetWidthHeight(Engine_OBB* obb, float width, float height)
{
    //Vector2_SetVector(&obb->sizeVector,
    //    Vector2_AddVector(obb->sizeVector, (Vector2){width,height}));
    obb->sizeVector.x = width;
    obb->sizeVector.y = height;
};

void OBB_SetTransform(union CollisionData* srcOBB, Engine_Matrix3x2 bodyTransform)
{
    Vector2 newBody = Vector2_MultiplyMatrix2x2(bodyTransform.RotationMatrix, srcOBB->OBB.sizeVector);

    OBB_SetWidthHeight(&srcOBB->OBB, newBody.x, newBody.y);
};

Engine_OBB OBB_GetPosition(Engine_OBB* obb, Engine_Matrix3x2 bodyTransform)
{
    return (Engine_OBB){Vector2_AddVector(obb->sizeVector, bodyTransform.Position)};
}