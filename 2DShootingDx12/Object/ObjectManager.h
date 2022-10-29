#pragma once
#include <memory>
#include <list>


class Object;
class Component;
class InputSystem;
class RenderManager;
class CbMatrix;
class Dx12Wrapper;
class Dx12Resource;
class TextureData;
class TextureSheetRender;
class AnimationData;
enum class ObjectID;

class ObjectManager
{
	using ObjectUptr = std::unique_ptr<Object>;
	using ObjectList = std::list<ObjectUptr>;
public:
	ObjectManager(std::shared_ptr<TextureData>& textureData, std::shared_ptr< AnimationData>& animData,std::shared_ptr<InputSystem>& input, Dx12Wrapper& dx12);
	~ObjectManager();
	void Update(void);
	void Draw(RenderManager& renderMng, CbMatrix& cbMat);
	void AddObject(ObjectUptr&& object);
	ObjectUptr RemovObjecte(ObjectList::iterator itr);
	const std::pair<ObjectList::const_iterator, bool> FindObject(ObjectID id);
private:
	ObjectList objList_;
	std::shared_ptr<Dx12Resource> tex_;
	std::unique_ptr< TextureSheetRender> texSheetRender_;
};

