#include "GameDemo.h"
#include "ChsEntity.h"
#include "ChsResourceManager.h"
#include "ChsRenderSystem.h"
#include "geometry/ChsPlane.h"
#include "ChsMaterial.h"
#include "ChsShaderProgram.h"

//--------------------------------------------------------------------------------------------------
using namespace Chaos;

GameDemo game;
static float transY = 0.0f;
//--------------------------------------------------------------------------------------------------
void GameDemo::onInit( void ) {
	ChsEntityManager * resMgr = ChsResourceManager::sharedEntityManager();
	ChsEntity * plane = resMgr->getEntity( "planeEntity" );
	ChsPlane * planeMesh = new ChsPlane(1.0f,1.0f);
	planeMesh->setMaterial();
	ChsMaterial * material = planeMesh->getMaterial();
	material->connectUniform("translate", (void *)&transY, CHS_UNIFORM_1_FLOAT,1);
	material->hasVertexColor(true);
	plane->add("planeMesh", planeMesh);
	this->render()->root()->add( "planeEntity", plane );
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onUpdate( void ) {
	transY += 0.075f;
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onShutdown( void ) {
}
