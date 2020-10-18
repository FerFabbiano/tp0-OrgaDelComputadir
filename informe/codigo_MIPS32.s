	.file	1 "utils.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.data
	.align	2
	.type	modTable, @object
	.size	modTable, 12
modTable:
	.word	0
	.word	2
	.word	1
	.rdata
	.align	2
	.type	base64_table, @object
	.size	base64_table, 65
base64_table:
	.ascii	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123"
	.ascii	"456789+/\000"
	.text
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	__b64_isvalidchar
	.type	__b64_isvalidchar, @function
__b64_isvalidchar:
	.frame	$fp,24,$31		# vars= 8, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	move	$2,$4
	sb	$2,24($fp)
	sb	$0,8($fp)
	lb	$2,24($fp)
	slt	$2,$2,48
	bne	$2,$0,$L2
	nop

	lb	$2,24($fp)
	slt	$2,$2,58
	beq	$2,$0,$L2
	nop

	li	$2,1			# 0x1
	sb	$2,8($fp)
$L2:
	lb	$2,24($fp)
	slt	$2,$2,65
	bne	$2,$0,$L3
	nop

	lb	$2,24($fp)
	slt	$2,$2,91
	beq	$2,$0,$L3
	nop

	li	$2,1			# 0x1
	sb	$2,8($fp)
$L3:
	lb	$2,24($fp)
	slt	$2,$2,97
	bne	$2,$0,$L4
	nop

	lb	$2,24($fp)
	slt	$2,$2,123
	beq	$2,$0,$L4
	nop

	li	$2,1			# 0x1
	sb	$2,8($fp)
$L4:
	lb	$3,24($fp)
	li	$2,43			# 0x2b
	beq	$3,$2,$L5
	nop

	lb	$3,24($fp)
	li	$2,47			# 0x2f
	beq	$3,$2,$L5
	nop

	lb	$3,24($fp)
	li	$2,61			# 0x3d
	bne	$3,$2,$L6
	nop

$L5:
	li	$2,1			# 0x1
	sb	$2,8($fp)
$L6:
	lbu	$2,8($fp)
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	__b64_isvalidchar
	.size	__b64_isvalidchar, .-__b64_isvalidchar
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	__len_base64_decode_output
	.type	__len_base64_decode_output, @function
__len_base64_decode_output:
	.frame	$fp,24,$31		# vars= 8, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	sw	$5,28($fp)
	lw	$2,24($fp)
	bne	$2,$0,$L9
	nop

	move	$2,$0
	b	$L10
	nop

$L9:
	sw	$0,8($fp)
	lw	$2,28($fp)
	srl	$3,$2,2
	move	$2,$3
	sll	$2,$2,1
	addu	$2,$2,$3
	sw	$2,8($fp)
	sw	$0,12($fp)
	b	$L11
	nop

$L13:
	lw	$3,24($fp)
	lw	$2,12($fp)
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,61			# 0x3d
	bne	$3,$2,$L12
	nop

	lw	$2,8($fp)
	addiu	$2,$2,-1
	sw	$2,8($fp)
$L12:
	lw	$2,12($fp)
	addiu	$2,$2,1
	sw	$2,12($fp)
$L11:
	lw	$3,12($fp)
	lw	$2,28($fp)
	sltu	$2,$3,$2
	bne	$2,$0,$L13
	nop

	lw	$2,8($fp)
$L10:
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	__len_base64_decode_output
	.size	__len_base64_decode_output, .-__len_base64_decode_output
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	__len_base64_encode_output
	.type	__len_base64_encode_output, @function
__len_base64_encode_output:
	.frame	$fp,24,$31		# vars= 8, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	lw	$2,24($fp)
	sw	$2,8($fp)
	lw	$4,24($fp)
	li	$2,-1431699456			# 0xffffffffaaaa0000
	ori	$2,$2,0xaaab
	multu	$4,$2
	mfhi	$2
	srl	$3,$2,1
	move	$2,$3
	sll	$2,$2,1
	addu	$2,$2,$3
	subu	$3,$4,$2
	beq	$3,$0,$L15
	nop

	lw	$4,24($fp)
	li	$2,-1431699456			# 0xffffffffaaaa0000
	ori	$2,$2,0xaaab
	multu	$4,$2
	mfhi	$2
	srl	$3,$2,1
	move	$2,$3
	sll	$2,$2,1
	addu	$2,$2,$3
	subu	$3,$4,$2
	lw	$2,8($fp)
	subu	$2,$2,$3
	addiu	$2,$2,3
	sw	$2,8($fp)
$L15:
	lw	$3,8($fp)
	li	$2,-1431699456			# 0xffffffffaaaa0000
	ori	$2,$2,0xaaab
	multu	$3,$2
	mfhi	$2
	srl	$2,$2,1
	sw	$2,8($fp)
	lw	$2,8($fp)
	sll	$2,$2,2
	sw	$2,8($fp)
	lw	$2,8($fp)
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	__len_base64_encode_output
	.size	__len_base64_encode_output, .-__len_base64_encode_output
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	__write
	.type	__write, @function
__write:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,32($fp)
	sw	$5,36($fp)
	sw	$6,40($fp)
	lw	$2,32($fp)
	beq	$2,$0,$L18
	nop

	lw	$2,36($fp)
	bne	$2,$0,$L19
	nop

$L18:
	li	$2,1			# 0x1
	b	$L20
	nop

$L19:
	lw	$7,32($fp)
	lw	$6,40($fp)
	li	$5,1			# 0x1
	lw	$4,36($fp)
	lw	$2,%call16(fwrite)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,fwrite
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$2,$0
$L20:
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	__write
	.size	__write, .-__write
	.align	2
	.set	nomips16
	.set	nomicromips
	.ent	__processFile
	.type	__processFile, @function
__processFile:
	.frame	$fp,48,$31		# vars= 16, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,48($fp)
	sw	$5,52($fp)
	sw	$6,56($fp)
	sw	$7,60($fp)
	sw	$0,24($fp)
	sw	$0,32($fp)
	sw	$0,28($fp)
	b	$L22
	nop

$L26:
	lbu	$2,67($fp)
	beq	$2,$0,$L23
	nop

	addiu	$2,$fp,32
	move	$6,$2
	lw	$5,28($fp)
	lw	$4,56($fp)
	lw	$2,%got(encodeBase64)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,encodeBase64
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,24($fp)
	b	$L24
	nop

$L23:
	addiu	$2,$fp,32
	move	$6,$2
	lw	$5,28($fp)
	lw	$4,56($fp)
	lw	$2,%got(decodeBase64)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,decodeBase64
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,24($fp)
$L24:
	lw	$2,24($fp)
	beq	$2,$0,$L25
	nop

	lw	$2,32($fp)
	move	$6,$2
	lw	$5,24($fp)
	lw	$4,52($fp)
	lw	$2,%got(__write)($28)
	addiu	$2,$2,%lo(__write)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,__write
1:	jalr	$25
	nop

	lw	$28,16($fp)
	lw	$4,24($fp)
	lw	$2,%call16(free)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,free
1:	jalr	$25
	nop

	lw	$28,16($fp)
$L25:
	lw	$6,60($fp)
	move	$5,$0
	lw	$4,56($fp)
	lw	$2,%call16(memset)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,memset
1:	jalr	$25
	nop

	lw	$28,16($fp)
$L22:
	lw	$7,48($fp)
	lw	$6,60($fp)
	li	$5,1			# 0x1
	lw	$4,56($fp)
	lw	$2,%call16(fread)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,fread
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,28($fp)
	lw	$2,28($fp)
	bne	$2,$0,$L26
	nop

	lw	$3,28($fp)
	li	$2,-1			# 0xffffffffffffffff
	bne	$3,$2,$L27
	nop

	li	$2,1			# 0x1
	b	$L29
	nop

$L27:
	move	$2,$0
$L29:
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	__processFile
	.size	__processFile, .-__processFile
	.align	2
	.globl	encodeBase64
	.set	nomips16
	.set	nomicromips
	.ent	encodeBase64
	.type	encodeBase64, @function
encodeBase64:
	.frame	$fp,88,$31		# vars= 56, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-88
	sw	$31,84($sp)
	sw	$fp,80($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,88($fp)
	sw	$5,92($fp)
	sw	$6,96($fp)
	lw	$2,88($fp)
	bne	$2,$0,$L31
	nop

	move	$2,$0
	b	$L32
	nop

$L31:
	lw	$4,92($fp)
	lw	$2,%got(__len_base64_encode_output)($28)
	addiu	$2,$2,%lo(__len_base64_encode_output)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,__len_base64_encode_output
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,36($fp)
	lw	$2,36($fp)
	addiu	$2,$2,1
	move	$5,$2
	li	$4,1			# 0x1
	lw	$2,%call16(calloc)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,calloc
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,40($fp)
	lw	$2,40($fp)
	bne	$2,$0,$L33
	nop

	move	$2,$0
	b	$L32
	nop

$L33:
	sw	$0,24($fp)
	sw	$0,28($fp)
	b	$L34
	nop

$L39:
	lw	$2,24($fp)
	addiu	$3,$2,1
	sw	$3,24($fp)
	lw	$3,88($fp)
	addu	$2,$3,$2
	lb	$2,0($2)
	andi	$2,$2,0x00ff
	sw	$2,44($fp)
	lw	$3,24($fp)
	lw	$2,92($fp)
	sltu	$2,$3,$2
	beq	$2,$0,$L35
	nop

	lw	$2,24($fp)
	addiu	$3,$2,1
	sw	$3,24($fp)
	lw	$3,88($fp)
	addu	$2,$3,$2
	lb	$2,0($2)
	b	$L36
	nop

$L35:
	move	$2,$0
$L36:
	sw	$2,48($fp)
	lw	$3,24($fp)
	lw	$2,92($fp)
	sltu	$2,$3,$2
	beq	$2,$0,$L37
	nop

	lw	$2,24($fp)
	addiu	$3,$2,1
	sw	$3,24($fp)
	lw	$3,88($fp)
	addu	$2,$3,$2
	lb	$2,0($2)
	b	$L38
	nop

$L37:
	move	$2,$0
$L38:
	sw	$2,52($fp)
	lw	$2,44($fp)
	sll	$3,$2,16
	lw	$2,48($fp)
	sll	$2,$2,8
	addu	$3,$3,$2
	lw	$2,52($fp)
	addu	$2,$3,$2
	sw	$2,56($fp)
	lw	$2,56($fp)
	srl	$2,$2,18
	andi	$2,$2,0x3f
	sw	$2,60($fp)
	lw	$2,56($fp)
	srl	$2,$2,12
	andi	$2,$2,0x3f
	sw	$2,64($fp)
	lw	$2,56($fp)
	srl	$2,$2,6
	andi	$2,$2,0x3f
	sw	$2,68($fp)
	lw	$2,56($fp)
	andi	$2,$2,0x3f
	sw	$2,72($fp)
	lw	$3,40($fp)
	lw	$2,28($fp)
	addu	$2,$3,$2
	lw	$3,%got(base64_table)($28)
	addiu	$4,$3,%lo(base64_table)
	lw	$3,60($fp)
	addu	$3,$4,$3
	lbu	$3,0($3)
	seb	$3,$3
	sb	$3,0($2)
	lw	$2,28($fp)
	addiu	$2,$2,1
	lw	$3,40($fp)
	addu	$2,$3,$2
	lw	$3,%got(base64_table)($28)
	addiu	$4,$3,%lo(base64_table)
	lw	$3,64($fp)
	addu	$3,$4,$3
	lbu	$3,0($3)
	seb	$3,$3
	sb	$3,0($2)
	lw	$2,28($fp)
	addiu	$2,$2,2
	lw	$3,40($fp)
	addu	$2,$3,$2
	lw	$3,%got(base64_table)($28)
	addiu	$4,$3,%lo(base64_table)
	lw	$3,68($fp)
	addu	$3,$4,$3
	lbu	$3,0($3)
	seb	$3,$3
	sb	$3,0($2)
	lw	$2,28($fp)
	addiu	$2,$2,3
	lw	$3,40($fp)
	addu	$2,$3,$2
	lw	$3,%got(base64_table)($28)
	addiu	$4,$3,%lo(base64_table)
	lw	$3,72($fp)
	addu	$3,$4,$3
	lbu	$3,0($3)
	seb	$3,$3
	sb	$3,0($2)
	lw	$2,28($fp)
	addiu	$2,$2,4
	sw	$2,28($fp)
$L34:
	lw	$3,24($fp)
	lw	$2,92($fp)
	sltu	$2,$3,$2
	bne	$2,$0,$L39
	nop

	sw	$0,32($fp)
	b	$L40
	nop

$L41:
	lw	$2,32($fp)
	lw	$3,36($fp)
	subu	$2,$3,$2
	addiu	$2,$2,-1
	lw	$3,40($fp)
	addu	$2,$3,$2
	li	$3,61			# 0x3d
	sb	$3,0($2)
	lw	$2,32($fp)
	addiu	$2,$2,1
	sw	$2,32($fp)
$L40:
	lw	$4,92($fp)
	li	$2,-1431699456			# 0xffffffffaaaa0000
	ori	$2,$2,0xaaab
	multu	$4,$2
	mfhi	$2
	srl	$3,$2,1
	move	$2,$3
	sll	$2,$2,1
	addu	$2,$2,$3
	subu	$3,$4,$2
	lw	$2,%got(modTable)($28)
	sll	$3,$3,2
	addiu	$2,$2,%lo(modTable)
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,32($fp)
	slt	$2,$2,$3
	bne	$2,$0,$L41
	nop

	lw	$4,40($fp)
	lw	$2,%call16(strlen)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,strlen
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$3,$2
	lw	$2,96($fp)
	sw	$3,0($2)
	lw	$2,40($fp)
$L32:
	move	$sp,$fp
	lw	$31,84($sp)
	lw	$fp,80($sp)
	addiu	$sp,$sp,88
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	encodeBase64
	.size	encodeBase64, .-encodeBase64
	.align	2
	.globl	decodeBase64
	.set	nomips16
	.set	nomicromips
	.ent	decodeBase64
	.type	decodeBase64, @function
decodeBase64:
	.frame	$fp,320,$31		# vars= 288, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-320
	sw	$31,316($sp)
	sw	$fp,312($sp)
	move	$fp,$sp
	.cprestore	16
	sw	$4,320($fp)
	sw	$5,324($fp)
	sw	$6,328($fp)
	lw	$2,320($fp)
	bne	$2,$0,$L43
	nop

	move	$2,$0
	b	$L57
	nop

$L43:
	lw	$2,320($fp)
	sw	$2,36($fp)
	addiu	$2,$fp,52
	li	$6,256			# 0x100
	li	$5,-1			# 0xffffffffffffffff
	move	$4,$2
	lw	$2,%call16(memset)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,memset
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$0,24($fp)
	b	$L45
	nop

$L46:
	lw	$2,%got(base64_table)($28)
	addiu	$3,$2,%lo(base64_table)
	lw	$2,24($fp)
	addu	$2,$3,$2
	lbu	$2,0($2)
	move	$4,$2
	lw	$2,24($fp)
	andi	$3,$2,0x00ff
	addiu	$2,$fp,24
	addu	$2,$2,$4
	sb	$3,28($2)
	lw	$2,24($fp)
	addiu	$2,$2,1
	sw	$2,24($fp)
$L45:
	lw	$2,24($fp)
	sltu	$2,$2,64
	bne	$2,$0,$L46
	nop

	lw	$5,324($fp)
	lw	$4,320($fp)
	lw	$2,%got(__len_base64_decode_output)($28)
	addiu	$2,$2,%lo(__len_base64_decode_output)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,__len_base64_decode_output
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,40($fp)
	lw	$2,40($fp)
	addiu	$2,$2,1
	move	$5,$2
	li	$4,1			# 0x1
	lw	$2,%call16(calloc)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,calloc
1:	jalr	$25
	nop

	lw	$28,16($fp)
	sw	$2,44($fp)
	lw	$2,44($fp)
	bne	$2,$0,$L47
	nop

	move	$2,$0
	b	$L57
	nop

$L47:
	sw	$0,28($fp)
	sw	$0,32($fp)
	b	$L48
	nop

$L56:
	lw	$3,320($fp)
	lw	$2,28($fp)
	addu	$2,$3,$2
	lb	$2,0($2)
	move	$4,$2
	lw	$2,%got(__b64_isvalidchar)($28)
	addiu	$2,$2,%lo(__b64_isvalidchar)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,__b64_isvalidchar
1:	jalr	$25
	nop

	lw	$28,16($fp)
	xori	$2,$2,0x1
	andi	$2,$2,0x00ff
	bne	$2,$0,$L58
	nop

	lw	$3,36($fp)
	lw	$2,28($fp)
	addu	$2,$3,$2
	lbu	$2,0($2)
	move	$3,$2
	addiu	$2,$fp,24
	addu	$2,$2,$3
	lbu	$2,28($2)
	sw	$2,48($fp)
	lw	$2,48($fp)
	sll	$2,$2,6
	lw	$3,28($fp)
	addiu	$3,$3,1
	lw	$4,36($fp)
	addu	$3,$4,$3
	lbu	$3,0($3)
	move	$4,$3
	addiu	$3,$fp,24
	addu	$3,$3,$4
	lbu	$3,28($3)
	or	$2,$2,$3
	sw	$2,48($fp)
	lw	$2,28($fp)
	addiu	$2,$2,2
	lw	$3,320($fp)
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,61			# 0x3d
	bne	$3,$2,$L51
	nop

	lw	$2,48($fp)
	sll	$2,$2,6
	b	$L52
	nop

$L51:
	lw	$2,48($fp)
	sll	$2,$2,6
	lw	$3,28($fp)
	addiu	$3,$3,2
	lw	$4,36($fp)
	addu	$3,$4,$3
	lbu	$3,0($3)
	move	$4,$3
	addiu	$3,$fp,24
	addu	$3,$3,$4
	lbu	$3,28($3)
	or	$2,$2,$3
$L52:
	sw	$2,48($fp)
	lw	$2,28($fp)
	addiu	$2,$2,3
	lw	$3,320($fp)
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,61			# 0x3d
	bne	$3,$2,$L53
	nop

	lw	$2,48($fp)
	sll	$2,$2,6
	b	$L54
	nop

$L53:
	lw	$2,48($fp)
	sll	$2,$2,6
	lw	$3,28($fp)
	addiu	$3,$3,3
	lw	$4,36($fp)
	addu	$3,$4,$3
	lbu	$3,0($3)
	move	$4,$3
	addiu	$3,$fp,24
	addu	$3,$3,$4
	lbu	$3,28($3)
	or	$2,$2,$3
$L54:
	sw	$2,48($fp)
	lw	$3,44($fp)
	lw	$2,32($fp)
	addu	$2,$3,$2
	lw	$3,48($fp)
	srl	$3,$3,16
	seb	$3,$3
	sb	$3,0($2)
	lw	$2,28($fp)
	addiu	$2,$2,2
	lw	$3,320($fp)
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,61			# 0x3d
	beq	$3,$2,$L55
	nop

	lw	$2,32($fp)
	addiu	$2,$2,1
	lw	$3,44($fp)
	addu	$2,$3,$2
	lw	$3,48($fp)
	srl	$3,$3,8
	seb	$3,$3
	sb	$3,0($2)
$L55:
	lw	$2,28($fp)
	addiu	$2,$2,3
	lw	$3,320($fp)
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,61			# 0x3d
	beq	$3,$2,$L50
	nop

	lw	$2,32($fp)
	addiu	$2,$2,2
	lw	$3,44($fp)
	addu	$2,$3,$2
	lw	$3,48($fp)
	seb	$3,$3
	sb	$3,0($2)
	b	$L50
	nop

$L58:
	nop
$L50:
	lw	$2,28($fp)
	addiu	$2,$2,4
	sw	$2,28($fp)
	lw	$2,32($fp)
	addiu	$2,$2,3
	sw	$2,32($fp)
$L48:
	lw	$3,28($fp)
	lw	$2,324($fp)
	sltu	$2,$3,$2
	bne	$2,$0,$L56
	nop

	lw	$4,44($fp)
	lw	$2,%call16(strlen)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,strlen
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$3,$2
	lw	$2,328($fp)
	sw	$3,0($2)
	lw	$2,44($fp)
$L57:
	move	$sp,$fp
	lw	$31,316($sp)
	lw	$fp,312($sp)
	addiu	$sp,$sp,320
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	decodeBase64
	.size	decodeBase64, .-decodeBase64
	.align	2
	.globl	encodeFileToBase64
	.set	nomips16
	.set	nomicromips
	.ent	encodeFileToBase64
	.type	encodeFileToBase64, @function
encodeFileToBase64:
	.frame	$fp,48,$31		# vars= 8, regs= 2/0, args= 24, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	.cprestore	24
	sw	$4,48($fp)
	sw	$5,52($fp)
	lw	$2,48($fp)
	beq	$2,$0,$L60
	nop

	lw	$2,52($fp)
	bne	$2,$0,$L61
	nop

$L60:
	li	$2,1			# 0x1
	b	$L63
	nop

$L61:
	li	$6,3			# 0x3
	move	$5,$0
	addiu	$2,$fp,32
	move	$4,$2
	lw	$2,%call16(memset)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,memset
1:	jalr	$25
	nop

	lw	$28,24($fp)
	li	$2,1			# 0x1
	sw	$2,16($sp)
	li	$7,3			# 0x3
	addiu	$2,$fp,32
	move	$6,$2
	lw	$5,52($fp)
	lw	$4,48($fp)
	lw	$2,%got(__processFile)($28)
	addiu	$2,$2,%lo(__processFile)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,__processFile
1:	jalr	$25
	nop

	lw	$28,24($fp)
$L63:
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	encodeFileToBase64
	.size	encodeFileToBase64, .-encodeFileToBase64
	.align	2
	.globl	decodeFileFromBase64
	.set	nomips16
	.set	nomicromips
	.ent	decodeFileFromBase64
	.type	decodeFileFromBase64, @function
decodeFileFromBase64:
	.frame	$fp,48,$31		# vars= 8, regs= 2/0, args= 24, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	.cprestore	24
	sw	$4,48($fp)
	sw	$5,52($fp)
	lw	$2,48($fp)
	beq	$2,$0,$L65
	nop

	lw	$2,52($fp)
	bne	$2,$0,$L66
	nop

$L65:
	li	$2,1			# 0x1
	b	$L68
	nop

$L66:
	li	$6,4			# 0x4
	move	$5,$0
	addiu	$2,$fp,32
	move	$4,$2
	lw	$2,%call16(memset)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,memset
1:	jalr	$25
	nop

	lw	$28,24($fp)
	sw	$0,16($sp)
	li	$7,4			# 0x4
	addiu	$2,$fp,32
	move	$6,$2
	lw	$5,52($fp)
	lw	$4,48($fp)
	lw	$2,%got(__processFile)($28)
	addiu	$2,$2,%lo(__processFile)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,__processFile
1:	jalr	$25
	nop

	lw	$28,24($fp)
$L68:
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	decodeFileFromBase64
	.size	decodeFileFromBase64, .-decodeFileFromBase64
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
