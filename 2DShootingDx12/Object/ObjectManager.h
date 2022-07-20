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


class ObjectManager
{
public:
	ObjectManager(std::shared_ptr<TextureData>& textureData,std::shared_ptr<InputSystem>& input, Dx12Wrapper& dx12);
	~ObjectManager();
	void Update(void);
	void Draw(RenderManager& renderMng, CbMatrix& cbMat);

	void AddAnimationRender(Object& obj);
	void RemoveAnimationRender(Object& obj);
private:
	
	std::list<std::shared_ptr<Component>> animeRenderPool_;
	std::list<std::unique_ptr<Object>> objList_;
	std::shared_ptr<Dx12Resource> tex_;
	std::unique_ptr< TextureSheetRender> texSheetRender_;
};

