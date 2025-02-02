#pragma once
#include <raylib.h>

class IWeapon {

    public:
        virtual void linkToPlayer(Vector2& playerPosition) = 0;
        virtual void render() = 0;
        virtual void shoot() = 0;
};

class M4A4 : public IWeapon {

    public:
        M4A4();
        void linkToPlayer(Vector2& playerPosition) override;
        void render() override;
        void shoot() override;

    private:
        Texture2D texture;
        Vector2 position;
        int ammo;
        int damage;
        int recoil;
        int firingSpeed;
};


class AWP : public IWeapon {

    public:
        void linkToPlayer(Vector2& playerPosition) override;
        void shoot() override;

    private:
        int ammo;
        int damage;
        int recoil;
        int firingSpeed;
};


class shotgun : public IWeapon {

    public:
        void linkToPlayer(Vector2& playerPosition) override;
        void shoot() override;

    private:
        int ammo;
        int damage;
        int recoil;
        int firingSpeed;
};
