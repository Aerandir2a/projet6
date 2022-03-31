#include <SDL_opengl.h>
#include <chrono>
#include <vector>;
#pragma one

template <typename T>
using Vector = std::vector<T>;

using Clock = std::chrono::high_resolution_clock;
using Timestamp = Clock::time_point;
using Duration = Clock::duration;

inline float Seconds(Duration const& iDuration)
{
	return std::chrono::duration_cast<std::chrono::duration<float>>(iDuration).count();
}

class Texture {
public:
	int x, y, frames, nrChannels;
	int* delay;
	unsigned char* data;
	GLuint texture;
	Timestamp timergif;
	void LoadTextureGif(const char* path);
	void LoadTexture2D(const char* path);
	static void GifTick(Texture tex, GLuint lay, int* frame);
};