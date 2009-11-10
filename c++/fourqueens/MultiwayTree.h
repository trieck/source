#pragma once

template <class T>
class MultiwayTree
{
public:
	MultiwayTree(uint32_t way) : nway(way), nnodes(0) {		
	}

	~MultiwayTree() {
	}

	struct Node {
		Node(uint32_t way, const T & o) 
			: nway(way), object(o) {
			nodes = new Node*[nway];
			memset(nodes, 0, sizeof(Node*) * nway);
		}
		Node(const Node &rhs) {
			*this = rhs;
		}

		~Node() {
			delete [] nodes;
		}

		Node &operator = (const Node &rhs) {
			if (this != &rhs) {
				delete [] nodes;
				object = rhs.object;
				nodes = new Node*[nway = rhs.nway];
				memcpy(nodes, rhs.nodes, sizeof(Node*) * nway);
			}
			return *this;
		}

		Node **nodes;
		uint32_t nway;
		T object;
	};

	Node *mkRoot(T object) {
		root = NodePtr(makeNode(object));
		nnodes++;
		return root.get();
	}

	Node *addNode(Node *parent, uint32_t index, T object) {
		Node *node = parent->nodes[index] = makeNode(object);
		nnodes++;
		return node;
	}

	uint32_t size() const { return nnodes; }

	operator Node*() const;
private:
	Node *makeNode(T object) const {
		return new Node(nway, object);
	}

	typedef std::auto_ptr<Node> NodePtr;
	NodePtr root;
	uint32_t nway;
	uint32_t nnodes;
};

template <class T>
inline MultiwayTree<T>::operator Node*() const {
	return root.get();
}

