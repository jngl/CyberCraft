//
// Created by jngl on 21/08/2021.
//

#ifndef CYBERCRAFT_COMPONENT_H
#define CYBERCRAFT_COMPONENT_H

namespace cc{
    template<class T,class Id>
    class ComponentManager{
    public:
        T& create(Id id){
            if(id.value() >= m_data.size()){
                m_data.resize(id.value()+1);
            }

            m_data[id.value()] = T{};

            return m_data[id.value()].value();
        }

        void destroy(Id id){
            m_data[id.value()].reset();
        }

        std::optional<T>& get(Id id){
            return m_data[id.value()];
        }

    private:
        std::vector<std::optional<T>> m_data;
    };
}

#endif //CYBERCRAFT_COMPONENT_H
