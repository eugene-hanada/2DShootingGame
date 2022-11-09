#pragma once
#include "ConstantResource.h"

template<class T>
concept CbValueC = std::integral<T> || std::floating_point<T>;

// 定数バッファ用の基底クラス
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
