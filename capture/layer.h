#ifndef LAYER_H
#define LAYER_H

#include <memory>
#include <bsoncxx/builder/basic/document.hpp>

class Layer
{
public:
    std::unique_ptr<Layer> nextLayer;
    virtual void print() = 0;
    virtual bsoncxx::builder::basic::document toBson() = 0;
};

#endif // LAYER_H