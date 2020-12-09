#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

vector<int> BozoSort(vector<int> arr,bool boolbnik = true);
vector<vector<int>> BozoSort(vector<vector<int>>, bool boolbnik = true);
vector<int> BozoSort(int a, int b, int c, bool boolbnik=true);

bool sorted(vector<int>arr);
bool sorted(vector<vector<int>>);

vector<int> reverse(vector<int> arr);
vector<vector<int>> reverse(vector<vector<int>> arr);

vector<int> swap(vector<int> arr, int first, int second);
vector<vector<int>> swap(vector<vector<int>> matrix, int first[], int second[]);

int main()
{	
	vector<int> input_vector;
	vector<vector<int>> matrix;
	int n,input;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> input;
		input_vector.push_back(input);
	}
	n = 0;
	for (int i = 0; i < sqrt(input_vector.size()); i++)
	{
		vector<int>temp;
		for (int j = 0; j < sqrt(input_vector.size()); j++)
		{
			temp.push_back(input_vector[n]);
			n++;
		}
		matrix.push_back(temp);
	}
	
	vector<int>sorted_arr=BozoSort(input_vector);
	for (auto item : sorted_arr)
	{
		cout << item << ' ';
	}
	cout << endl;
	sorted_arr = BozoSort(input_vector,false);
	for (auto item : sorted_arr)
		cout << item << ' ';
	cout << endl;
	vector<vector <int>> sorted_matrix = BozoSort(matrix);
	for (int i=0; i < sorted_matrix.size(); i++)
	{
		for (int j = 0; j < sorted_matrix.size(); j++)
		{
			cout << sorted_matrix[i][j]<<' ';
		}
	}
	cout << endl;
	vector<vector <int>> rev_sorted_matrix =reverse( BozoSort(matrix));
	for (int i = 0; i < rev_sorted_matrix.size(); i++)
	{
		for (int j = 0; j < rev_sorted_matrix.size(); j++)
		{
			cout << rev_sorted_matrix[i][j] << ' ';
		}
	}
	cout << endl;
	int a = input_vector[0], b = input_vector[1], c = input_vector[2];
	vector<int> sorted_abc = BozoSort(a, b, c);
	for (int i = 0; i < 3; i++)
	{
		cout << sorted_abc[i] << ' ';
	}
	cout << endl;
	vector<int> rev_sorted_abc = reverse(BozoSort(a, b, c));
	for (int i = 0; i < 3; i++)
	{
		cout << rev_sorted_abc[i] << ' ';
	}
 }
vector<int> reverse(vector<int> arr)
{
	vector<int> rev_arr;
	for (int i = arr.size(); i > 0; i--)
	{

		rev_arr.push_back(arr[i - 1]);
	}
	return rev_arr;
}
vector<vector<int>> reverse(vector<vector<int>> matrix)
{
	vector<vector<int>> rev_matrix;
	for (int i = 0; i < matrix.size(); i++)
	{
		vector<int>temp;
		for (int j=0; j < matrix.size(); j++)
		{
			temp.push_back(0);
		}
		rev_matrix.push_back(temp);
	}
	for (int i = matrix[0].size(); i > 0; i--)
	{
		for (int j = matrix[0].size(); j > 0; j--)
		{
			rev_matrix[matrix.size() - i ][matrix.size() - j ] = matrix[i-1][j-1];
		}
	}
	return rev_matrix;
}
bool sorted(vector<int>arr)
{
	for (int i = 0; i < arr.size() - 1; i++)
	{
		if (arr[i] < arr[i + 1])
		{
			continue;
		}
		else
			return 1;
	}
	return 0;
}
bool sorted(vector<vector<int>> matrix)
{
	for (int i = 0; i < matrix[0].size(); i++)
	{
		for (int j = 0; j < matrix[0].size()-1; j++)
		{
			if (matrix[i][j] < matrix[i][j+1])
			{
				continue;
			}
			else
			{
				return 1;
			}
		}
		if (i<matrix[0].size()-1) {
			if (matrix[i + 1][0] > matrix[i][matrix[0].size()-1])
			{
				continue;
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}
vector<int> swap(vector<int> arr, int first, int second)
{
	int temp = arr[first]; 
	arr[first] = arr[second];
	arr[second] = temp;
	return arr;
}

vector<vector<int>> swap(vector<vector<int>> matrix,vector<vector<int>> points)
{	
	int temp = matrix[points[0][0]][points[0][1]];
	matrix[points[0][0]][points[0][1]] = matrix[points[1][0]][points[1][1]];
	matrix[points[1][0]][points[1][1]] = temp;
	return matrix;
}
vector<int> BozoSort(vector<int> arr , bool boolbnik)
{
	while (sorted(arr)) 
	{
		int first_rand = rand() % arr.size(), sec_rand = rand() % arr.size() ;
		while (sec_rand == first_rand)
			sec_rand = rand() % arr.size();
		arr = swap(arr, first_rand, sec_rand);
	}
	if (boolbnik) {
		return arr;
	}
	else {
		return reverse(arr);
	}
}
vector<vector<int>> BozoSort(vector<vector<int>> matrix, bool boolbnik)
{
	while (sorted(matrix)) {
		vector<vector<int>> points;
		for (int i = 0; i < 2; i++) {
			vector <int>temp;
			for (int j = 0; j < 2; j++)
			{
				temp.push_back(rand() % matrix[0].size());
			}
			points.push_back(temp);
		}
		while (points[0][0] == points[1][0] && points[0][1] == points[1][1])
		{
			points[1][0] = rand() % matrix[0].size();
			points[1][1] = rand() % matrix[0].size();
		}
		matrix = swap(matrix, points);
	  }
	if (boolbnik) {
		return matrix;
		}
	else {
		return reverse(matrix);
		}
	}
	vector<int> BozoSort(int a, int b, int c, bool boolbnik)
	{
		while (!(a < b && b < c))
		{	
			int temp;
			int ran = rand() % 4;
			switch (rand()%4)
			{
			case 0:
				temp=a;
				a = b;
				b = temp;
				break;
			case 1:
				temp = a;
				a = c;
				c = temp;
				break;
			case 2:
				temp = b;
				b = c;
				c = temp;
				break;
			default:
				break;
			}
		}
		vector<int> vec_abc = { a,b,c };
		return vec_abc;
	}
