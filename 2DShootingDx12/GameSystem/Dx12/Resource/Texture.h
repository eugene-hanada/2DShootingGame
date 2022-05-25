#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <string_view>
#include "../../../common/Math.h"
#include "Dx12Resource.h"

namespace DirectX
{
    struct TexMetadata;
    class ScratchImage;
    struct Image;
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
    bool CreateResource(D3D12_RESOURCE_DESC& resourceDesc) override;
    static const LoadFuncMap loadFunc_;

    Math::Vector2 size_;
    std::unique_ptr<DirectX::ScratchImage> img_;
};

