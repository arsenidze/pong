#include "PaddleBot.h"
#include "Game/Game.h"
#include "Wall/Wall.h"

const Vector2D PaddleBot::DEFAULT_SPEED = { 0, 20 };

PaddleBot::PaddleBot(Vector2D pos, Vector2D size, const std::string& textureName, Vector2D eyeDirection, std::shared_ptr<Ball> ball, Vector2D speed)
    :
    pos(pos),
    size(size),
    textureName(textureName),
    ball(ball),
    speed(speed)
{
    this->collider.x = pos.x;
    this->collider.y = pos.y;
    this->collider.w_2 = size.x / 2;
    this->collider.h_2 = size.y / 2;
    this->collider.normal = eyeDirection;
}

void PaddleBot::handleInput()
{
}

void PaddleBot::update(Game& game, const InputHandler& inputHandler)
{
    auto newPos = this->pos;

    newPos.y = this->ball->getPosition().y;

    auto collideWith = game.checkCollision(std::shared_ptr<PaddleBot>(this, [](PaddleBot*) {}), newPos);
    if (collideWith != nullptr)
    {
        auto wall = std::dynamic_pointer_cast<Wall>(collideWith);
        if (wall)
        {
            return;
        }
    }
    this->pos = newPos;

    // NEED TO REFACTOR
    this->collider.x = this->pos.x;
    this->collider.y = this->pos.y;
}

void PaddleBot::render(Graphics& graphics) const
{
    int textureX = this->pos.x - this->size.x / 2;
    int textureY = this->pos.y - this->size.y / 2;

    graphics.addTextureToRender(this->textureName, textureX, textureY, this->size.x, this->size.y);
}

bool PaddleBot::isCollideWith(const std::shared_ptr<IGameObject> gameObject, Vector2D newPos) const
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

RectCollider	PaddleBot::getRectCollider() const
{
    return this->collider;
}

Vector2D PaddleBot::calculateBallCollisionPoint() const
{
    auto ballPos = this->ball->getPosition();
    auto ballSpeed = this->ball->getSpeed();

    auto t1 = (this->pos.x - ballPos.x) / ballSpeed.x;
    auto t2 = ballPos.y + ballSpeed.y * t1;

    return Vector2D(this->pos.x, t2);
}
