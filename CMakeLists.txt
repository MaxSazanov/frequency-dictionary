cmake_minimum_required(VERSION 3.27)
project(FrequencyDictionary)

set(CMAKE_CXX_STANDARD 20)

add_executable(FrequencyDictionary main.cpp
        HashTable.h
        LinkedList.h
        Word.cpp
        Word.h
        LinkedListIterator.h
        Node.h
        WordHash.h
        WordHash.cpp
        SimpleString.cpp
        SimpleString.h)
