#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include<cs50.h>

#define element 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./recover image");
        return 1;
    }

    FILE *data = fopen(argv[1], "r");       //open our data pack
    BYTE buffer[element];                    //initialize an array called buffer that will store the element data
    int jpgcounter = 0;                     //initialize a counter for the number of jpg's
    char filename[8];                       //allocating memory for the filename string
    FILE *img;                              //initializing the img file which we will be writing the recovered jpg's to
    
    if (data == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    
    
    
    while (fread(buffer, sizeof(buffer), 1, data) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)      //checks for a new jpeg
        {
            if (jpgcounter == 0)
            {
                sprintf(filename, "%03i.jpg", jpgcounter);              //creating new jpg output file name
                
                img = fopen(filename, "w");                             //opening the newly created output file
            
                jpgcounter = jpgcounter + 1;                            //increasing our jpg counter for the next jpg filename
            
                fwrite(buffer, sizeof(buffer), 1, img);                 //writing the jpg data into the respective jpg file inside img
            }
            else if (jpgcounter > 0)
            {
                fclose(img);
            
                sprintf(filename, "%03i.jpg", jpgcounter);              //creating new jpg output file name
                
                img = fopen(filename, "w");                              //opening the newly created output file
            
                jpgcounter = jpgcounter + 1;                            //increasing our jpg counter for the next jpg filename
            
                fwrite(buffer, sizeof(buffer), 1, img);                 //writing the jpg data into the respective jpg file inside img
            
            }
        }
        else if (jpgcounter > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }
        
    }
    fclose(img);
    fclose(data);

    return 0;
    
    
    
    
    //fread(data, size, number, inptr)... returns number of items of size size that were read. were reading number elements of size size
    //data: pointer to where to store data your reading
    //sizee: size of each element to read
    //number: number of elements to read
    //inptr: FILE * to read from. want to read from memory card file in 512 bite chunks

    //how to know if JPEG starts? read 512 block into some sort of buffer (say, an array of bytes?).
    //then check if buffer[0] == oxff buffer[1] == oxd8 and buffer[2] == oxff. for fourth use bitwise arithmetic
    //bitwise:      (buffer[3] & oxf0) == oxe0 (see video)

    //When we found beginnign of JPEG, create new file to read to the data to
    //How? create ###.jpeg starting with 000.jpg. sprintf prints to a string. filename is the string name
    //sprintf(filename, "%03i.jpeg", 2)... %03i means create integer with 3 digits to represent it.
    //make sure filename has enough memory to fully represent the entire filename
    //now, FILE *img = fopen(filename, "w") where w signifies write
    //fwrite(data, size, number, outptr)
    //data: pointer to bytes that will be written to file
    //size: size of each element to write
    //number: number of elements to write
    //outptr: FILE * to write to (JPEG we just opened)

}
