#include "../include/alcom.h"


ssize_t comment_splitter_position(const char * line) {
    if (!line) 
        return -1;                                                                                                 

    bool    reading_inside_quotes = false;                                                                        
    ssize_t current_index         = 0;                                                                           

    while ((size_t)current_index < strlen(line)) {
        if (line[current_index] == '\n')                          return current_index;                            
        if (line[current_index] == '\0')                          return current_index;                            
        if (line[current_index] == '\'')                          reading_inside_quotes = !reading_inside_quotes;
        if (line[current_index] == ';' && !reading_inside_quotes) return current_index;                     
        current_index++;                                                                                              
    }

    return current_index;                                                                                        
}


bool line_has_comment(const char * line)
{
    if (!line) 
        return false;                                                                                               

    bool    reading_inside_quotes = false;                                                                            
    size_t  current_index         = 0;                                                                                
    bool    found                 = false;                                                                            

    while (current_index < strlen(line) && !found)
    {
        if (line[current_index] == '\'') reading_inside_quotes = !reading_inside_quotes;
        if (line[current_index] == ';' && !reading_inside_quotes) {
            found = true;                                                                                          
            break;                                                                                            
        }
        current_index++;                                                                                             
    }

    if (current_index == strlen(line) - 1) 
        return false;                                                                                  

    if (found == true) {
        found = false;                                                                                            

        for (   ; current_index < strlen(line); current_index++) {
            char current_char = line[current_index];                                                                 
            
            if (strchr(" \t\n", current_char) != NULL) 
                continue;                                                                                            
            else 
                return true;                                                                                          
        }        
    }

    return found;                                                                                                     
}


size_t find_longest_line_without_comment(const char * filename) {
    
    FILE * source = fopen(filename, "r");                                                                            

    char *  line     = NULL;                                                                                          
    size_t  len      = 0;                                                                                            
    ssize_t line_len = 0;                                                                                             

    size_t longest_line_lenght = 0;                                                                                   

    while ((line_len = getline(&line, &len, source)) != -1) {

        ssize_t splitter_position = comment_splitter_position(line);                                                  
        
        //? Now we trim spaces tabs and new_lines
        while ((line[splitter_position] == '\n' || 
               line[splitter_position] == ' '   || 
               line[splitter_position] == '\t') &&
               splitter_position > 0) {
            splitter_position--;                                                                                      
        }

        if ((size_t)splitter_position > longest_line_lenght) //? swap for max line length
            longest_line_lenght = (size_t)splitter_position;                                                          
    }

    if (source)  
        fclose(source);    //? Closing file and prevent from ub with fclose(NULL)

    return longest_line_lenght;                                                                                       
}


bool line_is_empty(const char * line)
{
    for (size_t ind = 0; ind < strlen(line); ind++)
    {
        char current_char = line[ind];                                                                                
        if (strchr(" \t\n", current_char) == NULL) return false;                                                      
    }
    return true;                                                                                                      
}


void align_asm_file(char * filename) {

    const char * destination_filename = "./__aligning_file_temporary__.asm";                                          

    size_t longest_line_lenght = find_longest_line_without_comment(filename);                                         

    FILE * destination = fopen(destination_filename, "w");                                                            
    FILE * source      = fopen(filename, "r");                                                                        

    char *  line     = NULL;                                                                                          
    size_t  len      = 0;                                                                                            
    ssize_t line_len = 0;                                                                                             

    while ((line_len = getline(&line, &len, source)) != -1) {
    
        if (line_is_empty(line))
        {
            fprintf(destination, "%s\n", line);                                                                       
            continue;                                                                                                 
        }

        if (line_has_comment(line)) {

            ssize_t splitter_position = comment_splitter_position(line);                                              

            char comment[1024]   = "\0";    //? Does anyone use more chars for comments?
            char code[1024]      = "\0";    //? Imagin a man who uses more chars for one code line in asm brrr...
            char full_line[3000] = "\0";                                                                              

            ssize_t comment_start = splitter_position + 1;                                                            

            while ((line[comment_start] == ' '   || 
                    line[comment_start] == '\t') && 
                    (size_t)comment_start < strlen(line)) {
                comment_start++;                                                                                      
            }

            memcpy(comment, line + comment_start, strlen(line) - (size_t)comment_start - 1);                          
            memcpy(code,    line,                 splitter_position);                                                 

            size_t cursor = 0;                                                                                        

            for ( ; cursor < strlen(code) && cursor < 3000; cursor++)
                full_line[cursor] = code[cursor];                                                                     

            for (size_t space_count = 0; space_count < longest_line_lenght - strlen(code) + 5; space_count++)
            {
                full_line[cursor++] = ' ';                                                                            
            }

            if (!line_is_empty(comment)) {
                full_line[cursor++] = ';';                                                                            

                for (int _ = 0; _ < 4; _++)
                    full_line[cursor++] = ' ';                                                                        

                for (size_t comment_cursor = 0; comment_cursor < strlen(comment); comment_cursor++)
                    full_line[cursor++] = comment[comment_cursor];                                                    
            }

            fprintf(destination, "%s\n", full_line);                                                                  
        }
        else {

            char full_line[3000] = "\0";                                                                             
            char code[1024]      = "\0";                                                                            

            ssize_t last_char_position = comment_splitter_position(line);                                             

            while (line[last_char_position] == ' '  || 
                   line[last_char_position] == '\t' ||
                   line[last_char_position] == ';') {
                last_char_position--;                                                                               
            }

            memcpy(code, line, last_char_position);                                                                  

            for (size_t cursor = 0; cursor < strlen(code) && cursor < 3000; cursor++)
                full_line[cursor] = code[cursor];                                                                     
            fprintf(destination, "%s\n", full_line);                                                                  
        }
    }

    fclose(source);                                                                                                   
    fclose(destination);                                                                                              
    remove(filename);                                                                                                 
    rename(destination_filename, filename);                                                                           
}

#ifndef ALCOM__TEST 

int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {
        info printf("checking file: %s\n", argv[i]);                                                                  

        FILE * source = fopen(argv[i], "r");                                                                          

        if (source) {
            info printf("processing file: %s\n", argv[i]);                                                            

            align_asm_file(argv[i]);                                                                                  

            done printf("file: %s was succesfully processed!\n", argv[i]);                                            
        }
        else {
            error printf("file: %s does not exists!\n", argv[i]);                                                  
        }
    }
}

#endif
