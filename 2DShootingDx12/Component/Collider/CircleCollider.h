#include "Collider.h"

class CircleCollider :
	public Collider
{
public:
	CircleCollider();
	~CircleCollider();
	void Check(Collider& collider, ObjectManager& objectManager) final;
	bool Check(CircleCollider& collider) final;

	void SetRadius(const float radius)
	{
		radius_ = radius;
	}

	const float GetRadius(void) const
	{
		return radius_;
	}

private:
	float radius_;
};
