#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GraphicsConfig/GraphicsConfig.h"

#include <map>
#include <memory>
#include <filesystem>

class Graphics
{
public:
    static Graphics& getInstance();

    bool    init(const GraphicsConfig& graphicsConfig);
    void    deinit();
    bool    loadTextures(const std::map<std::string, std::filesystem::path>& textureFilesMap);
    void    addTextureToRender(const std::string textureName, int x, int y, int w, int h);
    void    preRenderActions();
    void    renderAll();
private:
    Graphics();
    Graphics(const Graphics&);
    //Graphics(const Graphics&);
    //Graphics& operator=(const Graphics&);
    class GraphicsImpl;
    std::unique_ptr<GraphicsImpl> pimpl;
};

#endif 