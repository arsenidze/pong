#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <memory>
#include <string>

class InputHandler
{
public:
    InputHandler();
	~InputHandler();

	bool ask();
	bool isKeyPressed(std::string& key) const;
	bool isKeyReleased(std::string& key) const;
	bool isWindowClosed() const;
private:
	class InputHandlerImpl;
	std::unique_ptr<InputHandlerImpl> pimpl;
};

#endif 