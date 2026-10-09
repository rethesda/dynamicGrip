#include "UI.h"

const char* dxKbNames[] = {
	"[NONE]",
	"Escape", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
	"Minus", "Equals", "Backspace", "Tab",
	"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
	"Left Bracket", "Right Bracket", "Enter",
	"Left Control", "A", "S", "D", "F", "G", "H", "J", "K", "L",
	"Semicolon", "Apostrophe", "~ (Console)", "Left Shift", "Back Slash",
	"Z", "X", "C", "V", "B", "N", "M",
	"Comma", "Period", "Forward Slash", "Right Shift",
	"NUM*", "Left Alt", "Spacebar", "Caps Lock",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10",
	"Num Lock", "Scroll Lock",
	"NUM7", "NUM8", "NUM9", "NUM-", "NUM4", "NUM5", "NUM6", "NUM+",
	"NUM1", "NUM2", "NUM3", "NUM0", "NUM.",
	"F11", "F12",
	"NUM Enter", "Right Control",
	"NUM/",
	"SysRq / PtrScr", "Right Alt",
	"Pause",
	"Home", "Up Arrow", "PgUp", "Left Arrow", "Right Arrow", "End", "Down Arrow", "PgDown",
	"Insert", "Delete",
	"Left Mouse Button", "Right Mouse Button", "Middle/Wheel Mouse Button",
	"Mouse Button 3", "Mouse Button 4", "Mouse Button 5",
	"Mouse Button 6", "Mouse Button 7", "Mouse Wheel Up", "Mouse Wheel Down"
};

const std::uint32_t dxKbValues[] = {
	0,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
	12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
	26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43,
	44, 45, 46, 47, 48, 49, 50,
	51, 52, 53, 54,
	55, 56, 57, 58,
	59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
	69, 70,
	71, 72, 73, 74, 75, 76, 77, 78,
	79, 80, 81, 82, 83,
	87, 88,
	156, 157,
	181,
	183, 184,
	197,
	199, 200, 201, 203, 205, 207, 208, 209,
	210, 211,
	256, 257, 258,
	259, 260, 261,
	262, 263, 264, 265
};

const char* dxGpNames[] = {
	"[NONE]",
	"DPAD UP", "DPAD DOWN", "DPAD LEFT", "DPAD RIGHT",
	"START", "BACK",
	"LEFT THUMB", "RIGHT THUMB",
	"LEFT SHOULDER", "RIGHT SHOULDER",
	"A", "B", "X", "Y",
	"LT", "RT"
};

static int FindComboIndex(const std::uint32_t* a_values, std::size_t a_count, std::uint32_t a_current)
{
	for (std::size_t i = 0; i < a_count; ++i) {
		if (a_values[i] == a_current) return static_cast<int>(i);
	}
	return -1;
}
/*
const std::uint32_t dxGpValues[] = {
	0,
	0x1, 0x2, 0x4, 0x8,
	0x10, 0x20,
	0x40, 0x80,
	0x100, 0x200,
	0x1000, 0x2000,	0x4000, 0x8000,
	0x9, 0xa
};
*/

const std::uint32_t dxGpValues[] = {
	0,
	266, 267, 268, 269,
	270, 271,
	272, 273,
	274, 275,
	276, 277, 278, 279,
	280, 281
};

void UI::Register() {
    if (!SKSEMenuFramework::IsInstalled()) {
        return;
    }
    SKSEMenuFramework::SetSection("DynamicGrip");
    SKSEMenuFramework::AddSectionItem("Settings", Settings::Render);
	SKSEMenuFramework::AddEvent(UI::Settings::OnEvent, 0);
}

void UI::LoadSettings(const char* a_section) {
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(Configuration::Settings::iniFilePath.c_str());

	Configuration::Settings::iKeyboardKey = (uint16_t)ini.GetDoubleValue(a_section, "iKeyboardKey", 34);
	Configuration::Settings::iKeyboardModifier = (uint16_t)ini.GetDoubleValue(a_section, "iKeyboardModifier", 0);
	Configuration::Settings::iGamePadKey = (uint16_t)ini.GetDoubleValue(a_section, "iGamePadKey", 9);		//LT
	Configuration::Settings::iGamePadMod = (uint16_t)ini.GetDoubleValue(a_section, "iGamePadMod", 4096);  //A

	auto s = (char*)ini.GetValue(a_section, "sRequiredPerk1H", "");
	Configuration::Settings::sRequiredPerk1H = new char[strlen(s) + 1];
	memcpy(Configuration::Settings::sRequiredPerk1H, s, strlen(s) + 1);

	s = (char*)ini.GetValue(a_section, "sRequiredPerk2H", "");
	Configuration::Settings::sRequiredPerk2H = new char[strlen(s) + 1];
	memcpy(Configuration::Settings::sRequiredPerk2H, s, strlen(s) + 1);

	Configuration::Settings::bPlaySounds = (uint16_t)ini.GetBoolValue(a_section, "bPlaySounds", true);
	Configuration::Settings::bEnableNPC = (uint16_t)ini.GetBoolValue(a_section, "bEnableNPC", false);
	Configuration::Settings::bMeleeStaffEnchants = (uint16_t)ini.GetBoolValue(a_section, "bMeleeStaffEnchants", false);

	Configuration::Settings::fMeleeStaffDamage = (float)ini.GetDoubleValue(a_section, "fMeleeStaffDamage", 13);
	Configuration::Settings::fMeleeStaffSpeed = (float)ini.GetDoubleValue(a_section, "fMeleeStaffSpeed", 1.6);
}

void UI::SaveSettings() {
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(Configuration::Settings::iniFilePath.c_str());
    
	ini.SetDoubleValue("Settings", "iKeyboardKey", Configuration::Settings::iKeyboardKey);
	ini.SetDoubleValue("Settings", "iKeyboardModifier", Configuration::Settings::iKeyboardModifier);
	ini.SetDoubleValue("Settings", "iGamePadKey", Configuration::Settings::iGamePadKey);
	ini.SetDoubleValue("Settings", "iGamePadMod", Configuration::Settings::iGamePadMod);
	ini.SetValue("Settings", "sRequiredPerk1H", Configuration::Settings::sRequiredPerk1H);
	ini.SetValue("Settings", "sRequiredPerk2H", Configuration::Settings::sRequiredPerk2H);
	ini.SetBoolValue("Settings", "bPlaySounds", Configuration::Settings::bPlaySounds);
	ini.SetBoolValue("Settings", "bEnableNPC", Configuration::Settings::bEnableNPC);
	ini.SetBoolValue("Settings", "bMeleeStaffEnchants", Configuration::Settings::bMeleeStaffEnchants);
	ini.SetDoubleValue("Settings", "fMeleeStaffDamage", Configuration::Settings::fMeleeStaffDamage);
	ini.SetDoubleValue("Settings", "fMeleeStaffSpeed", Configuration::Settings::fMeleeStaffSpeed);

    ini.SaveFile(Configuration::Settings::iniFilePath.c_str());
}

void UI::Settings::Render() {
	ImGuiMCP::Checkbox("Play Sounds", &Configuration::Settings::bPlaySounds);
	ImGuiMCP::Checkbox("Support for NPCs", &Configuration::Settings::bEnableNPC);

	ImGuiMCP::Spacing();
    ImGuiMCP::Text("Keybinds:");

	constexpr auto kbComboCount = std::size(dxKbValues);
	ImGuiMCP::SetNextItemWidth(ImGuiMCP::GetWindowWidth() * 0.4f);
	int kbIdx = FindComboIndex(dxKbValues, kbComboCount, Configuration::Settings::iKeyboardKey);
	if (kbIdx < 0) kbIdx = 0;
	if (ImGuiMCP::Combo("Keyboard Key", &kbIdx, dxKbNames, static_cast<int>(kbComboCount))) {
		Configuration::Settings::iKeyboardKey = dxKbValues[kbIdx];
	}

	constexpr auto kbmComboCount = std::size(dxKbValues);
	ImGuiMCP::SetNextItemWidth(ImGuiMCP::GetWindowWidth() * 0.4f);
	int kbmIdx = FindComboIndex(dxKbValues, kbmComboCount, Configuration::Settings::iKeyboardModifier);
	if (kbmIdx < 0) kbmIdx = 0;
	if (ImGuiMCP::Combo("Keyboard Modifier", &kbmIdx, dxKbNames, static_cast<int>(kbmComboCount))) {
		Configuration::Settings::iKeyboardModifier = dxKbValues[kbmIdx];
	}

	constexpr auto gpComboCount = std::size(dxGpValues);
	ImGuiMCP::SetNextItemWidth(ImGuiMCP::GetWindowWidth() * 0.4f);
	int gpIdx = FindComboIndex(dxGpValues, gpComboCount, Configuration::Settings::iGamePadKey);
	if (gpIdx < 0) gpIdx = 0;
	if (ImGuiMCP::Combo("Gamepad Key", &gpIdx, dxGpNames, static_cast<int>(gpComboCount))) {
		Configuration::Settings::iGamePadKey = dxGpValues[gpIdx];
	}

	constexpr auto gpmComboCount = std::size(dxGpValues);
	ImGuiMCP::SetNextItemWidth(ImGuiMCP::GetWindowWidth() * 0.4f);
	int gpmIdx = FindComboIndex(dxGpValues, gpmComboCount, Configuration::Settings::iGamePadMod);
	if (gpmIdx < 0) gpmIdx = 0;
	if (ImGuiMCP::Combo("Gamepad Modifier", &gpmIdx, dxGpNames, static_cast<int>(gpmComboCount))) {
		Configuration::Settings::iGamePadMod = dxGpValues[gpmIdx];
	}

	ImGuiMCP::Spacing();
	ImGuiMCP::Text("Perks:");
	ImGuiMCP::SetNextItemWidth(ImGuiMCP::GetWindowWidth() * 0.4f);
	ImGuiMCP::InputText("Required Perk 1H", Configuration::Settings::sRequiredPerk1H, 256);
	if (Configuration::Settings::sRequiredPerk1H)
	{
		Configuration::Settings::reqPerk1H = RE::TESForm::LookupByEditorID<RE::BGSPerk>(Configuration::Settings::sRequiredPerk1H);
		ImGuiMCP::SameLine();
		FontAwesome::PushBrands();
		if (Configuration::Settings::reqPerk1H)
			ImGuiMCP::Text(checkBoxTrue.c_str());
		else
			ImGuiMCP::Text(checkBoxFalse.c_str());
		FontAwesome::Pop();
	}

	ImGuiMCP::SetNextItemWidth(ImGuiMCP::GetWindowWidth() * 0.4f);
	ImGuiMCP::InputText("Required Perk 2H", Configuration::Settings::sRequiredPerk2H, 256);
	if (Configuration::Settings::sRequiredPerk2H)
	{
		Configuration::Settings::reqPerk2H = RE::TESForm::LookupByEditorID<RE::BGSPerk>(Configuration::Settings::sRequiredPerk2H);
		ImGuiMCP::SameLine();
		FontAwesome::PushBrands();
		if(Configuration::Settings::reqPerk2H)
			ImGuiMCP::Text(checkBoxTrue.c_str());
		else
			ImGuiMCP::Text(checkBoxFalse.c_str());
		FontAwesome::Pop();
	}

	ImGuiMCP::Spacing();
	ImGuiMCP::Text("Melee Staff:");
	ImGuiMCP::Checkbox("Enable Melee Staff Enchants", &Configuration::Settings::bMeleeStaffEnchants);
	ImGuiMCP::SliderFloat("Staff Damage", &Configuration::Settings::fMeleeStaffDamage, 0.0f, 100.0f);
	ImGuiMCP::SliderFloat("Staff Speed", &Configuration::Settings::fMeleeStaffSpeed, 0.0f, 10.0f);

}

void __stdcall UI::Settings::OnEvent(SKSEMenuFramework::Model::EventType eventType) {
    if (SKSEMenuFramework::Model::EventType::kCloseMenu == eventType) {
        UI::SaveSettings();
    }
}
