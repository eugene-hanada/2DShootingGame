#pragma once
#include <DirectXMath.h>
#include <vector>
#include "ConstantResource.h"

// �s��̕����ł̒萔�o�b�t�@�N���X
class CbMatrices :
	public ConstantResource<DirectX::XMFLOAT4X4>
{
public:
	CbMatrices(Dx12Wrapper& dx12, size_t num);

	void Update(void) override;

	// �s��̔z��
	std::vector<DirectX::XMFLOAT4X4> matrices_;
private:
};

