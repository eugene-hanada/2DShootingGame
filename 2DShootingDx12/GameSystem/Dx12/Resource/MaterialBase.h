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
	// �p�����[�^�[�C���f�b�N�X�ƃ��\�[�X��pair�ɂ���
public:
	MaterialBase(Dx12Wrapper& dx12,const Math::Vector2& size);
	virtual ~MaterialBase();

	std::shared_ptr<Mesh>& GetMesh(void) { return mesh_; }
	std::shared_ptr<Transform>& GetTransform(void) { return transform_; }
	void SetTransform(const std::shared_ptr<Transform>& transform) { transform_ = transform; }
	const std::vector<std::weak_ptr<Dx12Resource>>& GetShaderResource(void) const { return shaderResource_; }

	// shader�ɓn���p�̃��\�[�X
	std::vector<std::weak_ptr<Dx12Resource>> shaderResource_;
private:


	// �ȉ���_�͉�����`�悷��̂ɕK�v�Œ���̂̂���(�_���������ł��Ȃ�����)

	// 4���_�̃��b�V��
	std::shared_ptr<Mesh> mesh_;

	// �g��k�����s�ړ��p�̃f�[�^
	std::shared_ptr <Transform> transform_;
};

