#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

class Fraction
{
public:
	long long int numerator, denom;

	void setFraction(long long int newNumerator, long long int newDenom = 0)
	{
		if (newDenom == 0)
		{
			numerator = newNumerator;
			denom = 1;
		}
		else if (newNumerator % newDenom == 0)
		{
			numerator = newNumerator / newDenom;
			denom = 1;
		}
		else
		{
			numerator = newNumerator;
			denom = newDenom;
		}
	}

	long long int gcd(long long int a, long long int b)
	{
		while (b != 0)
		{
			long long int temp = b;
			b = a % b;
			a = temp;
		}

		return a;
	}

	void transformation(long long int newNumerator, long long int newDenom)
	{
		if (denom != 1 && newDenom != 1)
		{
			numerator = numerator * newDenom;
			denom = denom * newNumerator;

		}
		else if (denom != 1 && newDenom == 1)
		{
			numerator = numerator * newDenom;
			denom = denom * newNumerator;

		}
		else if (denom == 1 && newDenom != 1)
		{
			numerator = numerator * newDenom;
			denom = denom * newNumerator;

		}
		else if (denom == 1 && newDenom == 1)
		{
			numerator = numerator * newDenom;
			denom = denom * newNumerator;

		}

		if (denom < 0)
		{
			denom = abs(denom);
			numerator = -numerator;
		}

		long long int resGCD = gcd(numerator, denom);

		numerator = numerator / resGCD;
		denom = denom / resGCD;
	}

	void swapSign()
	{
		if (denom < 0)
		{
			denom = abs(denom);
			numerator = -numerator;
		}
	}

	void calculateRect(long long int numerator1, long long int denom1, long long int numerator2, long long int denom2, long long int numerator3, long long int denom3)
	{
		long long int mulNumerator, mulDenom;
		multiply(numerator1, denom1, numerator2, denom2, &mulNumerator, &mulDenom);
		
		long long int divNumerator, divDenom;
		division(mulNumerator, mulDenom, numerator3, denom3, &divNumerator, &divDenom);
		
		if (divNumerator != 0)
		{
			long long int subNumerator, subDenom;
			substraction(numerator, denom, divNumerator, divDenom, &subNumerator, &subDenom);
			
			long long int resGCD = gcd(subNumerator, subDenom);

			numerator = subNumerator / resGCD;
			denom = subDenom / resGCD;
		}
	}

	void multiply(long long int numerator1, long long int denom1, long long int numerator2, long long int denom2, long long int* resNumerator, long long int* resDenom)
	{
		*resNumerator = numerator1 * numerator2;
		*resDenom = denom1 * denom2;
	}

	void division(long long int numerator1, long long int denom1, long long int numerator2, long long int denom2, long long int* resNumerator, long long int* resDenom)
	{
		if (denom1 != 1 && denom2 != 1)
		{
			*resNumerator = numerator1 * denom2;
			*resDenom = denom1 * numerator2;
		}
		else if (denom1 != 1 && denom2 == 1)
		{
			*resNumerator = numerator1 * denom2;
			*resDenom = denom1 * numerator2;
		}
		else if (denom1 == 1 && denom2 != 1)
		{
			*resNumerator = numerator1 * denom2;
			*resDenom = numerator2;
		}
		else if (denom1 == 1 && denom2 == 1)
		{
			*resNumerator = numerator1 * denom2;
			*resDenom = numerator2;
		}

		if (*resDenom < 0)
		{
			*resDenom = abs(*resDenom);
			*resNumerator = -(*resNumerator);
		}
	}

	void substraction(long long int numerator1, long long int denom1, long long int numerator2, long long int denom2, long long int* resNumerator, long long int* resDenom)
	{
		if (denom1 == denom2)
		{
			*resNumerator = numerator1 - numerator2;
			*resDenom = denom1;
		}
		else
		{
			long long int maximum = (denom1 > denom2) ? denom1 : denom2;
			long long int lcm;

			while (1)
			{
				if ((maximum % denom1 == 0) && (maximum % denom2 == 0))
				{
					lcm = maximum;
					break;
				}
				else ++maximum;
			}

			long long int mul1 = lcm / denom1;
			long long int mul2 = lcm / denom2;

			numerator1 *= mul1;
			numerator2 *= mul2;

			*resNumerator = numerator1 - numerator2;
			*resDenom = lcm;
		}
	}

	void printFraction()
	{
		if (numerator == denom)
		{
			cout << 1 << "   ";
		}
		else if (numerator == 0)
		{
			cout << 0 << "   ";
		}
		else if (denom == 1)
		{
			cout << numerator << "   ";
		}
		else
		{
			cout << numerator << "/" << denom << " ";
		}
	}
};

bool ifEmpty(Fraction** mat, long long int row, long long int col, long long int n)
{
	for (long long int j = col; j < n - 1; j++)
	{
		if (mat[row][j].numerator == 0) continue;
		else
		{
			return false;
		}
	}
	return true;
}

bool NoSolution(Fraction** matrix, long long int row, long long int n)
{
	bool flag = false;

	for (long long int j = 0; j < n - 1; j++)
	{
		if (matrix[row][j].numerator == 0) continue;
		else
		{
			flag = true;
			break;
		}
	}

	if ((matrix[row][n - 1].numerator != 0) && (flag == false)) return true;
	else return false;
}

bool Zero(Fraction** matrix, long long int row, long long int col, long long int n)
{
	bool flag = false;

	for (long long int j = col; j < n - 1; j++)
	{
		if (matrix[row][j].numerator == 0) continue;
		else
		{
			flag = true;
			break;
		}
	}

	if (flag == false) return true;
	else return false;
}

void printSolutions(Fraction** matrix, long long int m, long long int n, long long int* answer)
{
	long long int numRow = 0;
	cout << endl;
	for (long long int i = 0; i < n - 1; i++)
	{
		if (answer[i] != -1)
		{
			cout << "x" << i + 1 << " =";
			if (matrix[numRow][n - 1].numerator != 0)
			{
				if (matrix[numRow][n - 1].numerator < 0)
				{
					if (matrix[numRow][n - 1].denom == 1) cout << " -" << abs(matrix[numRow][n - 1].numerator);
					else cout << " -" << abs(matrix[numRow][n - 1].numerator) << "/" << matrix[numRow][n - 1].denom;
				}
				else if (matrix[numRow][n - 1].numerator > 0)
				{
					if (matrix[numRow][n - 1].denom == 1) cout << " " << abs(matrix[numRow][n - 1].numerator);
					else cout << " " << abs(matrix[numRow][n - 1].numerator) << "/" << matrix[numRow][n - 1].denom;
				}
			}
			else
			{
				if (Zero(matrix, numRow, n - 1, n)) cout << " 0";
			}

			for (long long int j = answer[i] + 1; j < n - 1; j++)
			{
				if (matrix[numRow][j].numerator > 0)
				{
					if (matrix[numRow][j].denom == 1) cout << " - (" << abs(matrix[numRow][j].numerator) << ")x" << j + 1;
					else cout << " - (" << abs(matrix[numRow][j].numerator) << "/" << matrix[numRow][j].denom << ")x" << j + 1;
				}
				else if (matrix[numRow][j].numerator < 0)
				{
					if (matrix[numRow][j].denom == 1) cout << " + (" << abs(matrix[numRow][j].numerator) << ")x" << j + 1;
					else cout << " + (" << abs(matrix[numRow][j].numerator) << "/" << matrix[numRow][j].denom << ")x" << j + 1;
				}
			}
			numRow++;
			cout << endl;
		}
		else
		{
			cout << "x" << i + 1 << " - any" << endl;
		}
	}
}

void Solution(Fraction** matrix, long long int m, long long int n)
{
	long long int* answer = new long long int[n - 1];

	for (long long int i = 0; i < n - 1; i++) answer[i] = -1;

	long long int k = 0;

	long long int lastDetected = 0;

	for (long long int i = 0; i < m; i++)
	{
		for (long long int j = lastDetected; j < n - 1; j++)
		{
			if (matrix[i][j].numerator == 1)
			{
				answer[k] = j;
				lastDetected = j+1;
				k++;
				break;
			}
			else if (matrix[i][j].numerator == 0)
			{
				if (Zero(matrix, i, j, n))
				{
					break;
				}
				else
				{
					k++;
				}
			}
		}
	}

	printSolutions(matrix, m, n, answer);
}

int main()
{
	long long int m, n;

	ifstream file("matrix.txt");

	if (!file.is_open())
	{
		std::cerr << "Unable to open file" << std::endl;
		return 1;
	}

	file >> m >> n;

	Fraction** matrix = new Fraction * [m];
	for (long long int i = 0; i < m; i++) matrix[i] = new Fraction[n];

	vector<vector<long long int>> tempMatrix(m, vector<long long int>(n));

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			file >> tempMatrix[i][j];
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i][j].setFraction(tempMatrix[i][j]);
		}
	}

	for (long long int i = 0; i < m; i++)
	{
		for (long long int j = 0; j < n; j++)
		{
			matrix[i][j].setFraction(tempMatrix[i][j]);
		}
	}

	for (long long int q = 0, k = 0; (k < n - 1) && (q < m); q++, k++)
	{
		if (ifEmpty(matrix, q, k, n))
		{
			k--;
		}
		else if (matrix[q][k].numerator == 0)
		{
			q--;
		}
		else
		{
			for (long long int j = k + 1; j < n; j++)
			{
				for (long long int i = 0; i < m; i++)
				{
					if (i == q) continue;
					else
					{
						matrix[i][j].calculateRect(matrix[i][k].numerator, matrix[i][k].denom, matrix[q][j].numerator, matrix[q][j].denom, matrix[q][k].numerator, matrix[q][k].denom);
					}
				}
			}

			long long int tempNum = matrix[q][k].numerator, tempDenom = matrix[q][k].denom;
			for (long long int i = k; i < n; i++)
			{
				matrix[q][i].transformation(tempNum, tempDenom);
			}

			for (long long int i = 0; i < m; i++)
			{
				if (i == q) continue;
				else
				{
					matrix[i][k].setFraction(0);
				}
			}
		}

		for (long long int i = 0; i < m; i++)
		{
			for (long long int j = 0; j < n; j++) matrix[i][j].swapSign();
		}

		for (long long int i = 0; i < m; i++)
		{
			for (long long int j = 0; j < n; j++)
			{
				matrix[i][j].printFraction();
			}
			cout << endl;
		}
		cout << endl;
	}

	bool ifNoSolution;

	for (long long int i = 0; i < m; i++)
	{
		ifNoSolution = NoSolution(matrix, i, n);
		if (ifNoSolution) break;
	}

	if (ifNoSolution)
	{
		cout << "The system has no solutions";
	}
	else
	{
		Solution(matrix, m, n);
	}


	return 0;
}
