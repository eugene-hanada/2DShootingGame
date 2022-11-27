#pragma once
#include "ObjectBehavior.h"
#include <vector>

class AnimationData;
class EnemyFactory;
class BulletFactory;
class EffectFactory;
class ObjectManager;

class StageBehavior :
	public ObjectBehavior
{
	using SpawnFuncVec = std::vector<bool(StageBehavior::*)(ObjectManager&)>;
	using SpawnPair = std::pair<int, SpawnFuncVec>;
	using StageLevelVec = std::vector<SpawnPair>;
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


	bool SpawnMoveToPos1(ObjectManager& objectManager);
	bool SpawnMoveToPos2(ObjectManager& objectManager);
	bool SpawnMoveToPos3(ObjectManager& objectManager);
	bool SpawnMoveToPos4(ObjectManager& objectManager);

	bool SpawnMove1(ObjectManager& objectManager);
	bool SpawnMove2(ObjectManager& objectManager);
	bool SpawnMove3(ObjectManager& objectManager);

	// �^�C��
	float timer_;

	// �G�̐����N���X
	std::unique_ptr<EnemyFactory> enemyFactory_;

	// �X�R�A
	unsigned int score_;

	float spawnTime_;


	static StageLevelVec stageLevelVec_;
	SpawnFuncVec::const_iterator spawnItr_;
	StageLevelVec::const_iterator nowLevel_;
	int loopCount_;
};

