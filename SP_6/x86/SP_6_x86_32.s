# Вариант 9. Дана матрица размера N x M. Вывести количество строк столбцов,
# элементы которых монотонно возрастают, монотонно убывают

	
	#   4(%ebp) [4]  old %ebp
    #   0(%ebp) [4] 
    #  -4(%ebp) [4]  n
    #  -8(%ebp) [4]  m
    # -12(%ebp) [4]  matrix
    # -16(%ebp) [4]  i
    # -20(%ebp) [4]  j
    # -24(%ebp) [4]  flag1  
	# -28(%ebp) [4]  flag2
	# -32(%ebp) [4]  temp_res
	# -36(%ebp) [4]  temp M
	# -40(%ebp) [4]  result 
	# -44(%ebp) [4]  0 (%esp)

    .globl main
main:

	pushl %ebp
    movl %esp, %ebp
    #pushl %esi
    subl $44, %esp

	pushl $FirstMsg
    calll  printf
    addl  $4, %esp
	
	leal -8(%ebp), %edx
	pushl %edx
    leal -4(%ebp), %edx
	pushl %edx
    leal FormatPairIn, %edx
    pushl %edx
    calll scanf
	addl $12, %esp
	
	pushl $SecondMsg
    calll  printf
    addl  $4, %esp
	
	movl -4(%ebp), %eax
    imull -8(%ebp), %eax
    imull $4, %eax
    movl %eax, (%esp)
    calll malloc
    movl %eax, -12(%ebp)
	
	movl $0, %eax
	movl $0, %ebx
	movl $0, %ecx
	movl $0, %edx
	movl $0, -20(%ebp)
	movl $0, -16(%ebp)
	
	
# Считывание матрицы
# for (-16(%ebp) = 0; -16(%ebp) < -4(%ebp); -16(%ebp)++)
first_loop_I:
	# for (-20(%ebp) = 0; -20(%ebp) < -8(%ebp); -20(%ebp)++)
	second_loop_I:
		movl -20(%ebp), %eax
		cmp %eax, -8(%ebp)
		je second_exit_I
		
		movl -16(%ebp), %ecx
		imull -8(%ebp), %ecx
		addl -20(%ebp), %ecx
		imull $4, %ecx
		addl -12(%ebp), %ecx
		pushl %ecx
		pushl $FormatDigitIn
		calll scanf
		addl $8, %esp
		
		movl -20(%ebp), %eax
		addl $1, %eax
		movl %eax, -20(%ebp)

		jmp second_loop_I

	second_exit_I:
		movl -16(%ebp), %eax
		addl $1, %eax
		movl %eax, -16(%ebp)
		movl -16(%ebp), %eax
		cmp %eax, -4(%ebp)
		je first_exit_I
		
		movl $0, %ebx
		movl %ebx, -20(%ebp)
		
		jmp first_loop_I
first_exit_I:	
	
	movl $0, -16(%ebp)
	movl $0, -20(%ebp)
	
# Вывод матрицы
# for (-16(%ebp) = 0; -16(%ebp) < -4(%ebp); -16(%ebp)++)
	first_loop_W:
		# for (-20(%ebp) = 0; -20(%ebp) < -8(%ebp); -20(%ebp)++)
		second_loop_W:
			movl -20(%ebp), %eax
			cmp %eax, -8(%ebp)
			je second_exit_W
			
			movl -16(%ebp), %ecx
			imull -8(%ebp), %ecx
			addl -20(%ebp), %ecx
			imull $4, %ecx
			addl -12(%ebp), %ecx
			movl (%ecx), %edx
			pushl %edx
			pushl $FormatDigitOut
			calll printf
			addl $8, %esp
			
			movl -20(%ebp), %eax
			addl $1, %eax
			movl %eax, -20(%ebp)

			jmp second_loop_W

		second_exit_W:
			pushl $NewLine
			calll printf
			addl $4, %esp
			
			movl -16(%ebp), %eax
			addl $1, %eax
			movl %eax, -16(%ebp)
			movl -16(%ebp), %eax
			cmp %eax, -4(%ebp)
			je first_exit_W
			
			movl $0, %ebx
			movl %ebx, -20(%ebp)
			
			jmp first_loop_W
	first_exit_W:	

	
	movl $0, -16(%ebp)
	movl $0, -20(%ebp)
	movl $0, -24(%ebp)
	movl $0, -28(%ebp)
	movl $0, -32(%ebp)
	movl -8(%ebp), %eax
	subl $1, %eax
	movl %eax, -36(%ebp)
	movl $0, -40(%ebp)
	
#  Проверка строк
#  if (matrix[m * i + j - 1] > matrix[m * i + j])
#  if (matrix[-16(%ebp) * -8(%ebp) + -20(%ebp) - 1] > matrix[-16(%ebp) * -8(%ebp) + -20(%ebp)])

#  if (matrix[m * i + j - 1] < matrix[m * i + j])
#  if (matrix[(-16(%ebp) + 1) * -8(%ebp) - -20(%ebp) - 1] < matrix[(-16(%ebp) + 1) * -8(%ebp) - -20(%ebp)])
	
	# for (-16(%ebp) = 0; -16(%ebp) < -4(%ebp); -16(%ebp)++)
	first_loop_G:
		# for (-20(%ebp) = 1; -20(%ebp) < -8(%ebp); -20(%ebp)++)
		second_loop_G:
			movl -20(%ebp), %eax
			cmp %eax, -36(%ebp)
			je second_exit_G
			
			movl -20(%ebp), %eax
			addl $1, %eax
			movl %eax, -20(%ebp)
			
			movl -16(%ebp), %eax
			imull -8(%ebp), %eax
			addl -20(%ebp), %eax
			movl %eax, %ebx
			subl $1, %eax
			imull $4, %eax
			imull $4, %ebx
			
			addl -12(%ebp), %eax
			addl -12(%ebp), %ebx
			
			movl (%eax), %ecx
			movl (%ebx), %edx
			
			cmp %ecx, %edx
						
			jg change_flag_1_G
			
			continue_loop_G:
				
				movl -16(%ebp), %eax
				addl $1, %eax
				imull -8(%ebp), %eax
				subl -20(%ebp), %eax
				
				movl %eax, %ebx
				subl $1, %eax
				imull $4, %eax
				imull $4, %ebx
				
				addl -12(%ebp), %eax
				addl -12(%ebp), %ebx
				
				movl (%eax), %ecx
				movl (%ebx), %edx
				
				cmp %ecx, %edx
			
				jl change_flag_2_G

				jmp second_loop_G

		second_exit_G:
		
			movl -24(%ebp), %eax
			cmp $0, %eax
			jne nextop_G
			
			movl -32(%ebp), %eax
			addl $1, %eax
			movl %eax, -32(%ebp)
			
			jmp end_of_loop_G

			nextop_G:
				movl -28(%ebp), %eax
				cmp $0, %eax
				jne end_of_loop_G
				
				movl -32(%ebp), %eax
				addl $1, %eax
				movl %eax, -32(%ebp)
			
			end_of_loop_G:
			
				movl -16(%ebp), %eax
				addl $1, %eax
				movl %eax, -16(%ebp)
				cmp %eax, -4(%ebp)
				je first_exit_G
				
				movl $0, %ebx
				movl %ebx, -20(%ebp)
				
				movl $0, %ebx
				movl %ebx, -24(%ebp)
				
				movl $0, %ebx
				movl %ebx, -28(%ebp)
				
				jmp first_loop_G
				
				change_flag_1_G:
					movl -24(%ebp), %eax
					addl $1, %eax
					movl %eax, -24(%ebp)
					jmp continue_loop_G
				
				change_flag_2_G:
					movl -28(%ebp), %eax
					addl $1, %eax
					movl %eax, -28(%ebp)
					jmp second_loop_G
			
	first_exit_G:	
	
	
	movl -32(%ebp), %eax
	movl %eax, -40(%ebp)
	
	movl $0, -16(%ebp)
	movl $0, -20(%ebp)
	movl $0, -24(%ebp)
	movl $0, -28(%ebp)
	movl $0, -32(%ebp)
	movl -4(%ebp), %eax
	subl $1, %eax
	movl %eax, -36(%ebp)
	
#  Проверка столбцов
	

#  if (matrix[j * m + i] > matrix[(j - 1) * m + i])
#  if (matrix[-8(%ebp) * (-20(%ebp) - 1) + -16(%ebp)] > matrix[-8(%ebp) * -20(%ebp) + -16(%ebp)])

#  if (matrix[j * m + i] < matrix[(j - 1) * m + i])
#  if (matrix[-8(%ebp) * (-4(%ebp) - -20(%ebp) - 1) + -16(%ebp)] > matrix[-8(%ebp) * (-4(%ebp) - -20(%ebp)) + -16(%ebp)])
	
	# for (-16(%ebp) = 0; -16(%ebp) < $-8(%ebp); -16(%ebp)++)
	first_loop_V:
		# for (-20(%ebp) = 1; -20(%ebp) < -4(%ebp); -20(%ebp)++)
		second_loop_V:
			movl -20(%ebp), %eax
			cmp %eax, -36(%ebp)
			je second_exit_V
			
			movl -20(%ebp), %eax
			addl $1, %eax
			movl %eax, -20(%ebp)
			
			movl -20(%ebp), %eax
			subl $1, %eax
			imull -8(%ebp), %eax
			addl -16(%ebp), %eax
			imull $4, %eax
			
			movl -20(%ebp), %ebx
			imull -8(%ebp), %ebx
			addl -16(%ebp), %ebx
			imull $4, %ebx
			
			addl -12(%ebp), %eax
			addl -12(%ebp), %ebx
			
			movl (%eax), %ecx
			movl (%ebx), %edx
			
			cmp %ecx, %edx
						
			jg change_flag_1_V
							
			continue_loop_V:
				
				movl -4(%ebp), %eax
				subl -20(%ebp), %eax
				subl $1, %eax
				imull -8(%ebp), %eax
				addl -16(%ebp), %eax
				imull $4, %eax
				
				movl -4(%ebp), %ebx
				subl -20(%ebp), %ebx
				imull -8(%ebp), %ebx
				addl -16(%ebp), %ebx
				imull $4, %ebx
				
				addl -12(%ebp), %eax
				addl -12(%ebp), %ebx
				
				movl (%eax), %ecx
				movl (%ebx), %edx
				
				cmp %ecx, %edx
				
			
				jl change_flag_2_V

				jmp second_loop_V

		second_exit_V:
		
			movl -24(%ebp), %eax
			cmp $0, %eax
			jne nextop_V
			
			movl -32(%ebp), %eax
			addl $1, %eax
			movl %eax, -32(%ebp)
			
			jmp end_of_loop_V

			nextop_V:
				movl -28(%ebp), %eax
				cmp $0, %eax
				jne end_of_loop_V
				
				movl -32(%ebp), %eax
				addl $1, %eax
				movl %eax, -32(%ebp)
			
			end_of_loop_V:
				
				movl -16(%ebp), %eax
				addl $1, %eax
				movl %eax, -16(%ebp)
				cmp %eax, -8(%ebp)
				je first_exit_V
				
				movl $0, %ebx
				movl %ebx, -20(%ebp)
				
				movl $0, %ebx
				movl %ebx, -24(%ebp)
				
				movl $0, %ebx
				movl %ebx, -28(%ebp)
				
				jmp first_loop_V
				
				change_flag_1_V:
					movl -24(%ebp), %eax
					addl $1, %eax
					movl %eax, -24(%ebp)
					jmp continue_loop_V
				
				change_flag_2_V:
					movl -28(%ebp), %eax
					addl $1, %eax
					movl %eax, -28(%ebp)
					jmp second_loop_V
			
	first_exit_V:
	
#  Обработка и вывод результатов
	
	movl -40(%ebp), %eax
	addl -32(%ebp), %eax
	pushl %eax
	pushl $FormatDigitOut
	calll printf
	addl  $8, %esp
	
	pushl $NewLine
	calll printf
	addl  $4, %esp
	
	addl $44, %esp
    popl %ebp
	
	retl
	
	
	
	.data
	
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
	