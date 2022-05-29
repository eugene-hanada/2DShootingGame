#include "CbMatrix.h"

CbMatrix::CbMatrix(Dx12Wrapper& dx12) :
	ConstantResource{dx12}
{
	DirectX::XMStoreFloat4x4(&mat_, DirectX::XMMatrixIdentity());
	Update();
}

CbMatrix::~CbMatrix()
{
}
