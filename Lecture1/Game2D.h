#pragma once

#include "RGB.h"
#include "Vector2.h"
#include "Vector3.h"
#include "RGBColors.h"
#include "Timer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>         // std::this_thread::sleep_for
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace jm
{
	using vec2 = Vector2<float>;
	using vec3 = Vector3<float>;

	class Game2D
	{
	private:
		int width = 640;
		int height = 480;

		GLFWwindow* glfw_window = nullptr;

		Timer timer;

		float spf = 1.0f / 60.0f;		// second(s) per frame

		// control options
		std::map<int, bool> key_status; // key_id, is_pressed
		bool draw_grid = false;

	public:
		Game2D(const std::string& _title, const int& _width, const int& _height,
			const bool & use_full_screen = false, const int & display_ix = 0);

		~Game2D();

		void reportErrorAndExit(const std::string& function_name, const std::string& message);

		bool isKeyPressed(const int& key);
		bool isKeyReleased(const int & key);
		bool isKeyPressedAndReleased(const int& key);

		float getTimeStep();

		void drawGrid();

		void run();

		virtual void update() 
		{
			// draw
			// play sould
			// physics update
			// etc.
		}
	};
}