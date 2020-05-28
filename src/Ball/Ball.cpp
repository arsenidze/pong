#include "Ball.h"
#include "Game/Game.h"

#include <cmath>

const Vector2D Ball::DEFAULT_SPEED = { 0.1, 0.1 };

Ball::Ball(Vector2D pos, float radius, const std::string& textureName, Vector2D speed)
    :
    pos(pos),
    radius(radius),
    textureName(textureName),
    speed(speed),
    initialPos(pos)
{
    this->collider.x = pos.x;
    this->collider.y = pos.y;
    this->collider.w_2 = radius;
    this->collider.h_2 = radius;
}

void Ball::handleInput()
{
}

void Ball::update(Game& game, const InputHandler& inputHandler)
{
    static_cast<void>(inputHandler);

    auto newPos = this->pos + this->speed;

    auto collideWith = game.checkCollision(std::shared_ptr<Ball>(this, [](Ball*) {}), newPos);

    if (collideWith != nullptr)
    {
        auto newSpeed = this->speed.getReflectedVector(collideWith->getRectCollider().normal);

        this->speed = newSpeed;

        newPos = this->pos + this->speed;
    }

    this->pos = newPos;
    
    // NEED TO REFACTOR
    this->collider.x = this->pos.x;
    this->collider.y = this->pos.y;

    if (game.isFieldOver(this->pos))
    {
        // NEED TO REFACTOR. ?Observer
        game.updateScore(this->pos);

        this->goToInitialPosWithRandDir();
    }
}

void Ball::render(Graphics& graphics) const
{
    int textureX = this->pos.x - this->radius;
    int textureY = this->pos.y - this->radius;

    graphics.addTextureToRender(this->textureName, textureX, textureY, 2 * this->radius, 2 * this->radius);
}

bool Ball::isCollideWith(const std::shared_ptr<IGameObject> gameObject, Vector2D newPos) const
{
    auto c1 = this->collider;
    auto c2 = gameObject->getRectCollider();

    c2.x = newPos.x;
    c2.y = newPos.y;

    if ((c1.x + c1.w_2 >= c2.x - c2.w_2) &&
        (c2.x + c2.w_2 >= c1.x - c1.w_2) &&
        (c1.y + c1.h_2 >= c2.y - c2.h_2) &&
        (c2.y + c2.h_2 >= c1.y - c1.h_2))
    {
        return true;
    }

    return false;
}

RectCollider	Ball::getRectCollider() const
{
    return this->collider;
}

Vector2D Ball::getPosition() const
{
    return this->pos;
}

Vector2D Ball::getSpeed() const
{
    return this->speed;
}

void Ball::goToInitialPosWithRandDir()
{
    static Vector2D initialSpeeds[4] = {
        Vector2D(-1, -1),
        Vector2D(1, -1),
        Vector2D(1, 1),
        Vector2D(-1, 1)
    };
    static int counter = 0;

    this->pos = this->initialPos;
    auto newSpeed = initialSpeeds[counter++];
    this->speed.x = std::abs(this->speed.x) * newSpeed.x;
    this->speed.y = std::abs(this->speed.y) * newSpeed.y;
    if (counter >= sizeof(initialSpeeds) / sizeof(initialSpeeds[0]))
    {
        counter = 0;
    }
}
