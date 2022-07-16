#pragma once
#include <vector>
#include <DirectXMath.h>
#include <wrl.h>
#include <string_view>
#include "../../../common/Math.h"

class Dx12Wrapper;
class CbMatrices;
class TextureData;

struct ID3D12PipelineState;
struct ID3D12RootSignature;
struct D3D12_VERTEX_BUFFER_VIEW;
struct D3D12_INDEX_BUFFER_VIEW;
struct ID3D12Resource;

class TextureSheetRender
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	TextureSheetRender(Dx12Wrapper& dx12, std::shared_ptr< TextureData>& texData, std::uint32_t maxNum);
	virtual ~TextureSheetRender();
	void Draw(const Math::Vector2& pos, std::string_view key);
	void Draw(const Math::Vector2& lt, const Math::Vector2& rt, const Math::Vector2& lb, const Math::Vector2& rb, std::string_view key);
	void Draw(void);
private:

	bool CreateRootSignature(void);
	bool CreatePipeline(void);
	bool CreateVertex(void);
	bool CreateIdx(void);
	
	Dx12Wrapper& dx12_;

	// �p�C�v���C��
	ComPtr<ID3D12PipelineState> pipeline_{ nullptr };


	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature_{ nullptr };

	struct Vertex
	{
		Math::Vector2 pos;
		Math::Vector2 uv;
		std::uint32_t no;
	};

	std::vector<Vertex> vertices_;
	Vertex* vertMap_;
	std::unique_ptr<D3D12_VERTEX_BUFFER_VIEW> vbView_;
	ComPtr< ID3D12Resource> vb_;

	std::vector<std::uint16_t> idices_;
	std::uint16_t* idMap;
	std::unique_ptr< D3D12_INDEX_BUFFER_VIEW> ibView_;
	ComPtr<ID3D12Resource> ib_;
	

	std::unique_ptr<CbMatrices> mat_;

	std::string imgKey_;

	std::shared_ptr< TextureData> texData_;

	const std::uint32_t maxNum_;
	std::uint32_t nowNum_;
};
