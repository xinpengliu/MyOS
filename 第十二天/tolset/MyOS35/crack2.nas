[INSTRSET "i486p"]
[BITS 32]
		MOV		EAX,1*8			; ìn?pi
		MOV		DS,AX			; «´¶üDS
		MOV		BYTE [0x102600],0
		MOV		EDX,4
		INT		0x40
