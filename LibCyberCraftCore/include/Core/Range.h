//
// Created by jngl on 20/12/2020.
//

#ifndef CYBERCRAFT_RANGE_H
#define CYBERCRAFT_RANGE_H

#include <type_traits>
#include <optional>
#include <vector>
#include <string>

namespace cc {
    class InvalidRange : std::exception
    {
    public:
        [[nodiscard]] const char* what() const noexcept override;
    };



    template<class T>
    class Range
    {
    public:
        static_assert(std::is_integral_v<T>, "T must be a integral number");

        /// Construct a range from a to b or b to a
        constexpr Range(T min, T max):
            m_min(min),
            m_max(max)
        {
            if(m_min > m_max){
                throw InvalidRange();
            }
        }

        constexpr Range(const Range<T>& copyFrom):
            m_min(copyFrom.m_min),
            m_max(copyFrom.m_max)
        {
        }

        constexpr Range(Range<T>&& copyFrom) noexcept:
                m_min(copyFrom.m_min),
                m_max(copyFrom.m_max)
        {
        }

        virtual ~Range() = default;

        constexpr Range<T>& operator=(const Range<T>& right){
            if(this == &right){
                return *this;
            }

            m_min = right.m_min;
            m_max = right.m_max;

            return *this;
        }

        constexpr Range<T>& operator=(Range<T>&& right){
            if(this == &right){
                return *this;
            }

            m_min = right.m_min;
            m_max = right.m_max;

            return *this;
        }

        [[nodiscard]] constexpr T min() const {
            return m_min;

        };

        [[nodiscard]] constexpr T max() const {
            return m_max;
        };

        std::optional<T> tryPopMin() {
            if(m_min == m_max){
                return {};
            }

            T result = m_min;
            ++m_min;
            return result;
        }

        std::optional<T> tryPopMax() {
            if(m_min == m_max){
                return {};
            }

            T result = m_max;
            --m_max;
            return result;
        }

        static std::optional<Range<T>>  tryFusion(const Range<T>& a, const Range<T>& b){
            if(a.m_max + 1 == b.m_min) {
                return {{a.m_min, b.m_max}};
            }
            if(b.m_max + 1 == a.m_min) {
                return {{b.m_min, a.m_max}};
            }
            return {};
        }

        bool operator==(const Range<int>& other) const {
            return m_min == other.m_min && m_max == other.m_max;
        }

        [[nodiscard]] std::string toDebugString() const {
            return std::to_string(m_min) + "-" + std::to_string(m_max);
        }

        void pushMin() {
            --m_min;
        }

        void pushMax() {
            m_max++;
        }

    private:
        T m_min;
        T m_max;
    };

    /*template<class T>
    class MultiRange
    {
    public:
        static_assert(std::is_integral_v<T>, "T must be a integral number");

        void addNumber(T value){
            const size_t index = findPos(value);
            const cc::Range<T> valueRange(value, value);

            if(index > 0){
                if(value <= m_ranges[index - 1].max()){
                    return;
                }

                const std::optional<Range<int>> try1 = cc::Range<T>::tryFusion(m_ranges[index-1], valueRange);
                if(try1.has_value()){
                    m_ranges[index] = try1.value();
                    return;
                }
            }

            if(index < m_ranges.size()){
                if(value >= m_ranges[index].min()){
                    return;
                }

                const std::optional<Range<int>> try2 = cc::Range<T>::tryFusion(m_ranges[index], valueRange);
                if(try2.has_value()){
                    m_ranges[index] = try2.value();
                    return;
                }
            }

            m_ranges.insert(m_ranges.begin()+static_cast<ptrdiff_t>(index), valueRange);
        }

        std::optional<T> tryPopFirst(){
            if(m_ranges.empty()){
                return {};
            }

            if(m_ranges.front().min() == m_ranges.front().max()){
                const T result = m_ranges.front().min();
                m_ranges.erase(m_ranges.begin());
                return result;
            }

            return m_ranges.front().tryPopMin();
        }

    private:
        std::vector<Range<T>> m_ranges;

        size_t findPos(T value) const{
            size_t index = 0;

            while(index < m_ranges.size() && m_ranges[index].min() < value){
                ++index;
            }

            return index;
        };
    };*/

    template<class T>
    class MultiRange
    {
    public:
        MultiRange() = default;
        explicit MultiRange(const Range<T>& range){
            m_ranges.push_back(range);
        }

        T tryPopFirst(){
            if(m_ranges.size() == 0){
                return {};
            }

            auto maybeId =  m_ranges.back().tryPopMin();

            if(!maybeId.has_value()){
                const T result{m_ranges.back().min()};
                m_ranges.pop_back();
                return result;
            }

            return T{maybeId.value()};
        }

        void addNumber(T id){
            for(int index = nbRange() - 1; index >= 0; --index){
                if(tryDelete(index, id)){
                    return;
                }
            }

            if(!m_ranges.empty() &&  m_ranges.front().max() + 1 == id){
                m_ranges.front().pushMax();
            }else{
                m_ranges.insert(m_ranges.begin(), RangeT{id, id});
            }
        }

        std::string toDebugString(){
            std::string str = "IdGenerator[";
            for(const Range<T>& range: m_ranges){
                str += range.toDebugString() + ", ";
            }
            str += "]";
            return str;
        }

        [[nodiscard]] int nbRange() const {
            return static_cast<int>(m_ranges.size());
        }

        T size() const{
            T somme = 0;
            for(const Range<T>& range: m_ranges){
                somme += range.max() - range.min();
            }
            return somme;
        }


    private:
        using RangeT = Range<T>;
        std::vector<RangeT> m_ranges;

        RangeT& get(int index){
            return m_ranges[static_cast<size_t>(index)];
        };

        void doDelete(int index, T value){
            const bool fusionWithPrevious = index != nbRange() - 1 && get(index + 1).max() + 1 == value;
            const bool fusionWithCurrent = get(index).min() - 1 == value;

            if (fusionWithPrevious) {
                if(fusionWithCurrent){
                    get(index) = RangeT(get(index + 1).min(), get(index).max());
                    m_ranges.erase(m_ranges.begin() + static_cast<ptrdiff_t>(index) + 1);
                }
                else{
                    get(index+1).pushMax();
                }
            } else {
                if(fusionWithCurrent){
                    get(index).pushMin();
                }
                else{
                    m_ranges.insert(m_ranges.begin() + index + 1, RangeT{value, value});
                }
            }
        };

        bool tryDelete(int index, T value) {
            if(get(index).max() >= value && value >= get(index).min()){
                return true;
            }

            if(get(index).min() > value) {
                doDelete(index, value);
                return true;
            }

            return false;
        };
    };
}

#endif //CYBERCRAFT_RANGE_H
