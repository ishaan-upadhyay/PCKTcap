#ifndef LAYER_H
#define LAYER_H

#include <memory>
#include "../dependencies/json.hpp"

class Layer
{
public:
    std::unique_ptr<Layer> nextLayer;
    virtual void print() = 0;
    virtual nlohmann::json toJson() = 0;
};

#endif // LAYER_H