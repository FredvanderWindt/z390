# z390 File types

The scope value details where the option is used.

* M - Macro assembler
* A - Assembler
* L - Linker
* E - Execution

File extension | Scope | Format | File Description | File or Report Format Description
---|---|---|---|---
BAL | MA | ASCII | Basic Assembly Language generated ASCII source file generated by mz390 when option BAL is specified.  When option ASM is on (the default), mz390 starts az390 as a separate process running in parallel and passes generated BAL statements directly to it.  This allows the first pass of assembler processing to be overlapped with macro expansion and eliminates need to write this file to external disk.|Basic Assembler format is free form within first 71 characters with optional label starting in position 1 followed by opcode followed by operands if any.  If continuation is required a non-space character appears in position 72.  Positions 73-80 may be used for sequence numbering.  The ICTL  instruction may be used to change these default setting but it is not recommended as the macro and copybook files are all in the default format.  Embedded AREAD records longer than 71 characters must be in standard continuation format for preloading of MLC and MAC files (a z390 restriction).  Note the default NOALLOW limits AREAD and PUNCH records to maximum of 80.
CPY | MA | ASCII | Copybook source included in source programs, macros, or other copybooks|Same format as BAL
DAT | M | ASCII | Text data input files read via AREAD statements in macro processor specifying ID=, DDNAME= or DSNAME= extended parameters.  AREAD with no extended parameters reads the next statement in the input stream.|Same format as BAL except text records can be any length with no continuation format required using ALLOW
ERR | MALE | ASCII | Output log of all START and ENDED messages plus any errors plus any error file references.|Text file with messages showing start and stop statistics for each step and any error messages issued by those steps.  A cross reference of all macro and copybook files with errors is included at the end.  For full cross reference of all macros and copybooks used see STA file.
LOG | E | ASCII | Output log of for GUI or batch command execution controlled by CON option|Test file with messages issued udring program execution including start and stop statistics plus any errors and any WTO write to operator messages.
LKD | L | ASCII | Optional input command for linker (INCLUDE, ENTRY, ALIAS, NAME)|Same format as BAL.
MAC | M | ASCII | macro source files|Same format as BAL.
MLC|| M | ASCII | macro assembler source programs read by mz390|Same format as BAL.
MOD | LE | Binary | Binary code output from linker with no header and no RLD records.  This type file can be created using option MOD and can be loaded as a data table by Micro Focus CICS,|Binary file with all CSECT binary data.  For example DC C'ABC' using option MOD will result in 3 byte MOD file containing x'C1C2C3'.
OBJ|AL|EBCDIC, ASCII|Output relocatible object code file for macro assembler with two format options. |The default is mainframe linker compatible relocatible object code 80 records (ESD, TXT, RLD, and END).  When OBJHEX option is specified for assembler, ASCII readable text extended format supporting 31 bit long sections is generated.  The z390 linker can read either format by examining file.
OPT | MALE | ASCII | Optional options files referenced via @file option from command line or other option files|Text file with z390 options entered in free format delimited by spaces.  An * will terminate options on a line and start comments on that line. 
PCH|M|ASCII|Output text files written via PUNCH statements in macro processor using optional ID=, DDNAME=, or DSNAME= extended parameters.  The default is pgm.PCH.|Text file output which is not limited to 80 byte BAL format using ALLOW.  Any macro program generating BAL output must format continuations.
PRN|A|ASCII|Output assembly language listing from az390|Text file with the following listing fields:<br/>1) hex relative offset to instruction<br/>2) hex bytes in instruction or data with up ot 8 bytes per line.  Direction PRINT DATA will force listing all data 8 bytes per line.<br/>3) (file#/file-line#)generated-line# identified the file # and the relative file line #for the MLC, MAC, or CPY file that the generated line came from followed by the sequential generated line #.<br/>4) Flag field has + for macro generated lines, and = for line from copybook.<br/>5)BAL line with label, opcode, and operands.
STA|MALE|ASCII|Output statistics file listing options set, program statistics, and file references|Text file with detail statistics on each step including all option settings, complete macro and copybook cross reference for mz390, and execution statistics.
TRA|A|ASCII|Trace output file for assembler (lists each line being assembled during each pass)|Text file with ma390 assembler trace output including source file name, relative line, generated line, relative hex offset, and source statement for each assembler pass which may be 2 or more depending on usage of LOCTR.
TRE|E|ASCII|Trace output file for emulator (lists each instruction, address, and operand values)|Text file with ez390 emulator execution trace output showing, hex psw address, condition code, hex instruction, mnemonic, operand register and storage values at the start of each instruction.  Blank line inserted for each branch to non sequential address.  The high bit of PSW hex address indicates 24 or 31 bit address mode.
TRL|L|ASCII|Trace output file for linker (lists each OBJ record processed)|Text file with lz390 linker trace output including ESD external symbol hex addresses and lengths, TXT text records with relative offset within ESD and hex data.  RLD relocation records showing hex offset, field length, and ESD symbol.
TRM|M|ASCII|Trace output file for macro process (TRACEM lists each macro line executed, TRACEP lists every macro pseudo code instruction executed showing the current value of local and global variables used in SET statements and AIF statements etc.)|Text file with mz390 macro processor trace output file which is typically generated in parallel with the generation of the first pass information in the TRA file since mz390 and az390 run as concurrent tasks.  This file includes source file name, relative line number, and source macro statement.  For generated BAL output lines the source file# and relative line# cross reference is also include.  If the TRACEP option is specified, this file also includes listing of the generation and execution of macro pseudo code instructions.
TRS|E|ASCII|Report from ZPARTRS utility|TRACE CBL AND ASM source execution
ZSM|M|ASCII|ZSTRMAC Structured Conditional Macro source programs.|Use ZSTRMAC.BAT file1 file2 to translate ZSM type file to standard HLASM compatible MLC type source file.
390|LE|binary|Executable z390 load modules created by linker from OBJ files and loaded by emulator. |The 390 load modules contain 20 byte header with the following: