# Proposal of Bayesian Linear Regression

## Basic information

A simple library for **Bayesian Linear Regression of** machine learning
including some basic matrix operations (e.g., LU decomposition for matrix inversion)
The code of this project is hosted on Github 
[KentLee0820/BayesianLinearRegression](https://github.com/KentLee0820/BayesianLinearRegression)


## Problem to Solve

I’d like to build my own machine learning library in C++ that can run on low-end hardware without high level library in python
Bayesian linear regression is the first topic I want to implement.
In the future, if there is an opportunity, I hope to expand more machine learning features, such as implementing neural networks.

## Prospective Users

Anyone would like to use machine learning in either C++ or Python to solve various problems, or in a low-end hardware environment without using Python.

## System Architecture

For testing:

1. Random generator one data point
2. update the prior and calculate the parameters of predictive distribution
3. repeat 1~2 until converges

Output:

- posterior of the model
- predictive distribution of new data

## API Description

1. Matrix operations
    - matrix addition, multiplication, transpose
    - Gaussian-Jordan elimination
    - LU decomposition
    - inverse

2. Model operations
    - y_mean, y_variance = model.predict(x)
    - w_posterior_mean, w_posterior_varince =  model.inference(x, y)

## Engineering Infrastructure

- Build system: make
- Version control: git
- Testing framework: pytest

## Schedule

Week 1 (9/30): Study background knowledge and setup program environment.

Week 2 (10/7): implement prototype and test in Python

Week 3 (10/14): implement matrix operations in C++ 

Week 4 (10/21): implement matrix operations in C++ 

Week 5 (11/4): implement Bayesian regression model in C++ 

Week 6 (11/11): implement Bayesian regression model in C++ 

Week 7 (11/25): pybind11 wrapping and result/performance testing

Week 8 (12/2): documentation and presentation preparing