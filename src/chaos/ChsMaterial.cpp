#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

#include "ChsMaterial.h"
#include "shader/ChsShaderProgram.h"
#include "ChsResourceManager.h"
#include "ChsTexture2D.h"
#include "ChsRenderStates.h"

namespace Chaos {
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::ChsMaterial( void ) {
		this->_hasVertexColor = false;
		this->shaderUniforms.add( "hasVertexColor", &(this->_hasVertexColor), CHS_SHADER_UNIFORM_1_INT, 1);
		
		this->_hasTexture = false;
		this->shaderUniforms.add( "hasTexture", &(this->_hasTexture), CHS_SHADER_UNIFORM_1_INT, 1);
		
		this->_alpha = 1.0f;
		this->shaderUniforms.add( "alpha", &(this->_alpha), CHS_SHADER_UNIFORM_1_FLOAT, 1);

		this->_textureCount = 1;
		
		this->textures.clear();
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	ChsMaterial::~ChsMaterial( void ) {
		this->textures.clear();
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::addTexture( boost::shared_ptr<ChsTexture2D> texture ){
		if( !texture )
			return;
		this->hasTexture( true );
		this->shaderUniforms.add( texture->sampleName(), CHS_SHADER_UNIFORM_1_INT, (int[]){texture->activeUnit()} );
		this->textures += texture;
	}
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
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
			this->shaderUniforms.apply( currentProgram );
			ChsRSTexture2D( this->hasTexture() );
			if( this->hasTexture() ){
				BOOST_FOREACH( boost::shared_ptr<ChsTexture2D> & texture, this->textures )
					texture->bind();
			}
		}
		return currentProgram;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	#if 0
	void ChsMaterial::validate( void ) {
	// Validate program before drawing. This is a good check, but only really necessary in a debug build.
	// DEBUG macro must be defined in your debug configurations if that's not already the case.
    	if ( this->shaderProgram && !this->shaderProgram->validate() ) 
           printf("Failed to validate program: %d", this->shaderProgram->handle() );
	}
	#endif

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::setShader( std::string vshName, std::string fshName ){
		this->_shaderProgram = ChsResourceManager::sharedInstance()->getShaderProgram( vshName, fshName );
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------
	void ChsMaterial::linkShader( void ){
		if( !this->_shaderProgram.expired() ){
			boost::shared_ptr<ChsShaderProgram> shaderProgram = this->_shaderProgram.lock();
			shaderProgram->link();
		}
	}
	
}//namespace
