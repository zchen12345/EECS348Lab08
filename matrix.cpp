/*
Program name: matrix operations
Purpose: display all matrix oepration based on the requirement for Lab7
Input: userinput text file, for certain operation, user input row. column and value to update in the matrix
Output: all matrix operations including addition, multiplication, diagonal sums, row/column swap and element update
All collaborators: Copliot (GitHub AI)
Author: Zhang Chen
Creation date: 4/2/25
*/
// include require librarys and headers for matrix operations
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <utility>
#include <limits>
//declared namespace std for ease of use
using namespace std;

// Define a type alias for Matrix to improve readability
using Matrix = vector<vector<int>>;

// Task 1: Load matrices from file
bool loadMatricesFromFile(const string& filename, int& N, Matrix& A, Matrix& B) {
    // Open the file for reading
    ifstream file(filename);
    // Check if the file was opened successfully
    if (!file.is_open()) return false;
    // Read the size of the matrices (N)
    file >> N;
    // Check if N is a valid size for matrices
    if (N <= 0) return false;
    // Resize the matrices A and B to N x N
    A.resize(N, vector<int>(N));
    // Read matrix A from the file by using a nested for loop
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (!(file >> A[i][j])) return false;
    // Read matrix B from the file by using a nested for loop
    B.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (!(file >> B[i][j])) return false;
    //return true if all matrices are loaded successfully
    return true;
}

// Task 1: Print matrix with formatting
void printMatrix(const Matrix& mat) {
    //a for loop to iterate through each row of the matrix and print it in a formatted way
    for (const auto& row : mat) {
        for (int val : row)
        // setw(4) is used to set the width of each element to 4 characters for better alignment
            cout << setw(4) << val;
        //space between each element for better readability
        cout << endl;
    }
}

// Task 2: Matrix addition
Matrix addMatrices(const Matrix& A, const Matrix& B) {
    //set N as the size of A, since it should N x N matrices, whihc is the same for B
    int N = A.size();
    Matrix result(N, vector<int>(N));
    // A nested for loop to iterate through each element of the matrices A and B, adding corresponding elements together
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            result[i][j] = A[i][j] + B[i][j];
    //return the result of addition
    return result;
}

// Task 3: Matrix multiplication
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    //set N as the size of A, since it should N x N matrices, whihc is the same for B
    int N = A.size();
    //A nested for loop to perform matrix multiplication, initializing the result matrix with zeros
    Matrix result(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                result[i][j] += A[i][k] * B[k][j];
    //return the result of multiplication
    return result;
}

// Task 4: Diagonal sums
pair<int, int> sumDiagonals(const Matrix& mat) {
    //initialize the main and secondary diagonal sums to zero
    int main = 0, secondary = 0;
    // initialize N as the size of the matrix, since it should be N x N matrices
    int N = mat.size();
    // a for loop to iterate through each row of the matrix to calculate the sums of the main and secondary diagonals
    for (int i = 0; i < N; ++i) {
        main += mat[i][i];
        secondary += mat[i][N-1 - i];
    }
    //return the result of the sum
    return {main, secondary};
}

// Task 5: Swap rows
void swapRows(Matrix& mat, int r1, int r2) {
    //initailzed the matrix size as N
    int N = mat.size();
    //check if the provided row indices are valid, if not print an error message and return
    if (r1 < 0 || r1 >= N || r2 < 0 || r2 >= N) {
        cout << "Invalid row indices!" << endl;
        return;
    }
    // Swap the rows r1 and r2 in the matrix using std::swap
    swap(mat[r1], mat[r2]);
}

// Task 6: Swap columns
void swapColumns(Matrix& mat, int c1, int c2) {
    //initailzed the matrix size as N
    int N = mat.size();
    //check if the provided column indices are valid, if not print an error message and return
    if (c1 < 0 || c1 >= N || c2 < 0 || c2 >= N) {
        cout << "Invalid column indices!" << endl;
        return;
    }
    // Swap the columns c1 and c2 in the matrix by iterating through each row and swapping the elements at the specified column indices
    for (int i = 0; i < N; ++i)
        swap(mat[i][c1], mat[i][c2]);
}

// Task 7: Update element
void updateElement(Matrix& mat, int row, int col, int value) {
    //initailzed the matrix size as N
    int N = mat.size();
    //check if the provided row and column indices are valid, if not print an error message and return
    if (row < 0 || row >= N || col < 0 || col >= N) {
        cout << "Invalid indices!" << endl;
        return;
    }
    //set the value of the specified element in the matrix to the new value provided by the user
    mat[row][col] = value;
}

//declared a main function to execute the program
int main() {
    //string to hold the filename for input
    string filename;
    //display a prompt to the user to enter the input filename
    cout << "Enter input filename: ";
    // Read the filename from user input
    cin >> filename;

    //set a integer N to hold the size of the matrices
    int N;
    //created matrix A and B
    Matrix A, B;
    //if failed to load matrices from the file, print an error message and return 1 to indicate failure
    if (!loadMatricesFromFile(filename, N, A, B)) {
        cerr << "Error loading matrices!" << endl;
        return 1;
    }
    // Successfully loaded matrices, print their sizes
    cout << "\nMatrix A:\n";
    //print matrix A
    printMatrix(A);
    cout << "\nMatrix B:\n";
    //print matrix B
    printMatrix(B);

    // Matrix addition
    cout << "\nA + B:\n";
    // Call the addMatrices function to add A and B, and print the result
    printMatrix(addMatrices(A, B));

    // Matrix multiplication
    cout << "\nA * B:\n";
    // Call the multiplyMatrices function to multiply A and B, and print the result
    printMatrix(multiplyMatrices(A, B));

    // Diagonal sums
    // call the sumDiagonals function for both matrices A to get their diagonal sums
    auto aDiags = sumDiagonals(A);
    //set it to a pair of integers for main and secondary diagonals
    int aMain = aDiags.first, aSec = aDiags.second;
    // call the sumDiagonals function for both matrices B to get their diagonal sums
    auto bDiags = sumDiagonals(B);
    //set it to a pair of integers for main and secondary diagonals
    int bMain = bDiags.first, bSec = bDiags.second;
    //output the diagonal sums for both matrices A and B
    cout << "\nMatrix A diagonals - Main: " << aMain << ", Secondary: " << aSec << endl;
    cout << "Matrix B diagonals - Main: " << bMain << ", Secondary: " << bSec << endl;

    // Swap rows with user input
    cout << "\nThis below operation will swap the row for a matrix\n";
    //declared a character matrixChoice to allow the user to select which matrix they want to swap rows in
    char matrixChoice;
    //ask the user to enter which matrix they want to swap rows in, either A or B
    cout << "\nEnter the matrix to swap row(A/B):\n";
    // Read the user's choice for the matrix to swap rows in
    cin >> matrixChoice;
    //if the input is invalid (not A or B), clear the input stream and print an error message, 
    //and continue to the next step of the program
    if (cin.fail() || (toupper(matrixChoice) != 'A' && toupper(matrixChoice) != 'B')) {
        cout << "Invalid input!" << endl;
        cin.clear();
        // code provide by Copilot to clear the input stream in case of invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //else proceed with the selected matrix for swapping rows
    }else{
        // Select the matrix based on user input, A or B
    Matrix& selectedMat = (toupper(matrixChoice) == 'A') ? A : B;
    // Create a temporary matrix to perform the row swap operation, initialized with the selected matrix
    Matrix temp = selectedMat; 
    //initialized two integer variables r1 and r2 to hold the row indices for swapping
    int r1, r2;
    //ask user for the initial row indices to swap in the selected matrix, ensuring it is within the valid range (0 to N-1)
    cout << "\nEnter the intial row indices to swap in Matrix" << "(0-" << N-1 << "): ";
    // Read the initial row indices from user input
    cin >> r1;
    //ask user for the final row indices to swap in the selected matrix, ensuring it is within the valid range (0 to N-1)
    cout << "\n Enter the final row indices to swap in Matrix" << "(0-" << N-1 << "): ";
    // Read the final row indices from user input
    cin >> r2;
    // Check if the input is valid (both indices are within the range of 0 to N-1), if not vaild, print a error message
    // and move on to the next function
    if (cin.fail() || r1 < 0 || r1 >= N || r2 < 0 || r2 >= N) {
        cout << "Invalid row!" << endl;
        cin.clear();
        // code provide by Copilot to clear the input stream in case of invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //if vaild, proceed with the swap operation
    }else{
    //swap the row
    swapRows(temp, r1, r2);
    //print a statement to indicate the matrix after the swap operation, including which rows were swapped
    cout << "\nMatrix" << matrixChoice << " after swapping rows " << r1 << " and " << r2 << ":\n";
    //print the swapped matrix
    printMatrix(temp);
    }
}

    // Swap columns with user input
    cout << "\nThis below operation will swap the column for a matrix\n";
    //declared a character matrixChoice_1 to allow the user to select which matrix they want to swap rows in
    char matrixChoice_1;
    //ask the user to enter which matrix they want to swap rows in, either A or B
    cout << "\nEnter the matrix to swap column(A/B):\n";
    // Read the user's choice for the matrix to swap column in
    cin >> matrixChoice_1;
    //if the input is invalid (not A or B), clear the input stream and print an error message, 
    //and continue to the next step of the program
    if (cin.fail() || (toupper(matrixChoice_1) != 'A' && toupper(matrixChoice_1) != 'B')) {
        cout << "Invalid input!" << endl;
        cin.clear();
        // code provide by Copilot to clear the input stream in case of invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //else proceed with the selected matrix for swapping columns
    }else{
        // Select the matrix based on user input, A or B
    Matrix& selectedMat_1 = (toupper(matrixChoice_1) == 'A') ? A : B;
    // Create a temporary matrix to perform the column swap operation, initialized with the selected matrix
    Matrix temp_1 = selectedMat_1; 
    //initialized two integer variables c1 and c2 to hold the column indices for swapping
    int c1, c2;
    //ask user for the initial column indices to swap in the selected matrix, ensuring it is within the valid range (0 to N-1)
    cout << "\nEnter the intial column indices to swap in Matrix"<< matrixChoice_1 <<" (0-" << N-1 << "): ";
    //Read the initial column indices from user input
    cin >> c1;
    //ask user for the final column indices to swap in the selected matrix, ensuring it is within the valid range (0 to N-1)
    cout << "\n Enter the final column indices to swap in Matrix" << matrixChoice_1 << " (0-" << N-1 << "): ";
    // Read the final column indices from user input
    cin >> c2;
    // Check if the input is valid (both indices are within the range of 0 to N-1), if not valid, print a error message
    // and move on to the next function
        if (cin.fail() || c1 < 0 || c1 >= N || c2 < 0 || c2 >= N) {
        cout << "Invalid column!" << endl;
        cin.clear();
        // code provide by Copilot to clear the input stream in case of invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // If the input is valid, proceed with the column swap operation
    }else{
    //swap the columns
    swapColumns(temp_1, c1, c2);
    //print a statement to indicate the matrix after the swap operation, including which columns were swapped
    cout << "\nMatrix"<< matrixChoice <<"after swapping columns " << c1 << " and " << c2 << ":\n";
    //print the swapped matrix
    printMatrix(temp_1);
    }
}

    // Update element with user input
    cout << "\nThis below operation will update a element in a matrix\n";
    //declared a character matrixChoice_2 to allow the user to select which matrix they want to swap element in
    char matrixChoice_2;
    //ask the user to enter which matrix they want to swap element in, either A or B
    cout << "\nEnter the matrix to swap element(A/B):\n";
    // Read the user's choice for the matrix to swap element in
    cin >> matrixChoice_2;
    //if the input is invalid (not A or B), clear the input stream and print an error message,
    //and continue to the next step of the program
    if (cin.fail() || (toupper(matrixChoice_2) != 'A' && toupper(matrixChoice_2) != 'B')) {
        cout << "Invalid input!" << endl;
        cin.clear();
        // code provide by Copilot to clear the input stream in case of invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //else proceed with the selected matrix for updating an element
    }else{
        // Select the matrix based on user input, A or B
    Matrix& selectedMat_3 = (toupper(matrixChoice_2) == 'A') ? A : B;
    // Create a temporary matrix to perform the element update operation, initialized with the selected matrix
    Matrix temp_2 = selectedMat_3; 
    //initialized three integer variables to hold the row, column and value for updating the element in the matrix
    int row, col, value;
    // ask user for the row index to update in the selected matrix, ensuring it is within the valid range (0 to N-1)
    cout << "\nEnter row index to update in Matrix "<< matrixChoice <<" (0-" << N-1 << "): ";
    // Read the row index from user input
    cin >> row;
    // ask user for the column index to update in the selected matrix, ensuring it is within the valid range (0 to N-1)
    cout << "\nEnter column index to update in Matrix "<< matrixChoice <<" (0-" << N-1 << "): ";
    // read the column index from user input
    cin >> col;
    //ask user for the value to update in the selected matrix
    cout << "\nEnter value to update in Matrix "<< matrixChoice <<": ";
    // Read the value from user input
    cin >> value;
    // Check if the input is valid (both row and column indices are within the range of 0 to N-1),
    // if not valid, print a error message, and move on to the next function
    if (cin.fail() || row < 0 || row >= N || col < 0 || col >= N) {
        cout << "Invalid indices!" << endl;
        cin.clear();
        // code provide by Copilot to clear the input stream in case of invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //else if the input is valid, proceed with the element update operation
    }else{
        //update the element in the temporary matrix with the new value provided by the user
    updateElement(temp_2, row, col, value);
    //print a statement to indicate the matrix after the update operation, including which element was updated and its new value
    cout << "\nMatrix A after updating element (" << row << "," << col << "):\n";
    //print the updated matrix
    printMatrix(temp_2);
            }
        }
        //return 0 to indicate successful completion of the program
        return 0;
    }