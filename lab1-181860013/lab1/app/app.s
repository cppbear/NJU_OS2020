.code32

.global start
start:
	pushl $2004
	pushl $ascpic
	calll displayStr
loop:
	jmp loop

ascpic:
	.string "t;i1t;;,;;itL;;ii.:.:;;fLC888800000000000008000000008C800888C0000000000000000000ff1ff:tt;:;t1i;it;LGGCCC880000000000888000000800000000000000000008000000000000::tfLGtfi i;;ii1tLLCG8888888880888080000008888LL800000000000000008000000000001::;;1fLff111,:1fLGC8888C80C088800800808888L808f1i;::;;;;i800800800080080000001;;:;itt;,fttff1fG0C80G8GGGC8888880088CCGC808ti1t;;;:;;;;;;i;;;;i8808000000000:::;iti1111ttittG800808LLCC8C8888CGC8CC880tL8L1ff1i;;;:::;iiiiii1i;;;;G0000080;:;;1ttfL:;:ittfL8000CCL8CCGC888C8G1G8888Li1L808Gtt1ii;;;;;i11ttff11i;;;;;;f000;;;1tfG::;;;:i1L8C00GGCGfCCCGGGffCCL1iif88CLLf800Cff11ii;iiitft1ii;i1i;;;;;;;;:::;;;;;;iiii11tfC08CC8LGG88CLGCLGGif1LfttLGLffLLG8Gftii;:::;i;::;;;;;tiiii;;iii:;iiii;1ii1111if8088C8G888CC88LGt1fft1itt11t11ttttt1i;;;;;;;;:::;;i1;;1fii11iii111ftf111111fCC;C08C8888888G8LtfLfftfft111iiiiiiii;;;;;;;;;;::::;ii1tt1;1i11tt11tttftGCCC8CCG01t00080C880CCfLGGLLLft111iiiiiiiiiii;;;;;iiii11tttt1tffGt1LtffffffffffffCGC8CCC88fC800888CCCCGGLLftt11iiiiiiiiii11t11ttttftttfffffttffGGGLGLGfffffffffffLLGti1tCLG808088CCCCCGLftt1111iiiiiiii1ttffffLLLffffffffLf11tfGGGLGGffffttfttttfGCC1i;;itL888G8CCGCGLftt1111i1iiiiii1tLLffffffLftttttttttLGLLGLGLLGLftttt11111tLG8CC0ii1ttfLC0CCC8CLft11111111iiii11tGCGffi18CL1111iiiiii111LGGGLLGLfttt11111tLGC00000000;,;C8GGGGGfft11111111111it1fCCLti1C100ttt1iiiiiiiii11tffffftttt1111fLGG000000000  .1GCCCCGGLffttttttt11111ttCCft1t8080ttt1iiiiiii1i11ttttttt111111GGGG0000000000 ., iGLCCC8CGGGLLftttftttttt88ftttG8LLfft1iiiiii1111tttt1t111111C8CC000000000000 .,  LCC8888888CCCCGLLffffttGCfttttG8Cft11ii11ii111111111111iiG00000000000000000.:,   LC8808880888888CGGLLfLLCft1ttttttt11111iiiiiiii111iiii00000000000000000000ii,,;i:CCCC80088880008888888CCCLi1111t11t1i;;;;;iii11iiiG00000000000000000000880tt:  :;;G880GLGCCG8C8888888888CCCCCGtiiii1;:;i1iif8800000000800000000000000008001itfLfLLfL8C88088C88CGC88CCCCGGCC888888C8880800000000000008088888088000000000000LLLLLLLLLGCGLCCCC800888C8CGGCCCCCCCG88880800000000808888888800000000000000000000\n\0"

message:
	.string "Hello, World!\n\0"

displayStr:
	movl 4(%esp), %ebx
	movl 8(%esp), %ecx
	movl $0, %edi
	movb $0xf0, %ah
nextChar:
	movb (%ebx), %al
	movw %ax, %gs:(%edi)
	addl $2, %edi
	incl %ebx
	loopnz nextChar # loopnz decrease ecx by 1
	ret
