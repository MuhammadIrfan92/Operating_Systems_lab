#include "simplefs-ops.h"
extern struct filehandle_t file_handle_array[MAX_OPEN_FILES]; // Array for storing opened files

int simplefs_create(char *filename){
    /*
	    Create file with name `filename` from disk
	*/
    return -1;
}


void simplefs_delete(char *filename){
    /*
	    delete file with name `filename` from disk
	*/
}

int simplefs_open(char *filename){
    /*
	    open file with name `filename`
	*/
    return -1;
}

void simplefs_close(int file_handle){
    /*
	    close file pointed by `file_handle`
	*/
	file_handle_array[file_handle].offset = 0;
	file_handle_array[file_handle].inode_number = -1;

}

int simplefs_read(int file_handle, char *buf, int nbytes){
    /*
	    read `nbytes` of data into `buf` from file pointed by `file_handle` starting at current offset
	*/
    return -1;
}


int simplefs_write(int file_handle, char *buf, int nbytes){
    /*
	    write `nbytes` of data from `buf` to file pointed by `file_handle` starting at current offset
	*/
    return -1;
}


int simplefs_seek(int file_handle, int nseek){
    /*
	   increase `file_handle` offset by `nseek`
	*/
	
    if(file_handle_array[file_handle].offset + nseek < 0 || file_handle_array[file_handle].offset + nseek >= MAX_FILE_SIZE*BLOCKSIZE){
    	return -1; // failure, in case of offset goes beyond current file boundaries
    	}
		
    
    file_handle_array[file_handle].offset += nseek;
    return 0; // success
}
