#include <Veritum.h>

int main()
{
	if (VeritumInit()) return -1;
	auto win = Veritum::Window("Test Window", 600, 400);



	win.close();
	VeritumClose();
	return 0;
}
