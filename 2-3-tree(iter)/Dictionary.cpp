#include "Dictionary.h"


int Lior_Dictionary::Insert(Lior_StringKey* k, Lior_Worker* d)
{
	if (IsEmpty())
	{
		root = new Lior_LeafNode(k, d);
	}
	else
	{
		// no k found
		if (Find(k) != NULL)
		{
			// exists
			return 0;
		}
		else
		{
			//  new leaf
			Lior_LeafNode* newleaf = new Lior_LeafNode(k, d);

			// insertion

			if (root->IsLeaf()) // only one element in the tree
			{
				Lior_LeafNode* leafRoot = (Lior_LeafNode*)root;
				Lior_InteriorNode* newRoot = new Lior_InteriorNode();

				// leafRoot >= new
				if (leafRoot->Key()->Compare(newleaf->Key()) > 0)
				{
					newRoot->setLeft(newleaf);
					newRoot->setMin1(newleaf->Key());
					newRoot->setMid(leafRoot);
					newRoot->setMin2(leafRoot->Key());
				}
				else // new >leafRoot
				{
					newRoot->setLeft(leafRoot);
					newRoot->setMin1(leafRoot->Key());
					newRoot->setMid(newleaf);
					newRoot->setMin2(newleaf->Key());
				}

				//update root
				root = newRoot;
			}
			else // root is not a leaf
			{
				Lior_InteriorNode* parent = FindParent(newleaf->Key());

				// if parent has 2 children
				if (parent->getRight() == NULL)
				{
					Lior_LeafNode* left = (Lior_LeafNode*)parent->getLeft();
					Lior_LeafNode* mid = (Lior_LeafNode*)parent->getMid();

					if (newleaf->Key()->Compare(mid->Key()) > 0) // newleaf in the right
					{
						parent->setRight(newleaf);
						parent->setMin3(newleaf->Key());
						// no need to update min2 min3 of fathers of "parent"
					}
					else if (newleaf->Key()->Compare(left->Key()) > 0) // newleaf in the middle
					{
						parent->setRight(mid);
						parent->setMin3(mid->Key());
						parent->setMid(newleaf);
						parent->setMin2(newleaf->Key());
						// no need to update min2 min3 of fathers of "parent"
					}
					else if (newleaf->Key()->Compare(left->Key()) < 0) // newleaf in the left
					{
						parent->setRight(mid);
						parent->setMin3(mid->Key());
						parent->setMid(left);
						parent->setMin2(left->Key());
						parent->setLeft(newleaf);
						parent->setMin1(newleaf->Key());
					}

					Update(parent); // Update all fathers of "parent" till the root
				}
				else // parent has 3 children
				{
					Lior_TransitoryNode* temp = MakeTransitoryNode(parent, newleaf);

					parent->setLeft(NULL);
					parent->setMid(NULL);
					parent->setRight(NULL);
					delete parent; // we made a temp four-son out of it

					AddChild(temp);

				}
			}
		}
	}

	return 1; // good
}

Lior_InteriorNode* Lior_Dictionary::FindParent(Lior_StringKey* k)
{
	Lior_Node* node = root;
	Lior_InteriorNode* Interior = (Lior_InteriorNode*)node;

	Lior_InteriorNode* parent = NULL;

	while (!node->IsLeaf())
	{
		Interior = (Lior_InteriorNode*)node;

		parent = Interior;

		// k bigger than min3
		if ((Interior->getRight() != NULL) && (k->Compare(Interior->getMin3()) >= 0))
		{
			node = Interior->getRight();
		}
		else if (k->Compare(Interior->getMin2()) >= 0) // k between min2 and min3
		{
			node = Interior->getMid();
		}
		else // k between min1 and min2
			node = Interior->getLeft();
	}

	return parent;
}

Lior_TransitoryNode* Lior_Dictionary::MakeTransitoryNode(Lior_InteriorNode* parent, Lior_LeafNode* child)
{
	Lior_TransitoryNode* retFourSons = new Lior_TransitoryNode(); // will be instead of parent

	Lior_LeafNode* right = (Lior_LeafNode*)parent->getRight();
	Lior_LeafNode* left = (Lior_LeafNode*)parent->getLeft();
	Lior_LeafNode* mid = (Lior_LeafNode*)parent->getMid();

	Lior_StringKey* newChildKey = child->Key();

	//case 1: new is the biggest
	if (newChildKey->Compare(right->Key()) > 0)
	{
		retFourSons->setLeft(left);
		retFourSons->setMid(mid);
		retFourSons->setRight(right);
		retFourSons->setBiggest(child);
		retFourSons->setMin1(left->Key());
		retFourSons->setMin2(mid->Key());
		retFourSons->setMin3(right->Key());
		retFourSons->setMin4(child->Key());
	}
	//case2: new between 3 and 4
	else if (newChildKey->Compare(mid->Key()) > 0)
	{
		retFourSons->setLeft(left);
		retFourSons->setMid(mid);
		retFourSons->setRight(child);
		retFourSons->setBiggest(right);
		retFourSons->setMin1(left->Key());
		retFourSons->setMin2(mid->Key());
		retFourSons->setMin3(child->Key());
		retFourSons->setMin4(right->Key());
	}
	//case 3: new between 2 and 3 
	else if (newChildKey->Compare(left->Key()) > 0) // new is 2/4
	{
		retFourSons->setLeft(left);
		retFourSons->setMid(child);
		retFourSons->setRight(mid);
		retFourSons->setBiggest(right);
		retFourSons->setMin1(left->Key());
		retFourSons->setMin2(child->Key());
		retFourSons->setMin3(mid->Key());
		retFourSons->setMin4(right->Key());
	}
	else
	{
		retFourSons->setLeft(child);
		retFourSons->setMid(left);
		retFourSons->setRight(mid);
		retFourSons->setBiggest(right);
		retFourSons->setMin1(child->Key());
		retFourSons->setMin2(left->Key());
		retFourSons->setMin3(mid->Key());
		retFourSons->setMin4(right->Key());
	}

	if (parent != root)
	{
		Lior_InteriorNode* FatherOfParent = (Lior_InteriorNode*)parent->getParent(); // father of retFourSons (=parent but with 4 sons)

		retFourSons->SetParent(FatherOfParent);

		if (FatherOfParent->getLeft() == parent)//parent is left node
			FatherOfParent->setLeft(retFourSons);
		else if (FatherOfParent->getMid() == parent)//parent is mid node
			FatherOfParent->setMid(retFourSons);
		else if (FatherOfParent->getRight() == parent)//parent is right node
			FatherOfParent->setRight(retFourSons);

		Update(FatherOfParent);
	}
	return retFourSons;
}

void Lior_Dictionary::Update(Lior_InteriorNode* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		if (node->getLeft()->IsLeaf())//the sons are leaves
		{
			// Update one step above  leaves
			node->setMin1(((Lior_LeafNode*)node->getLeft())->Key());

			if (node->getMid() != NULL)
			{
				node->setMin2(((Lior_LeafNode*)node->getMid())->Key());
			}
			else
			{
				node->setMin2(NULL);
			}

			if (node->getRight() != NULL)
			{
				node->setMin3(((Lior_LeafNode*)node->getRight())->Key());
			}
			else
			{
				node->setMin3(NULL);
			}

			node = ((Lior_InteriorNode*)node->getParent());
		}

		// update loop, till the root
		while (node != NULL)
		{
			node->setMin1(((Lior_InteriorNode*)node->getLeft())->getMin1());

			if (node->getMid() != NULL)
			{
				node->setMin2(((Lior_InteriorNode*)node->getMid())->getMin1());
			}
			else
			{
				node->setMin2(NULL);
			}

			if (node->getRight() != NULL)
			{
				node->setMin3(((Lior_InteriorNode*)node->getRight())->getMin1());
			}
			else
			{
				node->setMin3(NULL);
			}

			if (node == root)
			{
				node = NULL;
			}
			else
			{
				node = ((Lior_InteriorNode*)node->getParent());
			}

		}
	}
}

void Lior_Dictionary::AddChild(Lior_TransitoryNode* trans)
{
	Lior_InteriorNode* rightMostInterior = new Lior_InteriorNode;

	rightMostInterior->setLeft(trans->getRight());
	rightMostInterior->setMid(trans->getBiggest());
	rightMostInterior->setMin1(trans->getMin3());
	rightMostInterior->setMin2(trans->getMin4());

	Lior_InteriorNode* leftMostInterior = new Lior_InteriorNode;

	leftMostInterior->setLeft(trans->getLeft());
	leftMostInterior->setMid(trans->getMid());
	leftMostInterior->setMin1(trans->getMin1());
	leftMostInterior->setMin2(trans->getMin2());

	if (trans->getParent() == NULL)
	{
		Lior_InteriorNode* parent = new Lior_InteriorNode;

		parent->setLeft(leftMostInterior);
		parent->setMid(rightMostInterior);
		parent->setMin1(leftMostInterior->getMin1());
		parent->setMin2(rightMostInterior->getMin1());

		root = parent;

		trans->setLeft(NULL);
		trans->setMid(NULL);
		trans->setRight(NULL);
		trans->setBiggest(NULL);
		delete trans;
	}
	else // trans is not the root
	{
		Lior_InteriorNode* parent = (Lior_InteriorNode*)trans->getParent();

		if (parent->getRight() == NULL) // parent has 2 children. it's ok to add
		{
			if (trans == parent->getLeft()) // the 4-son node is smallest of the two
			{
				parent->setRight(parent->getMid());
				parent->setLeft(leftMostInterior);
				parent->setMid(rightMostInterior);
			}
			else if (trans == parent->getMid())
			{
				parent->setMid(leftMostInterior);
				parent->setRight(rightMostInterior);
			}

			// update min1 min2 min3 till the root
			Update(parent);
		}
		else // parent already has 3 children. make a 4 son transitory node
		{
			Lior_TransitoryNode* tmpFather = new Lior_TransitoryNode;

			if (trans == parent->getLeft())
			{
				tmpFather->setLeft(leftMostInterior);
				tmpFather->setMid(rightMostInterior);
				tmpFather->setRight(parent->getMid());
				tmpFather->setBiggest(parent->getRight());

				tmpFather->setMin1(leftMostInterior->getMin1());
				tmpFather->setMin2(rightMostInterior->getMin1());
				tmpFather->setMin3(((Lior_InteriorNode*)parent->getMid())->getMin1());
				tmpFather->setMin4(((Lior_InteriorNode*)parent->getRight())->getMin1());
			}
			else if (trans == parent->getMid())
			{
				tmpFather->setLeft(parent->getLeft());
				tmpFather->setMid(leftMostInterior);
				tmpFather->setRight(rightMostInterior);
				tmpFather->setBiggest(parent->getRight());

				tmpFather->setMin1(((Lior_InteriorNode*)parent->getLeft())->getMin1());
				tmpFather->setMin2(leftMostInterior->getMin1());
				tmpFather->setMin3(rightMostInterior->getMin1());
				tmpFather->setMin4(((Lior_InteriorNode*)parent->getRight())->getMin1());
			}
			else if (trans == parent->getRight())
			{
				tmpFather->setLeft(parent->getLeft());
				tmpFather->setMid(parent->getMid());
				tmpFather->setRight(leftMostInterior);
				tmpFather->setBiggest(rightMostInterior);

				tmpFather->setMin1(((Lior_InteriorNode*)parent->getLeft())->getMin1());
				tmpFather->setMin2(((Lior_InteriorNode*)parent->getMid())->getMin1());
				tmpFather->setMin3(leftMostInterior->getMin1());
				tmpFather->setMin4(rightMostInterior->getMin1());
			}

			Lior_InteriorNode* FatherOfParent = (Lior_InteriorNode*)parent->getParent();
			tmpFather->SetParent(parent->getParent());

			if (FatherOfParent != NULL) // if parent is not root.
			{
				if (FatherOfParent->getLeft() == parent)//parent is left node
					FatherOfParent->setLeft(tmpFather);
				else if (FatherOfParent->getMid() == parent)//parent is mid node
					FatherOfParent->setMid(tmpFather);
				else if (FatherOfParent->getRight() == parent)//parent is right node
					FatherOfParent->setRight(tmpFather);

				Update(FatherOfParent); // update our transitory's father till the root
			}
			else // parent was root
			{
				root = tmpFather;
			}

			parent->setLeft(NULL);
			parent->setMid(NULL);
			parent->setRight(NULL);
			delete parent; // we switched the parent with our new tmpFather

			trans->setLeft(NULL);
			trans->setMid(NULL);
			trans->setRight(NULL);
			trans->setBiggest(NULL);
			delete trans; // trans was replaced with two sons

			// now we've got a  node with 4 sons. bad. call add child recursively
			AddChild(tmpFather);
		}
	}
}

Lior_Worker* Lior_Dictionary::Delete(Lior_StringKey* k)
{
	Lior_Worker* retWorkerDeleted = Find(k);

	if (retWorkerDeleted == NULL)
	{
		return NULL;
	}
	else
	{
		Lior_InteriorNode* parent = FindParent(k);

		if (parent == NULL) // leaf was root. make empty dictionary
		{
			delete root;
			root = NULL;
		}
		else
		{
			Lior_LeafNode* leafToDel;

			//  son who was delete
			if (parent->getMin1()->Compare(k) == 0)
			{
				leafToDel = (Lior_LeafNode*)parent->getLeft();

				parent->setLeft(parent->getMid()); // shift all left
				if (parent->getRight() != NULL)
				{
					parent->setMid(parent->getRight());
					parent->setRight(NULL);
				}
				else
				{
					parent->setMid(NULL);
				}
			}
			else if (parent->getMin2()->Compare(k) == 0)
			{
				leafToDel = (Lior_LeafNode*)parent->getMid();

				//3 sons
				if (parent->getRight() != NULL)
				{
					parent->setMid(parent->getRight());
					parent->setRight(NULL);
				}
				//2 sons
				else
				{
					parent->setMid(NULL);
				}
			}
			else if ((parent->getRight() != NULL) && (parent->getMin3()->Compare(k) == 0))
			{
				leafToDel = (Lior_LeafNode*)parent->getRight();

				parent->setRight(NULL);
			}

			delete leafToDel;

			Update(parent);
			// fix ilegal nodes
			while ((parent != NULL) && (!parent->IsLeaf()) && ((Lior_InteriorNode*)parent->getMid() == NULL))
			{
				//no perent
				if (parent->getParent() == NULL)
				{
					root = parent->getLeft();

					parent->setLeft(NULL);
					parent->setMid(NULL);
					parent->setRight(NULL);
					delete parent;

					if (!root->IsLeaf())
					{
						parent = (Lior_InteriorNode*)root; // start next iteration
					}
					else
					{
						parent = NULL;
					}
				}
				else // there is a parent for parent
				{
					Lior_InteriorNode* grandpa = (Lior_InteriorNode*)parent->getParent();

					Lior_InteriorNode* leftSibling = (Lior_InteriorNode*)grandpa->getLeft();
					Lior_InteriorNode* midSibling = (Lior_InteriorNode*)grandpa->getMid();
					Lior_InteriorNode* rightSibling = (Lior_InteriorNode*)grandpa->getRight();


					if (leftSibling == parent)
					{
						//take left son
						if (midSibling->getRight() != NULL)
						{
							leftSibling->setMid(midSibling->getLeft());

							// shift left mid
							midSibling->setLeft(midSibling->getMid());
							midSibling->setMid(midSibling->getRight());
							midSibling->setRight(NULL);

							Update(leftSibling);
							Update(midSibling);
							Update(rightSibling);
						}
						// mid to the right has two sons. give him one and put him on the left
						else
						{
							midSibling->setRight(midSibling->getMid());
							midSibling->setMid(midSibling->getLeft());
							midSibling->setLeft(leftSibling->getLeft());

							leftSibling->setLeft(NULL);
							leftSibling->setMid(NULL);
							leftSibling->setRight(NULL);
							delete leftSibling;

							grandpa->setLeft(midSibling);//shift left
							grandpa->setMid(rightSibling);
							grandpa->setRight(NULL);

							Update(midSibling);
							Update(rightSibling);

							parent = grandpa; // for next iteration
						}
					}
					else if (midSibling == parent)
					{
						if (leftSibling->getRight() != NULL) // left to the left has 3 sons. take his right son.
						{
							midSibling->setMid(midSibling->getLeft());
							midSibling->setLeft(leftSibling->getRight());

							leftSibling->setRight(NULL);

							Update(leftSibling);
							Update(midSibling);
							Update(rightSibling);
						}
						else // left to the left has two sons. give him one and put him on the right
						{
							leftSibling->setRight(midSibling->getLeft());

							midSibling->setLeft(NULL);
							midSibling->setMid(NULL);
							midSibling->setRight(NULL);
							delete midSibling;

							grandpa->setMid(rightSibling);//shift left
							grandpa->setRight(NULL);

							Update(leftSibling);
							Update(rightSibling);
							parent = grandpa; // for next iteration
						}
					}
					else if (rightSibling == parent)
					{
						if (midSibling->getRight() != NULL) // mid to the left has 3 sons. take his right son.
						{
							rightSibling->setMid(rightSibling->getLeft());
							rightSibling->setLeft(midSibling->getRight());

							midSibling->setRight(NULL);

							Update(leftSibling);
							Update(midSibling);
							Update(rightSibling);
						}
						else // mid to the left has two sons. give him one and put him on the right
						{
							midSibling->setRight(rightSibling->getLeft());

							rightSibling->setLeft(NULL);
							rightSibling->setMid(NULL);
							rightSibling->setRight(NULL);

							// now rightsibling is empty
							delete rightSibling;

							grandpa->setRight(NULL);

							Update(midSibling);
							Update(leftSibling);

							parent = grandpa; // for next iteration
						}
					}
				}
			} // end while 
		}
	}

	return retWorkerDeleted;
}

void Lior_Dictionary::PrintDictionary(ofstream& outputFile)
{
	if (IsEmpty()) // empty 
	{
		outputFile << "Empty" << endl;
		outputFile.flush();
	}
	else
	{
		print23(outputFile, root);
	}
}

void Lior_Dictionary::print23(ofstream& outputFile, Lior_Node* node)
{
	if (node == NULL)
		return;
	if (node->IsLeaf())
	{
		Lior_LeafNode* leaf = (Lior_LeafNode*)node;
		outputFile << *(leaf->Data()) << endl;
		outputFile.flush();
	}
	else
	{
		Lior_InteriorNode* interior = (Lior_InteriorNode*)node;

		// Print in the right order
		print23(outputFile, interior->getLeft());
		print23(outputFile, interior->getMid());
		print23(outputFile, interior->getRight());
	}
}

void Lior_Dictionary::FreeAllElements()
{
	freeAllElementsHelper(root); // Start from the root
}
void Lior_Dictionary::freeAllElementsHelper(Lior_Node* node)
{
	if (node == NULL)
		return;
	if (node->IsLeaf())
	{
		Lior_LeafNode* leaf = (Lior_LeafNode*)node;

		delete leaf->Data(); // worker's dtor deletes the name (Lior_StringKey)

		delete leaf;
	}
	else
	{
		Lior_InteriorNode* interior = (Lior_InteriorNode*)node;

		// delete his left, mid and right sons recursively

		freeAllElementsHelper(interior->getLeft());
		freeAllElementsHelper(interior->getMid());
		freeAllElementsHelper(interior->getRight());

		if (interior == root)
		{
			root = NULL;
		}

		interior->setLeft(NULL);
		interior->setMid(NULL);
		interior->setRight(NULL);
		delete interior;
	}
}

int Lior_Dictionary::IsEmpty()// Check if the dictionary is empty, if empty return 1(true), else return 0 (false)
{
	return (root == NULL);
}

Lior_Worker* Lior_Dictionary::Find(Lior_StringKey* k)
{
	//case 1:   dictionary is empty or k is null, return without search
	if (IsEmpty() || k == NULL)
	{
		return NULL;
	}

	Lior_InteriorNode* Interior;
	Lior_Node* node = root;

	while (!node->IsLeaf())
	{
		Interior = (Lior_InteriorNode*)node;

		// k >=min3
		if ((Interior->getRight() != NULL) && (k->Compare(Interior->getMin3()) >= 0))
		{
			node = Interior->getRight();
		}
		// k>=min2&&k<min3
		else if (k->Compare(Interior->getMin2()) >= 0)
		{
			node = Interior->getMid();
		}
		// k <min2
		else
			node = Interior->getLeft();
	}

	// leaf
	Lior_LeafNode* leaf = (Lior_LeafNode*)node;

	if (k->Compare(leaf->Key()) == 0)
		return leaf->Data();
	else
		return NULL;

}