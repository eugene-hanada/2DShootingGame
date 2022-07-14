#include "CbMatrices.h"

CbMatrices::CbMatrices(Dx12Wrapper& dx12, size_t num) :
	ConstantResource{dx12,num}
{
	matrices_.resize(num);
}

void CbMatrices::Update(void)
{
	std::copy(matrices_.begin(), matrices_.end(), mapped_);
}
