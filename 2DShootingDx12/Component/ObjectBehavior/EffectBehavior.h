#pragma once
#include "ObjectBehavior.h"
#include <unordered_map>

class Animator;
class EffectFactory;

// �G�t�F�N�g�̎��
enum class EffectType
{
	ExpM,			// ����
	ExpS,			// ������
	Score			// �X�R�A
};

// �G�t�F�N�g����悤�N���X
class EffectBehavior :
	public ObjectBehavior
{
public:

	EffectBehavior(EffectFactory& factory);
	void SetType(const EffectType type)
	{
		type_ = type;
	}

private:
	void Update(ObjectManager& objectManager) final;
	void Begin(ObjectManager& objectManager) final;
	void Destory(std::unique_ptr<Object>&& obj) final;

	/// <summary>
	/// ����M�̔j���p
	/// </summary>
	/// <param name="obj"></param>
	void DestoryExpM(std::unique_ptr<Object>&& obj);

	/// <summary>
	/// ����s�̔j���p
	/// </summary>
	/// <param name="obj"></param>
	void DestoryExpS(std::unique_ptr<Object>&& obj);

	/// <summary>
	/// �X�R�A�p
	/// </summary>
	/// <param name="obj"></param>
	void DestoryScore(std::unique_ptr<Object>&& obj);

	// �A�j���[�V��������N���X
	std::weak_ptr<Animator> animator_;

	// �G�t�F�N�g�����N���X
	EffectFactory& factory_;

	// �G�̃^�C�v
	EffectType type_;

	// �j���p�̊֐�
	static std::unordered_map<EffectType, void(EffectBehavior::*)(std::unique_ptr<Object>&&)> destoryFunc_;
};

