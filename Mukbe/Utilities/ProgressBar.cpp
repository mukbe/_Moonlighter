#include "Mukbe.h"
#include "ProgressBar.h"


ProgressBar::ProgressBar()
{
}


ProgressBar::~ProgressBar()
{
}

void ProgressBar::Init(float max, FloatRect area,float round, bool isPlayer)
{
	this->round = round;
	bChanged = false;
	bPlayer = isPlayer;
	valueMax = max;
	rc =frontRc = backRc = area;
	currentValue = backValue = max;
	shownTime = 0.3f;
	deltaTime = 0.5f;
	alpha = 0.f;
	color = normalColor;
}

void ProgressBar::SetCurrentValue(float value)
{
	float delta = value - currentValue;

	if (Math::FloatEqual(delta,0.f) == false)
	{
		currentValue += delta;
		float ratio = delta / valueMax;
		float size = rc.right - rc.left;
		frontRc.right += size * ratio;
		bChanged = true;
		show = shownTime;
		lerp = 0.f;
		alpha = 1.f;
		frameAlpha = 0.4;
		color.r = color.g = color.b = 1.f;
	}
}

void ProgressBar::Update()
{
	if (bPlayer)
	{
		
		if (bChanged)
		{
			show -= TickTime;
			if (show <= 0.f)
			{
				lerp += TickTime;
				float ratio = lerp / deltaTime;
				color.r = Math::Lerp(color.r, normalColor.r, ratio);
				color.g = Math::Lerp(color.g, normalColor.g, ratio);
				color.b = Math::Lerp(color.b, normalColor.b, ratio);

				if (ratio > 1.f)
				{
					color = normalColor;
					bChanged = false;
					lerp = 0.f;
				}

			}

		}
	}
	else
	{
		if (bChanged)
		{
			show -= TickTime;
			if (show <= 0.f)
			{
				lerp += TickTime;
				float ratio = lerp / deltaTime;
				backRc.right = Math::Lerp(backRc.right, frontRc.right, ratio);
				if (ratio > 1.f)
				{
					backRc.right = Math::Lerp(backRc.right, frontRc.right, 1.f);
					bChanged = false;
					lerp = 0.f;
				}

			}
		}
		else
		{
			alpha > 0.f ? alpha -= 0.01f : 0.f;
			frameAlpha > 0.f ? frameAlpha -= 0.004f : 0.f;			
		}


	}
	
}

void ProgressBar::Render(Matrix2D * trans)
{
	if (bPlayer)
	{
		p2DRenderer->FillRoundedRectangle(rc, round, trans,D3DXCOLOR(0.733f,0.643f,0.466f,1.f));
		p2DRenderer->FillRoundedRectangle(frontRc, round, trans, color);

	}
	else
	{
		p2DRenderer->FillRoundedRectangle(rc, round, trans, D3DXCOLOR(0.733f, 0.643f, 0.466f, frameAlpha));
		p2DRenderer->FillRoundedRectangle(backRc, round, trans, D2D1::ColorF::White, alpha);
		p2DRenderer->FillRoundedRectangle(frontRc, round, trans, D3DXCOLOR(0.9f, 0.278f, 0.278f, alpha));

	}






}
