#include <assert.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>

#include "File.h"

int get_file_size(FILE* fp)
{
    assert(fp != nullptr);

    struct stat st;
    fstat(fileno(fp), &st);
    return st.st_size;
}

void file_read(File* file)
{
    assert(file != nullptr);

    if(fread(file->buf, sizeof(char), file->sizeFile, file->fp) != file->sizeFile)
    {
        if(feof(file->fp))
            printf("Premature end of file\n");
        else
            printf("File read error\n");
    }
}

int skip_spaces(File* file, int index)
{
    assert(file != nullptr);
    assert(index >= 0);

    char ch = file->buf[index];
    while( (ch == ' ' || ch == '\n' || ch == '\r') && index < file->sizeFile)
    {
        index++;
        ch = file->buf[index];
    }

    return index;
}

File* file_ctor(const char* nameFile)
{
    assert(nameFile != nullptr);

    File* file = (File*)calloc(1, sizeof(File));
    assert(file != nullptr);
    
    FILE* fp = fopen(nameFile, "rb");
    assert(fp != nullptr);

    file->fp = fp;

    file->sizeFile = get_file_size(fp);
    file->buf = (char*)calloc(file->sizeFile, sizeof(char));
    assert(file->buf != nullptr);
    file_read(file);

    return file;
}

void file_dtor(File* file)
{
    assert(file != nullptr);

    free(file->buf);
    fclose(file->fp);
}
