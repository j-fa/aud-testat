// 2. praktische Aufgabe,  Klasse BTree
// Info 3, J. Willms, 2011

// Enthält die main()-Funktion

// Weitere Tests der Klasse BTree

// Der Quelltext der Klasse BTree ist noch unvollständig!
// Die Methoden nNodes() und remove() sollen in der bintree2.cpp
// implementiert werden
// Es soll lediglich die Datei bintree2.cpp geändert werden!
// _____________________________________________________________

//#include "stdafx.h"
#include <iostream>
#include <string>
#include <cassert>  // Wenn NDEBUG definiert ist, wird assert nicht ausgeführt!
#include "bintree.h"

#ifdef _WIN32
#include <windows.h>    // notwendig für SetConsoleOutputCP(1252), siehe unten
#endif



using namespace std;

// =========== Globale Hilfsfunktionen ===========================

// Gibt die Anzahl der Knoten des übergebenen Baums mit dem Schlüssel key aus
static void anzahlAusgeben(const BTree & tree, const string & key)
{
	cout << "Anzahl der Elemente mit Schlüssel " << key
		<< ": " << tree.count(key) << endl;

}

// Gibt den übergebenen Baum aus (zuerst inorder, dann preorder)
static void baumAusgeben(const BTree & btree, const string &outStr)
{
	cout << outStr << endl;
	cout << ">>>>>>>>>>>  INORDER:" << endl;
	btree.printInorder();
	cout << "-----------  PREORDER:" << endl;
	btree.printPreorder();
	cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;
}

// Gibt die Anzahl der Elemente, Tiefe und die
// Anzahl der Knoten aus.
// Prüft in der DEBUG-Version die Anzahl der allokierten Knoten
// und vergleicht Sie mit der Anzahl der Knoten im Baum
//
// PRECONDITION:
//                Es darf nur ein Objekt der Klasse BTree geben und
//                Objekte der Klasse Knoten dürfen nur von der
//                Klasse BTree erzeugt werden!
//
static void ausgabeAnzahl(const BTree &btree)
{
	cout << "Size: " << btree.size() << ", Tiefe: " << btree.depth() << endl;
	cout << "Anzahl der Knoten: " << btree.nNodes() << endl << endl;

	if (Knoten::getNumberOfObjects() != btree.nNodes())
	{
		cout << "Anzahl der momentan existierenden Objekte der Klasse Knoten: "
			<< Knoten::getNumberOfObjects() << endl;
		cout << "Rückgabewert von BTree::nNodes(): " << btree.nNodes() << endl;

		cout << "#### FOLGE-FEHLER:" << " Keine Übereinstimmung!" << endl << endl;
		assert(false);
	}
}



//  Löscht ein Element mit dem Schlüssel key und zusätzlich die Anzahl
//  der Elemente, Tiefe und die Anzahl der Knoten
//  Falls ein solches Element nicht vorhanden,
//  wird nur eine Warnung ausgegeben
static void loesche(BTree &btree, const string &key)
{
	if (btree.remove(key)){
		cout << "Element mit Schlüssel " << key << " gelöscht" << endl;
		ausgabeAnzahl(btree);
	}
	else {
		cout << "WARNUNG: Knoten \"" << key << "\" nicht vorhanden!" << endl;
	}
}

// =============================================================

int main()
{
	BTree b;
	string schluessel;

#ifdef _WIN32
	SetConsoleOutputCP(1252);     // Setzt unter Windows den ANSI-Zeichensatz auch in der
#endif                           // Konsole, falls unter Eigenschaften /Schriftart:
	// True-Type-Schriftart ausgewählt wurde


	cout << "##########  TEIL 1 #########################" << endl;
	baumAusgeben(b, "Leerer Baum:");

	b.insert("mpeg");
	b.insert("ean");
	b.insert("php");
	b.insert("pop3");
	b.insert("dns");
	b.insert("ftp");
	b.insert("ean");
	ausgabeAnzahl(b);

	b.insert("html");
	b.insert("pop3");
	b.insert("nat");
	b.insert("pop3");
	b.insert("gif");
	b.insert("odbc");

	baumAusgeben(b, "Nach dem Einfügen des Knoten \"odbc\":");
	ausgabeAnzahl(b);

	anzahlAusgeben(b, "pop3");
	anzahlAusgeben(b, "dns");
	anzahlAusgeben(b, "informatik");

	cout << endl << endl
		<< "#################  TEIL 2 ###################################" << endl;

	loesche(b, "informatik");
	loesche(b, "informatik1");
	loesche(b, "informatik2");
	loesche(b, "informatik3");

	loesche(b, "pop3");

	loesche(b, "dns");
	ausgabeAnzahl(b);

	loesche(b, "nat");
	baumAusgeben(b, "Nach dem Löschen des Knoten \"nat\":");

	loesche(b, "mpeg");
	baumAusgeben(b, "Nach dem Löschen des Knoten \"mpeg\":");

	b.insert("kom");
	b.insert("leo");
	b.insert("xml");
	b.insert("pkw");
	b.insert("icq");
	b.insert("leo");
	b.insert("md5");
	b.insert("pks");
	b.insert("pki");
	b.insert("mail");
	b.insert("pkq");
	b.insert("pkp");
	b.insert("md5");
	b.insert("map");
	b.insert("pki");
	b.insert("pkr");
	b.insert("mac");

	baumAusgeben(b, "Vor dem Löschen des Knoten \"odbc\":");
	ausgabeAnzahl(b);

	loesche(b, "odbc");
	baumAusgeben(b, "Vor dem Löschen des Knoten \"php\":");
	loesche(b, "php");
	baumAusgeben(b, "Nachdem Löschen des Knoten \"php\":");

	cout << endl << endl
		<< "#################  TEIL 3 ###################################" << endl;
	loesche(b, "mathematik");
	loesche(b, "kom");
	baumAusgeben(b, "Nachdem Löschen des Knoten \"kom\":");

	loesche(b, "html");
	baumAusgeben(b, "Nachdem Löschen des Knoten \"html\":");

	return 0;
}
