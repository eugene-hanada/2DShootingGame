#pragma once
#include <vector>
#include <memory>
#include "../../../common/Math.h"

class Mesh;
class BasicRender;
class Dx12Resource;
class Dx12Wrapper;
class CbMatrix;
class Transform;

class MaterialBase
{
	// パラメーターインデックスとリソースをpairにする
	using ResourcePair = std::pair<std::shared_ptr<Dx12Resource>, int>;
public:
	MaterialBase(Dx12Wrapper& dx12,const Math::Vector2& size);
	~MaterialBase();

	void Draw(BasicRender& render, CbMatrix& cbMat);
	bool PushResource(const std::shared_ptr<Dx12Resource>& resource);
	std::shared_ptr<Mesh>& GetMesh(void) { return mesh_; }
	std::shared_ptr<Transform>& GetTransform(void) { return transform_; }
	void SetTransform(const std::shared_ptr<Transform>& transform) { transform_ = transform; }
	const std::vector<ResourcePair>& GetShaderResource(void) const { return shaderResource; }
private:

	// shaderに渡す用のリソース
	std::vector<ResourcePair> shaderResource;

	std::shared_ptr<Mesh> mesh_;

	std::shared_ptr <Transform> transform_;
};

