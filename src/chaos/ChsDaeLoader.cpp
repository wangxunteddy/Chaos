#include <boost/assign.hpp>
using namespace boost::assign;
#include <boost/scoped_array.hpp>

#include "ChsDae.h"
#include "ChsDaeLoader.h"
#include "ChsModel.h"
#include "ChsMesh.h"
#include "io/ChsFileSystem.h"
#include "ChsUtility.h"
#include "tinyxml2/tinyxml2.h"
#include "platform/ChsOpenGL.h"
#include "ChsIndexBuffer.h"
#include "ChsVertexBuffer.h"

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	void reduceTriangleListAndVertexIndexList( DaeMesh & daeMesh, std::vector<int> & vertexIndexList, std::vector<unsigned short> & triangleList );
	void reduceTriangleListAndVertexIndexList( DaeMesh & daeMesh, std::vector<int> & vertexIndexList, std::vector<unsigned short> & triangleList ){
		int triangleIndexCount = daeMesh.triangles.p.size();
		int vertexComponentCount = daeMesh.triangles.input.size();
		std::map<std::string, int> vertexLookupList;//store vertex whitch be use,
		std::vector<int> vertexIndex;
		for( int triangleIndex = 0; triangleIndex < triangleIndexCount; triangleIndex += vertexComponentCount ){
			std::string key = "";
			vertexIndex.clear();
			//make a pair: key is string of the index, for looking, value is vertex`s component index
			for( int inputIndex = 0; inputIndex < vertexComponentCount; inputIndex++ ){
				int idx = daeMesh.triangles.p[triangleIndex + inputIndex];
				key += boost::lexical_cast<std::string>( idx );
				vertexIndex += idx;
			}
			int index = 0;
			auto iter = vertexLookupList.find( key );
			if( iter == vertexLookupList.end() ){
				//this is a new vertex,it will add into last of vertex list
				index = vertexIndexList.size() / vertexComponentCount;
				for( int inputIndex = 0; inputIndex < vertexComponentCount; inputIndex++ )
					vertexIndexList += vertexIndex[inputIndex];//store all vertex component index
				//save this vertex into lookup table
				insert( vertexLookupList ) ( key, index );
			}
			else{
				//this vertex was exist in vertex list,
				//just use it`s index
				index = iter->second;
			}
			triangleList += index;
		}
		vertexLookupList.clear();
	}
	
	//----------------------------------------------------------------------------------------------

	void vertexInputRedirection( const DaeMesh & daeMesh, DaeSharedInput & input );
	void vertexInputRedirection( const DaeMesh & daeMesh, DaeSharedInput & input ){
		if( input.semantic.compare( "VERTEX" ) )
			return;
		//from verteices
		BOOST_FOREACH( const DaeUnsharedInput & vertexInput, daeMesh.vertices.input ){
			if( !vertexInput.semantic.compare( "POSITION" )){
				input.source = vertexInput.source;
				input.semantic = vertexInput.semantic;
				return;							
			}
		}
	}

	//----------------------------------------------------------------------------------------------
	struct VertexAttribute{
		std::string name;
		const float * array;
		int stride;
	};
	typedef boost::scoped_array<VertexAttribute> VertexAttributePtr;
	//----------------------------------------------------------------------------------------------
	void makeVertexList( const std::vector<int> & vertexIndexList, std::vector<float> & vertexList, 
						int vertexAttributeCount, const VertexAttributePtr & VertexAttributes );
	
	void makeVertexList( const std::vector<int> & vertexIndexList, std::vector<float> & vertexList, 
						int vertexAttributeCount, const VertexAttributePtr & VertexAttributes ){
		int vertexIndexCount = vertexIndexList.size();
		for( int vertexIndex = 0; vertexIndex < vertexIndexCount; vertexIndex += vertexAttributeCount ){
			for( int attribute = 0; attribute < vertexAttributeCount; attribute++ ){
				int index = vertexIndexList[vertexIndex+attribute];
				int stride = VertexAttributes[attribute].stride;
				const float * array = VertexAttributes[attribute].array;
				for( int i = 0; i < stride; i++ )
					vertexList += array[index*stride + i];
			}
		}
	}
	
	//----------------------------------------------------------------------------------------------
	void makeVertexAttributes( DaeMesh & daeMesh, const VertexAttributePtr & vertexAttributes );
	
	void makeVertexAttributes( DaeMesh & daeMesh, const VertexAttributePtr & vertexAttributes ){
		std::vector<DaeSharedInput> & inputs = daeMesh.triangles.input;
		BOOST_FOREACH( DaeSharedInput & input , inputs ){
			vertexInputRedirection( daeMesh, input );
			std::string sourceId = input.source;
			std::string semantic = input.semantic;
			boost::to_lower( semantic );
			auto iter = daeMesh.sources.find( sourceId );
			if( iter != daeMesh.sources.end() ){
				const DaeSource & source = iter->second;
				if( input.set >= 0 )
					semantic += boost::lexical_cast<std::string>( input.set );
				vertexAttributes[input.offset].name = semantic;
				vertexAttributes[input.offset].array = source.floatArray.data.data();
				vertexAttributes[input.offset].stride = source.techniqueCommon.accessor.stride;
			}
		}
	}
	
	//----------------------------------------------------------------------------------------------
	ChsModel * ChsDaeLoader::load( const char * filename ){
		char * fileData;
		ChsFileSystem::sharedInstance()->readFileAsUTF8( filename, &fileData );
		if( fileData == NULL ){
			printf( "has no contents in xml file, or not found this file" );
			return NULL;
		}
		
		boost::scoped_array<char> fileDataPtr( fileData );
		tinyxml2::XMLDocument doc;
		int ret = doc.Parse( fileDataPtr.get() );
		if( tinyxml2::XML_NO_ERROR != ret ){
			printf( "errorStr1:%s\n", doc.GetErrorStr1() );
			printf( "errorStr2:%s\n", doc.GetErrorStr2() );
			doc.PrintError();//get some error
			return NULL;
		}
		
		ChsModel * model = new ChsModel( filename );
		tinyxml2::XMLElement * geometryElement = doc.FirstChildElement( "COLLADA" )
													->FirstChildElement( "library_geometries" )
													->FirstChildElement( "geometry" );
		
		std::vector<int> vertexIndexList;//store vertex index, include position normal and etc..
		std::vector<float> vertexList;//store all vertex infomation, 
		std::vector<unsigned short> triangleList;
		tinyxml2::XMLElement * meshElement;
		do{
			meshElement = geometryElement->FirstChildElement( "mesh" );
			std::string meshName = geometryElement->Attribute( "id" );
			DaeMesh daeMesh;
			daeMesh.setValue( meshElement );
			reduceTriangleListAndVertexIndexList( daeMesh, vertexIndexList, triangleList );
			int vertexAttributeCount = daeMesh.triangles.input.size();
			VertexAttributePtr vertexAttributes( new VertexAttribute [vertexAttributeCount] );
			makeVertexAttributes( daeMesh, vertexAttributes );
			makeVertexList( vertexIndexList, vertexList, vertexAttributeCount, vertexAttributes );
			vertexIndexList.clear();
			boost::shared_ptr<ChsMesh> mesh( new ChsMesh( meshName ) );
			for( int i = 0; i < vertexAttributeCount ; i++ ){
				const VertexAttribute & attribute = vertexAttributes[i];
				bool isNormalized = attribute.name.compare( "normal" ) ? false : true;
				mesh->vertexBuffer->addAttrib( attribute.stride, GL_FLOAT, isNormalized, attribute.name );
			}
			mesh->vertexBuffer->setData( vertexList );
			vertexList.clear();
			mesh->indexBuffer->setData( triangleList );
			triangleList.clear();
			mesh->indexBuffer->mode( GL_TRIANGLES );
			mesh->setMaterial();
			
			model->addMesh( mesh );
			geometryElement = geometryElement->NextSiblingElement();
		}while( geometryElement != NULL );
		return model;
	}

	//----------------------------------------------------------------------------------------------
	
}
