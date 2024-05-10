#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

using namespace std;

struct Recipe
{
    char ingredients[20];
    struct Recipe* next;
};
void CreateInEnd(struct Recipe** head, char ingredient[])
{
    struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
    

    strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    struct Recipe* last = *head;
    
    last->next = newNode;
}
void CreateInPos(struct Recipe** head, char ingredient[], int pos)
{
    struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
    strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
    

    if (pos == 0)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        struct Recipe* current = *head;

        if (current == NULL)
        {
            cout << "Position out of range" << endl;
            free(newNode); // Освобождаем память, выделенную для newNode
            return;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
void CreateAfterTarget(struct Recipe** head, char targetData[], char ingredient[])
{
    struct Recipe* current = *head;
    while (current != NULL && strcmp(current->ingredients, targetData) != 0)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        cout << "Data not founded" << endl;
        return;
    }
    struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
    strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
    newNode->next = current->next;
    current->next = newNode;

}
void CreateBeforeTarget(struct Recipe** head, char targetData[], char ingredient[])
{
    if (strcmp((*head)->ingredients, targetData) == 0)
    {
        struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
        strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
        newNode->next = *head;
        *head = newNode;
        return;
    }
    struct Recipe* current = *head;
    while (current->next != NULL && strcmp(current->next->ingredients, targetData) != 0)
    {
        current = current->next;
    }
    if (current->next == NULL)
    {
        printf("Data not founded");
        return;
    }
    struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
    strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
    newNode->next = current->next;
    current->next = newNode;
}
void CreateInMiddle(struct Recipe** head, char ingredient[])
{
    struct Recipe* slow = *head;
    struct Recipe* fast = *head;
    struct Recipe* prev = NULL;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }
    struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
    strncpy_s(newNode->ingredients, ingredient, sizeof(newNode->ingredients));
    newNode->next = slow;
    if (prev != NULL)
    {
        prev->next = newNode;
    }
    else
    {
        *head = newNode;
    }

}
void DeleteInMiddle(struct Recipe** head)
{
    struct Recipe* slow = *head;
    struct Recipe* fast = *head;
    struct Recipe* prev = NULL;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    if (prev == NULL)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        prev->next = slow->next;
        free(slow);
    }
}
void DeleteInTarget(struct Recipe** head, char target[]) {
    struct Recipe* temp = *head;
    struct Recipe* prev = *head;

    if (temp != NULL && strcmp(temp->ingredients, target) == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->ingredients, target) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "The element with name " << target << " was not found in the list.";
        return;
    }

    prev->next = temp->next;
    free(temp);
}
void DeleteInEnd(struct Recipe** head)
{
    if ((*head)->next == NULL)
    {
        free(*head);
        *head = NULL;
        return;
    }

    struct Recipe* current = *head;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}
void DeleteInPos(struct Recipe** head, int pos)
{
    if (pos == 0)
    {
        struct Recipe* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    struct Recipe* current = *head;
    for (int i = 0; current != NULL && i < pos - 1; i++)
    {
        current = current->next;
    }

    if (current == NULL || current->next == NULL)
    {
        cout<<"Position is greater"<<endl;
        return;
    }

    struct Recipe* temp = current->next;
    current->next = current->next->next;
    free(temp);
}
void DeleteFirst(struct Recipe** head)
{
    Recipe* temp = *head;
    *head = (*head)->next;
    free(temp);
}
void displayList(struct Recipe* node)
{
    while (node != NULL) {
        cout << node->ingredients <<endl;
        node = node->next;
    }
}

int main()
{
    struct Recipe* f = NULL;
    char ingredients[20];
    char target[20];
    int pos = 0;
    int choice = 1;

    while (choice != 0)
    {
        cout << "output - 0" << endl;
        cout << "creation at end - 1" << endl;
        cout << "creation in a specific position - 2" << endl;    
        cout << "creation after a certain position - 3" << endl;
        cout << "creation before a certain position - 4" << endl;   
        cout << "creation in the middle - 5" << endl;
        cout << "removal from the middle - 6" << endl;    
        cout << "removing the selected element - 7" << endl;
        cout << "removing the last element - 8" << endl;  
        cout << "remove from specified location - 9" << endl;
        cout << "removing the first element - 10" << endl; 
        cout << "list output - 11" << endl << endl;
        cout << "select function " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "enter the quantity of ingredients: " << endl;
            cin >> ingredients;
            ingredients[strcspn(ingredients, "\n")] = '\0';
            CreateInEnd(&f, ingredients);
            break;
        case 2:
            cout << "enter the quantity of ingredients: " << endl;
            cin >> ingredients;
            ingredients[strcspn(ingredients, "\n")] = '\0';
            cout << "select pos" << endl;
            cin >> pos;

            CreateInPos(&f, ingredients, pos - 1);
            break;
        case 3:
            cout << "enter the quantity of ingredients after which paste " << endl;
            cin >> target;
            target[strcspn(target, "\n")] = '\0';
            cout << "enter the quantity of ingredients: " << endl;
            cin >> ingredients;
            ingredients[strcspn(ingredients, "\n")] = '\0';

            CreateAfterTarget(&f, target, ingredients);
            break;
        case 4:
            cout << "enter the quantity of ingredients befor which paste " << endl;
            cin >> target;
            target[strcspn(target, "\n")] = '\0';
            cout << "enter the quantity of ingredients: " << endl;
            cin >> ingredients;
            ingredients[strcspn(ingredients, "\n")] = '\0';

            CreateBeforeTarget(&f, target, ingredients);
            break;
        case 5:
            cout << "enter the quantity of ingredients: " << endl;
            cin >> ingredients;
            ingredients[strcspn(ingredients, "\n")] = '\0';
           
            CreateInMiddle(&f, ingredients);
            break;
        case 6:
            DeleteInMiddle(&f);
            break;
        case 7:
            cout << "enter the quantity of ingredients: " << endl;
            cin >> target;
            target[strcspn(target, "\n")] = '\0';
            DeleteInTarget(&f, target);
            break;
        case 8:
            DeleteInEnd(&f);
            break;
        case 9:
            cout << "enter the position you want to delete:" << endl;
            cin >> pos;
            DeleteInPos(&f, pos - 1);
            break;
        case 10:
            DeleteFirst(&f);
        case 11:
            displayList(f);

        }
    }
}