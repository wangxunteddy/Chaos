#ifndef _CHS_INDEXBUFFER_H
#define _CHS_INDEXBUFFER_H
#pragma once

namespace Chaos {

//--------------------------------------------------------------------------------------------------------------------------------------------
class ChsIndexBuffer {
public:
    ChsIndexBuffer( void );
    ~ChsIndexBuffer( void );
    void setData( const void * triangles, int count, int type, int mode );
    void draw( void );
private:
    unsigned int handle;
    int mode;
    int count;
    int type;
	int size;
	char * triangles;
	bool isNeedUpdate;
};

//--------------------------------------------------------------------------------------------------------------------------------------------
}//namespaces
#endif//_CHS_INDEXBUFFER_H
