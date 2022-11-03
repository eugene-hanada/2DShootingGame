#pragma once
#include <string>
#include "../Component.h"

class TextureSheetRender;
class CbMatrix;

// オブジェクトの描画を行うクラス
class ObjRender :
	public Component
{
public:
	ObjRender() noexcept;
	virtual ~ObjRender();
	
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="texSheetRender"> renderクラス </param>
	virtual void Draw(TextureSheetRender& texSheetRender) = 0;

	/// <summary>
	/// 画像のキーをセット
	/// </summary>
	/// <param name="imgKey"> 画像のキー </param>
	void SetImgKey(const std::string& imgKey)
	{
		imgKey_ = imgKey;
	}
	
	/// <summary>
	/// セットされた画像のキーを取得
	/// </summary>
	/// <param name=""></param>
	/// <returns> 画像のキー </returns>
	const std::string& GetImgKey(void) const
	{
		return imgKey_;
	}

	/// <summary>
	/// 回転角度をセット
	/// </summary>
	/// <param name="rot"> 回転角度(ラジアン) </param>
	void SetRotation(float rot)
	{
		rotation_ = rot;
	}
protected:

	// 画像のキー
	std::string imgKey_;

	// 回転角度
	float rotation_;
private:
	const ComponentID GetID(void) const noexcept final { return ComponentID::Render; }
};

