#include "FigureCreator.h"

Figure* FigureCreator::create_figure(int type)
{
	switch (type)
	{
	case 1:
	{
		return new Circle();
	}
	case 2:
	{
		return new Rectangle();
	}
	}
}