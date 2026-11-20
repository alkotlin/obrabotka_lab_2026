#pragma once
#include "PhysValue.h"
#include <functional>
#include <vector>
#include <string>

template <typename UnitX, typename UnitY>
class Model {
public:
    using ModelFunction = std::function<double(double, const std::vector<double>&)>; // абстрактная функция , для всех функций 
    
    ModelFunction model_func; // имя функции 
    std::string name;
    int num_parameters; // число степеней свободы , для погрешности 

    Model(ModelFunction func, std::string model_name, int num_params)
        : model_func(func), name(model_name), num_parameters(num_params) {}

    virtual ~Model() = default;


    double evaluate(double x, const std::vector<double>& params) const {
        return model_func(x, params);
    }

    virtual std::vector<double> getInitialGuess(
        const std::vector<double>& x_data,
        const std::vector<double>& y_data
    ) const = 0;
};
