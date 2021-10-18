#ifndef BST_H_
#define BST_H_
/*A binary search tree designed to accomodate two types, with secondary type being used potentially for duplicate handling(identification), and for a hanging value
for data identification in application
*/
template <typename B, typename R>
class BST
{
private:
	B value;
	R val2;
	BST<B, R> *left;
	BST<B, R> *right;
	BST<B, R>* searchBSTParent(const B&, BST<B, R>*);//utility function searches for the parent of first node in tree with value type B specified
	BST<B, R>* changeToLargestLeft(BST<B, R>*);//utility function searches for largest node on left side of specified and restructures with it as root
	BST<B, R>* handleFoundDelete(BST<B, R>*, BST<B, R>*);//utility function handles case of a tbdeleted node found

public:
	BST(const B&, const R&);
	void setValue(const B& dataIn);//sets data
	void setValueSecondary(const R& dataIn);//sets secondary data
	void setLeft(BST<B, R>* nextIn);//sets pointer to left node
	void setRight(BST<B, R>* nextIn);//sets pointer to right node
	B getValue() const;//gets primary, sorted by data value
	R getValueSecondary() const;//gets secondary, nonsorted value
	BST<B, R>* getLeft() const;//gets pointer to left node
	BST<B, R>* getRight() const;//gets pointer to right node

	BST<B, R>* add(BST<B, R>*);//add value to tree, should only be called on the head node
	BST<B, R>* deleteValue(const B&, const R&);
	BST<B, R>* modifyBST(const B&, const R&, BST<B, R>*);
	BST<B, R>* searchBST(const B&);//searches tree by sorted value, normal bst search complexity, finds first node with specified type value in tree
	BST<B, R>* searchBSTSecondary(const R&);//searches tree by secondary, nonsorted value, O(n), returns first value found(does not work with duplicate secondaries)

};

/*PRE:a private utility function which accepts a target value to search for and a nullptr, used for recursive purposes
  POST:returns the parent BST node to the first node found with target value, if the tree does not contain the value or is consistent of only one node, a nullptr will be returned
*/
template<typename B, typename R>
BST<B, R>* BST<B, R>::searchBSTParent(const B& target, BST<B, R>* parent)
{
	if (target == value)
	{
		return parent;
	}
	else if (target < value)
	{
		if (left == nullptr)
			return nullptr;
		return left->searchBSTParent(target, this);
	}
	else {
		if (right == nullptr)
			return nullptr;
		return right->searchBSTParent(target, this);
	}
}

/*PRE:a private utility function which accepts a target node, assuming left of tree is not empty
  POST:restructures the node around the largest node to the left of entered node
*/
template<typename B, typename R>
BST<B, R>* BST<B, R>::changeToLargestLeft(BST<B, R>* oldRoot)
{
	BST<B, R>* cur = oldRoot->getLeft();
	while (cur->getRight() != nullptr)
	{
		cur = cur->getRight();
	}
	deleteValue(cur->getValue(), cur->getValueSecondary());
	oldRoot->setValue(cur->getValue());
	oldRoot->setValueSecondary(cur->getValueSecondary());
	return cur;
}

/*PRE: a private utility which accepts parent of and node to be deleted
  POST: modifies parent pointer to node to change root, calls changeToLargestLeft if right and left tree exist beneath
*/
template<typename B, typename R>
BST<B, R>* BST<B, R>::handleFoundDelete(BST<B, R>* var, BST<B, R>* parent)
{
	if (var->getLeft() == nullptr)//if no left tree, or if no left or right
	{
		if (parent->getLeft() == var)
		{
			parent->setLeft(parent->getLeft()->getRight());
		}
		else {
			parent->setRight(parent->getRight()->getRight());
		}
		return var;
	}
	else if (var->getRight() == nullptr) {//no right tree
		if (parent->getLeft() == var)//determine which node of parent is being modified
		{
			parent->setLeft(parent->getLeft()->getLeft());
		}
		else {
			parent->setRight(parent->getRight()->getLeft());
		}
		return var;
	}
	else {//if left and right both exist, restructure tree, using largest left node as new root at var
		return changeToLargestLeft(var);
	}
}

/*PRE: basic constructor
  POST: creates object of two generic types
*/
template <typename B, typename R>
BST<B, R>::BST(const B& b, const R& r)
{
	value = b;
	val2 = r;
	left = nullptr;
	right = nullptr;
}

/*PRE:add should not be a nullptr, else an exception wil be thrown
  POST:will add the node referred to in the tree
*/
template <typename B, typename R>
BST<B, R>* BST<B, R>::add(BST<B, R>* add)
{
	if (add->getValue() < value)
	{
		if (left == nullptr) {
			left = add;
		}
		else {
			left->add(add);
		}
	}
	else {
		if (right == nullptr)
		{
			right = add;
		}
		else {
			right->add(add);
		}
	}
	return add;
}

/*PRE: must be called on the portion of tree containing values, it treats the object it's being called by as the root
  POST: will delete a bst node with specified values, if there are duplicates, it will delete the first duplicate found
		it will not delete the root node, must be kept track of manually, as there is no bst handler class
		function does not free dynamic memory, it will return a pointer to the node that is dynamically allocated so it may be freed in main, while the function only restructures tree
		if this function is called on a sub node within the tree that has nothing beneath it, no action is performed
*/
template <typename B, typename R>
BST<B, R>* BST<B, R>::deleteValue(const B& tree1, const R& tree2)
{
	BST<B, R>* var = searchBST(tree1);
	BST<B, R>* parent = searchBSTParent(tree1, nullptr);
	if (var != nullptr) {//if value in tree

		if (var->getValueSecondary() == tree2)//if both fields identical
		{
			if (parent == nullptr)//if this is the root pointer
			{
				if (var->getRight() == nullptr && var->getLeft() == nullptr)//if only root exists, no action will be performed
					return var;
				if (var->getLeft() == nullptr)//if no left tree
				{
					BST<B, R>* del = var->getRight();
					var->setValue(var->getRight()->getValue());
					var->setValueSecondary(var->getRight()->getValueSecondary());
					var->setLeft(var->getRight()->getLeft());
					var->setRight(var->getRight()->getRight());
					return del;//no node needs to be deallocated since property is changed instead
				}
				else if (var->getRight() == nullptr) {//no right tree, but left tree exists
					BST<B, R>* del = var->getLeft();
					var->setValue(var->getLeft()->getValue());
					var->setValueSecondary(var->getLeft()->getValueSecondary());
					var->setRight(var->getLeft()->getRight());
					var->setLeft(var->getLeft()->getLeft());
					return del;//no node needs to be deallocated since property is changed instead
				}
				else {//if left and right both exist, restructure tree, using largest left node as new root at var
					return changeToLargestLeft(var);
				}
			}
			return handleFoundDelete(var, parent);//not root pointer
		}
		else {//second field does not match
			//find new var and parent, if none return false
			BST<B, R>* tempvar = var->getRight();
			BST<B, R>* tempparent = var;
			while (tempvar->getValue() == tree1)//find any duplicates in a row to right
			{
				if (tempvar->getValueSecondary() == tree2)
				{
					return handleFoundDelete(tempvar, tempparent);
				}
				tempparent = tempvar;
				tempvar = tempvar->getRight();
			}//after loop:tempvar does not reference a match, tempparent is a match
			return tempvar->deleteValue(tree1, tree2);//if none in row match second, recursion
		}
	}
	return nullptr;//not found
}

/*Pre:if used on the root node, this function will not restructure tree around a new root, but will instead restructure around the largest node to left and then add in replacement node
  POST:uses deleteValue and add to replace an old node with a new one, may modify placement of a node within the height of a tree
	   if new node is nullptr, exception
*/
template <typename B, typename R>
BST<B, R>* BST<B, R>::modifyBST(const B& b, const R& r, BST<B, R>* newVal)
{
	if (newVal == nullptr)
	{
		throw"cannot add a nullptr to tree";
	}
	else {
		deleteValue(b, r);
		return add(newVal);
	}
}

/*PRE:none
  POST:returns pointer to node with target val, else nullptr
*/
template <typename B, typename R>
BST<B, R>* BST<B, R>::searchBST(const B& target)
{
	if (target == value)
	{
		return this;
	}
	else if (target < value)
	{
		if (left == nullptr)
			return nullptr;
		return left->searchBST(target);
	}
	else {
		if (right == nullptr)
			return nullptr;
		return right->searchBST(target);
	}
}

/*PRE:none
  POST:returns pointer to node with target secondary, else nullptr
*/
template <typename B, typename R>
BST<B, R>* BST<B, R>::searchBSTSecondary(const R& target)
{
	if (target == val2)
	{
		return this;
	}
	else if (left != nullptr && left->searchBSTSecondary(target) != nullptr) {
		return left->searchBSTSecondary(target);
	}
	else if (right != nullptr && right->searchBSTSecondary(target) != nullptr) {
		return right->searchBSTSecondary(target);
	}
	return nullptr;
}

/*PRE: none
  POST: sets pointer to left node
 */
template <typename B, typename R>
void BST<B, R>::setLeft(BST<B, R> *nextNodePtr)
{
	left = nextNodePtr;
}

/*PRE: none
  POST: sets pointer to right node
 */
template <typename B, typename R>
void BST<B, R>::setRight(BST<B, R> *nextNodePtr)
{
	right = nextNodePtr;
}

/*PRE: none
  POST: sets data
 */
template <typename B, typename R>
void BST<B, R>::setValue(const B& dataIn)
{
	value = dataIn;
}

/*PRE: none
  POST: sets data2
 */
template <typename B, typename R>
void BST<B, R>::setValueSecondary(const R& dataIn)
{
	val2 = dataIn;
}

/*PRE: none
  POST: returns data
 */
template <typename B, typename R>
B BST<B, R>::getValue() const
{
	return value;
}

/*PRE: none
  POST: returns data 2
 */
template <typename B, typename R>
R BST<B, R>::getValueSecondary() const
{
	return val2;
}

/*PRE: none
  POST: returns pointer to left node, else null pointer
 */
template <typename B, typename R>
BST<B, R>* BST<B, R>::getLeft() const
{
	return left;
}

/*PRE: none
  POST: returns pointer to right node, else null pointer
 */
template <typename B, typename R>
BST<B, R>* BST<B, R>::getRight() const
{
	return right;
}

#endif /* BST_H_ */
