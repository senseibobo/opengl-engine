#include "Text.h"

void Text::SetText(std::string newText)
{
	this->text = newText;
}

std::string Text::GetText() const
{
	return text;
}

void Text::Draw() const
{
	Rect2 rect = GetRect();
	float width = 0.0f, height = 100.05f;
	for (int i = 0; i < text.size(); i++)
	{
		width += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);
	}
	glPushMatrix();
	glTranslatef(rect.position.x - width*0.6*0.5, rect.position.y - height*0.6*0.5, 0);
	glLineWidth(8.0f);
	glScalef(0.6, 0.6, 0.6);
	for (int i = 0; i < text.size(); i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	}
	glPopMatrix();
}
