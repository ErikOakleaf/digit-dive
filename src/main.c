#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    SDL_Window *window; // Declare a pointer
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL3

    // Create an application window with the following settings:
    window = SDL_CreateWindow("An SDL3 window", // window title
                              640,              // width, in pixels
                              480,              // height, in pixels
                              SDL_WINDOW_OPENGL // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                     SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n",
                     SDL_GetError());
        return 1;
    }

    printf("something here");

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                done = true;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Present the frame
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
