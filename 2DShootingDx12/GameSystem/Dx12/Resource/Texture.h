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
    Texture(Dx12Wrapper& dx12, const std::basic_string<TCHAR>& path);
    Texture(Dx12Wrapper& dx12, ComPtr<ID3D12Resource>& resource);
    ~Texture();
private:
    bool CreateView(Dx12Wrapper& dx12) override;
    bool CreateResource(Dx12Wrapper& dx12,D3D12_RESOURCE_DESC& resourceDesc) override;
    static const LoadFuncMap loadFunc_;

    Math::Vector2 size_;
    std::unique_ptr<DirectX::ScratchImage> img_;
};

