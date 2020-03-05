.code16
start:
	cli                             # 关闭中断
	inb $0x92, %al                  # 启动A20总线
	orb $0x02, %al
	outb %al, $0x92
	data32 addr32 lgdt gdtDesc      # 加载GDTR
	movl %cr0, %eax                 # 启动保护模式
	orb $0x01, %al
	movl %eax, %cr0                 # 设置CR0的PE位（第0位）为1
	data32 ljmp $0x08, $start32     # ⻓跳转切换⾄保护模式

.code32 
start32:
	                             # 初始化DS ES FS GS SS 初始化栈顶指针ESP
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movw %ax, %fs
	movw $0x18, %ax
	movw %ax, %gs
	movl $(128 << 20), %esp
	jmp bootMain                    # 跳转⾄bootMain函数  定义于boot.c

gdt:
	.word 0,0                       # GDT第⼀个表项必须为空
	.byte 0,0,0,0
	
	.word 0xffff,0                  # 代码段描述符
	.byte 0,0x9a,0xcf,0
	
	.word 0xffff,0                  # 数据段描述符
	.byte 0,0x92,0xcf,0
	
	.word 0xffff,0x8000             # 视频段描述符
	.byte 0x0b,0x92,0xcf,0
	

gdtDesc:
	.word (gdtDesc - gdt -1)
	.long gdt
