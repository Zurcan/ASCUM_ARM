/*
 *  This file describe the  SPI protocol between BKS and USB_BKS.
 *
 *	Global schema
 *	-------------
 *	AA - packet start marker
 *
 *
 *	00 (anything except FF) 
 *	b(status) 
 *
 *	AA w(size) b(cmd) ab(follow_code) d(CRC32)// atom command transp
 *	b(status) b(status) b(status) b(status) b(status) b(status) b(status) b(status)
 *
 *
 *	Details
 *	-------
 *	MOSI: AA        05 00 81(readBuffer) d(CRC32) 00 00 00 00 00 00 00 00 00 00 00 00
 *	MISO: b(status) b(status) b(status) b(status) xx xx xx xx xx xx AA w(size) DD DD 

DD DD DD DD DD DD DD DD CRC32
 *	
 *	MOSI: AA        w(size+5) 82(writeBuffer) DD DD DD DD DD DD DD DD DD DD CRC32
 *	MISO: b(status) b(status) b(status) b(status) b(status) b(status) b(status) b

(status)
 *			
 *	MOSI: AA        05 00 0D(read status) d(CRC32)
 *	MISO: b(status) b(status) b(status) b(status) xx xx xx xx AA w(size) b(cmd) b

(ErrorCode) CRC32
 *	
 *		
 *	cmd|  code            | follow code                              return
 *	---+------------------+-----------------------------------------------------
 *	01 |  open file desc    b(desc),b(mode),str(null_term_filename)  
 *	02 |  close file desc   b(desc)
 *	03 |  erase 		   			str(null_term_filename)
 *	04 |  seek file desc    b(desc),d(pos)
 *	05 |  read file desc    b(desc),d(size)
 *	06 |  write file desc   b(desc)
 *	07 |  cutFile desc      b(desc)
 *	08 |  mkDir             str(null_term_filename)
 *	09 |  rmDir             str(null_term_filename)
 *	0A |  chdir             str(null_term_filename)
 *	0B |  dir								str(null_term_filename)    
 *	0E |  setTimeStamp_desc b(desc)  * NOT IMPLIMENTED *
 *	0F |  setTimeStamp      d(new_time(time_t)),str(null_term_filename)
 *	10 |  get File info     str(null_term_filename)
 *	11 |  flush desc				b(desc)
 *	12 |  rename						str(null_term_filename_old),str(null_term_filename_new)
 *	13 |  file size desc		b(desc)
 *	14 |  get free space		
 
 *	81 |  readBuffer
 *	82 |  writeBuffer
 *	83 |  status update (clear read once flags)
 *	84 |  read status   
 * 	85 |  jump to bootloader
  
 *	41 |  get user program crc
 *	42 |  erase user program
 *	43 |  write user program block    d(addr_offset),d(size in bytes),program_itself
 *	44 |  jump to user program		b(forced)
 *	45 |  get signature
 *	46 |  set serial number	d(ser_num) | [can be set only once]
 *  47 |  set checked flag				 [can't be cleared]
 
---------------------------------------------------------------------------
SPI Protocol commands examples:
---------------------------------------------------------------------------
¹ | HEX command										| Description
---------------------------------------------------------------------------
1 | 01 01 13 41 42 43 2E 74 78 74 00				| open(1, FA_READ | FA_WRITE | FA_OPEN_ALWAYS, "ABC.txt")
---------------------------------------------------------------------------
2 | 82 54 68 69 73 20 69 73 20 61 20 74 65 78 74 2e	| WriteBuffer("This is a text.")
---------------------------------------------------------------------------
3 | 06 01	 										| write(1)
---------------------------------------------------------------------------
4 | 11 01	 										| flush(1)
---------------------------------------------------------------------------
5 | 02 01	 										| close(1)
---------------------------------------------------------------------------
6 | 84		 										| ReadStatus
---------------------------------------------------------------------------
7 | 81		 										| ReadBuffer
---------------------------------------------------------------------------
8 | 01 02 01 74 65 73 74 66 69 6C 65 2E 74 78 74 00	| open(2, FA_READ | FA_OPEN_EXISTING, "testfile.txt")
---------------------------------------------------------------------------
9 | 05 02 00 04 00 00 								| read(2, 1024)
---------------------------------------------------------------------------
10| 83		 										| StatusUpdate
---------------------------------------------------------------------------
11| 13 02	 										| file_size(2)
---------------------------------------------------------------------------
12| 04 01 0f 00 00 00 								| file_seek(1, 15)
---------------------------------------------------------------------------
13| 0a 2F 74 65 73 74 64 69 72 00					| ch_dir("/testdir")
---------------------------------------------------------------------------
14| 0b 2e 00 										| dir(".")
---------------------------------------------------------------------------
15| 07 01 											| cut(1)
---------------------------------------------------------------------------
16| 08 64 61 64 64 79 31 00							| mk_dir("daddy1")
---------------------------------------------------------------------------
17| 09 64 61 64 64 79 31 00							| rm_dir("daddy1")
---------------------------------------------------------------------------
18| 03 41 42 43 2E 74 78 74 00						| del("ABC.txt")
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMANDS_H__
#define __COMMANDS_H__

typedef enum {
	COMMAND_NOCMD   					= 0x00,
	COMMAND_OPEN							= 0x01,
	COMMAND_CLOSE							= 0x02,
	COMMAND_ERASE							= 0x03,
	COMMAND_SEEK							= 0x04,
	COMMAND_READ							= 0x05,
	COMMAND_WRITE							= 0x06,
	COMMAND_CUT								= 0x07,
	COMMAND_MKDIR							= 0x08,
	COMMAND_RMDIR							= 0x09,
	COMMAND_CHDIR							= 0x0a,
	COMMAND_DIR								= 0x0b,
	COMMAND_SETTIMESTAMPDESC	= 0x0e,
	COMMAND_SETTIMESTAMP			= 0x0f,
	COMMAND_GETFILEINFO				= 0x10,
	COMMAND_FLUSH							= 0x11,
	COMMAND_RENAME						= 0x12,
	COMMAND_FSIZE							= 0x13,
	COMMAND_GETFREESPACE			= 0x14,
		
	// There is no file operation commands
	COMMAND_SPICOMMAND		= 0x80,
	COMMAND_READBUFFER		= 0x81,
	COMMAND_WRITEBUFFER		= 0x82,
	COMMAND_STATUSUPDATE	= 0x83,
	COMMAND_READSTATUS		= 0x84,
	COMMAND_JMPBOOTLOADER	= 0x85,
	
	// There is bootloader commands
	COMMAND_BOOTLOADERCOMMAND		= 0X40, /* The mask of bootloader commands */
	COMMAND_GETUSERPROGRAMCRC		= 0x41,
	COMMAND_ERASEUSERPROGRAM		= 0x42,
	COMMAND_WRITEUSERPROGRAM		= 0x43,
	COMMAND_JMPUSERPROGRAM			= 0x44,
	COMMAND_GETSIGNATURE				= 0x45,
	COMMAND_SETSERIALNUMBER			= 0x46,
	COMMAND_SETCHECKED					= 0x47,
	COMMAND_TESTUSBPORT					= 0x48,
	
}COMMAND_Type;

// spi status flags define
#define SS_ANYERROR					0x3 
#define SS_RECVERROR				0x1 
#define SS_EXECERROR				0x2 
#define SS_READY						0x4 
#define SS_BUFFERREADY			0x8 
#define SS_VCPMODE					0x10	/* Virtual Com Port Mode, only in app mode */
#define SS_NOUSBDEV					0x80

// boot loader mode flags, the application should'n set these bits
#define SS_BOOTLOADERMODE				0x40
// boot loader mode flags, the application may use it for any other purposes
#define SS_BOOTLOADERCRCERROR		0x4f
#define SS_USERPROGRAMERROR			0x20
#define SS_HADWAREUNCHECKED			0x10

// packet start byte
#define START_MARKER					0xaa

#define MAX_DATA_SIZE					4096+10
#define MAX_PACKET_SIZE				MAX_DATA_SIZE+32//0x8000

#endif /*__COMMANDS_H__*/
