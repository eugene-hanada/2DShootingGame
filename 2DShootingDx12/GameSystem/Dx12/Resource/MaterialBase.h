#pragma once
#include <vector>
#include <memory>
#include "../../../common/Math.h"

class Mesh;
class Dx12Resource;
class Dx12Wrapper;
class CbMatrix;
class Transform;

class MaterialBase
{
	// パラメーターインデックスとリソースをpairにする
public:
	MaterialBase(Dx12Wrapper& dx12,const Math::Vector2& size);
	virtual ~MaterialBase();

	std::shared_ptr<Mesh>& GetMesh(void) { return mesh_; }
	std::shared_ptr<Transform>& GetTransform(void) { return transform_; }
	void SetTransform(const std::shared_ptr<Transform>& transform) { transform_ = transform; }
	const std::vector<std::weak_ptr<Dx12Resource>>& GetShaderResource(void) const { return shaderResource_; }

	// shaderに渡す用のリソース
	std::vector<std::weak_ptr<Dx12Resource>> shaderResource_;
private:


	// 以下二点は何かを描画するのに必要最低限ののもの(点か線しかできないけど)

	// 4頂点のメッシュ
	std::shared_ptr<Mesh> mesh_;

	// 拡大縮小平行移動用のデータ
	std::shared_ptr <Transform> transform_;
};

