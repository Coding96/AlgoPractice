/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: edward
 *
 * Created on 20 December 2016, 03:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tableRow
{
    int index;
    char Data[30];
    struct tableRow * nextRow;
    struct tableRow * prevRow;
};

//function declartion
void setTableRow(int index, struct tableRow *inputtedPointer);
//takes index needed and any point in the linked list
struct tableRow* getByIndex(int index, struct tableRow *inputtedPointer);
//removes by index from the table
void deleteRow(int index, struct tableRow *inputtedPointer);
//prints the current table
void printTable(struct tableRow *inputtedPointer);
//frees the table
void freeTable(struct tableRow *inputtedPointer);
//inserts a row given an index data and any point in the tree {not quite working}
void insertRow(int index, char Data[30], struct tableRow *inputtedPointer);

int main(int argc, char** argv)
{

    struct tableRow *first = malloc(sizeof (*first));

    struct tableRow *second = malloc(sizeof (*second));

    struct tableRow *third = malloc(sizeof (*third));

    first->nextRow = second;
    first->prevRow = NULL;

    second->nextRow = third;
    second->prevRow = first;

    third->nextRow = NULL;
    third->prevRow = second;

    //sets up initial table
    setTableRow(1, first);

    printf("\nfirst print\n");
    printTable(first);


    //gets by index for convience
    //getByIndex(1,first)

    //can delete row by changing pointers (removes row 1)
    deleteRow(2, first);

    printf("\nsecond print\n");
    printTable(first);

    char twoData[30];
    strcpy(twoData, "Has insert worked");
    insertRow(2, twoData, first);

    char fourData[30];
    strcpy(fourData, "Has insert worked");
    insertRow(4, fourData, first);

    printf("\nthird print\n");
    printTable(first);

    printf("\nfourth print\n");
    setTableRow(1, first);
    printTable(first);

    printf("\nfifth print\n");
    char zeroData[30];
    strcpy(zeroData, "top of table");
    insertRow(0, zeroData, first);
    printTable(first);

    freeTable(first);
    return (EXIT_SUCCESS);
}

void setTableRow(int index, struct tableRow *inputtedPointer)
{
    if (inputtedPointer->nextRow == NULL)
    {
        inputtedPointer->index = index;
        strcpy(inputtedPointer->Data, "next row is now null");
    }
    else
    {
        inputtedPointer->index = index;
        strcpy(inputtedPointer->Data, "next row not null");
        setTableRow(index + 1, inputtedPointer->nextRow);
    }

}

//takes index needed and any point in the linked list

struct tableRow* getByIndex(int index, struct tableRow *inputtedPointer)
{
    struct tableRow *temp = inputtedPointer;

    while (temp->prevRow != NULL)
    {
        //make sure we are at the top of the list
        temp = temp->prevRow;
    }

    while (temp != NULL)
    {
        if (temp->index == index)
        {
            break;
        }
        temp = temp->nextRow;
    }

    return temp;

}

void deleteRow(int index, struct tableRow *inputtedPointer)
{
    struct tableRow *temp = getByIndex(index, inputtedPointer);

    struct tableRow *prevTemp = temp->prevRow;
    struct tableRow *nextTemp = temp->nextRow;

    if (prevTemp != NULL)
    {
        prevTemp->nextRow = nextTemp;
    }
    if (nextTemp != NULL)
    {
        nextTemp->prevRow = prevTemp;
    }
}

void insertRow(int index, char Data[30], struct tableRow *inputtedPointer)
{
    struct tableRow *temp = inputtedPointer;

    //insert needs to insert into the correct location
    //currently seems to insert into the last position

    while (temp->prevRow != NULL)
    {
        //make sure we are at the top of the list
        temp = temp->prevRow;
    }


    //this if is to see if this new row is before any other in the list
    if (index < temp->index)
    {
        struct tableRow *insert = malloc(sizeof (*insert));
        insert->index = index;
        strcpy(insert->Data, Data);
        temp->prevRow = insert;
        insert->nextRow = temp;
        insert->prevRow = NULL;
    }
    else
    {
        //temp is the previous row to one we want to insert
        while (temp->index < (index - 1) && temp->nextRow != NULL)
        {
            temp = temp->nextRow;
        }

        //inset is a brand new row to be slid into
        struct tableRow *insert = malloc(sizeof (*insert));
        //next temp is the row after where we want to insert
        struct tableRow *nextTemp = temp->nextRow;

        //get the data and put it into our new row
        insert->index = index;
        strcpy(insert->Data, Data);

        //inserts pointers get set up
        insert->nextRow = nextTemp;
        insert->prevRow = temp;

        //previous node needs to point to insert

        temp->nextRow = insert;

        //provided we are not at the end of the list then next row has previous node insert
        if (nextTemp != NULL)
        {
            nextTemp->prevRow = insert;
        }
    }



}

void printTable(struct tableRow *inputtedPointer)
{
    struct tableRow *temp = inputtedPointer;

    while (temp->prevRow != NULL)
    {
        //make sure we are at the top of the list
        temp = temp->prevRow;
    }

    while (temp != NULL)
    {
        printf("index: %d, Data: %s\n", temp->index, temp->Data);
        temp = temp->nextRow;
    }
}

void freeTable(struct tableRow *inputtedPointer)
{
    struct tableRow *temp = inputtedPointer;
    struct tableRow *newTemp = temp;

    while (temp->prevRow != NULL)
    {
        //make sure we are at the top of the list
        temp = temp->prevRow;
    }

    while (temp != NULL)
    {
        newTemp = temp->nextRow;
        free(temp);
        temp = newTemp;
    }
}