#pragma once
#include "UIComponent.h"
class Text : public UIComponent
{
public:
	void SetText(std::string newText);
	std::string GetText() const;
	void Draw() const override;
private:
	std::string text;
};

