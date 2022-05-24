#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <string_view>
#include "Dx12Resource.h"

namespace DirectX
{
    struct TexMetadata;
}

namespace DirectX
{
    class ScratchImage;
}

using LoadFunc = std::function<bool(const std::basic_string<TCHAR>& , DirectX::TexMetadata*, DirectX::ScratchImage&)>;
using LoadFuncMap = std::unordered_map < std::basic_string_view<TCHAR>, LoadFunc>;

class Texture :
    public Dx12Resource
{
public:
    Texture(const std::basic_string<TCHAR>& path);
    ~Texture();
private:
    bool CreateView(void) override;
    bool CreateResource(void) override;
    static const LoadFuncMap loadFunc_;
};

