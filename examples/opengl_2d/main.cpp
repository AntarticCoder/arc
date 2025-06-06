#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

#define GLAD_GL_IMPLEMENTATION
#include <SDL.h>
// #include <SDL_opengl.h>

#include "utils.h"
#include "arc/arc_physics_world.h"
#include "arc/colliders/arc_aabb.h"

int main()
{
    arc::PhysicsWorld world;
    world.SetGravity(-3.0f);

    // Box 1 Creation
    arc::RigidBodyCreateInfo box1RBCreateInfo = {};
    box1RBCreateInfo.mass = 1.0f;

    arc::Object box1Info;
    box1Info.rigidBody = arc::RigidBody(box1RBCreateInfo);
    box1Info.transform.position = arc::Vec3(-10.0f, 5.0f, 0.0f);
    box1Info.collider = arc::CreateAABB(1.0f, 1.0f, 0.0f);

    arc::Object* box1 = world.AddObject(box1Info);

    // Box 2 Creation
    arc::RigidBodyCreateInfo box2RBCreateInfo = {};
    box2RBCreateInfo.mass = 1.0f;

    arc::Object box2Info;
    box2Info.rigidBody = arc::RigidBody(box2RBCreateInfo);
    box2Info.transform.position = arc::Vec3(0.0f, 5.0f, 0.0f);
    box2Info.collider = arc::CreateAABB(1.0f, 1.0f, 0.0f);

    arc::Object* box2 = world.AddObject(box2Info);

    // Floor Creation
    arc::RigidBodyCreateInfo floorRBCreateInfo = {};
    floorRBCreateInfo.mass = 10.0f;
    floorRBCreateInfo.applyGravity = false;
    floorRBCreateInfo.isStatic = true;

    arc::Object floorInfo;
    floorInfo.rigidBody = arc::RigidBody(floorRBCreateInfo);
    floorInfo.transform.position = arc::Vec3(0.0f, -10.0f, 0.0f);
    floorInfo.collider = arc::CreateAABB(100.0f, 10.0f, 0.0f);

    arc::Object* floor = world.AddObject(floorInfo);

    // Trigger Creation
    arc::RigidBodyCreateInfo triggerRBCreateInfo = {};
    triggerRBCreateInfo.mass = 1.0f;
    triggerRBCreateInfo.isStatic = true;
    triggerRBCreateInfo.isTrigger = true;

    arc::Object triggerInfo;
    triggerInfo.rigidBody = arc::RigidBody(triggerRBCreateInfo);
    triggerInfo.transform.position = arc::Vec3(-7.0f, -1.9f, 0.0f);
    triggerInfo.collider = arc::CreateAABB(6.0f, 6.0f, 0.0f);

    arc::Object* trigger = world.AddObject(triggerInfo);

    trigger->collider->SetCallback([](){
        std::cout << "Object inside Trigger" << std::endl;
    });

    box2->rigidBody.SetVelocity(arc::Vec3(-3.0f, 0.0f, 0.0f));
    
    ExampleData data = IntializeExample();
    GraphicsData graphicsData = CreateOpenGLResources();

    bool run = true;
    SDL_Event e;

    const double timeStep = 1.0 / 25.0; 
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

        if(box1->transform.position.y < -10) {
            box1->transform.position.y = 10;
        }

        if(box2->transform.position.y < -10) {
            // body2->SetPosition(arc::Vec3(body->GetPosition().x, 12.0f, 0.0f));
            box2->transform.position.y += 12;
        }

        graphicsData.objects = {
            Renderable(box1->transform.position),
            Renderable(box2->transform.position),
            Renderable(floor->transform.position, arc::Vec3(100.0f, 10.0f, 1.0f))
        };

        graphicsData.triggers = {
            Renderable(trigger->transform.position, arc::Vec3(6.0, 6.0, 1.0))
        };

        Render(&graphicsData);

        SDL_GL_SwapWindow(data.window);
    }

    SDL_DestroyWindow(data.window);
    SDL_Quit();

    return 0;
}