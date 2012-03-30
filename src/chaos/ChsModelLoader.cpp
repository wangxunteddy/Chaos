#include "tinyxml2/tinyxml2.h"
#include "ChsModelLoader.h"
#include "ChsModel.h"
#include "ChsMesh.h"
#include "ChsIndexBuffer.h"
#include "ChsVertexBuffer.h"
#include "io/ChsFileSystem.h"
#include "ChsResourceManager.h"
#include "ChsUtility.h"
#include "ChsMaterial.h"
#include "ChsTexture2D.h"
//--------------------------------------------------------------------------------------------------
namespace Chaos {
	//----------------------------------------------------------------------------------------------
	template<typename T>
	T readData( char ** data ){
		T value = *(reinterpret_cast<T*>(*data));
		skipData( data, sizeof(T) );
		return value;
	}
	
	//----------------------------------------------------------------------------------------------
	std::string readString( char ** data );
	std::string readString( char ** data ){
		int strCount = readData<int>( data );
		boost::scoped_ptr<char> p( new char[strCount+1] );
		memset( p.get(), 0, strCount+1 );
		memcpy( p.get(), *data, strCount );
		std::string str = p.get();
		skipData( data, strCount );
		return str;
	}
	
	//----------------------------------------------------------------------------------------------
	ChsModel * ChsModelLoader::loadAsXML( const char *filename ){
		char * data;
		ChsFileSystem::sharedInstance()->readFileAsUTF8( filename, &data );
		boost::scoped_ptr<char> modelData( data );
		tinyxml2::XMLDocument doc;
		int ret = doc.Parse( data );
		if( tinyxml2::XML_NO_ERROR != ret ){
			printf( "errorStr1:%s\n", doc.GetErrorStr1() );
			printf( "errorStr2:%s\n", doc.GetErrorStr2() );
			doc.PrintError();//get some error
			return NULL;
		}
		
		ChsModel * model = NULL;
		tinyxml2::XMLElement * modelElement = doc.FirstChildElement( "ChsModel" );
		if( !modelElement ){
			printf( "there no model elements\n" );
			return NULL;
		}
		
		std::string modelName = modelElement->Attribute( "name" );
		model = new ChsModel( modelName );
		tinyxml2::XMLElement * meshElement = modelElement->FirstChildElement( "ChsMesh" );
		while( meshElement ){
			std::string meshName = meshElement->Attribute( "name" );
			boost::shared_ptr<ChsMesh> mesh( new ChsMesh( meshName ) );
			
			tinyxml2::XMLElement * attrElement = meshElement->FirstChildElement( "ChsAttribute" );
			while ( attrElement ) {
				std::string attrName = attrElement->Attribute( "name" );
				int stride = attrElement->IntAttribute( "stride" );
				bool isNormalized = false;
				if( !attrName.compare( "normal" ) )
					isNormalized = true;
				mesh->vertexBuffer->addAttrib( stride, GL_FLOAT, isNormalized, attrName );
				attrElement = attrElement->NextSiblingElement( "ChsAttribute" );
			}
			
			std::vector<float> vertices;
			lexicalCastToArray( vertices, meshElement->FirstChildElement( "ChsVertexBuffer" )->GetText() );
			mesh->vertexBuffer->setData( vertices );
			vertices.clear();
			std::vector<unsigned short> indeices;
			lexicalCastToArray( indeices, meshElement->FirstChildElement( "ChsIndexBuffer" )->GetText() );
			mesh->indexBuffer->setData( indeices );
			indeices.clear();
			mesh->indexBuffer->mode( GL_TRIANGLES );
			
			tinyxml2::XMLElement * materialElement = meshElement->FirstChildElement( "ChsMaterial" );
			if( materialElement ){
				ChsMaterial * material = new ChsMaterial();
				std::string vsName = materialElement->FirstChildElement( "ChsVertexShader" )->Attribute( "src" );
				std::string fsName = materialElement->FirstChildElement( "ChsFragmentShader" )->Attribute( "src" );
				material->setShader( vsName, fsName );
				tinyxml2::XMLElement * textureElement = materialElement->FirstChildElement( "ChsTexture" );
				while( textureElement ){
					std::string textureFileName = textureElement->Attribute( "src" );
					boost::shared_ptr<ChsTexture2D> texture = ChsResourceManager::sharedInstance()->getTexture2D( textureFileName );
					texture->sampleName( textureElement->Attribute( "sampleName" ) );
					texture->activeUnit( textureElement->IntAttribute( "activeUnit" ) );
					material->addTexture( texture );
					textureElement = textureElement->NextSiblingElement( "ChsTexture");
				}
				mesh->setMaterial( material );
			}

			model->addMesh( mesh );
			meshElement = meshElement->NextSiblingElement( "ChsMesh" );
		}
		
		return model;
	}
	
	//----------------------------------------------------------------------------------------------
	ChsModel * ChsModelLoader::loadAsBinary( const char *filename ){
		char * data;
		ChsFileSystem::sharedInstance()->readFileAsRaw( filename, &data );
		boost::scoped_ptr<char> modelData( data );
		if( data[0] != 'c' || data[1] != 'h'||data[2] != 'm' || data[3] != 'o' ){
			printf( "this is not chsmodel file" );
			return NULL;
		}
		readData<int>( &data );//skip magic number
		std::string modelName = readString( &data );
		ChsModel * model = new ChsModel( modelName );
		int meshCount = readData<int>( &data );
		for( int meshIdx = 0; meshIdx < meshCount; meshIdx++ ){
			std::string meshName = readString( &data );
			boost::shared_ptr<ChsMesh> mesh( new ChsMesh( meshName ) );
			int attriCount = readData<int>( &data );
			for( int attrIdx = 0; attrIdx < attriCount; attrIdx++ ){
				std::string attrName = readString( &data );
				int stride = readData<int>( &data );
				bool isNormalized = false;
				if( !attrName.compare( "normal" ) )
					isNormalized = true;
				mesh->vertexBuffer->addAttrib( stride, GL_FLOAT, isNormalized, attrName );
			}
			int count = readData<int>( &data );
			mesh->vertexBuffer->setData( data, count*sizeof(float) );
			skipData( &data, count*sizeof(float) );
			count = readData<int>( &data );
			mesh->indexBuffer->setData( data, count );	
			skipData( &data, count*sizeof(unsigned short) );
			mesh->indexBuffer->mode( GL_TRIANGLES );
			ChsMaterial * material = new ChsMaterial();
			material->setShader( "Shader.vsh", "Shader.fsh" );
			mesh->setMaterial( material );
			model->addMesh( mesh );
		}
		return model;
	}
	
	//----------------------------------------------------------------------------------------------
	ChsModel * ChsModelLoader::load( const char *filename ){
		std::string fileName = filename;
		if( fileName.find( ".chsmodelx" ) != std::string::npos )
			return this->loadAsXML( filename );
		else 
			return this->loadAsBinary( filename );
	}
}
