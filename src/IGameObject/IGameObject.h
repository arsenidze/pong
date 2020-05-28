#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include "Graphics/Graphics.h"
#include "InputHandler/InputHandler.h"
#include "RectCollider/RectCollider.h"
#include "Vector2D/Vector2D.h"

class Game;

class IGameObject
{
public:
	virtual ~IGameObject() {};

	virtual void handleInput() = 0;
	virtual void update(Game& game, const InputHandler& inputHandler) = 0;
	virtual void render(Graphics& graphics) const = 0;
	virtual bool isCollideWith(const std::shared_ptr<IGameObject> gameObject, Vector2D newPos) const = 0;
	virtual RectCollider	getRectCollider() const = 0;
};

#endif 