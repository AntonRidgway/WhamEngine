#ifndef WE_NODE_H
#define WE_NODE_H

#include <vector>
#include "scene/Geometry.h"
#include "scene/Spatial.h"

class Node : public Spatial
{
private:
	Node* parent;
	std::vector<Geometry*> gChildren;
	std::vector<Node*> nChildren;
public:
	Node();
	Node( Node* parent );
	~Node();
	void attachChild( Geometry* c );
	void attachChild( Node* c );
	Spatial* getChild( std::string nodeName );
	Node* getNChild( unsigned int index ) const;
};

#endif