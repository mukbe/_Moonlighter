#pragma once
class TownScene : public SceneBase
{
public:
	TownScene();
	~TownScene();
	virtual void Init();
	virtual void OnceInit();
	virtual void Update(float tick);
	void Load();

};

