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

// １枚のテクスチャから描画する用のクラス
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
	
	// DirectX12のラッパークラス
	Dx12Wrapper& dx12_;

	// パイプライン
	ComPtr<ID3D12PipelineState> pipeline_{ nullptr };


	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature_{ nullptr };

	// 頂点
	struct Vertex
	{
		Math::Vector2 pos;		// 座標
		Math::Vector2 uv;		// uv
		std::uint32_t no = 0u;	// 使用する行列の番号
	};

	// 頂点
	std::vector<Vertex> vertices_;

	// マップされたアドレス
	Vertex* vertMap_;

	// 頂点ビュー
	std::unique_ptr<D3D12_VERTEX_BUFFER_VIEW> vbView_;

	// 頂点のリソース
	ComPtr<ID3D12Resource> vb_;

	// インデックス
	std::vector<std::uint16_t> idices_;

	// マップされたアドレス
	std::uint16_t* idMap_;

	// インデックスビュー
	std::unique_ptr<D3D12_INDEX_BUFFER_VIEW> ibView_;

	// インデックスのリソース
	ComPtr<ID3D12Resource> ib_;
	
	// 行列
	std::unique_ptr<CbMatrices> mat_;

	// 画像のキー
	std::string imgKey_;

	// テクスチャのデータ
	std::shared_ptr<TextureData> texData_;

	// 最大数
	const std::uint32_t maxNum_;

	// 現在の描画数
	std::uint32_t nowNum_;
};

