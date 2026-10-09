#pragma once
namespace Configuration {
    namespace Settings {

		inline std::string iniFilePath = "Data/SKSE/Plugins/dynamicGrip.ini";

		inline int iKeyboardKey = 34;
		inline int iKeyboardModifier = 0;
		inline int iGamePadKey = 9;
		inline int iGamePadMod = 4096;
		inline char* sRequiredPerk1H;
		inline char* sRequiredPerk2H;
		inline bool bPlaySounds = true;
		inline bool bEnableNPC = false;
		inline bool bMeleeStaffEnchants = false;
		inline float fMeleeStaffDamage = 13.0f;
		inline float fMeleeStaffSpeed = 1.6f;

		inline RE::BGSPerk* reqPerk1H;
		inline RE::BGSPerk* reqPerk2H;
    }
};