#pragma once
#include "ObjectBehavior.h"
#include "../../common/Math.h"

class Sound;
class BulletFactory;
class ObjRender;
class EffectFactory;

class MissileBehavior :
    public ObjectBehavior
{
public:
	MissileBehavior(BulletFactory& factory, EffectFactory& effect);
	void SetMoveVec(const Math::Vector2& moveVec)
	{
		moveVec_ = moveVec;
	}
private:
	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj) final;

	void UpdateHoming(void);

	void UpdateNotHoming(void);

	void OnHit(Collider& collider, ObjectManager& objectManager) final;

	// �A�b�v�f�[�g�֐��̊֐��|�C���^
	void (MissileBehavior::* update_)(void);

	// �e�̐����p�N���X
	BulletFactory& factory_;

	// �G�t�F�N�g�����N���X
	EffectFactory& effect_;

	// �ړ��x�N�g��
	Math::Vector2 moveVec_;

	// �^�[�Q�b�g�I�u�W�F�N�g�̃|�C���^
	Object* target_;

	// �T�E���h
	std::weak_ptr<Sound> sound_;

	// �����_�[
	std::weak_ptr< ObjRender> render_;
};

