	@ 44(sp) [4] old fp
	@ 40(sp) [4] old lr
	@ 36(sp) [4] old pc
	@ 32(sp) [4] n
	@ 28(sp) [4] m
	@ 24(sp) [4] matrix
    @ 20(sp) [4]    
	@ 16(sp) [4]  
	@ 12(sp) [4]  
	@  8(sp) [4] 
	@  4(sp) [4]   
	@  0(sp) [4]  
	
	.global main
main:
    push {fp, lr, pc}
	
	adr r0, FirstMsg
    bl printf
	
	sub sp, sp, #64                           
    
	mov r2, sp                                 
	add r2, r2, #56
    mov r1, r2                                 
    add r1, r1, #8                               
	adr r0, FormatPairIn
	bl scanf

	adr r0, FormatPairOut
	ldr r2, [sp, #56]
	ldr r1, [sp, #64]
    bl printf
	
	ldr r3, [sp, #56]
	ldr r4, [sp, #64]
	mul r0, r3, r4
	mov r1, #8
	mul r0, r1
	
	mov r1, r0
	adr r0, FormatDigitOut
	bl printf
	
	str r0, [sp, #48]
	bl malloc
	
	@str r0, [sp, #64]
	
	mov r1, sp
	add r1, r1, #48
	adr r0, FormatDigitOut
	bl printf
	
	
	
	mov r8, #0
	mov r9, #0
	
	
	

    mov r0, #0
	add sp, sp, #64
    pop {fp, lr, pc}
	
	bx lr
	
	
	

FirstMsg:    
    .asciz "Введите размер матрицы(Два целых числа, M x N):\n"
	
NewLine:    
    .asciz "\n"
	
SecondMsg:    
    .asciz "Введите матрицу(целые числа, по одному элементу): "
	
Space:    
    .asciz " "
	
FormatPairIn:
    .asciz "%d%d"
	
FormatDigitIn:
    .asciz "%d"
	
FormatDigitOut:
    .asciz "%d "
	
FormatPairOut:
    .asciz "%d %d\n"
	