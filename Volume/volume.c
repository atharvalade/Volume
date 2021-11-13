// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header [HEADER_SIZE]; //buffer; presumable create an array of the size 44 which already is mentioned in the distribution packet
    fread(header, HEADER_SIZE, 1, input); //read the buffer, read 44 bytes (header)
    fwrite(header, HEADER_SIZE, 1, output); //after reading the input, then copy it to output

    int16_t buf;//this is provided data type in the lab 4 descp, wherein it says that this is the kind of type we need to use to read 2 bytes and then multiple by then user's factor
    while (fread(&buf, sizeof(int16_t), 1, input))
    {
        buf = buf * factor; // increaese the volume
        fwrite(&buf, sizeof(int16_t), 1, output); // now write this updated data to the output
    }


    // TODO: Read samples from input file and write updated data to output file

    // Close files
    fclose(input);
    fclose(output);
}
