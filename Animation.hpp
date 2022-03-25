#pragma one

class Animation {
public:
	int x, y, frames = 0, nrChannels = 0;
	int* delay;
	unsigned char* data;
	Animation LoadGif(char* path);
	Animation Load2D(char* path);
};