#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

void show_end_message();
void show_intro();
void show_start_message();
void command_line_help();
void go_offset(FILE *file, unsigned long int offset);
unsigned long int get_file_size(FILE *file);
FILE *open_input_file(char *name);
FILE *create_output_file(char *name);
void data_dump(FILE *input, FILE *output, unsigned long int length);
void write_head(FNT head,FILE *output);
FNT prepare_head();
void work(char *pcx_name,char *text_file,char *fnt_file);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<4)
 {
  command_line_help();
 }
 else
 {
  show_start_message();
  work(argv[1],argv[2],argv[3]);
  show_end_message();
 }
 return 0;
}

void show_end_message()
{
 puts(" ");
 puts("Work finish");
}

void show_intro()
{
 puts(" ");
 puts("FNT BUILDER");
 puts("Version 2.0.2");
 puts("Mugen font compiler by Popov Evgeniy Alekseyevich, 2008-2016 year");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
}

void show_start_message()
{
 puts(" ");
 puts("Creating a font file.Please wait...");
}

void command_line_help()
{
 puts(" ");
 puts("You must give 3 command line arguments: graphic file, text file, font file");
}

void go_offset(FILE *file, unsigned long int offset)
{
 fseek(file,offset,SEEK_SET);
}

unsigned long int get_file_size(FILE *file)
{
 unsigned long int length;
 fseek(file,0,SEEK_END);
 length=ftell(file);
 rewind(file);
 return length;
}

FILE *open_input_file(char *name)
{
 FILE *file;
 file=fopen(name,"rb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(1);
 }
 return file;
}

FILE *create_output_file(char *name)
{
 FILE *file;
 file=fopen(name,"wb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(1);
 }
 return file;
}

void data_dump(FILE *input, FILE *output, unsigned long int length)
{
 unsigned char single_byte;
 unsigned long int index;
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,1);
 if (buffer==NULL)
 {
  for(index=0;index<length;index++)
  {
   fread(&single_byte,1,1,input);
   fwrite(&single_byte,1,1,output);
  }

 }
 else
 {
  fread(buffer,length,1,input);
  fwrite(buffer,length,1,output);
  free(buffer);
 }

}

void write_head(FNT head,FILE *output)
{
 fwrite(&head,sizeof(FNT),1,output);
}

FNT prepare_head()
{
 FNT fnt_head;
 strcpy(fnt_head.signature,"ElecbyteFnt");
 fnt_head.verhi=0;
 fnt_head.verhi2=1;
 fnt_head.verlo=0;
 fnt_head.verlo2=0;
 fnt_head.pcx_offset=sizeof(FNT);
 fnt_head.pcx_size=0;
 fnt_head.text_offset=0;
 fnt_head.text_size=0;
 strcpy(fnt_head.comment,"This font is created by FONT BULDER    ");
 return fnt_head;
}

void work(char *pcx_name,char *text_file,char *fnt_file)
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
 write_head(head,output);
 input=open_input_file(pcx_name);
 data_dump(input,output,head.pcx_size);
 fclose(input);
 input=open_input_file(text_file);
 data_dump(input,output,head.text_size);
 fclose(input);
 fclose(output);
}