#pragma once
#include <memory>
#include <list>
#include <string>

class Dx12Wrapper;
class RenderManager;
class CbMatrix;
class TextureSheetRender;
class TextureData;
class UiBase;

class UiManager
{
public:
	UiManager(const std::string& texFile, std::shared_ptr<TextureData>& textureData, Dx12Wrapper& dx12);
	void Update(void);
	void Draw(RenderManager& renderMng, CbMatrix& cbMat);
	void CreateGameUi(void);
private:
	std::unique_ptr< TextureSheetRender> texSheetRender_;
	std::shared_ptr<TextureData> textureData_;
	std::list<std::unique_ptr<UiBase>> uiList_;
};

