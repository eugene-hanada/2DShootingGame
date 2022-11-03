#include "Collider.h"

// �~�`�̓����蔻��N���X
class CircleCollider :
	public Collider
{
public:
	CircleCollider();
	~CircleCollider();
	void Check(Collider& collider, ObjectManager& objectManager) final;
	bool Check(CircleCollider& collider) final;

	/// <summary>
	/// ���a�̃Z�b�g
	/// </summary>
	/// <param name="radius"> ���a </param>
	void SetRadius(const float radius)
	{
		radius_ = radius;
	}

	/// <summary>
	/// ���a�̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const float GetRadius(void) const
	{
		return radius_;
	}

private:
	// ���a
	float radius_;
};
