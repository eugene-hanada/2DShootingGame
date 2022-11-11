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

// ���b�V���N���X
class Mesh
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Mesh(Dx12Wrapper& dx12,const Math::Vector2& size);
	
	/// <summary>
	/// ���_�̃Z�b�g
	/// </summary>
	/// <param name="vertices"></param>
	/// <returns></returns>
	bool SetVertex(const std::array<Vertex, 4>& vertices);

	/// <summary>
	/// ���_�o�b�t�@�r���[�̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns> ���_�o�b�t�@�r���[ </returns>
	const D3D12_VERTEX_BUFFER_VIEW& GetVertexBufferView(void) const { return *vbView_; }

	/// <summary>
	/// ���_�̐����擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const size_t GetVertexSize(void) const { return vertices_.size(); }
private:
	
	/// <summary>
	/// ���_�̍쐬
	/// </summary>
	/// <param name="dx12"></param>
	/// <returns></returns>
	bool CreateVertex(Dx12Wrapper& dx12);

	// ���_���
	std::array<Vertex,4> vertices_;

	// ���_���̃��\�[�X
	ComPtr<ID3D12Resource> vResource_;

	// �o�b�t�@�[�r���[
	std::unique_ptr<D3D12_VERTEX_BUFFER_VIEW> vbView_{ nullptr };


};

