//
// Created by jngl on 03/09/2020.
//

#ifndef CYBERCRAFT_ID_H
#define CYBERCRAFT_ID_H

#include "Range.h"

#include <string>
#include <limits>

namespace cc {
    template<class t_ValueType, class t_Tag>
    class Id {
    public:
        using ValueType = t_ValueType;
        using Tag = t_Tag;

        constexpr Id() = default;
        constexpr explicit Id(ValueType value): m_value(value) {}

        [[nodiscard]] constexpr bool isValid() const {
            return m_value != 0;
        }

        [[nodiscard]] std::string toDebugString() const{
            return "Id{"+std::to_string(m_value)+"}";
        }

        [[nodiscard]] ValueType value() const{return m_value;}

    private:

        ValueType m_value = 0;
    };

    template<class IdValue, class Tag>
    class IdGenerator {
    public:
        using This = IdGenerator<IdValue, Tag>;
        using ThisId = Id<IdValue, Tag>;

        IdGenerator():
            m_ids(Range<IdValue>(1, std::numeric_limits<unsigned int>::max()))
        {
        }

        ThisId create() {
            std::optional<IdValue> id = m_ids.tryPopFirst();

            if(!id.has_value()){
                return ThisId{0};
            }

            return ThisId{id.value()};
        }

        void destroy(ThisId id) {
            m_ids.addNumber(id.value());
        }

        std::string toDebugString(){
            return "IdGenerator{" + m_ids.toDebugString() + "}";
        }

        IdValue sizeOfAvailableIds() const{
            return m_ids.size();
        }

    private:
        MultiRange<IdValue> m_ids;
    };
}

#endif //CYBERCRAFT_ID_H
