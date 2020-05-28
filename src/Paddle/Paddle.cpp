#include "Paddle.h"
#include "Game/Game.h"
#include "Wall/Wall.h"

const Vector2D Paddle::DEFAULT_SPEED = { 0, 20 };

Paddle::Paddle(Vector2D pos, Vector2D size, const std::string& textureName, Vector2D eyeDirection, std::vector<std::string> moveKeys, Vector2D speed)
    :
    pos(pos),
    size(size),
    textureName(textureName),
    moveKeys(moveKeys),
    speed(speed)
{
    this->collider.x = pos.x;
    this->collider.y = pos.y;
    this->collider.w_2 = size.x / 2;
    this->collider.h_2 = size.y / 2;
    this->collider.normal = eyeDirection;
}

void Paddle::handleInput()
{
}

void Paddle::update(Game& game, const InputHandler& inputHandler)
{
    std::string key;

    Vector2D newPos;
    if (inputHandler.isKeyPressed(key))
    {
        newPos = this->pos;
        if (key == this->moveKeys[Paddle::UP_KEY_INDEX])
        {
            newPos.y -= this->speed.y;
        }
        else if (key == this->moveKeys[Paddle::DOWN_KEY_INDEX])
        {
            newPos.y += this->speed.y;
        }

        auto collideWith = game.checkCollision(std::shared_ptr<Paddle>(this, [](Paddle*) {}), newPos);
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
}

void Paddle::render(Graphics& graphics) const
{
    int textureX = this->pos.x - this->size.x / 2;
    int textureY = this->pos.y - this->size.y / 2;

    graphics.addTextureToRender(this->textureName, textureX, textureY, this->size.x, this->size.y);
}

bool Paddle::isCollideWith(const std::shared_ptr<IGameObject> gameObject, Vector2D newPos) const
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

RectCollider	Paddle::getRectCollider() const
{
    return this->collider;
}