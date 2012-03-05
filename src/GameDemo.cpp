#include "GameDemo.h"
#include "ChsEntity.h"
#include "ChsResourceManager.h"
#include "ChsRenderSystem.h"
#include "geometry/ChsPlane.h"
#include "ChsMaterial.h"
#include "ChsShaderProgram.h"

//--------------------------------------------------------------------------------------------------
using namespace Chaos;
#include <math.h>

GameDemo game;
static float transY = 0.0f;
ChsMaterial * material;
//--------------------------------------------------------------------------------------------------
void GameDemo::onInit( void ) {
	ChsEntityManager * resMgr = ChsResourceManager::sharedEntityManager();
	ChsEntity * plane = resMgr->getEntity( "planeEntity" );
	ChsPlane * planeMesh = new ChsPlane(1.0f,1.0f);
	planeMesh->setMaterial();
	material = planeMesh->getMaterial();
	//material->registerUniform("translate", (void *)&transY, CHS_UNIFORM_1_FLOAT,1);
	material->hasVertexColor(true);
	
	plane->add( planeMesh );
	this->renderer()->root()->add( plane->name(), plane );
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onUpdate( void ) {
	transY += 0.075f;
	float alpha = sin(transY);
	alpha = alpha >=0 ? alpha : -alpha;
	material->alpha(alpha);
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onShutdown( void ) {
}
