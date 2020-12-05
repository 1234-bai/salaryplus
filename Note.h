#ifndef NOTE_H
#define NOTE_H

template<class T>
class Note
{
private:
    Note<T> * next;
public:
    T data;
    Note(const T& data=0,Note<T>* next=0 );
    Note(Note<T> *p);
    void insertAfter(Note<T>* p);
    Note<T> *deleteAfter();
    Note<T> * nextNote();
    bool operator < (Note<T> &p);
    bool operator == (Note<T> &p);
    bool operator != (Note<T> &p);
    void operator = (Note<T>& p);
};

template<class T>
Note<T>::Note(const T& data, Note<T>* next)
{
    this->data = data;
    this->next = next;
}

template<class T>
Note<T>::Note(Note<T> *p)
{
    if (p == 0) {
        data = 0;
        next = 0;
    }
    else {
        data = p->data;
        next = 0;
    }
}

template<class T>
void Note<T>::insertAfter(Note<T>* p)	//p在后面
{
    p->next = next;
    next = p;
}

template<class T>
Note<T>* Note<T>::deleteAfter()		//删除后面的p
{
    Note<T>* temppre = next;
    if (next == 0) return 0;
    next = temppre->next;
    return temppre;
}

template<class T>
Note<T>* Note<T>::nextNote()
{
    return next;
}

template<class T>
bool Note<T>::operator<(Note<T> &p)
{
    return data < p.data;
}

template<class T>
bool Note<T>::operator==(Note<T> &p)
{
    return data == p.data;
}

template<class T>
bool Note<T>::operator!=(Note<T> &p)
{
    return data != p.data;
}

template<class T>
void Note<T>::operator=(Note<T> &p)
{
    data = p.data;
}

/*template<class T>
void Note<T>::changeNote(Note<T> &p)
{
    data = p.data;
}*/

template<class T>
void swapNote(Note<T>* p1, Note<T>* p2)
{
    Note<T> temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

#endif // NOTE_H
