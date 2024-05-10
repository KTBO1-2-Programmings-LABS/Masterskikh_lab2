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
    struct Recipe* prior;

};

void CreateInEnd(struct Recipe** head, char ingredient[])
{
    struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));

    strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
    newNode->next = NULL;
    newNode->prior = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    struct Recipe* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    
    
    last->next = newNode;
    newNode->prior = last;
}
void CreateInPos(struct Recipe** head, char ingredient[], int pos)
{
    struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
    struct Recipe* current = (struct Recipe*)malloc(sizeof(struct Recipe));
    strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
    current = *head;
    newNode->next = NULL;
    newNode->prior = NULL;

    if (pos == 0)
    {
        newNode->next = *head;
        if (*head != NULL)
            (*head)->prior = newNode;
        *head = newNode;
    }
    else
    {
        for (int i = 0; i < pos; i++) {
            if (current->next != NULL) {
                current = current->next;
            }
            else {
                break;
            }
        }
        newNode->next = current;
        newNode->prior = current->prior;
        current->prior->next = newNode;
        current->prior = newNode;
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
    newNode->prior = current;
    newNode->next = current->next;

    if (current->next != NULL)
    {
        current->next->prior = newNode;
    }

    current->next = newNode;
}
void CreateBeforeTarget(struct Recipe** head, char targetData[], char ingredient[])
{
    if (strcmp((*head)->ingredients, targetData) == 0)
    {
        struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
        strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
        newNode->next = *head;
        (*head)->prior = newNode;
        *head = newNode;
        return;
    }

    struct Recipe* current = *head;
    while (current != NULL && strcmp(current->ingredients, targetData) != 0)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Data not founded");
        return;
    }


    struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
    strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
    newNode->next = current;
    newNode->prior = current->prior;
    current->prior->next = newNode;
    current->prior = newNode;
}
void CreateInMiddle(struct Recipe** head, char ingredient[])
{
    struct Recipe* slow = *head;
    struct Recipe* fast = *head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        
    }

    struct Recipe* newNode = (struct Recipe*)malloc(sizeof(struct Recipe));
    if (newNode == NULL)
    {
        printf("Memory allocation failed");
        return;
    }
    strcpy_s(newNode->ingredients, sizeof(newNode->ingredients), ingredient);
    newNode->next = slow->prior->next;
    slow->prior->prior = slow->prior;
    slow->prior->next = newNode;


}
void DeleteInMiddle(struct Recipe** head)
{
    struct Recipe* slow = *head;
    struct Recipe* fast = *head;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    if (slow->prior == NULL)
    {
        free(*head);
        *head = NULL;
    }
    else
    {
        slow->prior->next = slow->next;
        free(slow);
    }
}
void DeleteInTarget(struct Recipe** head, char target[]) {
    struct Recipe* current = *head;

    if (current != NULL && strcmp(current->ingredients, target) == 0) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prior = NULL;
        }
        free(current);
        return;
    }
    while (current != NULL && strcmp(current->ingredients, target) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        cout << "The element with name " << target << " was not found in the list.";
        return;
    }
    if (current->prior != NULL) {
        current->prior->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prior = current->prior;
    }
    free(current);
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
    int i = 1;
    struct Recipe* current = (struct Recipe*)malloc(sizeof(struct Recipe));
    struct Recipe* tmp = (struct Recipe*)malloc(sizeof(struct Recipe));
    current = *head;
    tmp = *head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
        i++;
    }
    if (pos > i) {
        cout << "Position is greater than the length of the list";
    }
    if (pos == 0)
    {
        if (current->next != NULL) {
            *head = current->next;
            free(current);
            return;
        }
    }
    else
    {
        for (int i = 0; i < pos; i++) {
            if (current->next != NULL) {
                current = current->next;
            }
            else {
                break;
            }
        }
        current->prior->next = current->next;
        current->next->prior = current->prior;
        free(current);
        return;
    }
}
void DeleteFirst(struct Recipe** head)
{
    Recipe* temp = *head;
    (*head)->next->prior = NULL;
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
            cout << "select pos " << endl;
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
