#pragma once

#include "ntv.hpp"
#include "hash.hpp"

#include <array>
#include <cstdint>

namespace nob {
	namespace arm {
		struct weapon_info_t {
			alignas(uintptr_t) uint8_t damage, speed, capacity, accuracy, range;
			bool valid;
		};

		inline weapon_info_t weapon_info(const hasher &wpn) {
			weapon_info_t info;
			info.valid = ntv::WEAPON::GET_WEAPON_HUD_STATS(wpn.hash(), reinterpret_cast<int *>(&info));
			return info;
		}

		inline hasher weapon_group(const hasher &wpn) {
			return ntv::WEAPON::GET_WEAPONTYPE_GROUP(wpn.hash());
		}

		static constexpr std::array<hasher, 71> weapons {{
			"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_HEAVYPISTOL",
			"WEAPON_VINTAGEPISTOL", "WEAPON_SNSPISTOL", "WEAPON_MARKSMANPISTOL", "WEAPON_MACHINEPISTOL",
			"WEAPON_REVOLVER", "WEAPON_FLAREGUN",

			"WEAPON_SMG", "WEAPON_MICROSMG", "WEAPON_ASSAULTSMG", "WEAPON_MINISMG", "WEAPON_COMBATPDW",
			"WEAPON_MG", "WEAPON_COMBATMG", "WEAPON_GUSENBERG",

			"WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_BULLPUPRIFLE",
			"WEAPON_MARKSMANRIFLE", "WEAPON_COMPACTRIFLE", "WEAPON_SPECIALCARBINE", "WEAPON_MUSKET",

			"WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_STUNGUN",

			"WEAPON_UNARMED",
			"WEAPON_CROWBAR", "WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT",
			"WEAPON_GOLFCLUB", "WEAPON_DAGGER", "WEAPON_HATCHET", "WEAPON_KNUCKLE", "WEAPON_MACHETE",
			"WEAPON_SWITCHBLADE", "WEAPON_BATTLEAXE", "WEAPON_POOLCUE", "WEAPON_WRENCH", "WEAPON_FLASHLIGHT",

			"WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
			"WEAPON_HEAVYSHOTGUN", "WEAPON_DBSHOTGUN", "WEAPON_AUTOSHOTGUN",

			"WEAPON_RPG", "WEAPON_HOMINGLAUNCHER", "WEAPON_FIREWORK", "WEAPON_MINIGUN",
			"WEAPON_GRENADELAUNCHER", "WEAPON_COMPACTLAUNCHER", "WEAPON_RAILGUN",

			"WEAPON_GRENADE", "WEAPON_PIPEBOMB", "WEAPON_STICKYBOMB", "WEAPON_PROXMINE", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
			"WEAPON_MOLOTOV", "WEAPON_FLARE", "WEAPON_SNOWBALL",
			"WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN"
		}};
		// May not exist: "WEAPON_GRENADELAUNCHER_SMOKE", "WEAPON_SWEEPER"

		static constexpr std::array<hasher, 21> vehicle_weapons {{
			"VEHICLE_WEAPON_ROTORS", "VEHICLE_WEAPON_TANK", "VEHICLE_WEAPON_SPACE_ROCKET",
			"VEHICLE_WEAPON_PLANE_ROCKET", "VEHICLE_WEAPON_PLAYER_LAZER", "VEHICLE_WEAPON_PLAYER_LASER",
			"VEHICLE_WEAPON_PLAYER_BULLET", "VEHICLE_WEAPON_PLAYER_BUZZARD", "VEHICLE_WEAPON_PLAYER_HUNTER",
			"VEHICLE_WEAPON_ENEMY_LASER", "VEHICLE_WEAPON_SEARCHLIGHT", "VEHICLE_WEAPON_RADAR",
			"VEHICLE_WEAPON_WATER_CANNON", "VEHICLE_WEAPON_TURRET_INSURGENT", "VEHICLE_WEAPON_TURRET_TECHNICAL",
			"VEHICLE_WEAPON_NOSE_TURRET_VALKYRIE", "VEHICLE_WEAPON_PLAYER_SAVAGE", "VEHICLE_WEAPON_TURRET_LIMO",
			"VEHICLE_WEAPON_CANNON_BLAZER", "VEHICLE_WEAPON_TURRET_BOXVILLE", "VEHICLE_WEAPON_RUINER_BULLET"
		}};

		static constexpr std::array<hasher, 13> weapon_groups {{
			"GROUP_PISTOL", "GROUP_STUNGUN",
			"GROUP_SMG", "GROUP_MG",
			"GROUP_RIFLE",
			"GROUP_SNIPER",
			"GROUP_UNARMED", "GROUP_MELEE",
			"GROUP_SHOTGUN",
			"GROUP_HEAVY",
			"GROUP_THROWN", "GROUP_PETROLCAN", "GROUP_FIREEXTINGUISHER"
		}};

		static constexpr std::array<hasher, 25> ammo_types {{
			"AMMO_PISTOL", "AMMO_STUNGUN", "AMMO_FLAREGUN",
			"AMMO_SMG", "AMMO_MG",
			"AMMO_RIFLE",
			"AMMO_SNIPER",
			"AMMO_SHOTGUN",
			"AMMO_RPG", "AMMO_HOMINGLAUNCHER", "AMMO_FIREWORK", "AMMO_MINIGUN", "AMMO_GRENADELAUNCHER", "AMMO_RAILGUN",
			"AMMO_GRENADE", "AMMO_PIPEBOMB", "AMMO_STICKYBOMB", "AMMO_PROXMINE", "AMMO_SMOKEGRENADE", "AMMO_BZGAS", "AMMO_MOLOTOV", "AMMO_FLARE", "AMMO_SNOWBALL", "AMMO_PETROLCAN", "AMMO_FIREEXTINGUISHER"
		}};
		// May not exist: "AMMO_GRENADELAUNCHER_SMOKE"
	}
}
