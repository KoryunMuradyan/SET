#ifndef __SET__RB__TREE__HPP__
#define __SET__RB__TREE__HPP__

#include <initializer_list>
#include <cassert>
#include <utility>

namespace stl
{
    template <typename T>
    class set 
    {
    	public:
    		using value_type = T;
    		using size_type = std::size_t;
    		enum Colour { RED, BLACK };
    		struct Node
    		{
    			Colour color = RED; // RED->0 BLACK ->1	
    			T data ; 
    			Node* left = nullptr;
    			Node* right = nullptr;
    			Node* parent =  nullptr;
    		};
    	private:
    		Node *root = nullptr;
    		void FreeSpace(Node*);
    		void DeleteTheGivenVal (Node*, set&, T&);
    		void InsertFromGivenNode( Node*, Node*, bool&);
    		void RedDumpDown(Node*);
    		void UncleNullNodeRightchildParentLeftchild(Node*);
    		void UncleNullNodeLeftchildParentLeftchild(Node*);
    		void UncleNullNodeLeftchildParentRightchild(Node*);
    		void UncleNullNodeRightchildParentRightchild(Node*);
    		void UncleBlackNodeREDRightchildParentRedRightchild(Node*);
    		void UncleBlackNodeREDLeftchildParentRedLeftchild(Node*);
    		void UncleBlackNodeREDLeftchildParentRedRightchild(Node*);
    		void UncleBlackNodeREDRightchildParentRedLeftchild(Node*);
    		Node* DefineUncle(Node*);
		void MarginRotate(Node*&);
		void GlobalRotate(Node*&);
    		void insertFix(Node*&);
    		void MakeNull(Node*&);
    		void ColorFix(Node*&);
    		Node*  InOrder (Node*);
    		Node* find_right_more_node(Node*);
    		Node* find_left_more_node(Node*);
    	public:
    		bool shutFreeSpace = false;
    		set()
    		{}
    		// Destructor
    		~set()
    		{	
    			FreeSpace(root);
    		}
    		// Parametrized Constructor
    		set (std::initializer_list<T> _init_list )
    		{
    			for(auto i: _init_list){
    				insert(i);
    			}
    		}
    		void insert(T);
    		void Delete(T);
    		class iterator
    		{
    			private:
    				friend class set<T>;
    				Node* current;
    				iterator (Node* c)
    					: current(c)
    				{}
    			public:
    				value_type& operator* ();
    				iterator& operator++ ();
    				bool operator== (const iterator& o);
    				bool operator!= (const iterator& o);
    				Node* find_left_more_node(Node*);
    				Node* return_to_left_path(Node*);
    		}; // Iterator end
    		
    		iterator begin();
    		iterator end();
    }; // Class end 
} // Namespace end

#endif // __SET__RB__TREE__HPP__
