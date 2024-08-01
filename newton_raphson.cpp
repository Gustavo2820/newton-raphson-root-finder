#include<iostream>
#include<functional>
#include"exprtk.hpp"

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

    auto derivative = [](
        std::function<double(double)> f, 
        double h = 1e-5) -> std::function<double(double)> {
            return [f, h](double x) -> double {
                return (f(x + h) - f(x)) / h;
            };
    };

    //Receives the function, the derivative of the function, the first value, tolerance and max iterations.
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
                    return x; //Returns the current value if the derivative is 0.
                }
                double x_new = x - fx / dfx;
                if (std::abs(x_new - x) < tol) {
                return x_new; // Return if the change is less than the tolerance.
                }
                x = x_new;
            }
            std::cerr << "Número máximo de iterações alcançado." << std::endl;
            return x;
        };

    std::string input;
    std::cout << "Digite uma função matemática (Use x como váriavel): ";
    std::getline(std::cin, input);

    std::function<double(double)> input_function = create_lambda(input);

    std::function<double(double)> derivative_of_function = derivative(input_function);

    double x0;
    std::cout << "Digite um valor inicial para o método de newton-raphson: ";
    std::cin >> x0;

    double root = newton_raphson(input_function, derivative_of_function, x0);

    std::cout << "A raiz da função (mais próxima do valor inicial) é: " << root << "\n";

    return 0;
}