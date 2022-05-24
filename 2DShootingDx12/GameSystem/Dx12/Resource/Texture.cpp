#include <DirectXTex.h>
#include "Texture.h"

const LoadFuncMap Texture::loadFunc_{ 
    { TEXT("png"),[](const std::basic_string<TCHAR>& path, DirectX::TexMetadata* data, DirectX::ScratchImage& img) {
    return SUCCEEDED(DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_NONE, data, img));}},
    { TEXT("jpg"),[](const std::basic_string<TCHAR>& path, DirectX::TexMetadata* data, DirectX::ScratchImage& img) {
    return SUCCEEDED(DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_NONE, data, img)); }},
    { TEXT("bmp"),[](const std::basic_string<TCHAR>& path, DirectX::TexMetadata* data, DirectX::ScratchImage& img) {
    return SUCCEEDED(DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_NONE, data, img)); }},
    { TEXT("tga"),[](const std::basic_string<TCHAR>& path, DirectX::TexMetadata* data, DirectX::ScratchImage& img) {
    return SUCCEEDED(DirectX::LoadFromTGAFile(path.c_str(), data, img)); }},
    { TEXT("dds"),[](const std::basic_string<TCHAR>& path, DirectX::TexMetadata* data, DirectX::ScratchImage& img) {
    return SUCCEEDED(DirectX::LoadFromDDSFile(path.c_str(), DirectX::DDS_FLAGS_NONE,data, img)); }},
};

Texture::Texture(const std::basic_string<TCHAR>& path)
{
}

Texture::~Texture()
{
}

bool Texture::CreateView(void)
{
    return false;
}

bool Texture::CreateResource(void)
{
    return false;
}
