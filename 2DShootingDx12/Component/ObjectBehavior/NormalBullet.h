#pragma once
#include "../../common/Math.h"
#include "ObjectBehavior.h" 

class BulletFactory;

class NormalBullet :
	public ObjectBehavior
{
public:
	NormalBullet(BulletFactory& factory);
	~NormalBullet();

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="moveVec"> �ړ����� </param>
	void SetMoveVec(const Math::Vector2& moveVec);

	/// <summary>
	/// �X�s�[�h�̃Z�b�g
	/// </summary>
	/// <param name="speed"> �X�s�[�h </param>
	void SetSpeed(float speed);

	/// <summary>
	/// �e���ђʂ�����
	/// </summary>
	/// <param name=""></param>
	void ArmorPiercing(void);

	/// <summary>
	/// �q�b�g���̏���
	/// </summary>
	/// <param name="collider"></param>
	void OnHit(Collider& collider);
private:
	void Update(ObjectManager& objectManager) final;
	virtual void Destory(std::unique_ptr<Object>&& obj) final;
	void Begin(void) final;
	BulletFactory& factoy_;
	Math::Vector2 moveVec_;
	float speed_;
	bool isAp_;
};

