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
	void SetMoveVec(const Math::Vector2& moveVec);
	void SetSpeed(float speed);
private:
	void Update(ObjectManager& objectManager) final;
	virtual void Destory(std::unique_ptr<Object>&& obj) final;
	BulletFactory& factoy_;
	Math::Vector2 moveVec_;
	float speed_;
};

