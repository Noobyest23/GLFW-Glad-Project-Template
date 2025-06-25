#ifndef NAPP
#define NAPP

#include "window.h"
#include "texture.h"
#include "mesh.h"
#include "shader.h"
#include "input.h"
#include "DevMenu.h"
#include <thread>
#include <chrono>

class Application {
public:

	void run();

	Application();

	~Application();

	bool isQuerying = false;
private:

	void MainLoopBegin();
	void RenderLoopBegin(Query& query) const;
	void RenderLoopEnd(Query& query) const;
	void MainLoopEnd();

	std::chrono::steady_clock::time_point frameStart;

};

// todo for app template
// make configuring glad per window easier
// 
// throttle framerate myself because vsync is USELESS
// 
// 
// controller support
// remove berohine

#endif // !NAPP

