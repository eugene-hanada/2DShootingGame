#pragma once
#include <DirectXMath.h>
#include "ConstantResource.h"

// 行列の定数バッファ
class CbMatrix :
    public ConstantResource<DirectX::XMFLOAT4X4>
{
public:
    CbMatrix(Dx12Wrapper& dx12);
    virtual ~CbMatrix();

    // 行列
    DirectX::XMFLOAT4X4 mat_;

    void Update(void) override { *mapped_ = mat_; }
};

