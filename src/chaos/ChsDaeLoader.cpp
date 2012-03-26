#define BOOST_NO_CHAR16_T
#define BOOST_NO_CHAR32_T
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;
#include <boost/algorithm/string/split.hpp>
#include <boost/scoped_array.hpp>


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
		DaeFloatArray floatArray;
		DaeTechniqueCommon techniqueCommon;
		void setValue( tinyxml2::XMLElement * sourceElement ){
			this->id = sourceElement->Attribute( "id" );
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
			this->set = -1;
			inputElement->QueryIntAttribute( "set", &(this->set) );
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
					insert( this-> sources ) ( source.id, source );
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
			inputs += input;
			inputElement = inputElement->NextSiblingElement( "input" );
		}while( inputElement != NULL );
	}

	//----------------------------------------------------------------------------------------------
	template<typename T>
	void lexicalCastToArray( std::vector<T> & array, std::string stream ){
		std::vector<std::string> rs;
		boost::split( rs, stream, boost::is_any_of("\n ") );
		BOOST_FOREACH( const std::string & str, rs)
			if(!str.empty())
				array += boost::lexical_cast<T>( str );
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
			DaeMesh daeMesh;
			daeMesh.setValue( meshElement );
			reduceTriangleListAndVertexIndexList( daeMesh, vertexIndexList, triangleList );
			int vertexAttributeCount = daeMesh.triangles.input.size();
			VertexAttributePtr vertexAttributes( new VertexAttribute [vertexAttributeCount] );
			makeVertexAttributes( daeMesh, vertexAttributes );
			makeVertexList( vertexIndexList, vertexList, vertexAttributeCount, vertexAttributes );
			vertexIndexList.clear();
			boost::shared_ptr<ChsMesh> mesh( new ChsMesh() );
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
