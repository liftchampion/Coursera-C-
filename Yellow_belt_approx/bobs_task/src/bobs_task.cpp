#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
	int key;
	Node* right;
	Node* left;
};

void inserti(int xi, Node *&TTree) {
	if (TTree == NULL) {
		TTree = new Node;
		TTree->key = xi;
		TTree->right = TTree->left = NULL;
	}
	if (xi < TTree->key) {
		if (TTree->left != NULL) {
			inserti(xi, TTree->left);
		} else {
			TTree->left = new Node;
			TTree->left->left = TTree->left->right = NULL;
			TTree->left->key = xi;
		}
	}
	if (xi > TTree->key) {
		if (TTree->right != NULL) {
			inserti(xi, TTree->right);
		} else {
			TTree->right = new Node;
			TTree->right->left = TTree->right->right = NULL;
			TTree->right->key = xi;
		}

	}
}
Node *existi(int xi, Node **TTree) {
	if (*TTree != NULL) {
		while (xi != (*TTree)->key) {
			if (xi > (*TTree)->key) {
				if ((*TTree)->right != NULL) {
					TTree = &((*TTree)->right);
				} else {
					return NULL;
				}
			} else {
				if ((*TTree)->left != NULL) {
					TTree = &((*TTree)->left);
				} else {
					return NULL;
				}
			}

		}
		return (*TTree);
	} else {
		return NULL;
	}
}
int nexti(int xi, Node **TTree) {
	if (*TTree != NULL) {
		int last = 1000000001;
		while (1) {

			if ((*TTree)->key > xi) {
				if (last > (*TTree)->key) {
					last = (*TTree)->key;
				}
				if ((*TTree)->left != NULL) {
					TTree = &((*TTree)->left);
				} else {
					return last;
				}
			} else {
				if ((*TTree)->right != NULL) {
					TTree = &((*TTree)->right);
				} else {
					return last;
				}
			}
		}
	} else {
		return 1000000001;
	}
}
int previ(int xi, Node **TTree) {
	if (*TTree != NULL) {
		int last = -1000000001;
		while (1) {

			if ((*TTree)->key < xi) {
				if (last < (*TTree)->key) {
					last = (*TTree)->key;
				}
				if ((*TTree)->right != NULL) {
					TTree = &((*TTree)->right);
				} else {
					return last;
				}
			} else {
				if ((*TTree)->left != NULL) {
					TTree = &((*TTree)->left);
				} else {
					return last;
				}
			}
		}
	} else {
		return -1000000001;
	}
}
void deletei(int xi, Node **TTree) {
	if (*TTree != NULL) {
		Node zeroT;
		Node *ZTree = &zeroT;
		Node **LTree = &ZTree, **NTree = TTree, **NlTree = &ZTree, **PTree =
				&ZTree, **PlTree = &ZTree;
		(*NlTree)->key = 1000000001;
		while (xi != (*TTree)->key) {
			if (xi > (*TTree)->key) {
				if ((*TTree)->right != NULL) {
					LTree = TTree;
					TTree = &((*TTree)->right);
				} else {
					return;
				}
			} else {
				if ((*TTree)->left != NULL) {
					LTree = TTree;
					TTree = &((*TTree)->left);
				} else {
					return;
				}
			}
		}
		if ((*TTree)->right == NULL && (*TTree)->left == NULL) {
			if ((*LTree)->left == *TTree) {
				(*LTree)->left = NULL;
			} else {
				(*LTree)->right = NULL;
			}
		} else {
			if ((*TTree)->right == NULL) {
				if ((*LTree)->left == *TTree) {
					(*LTree)->left = (*TTree)->left;
				} else {
					(*LTree)->right = (*TTree)->left;
				}
			} else {
				if ((*TTree)->left == NULL) {
					if ((*LTree)->left == *TTree) {
						(*LTree)->left = (*TTree)->right;
					} else {
						(*LTree)->right = (*TTree)->right;
					}
				} else {
					/*############################*/
					while (1) {

						if ((*NTree)->key > xi) {
							if ((*NlTree)->key > (*NTree)->key) {
								PlTree = PTree;
								NlTree = NTree;
							}
							if ((*NTree)->left != NULL) {
								PTree = NTree;
								NTree = &((*NTree)->left);
							} else {
								break;
							}
						} else {
							if ((*NTree)->right != NULL) {
								PTree = NTree;
								NTree = &((*NTree)->right);
							} else {
								break;
							}
						}
					}
					/*###############################*/
					(*TTree)->key = (*NlTree)->key;
					if ((*PlTree)->left == *NlTree) {
						(*PlTree)->left = (*NlTree)->right;
					} else {
						(*PlTree)->right = (*NlTree)->right;
					}
				}
			}
		}
	} else {
		return;
	}
}
int main() {
	cout << "I'm alive" << endl;
	std::string ins = "insert";
	std::string del = "delete";
	std::string exi = "exists";
	std::string nex = "next";
	std::string pre = "prev";
	std::string oper;
	int x, ou;
	Node *Tree = NULL;
	Node *buff;
	Node **FTree;
	while (cin >> oper) {
		cin >> x;
		FTree = &Tree;
		if (oper == ins) {
			inserti(x, Tree);
		} else {
			if (oper == del) {
				deletei(x, FTree);
			} else {
				if (oper == exi) {
					buff = existi(x, FTree);
					if (buff == NULL) {
						cout << "false" << endl;
					} else {
						cout << "true" << endl;
					}
				} else {
					if (oper == nex) {
						ou = nexti(x, FTree);
						if (ou == 1000000001) {
							cout << "none" << endl;
						} else {
							cout << ou << endl;
						}
					} else {
						if (oper == pre) {
							ou = previ(x, FTree);
							if (ou == -1000000001) {
								cout << "none" << endl;
							} else {
								cout << ou << endl;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
/*
 *insert 2
insert 5
insert 3
exists 2
exists 5
exists 1
 *
 *
 */
