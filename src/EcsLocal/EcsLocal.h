#ifndef _EcsLocal_EcsLocal_h_
#define _EcsLocal_EcsLocal_h_


#include <EcsLib/EcsLib.h>
#include <Geometry/Geometry.h>
#include <DesktopSuite/DesktopSuite.h>

#include "CommonComponents.h"
#include "Viewport.h"
#include "EasingSystem.h"
#include "PaintStrokeSystem.h"
#include "InteractionSystem.h"
#include "ToolboxSystem.h"
#include "ToolSystem.h"
#include "Player.h"
#include "PhysicsSystem.h"
#include "PaintingSystem.h"
#include "ShootingSystem.h"
#include "ThrowingSystem.h"
#include "Prefabs.h"
#include "DesktopSystem.h"


NAMESPACE_ECS_BEGIN

template <class T> void DefaultCreate() {Ecs::GetActiveEngine().Get<EntityStore>()->GetRoot()->Create<T>();}
template <class T> void DefaultCreateOnStart() {Ecs::Engine::WhenPreFirstUpdate << callback(DefaultCreate<T>);}

NAMESPACE_ECS_END


NAMESPACE_TOPSIDE_BEGIN

void BindEcsToSerial();

NAMESPACE_TOPSIDE_END


#endif
