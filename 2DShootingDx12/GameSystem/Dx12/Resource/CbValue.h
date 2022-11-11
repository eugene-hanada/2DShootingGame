#pragma once
#include "ConstantResource.h"

template<class T>
concept CbValueC = std::integral<T> || std::floating_point<T>;

// �萔�o�b�t�@�p�̊��N���X
template<CbValueC T>
class CbValue :
    public ConstantResource<T>
{
public:
    CbValue(Dx12Wrapper& dx12);
    ~CbValue();
    void Update(void) final { (*this->mapped_) = val_; }
    T val_{};
};

template<CbValueC T>
inline CbValue<T>::CbValue(Dx12Wrapper& dx12) :
    ConstantResource<T>{dx12}
{
}

template<CbValueC T>
inline CbValue<T>::~CbValue()
{
}
