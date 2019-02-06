#include "pch.h"
#include <iostream>
using namespace std;



class SparseRow
{
protected:
	int row;
	int col;
	int value;
public:
	SparseRow(); // default constructor
	SparseRow(int, int, int); // non-default constructor
	SparseRow(const SparseRow& anotherRow); // copy constructor
	friend ostream& operator<< (ostream& s, const SparseRow& thisOne);
	void display();
	~SparseRow();

	// getters and setters
	int getColumn();
	int getValue();
	int getRow();
	void setColumn(int);
	void setValue(int);
	void setRow(int);

};

// default constructor
SparseRow::SparseRow()
{
	row = -1;
	col = -1;
	value = 0;
}

// non-default constructor
SparseRow::SparseRow(int r, int c, int val)
{
	row = r;
	col = c;
	value = val;
}

// copy constructor
SparseRow::SparseRow(const SparseRow& anotherOne)
{
	row = anotherOne.row;
	col = anotherOne.col;
	value = anotherOne.value;
}

// ostream operator overload
ostream& operator<< (ostream& s, const SparseRow& thisOne)
{
	s << thisOne.row << ", " << thisOne.col << ", " << thisOne.value << "\n";
	return s;
}

// displays the row's data
void SparseRow::display()
{
	cout << "SparseRow data: " << row << ", " << col << ", " << value << "\n";
}

// destructor
SparseRow::~SparseRow()
{
	cout << "SparseRow " << row << ", " << col << ", " << value << " has been destroyed.\n";

}

// getters for all public fields in SparseRow
int SparseRow::getRow()
{
	return row;
}
int SparseRow::getColumn()
{
	return col;
}
int SparseRow::getValue()
{
	return value;
}

// setters for all public fields in SparseRow
void SparseRow::setRow(int r)
{
	row = r;
}
void SparseRow::setColumn(int c)
{
	col = c;
}
void SparseRow::setValue(int val)
{
	value = val;
}


class SparseMatrix
{
protected:
	int noRows;
	int noCols;
	int commonValue;
	int noNonSparseValues;
	SparseRow* myMatrix;
public:
	SparseMatrix(); // default constructor
	SparseMatrix(int, int, int, int); // non-default constructor
	SparseMatrix(const SparseMatrix& anotherOne); // copy constructor
	friend ostream& operator<< (ostream& s, const SparseMatrix& thisOne); // ostream operator overload
	SparseMatrix* Transpose(); // transposes the matrix
	SparseMatrix* Multiply(SparseMatrix& M); // multiplies two matrices
	SparseMatrix* Add(SparseMatrix& M); // adds two matrices
	void display(); // displays the Sparse/matrix data
	void displayMatrix(); // displays the matrix in form, with the common value

	// getters and setters
	int getNoRows();
	int getNoCols();
	int getCommonValue();
	int getNoNonSparseValues();
	SparseRow* getMyMatrix();
	void setNoRows(int);
	void setNoCols(int);
	void setCommonValue(int);
	void setNoNonSparseValues(int);
	void setMyMatrix(SparseRow* M);
};

// default constructor
SparseMatrix::SparseMatrix()
{
	noRows = -1;
	noCols = -1;
	commonValue = 0;
	noNonSparseValues = -1;
}

// non-default constructor
SparseMatrix::SparseMatrix(int nr, int nc, int cv, int noNSV)
{
	noRows = nr;
	noCols = nc;
	commonValue = cv;
	noNonSparseValues = noNSV;
	myMatrix = new SparseRow[noNSV];
}

// copy constructor
SparseMatrix::SparseMatrix(const SparseMatrix& anotherOne)
{
	noRows = anotherOne.noRows;
	noCols = anotherOne.noCols;
	commonValue = anotherOne.commonValue;
	noNonSparseValues = anotherOne.noNonSparseValues;
	myMatrix = new SparseRow[noNonSparseValues];
}

// ostream operator overload
ostream& operator<< (ostream& s, const SparseMatrix& thisOne)
{
	s << "";
	for(int i = 0; i < thisOne.noNonSparseValues; i++)
	{
		s << thisOne.myMatrix[i];
	}
	return s;
}

// transposes the matrix
SparseMatrix* SparseMatrix::Transpose()
{
	return new SparseMatrix();
}

// multiplies two matrices
SparseMatrix* SparseMatrix::Multiply(SparseMatrix& M)
{
	return new SparseMatrix();
}

// adds two matrices
SparseMatrix* SparseMatrix::Add(SparseMatrix& M)
{
	return new SparseMatrix();
}

// displays SparseMatrix data
void SparseMatrix::display()
{
	cout << noRows << ", " << noCols << ", " << commonValue << ", " << noNonSparseValues << "\n";
	for (int i = 0; i < noNonSparseValues; i++)
	{
		myMatrix[i].display();
	}
}

// displays the matrix in form, with the common value
void SparseMatrix::displayMatrix()
{
	for (int r = 0; r < noRows; r++)
	{
		cout << "{";
		for (int c = 0; c < noCols; c++)
		{
			int val = commonValue;
			for (int i = 0; i < noNonSparseValues; i++)
			{
				if ((myMatrix[i].getRow() == r) && (myMatrix[i].getColumn() == c))
					val = myMatrix[i].getValue();
			}
			cout << val << " ";
		}
		cout << "}\n";
	}
}

// getters for all public fields in SparseMatrix
int SparseMatrix::getNoRows()
{
	return noRows;
}
int SparseMatrix::getNoCols()
{
	return noCols;
}
int SparseMatrix::getCommonValue()
{
	return commonValue;
}
int SparseMatrix::getNoNonSparseValues()
{
	return noNonSparseValues;
}
SparseRow* SparseMatrix::getMyMatrix()
{
	return myMatrix;
}

// setters for all public fields in SparseMatrix
void SparseMatrix::setNoRows(int nr)
{
	noRows = nr;
}
void SparseMatrix::setNoCols(int nc)
{
	noCols = nc;
}
void SparseMatrix::setCommonValue(int cv)
{
	commonValue = cv;
}
void SparseMatrix::setNoNonSparseValues(int noNSV)
{
	noNonSparseValues = noNSV;
}
void SparseMatrix::setMyMatrix(SparseRow* M)
{
	myMatrix = M;
}


int main()
{
	SparseRow *first = new SparseRow(0, 2, 900);
	SparseRow *second = new SparseRow(1, 3, 450);
	SparseRow *third = new SparseRow(3, 0, 127);
	SparseRow* temp = new SparseRow[3];
	temp[0] = *first;
	temp[1] = *second;
	temp[2] = *third;

	SparseMatrix *test = new SparseMatrix(4, 4, 0, 3);
	test->setMyMatrix(temp);
	test->display();
	cout << endl;
	test->displayMatrix();

}