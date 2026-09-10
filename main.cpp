#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

//Prints a given matrix
template <typename T>
void printMatrix(const std::vector<std::vector<T>>& matrix) {
    for (const auto& row : matrix) {
        std::cout << "[";
        for (const auto& element : row) {
            std::cout << std::setw(5) << element << " ";
        }
        std::cout << "]\n"; //New line at the end of each row
    }

}

//Adds two matrices together and returns the resulting matrix; assumes the matrices are the same size
template <typename T>
std::vector<std::vector<T>> addMatrices(std::vector<std::vector<T>>& matrix1, std::vector<std::vector<T>>& matrix2) {
    size_t rows = matrix1.size();
    size_t cols = matrix1[0].size();
    std::vector<std::vector<T>> matrix(rows, std::vector<T>(cols, 0));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix.at(i).at(j) = (matrix1.at(i).at(j) + matrix2.at(i).at(j));
        }
    }
    return matrix;
}

//Multiplies two matrices together and returns the resulting matrix; assumes correct dimensions
template <typename T>
std::vector<std::vector<T>> multiplyMatrices(std::vector<std::vector<T>>& matrix1, std::vector<std::vector<T>>& matrix2) {
    size_t rows = matrix1.size();
    size_t cols = matrix2[0].size();
    std::vector<std::vector<T>> matrix(rows, std::vector<T>(cols, 0));
    for (size_t i = 0; i < cols; i++) {
        for (size_t j = 0; j < rows; j++) {
            for (size_t k = 0; k < rows; k++) {
                matrix.at(j).at(i) += ((matrix2.at(k).at(i)) * (matrix1.at(j).at(k)));
            } 
        }
    }
    return matrix;
}

//Elementary row operations
//Permute equations/switch order
template <typename T>
void swapRows(std::vector<std::vector<T>>& matrix, size_t row1, size_t row2) {
    std::swap(matrix[row1], matrix[row2]);
}

//Multiply a row by a scalar
template <typename T>
void multiplyRow(std::vector<std::vector<T>>& matrix, size_t row, T scalar) {
    for (auto& element : matrix[row])
    {
        element *= scalar;
    }
}

//Add a multiple of one row to another
template <typename T>
void addRows(std::vector<std::vector<T>>& matrix, size_t changedRow, size_t unchangedRow, T scalar) {
    for (size_t i = 0; i < matrix.size(); i++) {
        matrix[changedRow][i] += (matrix[unchangedRow][i] * scalar);
    }
}

//Asks user to enter a matrix and returns that matrix
template <typename T>
std::vector<std::vector<T>> getMatrix() {
    int rows;
    int cols;
    char ex; 
    std::cout << "Enter the dimensions of your matrix (example: 3x3): ";
    std::cin >> rows >> ex >> cols;

    std::vector<std::vector<T>> matrix(rows, std::vector<T>(cols, 0));
    for (size_t i = 0; i < rows; i++) {
        std::cout << "Enter the values of row " << i+1 << " (e.x. 2 5 7): ";
        for (size_t j = 0; j < cols; j++) {
            T value;
            std::cin >> value;
            matrix.at(i).at(j) = value;
        }
        std::cout << std::endl;
    }
    return matrix;
}



int main(){
    std::string userInput;
    std::cout << "Type in the calculation you want to make: \n"<< "[addMatrices]\n" << "[multiplyMatrices]\n";
    std::cin >> userInput;


    if (userInput == "addMatrices") {
        auto matrix1 = getMatrix<double>();
        auto matrix2 = getMatrix<double>();
        if (matrix1.size() == matrix2.size() && matrix1[0].size() == matrix2[0].size() ) {
        auto matrix3 = addMatrices(matrix1,matrix2);
        printMatrix(matrix1);
        std::cout << "+\n";
        printMatrix(matrix2);
        std::cout << "=\n";
        printMatrix(matrix3);
        } else {
            std::cout << "Dimensions do not match";
        }
    } else if (userInput == "multiplyMatrices") {
        auto matrix1 = getMatrix<double>();
        auto matrix2 = getMatrix<double>();
        if (matrix1.size() == matrix2[0].size() && matrix1[0].size() == matrix2.size() ) {
        auto matrix3 = multiplyMatrices(matrix1,matrix2);
        printMatrix(matrix1);
        std::cout << "*\n";
        printMatrix(matrix2);
        std::cout << "=\n";
        printMatrix(matrix3);
        } else {
            std::cout << "Dimensions do not match";
        }
    }

    return 0;
}