#include<iostream>
#include<functional>
#include"exprtk.hpp"

// Creates a lambda function from a given mathematical expression string
std::function<double(double)> create_lambda(const std::string& expr_str) {
    return [expr_str](double x) -> double {
        // Define the variable used in the expression
        double x_value = x;
        exprtk::symbol_table<double> symbol_table;
        symbol_table.add_variable("x", x_value);

        exprtk::expression<double> expression;
        expression.register_symbol_table(symbol_table);

        exprtk::parser<double> parser;
        if (!parser.compile(expr_str, expression)) {
            // Handle parsing error
            return std::numeric_limits<double>::quiet_NaN();
        }

        // Evaluate the expression
        return expression.value();
    };
}

int main () {

    // Lambda function to compute the derivative of a given function using finite differences
    auto derivative = [](
        std::function<double(double)> f, 
        double h = 1e-5) -> std::function<double(double)> {
            return [f, h](double x) -> double {
                return (f(x + h) - f(x)) / h;
            };
    };

    // Lambda function to perform the Newton-Raphson method for finding roots of the function
    auto newton_raphson = [](
        std::function<double(double)> f,
        std::function<double(double)> df,
        double x0,
        double tol = 1e-6,
        int max_iter = 1000) -> double {
            double x = x0;
            for(int i = 0 ; i < max_iter ; i++) {
                double fx = f(x);
                double dfx = df(x);
                if(dfx == 0) {
                    std::cout << "A derivada da função é 0, impossível continuar.";
                    return x;  // Return current value if derivative is zero
                }
                double x_new = x - fx / dfx;
                if (std::abs(x_new - x) < tol) {
                return x_new; // Return if change is less than tolerance.
                }
                x = x_new;
            }
            std::cerr << "Número máximo de iterações alcançado." << std::endl;
            return x;
        };

    std::string input;
    std::cout << "Digite uma função matemática (Use x como váriavel): ";
    std::getline(std::cin, input);

    // Create a lambda function from the input expression
    std::function<double(double)> input_function = create_lambda(input);
    // Compute the derivative of the input function
    std::function<double(double)> derivative_of_function = derivative(input_function);

    double x0;
    std::cout << "Digite um valor inicial para o método de newton-raphson: ";
    std::cin >> x0;
    
    // Find the root using Newton-Raphson method
    double root = newton_raphson(input_function, derivative_of_function, x0);

    std::cout << "A raiz da função (mais próxima do valor inicial) é: " << root << "\n";

    return 0;
}
