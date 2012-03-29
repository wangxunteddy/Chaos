#ifndef _CHS_DAE_H
#define _CHS_DAE_H

#define BOOST_NO_CHAR16_T
#define BOOST_NO_CHAR32_T
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

#include <tinyxml2.h>
#include <vector>
#include <string>
#include <map>

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
	std::vector<std::string> rs;
	boost::split( rs, stream, boost::is_any_of("\n ") );
	BOOST_FOREACH( const std::string & str, rs){
		if(!str.empty())
			array.push_back( boost::lexical_cast<T>( str ) );
	}
}

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
	//std::vector<DaeParam> param; //not use yet
	~DaeAccessor( void ){
		//this->param.clear();
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


#endif
