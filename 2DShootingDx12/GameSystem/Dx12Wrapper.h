#pragma once
#include <vector>
#include <wrl.h>
#include <memory>

struct ID3D12Device;
struct IDXGIFactory6;
struct IDXGISwapChain4;
struct ID3D12CommandAllocator;
struct ID3D12GraphicsCommandList;
struct ID3D12CommandQueue;
struct ID3D12Resource;
struct ID3D12Fence;
struct ID3D12DescriptorHeap;
struct CD3DX12_VIEWPORT;
struct CD3DX12_RECT;

class Window;
class CbMatrix;

// directX12のラップクラス
class Dx12Wrapper
{
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Dx12Wrapper(Window& wnd);
	~Dx12Wrapper();

	/// <summary>
	/// 最後のレンダーターゲットに描画開始する
	/// </summary>
	/// <param name=""></param>
	void BeginFinalRenderTarget(void);

	/// <summary>
	/// 最後のレンダーターゲットの描画処理を終了する
	/// </summary>
	/// <param name=""></param>
	void EndFinalRenderTarget(void);

	/// <summary>
	/// 最後のレンダーターゲットを描画する
	/// </summary>
	/// <param name=""></param>
	void DrawFinalRenderTarget(void);

	// クリアカラーをセットする
	void SetClearRenderTarget(float r, float g, float b, float a)
	{
		clearColor_[0] = r;
		clearColor_[1] = g;
		clearColor_[2] = b;
		clearColor_[3] = a;
	}

	/// <summary>
	/// デバイスの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	ComPtr<ID3D12Device>& Device(void)
	{
		return device_;
	}

	/// <summary>
	/// コマンドリストの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	ComPtr<ID3D12GraphicsCommandList>& CmdLlist(void)
	{
		return cmdList_;
	}

	/// <summary>
	/// 行列の取得
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	CbMatrix& GetCbMat(void) { return *cbMat_; }

private:

	/// <summary>
	/// デバイスの生成
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool CreateDXGIDevice(void);

	/// <summary>
	/// コマンド類の生成
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool CreateCommand(void);

	/// <summary>
	/// スワップチェインの生成
	/// </summary>
	/// <param name="wnd"></param>
	/// <returns></returns>
	bool CreateSwapChain(Window& wnd);

	/// <summary>
	/// レンダーターゲットの生成
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool CreateFinalRenderTarget(void);

	// デバイス
	ComPtr<ID3D12Device> device_{ nullptr };

	// コマンドアロケーター
	ComPtr<ID3D12CommandAllocator> cmdAllocator_{ nullptr };

	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> cmdList_{ nullptr };

	// コマンドキュー
	ComPtr<ID3D12CommandQueue> cmdQueue_{ nullptr };

	// DXGI周り----------------------------------------
	// DXGIファクトリー
	ComPtr<IDXGIFactory6> dxgiFactory_{ nullptr };

	// スワップチェイン
	ComPtr<IDXGISwapChain4> swapChain_{ nullptr };

	// 表示関連のバッファ周り----------------------
	// バックバッファ
	std::vector<ComPtr<ID3D12Resource>> backBuffers_;

	// レンダーターゲット用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> rtvHeap_{ nullptr };

	// フェンスの値
	std::uint64_t fenceVal_{ 0 };
	
	// フェンス
	ComPtr<ID3D12Fence> fence_{ nullptr };

	// ビューポート
	std::unique_ptr<CD3DX12_VIEWPORT> viewPort_;

	// シザー矩形
	std::unique_ptr< CD3DX12_RECT> scissorRect_;

	// クリアカラー
	float clearColor_[4];

	// 行列
	std::unique_ptr<CbMatrix> cbMat_;
};

