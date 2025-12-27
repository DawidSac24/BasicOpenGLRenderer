#pragma once

class GameObject;

class Component
{
public:
    virtual ~Component() = default;

    virtual void onUpdate(float deltaTime) { }

    GameObject* owner = nullptr;
};
