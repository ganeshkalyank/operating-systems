#include <stdio.h>
#include <stdint.h>
#include <math.h>

void constructPageTable(uint32_t* pageTable, uint32_t pageTableSize) {
    for (uint32_t i = 0; i < pageTableSize; i++) {
        pageTable[i] = i;
    }
}

int main() {
    uint32_t logicalAddressRange = (1 << 32);
    uint32_t physicalAddressRange = (1 << 32);

    uint32_t pageSize;
    printf("Enter the page size (in bytes): ");
    scanf("%u", &pageSize);

    uint32_t numPages = logicalAddressRange / pageSize;

    uint32_t* pageTable = (uint32_t*)malloc(numPages * sizeof(uint32_t));

    constructPageTable(pageTable, numPages);

    uint32_t logicalAddress;
    printf("Enter the logical address: ");
    scanf("%u", &logicalAddress);

    uint32_t pageNumber = logicalAddress / pageSize;
    uint32_t offset = logicalAddress % pageSize;

    if (pageNumber < numPages) {
        uint32_t baseAddress = pageTable[pageNumber];

        uint32_t physicalAddress = (baseAddress * pageSize) + offset;

        printf("Logical Address: %u\n", logicalAddress);
        printf("Page Number: %u\n", pageNumber);
        printf("Offset: %u\n", offset);
        printf("Physical Address: %u\n", physicalAddress);
    } else {
        printf("Invalid page number: %u\n", pageNumber);
    }

    free(pageTable);

    return 0;
}
