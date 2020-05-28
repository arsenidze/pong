#ifndef GAME_H
#define GAME_H

#include "IGameObject/IGameObject.h"
#include "InputHandler/InputHandler.h"
#include "Graphics/Graphics.h"
#include "Vector2D/Vector2D.h"

#include <vector>
#include <memory>

class Game
{
public:
    Game(int fieldWidth, int fieldHeight, std::vector<std::shared_ptr<IGameObject>>	gameObjects);
    ~Game() = default;

	void handleInput(const InputHandler& inputHandler);
	void update(const InputHandler& inputHandler);
	void render(Graphics& graphics);
	bool isRunning() const;
	std::shared_ptr<IGameObject> checkCollision(const std::shared_ptr<IGameObject> objectToCheck, Vector2D newPos) const;
	bool isFieldOver(Vector2D pos) const;
	void updateScore(Vector2D ballOutPosition);
	int	getFieldWidth() const;
	int	getFieldHeight() const;
private:
	const static int MAX_SCORE;
	bool										_isRunning;
	std::vector<std::shared_ptr<IGameObject>>	gameObjects;
	int											fieldWidth;
	int											fieldHeight;
	int											leftScore;
	int											rightScore;
};

#endif 