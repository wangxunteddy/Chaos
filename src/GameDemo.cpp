#include "GameDemo.h"
#include "ChsEntity.h"
#include "ChsResourceManager.h"
#include "ChsRenderSystem.h"
#include "geometry/ChsPlane.h"
#include "ChsMaterial.h"
#include "ChsShaderProgram.h"
#include "camera/ChsCameraBase.h"
#include "math/ChsMath.h"

//--------------------------------------------------------------------------------------------------
using namespace Chaos;
#include <math.h>

GameDemo game;
ChsCameraBase camera;
static float transY = 0.0f;
ChsMaterial * material;
//--------------------------------------------------------------------------------------------------
void GameDemo::onInit( void ) {
	ChsEntityManager * resMgr = ChsResourceManager::sharedEntityManager();
	ChsEntity * plane = resMgr->getEntity( "planeEntity" );
	ChsPlane * planeMesh = new ChsPlane(1.0f,1.0f);
	planeMesh->setMaterial();
	material = planeMesh->getMaterial();
	material->hasVertexColor(true);
	
	plane->add( planeMesh );
	this->renderer()->root()->add( plane->name(), plane );
	ChsRect viewport = this->renderer()->getViewPort();
	camera.perspective( degree2Radian(90), viewport.w/(float)viewport.h, 0.1f, 100.0f  );
	camera.lookAt( 0,0,-2,0,0,0 );
	this->renderer()->currentCamera( &camera );
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onUpdate( void ) {
	transY += 0.075f;
	float alpha = sin(transY);
	camera.moveTo( cos(transY), 0, sin(transY));
	alpha = alpha >=0 ? alpha : -alpha;
	material->alpha(alpha);
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onShutdown( void ) {
}
