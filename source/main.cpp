#include "window.h"
#include <assert.h>
#include "hull.h"
#include <string> 
#include "timer.h"


void AnalyzePixel(Uint32* pixels, int x, int y, int w, std::vector<Point>& points)
{
	Uint32& pixel = pixels[y*w + x];
	if((pixel & (255<<24)) >> 24 > ConvexHull::alphaThreshold)
	{
		pixel = 0xFF0000FF;
		points.push_back({x,y});
	}
}

void TextureModifyingMagic(Window& window, int imageWidth, int imageHeight)
{
	SDL_Surface* surface;
	surface = IMG_Load(ConvexHull::imagePath.c_str());
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
			AnalyzePixel(upixels, x, y, surface->w, points);
		}
	}

	SDL_UnlockTexture(texture);
	pixels = nullptr;
	double scaleX = imageWidth / static_cast<double>(surface->w);
	double scaleY  = imageHeight / static_cast<double>(surface->h);
	SDL_FreeSurface(surface);

	SDL_Rect destination = {0, 0, imageWidth, imageHeight};
	SDL_RenderClear(window.GetRenderer());
	SDL_RenderCopy(window.GetRenderer(), texture, nullptr, &destination);
	
	SDL_SetRenderDrawColor(window.GetRenderer(), 0, 0, 255, 255);

	Timer::Instance().Update();
	
	std::vector<Point> hull = ConvexHull::CalculateConvexHull(points);
	
	Timer::Instance().Update();
	std::cout << "\n\tTime = " << Timer::Instance().GetTime() << "s\n";
	

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