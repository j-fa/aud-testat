#pragma once


// 2. praktische Aufgabe Klasse BTree
// Info 3, J. Willms, 2009
// Diese  Definitiondatei nicht ändern!
// Es darf nur die Datei bintree2.cpp geändert werden!

#include <string> 


// ****************************************************************************************
// Die Klasse ObjCount2 dient nur zu Debug-Zwecken
// In einer statischen Klassenvariable wird festgehalten, 
// wie viele aktuelle Objekte (Instanzen) der Klasse ObjCount2
// erzeugt, aber noch nicht gelöscht wurden
// SIEHE Studienbuch Informatik 3: Übungsaufgabe 3.3

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
// Die Klasse Knoten wird im binären Suchbaum benutzt
// Um Speicherlecks aufzuspüren, wird zu Debug-Zwecken hat die Klasse
// Knoten die Basisklasse ObjCount2

class Knoten : public ObjCount2 {
public:
	Knoten(const std::string & schluessel);
	std::string key_;          // Schlüssel  
	Knoten *l_;      // linker Nachfolger
	Knoten *r_;		 // rechter Nachfolger 
	int count_;      // Elementzähler
};

typedef Knoten * PKnoten;


// ****************************************************************************************
// Binärer Suchbaum mit Elementzähler
// (Unterschieden wird zwischen Knoten und Elementen)

class BTree
{
public:
	BTree();
	~BTree();
	void insert(const std::string & key);   // Einfügen eines Elements mit dem Schlüssel key
	bool remove(const std::string & key);   // Löschen eines Elements mit dem Schlüssel key
	void printInorder() const;  // Inorder-Ausgabe des gesamten Baums  
	void printPreorder() const; // Preorder-Ausgabe des gesamten Baums  
	int size() const;   // Gibt die Anzahl der Elemente des Baums zurück
	int nNodes() const; // Gibt die Anzahl der Knoten des Baums zurück
	int depth() const;  // Gibt die Tiefe des Baums zurück 
	int count(const std::string & key) const; // Gibt die Anzahl der eingefügten   
	// Elemente des Schlüssels key zurück


private:
	int size_;
	PKnoten root_;

	void deleteNodeR(PKnoten pk);
	void inorderR(const PKnoten pk) const;
	void preorderR(const PKnoten pk) const;
	void insertR(PKnoten & pk, const std::string & key);
	int depthR(const PKnoten pk) const;
	int countR(const PKnoten pk, const std::string & key) const;
	bool removeR(PKnoten& pk, const std::string & key);
	int nNodesR(const PKnoten pk) const;
};







