#ifndef PADDLE_H
#define PADDLE_H

#include "IGameObject/IGameObject.h"
#include "Vector2D/Vector2D.h"

#include <string>
#include <vector>

class Paddle : public IGameObject
{
public:
	Paddle(Vector2D pos, Vector2D size, const std::string& textureName, Vector2D eyeDirection, std::vector<std::string> moveKeys, Vector2D speed = Paddle::DEFAULT_SPEED);
    ~Paddle() = default;

	void handleInput() override;
	void update(Game& game, const InputHandler& inputHandler) override;
	void render(Graphics& graphics) const override;
	bool isCollideWith(const std::shared_ptr<IGameObject> gameObject, Vector2D newPos) const override;
	RectCollider	getRectCollider() const override;

	const static int UP_KEY_INDEX = 0;
	const static int DOWN_KEY_INDEX = 1;
	const static Vector2D DEFAULT_SPEED;
private:
	Vector2D	pos;
	Vector2D	speed;
	Vector2D	size;
	std::string	textureName;
	std::vector<std::string> moveKeys;

	RectCollider collider;
};

#endif 