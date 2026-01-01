#pragma once

#include <functional>
#include <imgui.h>
#include <memory>
#include <string>
#include <vector>

namespace Gui
{
class MenuItem
{
public:
    const std::string name;

    MenuItem(const std::string& name)
        : name(name)
    {
    }
    virtual ~MenuItem() = default;

    virtual void render() = 0;
};

class MenuActionItem : public MenuItem
{
public:
    std::function<void()> action;
    std::string shortcut;

    MenuActionItem(const std::string& name, std::function<void()> onClick, const std::string& shortcut = "")
        : MenuItem(name)
        , action(onClick)
        , shortcut(shortcut)
    {
    }

    virtual void render() override
    {
        if (ImGui::MenuItem(name.c_str(), shortcut.empty() ? nullptr : shortcut.c_str()))
        {
            if (action)
                action();
        }
    }
};

class MenuFlagItem : public MenuItem
{
public:
    bool* isSelected;

    MenuFlagItem(const std::string& name, bool* selected)
        : MenuItem(name)
        , isSelected(selected)
    {
    }

    virtual void render() override
    {
        if (isSelected)
        {
            ImGui::MenuItem(name.c_str(), nullptr, isSelected);
        }
    }
};

class Menu
{
public:
    std::string name;
    std::vector<std::shared_ptr<MenuItem>> items;

    Menu(const std::string& name)
        : name(name)
    {
    }

    void addItem(std::shared_ptr<MenuItem> item)
    {
        items.push_back(item);
    }

    void render()
    {
        if (ImGui::BeginMenu(name.c_str()))
        {
            for (auto& item : items)
            {
                item->render();
            }
            ImGui::EndMenu();
        }
    }
};

class MenuBar
{
public:
    std::vector<Menu> menus;

    void addMenu(const Menu& menu)
    {
        menus.push_back(menu);
    }

    void render()
    {
        if (ImGui::BeginMainMenuBar())
        {
            for (auto& menu : menus)
            {
                menu.render();
            }
            ImGui::EndMainMenuBar();
        }
    }
};
}
