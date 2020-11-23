#include "FrameworkPCH.h"

#include "MyMemory.h"
#include "CPPList.h"
#include "Utility/Helpers.h"

enum class NewType
{
    NotSet,
	Regular,
	Array,
    Max,
};

#undef new

class MemObject : public CPPListNode
{
public:
    char* m_file;
    unsigned long m_line;
    NewType m_type;

    MemObject() :
        m_file(0),
        m_line(0),
        m_type(NewType::NotSet)
    {
    }
};

CPPListHead g_Allocations;

void MyMemory_ValidateAllocations(bool AssertOnAnyAllocation)
{
    fw::OutputMessage( "Memory Leaks \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/\n" );

    bool somethingLeaked = false;

    CPPListNode* pNode;
    for( pNode = g_Allocations.HeadNode.Next; pNode->Next; pNode = pNode->Next )
    {
        MemObject* obj = (MemObject*)pNode;
        assert( obj->m_type < NewType::Max );
        assert( obj->Next != NULL );
        assert( obj->Prev != NULL );

        fw::OutputMessage( "%s(%d): Memory unreleased.\n", obj->m_file, obj->m_line );

        somethingLeaked = true;
    }

    fw::OutputMessage( "Memory Leaks ^^^^^^^^^^^^^^^^^^^^^^^\n" );

    if( AssertOnAnyAllocation && somethingLeaked )
        assert( false );
}

void* operator new(size_t size, char* file, unsigned long line)
{
    MemObject* mo = (MemObject*)malloc( size + sizeof(MemObject) );
    mo->m_file = file;
    mo->m_line = line;
    mo->m_type = NewType::Regular;
    g_Allocations.AddTail( mo );

    return ((char*)mo) + sizeof(MemObject);
}

void* operator new[](size_t size, char* file, unsigned long line)
{
    MemObject* mo = (MemObject*)malloc( size + sizeof(MemObject) );
    mo->m_file = file;
    mo->m_line = line;
    mo->m_type = NewType::Array;
    g_Allocations.AddTail( mo );

    return ((char*)mo) + sizeof( MemObject );
}

void operator delete(void* m, char* file, unsigned long line)
{
    delete (char*)m;
}

void operator delete[](void* m, char* file, unsigned long line)
{
    delete (char*)m;
}




void* operator new(size_t size)
{
    assert( size > 0 );

    MemObject* mo = (MemObject*)malloc( size + sizeof(MemObject) );
    mo->m_file = 0;
    mo->m_line = 0;
    mo->m_type = NewType::Regular;
    g_Allocations.AddTail( mo );

    return ((char*)mo) + sizeof( MemObject );
}

void* operator new[](size_t size)
{
    MemObject* mo = (MemObject*)malloc( size + sizeof(MemObject) );
    mo->m_file = 0;
    mo->m_line = 0;
    mo->m_type = NewType::Array;
    g_Allocations.AddTail( mo );

    return ((char*)mo) + sizeof( MemObject );
}

void operator delete(void* m)
{
    if( m == nullptr )
        return;

    MemObject* mo = (MemObject*)(((char*)m) - sizeof(MemObject));
    assert( mo->m_type == NewType::Regular );
    mo->Remove();

    free( mo );
}

void operator delete[](void* m)
{
    if( m == nullptr )
        return;

    MemObject* mo = (MemObject*)( ((char*)m) - sizeof(MemObject) );
    assert( mo->m_type == NewType::Array );
    mo->Remove();

    free( mo );
}
