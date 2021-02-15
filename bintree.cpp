// 2. praktische Aufgabe Klasse BTree
// Info 3, J. Willms, 20011

// Alle �nderungen und Erg�nzungen in dieser Datei hinterlegen!

//#include "stdafx.h"
#include <cassert>  // Wenn NDEBUG definiert ist, wird assert nicht ausgef�hrt!
#include <iostream>
#include "bintree.h"


using namespace std;

// ____________ EINF�GEN ______________________

bool BTree::remove(const string & key)
{
	bool res = removeR(root_, key);
	return res;
}

void removeNode(PKnoten &pk)
{
	if(pk->count_ > 1)
	{
		// Es existiert mehr als ein Knoten mit gesuchtem Schluessel
		pk->count_--;
	}
	else
	{
		if(pk->l_)
		{
			// Linker Teilbaum existiert
			if(pk->l_->r_)
			{
				PKnoten maxNode;
				PKnoten parentMaxNode;
				// Mind. ein groesserer Knoten existiert
				maxNode = pk->l_->r_;
				parentMaxNode = pk->l_;
				while(maxNode->r_)
				{
					parentMaxNode = maxNode;
					maxNode = maxNode->r_;
				}
				parentMaxNode->r_ = maxNode->l_;
				pk->key_ = maxNode->key_;
				pk->count_ = maxNode->count_;
				delete maxNode;
			}
			else
			{
				// Max. Knoten gefunden
				pk->key_ = pk->l_->key_;
				pk->count_ = pk->l_->count_;
				PKnoten toDelete = pk->l_;
				pk->l_ = pk->l_->l_;
				delete toDelete;
			}
		}
		else
		{
			// Linker Teilbaum existiert nicht
			if(pk->r_)
			{
				PKnoten toDelete = pk;
				pk = pk->r_;
				delete toDelete;
			}
			else
			{
				delete pk;
				pk = nullptr;
			}				
		}
	}
}

// Zugeh�rige rekursive private Methode
// WICHTIG: Referenzargument!!!
bool BTree::removeR(PKnoten &pk, const string & key)
{
	if(!pk)
	{
		return false;
	}
	
	// Suche Knoten mit key_ == key
	if(pk->key_ > key)
	{
		if(pk->l_)
		{
			removeR(pk->l_, key);
		}
	}
	else if(pk->key_ < key)
	{
		if(pk->r_)
		{
			removeR(pk->r_, key);
		}
	}
	else
	{
		// Knoten gefunden
		removeNode(pk);
	}
	
	return true;
}

// ____________ ANZAHL DER KNOTEN______________________


// Gibt Anzahl der Knoten zur�ck
int BTree::nNodes() const
{
	return nNodesR(root_);
}



// Zugeh�rige rekursive private Methode
int BTree::nNodesR(const PKnoten pk) const
{
	int n = 1;

	if(pk->l_)
	{
		n += nNodesR(pk->l_);
	}
	if(pk->r_)
	{
		n += nNodesR(pk->r_);
	}	

	return n;
}

// _____________________________________________________


// ============== Implementierung der Klasse ObjCount2 ==============
// SIEHE Studienbuch Informatik 3: �bungsaufgabe 3.3

int ObjCount2::count = 0;

ObjCount2::ObjCount2() // Konstruktor
{
	count++;   // erh�he Klassenz�hler
}

ObjCount2::~ObjCount2() // Destruktor
{
	count--;   // verringere Klassenz�hler
}

int ObjCount2::getNumberOfObjects()
{
	return count;
}



// ============== Implementierung der Klasse BTree ==============
// Die Klasse Knoten wird im bin�ren Suchbaum benutzt
// Um Speicherlecks aufzusp�ren, wird zu Debug-Zwecken die Anzahl
// der akutellen Knoten festgehalten

// Konstruktor der Klasse Knoten
Knoten::Knoten(const string & schluessel)
{
	key_ = schluessel;
	l_ = NULL;
	r_ = NULL;
	count_ = 1;
}


// ============== Implementierung der Klasse BTree ==============

// HINWEIS: Die (privaten) rekursiven Funktionen sind durch den Buchstaben R
//          am Ende des Funktionsnamens gekennzeichnet!
//          Beispiel:   Die �ffentliche Methode inorder() ruft
//                      die private rekursive Methode inorderR(root_) auf


BTree::BTree()    // Konstruktor
{
	size_ = 0;
	root_ = NULL;
}

BTree::~BTree()    // Destruktor
{
	deleteNodeR(root_);
}

// Wird nur vom Destruktor aufgerufen
void BTree::deleteNodeR(PKnoten pk)   // rekursiv
{
	if (pk) {
		deleteNodeR(pk->l_);
		deleteNodeR(pk->r_);
		delete pk;
	}
}

// Gibt die Anzahl der Elemente des Baums zur�ck
int BTree::size() const
{
	return size_;
}


// ____________ AUSGABE ______________________

// Inorder-Ausgabe des gesamten Baums
void BTree::printInorder() const
{
	inorderR(root_);
	cout << endl;
}

// Zugeh�rige rekursive private Methode
void BTree::inorderR(const PKnoten pk) const  // rekursiv
{
	if (pk) {
		inorderR(pk->l_);
		cout << pk->key_ << " (" << pk->count_ << "), ";
		inorderR(pk->r_);
	}
}

// --------------------------------------------------------

// Preorder-Ausgabe des gesamten Baums
void BTree::printPreorder() const
{
	preorderR(root_);
	cout << endl;
}

// Zugeh�rige rekursive private Methode
void BTree::preorderR(const PKnoten pk) const  // rekursiv
{
	if (pk) {
		cout << pk->key_ << " (" << pk->count_ << "), ";
		preorderR(pk->l_);
		preorderR(pk->r_);
	}
}



// ____________ TIEFE ______________________

// Gibt die Tiefe des Baums zur�ck
int BTree::depth() const
{
	return depthR(root_);
}

// Zugeh�rige rekursive private Methode
int BTree::depthR(const PKnoten pk) const
{
	if (pk) {
		int tr, tl;
		tr = depthR(pk->r_);
		tl = depthR(pk->l_);
		if (tr > tl) {
			tl = tr;
		}
		return 1 + tl;
	}
	else {
		return -1;
	}

}

// --------------------------------------------------------

// Gibt die Anzahl der eingef�gten Elemente dieses Schl�ssels zur�ck
int BTree::count(const string & key) const
{
	return countR(root_, key);
}

// Zugeh�rige rekursive private Methode
int BTree::countR(const PKnoten pk, const string & key) const
{
	int result = 0;

	if (pk != NULL) {
		if (key < pk->key_) {
			result = countR(pk->l_, key);
		}
		else if (key > pk->key_){
			result = countR(pk->r_, key);
		}
		else{  // Schluessel gefunden
			result = pk->count_;
		}
	}
	return result;
}





// ____________ EINF�GEN ______________________

// Einf�gen eines Elements
void BTree::insert(const string & key)
{
	insertR(root_, key);
}

// Zugeh�rige rekursive private Methode
// WICHTIG: Referenzargument!!!
void BTree::insertR(PKnoten & pk, const string & key)
{
	if (pk == NULL) {
		pk = new Knoten(key);
		size_++;
		return;
	}
	if (key < pk->key_) {
		insertR(pk->l_, key);
	}
	else if (key >  pk->key_){
		insertR(pk->r_, key);
	}
	else{
		assert(key == pk->key_);
		pk->count_++;
		size_++;
	}
}

