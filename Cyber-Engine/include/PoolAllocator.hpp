#pragma once

namespace core
{
    template<class Data, std::size_t MAX_DATA>
    class PoolAllocator
    {
    public:
        PoolAllocator()
        {
            mFirstFree = mData;
            for(std::size_t i(0); i<MAX_DATA-1; ++i){
                mData[i].mNext = &mData[i+1];
            }
        }
        
        Data* create(){
            MemBlock* a = mFirstFree;
            mFirstFree = a->mNext;
			new (&a->mData) Data;
            return &(a->mData);
        }
        
        void destroy(Data* d){
			d->~Data();
            auto a = reinterpret_cast<MemBlock*>(d);
            a->mNext = mFirstFree;
        }
        
    private:
        union MemBlock{
            Data mData;
            MemBlock* mNext;

            MemBlock(){
                mNext = nullptr;
            }
            ~MemBlock() {};
        };        
        
        MemBlock* mFirstFree;
        MemBlock mData[MAX_DATA];
    };
}
