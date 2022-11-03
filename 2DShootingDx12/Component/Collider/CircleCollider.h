#include "Collider.h"

// ‰~Œ`‚Ì“–‚½‚è”»’èƒNƒ‰ƒX
class CircleCollider :
	public Collider
{
public:
	CircleCollider();
	~CircleCollider();
	void Check(Collider& collider, ObjectManager& objectManager) final;
	bool Check(CircleCollider& collider) final;

	/// <summary>
	/// ”¼Œa‚ÌƒZƒbƒg
	/// </summary>
	/// <param name="radius"> ”¼Œa </param>
	void SetRadius(const float radius)
	{
		radius_ = radius;
	}

	/// <summary>
	/// ”¼Œa‚ÌŽæ“¾
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const float GetRadius(void) const
	{
		return radius_;
	}

private:
	// ”¼Œa
	float radius_;
};
