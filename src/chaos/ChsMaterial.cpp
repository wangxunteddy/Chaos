#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "ChsResourceManager.h"
#include "ChsTexture2D.h"
#include "ChsRenderStates.h"

namespace Chaos {
	
	//----------------------------------------------------------------------------------------------
	ChsMaterial::ChsMaterial( void ) {
		this->shaderUniformSet.reset();
		
		//this->_hasVertexColor = false;
		this->shaderUniformSet.add( "hasVertexColor", CHS_SHADER_UNIFORM_1_INT, 1);
		this->setProperty( "hasVertexColor", false );
		
		//this->_hasTexture = false;
		this->shaderUniformSet.add( "hasTexture", CHS_SHADER_UNIFORM_1_INT, 1);
		this->setProperty( "hasTexture", false );
		
		//this->_alpha = 1.0f;
		this->shaderUniformSet.add( "alpha", CHS_SHADER_UNIFORM_1_FLOAT, 1);
		this->setProperty( "alpha", 1.0 );

		this->textures.clear();
		
		this->setRenderState( CHS_RS_DEPTH_TEST, CHS_RS_ENABLE );
	}

	//----------------------------------------------------------------------------------------------
	ChsMaterial::~ChsMaterial( void ) {
		this->textures.clear();
		this->shaderUniformSet.reset();
	}

	//----------------------------------------------------------------------------------------------
	void ChsMaterial::addTexture( boost::shared_ptr<ChsTexture2D> texture ){
		if( !texture )
			return;
		this->setProperty( "hasTexture", true );
		this->shaderUniformSet.add( texture->sampleName(), CHS_SHADER_UNIFORM_1_INT, 1);
		this->setProperty( texture->sampleName(), texture->activeUnit() );
		this->textures += texture;
	}
	
	//----------------------------------------------------------------------------------------------
	ChsShaderProgram * ChsMaterial::apply( ChsShaderProgram * sysProgram ) {
		ChsShaderProgram * currentProgram = sysProgram;
		if( !this->_shaderProgram.expired() || currentProgram ){
			if( !this->_shaderProgram.expired() ){
				currentProgram = this->_shaderProgram.lock().get();
				if( currentProgram != sysProgram ){
//					printf( "use new program\n" );
					currentProgram->use();
				}
				else{
//					printf( "use last program\n" );
				}
			}
			std::pair<ChsRenderState,unsigned int> p;
			BOOST_FOREACH( p, this->renderStates ){
				ChsRenderStates::sharedInstance()->set( p.first,p.second );
			}
			
			this->shaderUniformSet.apply( currentProgram );
			bool hasTexture = this->getProperty<bool>( "hasTexture" );
			ChsRSTexture2D( hasTexture );
			if( hasTexture ){
				BOOST_FOREACH( boost::shared_ptr<ChsTexture2D> & texture, this->textures )
					texture->bind();
			}
		}
		return currentProgram;
	}

	//----------------------------------------------------------------------------------------------
	#if 0
	void ChsMaterial::validate( void ) {
	// Validate program before drawing. This is a good check, but only really necessary in a debug build.
	// DEBUG macro must be defined in your debug configurations if that's not already the case.
    	if ( this->shaderProgram && !this->shaderProgram->validate() ) 
           printf("Failed to validate program: %d", this->shaderProgram->handle() );
	}
	#endif

	//----------------------------------------------------------------------------------------------
	void ChsMaterial::setShader( std::string vshName, std::string fshName ){
		this->_shaderProgram = ChsResourceManager::sharedInstance()->getShaderProgram( vshName, fshName );
	}

	//----------------------------------------------------------------------------------------------
	void ChsMaterial::linkShader( void ){
		if( !this->_shaderProgram.expired() ){
			boost::shared_ptr<ChsShaderProgram> shaderProgram = this->_shaderProgram.lock();
			shaderProgram->link();
		}
	}

	//----------------------------------------------------------------------------------------------
	void ChsMaterial::setRenderState( ChsRenderState state, unsigned int value ){
		auto iter = this->renderStates.find( state );
		if( iter != this->renderStates.end() ){
			this->renderStates[state] = value;
		}
		else{
			insert( this->renderStates )( state, value );
		}
	}
}//namespace
