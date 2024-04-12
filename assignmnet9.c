#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next; 
};

struct HashType
{
    struct RecordType* head;
};

// Compute the hash function
int hash(int x, int HASH_SIZE)
{
    
    return x % HASH_SIZE;
}

// Display records in the hash structure
// Skip the indices which are free
// The output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* pHashArray, int hashSz)
{
    for (int i = 0; i < hashSz; ++i)
    {
        if (pHashArray[i].head != NULL)
        {
            printf("Index %d -> ", i);
            struct RecordType* temp = pHashArray[i].head;
            while (temp != NULL){
            
                printf("(%d, %c, %d) -> ", temp->id, temp->name, temp->order);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;

    
    FILE* inFile = fopen("input.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

  
    int HASH_SIZE;
    fscanf(inFile, "%d", &HASH_SIZE);
    printf("HASH_SIZE: %d\n", HASH_SIZE);

  
    fscanf(inFile, "%d", &recordSz);
    pRecords = (struct RecordType*)malloc(sizeof(struct RecordType) * recordSz);
    for (int i = 0; i < recordSz; ++i)
    {
        fscanf(inFile, "%d %c %d", &pRecords[i].id, &pRecords[i].name, &pRecords[i].order);
    }

  
    fclose(inFile);

    printf("Records:\n");
    for (int i = 0; i < recordSz; ++i)
    {
        printf("\t%d %c %d\n", pRecords[i].id, pRecords[i].name, pRecords[i].order);
    }

   
    struct HashType* hashTable = (struct HashType*)malloc(sizeof(struct HashType) * HASH_SIZE);

 
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        hashTable[i].head = NULL;
    }


    for (int i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id, HASH_SIZE);
        struct RecordType* newRecord = (struct RecordType*)malloc(sizeof(struct RecordType));
        *newRecord = pRecords[i];
        newRecord->next = NULL;

        if (hashTable[index].head == NULL)
        {
            hashTable[index].head = newRecord;
        }
        else
        {
            struct RecordType* temp = hashTable[index].head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newRecord;
        }
    }

   
    displayRecordsInHash(hashTable, HASH_SIZE);

   
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        struct RecordType* temp = hashTable[i].head;
        while (temp != NULL)
        {
            struct RecordType* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(hashTable);
    free(pRecords);

    return 0;
}
