	/* Section: Data memory
	 * Range: 	[0x20000000-0x20004FFF]
	 */
	.section	.data
counter:
	.word		2666664
	/* Section: Program memory
	 * Range: 	[0x08000000-0x0801FFFF]
	 */
	.section	.text
	.syntax 	unified
	.global 	main

	.equ	RCC_BASE, 0x40021000
	.equ	GPIOA_BASE, 0x40010800
main:
	/* USER CODE BEGIN 1 */
	/* Code to turn-on and turn-off the LD2 (User LED) */
	ldr	r0, =RCC_BASE//			RCC base address
	ldr	r1, [r0, #0x18]//		RCC_APB2ENR register actual value
	mov	r2, #1//			mask value
	orr	r1, r1, r2, lsl #2//	set bit 2 to IO port A clock enable
	str	r1, [r0, #0x18]//		RCC_APB2ENR modified

	ldr	r0, =GPIOA_BASE//		GPIO Port A base address
	mov	r1, r2, lsl #5//		value to set/reset pin 5 of port A (LD2 is PA5)
	str	r1, [r0, #0x14]//		GPIOx_BRR register modified (reset)

	ldr	r1, [r0]//			GPIOx_CRL register actual value
	mov	r2, #3
	mvn	r3, r2, lsl #22//		mask value
	and	r1, r1, r3//			clear bits 23-22 to configure pin as output
	mov	r2, #2
	mvn	r3, r2, lsl #20//		mask value
	and	r1, r1, r3//			clear bit 21 for speed
	str	r1, [r0]//			GPIOx_CRL modified

	ldr	r1, [r0]//			GPIOx_CRL register actual value
	mov	r2, #1//			mask value
	orr	r1, r1, r2, lsl #20//	set bit 20 to select max speed 10MHz
	str	r1, [r0]//			GPIOx_CRL modified

	mov	r2, #1
	mov	r1, r2, lsl #5//		immediate value for bit 5
loopForever:
	str	r1, [r0, #0x10]//		GPIOx_BSRR modified (set/Turn-ON LD2)
	bl	delay_1s//			call delay subroutine
	str	r1, [r0, #0x14]//		GPIOx_BRR modified (Turn-OFF LD2)
	bl	delay_1s//			call delay subroutine
	b	loopForever//			infinite cycle

	/* 1 second delay subroutine */
delay_1s:
	push	{r1}//				save to stack r1 value
	ldr	r2, =counter//			read memory address of counter variable
	ldr	r1, [r2]//			read counter value
decrement:
	subs	r1, r1, #1//			decrement counter
	bne	decrement//			if counter!=0 decrement again
	nop//					no operation (1 cycle)
	pop	{r1}//				return from stack r1 value
	bx	lr//				return from subroutine
	/* USER CODE END 1 */
