#pragma once
#include <memory>
#include <wrl.h>
#include "../../../common/Math.h"

class Dx12Wrapper;
class CbMatrix;
class MaterialBase;
class Texture;
struct ID3D12Resource;
struct CD3DX12_RECT;
struct CD3DX12_VIEWPORT;
struct ID3D12DescriptorHeap;

// レンダーターゲットのクラス
class RenderTarget
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	RenderTarget(Dx12Wrapper& dx12,const Math::Vector2& size);
	~RenderTarget();

	// 初期化用のカラーをセット
	void SetClearColor(float r, float g, float b, float a)
	{
		color_[0] = r;
		color_[1] = g;
		color_[2] = b;
		color_[3] = a;
	}

	/// <summary>
	/// 描画開始
	/// </summary>
	/// <param name=""></param>
	void DrawBegin(void);

	/// <summary>
	/// 描画終了
	/// </summary>
	/// <param name=""></param>
	void DrawEnd(void);

	/// <summary>
	/// クリア
	/// </summary>
	/// <param name=""></param>
	void Clear(void);

	/// <summary>
	/// マテリアルの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	MaterialBase& GetMaterial(void) { return *material_; }

	/// <summary>
	/// 変換用行列の取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	CbMatrix& GetCbMat(void) { return *cbMat_; }
private:
	
	/// <summary>
	/// レンダーターゲットの作成
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool CreateRenderTarget(void);


	// directXのラップクラス
	Dx12Wrapper& dx12_;

	// レンダーターゲットのサイズ(高さと幅)
	Math::Vector2 size_;

	//// メッシュ
	//std::unique_ptr<Mesh> mesh_;

	// スクリーン状の座標からシェーダ用に変換する行列
	std::unique_ptr<CbMatrix> cbMat_;

	// クリア時のカラー
	float color_[4]{0.0f,0.0f,0.0f,0.0f};

	//// リソース
	//ComPtr<ID3D12Resource> resource_;

	// レンダーターゲット用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> rtDescriptorHeap_;

	// マテリアル
	std::unique_ptr<MaterialBase> material_;

	// テクスチャ
	std::shared_ptr<Texture> texure_;

	// ビューポート
	std::unique_ptr<CD3DX12_VIEWPORT> viewPort_;

	// シザー矩形
	std::unique_ptr<CD3DX12_RECT> scissorRect_;
};

