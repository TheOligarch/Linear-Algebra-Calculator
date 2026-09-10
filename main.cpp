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
    std::cout<<std::endl;

}

//Adds two matrices together and returns the resulting matrix; assumes the matrices are the same size
template <typename T>
std::vector<std::vector<T>> addMatrices(std::vector<std::vector<T>>& matrix1, std::vector<std::vector<T>>& matrix2) {
    //Getting bounds and initilizing new empty matrix to store values to
    size_t rows = matrix1.size();
    size_t cols = matrix1[0].size();
    std::vector<std::vector<T>> matrix(rows, std::vector<T>(cols, 0));
    //Iterate through each element within a row, each row within the matrix; adding corresponding elements together
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
    for (size_t i = 0; i < matrix[0].size(); i++) {
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

//Turns a matrix into its Reduced Row-Echelon form and returns that matrix
template <typename T>
std::vector<std::vector<T>> RREF(std::vector<std::vector<T>>& matrix) {
    //Initialize bounds
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    //Find first non-zero column, working from last column to first column
    int colTracker = cols;
    for(int i = cols-1; i > -1; i--) {
        for (int j = rows-1; j > -1; j--) {
            if (matrix.at(j).at(i) != 0) {
                colTracker = i;
            }
        }
    }

    int leadingOne = 0; //Tracks position of the leading 1
    std::vector<int> pivotTracker; //Contains the index of all columns that are pivot columns
    //First, row echelon reduce
    //Iterates through each column
    while (colTracker < cols) {
        //Working only within columns right now
        //Get the first non-zero number in that column into the top row or the toppest row below a leading 1 row, and then makes that number 1
        for(int i = leadingOne; i < rows; i++) {
            if (matrix.at(i).at(colTracker) != 0 ) {
                if (i == leadingOne) {
                    std::cout<< "No rowswapping necessary" << i << colTracker << std::endl;
                    printMatrix(matrix);
                    multiplyRow(matrix,i,1.0);
                    printMatrix(matrix);
                    std::cout<<"turn to 1 by multiplying by " << (1.0/(matrix.at(leadingOne).at(colTracker)));
                    printMatrix(matrix);
                    multiplyRow(matrix,i,(1.0/(matrix.at(leadingOne).at(colTracker))));
                    printMatrix(matrix);
                    pivotTracker.push_back(colTracker);
                    break;
                } else {
                    std::cout<<"Rowswap " << i<< " "<< (leadingOne) << std::endl;
                    printMatrix(matrix);
                    swapRows(matrix,(leadingOne),i);
                    printMatrix(matrix);
                    std::cout<<"turn to 1 by multiplying by " << (1.0/(matrix.at(leadingOne).at(colTracker)));
                    printMatrix(matrix);
                    multiplyRow(matrix,(leadingOne),(1.0/(matrix.at(leadingOne).at(colTracker))));
                    printMatrix(matrix);
                    pivotTracker.push_back(colTracker);
                    break;
                }
            }
        }

        //Zero out that column under the leading 1
        for(size_t i = (leadingOne+1); i < rows; i++) {
            if (matrix.at(i).at(colTracker) != 0) {
                std::cout<<"zeroing out a row. LeadingOne: " << leadingOne << "changing row" << i << " scalar is " << ((matrix.at(i).at(colTracker))/(matrix.at(leadingOne).at(colTracker))) ;
                printMatrix(matrix);
                addRows(matrix, i, leadingOne, (-1.0 * ((matrix.at(i).at(colTracker))/(matrix.at(leadingOne).at(colTracker))) ));
                printMatrix(matrix);
            }
        }
        //increase colTracker by 1
        colTracker++;
        leadingOne++;
    }
    colTracker--;
    leadingOne--;
    std::cout<<"Now in REF form, reduce to RREF";
    //Now that we have it in REF form, we work backwards and convert to RREF
    while (colTracker > 0) {
            //Only executes if it is a pivot column
            if (std::find(pivotTracker.begin(), pivotTracker.end(), colTracker) != pivotTracker.end()) {
                for (int i = leadingOne-1; i > -1; i--) {
                    std::cout<<"zeroing out a row. LeadingOne: " << leadingOne << "changing row" << i << " scalar is " << ((matrix.at(i).at(colTracker))/(matrix.at(leadingOne).at(colTracker))) ;
                    printMatrix(matrix);
                    addRows(matrix, i, leadingOne, (-1.0 * ((matrix.at(i).at(colTracker))/(matrix.at(leadingOne).at(colTracker))) ));
                    printMatrix(matrix);
                }
            }
        colTracker--;
        leadingOne--;
    }
    return matrix;
}

//Performs the Gauss Jordan elimination technique on an augmented matrix and returns the matrix back
template <typename T>
std::vector<std::vector<T>> gaussJordan(std::vector<std::vector<T>>& matrix) {
    //Initialize bounds
    size_t rows = matrix.size();
    size_t cols = matrix[0].size()-1;

    //Find first non-zero column, working from last column to first column
    int colTracker = cols;
    for(int i = cols-1; i > -1; i--) {
        for (int j = rows-1; j > -1; j--) {
            if (matrix.at(j).at(i) != 0) {
                colTracker = i;
            }
        }
    }

    int leadingOne = 0; //Tracks position of the leading 1
    std::vector<int> pivotTracker; //Contains the index of all columns that are pivot columns
    //First, row echelon reduce
    //Iterates through each column
    while (colTracker < cols) {
        //Working only within columns right now
        //Get the first non-zero number in that column into the top row or the toppest row below a leading 1 row, and then makes that number 1
        for(int i = leadingOne; i < rows; i++) {
            if (matrix.at(i).at(colTracker) != 0 ) {
                if (i == leadingOne) {
                    std::cout<< "No rowswapping necessary" << i << colTracker << std::endl;
                    printMatrix(matrix);
                    multiplyRow(matrix,i,1.0);
                    printMatrix(matrix);
                    std::cout<<"turn to 1 by multiplying by " << (1.0/(matrix.at(leadingOne).at(colTracker)));
                    printMatrix(matrix);
                    multiplyRow(matrix,i,(1.0/(matrix.at(leadingOne).at(colTracker))));
                    printMatrix(matrix);
                    pivotTracker.push_back(colTracker);
                    break;
                } else {
                    std::cout<<"Rowswap " << i<< " "<< (leadingOne) << std::endl;
                    printMatrix(matrix);
                    swapRows(matrix,(leadingOne),i);
                    printMatrix(matrix);
                    std::cout<<"turn to 1 by multiplying by " << (1.0/(matrix.at(leadingOne).at(colTracker)));
                    printMatrix(matrix);
                    multiplyRow(matrix,(leadingOne),(1.0/(matrix.at(leadingOne).at(colTracker))));
                    printMatrix(matrix);
                    pivotTracker.push_back(colTracker);
                    break;
                }
            }
        }

        //Zero out that column under the leading 1
        for(size_t i = (leadingOne+1); i < rows; i++) {
            if (matrix.at(i).at(colTracker) != 0) {
                std::cout<<"zeroing out a row. LeadingOne: " << leadingOne << "changing row" << i << " scalar is " << ((matrix.at(i).at(colTracker))/(matrix.at(leadingOne).at(colTracker))) ;
                printMatrix(matrix);
                addRows(matrix, i, leadingOne, (-1.0 * ((matrix.at(i).at(colTracker))/(matrix.at(leadingOne).at(colTracker))) ));
                printMatrix(matrix);
            }
        }
        //increase colTracker by 1
        colTracker++;
        leadingOne++;
    }
    colTracker--;
    leadingOne--;
    std::cout<<"Now in REF form, reduce to RREF";
    //Now that we have it in REF form, we work backwards and convert to RREF
    while (colTracker > 0) {
            //Only executes if it is a pivot column
            if (std::find(pivotTracker.begin(), pivotTracker.end(), colTracker) != pivotTracker.end()) {
                for (int i = leadingOne-1; i > -1; i--) {
                    std::cout<<"zeroing out a row. LeadingOne: " << leadingOne << "changing row" << i << " scalar is " << ((matrix.at(i).at(colTracker))/(matrix.at(leadingOne).at(colTracker))) ;
                    printMatrix(matrix);
                    addRows(matrix, i, leadingOne, (-1.0 * ((matrix.at(i).at(colTracker))/(matrix.at(leadingOne).at(colTracker))) ));
                    printMatrix(matrix);
                }
            }
        colTracker--;
        leadingOne--;
    }
    return matrix;
}

//Finds the rank of a matrix and returns it
template <typename T>
int rank(std::vector<std::vector<T>>& matrix) {
    matrix = gaussJordan(matrix);
    int counter = 0; //Adds 1 every time there is a nonzero row
    for (const auto& row : matrix) {
        for(const auto& element : row) {
            if (element != 0) {
                counter++;
                break;
            }
        }
    }
    return counter;
}

//Checks the invertability of a matrix using the rank
template <typename T>
bool invertability(std::vector<std::vector<T>>& matrix) {
    //Checks if rank(A) = n and if the matrix is square
    if (rank(matrix) == matrix.size() && matrix.size() == matrix[0].size()) {
        return true;
    } else {
        return false;
    }
}




int main(){

    std::string userInput;
    std::cout << "Type in the calculation you want to make: \n"<< 
    "[addMatrices]\n" << 
    "[multiplyMatrices]\n" <<
    "[RREF]\n" <<
    "[gaussJordan]\n" <<
    "[rank]\n" <<
    "[invertability]\n";
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
    } else if (userInput == "RREF") {
        auto matrix1 = getMatrix<double>();
        printMatrix(RREF(matrix1));
    } else if (userInput == "gaussJordan") {
        auto matrix1 = getMatrix<double>();
        printMatrix(gaussJordan(matrix1));
    } else if (userInput == "rank") {
        auto matrix1 = getMatrix<double>();
        int rankOfMatrix = rank(matrix1);
        std::cout<<"Rank(A) = " << rankOfMatrix << std::endl;
    } else if (userInput == "invertability") {
        auto matrix1 = getMatrix<double>();
        if (invertability(matrix1)) {
            std::cout <<"This matrix is invertable";
        } else {
            std::cout << "This matrix is not invertable";
        }
    }
    return 0;
}