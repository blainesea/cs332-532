#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024
#define INITIAL_MAX_LISTINGS 100

/* struct to hold data from each listing */
struct listing {
    int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count, availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
};

/* parsing each line and putting each field into the struct */
struct listing getfields(char* line) {
    struct listing item;
    item.id = atoi(strtok(line, ","));
    item.host_id = atoi(strtok(NULL, ","));
    item.host_name = strdup(strtok(NULL, ","));
    item.neighbourhood_group = strdup(strtok(NULL, ","));
    item.neighbourhood = strdup(strtok(NULL, ","));
    item.latitude = atof(strtok(NULL, ","));
    item.longitude = atof(strtok(NULL, ","));
    item.room_type = strdup(strtok(NULL, ","));
    item.price = atof(strtok(NULL, ","));
    item.minimum_nights = atoi(strtok(NULL, ","));
    item.number_of_reviews = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365 = atoi(strtok(NULL, ","));
    return item;
}

/* function to sort entries by host name */
int compareByName(const void *a, const void *b) {
    struct listing *item1 = (struct listing *)a;
    struct listing *item2 = (struct listing *)b;
    return strcmp(item1->host_name, item2->host_name);
}

/* function to sort entries by price */
int compareByPrice(const void *a, const void *b) {
    struct listing *item1 = (struct listing *)a;
    struct listing *item2 = (struct listing *)b;
    if (item1->price < item2->price)
        return -1;
    else if (item1->price > item2->price)
        return 1;
    else
        return 0;
}

int main() {
    FILE *fptr; /* file pointer */
    char line[LINESIZE]; /* array storing each line from original file */
    int count = 0;
    int max_listings = INITIAL_MAX_LISTINGS; /* intial size of array listing */
    /* allocating memory for the listing array */
    struct listing *list_items = malloc(max_listings * sizeof(struct listing));

    /* opening csv file in read mode */
    fptr = fopen("listings.csv", "r");
    if (fptr == NULL) {
        perror("Error opening file");
        return 1;
    }

    /* reading each line of the file 
    manipulating buffer size to prevent segmentation faults */
    while (fgets(line, LINESIZE, fptr) != NULL) {
        /* checking if num of entries > buffer size */
        if (count >= max_listings) {
            max_listings *= 2; /* double the size of the buffer */
            /* reallocating memory for new buffer */
            list_items = realloc(list_items, max_listings * sizeof(struct listing));

            /* error handling for if mem allocating fails */
            if (list_items == NULL) {
                perror("Memory allocation failed");
                return 1;
            }
        }
        /* parse thru lines, store data in listing array */
        list_items[count++] = getfields(line);
    }

    fclose(fptr);

    /* sorting by host name */
    qsort(list_items, count, sizeof(struct listing), compareByName);

    /* open new file in write mode for host name */
    fptr = fopen("sorted_by_name.csv", "w");
    if (fptr == NULL) {
        perror("Error opening file");
        return 1;
    }
    /* writing to the file for host name */
    for (int i = 0; i < count; i++) {
        fprintf(fptr, "%d,%d,%s,%s,%s,%f,%f,%s,%f,%d,%d,%d,%d\n",
            list_items[i].id, list_items[i].host_id, list_items[i].host_name, list_items[i].neighbourhood_group,
            list_items[i].neighbourhood, list_items[i].latitude, list_items[i].longitude, list_items[i].room_type,
            list_items[i].price, list_items[i].minimum_nights, list_items[i].number_of_reviews,
            list_items[i].calculated_host_listings_count, list_items[i].availability_365);
    }
    fclose(fptr);

    /* sorting by price */
    qsort(list_items, count, sizeof(struct listing), compareByPrice);

    /* open new file in write mode for price */
    fptr = fopen("sorted_by_price.csv", "w");
    if (fptr == NULL) {
        perror("Error opening file");
        return 1;
    }
    /* writing to the file for price */
    for (int i = 0; i < count; i++) {
        fprintf(fptr, "%d,%d,%s,%s,%s,%f,%f,%s,%f,%d,%d,%d,%d\n",
            list_items[i].id, list_items[i].host_id, list_items[i].host_name, list_items[i].neighbourhood_group,
            list_items[i].neighbourhood, list_items[i].latitude, list_items[i].longitude, list_items[i].room_type,
            list_items[i].price, list_items[i].minimum_nights, list_items[i].number_of_reviews,
            list_items[i].calculated_host_listings_count, list_items[i].availability_365);
    }
    fclose(fptr);

    /* freeing dynamically allocated memory */
    free(list_items);

    /* print message if executed succesfully */
    printf("Files Created Successfully\n");

    return 0;
}