#ifndef WALL_H
#define WALL_H

#include "Game/Game.h"
#include "Graphics/Graphics.h"
#include "InputHandler/InputHandler.h"
#include "IGameObject/IGameObject.h"
#include "Vector2D/Vector2D.h"
#include "RectCollider/RectCollider.h"

#include <string>

class Wall : public IGameObject
{
public:
    Wall(Vector2D pos, Vector2D size, const std::string& textureName, Vector2D eyeDirection);
    ~Wall() = default;

	void handleInput() override;
	void update(Game& game, const InputHandler& inputHandler) override;
	void render(Graphics& graphics) const override;
	virtual bool isCollideWith(const std::shared_ptr<IGameObject> gameObject, Vector2D newPos) const override;
	virtual RectCollider	getRectCollider() const override;
private:
	Vector2D	pos;
	Vector2D	size;
	std::string	textureName;

	RectCollider collider;
};

#endif 