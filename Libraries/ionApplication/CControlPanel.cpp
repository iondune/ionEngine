
#include "CControlPanel.h"

#include <ionGUI.h>


namespace ion
{

	void CControlPanel::AddComponent(IControlComponent * component)
	{
		Components.push_back(component);
	}

	void CControlPanel::Display()
	{
		if (! IsVisible)
		{
			return;
		}

		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
		if (ImGui::Begin("ionEngine"))
		{
			for (IControlComponent * component : Components)
			{
				string s = component->GetName();

				if (ImGui::Button(s.c_str()))
				{
					ToggleBool(component->IsOpen);
				}
			}
		}
		ImGui::End();

		for (IControlComponent * component : Components)
		{
			if (component->IsOpen)
			{
				string s = "ionEngine :: "s + component->GetName();

				if (ImGui::Begin(s.c_str()))
				{
					component->DrawGUIControls();
				}
				ImGui::End();
			}
		}
	}

}
