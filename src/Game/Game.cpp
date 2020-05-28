#include "Game.h"
#include <iostream>
#include <string>

const int Game::MAX_SCORE = 10;

Game::Game(int fieldWidth, int fieldHeight, std::vector<std::shared_ptr<IGameObject>>	gameObjects)
	: _isRunning(true),
	gameObjects(gameObjects),
	fieldWidth(fieldWidth),
	fieldHeight(fieldHeight),
	leftScore(0),
	rightScore(0)
{
}

void Game::handleInput(const InputHandler& inputHandler)
{
	//if (inputHandler.isKeyPressed())
	//{

	//}
	//else if (inputHandler.isKeyReleased())
	//{

	//}
}

void Game::update(const InputHandler& inputHandler)
{
	for (const auto& object : this->gameObjects)
	{
		object->update(*this, inputHandler);
	}
}

void Game::render(Graphics& graphics)
{
	graphics.preRenderActions();
	for (const auto& object : this->gameObjects)
	{
		object->render(graphics);
	}
	graphics.renderAll();
}

bool Game::isRunning() const
{
	return this->_isRunning;
}

std::shared_ptr<IGameObject> Game::checkCollision(std::shared_ptr<IGameObject> objectToCheck, Vector2D newPos) const
{
	// SIMPLIFICATION: only two objects can collide in same time
	for (const auto& object : this->gameObjects)
	{
		if (object == objectToCheck)
		{
			continue;
		}
		if (object->isCollideWith(objectToCheck, newPos))
		{
			return object;
		}
	}
	return nullptr;
}

bool Game::isFieldOver(Vector2D pos) const
{
	if (pos.x > this->fieldWidth || 
		pos.x < 0 ||
		pos.y > this->fieldHeight ||
		pos.y < 0)
	{
		return true;
	}
	return false;
}

void Game::updateScore(Vector2D ballOutPosition)
{
	if (ballOutPosition.x > this->fieldWidth / 2)
	{
		this->rightScore++;
	}
	else
	{
		this->leftScore++;
	}
	std::cout << "Score: " + std::to_string(this->leftScore) + std::string(" - ") + std::to_string(this->rightScore) << std::endl;

	if (this->leftScore >= this->MAX_SCORE || this->rightScore >= this->MAX_SCORE)
	{
		this->_isRunning = false;
	}
}

int Game::getFieldWidth() const
{
	return this->fieldWidth;
}

int Game::getFieldHeight() const
{
	return this->fieldHeight;
}
