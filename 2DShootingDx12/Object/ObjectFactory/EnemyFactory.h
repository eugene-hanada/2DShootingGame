#pragma once
#include <memory>
#include <forward_list>
#include "../../common/Math.h"

class Component;
class Object;
class ObjectManager;
class AnimationData;
class BulletFactory;
class PowerUpItemFactory;
class EffectFactory;

enum class ShotType;

class EnemyFactory
{
	using ComponentShPtr = std::shared_ptr<Component>;
public:
	EnemyFactory(std::shared_ptr<AnimationData>& animData, std::shared_ptr<BulletFactory>& bulletFactory, std::shared_ptr< EffectFactory>& effectFactory);

	void CreateMoveToPosEnemyS(ObjectManager& objManager, const Math::Vector2& start, const Math::Vector2& end, const ShotType type, float shotSpeed = 3.0f);
	void CreateMoveToPosEnemyM(ObjectManager& objManager, const Math::Vector2& start, const Math::Vector2& end, const ShotType type, float shotSpeed = 3.0f);
	void CreateMoveEnemyS(ObjectManager& objManager, const Math::Vector2& pos, const Math::Vector2& moveDir, const ShotType type, float shotSpeed = 3.0f);
	void CreateMoveEnemyM(ObjectManager& objManager, const Math::Vector2& pos, const Math::Vector2& moveDir, const ShotType type, float shotSpeed = 3.0f);
	void DeleteMoveToPosEnemy(std::unique_ptr<Object>&& obj);
	void DeleteMoveEnemy(std::unique_ptr<Object>&& obj);
private:
	void CheckMoveToPosPool(void);
	void CheckMovePool(void);
	void CheckRenderPool(void);
	void CheckCollider(void);
	void CheckAnimator(void);
	void CheckObjPool(void);

	std::forward_list<ComponentShPtr> moveToPosBehaviorList_;
	std::forward_list<ComponentShPtr> moveBehaviorList_;
	std::forward_list<ComponentShPtr> renderList_;
	std::forward_list<ComponentShPtr> colliderList_;
	std::forward_list<ComponentShPtr> animatorList_;
	std::forward_list<std::unique_ptr<Object>> objPool_;
	std::unique_ptr< PowerUpItemFactory> itemfactory_;
	std::shared_ptr< EffectFactory> effectFactory_;
	std::shared_ptr<BulletFactory> bulletFactory_;
	std::shared_ptr<AnimationData> animData_;
};

