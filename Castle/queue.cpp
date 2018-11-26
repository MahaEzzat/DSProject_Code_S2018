#include<iostream>

#include<cstdlib>

#define MAX_SIZE 10


using namespace std;


class Queue{

    private:

        int item[MAX_SIZE];

        int rear;

        int front;

    public:

        Queue();

        void enqueue(int);

        int dequeue();

        int size();

        void display();

        bool isEmpty();

        bool isFull();



};

Queue::Queue(){

    rear = -1;

    front = 0;

}


void Queue::enqueue(int data){

        item[++rear] = data;

}


int Queue::dequeue(){

        return item[front++];

}


void Queue::display(){

    if(!this->isEmpty()){

        for(int i=front; i<=rear; i++)

            cout<<item[i]<<endl;

    }else{

        cout<<"Queue Underflow"<<endl;

    }

}



int Queue::size(){

    return (rear - front + 1);

}

bool Queue::isEmpty(){

    if(front>rear){

        return true;

    }else{

        return false;

    }

}

bool Queue::isFull(){

    if(this->size()>=MAX_SIZE){

        return true;

    }else{

        return false;

    }

}





         
