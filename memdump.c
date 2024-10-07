#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> // For chdir() and getcwd()
#define BufferSize 0x800
#define InputNameBuffer 15
#define CharacterCount 16
#define SpacesPerLine 17

void MemDump(void *memptr, unsigned int offset, unsigned int length);
int LoadFile(void *buffer, unsigned int max);

void setWorkingDirectory(const char* newPath) {
   if (chdir(newPath) == 0) {
      char cwd[1024];
      if (getcwd(cwd, sizeof(cwd)) != NULL) {
         printf("New working dir: %s\n", cwd);
         } else {
            perror("getcwd() error");
            }
      } else {
               perror("chdir() error");
            }
   }

int main(int argc, char * argv[ ])
{
   // Set the working directory to the folder where your files are located
   setWorkingDirectory("C:/path/to/your/folder");
   char cwd[1024];

   if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("Current working dir: %s\n", cwd);
   } else {
      perror("getcwd() error");
   }

	//char buffer[256]= "This is a lab test a great vision";
	char buffer[BufferSize];//create buffer
	int a =255;//To print Int
	int filesize = -1;//if file not found 
	while(filesize == -1){//Check to See if file was opened
	   filesize = LoadFile(buffer,sizeof (buffer));//Load the File
	}
	
	if(filesize >= (sizeof (buffer))){//If file size is equal to or greater
	//Buffer max out File Too Large
	   fprintf(stdout,"MAX BUFFER: File Too Large For Buffer\n"); 
	}
	MemDump(buffer,0,filesize);//Dump the contents of the Buffer
	//File size
	fprintf(stdout,"The Size of the File is ==> %d \n", filesize);

  } 
  /*LoadFile will ask for a file name attempted to open the file
  and read from the file. If it cann't then the proper Error
  Message will be displayed and a neccessary return value 
  will be given
  Parameters: void * Buffer - The buffer where the file will be read in
  int max - the Maximum Amount of Data to be read from the file
  Returns a int - value determines if file loading was successful or not*/
  int LoadFile(void *buffer, unsigned int max){
     char filebuffer[InputNameBuffer];//input filename buffer
     char temp[InputNameBuffer];//temp buffer to store name without '\n'
     int size;
     FILE *fp;//Crate file pointer
	 //Enter file name max 9 Characters
     printf("\nEnter the Name of the File 9 max characters, 'q' to exit: "); 
     fgets(filebuffer,11,stdin);//get the File name

	 if((strlen(filebuffer)) >=10  ){//If characters exceeded
         printf("Name too Long");
	 return -1;
     }
     sscanf(filebuffer,"%s",temp);//Take out the '\n'

     if((fp = fopen(temp,"rb")) != NULL){//Open the file if exists
        printf("File Exits\n"); 
        size = fread(buffer,sizeof (char),max, fp);//Read File
        printf("Reading....\n"); 
    	return size;//Return Size if not read -1 will return
     }
     else{
        if(strcmp(temp,"q") == 0)//see if input is q for exit
           exit(0);
        printf("File Doesn't Exist");//or else file doesn't exist
	return -1;//return error code
     }
  }
  /*MemeDump will take a pointer were the file is loaded in in memory
  will take the offset where to read the memeory and the length to read.
  it will display the memory location on the left followed by 16 hex 
  characters and then the ASCCI reprentation in characters if exsits
  Parameters- Void * memptr - pointer to where the file is loaded in 
  memory
  Int offset - where to look in the memory location of the file
  int length - how long should the ouput be
  Returns - nothing*/
  void MemDump(void *memptr, unsigned int offset, unsigned int length){
     unsigned char * ch_ptr;//Store the Object from memory to a char
     int i;//Counter
     int linecounter = 1;//Which line are we at? Start with line 1
     int charactercounter = 0;//How many characters have passed
     int temp;//Tempeary storage used to count back how many characters printed
     int endFlag;//Check if the End was reached on a line
     ch_ptr = (unsigned char *) memptr;//Derference the Object to a Char
     
     fprintf(stdout,"%04x ", offset); //Print the First offset
     //Check to see if Begginning of offset has reached to The Length
     for(i = offset ; i < (offset+length); i++){
           endFlag = 0;//Line not Ended
           fprintf(stdout,"%02x ",*(ch_ptr+i));//Print Hex Code  
	if(charactercounter == (CharacterCount)){//Check to see if 16 Character
	   endFlag = 1;//End of Line print Characters
	   temp = (i - charactercounter);//How many hex values Printed
	   for(;temp<i;temp++){//Print to the Current count Number
              if(isprint(*(ch_ptr+temp)))//Check if the Byte is a Character	
                 fprintf(stdout,"%c",*(ch_ptr+temp)); 
              else//If not Print Dot
                 fprintf(stdout,".");
	   }
	   fprintf(stdout,"\n"); 
	   //Print next offset
	   fprintf(stdout,"%04x ", offset+(CharacterCount*linecounter)); 
	   
	   linecounter++;//Gone to Next Line
	   charactercounter = 0;//Characters are now Zero for next line
	}
	else//If still on same line Add Characater Count
	   charactercounter++;
      }
      if(endFlag == 0){//If not Finished on the Line
      temp = (i - charactercounter);//Check how many Characters Printed
      
      while(charactercounter != SpacesPerLine){//Add the Nesccarry Number of Spaces
         fprintf(stdout,"   "); 
         charactercounter++;
	 }
          for(;temp<(offset+length);temp++){//Print to the Current Count Number 
	    if(isprint(*(ch_ptr+temp))){//If Printalbe ASCII Character	
               fprintf(stdout,"%c",*(ch_ptr+temp)); 
	       }
            else{//If not Printable ASCII
               fprintf(stdout,".");
	       }
	  }
      }
      
	   fprintf(stdout,"\n"); 
  }