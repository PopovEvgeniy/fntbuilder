#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

void show_intro();
unsigned long int get_file_size(FILE *file);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
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
  puts("You must give 3 command line arguments: graphic file, text file, font file");
 }
 else
 {
  puts("Creating a font file. Please wait...");
  work(argv[1],argv[2],argv[3]);
  puts("Work finish");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("FNT BUILDER");
 puts("Version 2.2.2");
 puts("Mugen font compiler by Popov Evgeniy Alekseyevich, 2008-2022 years");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
}

unsigned long int get_file_size(FILE *file)
{
 unsigned long int length;
 fseek(file,0,SEEK_END);
 length=ftell(file);
 rewind(file);
 return length;
}

FILE *open_input_file(const char *name)
{
 FILE *target;
 target=fopen(name,"rb");
 if (target==NULL)
 {
  puts("Can't open input file");
  exit(1);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target;
 target=fopen(name,"wb");
 if (target==NULL)
 {
  puts("Can't create ouput file");
  exit(2);
 }
 return target;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char data;
 size_t index;
 data=0;
 for (index=0;index<length;++index)
 {
  fread(&data,sizeof(unsigned char),1,input);
  fwrite(&data,sizeof(unsigned char),1,output);
 }

}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,sizeof(unsigned char));
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  fread(buffer,sizeof(unsigned char),length,input);
  fwrite(buffer,sizeof(unsigned char),length,output);
  free(buffer);
 }

}

void write_head(const FNT *head,FILE *output)
{
 fwrite(head,sizeof(FNT),1,output);
}

FNT prepare_head()
{
 FNT fnt_head;
 memset(&fnt_head,0,sizeof(FNT));
 strncpy(fnt_head.signature,"ElecbyteFnt",12);
 strncpy(fnt_head.comment,"This font is created by FONT BULDER    ",40);
 fnt_head.pcx_offset=(unsigned long int)sizeof(FNT);
 return fnt_head;
}

void work(const char *pcx_name,const char *text_file,const char *fnt_file)
{
 FILE *input;
 FILE *output;
 FNT head;
 head=prepare_head();
 input=open_input_file(pcx_name);
 head.pcx_size=get_file_size(input);
 head.text_offset=head.pcx_offset+head.pcx_size;
 fclose(input);
 input=open_input_file(text_file);
 head.text_size=get_file_size(input);
 fclose(input);
 output=create_output_file(fnt_file);
 write_head(&head,output);
 input=open_input_file(pcx_name);
 data_dump(input,output,(size_t)head.pcx_size);
 fclose(input);
 input=open_input_file(text_file);
 data_dump(input,output,(size_t)head.text_size);
 fclose(input);
 fclose(output);
}