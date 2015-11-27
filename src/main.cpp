#include "op.hh"

int main()
{
	Map yolo(10, 10);
	AI  *buff;

	std::cout << yolo.getSizeX() << " " << yolo.getSizeY() << std::endl;
	yolo.displayMap();
	std::cout << std::endl;
	int x,y;
	while (true)
	{
		std::cout << "Enter x between 0 and " << yolo.getSizeX() - 1 << std::endl;
		std::cin >> x;
		std::cout << "Enter y between 0 and " << yolo.getSizeY() - 1 << std::endl;
		std::cin >> y;
		if (!yolo.checkCase(x, y))
			std::cout << "Ouch that's not working" << std::endl;
		else
		{
			yolo.setMapValue(x, y, 2);
			std::cout << std::endl;
			yolo.displayMap();
			int win = yolo.hasWon();
			if (win != 0)
			{
				std::cout << "Player " << win << " just won :DDD" << std::endl;
				return (0);
			}
			buff = new AI(yolo, PLAYING);
			buff->startAi(PLAYING, 0);
			buff->place(&yolo);
			delete buff;
			std::cout << std::endl;
			yolo.displayMap();
			win = yolo.hasWon();
			if (win != 0)
			{
				std::cout << "Player " << win << " just won :DDD" << std::endl;
				return (0);
			}
			if (yolo.isFull() && win == 0)
			{
				std::cout << "That's a draw folks" << std::endl;
				return (0);
			}
		}
	}
	return (0);
}
