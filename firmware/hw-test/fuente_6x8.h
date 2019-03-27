//Fuente 6x8 píxeles ordenana en ASCII
// Small 6x8 font
const char fuente[96][6]  = {  
{0x00,0x00,0x00,0x00,0x00,0x00},	//0	space
{0x00,0x00,0x5F,0x00,0x00,0x00},	//1	!
{0x00,0x00,0x07,0x00,0x07,0x00},	//2	"
{0x00,0x14,0x7F,0x14,0x7F,0x14},	//3	#
{0x00,0x24,0x2A,0x7F,0x2A,0x12},	//4	$
{0x00,0x23,0x13,0x08,0x64,0x62},	//5	%
{0x00,0x36,0x49,0x55,0x22,0x50},	//6	&
{0x00,0x00,0x05,0x03,0x00,0x00},	//7	'
{0x00,0x1C,0x22,0x41,0x00,0x00},	//8	(
{0x00,0x41,0x22,0x1C,0x00,0x00},	//9	)
{0x00,0x08,0x2A,0x1C,0x2A,0x08},	//10	*
{0x00,0x08,0x08,0x3E,0x08,0x08},	//11	+
{0x00,0xA0,0x60,0x00,0x00,0x00},	//12	,
{0x00,0x08,0x08,0x08,0x08,0x08},	//13	-
{0x00,0x60,0x60,0x00,0x00,0x00},	//14	.
{0x00,0x20,0x10,0x08,0x04,0x02},	//15	/
{0x00,0x3E,0x51,0x49,0x45,0x3E},	//16	0
{0x00,0x00,0x42,0x7F,0x40,0x00},	//17	1
{0x00,0x62,0x51,0x49,0x49,0x46},	//18	2
{0x00,0x22,0x41,0x49,0x49,0x36},	//19	3
{0x00,0x18,0x14,0x12,0x7F,0x10},	//20	4
{0x00,0x27,0x45,0x45,0x45,0x39},	//21	5
{0x00,0x3C,0x4A,0x49,0x49,0x30},	//22	6
{0x00,0x01,0x71,0x09,0x05,0x03},	//23	7
{0x00,0x36,0x49,0x49,0x49,0x36},	//24	8
{0x00,0x06,0x49,0x49,0x29,0x1E},	//25	9
{0x00,0x00,0x36,0x36,0x00,0x00},	//26	:
{0x00,0x00,0xAC,0x6C,0x00,0x00},	//27	;
{0x00,0x08,0x14,0x22,0x41,0x00},	//28	<
{0x00,0x14,0x14,0x14,0x14,0x14},	//29	=
{0x00,0x41,0x22,0x14,0x08,0x00},	//30	>
{0x00,0x02,0x01,0x51,0x09,0x06},	//31	?
{0x00,0x32,0x49,0x79,0x41,0x3E},	//32	@
{0x00,0x7E,0x09,0x09,0x09,0x7E},	//Se supone que es una A
{0x00,0x7F,0x49,0x49,0x49,0x36},	//34	B
{0x00,0x3E,0x41,0x41,0x41,0x22},	//35	C
{0x00,0x7F,0x41,0x41,0x22,0x1C},	//36	D
{0x00,0x7F,0x49,0x49,0x49,0x41},	//37	E
{0x00,0x7F,0x09,0x09,0x09,0x01},	//38	F
{0x00,0x3E,0x41,0x41,0x51,0x72},	//39	G
{0x00,0x7F,0x08,0x08,0x08,0x7F},	//40	H
{0x00,0x41,0x7F,0x41,0x00,0x00},	//41	I
{0x00,0x20,0x40,0x41,0x3F,0x01},	//42	J
{0x00,0x7F,0x08,0x14,0x22,0x41},	//43	K
{0x00,0x7F,0x40,0x40,0x40,0x40},	//44	L
{0x00,0x7F,0x02,0x0C,0x02,0x7F},	//45	M
{0x00,0x7F,0x04,0x08,0x10,0x7F},	//46	N
{0x00,0x3E,0x41,0x41,0x41,0x3E},	//47	O
{0x00,0x7F,0x09,0x09,0x09,0x06},	//48	P
{0x00,0x3E,0x41,0x51,0x21,0x5E},	//49	Q
{0x00,0x7F,0x09,0x19,0x29,0x46},	//50	R
{0x00,0x26,0x49,0x49,0x49,0x32},	//51	S
{0x00,0x01,0x01,0x7F,0x01,0x01},	//52	T
{0x00,0x3F,0x40,0x40,0x40,0x3F},	//53	U
{0x00,0x1F,0x20,0x40,0x20,0x1F},	//54	V
{0x00,0x3F,0x40,0x38,0x40,0x3F},	//55	W
{0x00,0x63,0x14,0x08,0x14,0x63},	//56	X
{0x00,0x03,0x04,0x78,0x04,0x03},	//57	Y
{0x00,0x61,0x51,0x49,0x45,0x43},	//58	Z
{0x00,0x7F,0x41,0x41,0x00,0x00},	//59	[
{0x00,0x02,0x04,0x08,0x10,0x20},	//60	\ 
{0x00,0x41,0x41,0x7F,0x00,0x00},	//61	]
{0x00,0x04,0x02,0x01,0x02,0x04},	//62	^
{0x00,0x80,0x80,0x80,0x80,0x80},	//63	_
{0x00,0x01,0x02,0x04,0x00,0x00},	//64	'
{0x00,0x20,0x54,0x54,0x54,0x78},	//65	a
{0x00,0x7F,0x48,0x44,0x44,0x38},	//66	b
{0x00,0x38,0x44,0x44,0x28,0x00},	//67	c
{0x00,0x38,0x44,0x44,0x48,0x7F},	//68	d
{0x00,0x38,0x54,0x54,0x54,0x18},	//69	e
{0x00,0x08,0x7E,0x09,0x02,0x00},	//70	f
{0x00,0x18,0xA4,0xA4,0xA4,0x7C},	//71	g
{0x00,0x7F,0x08,0x04,0x04,0x78},	//72	h
{0x00,0x00,0x7D,0x00,0x00,0x00},	//73	i
{0x00,0x80,0x84,0x7D,0x00,0x00},	//74	j
{0x00,0x7F,0x10,0x28,0x44,0x00},	//75	k
{0x00,0x41,0x7F,0x40,0x00,0x00},	//76	l
{0x00,0x7C,0x04,0x18,0x04,0x78},	//77	m
{0x00,0x7C,0x08,0x04,0x7C,0x00},	//78	n
{0x00,0x38,0x44,0x44,0x38,0x00},	//79	o
{0x00,0xFC,0x24,0x24,0x18,0x00},	//80	p
{0x00,0x18,0x24,0x24,0xFC,0x00},	//81	q
{0x00,0x00,0x7C,0x08,0x04,0x00},	//82	r
{0x00,0x48,0x54,0x54,0x24,0x00},	//83	s
{0x00,0x04,0x7F,0x44,0x00,0x00},	//84	t
{0x00,0x3C,0x40,0x40,0x7C,0x00},	//85	u
{0x00,0x1C,0x20,0x40,0x20,0x1C},	//86	v
{0x00,0x3C,0x40,0x30,0x40,0x3C},	//87	w
{0x00,0x44,0x28,0x10,0x28,0x44},	//88	x
{0x00,0x1C,0xA0,0xA0,0x7C,0x00},	//89	y
{0x00,0x44,0x64,0x54,0x4C,0x44},	//90	z
{0x00,0x08,0x36,0x41,0x00,0x00},	//91	{
{0x00,0x00,0x7F,0x00,0x00,0x00},	//92	|
{0x00,0x41,0x36,0x08,0x00,0x00},	//93	}
{0x00,0x02,0x01,0x01,0x02,0x01},	//94	x3^
{0x00,0x02,0x05,0x05,0x02,0x00} 	//95	x4^
};

