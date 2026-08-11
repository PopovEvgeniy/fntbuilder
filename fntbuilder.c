#include "fntbuilder.h"
#include "format.h"
#include "exitcode.h"

void show_intro();
void show_error(const char *message);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
unsigned long int get_file_size(FILE *target);
void read_data(void *data,const size_t length,FILE *input);
void write_data(const void *data,const size_t length,FILE *output);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_head(const FNT *head,FILE *output);
FNT prepare_head();
void work(const char *pcx_name,const char *text_file,const char *fnt_file);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<4)
 {
  puts("You must give 3 command-line arguments: a graphic file, a text file, and the font file");
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
 }
 else
 {
  puts("Creating a font file. Please wait...");
  work(argv[1],argv[2],argv[3]);
  puts("The work has been finished");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("FNT BUILDER");
 puts("Version 2.4.9");
 puts("Mugen font compiler by Popov Evgeniy Alekseyevich, 2008-2026 years");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
}

void show_error(const char *message)
{
 fputc('\n',stderr);
 fputs(message,stderr);
 fputc('\n',stderr);
}

FILE *open_input_file(const char *name)
{
 FILE *target=NULL;
 if (name==NULL)
 {
  show_error("Can't open the input file");
  exit(OPEN_FILE_ERROR);
 }
 target=fopen(name,"rb");
 if (target==NULL)
 {
  show_error("Can't open the input file");
  exit(OPEN_FILE_ERROR);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target=NULL;
 if (name==NULL)
 {
  show_error("Can't create the ouput file");
  exit(CREATE_FILE_ERROR);
 }
 target=fopen(name,"wb");
 if (target==NULL)
 {
  show_error("Can't create the ouput file");
  exit(CREATE_FILE_ERROR);
 }
 return target;
}

unsigned long int get_file_size(FILE *target)
{
 unsigned long int length=0;
 if (fseek(target,0,SEEK_END)!=0)
 {
  show_error("Can't get the file size!");
  exit(GET_FILE_SIZE_ERROR);
 }
 length=ftell(target);
 rewind(target);
 return length;
}

void read_data(void *data,const size_t length,FILE *input)
{
 if (fread(data,sizeof(char),length,input)<length)
 {
  show_error("Can't read data!");
  exit(READ_DATA_ERROR);
 }

}

void write_data(const void *data,const size_t length,FILE *output)
{
 if (fwrite(data,sizeof(char),length,output)<length)
 {
  show_error("Can't write data!");
  exit(WRITE_DATA_ERROR);
 }

}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 size_t current=0;
 size_t elapsed=0;
 size_t block=4096;
 buffer=(char*)calloc(block,sizeof(char));
 if (buffer==NULL)
 {
  puts("Can't allocate memory");
  exit(6);
 }
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  read_data(buffer,block,input);
  write_data(buffer,block,output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  read_data(buffer,length,input);
  write_data(buffer,length,output);
  free(buffer);
 }

}

void write_head(const FNT *head,FILE *output)
{
 write_data(head,sizeof(FNT),output);
}

FNT prepare_head()
{
 FNT head;
 memset(&head,0,sizeof(FNT));
 strncpy(head.signature,"ElecbyteFnt",12);
 head.signature[11]=0;
 head.version[0]=0;
 head.version[1]=1;
 head.version[2]=0;
 head.version[3]=0;
 head.pcx_offset=sizeof(FNT);
 head.pcx_size=0;
 head.text_offset=0;
 head.text_size=0;
 strncpy(head.comment,"This font was created by FNT BUILDER   ",39);
 head.comment[39]=0;
 return head;
}

void work(const char *pcx_name,const char *text_file,const char *fnt_file)
{
 FILE *pcx=NULL;
 FILE *text=NULL;
 FILE *font=NULL;
 FNT head;
 head=prepare_head();
 pcx=open_input_file(pcx_name);
 text=open_input_file(text_file);
 font=create_output_file(fnt_file);
 head.pcx_size=get_file_size(pcx);
 head.text_size=get_file_size(text);
 head.text_offset=head.pcx_offset+head.pcx_size;
 write_head(&head,font);
 fast_data_dump(pcx,font,(size_t)head.pcx_size);
 fast_data_dump(text,font,(size_t)head.text_size);
 fclose(pcx);
 fclose(text);
 fclose(font);
}