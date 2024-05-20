#include<graphics.h>
#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

// Start screen of Josephus Game
void start()
{
	setcolor(WHITE);
	settextstyle(8,0,6);
	outtextxy(30,100,"Welcome to Josephus Game");
	settextstyle(8,0,4);
	outtextxy(50,250,"Rules:");
	outtextxy(50,300,"Press Space key to start the Game");
	outtextxy(50,350,"Press Escape key to exit the Game");
}

// Ending screen of Josephus Game
void end()
{
	
	cleardevice();
	setcolor(RED);
	settextstyle(8,0,7);
	outtextxy(200,200,"Game Over!");
	delay(3000);
}

// Printing Winner on the screen
void winner(int i)
{
	
	cleardevice();
	setcolor(RED);
	settextstyle(8,0,6);
	char *arr;
	if(i < 10)
	{
		arr = new char[2];
		arr[1]='\0';
		arr[0]=char(i+48);
	}
	else
	{
		arr = new char[3];
		arr[2]='\0';
		arr[1]=char(i%10+48);
		arr[0] = char(i/10+48);
	}
	outtextxy(100,200,arr);
	outtextxy(200,200,"is the winner");
	delay(3000);
}

// Printing people in the game
void man(int x, int y, int i)
{
	// choosing rows and columns to print people on screen
	if(x > 3500)
	{
		x = x-3500;
		y += 500;
	}
	else if(x > 2800)
	{
		x = x-2800;
		y += 400;
	}
	else if(x > 2100)
	{
		x = x-2100;
		y += 300;
	}
	else if(x > 1400)
	{
		x = x-1400;
		y += 200;
	}
	else if(x > 700)
	{
		x = x-700;
		y += 100;
	}
	
	// Face
	setcolor(YELLOW);
	circle(x,y,30);
	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(x,y,YELLOW);
	// Eyes
	setcolor(BLACK);
	circle(x-10,y-5,5);
	circle(x+10,y-5,5);
	setfillstyle(SOLID_FILL,BLACK);
	floodfill(x-10,y-5,BLACK);
	floodfill(x+10,y-5,BLACK);
	// Smile
	line(x-11,y+10,x-6,y+15);
	line(x-6,y+15,x+6,y+15);
	line(x+6,y+15,x+11,y+10);
	
	// Printing number below each person to represent correct order
	setcolor(BLUE);
	settextstyle(8,0,3);
	
	char *arr;
	if(i < 10)
	{
		arr = new char[2];
		arr[1]='\0';
		arr[0]=char(i+48);
	}
	else
	{
		arr = new char[3];
		arr[2]='\0';
		arr[1]=char(i%10+48);
		arr[0] = char(i/10+48);
	}
	outtextxy(x-10,y+35,arr);
}

// Queue implementation using Linked List
template<class T>
class Node
{
public:
	T data;
	Node* next;
	Node()
	{
		data = 0;
		next = NULL;
	}
};

template<class T>
class Queue
{
	T data;
	Node<T>* front;
	Node<T>* rear;
	int maxsize;

public:
	Queue()
	{
		front = NULL;
		rear = NULL;
		data = 0;
		maxsize = 0;
	}
	~Queue()
	{
		Node<T> *temp1, *temp2;
		temp1 = front;
		while (temp1 != NULL)
		{
			temp2 = temp1->next;
			delete temp1;
			temp1 = temp2;
		}
	}
	bool isEmpty()
	{
		return(front == NULL);
	}
	void Enqueue(int val)
	{
		Node<T>* newnode = new Node<T>;
		newnode->data = val;
		if (front == NULL)
		{
			front = newnode;
			rear = newnode;
		}
		else
		{
			rear->next = newnode;
			rear = newnode;
		}
		maxsize++;
	}
	T Dequeue()
	{
		T n = 0;
		if(!isEmpty())
		{
			Node<T>* temp = front;
			n = front->data;
			front = front->next;
			delete temp;
			maxsize--;
		}
		return n;
	}
	void print()
	{
		cleardevice();
		for(int i = 0; i < maxsize; i++)
		{
			int n = Dequeue();
			Enqueue(n);
			cout << n << " ";
			man(n*100,50, n); // callig man function to print the people
		}
		cout << endl << endl;
		delay(1000);
	}
	
	int Size()
	{
		return maxsize;
	}
};

// Josephus Game Algorithm
int josephus(Queue<int>& Q, int s, int k)
{
	int en = 0; // to end the game if en=1
	do
	{
		start();
		if(GetAsyncKeyState(VK_ESCAPE)) // to exit the game
		{
			end();
			en = 1;
			return en;
		}
	} while(!GetAsyncKeyState(VK_SPACE)); // to start the game
	
	Q.print(); // Printing n number of people at start of the game
	delay(2000);
	int max = Q.Size();
	int size = 0;
	
	// using loop to start from the standing position "s"
	int e = s-1;
	while (e > 0)
	{
		int n = Q.Dequeue();
		Q.Enqueue(n);
		e--;
	}
	
	int c = Q.Size();
	while (max!=1)
	{
		size++;
		if(GetAsyncKeyState(VK_ESCAPE)) // to exit during the game
		{
			en = 1;
			end();
			return en;
		}
		// Removing the person from the queue who gets dead in the game
		if ((size)%k == 0)
		{
			Q.Dequeue();
			max--; 
			Q.print();
		}
		else
		{
			int n = Q.Dequeue();
			Q.Enqueue(n);
		}
	}
	return en;
}

int main()	
{
	// Taking input of Number of People N
	int n;
	cout << "Enter number of people N: ";
	cin >> n;
	// Taking input again for invalid value
	while(n <= 1)
	{
		cout << "Invalid value please try again!" << endl;
		cout << "Enter number of people N: ";
		cin >> n;
	}
	// Taking input k from the user
	int k;
	cout << "Enter value of k: ";
	cin >> k;
	// Taking input again for invalid value
	while(k <= 1 || k > n)
	{
		cout << "Invalid value please try again!" << endl;
		cout << "Enter value of k: ";
		cin >> k;
	}
	
	// Using random function to select standing position randomly
	//srand(time(0));
	//int s = rand()%n + 1;
	int s = 0;
	cout << "Standing Position: " << s << endl;
	
	initwindow(800,600);
	Queue<int> Q2;	
	for (int i = 0; i < n; i++)
	{
		Q2.Enqueue(i+1);
	}
	
	int g = josephus(Q2,s, k); // calling function to play the game
	if(g != 1) 
	{
		// Using condition to print the winner screen only if the game has completed 
		//Q2.print();
		winner(Q2.Dequeue());
		end();
	}
	delay(2000);
	
	return 0;
}