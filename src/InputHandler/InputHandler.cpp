#include "InputHandler.h"

#include "SDL.h"

class InputHandler::InputHandlerImpl
{
public:
    bool ask()
    {
        auto isEvent = SDL_PollEvent(&this->event);

        return true ? isEvent == 1 : false;
    }
    bool isKeyPressed(std::string& key) const
    {
        if (this->event.type != SDL_KEYDOWN)
            return false;

        key = SDL_GetKeyName(this->event.key.keysym.sym);

        return true;
    }
    bool isKeyReleased(std::string& key) const
    {
        if (this->event.type != SDL_KEYUP)
            return false;

        key = SDL_GetKeyName(this->event.key.keysym.sym);

        return true;
    }

    bool isWindowClosed() const
    {
        if (this->event.type != SDL_QUIT)
            return false;

        return true;
    }
private:
    bool        isEvent;
    SDL_Event   event;
};

InputHandler::InputHandler()
    : pimpl(std::make_unique<InputHandlerImpl>())
{
}

InputHandler::~InputHandler() = default;

bool InputHandler::ask()
{
    return this->pimpl->ask();
}

bool InputHandler::isKeyPressed(std::string& key) const
{
    return this->pimpl->isKeyPressed(key);
}

bool InputHandler::isKeyReleased(std::string& key) const
{
    return this->pimpl->isKeyReleased(key);
}

bool InputHandler::isWindowClosed() const
{
    return this->pimpl->isWindowClosed();
}