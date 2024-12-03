#ifndef LAYER_H
#define LAYER_H

#include <memory>
#include <bsoncxx/builder/basic/document.hpp>

/*
* Layer is an abstract class that represents a layer in a network packet.
* All layers must implement this class. 
* nextLayer is a pointer to the next layer in the packet.
* toBson() is used for serialization and storage in the database.
*/
class Layer
{
public:
    std::unique_ptr<Layer> nextLayer;
    virtual bsoncxx::builder::basic::document toBson() = 0;
};

#endif // LAYER_H