#pragma once
#include <DirectXMath.h>
#include <vector>
#include "ConstantResource.h"

// 行列の複数版の定数バッファクラス
class CbMatrices :
	public ConstantResource<DirectX::XMFLOAT4X4>
{
public:
	CbMatrices(Dx12Wrapper& dx12, size_t num);

	void Update(void) override;

	// 行列の配列
	std::vector<DirectX::XMFLOAT4X4> matrices_;
private:
};

