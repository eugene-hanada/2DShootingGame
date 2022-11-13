#pragma once
#include <memory>
#include <list>


class Object;
class Component;
class InputSystem;
class RenderManager;
class CbMatrix;
class Dx12Wrapper;
class TextureData;
class TextureSheetRender;
class AnimationData;
class Xaudio2;
enum class ObjectID;

class ObjectManager
{
	using ObjectUptr = std::unique_ptr<Object>;
	using ObjectList = std::list<ObjectUptr>;
public:
	ObjectManager(std::shared_ptr<TextureData>& textureData,std::shared_ptr<InputSystem>& input, Dx12Wrapper& dx12, Xaudio2& xaudio);
	~ObjectManager();
	bool Update(void);
	void Draw(RenderManager& renderMng, CbMatrix& cbMat);
	void AddObject(ObjectUptr&& object);
	ObjectUptr RemovObjecte(ObjectList::iterator itr);
	const std::pair<ObjectList::const_iterator, bool> FindObject(ObjectID id);
	const std::pair<ObjectList::const_iterator, bool> FindNearObject(ObjectID id, const Math::Vector2 pos);
	void GameEnd(void);

	static constexpr Math::Vector2 fieldSize_{ 550.0f, 600.0f };
private:
	ObjectList objList_;
	std::unique_ptr< TextureSheetRender> texSheetRender_;
	std::shared_ptr<TextureData> textureData_;
	std::shared_ptr< AnimationData> animData_;

	// èIóπÇ‹Ç≈ÇÃéûä‘Çê}ÇÈ
	float endTimer_;

	bool isEnd_;
};

