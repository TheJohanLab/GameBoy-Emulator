#pragma once

//#include <SDL.h>
//#include <unordered_map>
//#include <memory>

#include "Screen/ImGuiRenderer.h"

class WindowEventManager {

private:
    SDL_Event mEvent;
    std::unordered_map<SDL_Keycode, bool> mKeyStates;
    bool mQuit = false;

public:

    void handleEvents(std::shared_ptr<ImGuiRenderer> imGuiRenderer) {
        mKeyStates.clear();

        while (SDL_PollEvent(&mEvent) != 0) {
            if (mEvent.type == SDL_QUIT) {
                mQuit = true;
            }
            if (mEvent.type == SDL_KEYDOWN) {
                mKeyStates[mEvent.key.keysym.sym] = true;
            }
            else if (mEvent.type == SDL_KEYUP) {
                mKeyStates[mEvent.key.keysym.sym] = false;
            }

            imGuiRenderer->processEvent(&mEvent);
        }
    }

    bool isKeyPressed(SDL_Keycode key) 
    {
        return mKeyStates[key];
    }




};