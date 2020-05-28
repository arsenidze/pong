#include "Wall.h"

Wall::Wall(Vector2D pos, Vector2D size, const std::string& textureName, Vector2D eyeDirection)
    :
    pos(pos),
    size(size),
    textureName(textureName)
{
    this->collider.x = pos.x;
    this->collider.y = pos.y;
    this->collider.w_2 = size.x / 2;
    this->collider.h_2 = size.y / 2;
    this->collider.normal = eyeDirection;
}

void Wall::handleInput()
{
}

void Wall::update(Game& game, const InputHandler& inputHandler)
{
}

void Wall::render(Graphics& graphics) const
{
    int textureX = this->pos.x - this->size.x / 2;
    int textureY = this->pos.y - this->size.y / 2;

    graphics.addTextureToRender(this->textureName, textureX, textureY, this->size.x, this->size.y);
}

bool Wall::isCollideWith(const std::shared_ptr<IGameObject> gameObject, Vector2D newPos) const
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

RectCollider	Wall::getRectCollider() const
{
    return this->collider;
}