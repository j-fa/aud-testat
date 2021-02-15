#pragma once


// 2. praktische Aufgabe Klasse BTree
// Info 3, J. Willms, 2009
// Diese  Definitiondatei nicht �ndern!
// Es darf nur die Datei bintree2.cpp ge�ndert werden!

#include <string> 


// ****************************************************************************************
// Die Klasse ObjCount2 dient nur zu Debug-Zwecken
// In einer statischen Klassenvariable wird festgehalten, 
// wie viele aktuelle Objekte (Instanzen) der Klasse ObjCount2
// erzeugt, aber noch nicht gel�scht wurden
// SIEHE Studienbuch Informatik 3: �bungsaufgabe 3.3

class ObjCount2
{
public:
	ObjCount2();
	~ObjCount2();
	static int getNumberOfObjects();  // Klassenmethode
private:
	static int count;     // Klassenattribut: Anzahl aller noch nicht beendeten Instanzen  
};


// ****************************************************************************************
// Die Klasse Knoten wird im bin�ren Suchbaum benutzt
// Um Speicherlecks aufzusp�ren, wird zu Debug-Zwecken hat die Klasse
// Knoten die Basisklasse ObjCount2

class Knoten : public ObjCount2 {
public:
	Knoten(const std::string & schluessel);
	std::string key_;          // Schl�ssel  
	Knoten *l_;      // linker Nachfolger
	Knoten *r_;		 // rechter Nachfolger 
	int count_;      // Elementz�hler
};

typedef Knoten * PKnoten;


// ****************************************************************************************
// Bin�rer Suchbaum mit Elementz�hler
// (Unterschieden wird zwischen Knoten und Elementen)

class BTree
{
public:
	BTree();
	~BTree();
	void insert(const std::string & key);   // Einf�gen eines Elements mit dem Schl�ssel key
	bool remove(const std::string & key);   // L�schen eines Elements mit dem Schl�ssel key
	void printInorder() const;  // Inorder-Ausgabe des gesamten Baums  
	void printPreorder() const; // Preorder-Ausgabe des gesamten Baums  
	void printStructure() const;
	int size() const;   // Gibt die Anzahl der Elemente des Baums zur�ck
	int nNodes() const; // Gibt die Anzahl der Knoten des Baums zur�ck
	int depth() const;  // Gibt die Tiefe des Baums zur�ck 
	int count(const std::string & key) const; // Gibt die Anzahl der eingef�gten   
	// Elemente des Schl�ssels key zur�ck


private:
	int size_;
	PKnoten root_;

	void deleteNodeR(PKnoten pk);
	void inorderR(const PKnoten pk) const;
	void preorderR(const PKnoten pk) const;
	void printStructureR(const PKnoten pk) const;
	void insertR(PKnoten & pk, const std::string & key);
	int depthR(const PKnoten pk) const;
	int countR(const PKnoten pk, const std::string & key) const;
	bool removeR(PKnoten& pk, const std::string & key);
	int nNodesR(const PKnoten pk) const;
};







