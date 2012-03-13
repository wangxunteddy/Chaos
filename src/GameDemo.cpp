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
ChsPlane * planeMesh1;
ChsPlane * planeMesh2;
ChsPlane * planeMesh3;
//--------------------------------------------------------------------------------------------------
void GameDemo::onInit( void ) {
	ChsEntityManager * resMgr = ChsResourceManager::sharedEntityManager();
	ChsEntity * plane1 = resMgr->getEntity( "planeEntity1" );
	ChsEntity * plane2 = resMgr->getEntity( "planeEntity2" );
	ChsEntity * plane3 = resMgr->getEntity( "planeEntity3" );

	planeMesh1 = new ChsPlane(4.0f,1.0f);
	planeMesh2 = new ChsPlane(2.0f,2.0f);
	planeMesh3 = new ChsPlane(3.0f,3.0f);
	
	planeMesh1->setMaterial();
	material = planeMesh1->getMaterial();
	material->hasVertexColor(false);
	planeMesh2->setMaterial();
	material = planeMesh2->getMaterial();
	material->hasVertexColor(true);
	planeMesh3->setMaterial();
	material = planeMesh3->getMaterial();
	material->hasVertexColor(true);

	
	plane1->add( planeMesh1 );
	plane2->add( planeMesh2 );
	plane3->add( planeMesh3 );
	
	//this->renderer()->root()->add( plane3->name(), plane3 );
	this->renderer()->root()->add( plane2->name(), plane2 );
	//this->renderer()->root()->add( plane1->name(), plane1 );
	
	ChsRect viewport = this->renderer()->getViewPort();
	camera.perspective( degree2Radian(60), viewport.w/(float)viewport.h, 0.001f, 1000.0f  );
	camera.lookAt( 0,20,0,0,0,0 );
	this->renderer()->currentCamera( &camera );
	this->renderer()->showDebugCoordinate( true );
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onUpdate( void ) {
	transY += 0.0075f;
	float alpha = sin(transY);
	camera.moveTo( cos(transY)*3, 2, sin(transY)*3);
	alpha = alpha >=0 ? alpha : -alpha;
	material = planeMesh2->getMaterial();
	material->alpha(alpha);
	material = planeMesh3->getMaterial();
	material->alpha(1.0f-alpha);
	
}

//--------------------------------------------------------------------------------------------------
void GameDemo::onShutdown( void ) {
}
