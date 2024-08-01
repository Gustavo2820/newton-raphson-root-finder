# Newton-Raphson Root Finder with ExprTk

This C++ program demonstrates how to find the root of a mathematical function using the Newton-Raphson method. The program utilizes the `exprtk` library to parse and evaluate mathematical expressions.

## Features

- Allows users to input a mathematical function as a string.
- Computes the derivative of the function using finite differences.
- Finds the root of the function using the Newton-Raphson method.

## Dependencies

- [ExprTk](https://www.partow.net/programming/exprtk/) - Expression Template Toolkit

## How It Works

The **Newton-Raphson method** is a root-finding algorithm that uses iterative approximation to find the roots of a real-valued function. It is particularly useful for finding roots of non-linear equations. The method is based on linear approximation and uses the derivative of the function to iteratively converge to the root.

### Newton-Raphson Method

1. **Initial Guess**: Start with an initial guess for the root of the function, denoted as \(x_0\).
2. **Iterative Process**: Use the formula:

   \[
   x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)}
   \]

   where \(f(x)\) is the function whose root we want to find, and \(f'(x)\) is the derivative of the function.
3. **Convergence**: Repeat the process until the difference between successive approximations \(x_{n+1}\) and \(x_n\) is smaller than a predefined tolerance level. This indicates that the approximation is close enough to the actual root.
