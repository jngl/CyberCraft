//
// Created by jngl on 08/08/2020.
//

#ifndef CYBERCRAFT_ITERATOR_H
#define CYBERCRAFT_ITERATOR_H


class Iterator{
public:
    bool operator!=(const Iterator& range);

    const Iterator& operator++();

    template<class T>
    T& get();

    Iterator& operator*();
};

#endif //CYBERCRAFT_ITERATOR_H
