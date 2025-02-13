#pragma once

//#include <SDL.h>
//#include <unordered_map>
//#include <memory>

#include "ImGui/ImGuiRenderer.h"

#include "Utils/Singleton.h"

class WindowEventManager : public Singleton<WindowEventManager> 
{

private:

    SDL_Event mEvent;
    std::shared_ptr<ImGuiRenderer> mImGuiRenderer;
    std::unordered_map<SDL_Keycode, bool> mKeyStates;

public:

    void handleEvents() {
        mKeyStates.clear();

        while (SDL_PollEvent(&mEvent) != 0) {
            if (mEvent.type == SDL_QUIT) {
                mOnQuit();
            }
            if (mEvent.type == SDL_KEYDOWN) {
                mKeyStates[mEvent.key.keysym.sym] = true;
            }
            else if (mEvent.type == SDL_KEYUP) {
                mKeyStates[mEvent.key.keysym.sym] = false;
            }

            mImGuiRenderer->processEvent(&mEvent);
        }
    }

    bool isKeyPressed(SDL_Keycode key) 
    {
        return mKeyStates[key];
    }

    void setImGuiRenderer(std::shared_ptr<ImGuiRenderer> renderer)
    {
        mImGuiRenderer = renderer;
    }


//callbacks
private:
    using onQuitCallback = std::function<void()>;
    onQuitCallback mOnQuit{ nullptr };

public:
    void setOnQuitCallback(onQuitCallback callback) { mOnQuit = callback; }

};