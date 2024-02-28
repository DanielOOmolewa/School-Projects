// CMSC 341 - Fall 2020 - Project 1
#include "csr.h"

CSR::CSR(){
    m_values = nullptr;
    m_col_index = nullptr;
    m_row_index = nullptr;
    m_nonzeros = 0;
    m_m = 0;
    m_n = 0;
    m_next = nullptr;
}

CSR::~CSR(){
    clear();
    m_next = nullptr;
}

CSR::CSR(const CSR & rhs) {
    m_next = nullptr;
    //If the source matrix is not empty then copy its content into the copy matrix
    if (!rhs.empty())
    {
        //Set the static member variables to the corresponding static member variables of the source matrix
        m_nonzeros = rhs.m_nonzeros;
        m_m = rhs.m_m;
        m_n = rhs.m_n;
        //Allocate space for the dynamically allocated arrays
        m_values = new int[m_nonzeros];
        m_col_index = new int[m_nonzeros];
        m_row_index = new int[m_m + 1];
        //Enter the elements from the arrays of the source matrix into the corresponding arrays
        for (int i = 0; i < m_nonzeros; i++)
        {
            m_values[i] = rhs.m_values[i];
            m_col_index[i] = rhs.m_col_index[i];
        }
        for (int i = 0; i < m_m + 1; i++)
        {
            m_row_index[i] = rhs.m_row_index[i];
        }
    }
    //Otherwise run clear
    else
    {
        clear();
    }
}

void CSR::dump(){
    cout << endl;
    if (!empty()){
        for (int i=0;i<m_nonzeros;i++)
            cout << m_values[i] << " ";
        cout << endl;
        for (int i=0;i<m_nonzeros;i++)
            cout << m_col_index[i] << " ";
        cout << endl;
        for (int i=0;i<m_m+1;i++)
            cout << m_row_index[i] << " ";
    }
    else
        cout << "The object is empty!";
    cout << endl;
}

void CSR::clear(){
    //Deallocate memory of the dynamically allocated member variables
    delete m_values;
    delete m_col_index;
    delete m_row_index;
    //Set the rest of the memory variables to 0
    m_nonzeros = 0;
    m_m = 0;
    m_n = 0;
}

bool CSR::empty() const{
    //If any of the arrays are empty return false, otherwise return true
    if (m_m == 0 || m_n == 0)
    {
        return true;
    }
    return false;
}

void CSR::compress(int m, int n, int array[], int arraySize){
    //Deallocate memory of the member variables
    clear();

    int ind = 0; //Keeps track of the indices for m_values and m_col_index;
    int a_sum = 0; // Keeps track of the accumulated number of values for m_row_index

    //Traverse the given array and count the number of non-zero values
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i] != 0)
        {
            m_nonzeros++;
        }
    }

    //Allocate memory for m_values, m_col_index, and m_row_index
    m_values = new int[m_nonzeros];
    m_col_index = new int[m_nonzeros];
    m_row_index = new int[m_m+1];
    //Make sure that the first element of m_row_index is always 0
    m_row_index[0] = a_sum;
    m_m = m;
    m_n = n;
    //Using the row-by-row scanning pattern, pop each non-zero value into m_value and
    //and the corresponding column index in m_col_index while incrementing a_sum.
    //After going through a row, pop a_sum into m_row_index
    for (int i = 0; i < m_m; i++)
    {
        for (int j = 0; j < m_n; j++)
        {
            if (array[i*m_n + j] != 0)
            {
                m_values[ind] = array[i*m_n + j];
                m_col_index[ind] = j;
                ind++;
                a_sum++;
            }
        }
        m_row_index[i+1] = a_sum;
    }
}

int CSR::getAt(int row, int  col) const{
    //If the given row and col are out of bounds or if the matrix is empty, throw the
    //the corresponding exception
    if (row > m_m || row < 0 || col > m_n || col < 0)
    {
        throw range_error("CSR::getAt(): attempt to get value that's out of scope");
    }
    else if (empty())
    {
        throw range_error("CSR::getAt(): attempt to get value from empty matrix");
    }
    //Otherwise, get and return the value according to the coordinate
    int row_start = m_row_index[row];
    int row_end = m_row_index[row+1];
    int ind = 0;
    for (int i = row_start; i < row_end; i++)
    {
        if (m_col_index[i] == col)
        {
            ind = i;
        }
    }
    return m_values[ind];
} 

bool CSR::operator==(const CSR & rhs) const{
    //If there are any discrepancies between the integer member variables of the copy and source matrix,
    //return false
    if (m_nonzeros != rhs.m_nonzeros)
    {
        return false;
    }
    if (m_m != rhs.m_m)
    {
        return false;
    }
    if (m_n != rhs.m_n)
    {
        return false;
    }
    //Traverse each array and if there are any discrepancies from between an element of the copy matrix
    //and source matrix return false.
    for (int i = 0; i < m_nonzeros; i++)
    {
        if (m_values[i] != rhs.m_values[i])
        {
            return false;
        }
    }
    for (int i = 0; i < m_nonzeros; i++)
    {
        if (m_col_index[i] != rhs.m_col_index[i])
        {
            return false;
        }
    }
    for (int i = 0; i < m_m + 1; i++)
    {
        if (m_row_index[i] != rhs.m_row_index[i])
        {
            return false;
        }
    }
    //If there are no discrepancies found whatsoever, return true
    return true;
}

int CSR::sparseRatio(){

    float sparseRatio = 0; //The sparse ratio
    float totalSize = 0; //The total size of the original array
    float numZeros = 0; //The number of zeroes found in the array
    //After getting the total size and number of zeroes, find and return the sparse ratio
    totalSize = m_m * m_n;
    numZeros = totalSize - m_nonzeros;
    sparseRatio = (numZeros/totalSize) * 100;

    return sparseRatio;
}