#pragma once
#include <wrl.h>
struct ID3D12Resource;
struct ID3D12DescriptorHeap;
struct D3D12_RESOURCE_DESC;

class Dx12Wrapper;

// directX12系のリソースの基底クラス
class Dx12Resource
{
protected:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Dx12Resource(Dx12Wrapper& dx12);
	virtual ~Dx12Resource();

	/// <summary>
	/// ディスクリプタヒープを取得
	/// </summary>
	/// <param name=""></param>
	/// <returns> ディスクリプタヒープを取得 </returns>
	ComPtr<ID3D12DescriptorHeap>& DescriptorHeap(void)
	{
		return descriptorHeap_;
	}

	/// <summary>
	/// リソースの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns> リソース </returns>
	ComPtr<ID3D12Resource>& GetResource(void) { return resource_; }

private:
	
	/// <summary>
	/// ビューの作成
	/// </summary>
	/// <param name="dx12"></param>
	/// <returns> 成功時true、失敗時false </returns>
	virtual bool CreateView(Dx12Wrapper& dx12) = 0;

	/// <summary>
	/// リソースの作成
	/// </summary>
	/// <param name="dx12"> directX12のラップクラス </param>
	/// <param name="resourceDesc"> リソースの設定クラス </param>
	/// <returns></returns>
	virtual bool CreateResource(Dx12Wrapper& dx12,D3D12_RESOURCE_DESC&  resourceDesc) = 0;
protected:
	bool CreateDescriptorHeap(Dx12Wrapper& dx12);

	// リソース
	ComPtr<ID3D12Resource> resource_;

	// ディスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descriptorHeap_;
};

