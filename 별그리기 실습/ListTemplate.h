#pragma once
#include<stdio.h>
#include<stdlib.h>


template <typename T>
struct Node {
	struct Node* NextNode;
	T data;
};

template <typename T>
struct List {
	struct Node<T>* Head;
	struct Node<T>* Tail;
};

template <typename T>
Node<T>* createNode(T data)
{
	Node<T>* newNode = (Node<T>*)malloc(sizeof(Node<T>));
	newNode->data = data;
	newNode->NextNode = NULL;
	return newNode;
}

template <typename T>
void addNode(List<T>* list, Node<T>* newNode)
{
	if (list->Head == NULL)
		list->Head = list->Tail = newNode;
	else
	{
		list->Tail->NextNode = newNode;
		list->Tail = newNode;
	}
}

template <typename T>
void printNode(List<T> Head)
{
	Node<T>* currentNode = Head.Head;

	while (currentNode != NULL)
	{
		printf("%d   %d\n", currentNode->data.x, currentNode->data.y);
		currentNode = currentNode->NextNode;
	}
}

template <typename T>
void deleteList(List<T>* list)
{
	Node<T>* current = list->Head;
	Node<T>* temp = NULL;
	while (current != NULL)
	{
		temp = current;
		current = current->NextNode;
		free(temp);
	}
	list->Head = NULL;
}

template <typename T>
void doSomething(List<T> list, void(*fp)()) {
	Node<T>* current = list.Head;
	while (current != NULL) {
		fp();
		current = current->NextNode;
	}
}