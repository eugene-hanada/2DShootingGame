#include <DirectXTex.h>
#include <d3dx12.h>
#include "../../Dx12Wrapper.h"
#include "Texture.h"
#include "../../../common/Debug.h"

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

Texture::Texture(Dx12Wrapper& dx12,const std::basic_string<TCHAR>& path) :
	Dx12Resource{dx12}
{
	std::basic_string_view<TCHAR> ext(path);
	
	ext = ext.substr(ext.find_last_of(TEXT(".")) + 1);
	if (!loadFunc_.contains(ext))
	{
		DebugLog("�g���q���s���ł��Bbmp�Ƃ��ēǂݍ��݂܂�");
		ext = TEXT("bmp");
	}

	// �e�N�X�`���ǂݍ���
	DirectX::TexMetadata metadate{};
	img_ = std::make_unique<DirectX::ScratchImage>();
	if (!loadFunc_.at(ext)(path, &metadate, *img_))
	{
		resource_ = nullptr;
		return;
	}

	D3D12_RESOURCE_DESC resDesc{
		CD3DX12_RESOURCE_DESC::Tex2D(
			metadate.format,
			static_cast<std::uint16_t>(metadate.width),
			static_cast<std::uint16_t>(metadate.height),
			static_cast<std::uint16_t>(metadate.arraySize),
			static_cast<std::uint16_t>(metadate.mipLevels))
	};

	size_.x = static_cast<float>(metadate.width);
	size_.y = static_cast<float>(metadate.height);

	if (!CreateResource(dx12,resDesc))
	{
		DebugLog("�e�N�X�`���̍쐬�Ɏ��s���܂���");
		return;
	}

	if (!CreateDescriptorHeap(dx12))
	{
		DebugLog("�f�B�X�N���v�^�q�[�v�̐����Ɏ��s���܂���");
	}

	if (!CreateView(dx12))
	{
		DebugLog("�r���[�̐����Ɏ��s���܂���");
	}

}

Texture::Texture(Dx12Wrapper& dx12, ComPtr<ID3D12Resource>& resource) :
	Dx12Resource{dx12}
{
	resource_ = resource;
	if (!CreateDescriptorHeap(dx12))
	{
		return;
	}

	if (!CreateView(dx12))
	{
		DebugLog("�r���[�̐����Ɏ��s���܂���");
	}

}

Texture::~Texture()
{
}

bool Texture::CreateView(Dx12Wrapper& dx12)
{
	// �e�N�X�`���r���[�̐ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = resource_->GetDesc().Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;		// 2d�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;
	dx12.Device()->CreateShaderResourceView(resource_.Get(), &srvDesc, descriptorHeap_->GetCPUDescriptorHandleForHeapStart());
	return true;
}

bool Texture::CreateResource(Dx12Wrapper& dx12,D3D12_RESOURCE_DESC& resourceDesc)
{
	D3D12_HEAP_PROPERTIES texHeapProp{ CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0) };

	// ���\�[�X����
	if (FAILED(dx12.Device()->CreateCommittedResource(
		&texHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		nullptr,
		IID_PPV_ARGS(resource_.ReleaseAndGetAddressOf()))))
	{
		DebugLog("���\�[�X�����Ɏ��s");
		return false;
	}

	

	// 
	auto image = img_->GetImage(0,0,0);
	if (FAILED(resource_->WriteToSubresource(
		0,
		nullptr,
		image->pixels,
		static_cast<std::uint16_t>(image->rowPitch),
		static_cast<std::uint16_t>(image->slicePitch)
	)))
	{
		DebugLog("�e�N�X�`���̏������݂Ɏ��s���܂���");
		return false;
	}


	return true;
}
