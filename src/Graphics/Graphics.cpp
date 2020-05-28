#include "Graphics.h"
#include "SDL.h"

#include <string>
#include <SDL_image.h>

class Graphics::GraphicsImpl
{
public:
	~GraphicsImpl()
	{
		this->freeTextureMap();
	}

    bool init(const GraphicsConfig& graphicsConfig)
    {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			this->logMessage("Unable to initialize SDL: %s", SDL_GetError());
			return false;
		}

		this->window = SDL_CreateWindow(graphicsConfig.winName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			graphicsConfig.winWidth, graphicsConfig.winHeight, 0);
		if (!this->window)
		{
			this->logMessage("Unable to create window: %s", SDL_GetError());
			return false;
		}

		this->renderer = SDL_CreateRenderer(this->window, -1, 0);
		if (!this->renderer)
		{
			this->logMessage("Unable to create renderer: %s", SDL_GetError());
			SDL_DestroyWindow(this->window);
			return false;
		}

		if (SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
		{
			this->logMessage("Unable to set render draw color: %s", SDL_GetError());
			SDL_DestroyRenderer(this->renderer);
			SDL_DestroyWindow(this->window);
			return false;
		}

		return true;
    }

	void deinit()
	{
		if (!this->renderer)
			SDL_DestroyRenderer(this->renderer);
		if (!this->window)
			SDL_DestroyWindow(this->window);
		SDL_Quit();
	}

	bool loadTextures(const std::map<std::string, std::filesystem::path>& textureFilesMap)
	{
		//int flags = IMG_INIT_JPG | IMG_INIT_PNG;
		//int initted = IMG_Init(flags);

		for (const auto& textureFile : textureFilesMap)
		{
			auto surface = IMG_Load(textureFile.second.string().c_str());
			if (!surface)
			{
				this->logMessage("Unable to load image: %s", SDL_GetError());
				this->freeTextureMap();
				return false;
			}
			auto texture = SDL_CreateTextureFromSurface(this->renderer, surface);
			SDL_FreeSurface(surface);
			if (!texture)
			{
				this->logMessage("Unable to create texture for image: %s", SDL_GetError());
				this->freeTextureMap();
				return false;
			}
			this->textureMap.insert({ textureFile.first, texture});
		}
		return true;
	}
	void addTextureToRender(const std::string textureName, int x, int y, int w, int h)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		
		auto search = this->textureMap.find(textureName);
		if (search != this->textureMap.end())
		{
			SDL_RenderCopy(this->renderer, search->second, NULL, &rect);
		}
	}
	void preRenderActions()
	{
		SDL_RenderClear(this->renderer);
	}
	void renderAll()
	{
		SDL_RenderPresent(this->renderer);
	}
private:
	void	logMessage(const char* fmt, ...) const
	{
		printf(fmt);
	}
	void	freeTextureMap()
	{
		for (const auto& t : this->textureMap)
		{
			SDL_DestroyTexture(t.second);
		}
	}

    SDL_Window* window;
    SDL_Renderer* renderer;
	std::map<std::string, SDL_Texture*>	textureMap;
};

Graphics::Graphics()
	: pimpl(std::make_unique<GraphicsImpl>())
{
}

Graphics& Graphics::getInstance()
{
	static Graphics instance;

	return instance;
}

bool Graphics::init(const GraphicsConfig& graphicsConfig)
{
    return this->pimpl->init(graphicsConfig);
}

void Graphics::deinit()
{
	this->pimpl->deinit();
}

bool Graphics::loadTextures(const std::map<std::string, std::filesystem::path>& textureFilesMap)
{
	return this->pimpl->loadTextures(textureFilesMap);
}

void Graphics::addTextureToRender(const std::string textureName, int x, int y, int w, int h)
{
	this->pimpl->addTextureToRender(textureName, x, y, w, h);
}

void Graphics::preRenderActions()
{
	this->pimpl->preRenderActions();
}

void Graphics::renderAll()
{
	this->pimpl->renderAll();
}