#ifndef BALL_H
#define BALL_H

#include "IGameObject/IGameObject.h"
#include "Vector2D/Vector2D.h"

class Ball : public IGameObject
{
public:
    Ball(Vector2D pos, float radius, const std::string& textureName, Vector2D speed = Ball::DEFAULT_SPEED);
    ~Ball() = default;

	void handleInput() override;
	void update(Game & game, const InputHandler & inputHandler) override;
	void render(Graphics & graphics) const override;
	bool isCollideWith(const std::shared_ptr<IGameObject> gameObject, Vector2D newPos) const override;
	RectCollider	getRectCollider() const override;

	Vector2D	getPosition() const;
	Vector2D	getSpeed() const;

	const static Vector2D DEFAULT_SPEED;
private:
	Vector2D	pos;
	Vector2D	speed;
	float		radius;
	std::string	textureName;

	// SIMPLIFICATION: ball has rectengular collider
	RectCollider collider;
	Vector2D	initialPos;
	void		goToInitialPosWithRandDir();
};

#endif 