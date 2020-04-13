//
// Created by esteban on 4/12/20.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

#include <iostream>
#include "macros.h"


namespace utec
{
    
    template<class T>
    struct node
    {

        node * next;
        T value;

        // Empty constructor
        constexpr
        node();
        
        constexpr explicit
        node(const T & value);
        
        ~node();
        
        constexpr
        void
        insertNext(node<T> * nNext);
        
        constexpr
        void
        removeNext();

        constexpr
        T&
        operator * ();
        
    };
    
    template<class T>
    constexpr
    node<T>::node()
            : next(nullptr), value {} { }
    
    
    template<class T>
    constexpr
    node<T>::node(const T & value)
            : value(value), next(nullptr)
    {
        DEBUG(std::cout << "called constructor for address " << this << '\n';)
    }
    
    template<class T>
    node<T>::~node()
    {
        DEBUG(std::cout << "called destructor for address " << this << '\n';)
        next = nullptr;
    }
    
    template<class T>
    constexpr void
    node<T>::insertNext(node<T> * nNext)
    {
        next = nNext;
    }
    
    template<class T>
    constexpr void
    node<T>::removeNext()
    {
        if (next == nullptr)
            return;
        
        auto temp = next->next;
        delete next;
        next = temp;
    }
    
    template<class T>
    constexpr T & node<T>::operator *() {
        return value;
    }
}

#endif //UNTITLED_NODE_H
