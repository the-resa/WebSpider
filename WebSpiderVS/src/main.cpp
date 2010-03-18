#include <iostream>
#include <windows.h>

using namespace std;


int main() {

	ShellExecute(Null, "open", "http://www.google.de", NULL, NULL, SW_SHOWNORMAL);
  return EXIT_SUCCESS;

	return 0;

}