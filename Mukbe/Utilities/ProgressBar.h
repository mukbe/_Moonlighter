#pragma once

class ProgressBar
{
public:
	ProgressBar();
	~ProgressBar();

	void Init(float max, FloatRect area, float round, bool isPlayer);
	void SetCurrentValue(float value);

	void Update();
	void Render(Matrix2D* trans);
private:

	float valueMax;
	float currentValue;
	float backValue;
	FloatRect rc;
	FloatRect backRc;
	FloatRect frontRc;
	float round;

	D3DXCOLOR color;
	D3DXCOLOR normalColor = D3DXCOLOR(0.9f, 0.278f, 0.278f, 1.f);
	float alpha;
	float frameAlpha;
	bool bChanged;
	bool bPlayer;
	float shownTime;
	float show;
	float deltaTime;
	float lerp;
};

