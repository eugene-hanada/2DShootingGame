#pragma once
#include <memory>
#include <vector>
#include <DirectXMath.h>
#include <wrl.h>
#include <string>
#include "../../../common/Math.h"

class Dx12Wrapper;
class CbMatrices;
class TextureData;
class CbMatrix;

struct ID3D12PipelineState;
struct ID3D12RootSignature;
struct D3D12_VERTEX_BUFFER_VIEW;
struct D3D12_INDEX_BUFFER_VIEW;
struct ID3D12Resource;

// �P���̃e�N�X�`������`�悷��p�̃N���X
class TextureSheetRender
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	TextureSheetRender(const std::string& imgKey,Dx12Wrapper& dx12, std::shared_ptr< TextureData>& texData, std::uint32_t maxNum);
	~TextureSheetRender();

	void Draw(const Math::Vector2& pos, const std::string& key, float rot = 0.0f,int idx = 0);

	void DrawLT(const Math::Vector2& pos, const std::string& key, int idx = 0);
	void Draw(const Math::Vector2& lt, const Math::Vector2& rt, const Math::Vector2& lb, const Math::Vector2& rb, const std::string& key, int idx = 0);
	void Draw(CbMatrix& cbMat);
	void Update(void);
	const Math::Vector2& GetImgSize(const std::string& key);

	void SetImgKey(const std::string& imgKey)
	{
		imgKey_ = imgKey;
	}
private:

	bool CreateRootSignature(void);
	bool CreatePipeline(void);
	bool CreateVertex(void);
	bool CreateIdx(void);
	
	// DirectX12�̃��b�p�[�N���X
	Dx12Wrapper& dx12_;

	// �p�C�v���C��
	ComPtr<ID3D12PipelineState> pipeline_{ nullptr };


	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature_{ nullptr };

	// ���_
	struct Vertex
	{
		Math::Vector2 pos;		// ���W
		Math::Vector2 uv;		// uv
		std::uint32_t no = 0u;	// �g�p����s��̔ԍ�
	};

	// ���_
	std::vector<Vertex> vertices_;

	// �}�b�v���ꂽ�A�h���X
	Vertex* vertMap_;

	// ���_�r���[
	std::unique_ptr<D3D12_VERTEX_BUFFER_VIEW> vbView_;

	// ���_�̃��\�[�X
	ComPtr<ID3D12Resource> vb_;

	// �C���f�b�N�X
	std::vector<std::uint16_t> idices_;

	// �}�b�v���ꂽ�A�h���X
	std::uint16_t* idMap_;

	// �C���f�b�N�X�r���[
	std::unique_ptr<D3D12_INDEX_BUFFER_VIEW> ibView_;

	// �C���f�b�N�X�̃��\�[�X
	ComPtr<ID3D12Resource> ib_;
	
	// �s��
	std::unique_ptr<CbMatrices> mat_;

	// �摜�̃L�[
	std::string imgKey_;

	// �e�N�X�`���̃f�[�^
	std::shared_ptr<TextureData> texData_;

	// �ő吔
	const std::uint32_t maxNum_;

	// ���݂̕`�搔
	std::uint32_t nowNum_;
};

