#include "ChsDaeLoader.h"
#include "ChsMesh.h"
#include "io/ChsFileSystem.h"
#include "ChsUtility.h"
#include "tinyxml2/tinyxml2.h"
#include "platform/ChsOpenGL.h"
#include "ChsIndexBuffer.h"
#include "ChsVertexBuffer.h"
#include <vector>
#include <map>

#define BOOST_NO_CHAR16_T
#define BOOST_NO_CHAR32_T
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

namespace Chaos {
	//----------------------------------------------------------------------------------------------
	template<typename T> void lexicalCastToArray( std::vector<T> & array, std::string stream );
	template<typename DaeInputType> void prepareInput( std::vector<DaeInputType> & inputs, tinyxml2::XMLElement * inputElement );
	//----------------------------------------------------------------------------------------------
	struct DaeParam{
		std::string name;
		std::string type;
	};
	
	//----------------------------------------------------------------------------------------------
	struct DaeAccessor{
		std::string source;
		int count;
		int stride;
		std::vector<DaeParam> param;
		~DaeAccessor( void ){
			this->param.clear();
		}
		void setValue( tinyxml2::XMLElement * accessorElement ){
			this->source = accessorElement->Attribute( "source" );
			this->count = accessorElement->IntAttribute( "count" );
			this->stride = accessorElement->IntAttribute( "stride" );
		}
	};
	
	//----------------------------------------------------------------------------------------------
	struct DaeTechniqueCommon{
		DaeAccessor accessor;
	};

	//----------------------------------------------------------------------------------------------
	struct DaeFloatArray{
		std::string id;
		int count;
		std::vector<float> data;
		~DaeFloatArray( void ){
			this->data.clear();
		}
		void setValue( tinyxml2::XMLElement * arrayElement ){
			this->id = arrayElement->Attribute( "id" );
			this->count = arrayElement->IntAttribute( "count" );
			lexicalCastToArray( this->data, arrayElement->GetText() );
		}
	};
	
	//----------------------------------------------------------------------------------------------
	struct DaeSource{
		std::string id;
		std::string name;
		DaeFloatArray floatArray;
		DaeTechniqueCommon techniqueCommon;
		void setValue( tinyxml2::XMLElement * sourceElement ){
			this->id = sourceElement->Attribute( "id" );
			this->name = sourceElement->Attribute( "name" );
			this->floatArray.setValue( sourceElement->FirstChildElement( "float_array" ) );
			tinyxml2::XMLElement * accessorElement = sourceElement->FirstChildElement( "technique_common" )->FirstChildElement( "accessor" );
			this->techniqueCommon.accessor.setValue( accessorElement );
		}
	};
	
	//----------------------------------------------------------------------------------------------
	typedef struct DaeInput{
		std::string semantic;
		std::string source;
		void setValue( tinyxml2::XMLElement * inputElement ){
			this->semantic = inputElement->Attribute( "semantic" );
			//get source with strip the first char "#"
			this->source = inputElement->Attribute( "source" ) + 1;
		}
	} DaeUnsharedInput;

	//----------------------------------------------------------------------------------------------
	struct DaeSharedInput : DaeInput{
		int offset;
		int set;
		void setValue( tinyxml2::XMLElement * inputElement ){
			DaeUnsharedInput::setValue( inputElement );
			this->offset = inputElement->IntAttribute( "offset" );
			this->set = inputElement->IntAttribute( "set" );
		}
	};
	
	//----------------------------------------------------------------------------------------------
	struct DaeVertices{
		std::string id;
		std::vector<DaeUnsharedInput> input;
		~DaeVertices( void ){
			this->input.clear();
		}
		void setValue( tinyxml2::XMLElement * verticesElement ){
			this->id = verticesElement->Attribute( "id" );
			prepareInput<DaeUnsharedInput>( this->input, verticesElement->FirstChildElement( "input" ) );
		}
	};
	
	//----------------------------------------------------------------------------------------------
	struct DaeTriangles{
		std::string material;
		int count;
		std::vector<DaeSharedInput> input;
		std::vector<int> p;
		~DaeTriangles( void ){
			this->input.clear();
			this->p.clear();
		}
		void setValue( tinyxml2::XMLElement * triangleElement ){
			this->material = triangleElement->Attribute( "material" );
			this->count = triangleElement->IntAttribute( "count" );
			prepareInput<DaeSharedInput>( this->input, triangleElement->FirstChildElement( "input" ) );
			lexicalCastToArray( this->p, triangleElement->FirstChildElement( "p" )->GetText() );
		}
	};
	
	//----------------------------------------------------------------------------------------------
	struct DaeMesh{
		std::map<std::string,DaeSource> sources;
		DaeVertices vertices;
		DaeTriangles triangles;
		~DaeMesh( void ){
			this->sources.clear();
		}
		void setValue( tinyxml2::XMLElement * meshElement ){
			tinyxml2::XMLElement * element = meshElement->FirstChildElement();
			do{
				std::string elementName = element->Name();
				if( !elementName.compare( "source" ) ){
					DaeSource source;
					source.setValue( element );
					this->sources.insert( std::make_pair( source.id, source ) );
				}
				else if(!elementName.compare( "vertices" )){
					this->vertices.setValue( element );
				}
				else if(!elementName.compare( "triangles" )){
					this->triangles.setValue( element );
				}
				element = element->NextSiblingElement();
			}while( element != NULL );
		}
	};

	//----------------------------------------------------------------------------------------------
	template<typename DaeInputType>
	void prepareInput( std::vector<DaeInputType> & inputs, tinyxml2::XMLElement * inputElement ){
		do{
			DaeInputType input;
			input.setValue( inputElement );
			inputs.push_back( input );
			inputElement = inputElement->NextSiblingElement( "input" );
		}while( inputElement != NULL );
	}

	//----------------------------------------------------------------------------------------------
	template<typename T>
	void lexicalCastToArray( std::vector<T> & array, std::string stream ){
		std::string::size_type start = 0;
		std::string::size_type to = stream.find( " " );
		int idx = 0;
		while ( to != std::string::npos ) {
			array.push_back( boost::lexical_cast<T>( stream.substr( start, to-start ) ) );
			idx++;
			start = ++to;
			to = stream.find( " ", to );
		}
		//last one
		array.push_back( boost::lexical_cast<T>( stream.substr( start, stream.length() - start ) ) );
	}

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
				vertexIndex.push_back( idx );
			}
			int index = 0;
			std::map<std::string, int>::iterator iter = vertexLookupList.find( key );
			if( iter == vertexLookupList.end() ){
				//this is a new vertex,it will add into last of vertex list
				index = vertexIndexList.size() / vertexComponentCount;
				for( int inputIndex = 0; inputIndex < vertexComponentCount; inputIndex++ )
					vertexIndexList.push_back( vertexIndex[inputIndex] );//store all vertex component index
				//save this vertex into lookup table
				vertexLookupList.insert( std::make_pair( key, index) );
			}
			else{
				//this vertex was exist in vertex list,
				//just use it`s index
				index = iter->second;
			}
			triangleList.push_back( index );
		}
		vertexLookupList.clear();
	}
	
	//----------------------------------------------------------------------------------------------
	ChsMesh * ChsDaeLoader::load( std::string filename ){
		
		char * file = (char *)ChsFileSystem::sharedInstance()->readFileAsRaw( filename.c_str() );
		if( file == NULL ){
			printf( "has no contents in xml file, or not found this file" );
			return NULL;
		}
		
		tinyxml2::XMLDocument doc;
		int ret = doc.Parse( file );
		safeDelete( &file );
		if( tinyxml2::XML_NO_ERROR != ret ){
			doc.PrintError();//get some error
			return NULL;
		}
		
		ChsMesh * mesh = NULL;
		tinyxml2::XMLElement * geometryElement = doc.FirstChildElement( "COLLADA" )
														->FirstChildElement( "library_geometries" )
														->FirstChildElement( "geometry" );
		
		do{
			tinyxml2::XMLElement * meshElement = geometryElement->FirstChildElement( "mesh" );
			DaeMesh daeMesh;
			daeMesh.setValue( meshElement );
			
			std::vector<int> vertexIndexList;//store vertex index, include position normal and etc..
			std::vector<unsigned short> triangleList;
			reduceTriangleListAndVertexIndexList( daeMesh, vertexIndexList, triangleList );
			
			mesh = new ChsMesh();
			
			//get size of vertex array, need calculate all components of vertex
			//looking for components from triangle inputs
			std::vector<float> vertexArray;
			int vertexComponentCount = daeMesh.triangles.input.size();
			float ** vertexArrayList = new float*[vertexComponentCount];
			int *strideList = new int[vertexComponentCount];
			for( int componentIndex = 0; componentIndex < vertexComponentCount; componentIndex++ ){
				DaeSharedInput input = daeMesh.triangles.input[componentIndex];
				std::string sourceId = input.source;
				std::string semantic = input.semantic;
				if( !semantic.compare( "VERTEX" ) ){
					//from verteices
					for( int i = 0; i< daeMesh.vertices.input.size(); i++ ){
						if( !daeMesh.vertices.input[i].semantic.compare( "POSITION" )){
							sourceId = daeMesh.vertices.input[0].source;
							semantic = daeMesh.vertices.input[0].semantic;
							break;							
						}
					}
				}
				boost::to_lower( semantic );
				std::map<std::string,DaeSource>::iterator iter =  daeMesh.sources.find( sourceId );
				if( iter != daeMesh.sources.end() ){
					const DaeSource & source = iter->second;
					bool isNormalized = false;
					int stride = source.techniqueCommon.accessor.stride;
					if( !semantic.compare( "normal" ) )
						isNormalized = true;//normal data is normalized
					if( !semantic.compare( "texcoord" ) )
						semantic += boost::lexical_cast<std::string>( input.set );
					mesh->vertexBuffer->addAttrib( stride, GL_FLOAT, isNormalized, semantic );
					vertexArrayList[input.offset] = ( float * )source.floatArray.data.data();
					strideList[input.offset] = stride;
				}
			}
			
			std::vector<float> vertexList;
			for( int i = 0; i < vertexIndexList.size(); i += vertexComponentCount ){
				for( int component = 0; component < vertexComponentCount; component++ ){
	 				int index = vertexIndexList[i+component];
					int stride = strideList[component];
					float * componentArray = vertexArrayList[component];
					for( int k = 0; k < stride; k++ )
						vertexList.push_back( componentArray[index*stride + k] );
				}
			}
			
			mesh->vertexBuffer->setData( vertexList.data(), vertexList.size() * sizeof(float) );
			mesh->indexBuffer->setData( triangleList.data(), triangleList.size() , GL_UNSIGNED_SHORT, GL_TRIANGLES );

			vertexList.clear();
			vertexIndexList.clear();
			triangleList.clear();
			geometryElement = geometryElement->NextSiblingElement();
		}while( geometryElement != NULL );
		return mesh;
	}

	//----------------------------------------------------------------------------------------------
	
}
