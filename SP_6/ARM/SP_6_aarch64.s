	// 96(sp) [8] old x19
	// 88(sp) [8] old x30
	// 80(sp) [8] old x21
	// 72(sp) [8] old x20
	// 64(sp) [8] n
	// 56(sp) [8] m
	// 48(sp) [8] matrix -> x15
    // 40(sp) [8]    
	// 32(sp) [8]  
	// 24(sp) [8]  
	// 16(sp) [8] 
	//  8(sp) [8]   
	//  0(sp) [8]  
	
	.global main
main:
    str x19, [sp, #-8]!
	str x20, [sp, #-8]!
    str x21, [sp, #-8]!
	str x30, [sp, #-8]!
	
	adr x0, FirstMsg
    bl printf
	
	sub sp, sp, #64
	
	
    mov x2, fp                                 
    mov x1, x2                                 
    add x1, x1, #-8                                 
	adr x0, FormatPairIn
	bl scanf
	
	adr x0, SecondMsg
    bl printf
	
	ldr w20, [fp]
	ldr w21, [fp, #-8]
	mul w23, w20, w21
	mov w20, #8
	mul w23, w23, w20
	sub sp, sp, w23
	
	mov x23, #0
	mov x24, #0
	
// Ввод матрицы
// for (x23 = 0; x23 < [fp]; x23++)
first_loop_R:
	// for (x24 = 0; x24 < [fp, #-8]; x24++)
	second_loop_R:
		ldr w20, [fp, #-8]
		cmp w24, w20
		beq second_exit_R
		
		mov w20, w23
		ldr w21, [fp]
		mul w20, w20, w21
		add w20, w20, w24
		mov w21, #8
		mul w20, w20, w21
		mov x15, sp
		add x20, x20, x15
		
		mov x1, x20		
		adr x0, FormatDigitIn
		bl scanf
		
		add w24, w24, #1

		b second_loop_R

	second_exit_R:		
		add w23, w23, #1
		mov w24, #0
		ldr w20, [fp]
		cmp w23, w20
		beq first_exit_R
		b first_loop_R
first_exit_R:	


	mov w23, #0
	mov w24, #0

// Вывод матрицы
// for (x23 = 0; x23 < [fp]; x23++)
first_loop_W:
	// for (x24 = 0; x24 < [fp, #-8]; x24++)
	second_loop_W:
		ldr w20, [fp, #-8]
		cmp w24, w20
		beq second_exit_W
		
		mov w20, w23
		ldr w21, [fp]
		mul w20, w20, w21
		add w20, w20, w24
		mov w21, #8
		mul w20, w20, w21
		mov x15, sp
		add x20, x20, x15
		
		ldr x1, [x20]		
		adr x0, FormatDigitOut
		bl printf
		
		add w24, w24, #1

		b second_loop_W

	second_exit_W:
		adr x0, NewLine
		bl printf
		
		add w23, w23, #1
		mov w24, #0
		ldr w20, [fp]
		cmp w23, w20
		beq first_exit_W
		b first_loop_W
first_exit_W:


	mov w23, #0
	mov w24, #0
	mov w25, #0
	mov w26, #0
	mov w27, #0
	mov x28, #0
	
	
//  Проверка строк
//  if (matrix[m * i + j - 1] > matrix[m * i + j])
//  if (matrix[[sp, #-8] * w23 + w24 - 1] > matrix[[sp, #-8] * w23 + w24])

//  if (matrix[m * i + j - 1] < matrix[m * i + j])
//  if (matrix[[sp, #-8] * w23 + w24 - 1] < matrix[[sp, #-8] * w23 + w24])
	
	// for (x23 = 0; x23 < [fp]; x23++)
	first_loop_G:
		// for (x24 = 1; x24 < [fp, #-8]; x24++)
		second_loop_G:
			ldr w19, [fp, #-8]
			
			add w24, w24, #1
			
			mov w20, w24
			
			cmp w19, w20
			
			b.eq second_exit_G
			
			ldr w19, [fp, #-8]
			mul w19, w19, w23
			add w19, w19, w24
			mov w20, w19
			sub w19, w19, #1
			mov w21, #8
			mul w19, w19, w21
			mul w20, w20, w21
			mov x21, sp
			add x19, x19, x21
			add x20, x20, x21
			
			ldr x21, [x19]
			ldr x22, [x20]
			
			cmp w21, w22
						
			b.gt change_flag_1_G
			
			continue_loop_G:
				
				ldr w19, [fp, #-8]
				mul w19, w19, w23
				add w19, w19, w24
				mov w20, w19
				sub w19, w19, #1
				mov w21, #8
				mul w19, w19, w21
				mul w20, w20, w21
				mov x15, sp
				add x19, x19, x15
				add x20, x20, x15
				
				ldr x21, [x19]
				ldr x22, [x20]
				
				cmp w21, w22
			
				b.lt change_flag_2_G

				b second_loop_G

		second_exit_G:
		
			mov w20, w25
			mov w21, #0
			cmp w20, w21
			b.ne nextop_G

			add w27, w27, #1
			
			b end_of_loop_G

			nextop_G:
				mov w20, w26
				mov w21, #0
				cmp w20, w21
				b.ne end_of_loop_G	
			
				add x27, x27, #1
			
			end_of_loop_G:
			
				mov w25, #0
				mov w26, #0
				mov w24, #0
			
				add w23, w23, #1
				ldr w19, [fp]
								
				cmp w19, w23
				b.eq first_exit_G
				
				b first_loop_G
				
				change_flag_1_G:
					add w25, w25, #1
					b continue_loop_G
				
				change_flag_2_G:
					add w26, w26, #1
					b second_loop_G
			
	first_exit_G:
	
	
	mov w23, #0
	mov w24, #0
	mov w25, #0
	mov w26, #0
	mov x28, #0
	
	
//  Проверка столбцов
//  if (matrix[j * m + i] > matrix[(j - 1) * m + i])
//  if (matrix[[sp, #-8] * w24 + w23] > matrix[[sp, #-8] * (w24 - 1) + w23])

//  if (matrix[j * m + i] < matrix[(j - 1) * m + i])
//  if (matrix[[sp, #-8] * w24 + w23] < matrix[[sp, #-8] * (w24 - 1) + w23])
	
	// for (x23 = 0; x23 < [fp, #-8]; x23++)
	first_loop_V:
		// for (x24 = 1; x24 < [fp]; x24++)
		second_loop_V:
			ldr w19, [fp]
			
			add w24, w24, #1
			
			mov w20, w24
			
			cmp w19, w20
			
			b.eq second_exit_V
			
			ldr w19, [fp, #-8]
			mul w19, w19, w24
			add w19, w19, w23
			mov w20, w24
			sub w20, w20, #1
			ldr w21, [fp, #-8]
			mul w20, w20, w21
			add w20, w20, w23
			
			mov w21, #8
			mul w19, w19, w21
			mul w20, w20, w21
			
			mov x21, sp
			add x19, x19, x21
			add x20, x20, x21
			
			ldr x21, [x19]
			ldr x22, [x20]
			
			cmp w21, w22
						
			b.gt change_flag_1_V
			
			continue_loop_V:
				
				ldr w19, [fp, #-8]
				mul w19, w19, w24
				add w19, w19, w23
				mov w20, w24
				sub w20, w20, #1
				ldr w21, [fp, #-8]
				mul w20, w20, w21
				add w20, w20, w23
				
				mov w21, #8
				mul w19, w19, w21
				mul w20, w20, w21
				
				mov x21, sp
				add x19, x19, x21
				add x20, x20, x21			
				
				ldr x21, [x19]
				ldr x22, [x20]
				
				cmp w21, w22
			
				b.lt change_flag_2_V

				b second_loop_V

		second_exit_V:
		
			mov w20, w25
			mov w21, #0
			cmp w20, w21
			b.ne nextop_V

			add w27, w27, #1
			
			b end_of_loop_V

			nextop_V:
				mov w20, w26
				mov w21, #0
				cmp w20, w21
				b.ne end_of_loop_V	
			
				add x27, x27, #1
			
			end_of_loop_V:
			
				add w23, w23, #1
				ldr w19, [fp, #-8]
								
				cmp w19, w23
				b.eq first_exit_V
				
				mov w20, #0
				mov w25, #0
				mov w26, #0
				mov w24, #0
				
				b first_loop_V
				
				change_flag_1_V:
					add w25, w25, #1
					b continue_loop_V
				
				change_flag_2_V:
					add w26, w26, #1
					b second_loop_V
			
	first_exit_V:

	mov x1, x27
	adr x0, FormatDigitOut
	bl printf
	
	adr x0, NewLine
	bl printf
	
	
	ldr w3, [fp]
	ldr w4, [fp, #-8]
	mul w0, w3, w4
	mov w1, #8
	mul w0, w0, w1
	add sp, sp, w0
	
	add sp, sp, #64

	ldr x30, [sp], #8
	ldr x21, [sp], #8
	ldr x20, [sp], #8
	ldr x19, [sp], #8	

    mov x0, #0                                  

    ret
	
	
	

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
	