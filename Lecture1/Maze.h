#pragma once
#include "Game2D.h"
#include <bitset>

const int maze[][24] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,1,1,1,1,1,1,0,0,0,1,0,1,1,1,0,1},
    {1,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1},
    {1,0,1,1,0,0,0,0,1,1,1,1,0,1,1,1,0,0,0,1,1,1,0,1},
    {1,0,1,0,1,1,1,1,1,0,0,0,0,1,0,1,1,1,0,1,0,0,0,1},
    {1,0,1,0,1,0,0,0,1,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,0,1,0,1,1,1,1,1,0,1,0,1},
    {1,0,1,1,1,0,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,1,1,1,0,1,0,1,0,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,1,1,1,0,0,1,1,0,0,1,0,1,1,1,0,1},
    {1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1,1,1,0,0,0,0,0,1},
    {1,0,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,0,1,1,1,0,1,1,1,0,1,0,0,0,1},
    {1,0,1,0,1,0,0,0,1,1,1,1,0,1,0,1,0,0,0,1,1,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,0,1,0,1,1,1,1,0,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

class Maze : public jm::Game2D
{
	//const int maze[18][24];

public:
	Maze() : jm::Game2D("Moony exercise", 1024, 768, false, 2)
	{

	}

	~Maze() {

	}

	int selectBlock(int x, int y) {
		int result = 0;
        if (maze[y][x] == 0) {
            return result;
        }

		if (y - 1 >= 0) {
			result |= (maze[y-1][x]);

		}
		if (x + 1 < 24) {
			result |= (maze[y][x + 1] << 1);

		}
		if (y + 1 < 18) {
			result |= (maze[y + 1][x] << 2);

		}
		if (x - 1 >= 0) {
			result |= (maze[y][x - 1] << 3);
		}
		return result;
	}

    bool hasYElement(int type) const { return (type & 0x5) != 0; }
    bool hasXElement(int type) const { return (type & 0xa) != 0; }

    float xLen(int type, float unit) const {
        using namespace std;
        std::bitset<8> counter(type & 0xa);
        return counter.count() * unit;
    }
    float yLen(int type, float unit) const {
        using namespace std;
        std::bitset<8> counter(type & 0x5);
        return counter.count() * unit;
    }
    float xTranslated(int type, float unit) const {
        int posDiff = 0;
        if (type & 0x2) {
            posDiff--;
        }
        if (type & 0x8) {
            posDiff++;
        }
        return -unit * posDiff;
    }

    float yTranslated(int type, float unit) const {
        int posDiff = 0;
        if (type & 0x1) {
            posDiff--;
        }
        if (type & 0x4) {
            posDiff++;
        }
        return -unit * posDiff;
    }

    void drawXDirBlock(int type, float lengthUnit, float posUnit, float thickness) {
        using namespace jm;
        if (xLen(type, lengthUnit) > 0) {
            if (xTranslated(type, posUnit) != 0) {
                beginTransformation();
                translate(xTranslated(type, posUnit), 0);
                drawFilledBox(Colors::black, xLen(type, lengthUnit), thickness);
                endTransformation();
            }
            else {
                drawFilledBox(Colors::black, xLen(type, lengthUnit), thickness);
            }
        }
    }

    void drawYDirBlock(int type, float lengthUnit, float posUnit, float thickness) {
        using namespace jm;
        if (yLen(type, lengthUnit) > 0) {
            if (yTranslated(type, posUnit) != 0) {
                beginTransformation();
                translate(0, yTranslated(type, posUnit));
                drawFilledBox(Colors::black, thickness, yLen(type, lengthUnit));
                endTransformation();
            }
            else {
                drawFilledBox(Colors::black, thickness, yLen(type, lengthUnit));
            }
        }
    }

    void drawOriginThickBlock(int type, float posUnit, float thickness) {
        bool needOriginThickBlock = false;
        if (xTranslated(type, posUnit)) {
            if (yTranslated(type, posUnit) || hasYElement(type)) {
                needOriginThickBlock = true;
            }
        }
        else if (yTranslated(type, posUnit)) {
            if (hasXElement(type)) {
                needOriginThickBlock = true;
            }
        }
        using namespace jm;
        if (needOriginThickBlock) {
            drawFilledBox(Colors::black, thickness, thickness);
        }
    }

    void drawBlock(int type) {
        const float thickness = 0.02f;
        const float lengthUnit = 0.05f;
        const float posUnit = 0.025f;

        using namespace jm;
        // first x direction
        drawXDirBlock(type, lengthUnit, posUnit, thickness);

        // next y direction
        drawYDirBlock(type, lengthUnit, posUnit, thickness);

        drawOriginThickBlock(type, posUnit, thickness);        
    }



	void update() override
	{
		using namespace jm;

        translate(-1.3f, 1.0f);
        for (int i = 0; i < sizeof (maze[0])/sizeof (int); i++) {
            translate(0.1f, 0);
            beginTransformation();
            for (int j = 0; j < sizeof(maze)/sizeof(maze[0]); j++) {
                translate(0, -0.1f);
                drawBlock(selectBlock(i, j));
            }
            endTransformation();
        } 
	}
};

