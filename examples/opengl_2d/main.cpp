#include <iostream>
#include <chrono>
#include <thread>

#define GLAD_GL_IMPLEMENTATION
#include "utils.h"
#include <SDL.h>
#include <SDL_opengl.h>

#include "utils.h"
#include "arc/arc_physics_world.h"

int main()
{
    arc::PhysicsWorld world;
    arc::Body* body = world.AddBody(arc::Body(arc::Vec3(), 2.0));
    
    ExampleData data = IntializeExample();
    GLData glData = CreateOpenGLResources();

    bool run = true;
    SDL_Event e;

    const double timeStep = 1.0 / 120.0; 
    const auto timeStepDuration = std::chrono::duration<double>(timeStep);

    auto previous = std::chrono::steady_clock::now();
    double accumulator = 0.0;

    while(run) 
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> frameTime = now - previous;
        previous = now;

        accumulator += frameTime.count();

        while(accumulator >= timeStep) 
        {
            world.Simulate(timeStep);
            accumulator -= timeStep;
        }

        while(SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT)
                run = false;
        }

        if(body->GetPosition().y < -10) {
            body->SetPosition(arc::Vec3(body->GetPosition().x, 10.0f, 0.0f));
        }

        glData.position = arc::Vec2(body->GetPosition().x, body->GetPosition().y);
        Render(glData);

        SDL_GL_SwapWindow(data.window);
    }

    SDL_DestroyWindow(data.window);
    SDL_Quit();

    return 0;
}