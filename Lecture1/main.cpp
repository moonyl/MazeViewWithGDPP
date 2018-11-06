#include "Game2D.h"
#include "RGBColors.h"
#include "DrawFunctions.h"
#include "TankExample.h"
#include <iostream>

using namespace jm;

class DrawingPrimitives : public Game2D
{
private:
	float time = 0.0f;

public:
	DrawingPrimitives()
		: Game2D("This is my digital canvas!", 1280, 960, false, 2)
	{}

	void update() override
	{
		beginTransformation();
		{
			translate(0.5f, 0.5f);
			//rotate(time * 180.0f);
			//scale(2.0f, 1.0f);

			setLineWidth(3);
			drawWiredSquare(jm::RGBColors::blue, 0.5f);
			drawFilledTriangle(jm::RGBColors::gray, 0.5f);
			drawWiredTriangle(jm::RGBColors::red, 0.5f);

			translate(-0.5f, -0.5f);
			drawFilledBox(jm::RGBColors::green, 0.1f, 0.2f);
			drawLine(jm::RGBColors::olive, vec2(-0.1f, -0.1f), jm::RGBColors::blue, vec2(0.2f, 0.2f));

			translate(-0.5f, -0.5f);
			drawLine(jm::RGBColors::olive, vec2(-0.1f, -0.1f), jm::RGBColors::blue, vec2(0.1f, 0.1f));
		}
		endTransformation();

		beginTransformation();
		{
			translate(-0.25f, 0.0f);
			drawWiredCircle(jm::RGBColors::black, 0.05f);

			translate(-0.25f, 0.0f);
			drawFilledCircle(jm::RGBColors::black, 0.1f);

			translate(-0.25f, 0.0f);
			drawWiredPentagon(jm::RGBColors::black, 0.1f);

			translate(-0.25f, 0.0f);
			drawFilledPentagon(jm::RGBColors::black, 0.1f);
		}
		endTransformation();

		time += getTimeStep();
	}
};

int main(void)
{
	//TankExample().run();
	DrawingPrimitives().run();

	return 0;
}
