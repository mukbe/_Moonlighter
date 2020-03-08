#pragma once
#include "./Utilities/Logging.h"

//Manager
#include "./System/Keyboard.h"
#include "./System/Mouse.h"
#include "./System/Time.h"
#include "./System/Manage/SoundManager.h"
#include "./System/Message/DataContext.h"
#include "./System/SceneBase.h"
#include "./System/Manage/MessageManager.h"
#include "./System/Manage/SceneManager.h"
#include "./System/Manage/ObjectManager.h"
#include "./System/Manage/RenderManager.h"
#include "./Utilities/Matrix2D.h"
#include "./Utilities/Matrix2x2.h"

#include "./Render/ComputeShader/ComputeResource.h"
#include "./Render/ComputeShader/ComputeShader.h"
#include "./Render/BufferManager.h"
#include "./Render/VertexLayout.h"
#include "./Render/States.h"
#include "./Render/ShaderBuffer.h"
#include "./Render/Shader.h"
#include "./Render/ShaderManager.h"
#include "./Render/Texture.h"
#include "./Render/ImageManager.h"
#include "./Render/RenderTargetBuffer.h"

#include "./System/Manage/EffectManager.h"

#include "./View/CameraManager.h"

#include "./Utilities/Line.h"
#include "./Utilities/Math.h"
#include "./Utilities/Json.h"
#include "./Utilities/BinaryFile.h"
#include "./Utilities/String.h"
#include "./Utilities/Path.h"
#include "./Utilities/Buffer.h"
#include "./Utilities/Animation.h"
#include "./Utilities/Animator.h"
#include "./Utilities/ProgressBar.h"

#define KeyCode Keyboard::Get()
#define GameMouse Mouse::Get()
#define DeltaTime Time::Delta()
#define TickTime Time::Tick()
