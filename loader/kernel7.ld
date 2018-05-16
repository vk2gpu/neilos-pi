SECTIONS
{
	.ivt 0x0000 :
	{
		*(.ivt)
	}

	.init 0x8000 :
	{
		*(.init)
	}
	
	.text :
	{
		*(.text)
	}
	
	.data :
	{
		*(.data)
	}

	/DISCARD/ :
	{
		*(*)
	}
}
