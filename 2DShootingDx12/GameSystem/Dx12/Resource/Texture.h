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

// �e�N�X�`���N���X
class Texture :
    public Dx12Resource
{
public:
    Texture(Dx12Wrapper& dx12, const std::basic_string<TCHAR>& path);
    Texture(Dx12Wrapper& dx12, ComPtr<ID3D12Resource>& resource);
    ~Texture();

    /// <summary>
    /// �T�C�Y�̎擾
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const Math::Vector2& GetSize(void) const noexcept { return size_; }
private:

    /// <summary>
    /// �r���[�̍쐬
    /// </summary>
    /// <param name="dx12"></param>
    /// <returns></returns>
    bool CreateView(Dx12Wrapper& dx12) override;

    /// <summary>
    /// ���\�[�X�̍쐬
    /// </summary>
    /// <param name="dx12"></param>
    /// <param name="resourceDesc"></param>
    /// <returns></returns>
    bool CreateResource(Dx12Wrapper& dx12,D3D12_RESOURCE_DESC& resourceDesc) override;

    // ���[�h�p�֐�
    static const LoadFuncMap loadFunc_;

    // �T�C�Y
    Math::Vector2 size_;

    // �摜
    std::unique_ptr<DirectX::ScratchImage> img_;
};

