#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include <memory>
#include <array>
#include "../../../common/Math.h"

struct Vertex
{
	DirectX::XMFLOAT2 pos;
	DirectX::XMFLOAT2 uv;
};

class Dx12Wrapper;

struct ID3D12Resource;
struct D3D12_VERTEX_BUFFER_VIEW;

class Mesh
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Mesh(Dx12Wrapper& dx12,const Math::Vector2& size);
	
	bool SetVertex(const std::array<Vertex, 4>& vertices);

	const D3D12_VERTEX_BUFFER_VIEW& GetVertexBufferView(void) const { return *vbView_; }

	const size_t GetVertexSize(void) const { return vertices_.size(); }
private:
	
	bool CreateVertex(Dx12Wrapper& dx12);

	// 頂点情報
	std::array<Vertex,4> vertices_;

	// 頂点情報のリソース
	ComPtr<ID3D12Resource> vResource_;

	// バッファービュー
	std::unique_ptr<D3D12_VERTEX_BUFFER_VIEW> vbView_{ nullptr };


};

