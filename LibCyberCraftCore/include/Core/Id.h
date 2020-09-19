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

struct TypeId : public Id {};

namespace Impl{
    extern IdGenerator<TypeId> typeIdGenerator;
}

template<class T>
TypeId getTypeId() {
    static TypeId id = Impl::typeIdGenerator.generate();
    return id;
}


#endif //CYBERCRAFT_ID_H
