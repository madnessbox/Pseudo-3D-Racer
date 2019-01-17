#pragma once
#include "Entity.h"
#include "Sphere.h"
#include "Plane.h"

enum class WeaponType : unsigned char
{
	Pistol, // = 0
	MachineGun,
	SlowMachineGun,
	MAX
};

class Player : public Entity
{
public:
	Player(const Vector& position);

	void Update() override;
	void Draw() override;

	bool IsColliding = false;
	int InventorySpace;

	WeaponType CurrentWeapon = WeaponType::Pistol;

private:
	float timer = 0.f;
	float aimTime = 0.f;
	float WeaponCooldown = 0.f;
};