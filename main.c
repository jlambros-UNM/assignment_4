#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index){
    //In this function, I allocate memory using strlen that is the size of the string + 1, since strlen doesn't include the '
    item_list[index].sku = (char *)malloc(strlen(sku) + 1 * sizeof(char));
    strcpy(item_list[index].sku, sku);
    item_list[index].category = (char *)malloc(strlen(category) + 1 * sizeof(char));
    strcpy(item_list[index].category, category);
    item_list[index].name = (char *)malloc(strlen(name) + 1 * sizeof(char));
    strcpy(item_list[index].name, name);
    item_list[index].price = price;
}

void free_items(Item *item_list, int size){
    //Free memory. Not sure if the double needs to be cleared
    free(item_list->category);
    free(item_list->sku);
    free(item_list->name);
    //free(item_list->price);
}

void print_items(Item *item_list, int sizeIndex, bool operator){
    //For this function, I modified the behavior to allow for different operating modes. If the operating mode is 0, it prints out all items (to the size requested). Else it treats the size as an Index and just prints 1 item
    if(operator == 0){
        for(int i = 0; i < sizeIndex; i++){
            printf("==============\n");
            printf("SKU = %s\n", item_list[i].sku);
            printf("Name = %s\n", item_list[i].name);
            printf("Category = %s\n", item_list[i].category);
            printf("Price = %f\n", item_list[i].price);
        }
    }
    else if(operator == 1){
        printf("==============\n");
        printf("SKU = %s\n", item_list[sizeIndex].sku);
        printf("Name = %s\n", item_list[sizeIndex].name);
        printf("Category = %s\n", item_list[sizeIndex].category);
        printf("Price = %f\n", item_list[sizeIndex].price);
    }
}

double average_price(Item *item_list, int size){
    double temp = 0;
    for(int i = 0; i < size; i++){
        temp = item_list[i].price + temp;
    }
    temp = temp/size;
    //printf("%f", temp);
    return temp;
}
//Big thanks to this guy! https://stackoverflow.com/questions/5157337/reading-command-line-parameters
int main(int argc, char *argv[]){
    int numberOfItems = 5;
    //printf("%s\n", argv[1]);
    Item *items = (Item * )malloc(numberOfItems *sizeof(Item));
    add_item(items, .50, "134457", "Dairy", "Great Value Butter", 0);
    add_item(items, 5.00, "237900", "Bread", "White Bread", 1);
    add_item(items, 300, "111111", "Computers", "Acer Laptop", 2);
    add_item(items, 40, "222222", "Fruit", "Orange", 3);
    add_item(items, 10, "333333", "Dishware", "Great Value Plate", 4);
    int i = 0;
    while (i < numberOfItems){
        //I don't see the point of the  ""&& strcmp(items[i].sku, argv[1]) != 0" as given in the assignment details. I did try them both ways.
        //For this, I had the thought to end the program if the item was found, otherwise give an error and print out the available items.
        if(strcmp(items[i].sku, argv[1]) == 0){
            print_items(items, i, 1);
            return 0;
        }
        else if(i == (numberOfItems - 1)){
            printf("Item not found!\n");
        }
        //printf("%d\n", i); I had a bug above where I did i = numberOfItems - 1, which set the loop to 4 and ended it early every time. Very annoying. It's -1 since we start from 0 not 1.
        i++;
    }
    printf("AVALIABLE ITEMS\n");
    print_items(items, numberOfItems, 0);
    double average = average_price(items, numberOfItems);
    printf("The average price for items at this store is %f\n", average);
    free_items;
    return 0;
}
