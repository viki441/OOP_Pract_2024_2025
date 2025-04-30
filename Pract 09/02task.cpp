#include <iostream>
#include <cmath>
#include <fstream> 
#include <stdexcept>
#include <cstdlib>
#include <ctime>
//x++ - lvalue -> A operator++(int);
//++x - rvalue -> A& operator++(); 
/*
a++ increments firts and then returns the result
++a makes a copy and then increments and then returns the copy
*/

class Matrix {
private:
	int rows = 2;
	int cols = 2;
	int** matrix;
	
	//for the matrix
	void freeDynamic()
	{
		if (matrix)
		{
			for (int i = 0; i < rows; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;
			matrix = nullptr;
			rows = 0;
			cols = 0;
		}
	}

	void copyDynamic(const Matrix& other)
	{
		rows = other.rows;
		cols = other.cols;

		matrix = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
			matrix[i] = new int[cols];
			for (int j = 0; j < cols; j++)
			{
				matrix[i][j] = other.matrix[i][j];
			}
		}
	}


public:

	//helper function for sum
	int sumElements() const
	{
		int sum = 0;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				sum += matrix[i][j];
			}
		}
		return sum;
	}

	Matrix(int rows, int cols) : rows(rows), cols(cols)
	{
		matrix = new int* [rows];

		for (int i = 0; i < rows; i++)
		{
			matrix[i] = new int[cols];
			for (int j = 0; j < cols; ++j)
			{
				matrix[i][j] = i;
					//rand() % 100;
			}
		}
	}

	Matrix(const Matrix& other)
		:rows(other.rows), cols(other.cols)
	{
		copyDynamic(other);

	}

	Matrix& operator=(const Matrix& other)
	{
		if (this != &other)
		{
			freeDynamic();
			copyDynamic(other);
		}
		return *this;
	}

	~Matrix()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	void print() const {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
	}


	//addition +=
	Matrix& operator+=(const Matrix& otherMatrix)
	{
		if (cols != otherMatrix.cols || rows != otherMatrix.rows)
		{
			throw std::logic_error("invalid matrixes\n");
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				matrix[i][j] += otherMatrix.matrix[i][j];
			}
		}
		return *this;
	}

	//addition +
	Matrix operator+(const Matrix& otherMatrix)
	{
		Matrix result(*this);
		result += otherMatrix;
		return result;
	}

	//substract -=
	Matrix& operator-=(const Matrix& otherMatrix)
	{
		if (cols != otherMatrix.cols || rows != otherMatrix.rows)
		{
			throw std::logic_error("invalid matrixes\n");
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				matrix[i][j] -= otherMatrix.matrix[i][j];
			}
		}
		return *this;
	}

	//substract -
	Matrix operator-(const Matrix& otherMatrix)
	{
		Matrix result(*this);
		result -= otherMatrix;
		return result;
	
	}
	//++z
	Matrix& operator++()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				matrix[i][j]++;
			}
		}
		return *this;
	}
	//z++
	Matrix operator++(int)
	{
		Matrix temp(*this);
		++(*this);
		return temp;
	}
	//--z
	Matrix& operator--()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				matrix[i][j]--;
			}
		}
		return *this;
	}
	//z--
	Matrix operator--(int)
	{
		Matrix temp(*this);
		--(*this);
		return temp;
	}

	//*=
	Matrix& operator*=(const int num)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				matrix[i][j] *= num;
			}
		}
		return *this;
	}

	//*
	Matrix operator*(int num) const
	{
		Matrix result(*this);
		result *= num;
		return result;
	}

	//==
	bool operator==(const Matrix& otherMatrix) const
	{
		/*if (rows != otherMatrix.rows || cols != otherMatrix.cols) {
			return false;
		}*/
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (matrix[i][j] != otherMatrix.matrix[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	//!=
	bool operator!=(const Matrix& otherMatrix)
	{
		return !(*this == otherMatrix);
	}

	//[]
	int* operator[](int rowIndex) 
	{
		if (rowIndex < 0 || rowIndex >= rows)
		{
			throw std::out_of_range("Invalid row index");
		}
		return matrix[rowIndex];
	}

	const int* operator[](int rowIndex) const 
	{
		if (rowIndex < 0 || rowIndex >= rows)
		{
			throw std::out_of_range("Invalid row index");
		}	
		return matrix[rowIndex];
	}

	//files
	friend std::ofstream& operator<<(std::ofstream& writeFile, const Matrix& v);
	friend std::ifstream& operator>>(std::ifstream& readFile, Matrix& v);
	
	//operators < > <= =>
	//to prevent double summing, make ints
	bool operator<(const Matrix& otherMatrix) const
	{
		int sum1 = this->sumElements();
		int sum2 = otherMatrix.sumElements();
		return sum1 < sum2;
	}
	bool operator>(const Matrix& otherMatrix) const
	{
		int sum1 = this->sumElements();
		int sum2 = otherMatrix.sumElements();
		return sum1 > sum2;
	}
	bool operator<=(const Matrix& otherMatrix) const
	{
		int sum1 = this->sumElements();
		int sum2 = otherMatrix.sumElements();
		return sum1 <= sum2;
	}
	bool operator>=(const Matrix& otherMatrix) const
	{
		int sum1 = this->sumElements();
		int sum2 = otherMatrix.sumElements();
		return sum1 >= sum2;
	}

	//operator ()
	Matrix operator()()
	{
		Matrix transponed(cols, rows);

		for (int i = 0; i < rows; ++i)
			{
			for (int j = 0; j < cols; ++j)
				{
					transponed.matrix[j][i] = matrix[i][j];
				}
			}
			return transponed;
		}

	//check if matrix is 0
	operator bool() const
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (matrix[i][j] != 0)
				{
					return false;
				}
			}
		}
		return true;
	}

};



std::ofstream& operator<<(std::ofstream& writeFile, const Matrix& otherMatrix)
{
	writeFile << otherMatrix.rows << " " << otherMatrix.cols;

	for (int i = 0; i < otherMatrix.rows; ++i) 
	{
		for (int j = 0; j < otherMatrix.cols; ++j) 
		{
			writeFile << otherMatrix.matrix[i][j] << " ";
		}
		writeFile << "\n";
	}
	return writeFile;
}

std::ifstream& operator>>(std::ifstream& readFile, Matrix& otherMatrix)
{
	int r,c;
	readFile >> r >> c;
	otherMatrix.freeDynamic();
	otherMatrix.rows = r;
	otherMatrix.cols = c;
	otherMatrix.matrix = new int* [r];
	for (int i = 0; i < r; ++i)
	{
		otherMatrix.matrix[i] = new int[c];
		for (int j = 0; j < c; ++j)
		{
			readFile >> otherMatrix.matrix[i][j];
		}
	}
	return readFile;
}

int main() {

	srand(time(0));

	Matrix m1(2,2);
	Matrix m2(2, 2);
	Matrix m22(2, 3);
	Matrix m3(3, 3);
	Matrix m4(4, 4);
	try 
	{	
		 //m4();
	
	}
	catch (const std::logic_error& e)
	{
		std::cerr << e.what();
	}
	catch (const std::out_of_range& e) 
	{
		std::cerr << e.what();
	}
	if (m4) 
	{
		m4.print();
	}
	else
	{
		std::cout << "hell nah";
	}
	
}
