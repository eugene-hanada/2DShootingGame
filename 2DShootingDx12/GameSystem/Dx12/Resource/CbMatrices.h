#pragma once
#include <DirectXMath.h>
#include <vector>
#include "ConstantResource.h"

class CbMatrices :
    public ConstantResource<DirectX::XMFLOAT4X4>
{
public:
    CbMatrices(Dx12Wrapper& dx12, size_t num);
    void Update(void);
    std::vector<DirectX::XMFLOAT4X4> matrices_;
private:
};

