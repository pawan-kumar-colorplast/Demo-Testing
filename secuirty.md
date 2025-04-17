
62 2C [File Control Parameters & Length]

	82 02 [File Descriptor & Length]
		78 [File descriptor byte]
			01 [Shareable file ] -> File accessibility
			111 [DF or ADF] -> File type
			000 [No information given] -> EF structure
		21 [Data coding byte] -> The actual value shall not be checked nor used by the terminal. 
		
	83 02 [File Identifier]
		3F 00 
		
	A5 0C [Proprietary information & Length] 
		80 01 [UICC characteristics & Length]
			71 
				0100
				0111
		83 04 [Amount of available memory]
			00 03 8C C8
		87 01 [Supported system commands & Length]
			00 
			
	8A 01 [Life Cycle Status Integer & Length]
		05 
	8B 03 [Security attributes & Length]
		2F 06 04 
	
	C6 0C [PIN Status Template DO & Length]
		90 01 [PS_DO tag & Length]
			E0 
		83 01 [Key reference tag & Key reference length ]
			01 
		83 01 [Key reference tag & Key reference length ]
			0A 
		83 01 [Key reference tag & Key reference length ]
			81 
	90 00 [Command successfully executed (OK)]
	




=====selet MF & get Response
62 -2C- 82 02 78 21 83 02 -3F- -00- A5 0C 80 01 71 83 04 00 03 8C C8 87 01 00 8A 01 05 8B 03 2F 06 -04- C6 -0C- 90 01 -E0- 83 01 01 83 01 0A 83 01 81 90 00
=====selet DF & get Response
62 -29- 82 02 78 21 83 02 -7F- -49- A5 0C 80 01 71 83 04 00 03 8C C8 87 01 00 8A 01 05 8B 03 2F 06 -03- C6 -09- 90 01 -C0- 83 01 01 83 01 0A 90 00
=====selet EF & get Response
62 16 82 02 41 21 83 02 6F 17 8A 01 05 8B 03 2F 06 03 80 02 00 30 88 00 90 00



62 16 [File Control Parameters & Length]
	82 02  [File Descriptor & Length]
		41 
			01 [Shareable file]
			000 [Working EF]
			001 [Transparent structure]
		21 [Data coding byte] -> The actual value shall not be checked nor used by the terminal. 
	83 02  [File Identifier]
		6F 17 
		
	8A 01  [Life Cycle Status Integer & Length]
		05 [Operational state - activated]
		
	8B 03 [Security attributes & Length]
		2F 06 [File ID ]
			03 [Record number ]
	80 02 [File size & Length]
		00 30 
	88 00 [Short File Identifier (SFI) & Length]
90 00




==============
Reset successful.
Send: 00 A4 00 04 02 3F 00
Recv: 61 2E
Time used: 235.000 ms
Send: 00 A4 00 04 02 7F 49
Recv: 61 2B
Time used: 47.000 ms
Send: 00 A4 00 04 02 6F 17
Recv: 61 18
Time used: 31.000 ms
Send: 00 C0 00 00 18
Recv: 62 16 82 02 41 21 83 02 6F 17 8A 01 05 8B 03 2F 06 03 80 02 00 30 88 00 90 00
Time used: 16.000 ms
Send: 00 B0 00 00 00
Recv: 6C 30
Time used: 32.000 ms
Send: 00 B0 00 00 05
Recv: FF FF FF FF FF 90 00
Time used: 16.000 ms
Send: 00 D6 00 05 05 50 41 57 41 4E
Recv: 69 82
Time used: 16.000 ms
==============


Send: 00 A4 00 04 02 3F 00
Recv: 61 2E
Time used: 33.000 ms
Send: 00 A4 00 04 02 2F 06
Recv: 61 1B
Time used: 47.000 ms
Send: 00 C0 00 00 1B
Recv: 62 19 82 05 42 21 00 37 28 83 02 2F 06 8A 01 05 8B 03 2F 06 06 80 02 08 98 88 00 90 00
Time used: 32.000 ms




Parsing
=======
62 19 
	82 05 [File Descriptor & Length]
		42 
			01 -> Shareable file
			000 -> Working EF 
			010 -> Linear fixed structure 
		21 -> Data coding byte
		00 37   -> Record length 
		28 -> Number of records 
	
	83 02  [File Identifier & Length]
		2F 06 
	
	8A 01 [Life Cycle Status Integer & Length]
		05 
	
	8B 03 [Security attributes & Length]
		2F 06 
		06 
	
	80 02 [File size & Length]
		08 98 
	
	88 00 [Short File Identifier (SFI) & Length]

90 00

========
Send: 00 B2 06 04 37
Recv: 80 01 01 90 00 80 01 1A A4 06 83 01 0A 95 01 08 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 90 00
Time used: 39.000 ms
========= Parsing
80 01 [Access mode byte & Length]
	01  [READ BINARY, READ RECORD (S), SEARCH BINARY, SEARCH RECORD]

90 00 [ ALW ]

80 01 [Access mode byte & Length]
	1A 
		0001 ACTIVATE FILE
		1   DEACTIVATE FILE
		0
		1   UPDATE BINARY, UPDATE RECORD, ERASE BINARY, ERASE RECORD (S) 
		0

A4 06 83 01 0A 95 01 08 [PIN mapping into key references ]
		A4 - CRT Tag
		06 - Length
		83 - Key Ref Tag
		01 - Length
		0A - Value    (0A -> 3g/4g/5g and 04 -> 2g)
		95 - Usage Qualifier Tag
		01 - Length
		08 - Value
		
FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF (Blank)
90 00 [Command successfully executed (OK).]

========
PIN = 34 33 32 31 FF FF FF FF
=========
Send: 00 20 00 0A 08 34 33 32 31 FF FF FF FF 37
Recv: 90 00
Time used: 55.000 ms
========

50 41 57 41 4E FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
