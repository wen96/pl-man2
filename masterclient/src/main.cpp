#include <iostream>
#include "CMasterMan.h"
#include "CLauncher.h"

using namespace std;

/*
This is the main method. We can now use main() on every platform.
 */
int main(int argc, char * argv[])
{

	try {
		if (argc > 2) throw "Error: Solo se permite en argumento -a\n";

		string param = "";
		if (argc > 1) param = argv[1];

		if (argc == 2 && param == "-a"){
			masterclient::CLauncher::get().loadConfig();
			masterclient::CMasterMan::get().run();
		}else{
			if (masterclient::CLauncher::get().run()){
				masterclient::CMasterMan::get().run();
			}
		}

	}
	catch (const char * e)
	{
		cerr << e << endl;
	}

	return 0;
}

