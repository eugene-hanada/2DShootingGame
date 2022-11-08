#include "Collider.h"

// �~�`�̓����蔻��N���X
class CircleCollider :
	public Collider
{
public:
	CircleCollider();
	~CircleCollider();

	/// <summary>
	/// �����蔻����`�F�b�N���J�n����
	/// </summary>
	/// <param name="collider"> �R���C�_�[ </param>
	/// <param name="objectManager"> �I�u�W�F�N�g�}�l�[�W���[ </param>
	void Check(Collider& collider, ObjectManager& objectManager) final;

	/// <summary>
	/// �~�`�Ƃ̓����蔻����`�F�b�N����
	/// </summary>
	/// <param name="collider"> �~�`�̓����蔻�� </param>
	/// <returns> �������Ă���Ƃ�true </returns>
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
