#include "MultiMapIterator.h"
#include "MultiMap.h"

///Best case : θ(1)
///Worst case : θ(n)
/// Average : θ(n)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	if(col.s == 0 )
        current = -1;
    else
    {
        current = 0;
        while ((col.HashTable[current]== NULL_TELEM || col.HashTable[current]== NULL_TELEM2 ) && current < col.m)
            current = current + 1;

    }

}
///Best case : θ(1)
///Worst case : θ(1)
/// Average : θ(1)
TElem MultiMapIterator::getCurrent() const{
    if(!valid())
        throw exception();
	return col.HashTable[current];
}
///Best case : θ(1)
///Worst case : θ(1)
/// Average : θ(1)
bool MultiMapIterator::valid() const {
	if (current >= 0 and current < col.m  and col.HashTable[current]!= NULL_TELEM and col.HashTable[current]!= NULL_TELEM2 )
	    return true;
    return false;
}
///Best case : θ(1)
///Worst case : θ(n)
/// Average : θ(n)
void MultiMapIterator::next() {
    if(!valid())
        throw exception();
    current = current +1;
        while (current<col.m && (col.HashTable[current]== NULL_TELEM || col.HashTable[current]== NULL_TELEM2 ))
            current = current + 1;


}
///Best case : θ(1)
///Worst case : θ(n)
/// Average : θ(n)
void MultiMapIterator::first() {
    if (col.size() == 0)
        current = -1;
    else
    {
        current = 0;
        while (col.HashTable[current]== NULL_TELEM || col.HashTable[current]== NULL_TELEM2 )
            current = current + 1;

    }


}
///Best case : θ(1)
///Worst case : θ(n)
/// Average : θ(n)
bool MultiMapIterator::modify( TElem change) {
    if(!valid())
        return false;
    else
    {
        if (  col.HashTable[current].first == change.first)
        {
            col.HashTable[current].second = change.second;
            return true;
        }
        else
        {
            col.HashTable[current] = NULL_TELEM2;
            // wir addieren das neune elem
            int i = 0;
            int h= col.Hash_Function(change.first,i);
            while(col.HashTable[h] != NULL_TELEM && col.HashTable[h] != NULL_TELEM2 && i < col.m)
            {
                i++;
                h = col.Hash_Function(change.first,i);
            }


           col.HashTable[h] = change;
            return true;


        }


    }


}

