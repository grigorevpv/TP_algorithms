//
// Created by grigo on 19.05.2017.
//

#ifndef HUFFMAN_V2_HUFFMAN_H
#define HUFFMAN_V2_HUFFMAN_H

typedef unsigned char byte;

class IInputStream {
    // Возвращает false, если поток закончился
public:
    virtual bool Read(byte& value) = 0;
};

class IOutputStream {
public:
    virtual void Write(byte value) = 0;
};

#endif //HUFFMAN_V2_HUFFMAN_H
