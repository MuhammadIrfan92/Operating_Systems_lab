#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>


const int PAGE_SIZE = 256;
const int PAGE_TABLE_SIZE = 256;
const int PHYSICAL_MEM_SIZE = 65536;
const int TLB_SIZE = 16;


// tlb struc
struct tlb_struct {
	unsigned int page;
	unsigned int frame;
};


float percentage(int a){
	float per;
	per = ((double) a/1000) * 100;
	return per;
}

int main (int argc, char *argv[]){
	int i;
	
	//initialilze page table. 256 rows and 1 column
	
	int page_table[PAGE_TABLE_SIZE];
	for (i = 0; i < PAGE_TABLE_SIZE; i++){
		page_table[i] = -1;
	}
	
	//memset(page_table,-1,PAGE_TABLE_SIZE*sizeof(int));
	
	//initialize tlb table 16 rows 2 colums
	struct tlb_struct tlb[TLB_SIZE];	
	for (i =0; i < TLB_SIZE; i++){
		tlb[i].page	= -1;
		tlb[i].frame = -1;
	}
	//memset(page_table,-1,TLB_SIZE*sizeof(char));
	
	int physical_memory[PHYSICAL_MEM_SIZE];
	
	char buffer[PAGE_SIZE];
	
	int logicalAddress = 0;
	int page_number = 0;
	int offset = 0;
	
	int physical_address =0;
	int frame =0;
	int value =0;
	
	int tlb_hit =0;
	int tlbIndex=0;
	int tlb_buffer =0;
	
	int page_fault_count =0;
	double page_fault_rate =0;
	int tlb_hit_count =0;
	double tlb_hit_rate=0;
	
	FILE *addressFile;
	addressFile = fopen(argv[1],"r");
	if ( addressFile == NULL){
		printf("address.txt is not available!\n");
		return 0;
	}
	
	// OPEN backing_store.bin
	
	FILE *backing_store;
	backing_store = fopen("BACKING_STORE.bin","rb");
	
	if (backing_store == NULL){
		printf("BACKING_STOREE.bin is not available\n");
		return 0;
	}
	
	//read addresses from address.txt
	
	while(fscanf(addressFile,"%d",&logicalAddress)==1){
		//extracting right most 16 bits, 8 for offset and 8 for page number
		page_number = (logicalAddress & 0xFF00) >> 8;
		offset = logicalAddress & 0x00FF;
		tlb_hit = -1;
		//check the tlb to find a match for given page number
		for ( i =0;i<tlb_buffer;i++){
			if(tlb[i].page == page_number){
				tlb_hit = tlb[i].frame;
				physical_address = tlb_hit*PAGE_SIZE + offset;
			}
		}
		
		// if not found in tlb then check in page table
		if (!(tlb_hit == -1)){
			tlb_hit_count++;
		}
		else if(page_table[page_number] == -1){
			//it reads from backing_store.bin to update the physical memory
			fseek(backing_store,page_number*PAGE_SIZE,SEEK_SET);
			fread(buffer, sizeof(char), PAGE_SIZE, backing_store);
			page_table[page_number] = frame;
			for(i = 0 ; i <PAGE_SIZE; i++){
				physical_memory[frame*PAGE_SIZE + i]= buffer[i];
				
			}
			page_fault_count++;
			frame++;
			
			if(tlb_buffer == TLB_SIZE){
				tlb_buffer--;
			}
			
			//update the tlb
			for(tlbIndex=tlb_buffer; tlbIndex > 0; tlbIndex--){
				tlb[tlbIndex].page = tlb[tlbIndex -1].page;
				tlb[tlbIndex].frame = tlb[tlbIndex -1].frame;
			}
			
			if(tlb_buffer <=15){
				tlb_buffer++;
			}
			
			tlb[0].page = page_number;
			tlb[0].frame = page_table[page_number];
			physical_address = page_table[page_number]*PAGE_SIZE + offset;
			
			
		}
		else {
			physical_address = page_table[page_number]*PAGE_SIZE + offset;
			
		}
		
		value = physical_memory[physical_address];
		printf("Virtual address:%4d\t",logicalAddress);
		printf("Physical address: %4d\t", physical_address);
		printf("Value: %4d\n",value);
		
	}
	
	
	page_fault_rate = percentage(page_fault_count);
	printf("page fault rate: %.2f%%\n",page_fault_rate);
	
	
	tlb_hit_rate = percentage(tlb_hit_count);
	printf("tlb hit rate: %.2f%%\n",tlb_hit_rate);
	
	fclose(addressFile); 
	return 0;
	
	
	
	
	
	
	
}
