#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

///Best case : θ(n)
///Worst case : θ(n)
/// Average : θ(n)
MultiMap::MultiMap() {
	m = 4;
    s= 0;
    HashTable = new TElem[m];
    for(int i=0;i<m;i++)
        HashTable[i]=NULL_TELEM;
}

///Best case : θ(1)
///Worst case : θ(n) amortiziert
/// Average : θ(n)
void MultiMap::add(TKey c, TValue v) {
    int i = 0;
	int h= Hash_Function(c,i);
    while(HashTable[h] != NULL_TELEM && HashTable[h] != NULL_TELEM2 && i < m)
    {
        i++;
        h = Hash_Function(c,i);
    }
    if(i==m)
    {
        resize_up();
        i =0;
        h= Hash_Function(c,i);
        while(HashTable[h] != NULL_TELEM && HashTable[h] != NULL_TELEM2 && i < m)
        {
            i++;
            h = Hash_Function(c,i);
        }
    }
        TElem p = pair<TKey, TValue>(c,v);
        HashTable[h] = p;
        s++;


}

///Best case : θ(1)
///Worst case : θ(n) amortisiert
/// Average : θ(n)
bool MultiMap::remove(TKey c, TValue v) {
    int h,i=0;

    while(i < m)
    {
        h = Hash_Function(c,i);
        if(HashTable[h].first == c && HashTable[h].second == v )
        {
            HashTable[h] = NULL_TELEM2;
            s--;
            if (s<m/4)
            {
                // Da wir nur einmal einen Element finden konnen und falls wir resize machen konnen wird das der komplexitat nicht viel schaden denn in den schlechtesten fall wird man Komplexitat Theta 2n erreichen also theta n

                resize_down();
            }
            return true;
        }
        i++;
    }

	return  false;
}
///Best case : θ(1)
/// (Im fall das alle Keys gleich sind und Die Multimap ist voll dann mussen wur die ganze Multimap durchgehen (denn alle Elememte sind auf der selben Position gehasht))
///Worst case : θ(n)
/// Average : θ(n)
vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> return_values= {};
    int h= Hash_Function(c,0),i=1;
    //for(int j=0;j<m;j++)
      //  if(HashTable[j].first == c)
        //    return_values.emplace_back(HashTable[j].second);
    while(HashTable[h] != NULL_TELEM && i < m )
    {
        if (HashTable[h].first == c)
        {
            return_values.emplace_back(HashTable[h].second);
        }
        h = Hash_Function(c,i);
        i++;
    }
    return return_values;
}

///Best case : θ(1)
///Worst case : θ(1)
/// Average : θ(1)
int MultiMap::size() const {
	return s;
}

///Best case : θ(1)
///Worst case : θ(1)
/// Average : θ(1)
bool MultiMap::isEmpty() const {

    if(size() == 0)
        return true;
	return false;
}
///Best case : θ(1)
///Worst case : θ(1)
/// Average : θ(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

///Best case : θ(1)
///Worst case : θ(1)
/// Average : θ(1)
MultiMap::~MultiMap() {
	delete [] HashTable ;
}
///Best case : θ(1)
///Worst case : θ(1)
/// Average : θ(1)
int MultiMap::Hash_Function(TKey k, int i) const {
    float c1= 0.5;
    float c2= 0.5;
    int h = Inside_Hash(k);
    return int(h+ c1*i +c2*i*i) % m ;
}
///Best case : θ(1)
///Worst case : θ(1)
/// Average : θ(1)
int MultiMap::Inside_Hash(TKey n) const{
    return (m+n%m)%m;
}
///Best case : θ(n)
///Worst case : θ(n)
/// Average : θ(n)
void MultiMap::resize_up() {
    m*=2;
    int h,j;
    auto* NewHashTable = new TElem[m];

    for(int i = 0; i < m; i ++)
        NewHashTable[i] = NULL_TELEM;

    for(int i = 0; i < m / 2; i ++)
    {
        j = 1;
        // dieses if wird, falls das program richtig funktioniert, nie ubersprungen.
        if(HashTable[i] != NULL_TELEM && HashTable[i] != NULL_TELEM2)
        {
            h = Hash_Function(HashTable[i].first,0);
            while(NewHashTable[h] != NULL_TELEM)
            {
                h = Hash_Function(HashTable[i].first,j);
                j++;
            }
            NewHashTable[h]=HashTable[i];
        }
    }
    delete[] HashTable;
    HashTable = NewHashTable;
}
///Best case : θ(n)
///Worst case : θ(n)
/// Average : θ(n)
void MultiMap::resize_down() {
    m/=2;
    int h,j;
    auto* NewHashTable = new TElem[m];

    for(int i = 0; i < m; i ++)
        NewHashTable[i] = NULL_TELEM;

    for(int i = 0; i < m * 2; i ++)
    {
        j = 1;
        if(HashTable[i] != NULL_TELEM && HashTable[i] != NULL_TELEM2)
        {
            h = Hash_Function(HashTable[i].first,0);
            while(NewHashTable[h] != NULL_TELEM)
            {
                h = Hash_Function(HashTable[i].first,j);
                j++;
            }
            NewHashTable[h]=HashTable[i];
        }
    }
    delete[] HashTable;
    HashTable = NewHashTable;
}

