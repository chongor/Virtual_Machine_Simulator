/*
 * ObjectFiles.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "ObjectFiles.h"

int ReadObjectFile (char *filename, MachineState *theMachineState)
{

	//types of sections
	//CODE: 3-word header (xCADE, <address>, <n>), n-word body comprising the instructions
	//DATA: 3-word header (xDADA, <address>, <n>), n-word body comprising the initial data values
	//Symbol: (xC3B7, <address>, <n>), n-character body comprising symbol string, each char is 1 byte
	//	each symbol is own section
	//File name: (xF17E, <n>), n-character body comprising the filename string, each char is 1 byte
	//	each file is its own section
	//Line number: (x715E, <addr>, <line>, <file-index>), no body.  file-index = index of file in 
	//	list of file name sections, so if code comes from two C files, 
	//	line number directives should be attached to file numbers 0 or 1

	//open file for reading
	FILE *file;	
	unsigned long fileLeng;
	short int ms_byte;
	short int ls_byte;
	int addr;
	int two_byte;
	int insn_byte;
	int n;
	int i = 0;
	//for header: 1 = id, 2 = addr, 3 = n, 4 = line, 5 = file-index
	int header = 0;
	//for mode: 1 = id, addr, n; 2 = id, n; 3 = id, addr, n, line file-index
	unsigned int totalcode = 0;
	unsigned int totaldata = 0;
	int iscode = 0;

	printf("Reading object file %s.....\n", filename);

	file = fopen(filename, "rb");

	if (file == NULL)
	{
		printf("Error: Couldn't open file %s. Execution aborted.\n", filename);
		return 1;
	}

	while (1)
	{
		iscode = 0;
		
		ms_byte = fgetc(file);
		ls_byte = fgetc(file);

		if (ms_byte == EOF || ls_byte == EOF)
		{
			break;	// EOF
		}

		two_byte = ((ms_byte << 8) | (ls_byte & 0xFF));

		//Line number
		if (two_byte == 0x715E)
		{
			for (i = 0; i < 6; i++)
			{
				ms_byte = fgetc(file);
				if (ms_byte == EOF)
				{
					printf("Error: Bad format reading Line Number Section. Execution aborted\n");
					fclose(file);
					return 1;
				}
			}
			continue;
		}

		//File name
		if (two_byte == 0xF17E)
		{
			ms_byte = fgetc(file);
			ls_byte = fgetc(file);

			if (ms_byte == EOF || ls_byte == EOF)
			{
				printf("Error: Bad format reading File Name Section. Execution aborted\n");
				fclose(file);
				return 1;
			}
	
			n = ((ms_byte << 8) | (ls_byte & 0xFF));
			
			for (i = 0; i < n; i ++)
			{
				ms_byte = fgetc(file);

				if (ms_byte == EOF)
				{
					printf("Error: Bad format reading File Name Section. Execution aborted\n");
					fclose(file);
					return 1;
				}
            }
			
			continue; 
		}
		
		//Symbol
		if (two_byte == 0xC3B7)
		{
			//to skip the address
			for (i = 0; i < 2; i++)
			{
				ms_byte = fgetc(file);
				ls_byte = fgetc(file);
				
				addr = ((ms_byte << 8) | (ls_byte & 0xFF));
				if (ms_byte == EOF || ls_byte == EOF)
				{
					printf("Error: Bad format reading File Name Section. Execution aborted\n");
					fclose(file);
					return 1;
				}		
			}

			n = addr;	
		
			for (i = 0; i < n; i ++)
			{
				ms_byte = fgetc(file);
				if (ms_byte == EOF)
				{
					printf("Error: Bad format reading Symbol Section. Execution aborted\n");
					fclose(file);
					return 1;
				}
			}
			continue;
		}		

		//CODE and DATA
		if (two_byte != 0xCADE && two_byte != 0xDADA)
		{
			printf("Error: invalid Section id found: %04X.  Execution aborted.\n", two_byte);
			fclose(file);
			return 1;
		}

		ms_byte = fgetc(file);
		ls_byte = fgetc(file);

		if (ms_byte == EOF || ls_byte == EOF)
		{
			printf("Error: Unexpected End of File Encountered.  Execution Aborted\n");
			fclose(file);
			return 1;
		}

		addr = ((ms_byte << 8) | (ls_byte & 0xFF));

		if (two_byte == 0xCADE)
		{
			iscode = 1;
			if ((addr >= 0x4000 && addr <= 0x7FFF) || addr >= 0xA000)
			{
				printf("Error: invalid code memory address\n");
				fclose(file);
				return 1;
			}
		}

		if (two_byte == 0xDADA)
		{
			if ((addr <= 0x3FFF) || (addr >= 0x8000 && addr <= 0x9FFF ))
			{
				printf("Error: invalid data memory address\n");
				fclose(file);
				return 1;
			}
		}

		ms_byte = fgetc(file);
		ls_byte = fgetc(file);
		
		if (ms_byte == EOF || ls_byte == EOF)
		{
			printf("Error: Unexpected End of File Encountered.  Execution Aborted\n");
			fclose(file);
			return 1;
		}

		n = ((ms_byte << 8) | (ls_byte & 0xFF));

		if(iscode == 1)
			totalcode += n;
		else
			totaldata += n;
			
		for (i = 0; i < n; i++)
		{
			ms_byte = fgetc(file);
			ls_byte = fgetc(file);

			if (ms_byte == EOF && ls_byte == EOF)
			{
				printf("Error: Unexpected End of File Encountered.  Execution Aborted\n");
				fclose(file);
				return 1;
			}
			
			insn_byte = ((ms_byte << 8) | (ls_byte & 0xFF));
			theMachineState->memory[addr + i] = insn_byte;
		}
	}
	fclose(file);
	printf("Successfully read file: %s. Total Code: %d  Total Data: %d.\n", 
		filename, totalcode, totaldata);

	//no problems encountered
	return 0;
}
