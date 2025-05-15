#pragma once
#ifndef MODS_IGAMEMOD_H_
#define MODS_IGAMEMOD_H_

class IGameMod
{
private:
	IGameMod() = default;

public:
    IGameMod(const IGameMod&) = delete;
	virtual ~IGameMod() = default;

public:
    /// @brief call when mod instance create
    static void init() {  }

    /// @brief call when mod load
    virtual void onLoad() = 0;

    /// @brief call every frame
    virtual void onUpdate(const float& dt) = 0;

    /// @brief call when mod unload
    virtual void onUnload() = 0;

    /// @brief get mod name
    /// @return char array of class name
    virtual const char* getName() { return typeid(*this).name(); };

protected:

private:

};


#endif // !MODS_IGAMEMOD_H_