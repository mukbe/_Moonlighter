#include "Mukbe.h"
#include "BufferManager.h"

#include "./Render/WorldBuffer.h"

SingletonCpp(BufferManager)

BufferManager::BufferManager()
{
}


BufferManager::~BufferManager()
{
	ShaderBufferIter iter = bufferContainer.begin();

	for (; iter != bufferContainer.end(); ++iter)
	{
		SafeDelete(iter->second);
	}

	bufferContainer.clear();
}

void BufferManager::Init()
{
	this->bufferContainer.insert(make_pair(WorldBuffer::GetCode(), new WorldBuffer));
}
