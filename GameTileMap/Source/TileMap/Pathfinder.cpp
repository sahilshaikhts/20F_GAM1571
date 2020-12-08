#include "GamePCH.h"
#include <assert.h>
#include <float.h>
#include <math.h>

#include "TileMap.h"
#include "Pathfinder.h"

Pathfinder::Pathfinder(TileMap* pTileMap, int width, int height)
{
    m_pTileMap = pTileMap;

    m_NumNodes = width * height;

    m_Nodes = new PathNode[m_NumNodes];
    m_OpenNodes = new int[m_NumNodes];

    m_MapWidth = width;
    m_MapHeight = height;

    Reset();
}
    
Pathfinder::~Pathfinder()
{
    delete[] m_Nodes;
    delete[] m_OpenNodes;
}

void Pathfinder::Reset()
{
    m_NumOpen = 0;

    for( int i=0; i<m_NumNodes; i++ )
    {
        m_Nodes[i].parentNodeIndex = -1;
        m_Nodes[i].status = PathNode::Unchecked;

        m_Nodes[i].f = 0;
        m_Nodes[i].g = FLT_MAX; // Set G to be highest cost possible, so any comparison will be better.
        m_Nodes[i].h = -1; // -1 indicates the heuristic hasn't been calculated yet.
    }
}
        
bool Pathfinder::FindPath(int sx, int sy, int ex, int ey)
{
    // Reset the pathfinder.
    Reset();

    // Get the starting tile index and the destination tile index.
    int currentNodeIndex = CalculateNodeIndex( sx, sy );
    int endNodeIndex = CalculateNodeIndex( ex, ey );

    // Set starting node cost to zero.
    m_Nodes[currentNodeIndex].g = 0;
    
    // Add start node to open list.
    AddToOpen( currentNodeIndex );

    while( true )
    {
        // Find the node with the lowest score.
        currentNodeIndex = FindNodeIndexWithLowestFInOpen();

        // Remove it from the open list.
        RemoveFromOpen( currentNodeIndex );

        // If we found the end node, we're done. Return.
        if( currentNodeIndex == endNodeIndex )
            return true;

        // Mark the node as closed.
        m_Nodes[currentNodeIndex].status = PathNode::Closed;

        // Add neighbours to open list.
        AddNeighboursToOpenList( currentNodeIndex, endNodeIndex );

        // If we're out of nodes to check, then we're done without finding the end node.
        if( m_NumOpen == 0 )
            return false;
    }

    // This shouldn't happen, we should either find the destination or run out of nodes in the open list.
    assert( false );
    return false;
}

int Pathfinder::GetPath(int* path, int maxdistance, int ex, int ey)
{
    int nodeIndex = CalculateNodeIndex( ex, ey );

    int length = 0;
    while( true )
    {
        if( path != nullptr && length >= maxdistance )
            return -1; // Path didn't fit in size.

        if( path != nullptr ) // If no path array is passed in, just get the length.
            path[length] = nodeIndex;
        length++;

        nodeIndex = m_Nodes[nodeIndex].parentNodeIndex;

        if( nodeIndex == -1 )
            return length;
    }

    // There should be no way to get here.
    assert( false );
    return -1;
}

void Pathfinder::AddToOpen(int nodeindex)
{
    assert( m_Nodes[nodeindex].status != PathNode::Closed );

    // If the node isn't already open, then add it to the list.
    if( m_Nodes[nodeindex].status != PathNode::Open )
    {
        m_OpenNodes[m_NumOpen] = nodeindex;
        m_NumOpen++;
        m_Nodes[nodeindex].status = PathNode::Open;
    }
}

void Pathfinder::RemoveFromOpen(int nodeindex)
{
    // Remove the node from the open list, since we don't care about order, replace the node we're removing with the last node in list.
    for( int i=0; i<m_NumOpen; i++ )
    {
        if( m_OpenNodes[i] == nodeindex )
        {
            m_NumOpen--;
            m_OpenNodes[i] = m_OpenNodes[m_NumOpen];
            return;
        }
    }
}

int Pathfinder::FindNodeIndexWithLowestFInOpen()
{
    float lowestF = FLT_MAX;
    int lowestIndex = -1;

    for( int i=0; i<m_NumOpen; i++ )
    {
        int tileIndex = m_OpenNodes[i];

        if( m_Nodes[tileIndex].f < lowestF )
        {
            lowestF = m_Nodes[tileIndex].f;
            lowestIndex = tileIndex;
        }
    }

    return lowestIndex;
}

int Pathfinder::CalculateNodeIndex(int tx, int ty)
{
    assert( tx >= 0 && tx < m_MapWidth &&
            ty >= 0 && ty < m_MapHeight );

    // Calculate the node index based on the tiles x/y.
    return ty*m_MapWidth + tx;
}

int Pathfinder::CheckIfNodeIsClearAndReturnNodeIndex(int tx, int ty)
{
    if( tx < 0 || ty < 0 || tx >= m_MapWidth || ty >= m_MapHeight )
        return -1;

    int nodeIndex = CalculateNodeIndex( tx, ty );

    // If the node is already closed, return -1 (an invalid tile index).
    if( m_Nodes[nodeIndex].status == PathNode::Closed )
        return -1;
        
    // If the node can't be walked on, return -1 (an invalid tile index).
    if( m_pTileMap->IsWalkable( tx, ty ) == false )
        return -1;

    // Return a valid tile index.
    return nodeIndex;
}

void Pathfinder::AddNeighboursToOpenList(int nodeIndex, int endNodeIndex)
{
    // Calculate the tile x/y based on the nodeIndex.
    int tx = nodeIndex % m_MapWidth;
    int ty = nodeIndex / m_MapWidth;

    // Fill an array with the four neighbour tile indices. (use CheckIfNodeIsClearAndReturnNodeIndex() for each to see if it's valid).
    int neighbours[4] = { -1, -1, -1, -1 };
    neighbours[0] = CheckIfNodeIsClearAndReturnNodeIndex( tx, ty+1 ); // 10 + width
    neighbours[1] = CheckIfNodeIsClearAndReturnNodeIndex( tx+1, ty ); // 10 + 1
    neighbours[2] = CheckIfNodeIsClearAndReturnNodeIndex( tx, ty-1 ); // 10 - width
    neighbours[3] = CheckIfNodeIsClearAndReturnNodeIndex( tx-1, ty ); // 10 - 1

    // Loop through the array.
    for( int i=0; i<4; i++ )
    {
        int nodeToAdd;
        nodeToAdd = neighbours[i];

        // Check if the node to add has a valid node index.
        if( nodeToAdd != -1 )
        {
            AddToOpen( nodeToAdd );

            int cost = 1; // Assume a travel cost of 1 for each tile.

            // Calculate a new G cost.
            float newG = m_Nodes[nodeIndex].g + cost;

            // If the new cost is less than the previous cost, then overwrite the values.
            if( newG < m_Nodes[nodeToAdd].g )
            {
                // Set the parent node.
                m_Nodes[nodeToAdd].parentNodeIndex = nodeIndex;

                // If we haven't already calculated the heuristic, calculate it.
                if( m_Nodes[nodeToAdd].h == -1 )
                    m_Nodes[nodeToAdd].h = CalculateH( nodeToAdd, endNodeIndex );

                m_Nodes[nodeToAdd].g = newG;
                m_Nodes[nodeToAdd].f = m_Nodes[nodeToAdd].g + m_Nodes[nodeToAdd].h;
            }
        }
    }
}

float Pathfinder::CalculateH(int nodeIndex1, int nodeIndex2)
{
    // Calculate the h score using the Manhatten distance (absolute diff in x + absolute diff in y).
    int tx1 = nodeIndex1 % m_MapWidth;
    int ty1 = nodeIndex1 / m_MapWidth;

    int tx2 = nodeIndex2 % m_MapWidth;
    int ty2 = nodeIndex2 / m_MapWidth;

    return (float)abs( tx1 - tx2 ) + abs( tx1 - tx2 );
}
