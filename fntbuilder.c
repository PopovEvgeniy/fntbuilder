#include "fntbuilder.h"
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
  puts("You must give 3 command-line arguments: a graphic file, a text file, the font file");
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
 puts("Version 2.3.8");
 puts("Mugen font compiler by Popov Evgeniy Alekseyevich, 2008-2025 years");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
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
  puts("Can't open the input file");
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
  puts("Can't create the ouput file");
  exit(2);
 }
 return target;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer;
 size_t current,elapsed,block;
 elapsed=0;
 block=4096;
 buffer=(char*)calloc(block,sizeof(char));
 if (buffer==NULL)
 {
  puts("Can't allocate memory");
  exit(3);
 }
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  fread(buffer,sizeof(char),block,input);
  fwrite(buffer,sizeof(char),block,output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  fread(buffer,sizeof(char),length,input);
  fwrite(buffer,sizeof(char),length,output);
  free(buffer);
 }

}

void write_head(const FNT *head,FILE *output)
{
 fwrite(head,sizeof(FNT),1,output);
}

FNT prepare_head()
{
 FNT head;
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
 strncpy(head.comment,"This font was created by FNT BUILDER.   ",40);
 return head;
}

void work(const char *pcx_name,const char *text_file,const char *fnt_file)
{
 FILE *pcx;
 FILE *text;
 FILE *font;
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