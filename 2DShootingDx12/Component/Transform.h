#pragma once
#include "../GameSystem/Dx12/Resource/CbMatrix.h"
#include "../common/Math.h"
class Transform :
    public CbMatrix
{
public:
    Transform(Dx12Wrapper& dx12);
    ~Transform();
   void SetPos(const Math::Vector2& pos);
   void SetPos(const Math::Vector2& pos, float angle, const Math::Vector2& scale);
   const Math::Vector2 GetPos(void);
};

