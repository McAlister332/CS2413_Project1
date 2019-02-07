#include "pch.h"
#include <iostream>
using namespace std;


/*
a class representing a value in a specific row and column of a matrix.
*/
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

/*
a class representing a matrix with only a few values that differ from the common value.
*/
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
	SparseRow* temp = new SparseRow[noNonSparseValues];
	for (int i = 0; i < noNonSparseValues; i++)
	{
		temp[i].setRow(myMatrix[i].getColumn());
		temp[i].setColumn(myMatrix[i].getRow());
		temp[i].setValue(myMatrix[i].getValue());
	}

	SparseMatrix *newMatrix = new SparseMatrix(noCols, noRows, commonValue, noNonSparseValues);
	newMatrix->setMyMatrix(temp);
	//newMatrix->displayMatrix(); // check line
	return newMatrix;
}

// multiplies two matrices
SparseMatrix* SparseMatrix::Multiply(SparseMatrix& M)
{
	SparseRow* A = myMatrix;
	SparseRow* B = M.getMyMatrix();
	SparseMatrix *temp = new SparseMatrix(noRows, M.getNoCols(), commonValue, 0);

	int noNSV = noNonSparseValues;
	int mNSV = M.getNoNonSparseValues();
	int length = noNSV + mNSV;

	for (int i = 0; i < noRows; i++)
	{
		for (int j = 0; j < noCols; j++)
		{

			int val = 0;

			for (int k = 0; k < noNSV; k++)
			{

				for (int h = 0; h < mNSV; h++)
				{

					if ((A[k].getRow() == i) && (B[h].getColumn() == j))
					{

						if (A[k].getColumn() == B[h].getRow())
						{
							val += A[k].getValue() * B[h].getValue();
							
						}

					}

				}

			}

			(*temp).myMatrix[(*temp).noNonSparseValues].setRow(i);
			(*temp).myMatrix[(*temp).noNonSparseValues].setColumn(j);
			//(*temp).myMatrix[(*temp).noNonSparseValues++].setValue(val);

		}
	}
	temp->displayMatrix();
	return temp;
}

// adds two matrices
SparseMatrix* SparseMatrix::Add(SparseMatrix& M)
{
	
	int noNSV = noNonSparseValues;
	int mNSV = M.getNoNonSparseValues();
	int length = noNSV + mNSV;

	SparseMatrix* temp = new SparseMatrix(noRows, noCols, commonValue, noNSV + mNSV);

	int i = 0;
	int j;
	bool found;
	int valueToAdd;

	bool* mArray = new bool[mNSV];
	for (int k = 0; k < mNSV; k++)
	{
		mArray[k] = false;
	}

	while (i < noNSV)
	{
		j = 0;
		found = false;
		valueToAdd = 0;

		(*temp).myMatrix[(*temp).noNonSparseValues].setRow(myMatrix[i].getRow());
		(*temp).myMatrix[(*temp).noNonSparseValues].setColumn(myMatrix[i].getColumn());

		while ((j < mNSV) && (!found)) {
			if ((myMatrix[i].getRow() == M.myMatrix[j].getRow()) &&
				(myMatrix[i].getColumn() == M.myMatrix[j].getColumn()))
			{
				found = true;
				valueToAdd = M.myMatrix[j].getValue();
				mArray[j] = true;
			}
			else
				j++;
		}

		(*temp).myMatrix[(*temp).noNonSparseValues++].setValue(myMatrix[i].getValue() + valueToAdd);
		i++;
	}

	for (int k = 0; k < mNSV; k++)
	{
		if (!mArray[k])
		{
			(*temp).myMatrix[(*temp).noNonSparseValues].setRow(myMatrix[k].getRow());
			(*temp).myMatrix[(*temp).noNonSparseValues].setColumn(myMatrix[k].getColumn());
			//(*temp).myMatrix[(*temp).noNonSparseValues++].setValue(myMatrix[k].getValue());
		}
	}


	return temp;
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
	SparseRow *first = new SparseRow(0, 0, 2);
	SparseRow *second = new SparseRow(0, 1, 2);
	SparseRow *third = new SparseRow(0, 2, 2);
	SparseRow *fourth = new SparseRow(2, 1, 7);
	SparseRow* temp1 = new SparseRow[3];
	SparseRow* temp2 = new SparseRow[3];
	temp1[0] = *first;
	temp1[1] = *second;
	temp1[2] = *third;
	temp2[0] = *first;
	temp2[1] = *second;
	temp2[2] = *fourth;
	SparseMatrix *test1 = new SparseMatrix(3, 3, 0, 3);
	SparseMatrix *test2 = new SparseMatrix(3, 3, 0, 3);
	test1->setMyMatrix(temp1);
	test2->setMyMatrix(temp2);
	
	//test1->display();
	cout << endl;
	test2->displayMatrix();

	SparseMatrix* temp = (*test1).Transpose();
	//(*temp).display();
	cout << endl;
	//(*temp).displayMatrix();

	temp = (*test1).Add((*test2));
	(*temp).display();
	cout << endl;
	(*temp).displayMatrix();

	/*
	temp = (*test1).Multiply((*test1));
	(*temp).display();
	cout << endl;
	(*temp).displayMatrix();
	*/

	/*
	int n, m, cv, noNSV;
	SparseMatrix* temp;

	cin >> n >> m >> cv >> noNSV;
	SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);

	//Write the Statements to read in the first matrix

	cin >> n >> m >> cv >> noNSV;
	SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);

	//Write the Statements to read in the second matrix

	cout << "First one in sparse matrix format" << endl;
	(*firstOne).display();

	cout << "First one in normal matrix format" << endl;
	(*firstOne).displayMatrix();

	cout << "Second one in sparse matrix format" << endl;
	(*secondOne).display();

	cout << "Second one in normal matrix format" << endl;
	(*secondOne).displayMatrix();



	cout << "After Transpose first one in normal format" << endl;
	temp = (*firstOne).Transpose();
	(*temp).displayMatrix();

	cout << "After Transpose second one in normal format" << endl;
	temp = (*secondOne).Transpose();
	(*temp).displayMatrix();


	cout << "Multiplication of matrices in sparse matrix form:" << endl;
	temp = (*secondOne).Multiply(*firstOne);
	(*temp).display();

	cout << "Addition of matrices in sparse matrix form:" << endl;
	temp = (*secondOne).Add(*firstOne);
	(*temp).display();

	*/
}