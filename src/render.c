#include "render.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>




int render_init(char const *title,int width,int height)
{
  // Create window
  render_window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,
                                  height,SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
  if (render_window == NULL)
  {
    printf("sdl can't make window, error: %s\n",SDL_GetError());
    return 1;
  }

  // Create renderer for window
  render_renderer = SDL_CreateRenderer(render_window,-1,SDL_RENDERER_ACCELERATED);
  if (render_renderer == NULL)
  {
    printf("Couldn't get SDL Renderer going :( SDL Error:%s\n",SDL_GetError());
    return 1;
  }
  SDL_SetRenderDrawColor(render_renderer,0xFF,0xaa,0x69,0xFF);

  // Turn on PNG Loading
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags))
  {
    printf("SDL_image could not initialize! SDL_image Error: %s\n",IMG_GetError());
    return 1;
  }
}

void render_close()
{
  SDL_DestroyRenderer(render_renderer);
  SDL_DestroyWindow(render_window);
  IMG_Quit();
}


void render_update()
{
  SDL_RenderPresent(render_renderer);
}