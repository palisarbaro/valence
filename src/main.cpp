#include <cstdlib>
#include "h/ui.h"
#include "h/model.h"

int main(int argc, char* argv[]) {
	std::srand(std::time(nullptr));
	Model m(600,600,2,500);
	UI::model = &m;
	init(argc,argv);
	loop();
	return 0;
}
