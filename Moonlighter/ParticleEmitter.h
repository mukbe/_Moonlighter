#pragma once

class ParticleEmitter : public GameObject
{
	ClassInherited(GameObject)

public:
	ParticleEmitter(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~ParticleEmitter();

protected:

};

