#ifndef LIST_H
#define LIST_H

#include "Note.h"
#include <fstream>
#include <iostream>

template<class T>
class List
{
private:
    Note<T>* head, *tail;
public:
    int length;
    Note<T>* nowPtr;
    List(Note<T>* head=0,Note<T>* tail=0);
    List(const char* filename);
    void createHead(Note<T>* p);
    bool insertNote(Note<T>* p);
    void tailInsertNote(Note<T>* p);
    void sortList(bool ( *sortRule)(Note<T>* p1, Note<T>* p2));
    bool is_empty();
    T popNote();
    void moveNext();
    void deleteNode(Note<T>* p);
    bool file_to_List(const char* filename);
    void List_to_file(const char* filename);
    void clear();
    void reset();
};

template<class T>
List<T>::List(Note<T>* head, Note<T>* tail) :head(head), tail(tail) { length = 0; nowPtr = head; }


template<class T>
List<T>::List(const char* filename)
{
    head = tail = 0;
    nowPtr = head;
    length = 0;
    file_to_List(filename);
}


template<class T>
void List<T>::createHead(Note<T>* st)
{
    Note<T>* p = new Note<T>(st);
    head = p;
    tail = p;
    length = 1;
    nowPtr = head;
}

template<class T>
bool List<T>::insertNote(Note<T>* st)
{
    Note<T>* p = new Note<T>(st);
    if (head == 0) createHead(p);
    else {
        if (*p == *head) return false;
        if (*p < *head) {
            p->insertAfter(head);
            head = p;
            nowPtr = head;
        }
        else {
            Note<T>* pre = head;
            Note<T>* now = pre->nextNote();
            while (now != 0 && *now < *p) {
                if (*now == *p) return false;
                pre = pre->nextNote();
                now = now->nextNote();
            }
            pre->insertAfter(p);
        }
        if (tail->nextNote() != 0) tail = tail->nextNote();
        length++;
    }
    return true;
}

template<class T>
void List<T>::tailInsertNote(Note<T>* st)
{
    Note<T>* p = new Note<T>(st);
    if (head == 0) createHead(p);
    else {
        tail->insertAfter(p);
        tail = p;
        length++;
    }
}

template<class T>
void List<T>::sortList(bool(* sortRule)(Note<T>* p1, Note<T>* p2))
{
    Note<T>* p1 = head;
    while (p1 != 0) {
        Note<T>* p2 = p1;
        Note<T>* p3 = p2->nextNote();
        while (p3 != 0) {
            if (sortRule(p3, p2)) p2 = p3;
            p3 = p3->nextNote();
        }
        if (*p2 != *p1) swapNote(p2, p1);
        p1 = p1->nextNote();
    }
}

template<class T>
bool List<T>::is_empty()
{
    return (nowPtr == 0);
}

template<class T>
T List<T>::popNote()
{
    return nowPtr->data;

}

template<class T>
inline void List<T>::moveNext()
{
    nowPtr = nowPtr->nextNote();
}

template<class T>
void List<T>::deleteNode(Note<T>* p)
{
    if (p == head) {
        head = head->nextNote();
        free(p);
    }
    else {
        Note<T>* pre = head;
        while (pre->nextNote() != p) {
            pre = pre->nextNote();
        }
        free(pre->deleteAfter());
    }
}

template<class T>
bool List<T>::file_to_List(const char* filename)
{
    std::ifstream fp(filename);
    if(!fp.is_open()) return false;
    fp.get();
    while (!fp.eof()) {
        T pe;
        fp >> pe;
        Note<T>* p = new Note<T>(pe);
        tailInsertNote(p);
    }
    fp.close();
    return true;
}

template<class T>
void List<T>::List_to_file(const char* filename)
{
    std::ofstream fp(filename);
    Note<T>*now = head;
    while (now != 0) {
        fp << now->data;
        now = now->nextNote();
    }
    fp.close();
}

template<class T>
void List<T>::clear()
{
    Note<T>* p = head;
    while (p != 0)
    {
        head = head->nextNote();
        delete p;
        p = head;
    }
    head = tail = 0;
    length = 0;
}

template<class T>
void List<T>::reset()
{
    nowPtr = head;
}

#endif // LIST_H
