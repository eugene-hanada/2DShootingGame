#pragma once
#include <string>
#include "../Component.h"

class TextureSheetRender;
class CbMatrix;

// �I�u�W�F�N�g�̕`����s���N���X
class ObjRender :
	public Component
{
public:
	ObjRender() noexcept;
	virtual ~ObjRender();
	
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="texSheetRender"> render�N���X </param>
	virtual void Draw(TextureSheetRender& texSheetRender) = 0;

	/// <summary>
	/// �摜�̃L�[���Z�b�g
	/// </summary>
	/// <param name="imgKey"> �摜�̃L�[ </param>
	void SetImgKey(const std::string& imgKey)
	{
		imgKey_ = imgKey;
	}
	
	/// <summary>
	/// �Z�b�g���ꂽ�摜�̃L�[���擾
	/// </summary>
	/// <param name=""></param>
	/// <returns> �摜�̃L�[ </returns>
	const std::string& GetImgKey(void) const
	{
		return imgKey_;
	}

	/// <summary>
	/// ��]�p�x���Z�b�g
	/// </summary>
	/// <param name="rot"> ��]�p�x(���W�A��) </param>
	void SetRotation(float rot)
	{
		rotation_ = rot;
	}
protected:

	// �摜�̃L�[
	std::string imgKey_;

	// ��]�p�x
	float rotation_;
private:
	const ComponentID GetID(void) const noexcept final { return ComponentID::Render; }
};

