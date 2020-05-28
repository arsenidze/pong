#ifndef PADDLEBOT_H
#define PADDLEBOT_H

#include "IGameObject/IGameObject.h"
#include "Vector2D/Vector2D.h"
#include "Ball/Ball.h"

class PaddleBot : public IGameObject
{
public:
	PaddleBot(Vector2D pos, Vector2D size, const std::string& textureName, Vector2D eyeDirection, std::shared_ptr<Ball> ball, Vector2D speed = PaddleBot::DEFAULT_SPEED);
	~PaddleBot() = default;

	void handleInput() override;
	void update(Game& game, const InputHandler& inputHandler) override;
	void render(Graphics& graphics) const override;
	bool isCollideWith(const std::shared_ptr<IGameObject> gameObject, Vector2D newPos) const override;
	RectCollider	getRectCollider() const override;

	const static Vector2D DEFAULT_SPEED;
private:
	Vector2D	pos;
	Vector2D	speed;
	Vector2D	size;
	std::string	textureName;

	RectCollider collider;

	std::shared_ptr<Ball> ball;
	Vector2D calculateBallCollisionPoint() const;
};
#endif 