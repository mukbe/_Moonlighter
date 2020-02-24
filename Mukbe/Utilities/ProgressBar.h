#pragma once

class ProgressBar
{
public:
	ProgressBar();
	~ProgressBar();

	//void Init(string back, string front, float max, FloatRect area);

	//void Update(float current);
	//void Render();
private:
	shared_ptr<Texture> back;
	shared_ptr<Texture> front;

	float valueMax;
	float current;
	FloatRect rc;
};

