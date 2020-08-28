# Вариант 9. Дана матрица размера N x M. Вывести количество строк столбцов,
# элементы которых монотонно возрастают, монотонно убывают

# CheckG(a0 - sp, s0 - N, s1 - M) функция, проверяющая строки по условию
    .globl CheckG
CheckG:
    addi $sp, $sp, -4        
    sw $ra, ($sp)
	addi $sp, $sp, -4        
    sw $s3, ($sp)
    addi $sp, $sp, -4        
    sw $s6, ($sp)	
    addi $sp, $sp, -4        
    sw $s7, ($sp)    
    addi $sp, $sp, -4        
    sw $s8, ($sp) 
	
    move $s6, $a0                               
    move $s7, $a1      # s7 - N                         
    move $s8, $a2	   # s8 - M
	
#  if (matrix[m * i + j - 1] > matrix[m * i + j])
#  if (matrix[s8 * s0 + s1 - 1] (bgt) matrix[s8 * s0 + s1])

#  if (matrix[m * i + j - 1] < matrix[m * i + j])
#  if (matrix[s8 * s0 + s1 - 1] (blt) matrix[s8 * s0 + s1])

	li $t5, 1
	li $s0, 0
	li $s1, 0
	li $t1, 0
	li $t0, 0
	li $s3, 0
	li $t4, 4
	li $v0, 1
	
# for ($s0 = 0; $s0 < $s7; $s0++)
first_loop_G:
	# for ($s1 = 1; $s1 < $s8; $s1++)
	second_loop_G:
		beq $s1, $s8, second_exit_G
		
		addi $s1, $s1, 1

		li $t0, 1  
		mul $t0, $t0, $s0
		mul $t0, $t0, $s8
		add $t0, $t0, $s1
		sub $t0, $t0, $t5
		mul $t0, $t0, $t4
		add $t0, $t0, $s6
		lw $t0, ($t0)               
		li $t1, 1                  
		mul $t1, $t1, $s0
		mul $t1, $t1, $s8		
		add $t1, $t1, $s1
		mul	$t1, $t1, $t4	
		add $t1, $t1, $s6
		lw $t1, ($t1) 
		
	    bgt $t0, $t1, first_flag_G 
			
		continue_loop_G:  #  if (matrix[(s0 + 1) * s8 - s1 - 1] (blt) matrix[(s0 + 1) * s8 - s1])
			    
			li $t0, 1
			add $t0, $t0, $s0
			mul $t0, $t0, $s8
			sub $t0, $t0, $s1
			sub $t0, $t0, $t5
			mul $t0, $t0, $t4
			add $t0, $t0, $s6
			lw $t0, ($t0)               
			li $t1, 1
			add $t1, $t1, $s0
			mul $t1, $t1, $s8			
			sub $t1, $t1, $s1
			mul $t1, $t1, $t4
			add $t1, $t1, $s6
			lw $t1, ($t1)   
            
			blt $t0, $t1, second_flag_G 
				
			j second_loop_G

	second_exit_G:
				
		bne $t8, $zero, nextop_G
		addi $s3, $s3, 1
		j end_of_loop_G
		nextop_G:
			bne $t9, $zero, end_of_loop_G
			addi $s3, $s3, 1
			
			end_of_loop_G:
				
				addi $s0, $s0, 1
				li $s1, 0  
				li $t8, 0
				li $t9, 0
				
				beq $s0, $s7, first_exit_G
				j first_loop_G
				
				first_flag_G:	
					addi $t8, $t8, 1
					j continue_loop_G
								
				second_flag_G:	
					addi $t9, $t9, 1
					j second_exit_G 
first_exit_G:

		move $v0, $s3

		lw $s8, ($sp)        
		addi $sp, $sp, 4    
		lw $s7, ($sp)        
		addi $sp, $sp, 4 
		lw $s6, ($sp)        
		addi $sp, $sp, 4 
		lw $s3, ($sp)        
		addi $sp, $sp, 4
		lw $ra, ($sp)        
		addi $sp, $sp, 4 
		
		jr $ra
		
		
		
# CheckV(a0 - sp, s0 - N, s1 - M) функция, проверяющая столбцы по условию
    .globl CheckV
CheckV:
    addi $sp, $sp, -4        
    sw $ra, ($sp)
	addi $sp, $sp, -4        
    sw $s3, ($sp)
    addi $sp, $sp, -4        
    sw $s6, ($sp)	
    addi $sp, $sp, -4        
    sw $s7, ($sp)    
    addi $sp, $sp, -4        
    sw $s8, ($sp) 
	
    move $s6, $a0                               
    move $s7, $a1      # s7 - N                         
    move $s8, $a2	   # s8 - M
	move $t2, $s7
	
#  if (matrix[j * m + i] > matrix[(j - 1) * m + i])
#  if (matrix[s1 * s8 + s0] (bgt) matrix[(s1 - 1) * s8 + s0])

#  if (matrix[j * m + i] < matrix[(j - 1) * m + i])
#  if (matrix[s1 * s8 + s0] (blt) matrix[(s1 - 1) * s8 + s0])

	li $t5, 1
	li $s0, 0
	li $s1, 0
	li $t1, 0
	li $t0, 0
	li $s3, 0
	li $t4, 4
	li $v0, 1
	sub $t2, $t2, $t5
	
# for ($s0 = 0; $s0 < $s8; $s0++)
first_loop_V:
	# for ($s1 = 1; $s1 < $s7; $s1++)
	second_loop_V:
		beq $s1, $t2, second_exit_V
		
		addi $s1, $s1, 1 #  if (matrix[s8 * (s1 - 1) + s0] (bgt) matrix[s8 * s1 + s0])

		li $t0, 1  
		li $t6, -1
		add $t6, $t6, $s1
		mul $t0, $t0, $s8
		mul $t0, $t0, $t6
		add $t0, $t0, $s0
		mul $t0, $t0, $t4
		add $t0, $t0, $s6
		lw $t0, ($t0) 		
		
		li $t1, 1                  
		mul $t1, $t1, $s8
		mul $t1, $t1, $s1		
		add $t1, $t1, $s0
		mul $t1, $t1, $t4		
		add $t1, $t1, $s6
		lw $t1, ($t1) 
		
	    bgt $t0, $t1, first_flag_V 
			
		continue_loop_V:  #  if (matrix[s8 * (s7 - s1 - 1) + s0] (bgt) matrix[s8 * (s7 - s1) + s0])
			    
			li $t0, -1			
			add $t0, $s7, $t0			
			sub $t0, $t0, $s1			
			mul $t0, $t0, $s8			
			add $t0, $t0, $s0		
			mul $t0, $t0, $t4			
			add $t0, $t0, $s6
			lw $t0, ($t0) 	
			
			li $t1, 0
			add $t1, $t1, $s7
			sub $t1, $t1, $s1
			mul $t1, $t1, $s8			
			add $t1, $t1, $s0
			mul $t1, $t1, $t4
			add $t1, $t1, $s6
			lw $t1, ($t1)	
            
			blt $t0, $t1, second_flag_V
				
			j second_loop_V

	second_exit_V:
				
		bne $t8, $zero, nextop_V
		addi $s3, $s3, 1
		j end_of_loop_V
		nextop_V:
			bne $t9, $zero, end_of_loop_V
			addi $s3, $s3, 1
			
			end_of_loop_V:
				
				addi $s0, $s0, 1
				li $s1, 0  
				li $t8, 0
				li $t9, 0
				
				beq $s0, $s8, first_exit_V
				j first_loop_V
				
				first_flag_V:	
					addi $t8, $t8, 1
					j continue_loop_V
								
				second_flag_V:	
					addi $t9, $t9, 1
					j second_loop_V 
first_exit_V:

		move $v0, $s3

		lw $s8, ($sp)        
		addi $sp, $sp, 4    
		lw $s7, ($sp)        
		addi $sp, $sp, 4 
		lw $s6, ($sp)        
		addi $sp, $sp, 4 
		lw $s3, ($sp)        
		addi $sp, $sp, 4
		lw $ra, ($sp)        
		addi $sp, $sp, 4 
		
		jr $ra
 

# Write matrix(a0 - sp, s0 - N, s1 - M)
    .globl Write
Write:      
    addi $sp, $sp, -4        
    sw $ra, ($sp)
    addi $sp, $sp, -4        
    sw $s6, ($sp)	
    addi $sp, $sp, -4        
    sw $s7, ($sp)    
    addi $sp, $sp, -4        
    sw $s8, ($sp) 

    move $s6, $a0                               
    move $s7, $a1                               
    move $s8, $a2	
	
	li $s0, 0
	li $s1, 0
	li $t1, 4
	li $t0, 0

	# for ($s0 = 0; $s0 < $s7; $s0++)
	first_loop_write:
		# for ($s1 = 0; $s1 < $s8; $s1++)
		second_loop_write:
			beq $s1, $s8, second_exit_write
			
			li $v0, 1
			mul $t0, $s0, $s8           
            add $t0, $t0, $s1                             
            mul $t0, $t0, $t1           
            add $t0, $s6, $t0 
            lw $a0, ($t0)               
            syscall                     
            li $v0, 4                   
            la $a0, Space              
            syscall                     
			addi $s1, $s1, 1

			j second_loop_write

		second_exit_write:
			addi $s0, $s0, 1
			li $s1, 0
			
			li $v0, 4                   
            la $a0, NewLine              
            syscall  
			
			beq $s0, $s7, first_exit_write
			j first_loop_write
	first_exit_write:

    lw $s8, ($sp)        
    addi $sp, $sp, 4    
    lw $s7, ($sp)        
    addi $sp, $sp, 4 
	lw $s6, ($sp)        
    addi $sp, $sp, 4 
    lw $ra, ($sp)        
    addi $sp, $sp, 4 	
	
    jr $ra


# main
    .globl main
main:
	li $v0, 4                                   
    la $a0, FirstMsg                      
    syscall  

    li $v0, 5                                   
    syscall                                     
    move $s7, $v0              # read s7 - N

    li $v0, 5                                   
    syscall                                     
    move $s8, $v0              # read s8 - M	
	
	li $v0, 4
	la $a0, SecondMsg
	syscall
	
	li $t0, 4
	mul $t0, $t0, $s7                           
    mul $t0, $t0, $s8                           
    sub $sp, $sp, $t0 
	
	li $s0, 0
	li $s1, 0
	li $t1, 4
	li $t0, 0
	
# for ($s0 = 0; $s0 < $s7; $s0++)
first_loop:
	# for ($s1 = 0; $s1 < $s8; $s1++)
	second_loop:
		beq $s1, $s8, second_exit
		
		li $v0, 5             
        syscall                     
        move $t2, $v0
		mul $t0, $s0, $s8
		add $t0, $t0, $s1
		mul $t0, $t0, $t1
		add $t0, $t0, $sp
		sw $t2, ($t0)
		
		addi $s1, $s1, 1

		j second_loop

	second_exit:
		addi $s0, $s0, 1
		li $s1, 0
		beq $s0, $s7, first_exit
		j first_loop
first_exit:	

    move $a0, $sp                               
    move $a1, $s7                               
    move $a2, $s8
	jal Write
	
	move $a0, $sp                               
    move $a1, $s7                               
    move $a2, $s8
	jal CheckV
	move $s2, $v0
	
	move $a0, $sp                               
    move $a1, $s7                               
    move $a2, $s8
	jal CheckG
	move $s1, $v0
	add $s2, $s2, $s1
	
    li $v0, 1
	move $a0, $s2
    syscall
	
	li $v0, 4                   
    la $a0, NewLine              
    syscall  
	

	li $v0, 10                                 
    syscall 
	
	.data
	
FirstMsg:    
    .asciiz "Введите размер матрицы(Два целых числа, M x N): "
	
NewLine:    
    .asciiz "\n"
	
SecondMsg:    
    .asciiz "Введите матрицу(целые числа, по одному элементу): "
	
Space:    
    .asciiz " "