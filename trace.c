/*
 * trace.c 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "ObjectFiles.h"

#define VIDEO_ADDR   0xC000	// VIDEO Memeory Address
#define VIDEO_COLS   128	// Video Columns
#define VIDEO_ROWS   124	// Video Rows

#define INSN_14_10(I) (((I) >> 10) & 0x1F)
#define INSN_9_5(I) (((I) >> 5) & 0x1F)
#define INSN_4_0(I) ((I) & 0x1F)

MachineState theMachine;
ControlSignals theControls;
DatapathSignals theSignals;


int main(int argc, char *argv[])
{
	MachineState *ptrMachine = &theMachine;
	ControlSignals *ptrControls = &theControls;
	DatapathSignals *ptrSignals = &theSignals;
	int i;
	FILE *outFile;
	FILE *outImg;
	unsigned short int pc;
	unsigned short int insn;
	unsigned short int arr[2];
	char ppm[128];
	unsigned char rgb[3];
	int ret;

	unsigned int rn = 0; 


        if (argc <= 2)
        {
                printf("Error: Not enough arguments.  Requires trace output_filename obj_file... (at least 1 obj file)\n");
                return 1;
        }

	//reset the machine
	Reset (ptrMachine);

	//argv[0] = trace, ignore
	//argv[1] = output filename
	outFile = fopen(argv[1], "wb");
	outImg = fopen("image.ppm", "wb");

	if (outFile == NULL)
	{
		printf("Error: Failed to create trace file %s. Execution aborted\n", argv[1]);
		fclose(outImg);
		return 1;
	}

	if (outImg == NULL)
	{
		printf("Error: Failed to create PPM image file image.ppm. Execution aborted.\n");
		fclose(outFile);
		return 1;
	}

	
	//rest are .obj files
	for (i = 2; i < argc; i++)
	{
		ret = ReadObjectFile(argv[i], ptrMachine);
		if(ret != 0) {
			return 1;
		}
	}

	while (ptrMachine->PC != 0x80FF)
	{
		pc = ptrMachine->PC;
		insn = ptrMachine->memory[pc];
		arr[0] = pc;
		arr[1] = insn;

		//fwrite(arr, sizeof(short int), 2, outFile);
		++rn;
		printf("%d: Instruction -- ", rn);

		ret = DecodeCurrentInstruction(insn, ptrControls);		
	

		if (ret == 1) {
			printf("Error: Invalid Instruction encountered.  Execution Aborted.\n");
			break;	
		}	

		ret = SimulateDatapath(ptrControls, ptrMachine, ptrSignals);
		if (ret == 1)
		{		
			printf("Error: errors encountered while simulating datapth. Execuution Aborted.\n");
			break;
		}
		ret = UpdateMachineState(ptrControls, ptrMachine, ptrSignals);
		
                switch (ret)
                {
                        case 1 :
                                printf("Error: Attempting to execute a data section address as code\n");
                                break;
                        case 2 :
                                printf("Error: Attempting to read or write a code section address as data\n");
                                break;
                        case 3 :
                                printf("Error: Attempting to access an address or instruction in the OS section of memory when the processor is in user mode\n");
                                break;
                }


		if (ret != 0)
		{
			printf("Error: Update Machine error. Execution Aborted.\n");
			fclose(outImg);
			fclose(outFile);
			return 1;
		}
		else
		{
			// write PC and Instruction to trace file
                	fwrite(arr, sizeof(short int), 2, outFile);
		}

		if(ptrMachine->PC == 0x80FF)
		{	
			printf("PC = 0x80FF, Entering last instruction.  Execution Completed.\n");
   	             	pc = ptrMachine->PC;
			insn = 0xC907;		// TRAP Halt
                	arr[0] = pc;
                	arr[1] = insn;

                	fwrite(arr, sizeof(short int), 2, outFile);
			break;
		}
	}

	// PPM Header: P6 Width Height Max Colors
	strcpy(ppm, "P6 128 124 32\n");

	fwrite(ppm, 1, strlen(ppm), outImg);
        //output of video memory
        for (i = 0; i < (VIDEO_ROWS * VIDEO_COLS); i++)
        {
		rgb[0] = INSN_14_10(ptrMachine->memory[0xC000 + i]);
		rgb[1] = INSN_9_5(ptrMachine->memory[0xC000 + i]);
		rgb[2] = INSN_4_0(ptrMachine->memory[0xC000 + i]);
		fwrite(rgb, sizeof(unsigned char), 3, outImg);
        }

	fclose(outImg);
	fclose(outFile);

	printf("Summary: %d Instruction executed.  Trace File: %s created.  PPM Image File: image.ppm created.\n", rn, argv[1]);

	return 0;
}
