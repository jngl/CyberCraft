//
// Created by jngl on 03/09/2020.
//

#ifndef CYBERCRAFT_ID_H
#define CYBERCRAFT_ID_H

struct Id
{
    int value;

    bool operator<(Id right) const{
        return value<right.value;
    }

};

template<class T>
class IdGenerator
{
public:
    constexpr T generate(){
        return T{++m_maxId};
    }
private:
    int m_maxId = 0;
};

#endif //CYBERCRAFT_ID_H
