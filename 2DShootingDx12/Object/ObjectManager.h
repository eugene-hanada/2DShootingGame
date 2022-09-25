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

class ObjectManager
{
public:
	ObjectManager(std::shared_ptr<TextureData>& textureData, std::shared_ptr< AnimationData>& animData,std::shared_ptr<InputSystem>& input, Dx12Wrapper& dx12);
	~ObjectManager();
	void Update(void);
	void Draw(RenderManager& renderMng, CbMatrix& cbMat);
	void AddObject(std::unique_ptr<Object>&& object);
	std::unique_ptr<Object> RemovObjecte(std::list<std::unique_ptr<Object>>::iterator itr);
private:
	std::list<std::unique_ptr<Object>> objList_;
	std::shared_ptr<Dx12Resource> tex_;
	std::unique_ptr< TextureSheetRender> texSheetRender_;
};

