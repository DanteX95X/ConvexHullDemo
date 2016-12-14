#include "window.h"
#include <assert.h>
#include "hull.h"
#include <string>

std::string imagePath = "weirdFace.png";
unsigned int alphaThreshold =0;


//Samples of input sets for convex hull problem
//std::vector<Point> input = { {-10,10}, {-7,3}, {-10,-10}, {-1,9}, {-1,0}, {-2,-3}, {6,4}, {5,-3}, {10,10}, {10,-10}};
//std::vector<Point> input = {{2, 1}, {2, 1}, {2, 1}, {3, 1}, {3, 1}, {3, 2}, {4, 3}, {5, 2}, {5, 1}, {4, 0}, {2, 0}, {2, 1}};
std::vector <Point> input = {{20, 13}, {24, 17}, {28, 18}, {34, 12}, {37, 16}, {34, 20}, {41, 30}, {53, 26}, {54, 12}, {49, 8}, {29, 7}, {20, 13}};

void ColorOpaquePixels(Uint32* pixels, int x, int y, int w, std::vector<Point>& points)
{
	Uint32& pixel = pixels[y*w + x];
	if((pixel & (255<<24)) >> 24 > alphaThreshold)
	{
		//pixel = 0b11111111000000000000000011111111;
		points.push_back({x,y});
	}
}

void TextureModifyingMagic(Window& window, int imageWidth, int imageHeight)
{
	SDL_Surface* surface;
	surface = IMG_Load(imagePath.c_str());
	assert(surface != nullptr);
	
	void* pixels;
	SDL_Texture* texture = SDL_CreateTexture(window.GetRenderer(), SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, surface->w, surface->h);
	assert(texture != nullptr);
	
	SDL_LockTexture(texture, nullptr, &pixels, &surface->pitch);
	memcpy(pixels, surface->pixels, surface->pitch * surface->h);
	
	Uint32* upixels = (Uint32*) pixels;
	std::vector<Point> points;
	
	for(int x = 0; x < surface->w; ++x)
	{
		for(int y = 0; y < surface->h; ++y)
		{
			ColorOpaquePixels(upixels, x, y, surface->w, points);
		}
	}

	SDL_UnlockTexture(texture);
	pixels = nullptr;
	double scaleX = imageWidth/surface->w;
	double scaleY  = imageHeight/surface->h;
	SDL_FreeSurface(surface);

	SDL_Rect destination = {0, 0, imageWidth, imageHeight};
	SDL_RenderClear(window.GetRenderer());
	SDL_RenderCopy(window.GetRenderer(), texture, nullptr, &destination);
	
	SDL_SetRenderDrawColor(window.GetRenderer(), 0, 0, 255, 255);
	std::vector<Point> hull = ConvexHull::Quickhull(points);
	for(std::size_t i = 0; i < hull.size(); ++i)
	{
		Point first = hull[i];
		Point second = hull[(i+1)%hull.size()];
		SDL_RenderDrawLine(window.GetRenderer(), first.x*scaleX, first.y*scaleY, second.x*scaleX, second.y*scaleY);
	}
	SDL_RenderPresent(window.GetRenderer());
	
	SDL_DestroyTexture(texture);
}

int main(int argc, char** argv)
{
	bool isDone = false;

	SDL_Event event;
	Window window(1024, 1024);

	TextureModifyingMagic(window, 1024, 1024);
		
	while( !isDone)
	{

			while(SDL_PollEvent(&event))
			{
					if(event.type == SDL_QUIT)
					{
							isDone = true;
					}

			}
	}
	
	return 0;
}