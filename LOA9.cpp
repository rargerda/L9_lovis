#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <stack>
#include <fstream> 

#define X 1

using namespace std; // ��������� ��� ������������� ������������ ���� std

struct Node 
{
	int data;
	Node* next;
};

// ������� ��� ��������� ������ ��� ��������� ������
int** createMatrix(int size)
{
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
	}
	return matrix;
}

// ������� ��� ���������� ������� ���������� ����������
void fillMatrixRandom(int** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			if (i == j) {
				matrix[i][j] = 0;
			}
			else {
				int randomValue = rand() % 2;
				matrix[i][j] = randomValue;
				matrix[j][i] = randomValue; // ������� �����������
			}
		}
	}
}

// ������� ��� ������ ������� � ����������
void printMatrix(int** matrix, int size)
{
	cout << "\n������� ���������:" << endl;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << matrix[i][j];
			cout << " ";

		}
		cout << endl;
	}
}

// ������� ��� ������������ ������, ���������� ��� �������
void deleteMatrix(int** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

// ������� ������ ������ ��������� 
void printAdjacencyList(Node** adjacencyList, int size) 
{
	for (int i = 0; i < size; i++)
	{
		cout << "������� " << i << " ������ �: ";
		Node* current = adjacencyList[i];
		while (current != nullptr) 
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
}

// ������� ������������ ������, ���������� ��� ������ ��������� 
void freeAdjacencyList(Node** adjacencyList, int size)
{
	for (int i = 0; i < size; i++)
	{
		Node* current = adjacencyList[i];
		while (current != nullptr)
		{
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] adjacencyList;
}

// ������� �������� ������� ��������� � ������ ��������� � �������� �������� �������� ������
Node** adjacencyMatrixToAdjacencyList(int** matrix, int size) 
{
	Node** adjacencyList = new Node * [size];

	for (int i = 0; i < size; i++) 
	{
		adjacencyList[i] = nullptr;  // ������������� ������ ��� ������� ������� 

		// ���� � �������� �������, ����� �������� �������� ������� � �������� �������
		for (int j = size - 1; j >= 0; j--) 
		{ 
			if (matrix[i][j] == 1) 
			{
				Node* newNode = new Node;
				newNode->data = j;
				newNode->next = adjacencyList[i];
				adjacencyList[i] = newNode;
			}
		}
	}
	return adjacencyList;
}

void bfsDistanceList(Node** adjacencyList, int size, int startVertex, int* distances) 
{
	for (int i = 0; i < size; i++) 
	{
		distances[i] = -1;  // �������������� ���������� ��� "�� ����������"
	}

	queue<int> q;  // ������� ������� ��� BFS
	distances[startVertex] = 0;  // ��������� ������� ����� ���������� 0
	q.push(startVertex);  // �������� ��������� ������� � �������

	while (!q.empty()) 
	{
		int currentVertex = q.front();
		q.pop();

		Node* adjacentNode = adjacencyList[currentVertex];
		while (adjacentNode != nullptr) 
		{
			int neighbor = adjacentNode->data;
			if (distances[neighbor] == -1) 
			{
				distances[neighbor] = distances[currentVertex] + 1;
				q.push(neighbor);
			}
			adjacentNode = adjacentNode->next;
		}
	}
}

// ������� ��� ������ ���������� � ����� � �������������� ������� ���������
void bfsDistanceMatrix(int** matrix, int size, int startVertex, int* distances) 
{
	bool* visited = new bool[size];

	for (int i = 0; i < size; i++) 
	{
		distances[i] = -1; // �������������� ���������� ��� "�� ����������"
		visited[i] = false; // �������������� ��� ������� ��� �� ����������
	}

	queue<int> q; // ������� ������� ��� BFS
	distances[startVertex] = 0; // ��������� ������� ����� ���������� 0
	visited[startVertex] = true; // �������� ��������� ������� ��� ����������
	q.push(startVertex); // �������� ��������� ������� � �������

	while (!q.empty()) 
	{
		int currentVertex = q.front();
		q.pop();

		for (int neighbor = 0; neighbor < size; neighbor++) 
		{
			if (matrix[currentVertex][neighbor] == 1 && !visited[neighbor]) 
			{
				distances[neighbor] = distances[currentVertex] + 1;
				visited[neighbor] = true;
				q.push(neighbor);
			}
		}
	}
	delete[] visited;
}

void dfsDistanceMatrix(int** matrix, int size, int startVertex, int* distances) 
{
	bool* visited = new bool[size];

	for (int i = 0; i < size; i++) 
	{
		distances[i] = -1;
		visited[i] = false;
	}

	stack<int> s;
	distances[startVertex] = 0;
	visited[startVertex] = true;
	s.push(startVertex);

	while (!s.empty()) {
		int currentVertex = s.top();
		s.pop();

		for (int neighbor = 0; neighbor < size; neighbor++)
		{
			if (matrix[currentVertex][neighbor] == 1 && !visited[neighbor]) 
			{
				distances[neighbor] = distances[currentVertex] + 1;
				visited[neighbor] = true;
				s.push(neighbor);
			}
		}
	}
	delete[] visited;
}

void dfsDistanceList(Node** adjacencyList, int size, int startVertex, int* distances) 
{
	bool* visited = new bool[size];

	for (int i = 0; i < size; i++) 
	{
		distances[i] = -1;
		visited[i] = false;
	}

	stack<int> s;
	distances[startVertex] = 0;
	visited[startVertex] = true;
	s.push(startVertex);

	while (!s.empty()) 
	{
		int currentVertex = s.top();
		s.pop();

		Node* adjacentNode = adjacencyList[currentVertex];
		while (adjacentNode != nullptr) {
			int neighbor = adjacentNode->data;
			if (!visited[neighbor]) {
				distances[neighbor] = distances[currentVertex] + 1;
				visited[neighbor] = true;
				s.push(neighbor);
			}
			adjacentNode = adjacentNode->next;
		}
	}
	delete[] visited;
}

int main() 
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	int choice;

	cout << "\t\t\t\t\t\t  9 ������������ ������" << endl;

	do 
	{
		// ���������� ����
		cout << "����:" << endl;
		cout << "1) ��������� ����� � ����� ����������" << endl;
		cout << "2) ���� ���������� ������ ����������(��������� � ����� \"Result.txt\")" << endl;
		cout << "3) �����" << endl;

		// ���� ������ ������ 
		cout << "\n";
		cout << "����������, ������� ����� ���������� ������: ";
		cin >> choice;
		cout << "\n";

		// ��������� ������ ������������
		switch (choice) 
		{
		// ������� �1
		case 1: 
		{
			cout << "�� ������� ����� 1." << endl;
			// ����� ����� ���������� ��� ��� ���������� �������� ������ 1
			int size;
			cout << "\n������� ������ ������� ���������: ";
			cin >> size;
			int** adjacencyMatrix = createMatrix(size);
			fillMatrixRandom(adjacencyMatrix, size);
			printMatrix(adjacencyMatrix, size);

			// Convert the adjacency matrix to an adjacency list and print it
			cout << "\n������ ���������:\n";
			Node** adjacencyList = adjacencyMatrixToAdjacencyList(adjacencyMatrix, size);
			printAdjacencyList(adjacencyList, size);

			// ����� ������� ������ ���������� � ��������� ��������� �������
			int startVertex;
			cout << "\n������� ��������� ������� ��� ������ ����������: ";
			cin >> startVertex;

			if (startVertex >= 0 && startVertex < size) 
			{
				int* distances = new int[size];
				bfsDistanceList(adjacencyList, size, startVertex, distances);

				cout << "\nBFSD list: ���������� �� ������� " << startVertex << " �� ������ ������:\n";
				for (int i = 0; i < size; i++) 
				{
					cout << "������� " << i << ": " << distances[i] << endl;
				}


				bfsDistanceMatrix(adjacencyMatrix, size, startVertex, distances);

				cout << "\nBFSD matrix: ���������� �� ������� " << startVertex << " �� ������ ������:\n";
				for (int i = 0; i < size; i++) 
				{
					cout << "������� " << i << ": " << distances[i] << endl;
				}

				dfsDistanceMatrix(adjacencyMatrix, size, startVertex, distances);

				cout << "\nDFSD matrix: ���������� �� ������� " << startVertex << " �� ������ ������:\n";
				for (int i = 0; i < size; i++) 
				{
					cout << "������� " << i << ": " << distances[i] << endl;
				}

				dfsDistanceList(adjacencyList, size, startVertex, distances);

				cout << "\nDFSD list: ���������� �� ������� " << startVertex << " �� ������ ������:\n";
				for (int i = 0; i < size; i++) 
				{
					cout << "������� " << i << ": " << distances[i] << endl;
				}
				cout << "\n";
				delete[] distances;

			}
			else 
			{
				cout << "\n";
				cout << "������: ������� ������������ ��������� �������." << endl;
			}

			// ������������ ������
			deleteMatrix(adjacencyMatrix, size);
			freeAdjacencyList(adjacencyList, size);

			break;
		}
		// ������� �2
		case 2: 
		{
			cout << "�� ������� ����� 2." << endl;
			// ����� ����� ���������� ��� ��� ���������� �������� ������ 2

			int num_vertex;
			cout << "\n������� ���������� ������ �����: ";
			cin >> num_vertex;
			cout << "\n";

			// ������ ����� ��� ������ 
			int* sizes = new int[X];

			for (int i = 0; i < X; i++)
			{
				*(sizes + i) = num_vertex;

			}

			// ������ � ������, ������ �����������
			ofstream outputFile("Result.txt");
			if (!outputFile.is_open()) 
			{
				cerr << "������. ��������� ������� ����." << endl;
				return 1;
			}

			outputFile << "Matrix size\t  bfsDList\t  bfsDMatrix\t  dfsDMatrix\t  dfsDList\n";

			for (int i = 0; i < 1; i++) 
			{
				int size = sizes[i];
				int** adjacencyMatrix = createMatrix(size);
				fillMatrixRandom(adjacencyMatrix, size);

				Node** adjacencyList = adjacencyMatrixToAdjacencyList(adjacencyMatrix, size);
				int startVertex = 0;
				int* distances = new int[size];

				clock_t startTime, endTime;

				startTime = clock();
				bfsDistanceList(adjacencyList, size, startVertex, distances);
				endTime = clock();
				double bfsDistanceListTime = double(endTime - startTime) / CLOCKS_PER_SEC;

				startTime = clock();
				bfsDistanceMatrix(adjacencyMatrix, size, startVertex, distances);
				endTime = clock();
				double bfsDistanceMatrixTime = double(endTime - startTime) / CLOCKS_PER_SEC;

				startTime = clock();
				dfsDistanceMatrix(adjacencyMatrix, size, startVertex, distances);
				endTime = clock();
				double dfsDistanceMatrixTime = double(endTime - startTime) / CLOCKS_PER_SEC;

				startTime = clock();
				dfsDistanceList(adjacencyList, size, startVertex, distances);
				endTime = clock();
				double dfsDistanceListTime = double(endTime - startTime) / CLOCKS_PER_SEC;


				outputFile << size << "\t\t   " << bfsDistanceListTime << "\t\t" << bfsDistanceMatrixTime << "\t\t\t" << dfsDistanceMatrixTime << "\t\t\t" << dfsDistanceListTime << "\n";

				deleteMatrix(adjacencyMatrix, size);
				freeAdjacencyList(adjacencyList, size);
			}

			// ���������� �����
			outputFile.close();
			delete[] sizes;
			break; 
		}
		// ���������� ������ ��������� 
		case 3:
			cout << "�����." << endl;
			break;
		// ������ ��� ����� 
		default:
			cout << "������������ �����. ����������, ������� ������ ����� ������." << endl;
			break;
		}
	} 
	while (choice != 3); // ����� �� ���� ��� ������ "�����" (����� 4)

	return 0;
}
