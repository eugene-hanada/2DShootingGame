#pragma once
#include "ObjectBehavior.h"

class AnimationData;
class EnemyFactory;
class BulletFactory;
class EffectFactory;

class StageBehavior :
	public ObjectBehavior
{
public:
	StageBehavior(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory);
	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	const unsigned int GetScore(void) const
	{
		return score_;
	}

	/// <summary>
	/// �X�R�A�̉��Z����
	/// </summary>
	/// <param name="addValue"> ���Z����X�R�A�̒l </param>
	void AddScore(unsigned int addValue);

	/// <summary>
	/// �X�R�A�����Z����
	/// </summary>
	/// <param name="subValue"> ���Z����X�R�A�̒l </param>
	void SubScore(unsigned int subValue);

private:

	// �^�C��
	float timer_;

	// �G�̐����N���X
	std::unique_ptr<EnemyFactory> enemyFactory_;

	// �X�R�A
	unsigned int score_;
};

