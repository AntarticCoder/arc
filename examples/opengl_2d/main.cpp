#include <iostream>
#include <chrono>
#include <thread>

#define GLAD_GL_IMPLEMENTATION
#include "utils.h"
#include <SDL.h>
#include <SDL_opengl.h>

#include "utils.h"
#include "arc/arc_physics_world.h"
#include "arc/colliders/arc_aabb.h"

int main()
{
    arc::PhysicsWorld world;
    world.SetGravity(-3.0f);

    arc::RigidBody* body = world.CreateBody(arc::Vec3(0.0f), 1.0f);
    body->AddAABB(arc::Vec3(-0.5f, -0.5f, 0.0f), arc::Vec3(0.5f, 0.5f, 0.0f));
    // body->SetGravity(false);

    arc::RigidBody* body2 = world.CreateBody(arc::Vec3(10.0f, 0.0f, 0.0f), 1.0f);
    body2->AddAABB(arc::Vec3(-0.5f, -0.5f, 0.0f), arc::Vec3(0.5f, 0.5f, 0.0f));
    body2->SetVelocity(arc::Vec3(-3.0f, 0.0f, 0.0f));

    arc::RigidBody* floor = world.CreateBody(arc::Vec3(0.0f, -10.0f, 0.0f), 10.0f);
    floor->AddAABB(arc::Vec3(-50.0f, -5.0f, 0.0f), arc::Vec3(50.0f, 5.0f, 0.0f));
    floor->SetGravity(false);
    floor->SetStatic(true);
    
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

        if(body2->GetPosition().y < -10) {
            body2->SetPosition(arc::Vec3(body->GetPosition().x, 12.0f, 0.0f));
        }

        glData.cubePosition = body->GetPosition();
        glData.floorPosition = floor->GetPosition();
        glData.body2Position = body2->GetPosition();
        glData.floorScale = arc::Vec3(100.0f, 10.0f, 1.0f);

        Render(&glData);

        SDL_GL_SwapWindow(data.window);
    }

    SDL_DestroyWindow(data.window);
    SDL_Quit();

    return 0;
}