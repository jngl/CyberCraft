//
// Created by jngl on 22/07/2020.
//

#ifndef CYBERCRAFT_BTREEPLUS_H
#define CYBERCRAFT_BTREEPLUS_H

#include "Common.h"

#include <cassert>
#include <iostream>
#include <array>

/**************************************************************
 *                  BTreePlusNode
 *************************************************************/
template<class Key, class Data, size_t MaxSize>
class BTreePlusNode
{
public:
    using ThisType = BTreePlusNode<Key, Data, MaxSize>;

    virtual void debugPrint(int nbTab) const = 0;
    virtual std::unique_ptr<ThisType> insert(Key newKey, Data newData) = 0;
    [[nodiscard]] virtual size_t size() const = 0;
    virtual Key firstKey() const = 0;
};

/**************************************************************
 *                  BTreePlusLeaf
 *************************************************************/
template<class Key, class Data, size_t MaxSize>
class BTreePlusLeaf final : public BTreePlusNode<Key, Data, MaxSize>
{
public:
    using ThisType = BTreePlusLeaf<Key, Data, MaxSize>;
    using ParentType = BTreePlusNode<Key, Data, MaxSize>;

    void debugPrint(int nbTab) const override {
        for(int i=0; i<m_size; ++i){
            printTabs(nbTab);
            std::cout<<m_keys[i]<<" : "<<m_datas[i]<<"\n";
        }
    }

    std::unique_ptr<ParentType> insert(Key newKey, Data newData) override {
        if(m_size<MaxSize){
            insertInLeaf(newKey, newData);
            return std::unique_ptr<ParentType>();
        }else{
            std::unique_ptr<ThisType> newLeaf = split();
            if(newKey < newLeaf->m_keys[0]){
                insertInLeaf(newKey, newData);
            }else{
                newLeaf->insertInLeaf(newKey, newData);
            }
            return newLeaf;
        }
    }

    [[nodiscard]] size_t size() const override {
        return m_size;
    }

    Key firstKey() const override {
        assert(m_size>0);
        return m_keys[0];
    }
private:
    std::array<Key, MaxSize> m_keys;
    std::array<Data, MaxSize> m_datas;
    size_t m_size = 0;

    void insertInLeaf(Key newKey, Data newData) {
        assert(m_size < MaxSize);
        int index = 0;
        for(; index<m_size && m_keys[index]<newKey; ++index);
        for(int i=m_size-1; i>=index; --i){
            m_keys[i+1] = m_keys[i];
            m_datas[i+1] = m_datas[i];
        }
        m_keys[index] = newKey;
        m_datas[index] = newData;
        ++m_size;
    }

    std::unique_ptr<ThisType> split() {
        std::unique_ptr<BTreePlusLeaf<Key, Data, MaxSize>> newNode = std::make_unique<BTreePlusLeaf<Key, Data, MaxSize>>();

        int newIndex = 0;
        int oldIndex = m_size/2;
        for(; oldIndex<m_size; ++oldIndex, ++newIndex){
            newNode->m_keys[newIndex] = m_keys[oldIndex];
            newNode->m_datas[newIndex] = m_datas[oldIndex];
            ++newNode->m_size;
        }

        m_size = m_size - newNode->m_size;

        return newNode;
    }
};

/**************************************************************
 *                  BTreePlusBranch
 *************************************************************/
template<class Key, class Data, size_t MaxSize>
class BTreePlusBranch final : public BTreePlusNode<Key, Data, MaxSize>
{
public:
    using ThisType = BTreePlusBranch<Key, Data, MaxSize>;
    using ParentType = BTreePlusNode<Key, Data, MaxSize>;

    void debugPrint(int nbTab) const override{
        for(int i=0; i<m_size; ++i){
            if(i != 0){
                printTabs(nbTab);
                std::cout<<m_keys[i-1]<<"\n";
            }
            m_children[i]->debugPrint(nbTab+1);
        }
    }

    std::unique_ptr<ParentType> insert(Key newKey, Data newData) override{
        int index = findBranch(newKey);
        std::unique_ptr<ParentType> newNode = m_children[index]->insert(newKey, newData);
        if(newNode){
            assert(m_size<MaxSize);
            for(int i=m_size; i>=index; --i){
                m_children[i+1] = std::move(m_children[i]);
                m_keys[i] = m_keys[i-1];
            }
            m_children[index] = std::move(newNode);
            m_keys[index-1] = m_children[index]->firstKey();
            ++m_size;
        }

        return {};
    }

    void add(std::unique_ptr<ParentType> node){
        assert(node);
        assert(node->size()>0);
        if(m_size==0){
            m_children[0] = std::move(node);
        }else{
            assert(m_size==1);
            if(m_children[0]->firstKey()<node->firstKey()){
                m_children[1] = std::move(node);
            }else{
                m_children[1] = std::move(m_children[0]);
                m_children[0] = std::move(node);

            }
            m_keys[0] = m_children[1]->firstKey();
        }
        ++m_size;
    }

    [[nodiscard]] size_t size() const override {
        return m_size;
    }

    Key firstKey() const override {
        assert(m_size>0);
        return m_keys[0];
    }

private:
    std::array<Key, MaxSize-1> m_keys;
    std::array<std::unique_ptr<ParentType>, MaxSize> m_children;
    size_t m_size = 0;

    int findBranch(Key key) const {
        int result = 0;
        for(int i=0; i<m_size-1; ++i){
            if(m_keys[i] < key) {
                result = i;
            }else{
                break;
            }
        }
        return result;
    }
};

/**************************************************************
 *                  BTreePlus
 *************************************************************/
template<class Key, class Data, size_t MaxSize>
class BTreePlus
{
public:
    using ThisType  = BTreePlus<Key, Data, MaxSize>;
    using Node      = BTreePlusNode<Key, Data, MaxSize>;
    using Leaf      = BTreePlusLeaf<Key, Data, MaxSize>;
    using Branch    = BTreePlusBranch<Key, Data, MaxSize>;

    void insert(Key newKey, const Data& data) {
        if (!m_root) {
            m_root = std::make_unique<Leaf>();
        }

        std::unique_ptr<Node> newNode = m_root->insert(newKey, data);

        if(newNode){
            std::unique_ptr<Branch> newRoot = std::make_unique<Branch>();
            newRoot->add(std::move(m_root));
            newRoot->add(std::move(newNode));
            m_root = std::move(newRoot);
        }
    }
    void debugPrint() const{
            std::cout<<"BTreePlus\n";
            if(m_root){
                m_root->debugPrint(1);
            }
        }

private:
    std::unique_ptr<Node> m_root;
};


#endif //CYBERCRAFT_BTREEPLUS_H
