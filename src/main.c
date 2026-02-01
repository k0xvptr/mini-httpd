#include "../include/server.h"

int main(int argc, char** argv){
	int serverfd = create_server(8080);
	return 0;
}
