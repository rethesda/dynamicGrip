#pragma once
#include <SimpleIni.h>
#include "SKSEMenuFramework.h"
#include "Configuration.h"
namespace UI {
    void Register();
	void LoadSettings(const char* a_section);
	void SaveSettings();

    namespace Settings {
		inline std::string checkBoxTrue = "\t" + FontAwesome::UnicodeToUtf8(0xf00c);
		inline std::string checkBoxFalse = "\t" + FontAwesome::UnicodeToUtf8(0xf00d);

        void __stdcall Render();
        void __stdcall OnEvent(SKSEMenuFramework::Model::EventType eventType);

	}
};