.intel_syntax noprefix
//  AES-128 encryption sequence.
//  The data block is in xmm15.
//  Registers xmm0–xmm10 hold the round keys(from 0 to 10 in this order).
//  In the end, xmm15 holds the encryption result. 
AES_Encrypt128:
    pxor xmm15, xmm0 //  Whitening step (Round 0)
    aesenc xmm15, xmm1 //  Round 1
    aesenc xmm15, xmm2 //  Round 2
    aesenc xmm15, xmm3 //  Round 3
    aesenc xmm15, xmm4 //  Round 4
    aesenc xmm15, xmm5 //  Round 5
    aesenc xmm15, xmm6 //  Round 6
    aesenc xmm15, xmm7 //  Round 7
    aesenc xmm15, xmm8 //  Round 8
    aesenc xmm15, xmm9 //  Round 9
    aesenclast xmm15, xmm10 

//  AES-192 decryption sequence.
 //  The data is in xmm15.
 //  Registers xmm12 – xmm0 hold the decryption round keys.
 //  (the decryption round keys are derived from the encryption round keys by
 //  passing them (except for the first and the last) through the
 //  InvMixColumns transformation.)
 //  In the end - xmm15 holds the decryption result
AES_Decrypt128:
    pxor xmm15, xmm10 //  First xor(consuming round keys in reverse order)
    aesdec xmm15, xmm9 //  Round 3
    aesdec xmm15, xmm8 //  Round 4
    aesdec xmm15, xmm7 // Round 5
    aesdec xmm15, xmm6 // Round 6
    aesdec xmm15, xmm5 // Round 7
    aesdec xmm15, xmm4 //  Round 8
    aesdec xmm15, xmm3 //  Round 9
    aesdec xmm15, xmm2 //  Round 10
    aesdec xmm15, xmm1 //  Round 11
    aesdeclast xmm15, xmm0 //  Round 12 

//  Cipher key is stored in “Key”. For example,
//  Key 0x0f0e0d0c0b0a09080706050403020100
//  The key scheduled to be stored in the array Key_Schedule.
Key_Expand:
    movdqu xmm1, XMMWORD PTR Key
    movdqu XMMWORD PTR Key_Schedule, xmm1
    mov rcx, OFFSET Key_Schedule+16
    aeskeygenassist xmm2, xmm1, 0x1
    call key_expansion_128
    aeskeygenassist xmm2, xmm1, 0x2
    call key_expansion_128
    aeskeygenassist xmm2, xmm1, 0x4
    call key_expansion_128
    aeskeygenassist xmm2, xmm1, 0x8
    call key_expansion_128
    aeskeygenassist xmm2, xmm1, 0x10
    call key_expansion_128
    aeskeygenassist xmm2, xmm1, 0x20
    call key_expansion_128
    aeskeygenassist xmm2, xmm1, 0x40
    call key_expansion_128
    aeskeygenassist xmm2, xmm1, 0x80
    call key_expansion_128
    aeskeygenassist xmm2, xmm1, 0x1b
    call key_expansion_128
    aeskeygenassist xmm2, xmm1, 0x36
    call key_expansion_128 
    jmp END 
key_expansion_128:
    pshufd xmm2, xmm2, 0xff
    vpslldq xmm3, xmm1, 0x4
    pxor xmm1, xmm3
    vpslldq xmm3, xmm1, 0x4
    pxor xmm1, xmm3
    vpslldq xmm3, xmm1, 0x4
    pxor xmm1, xmm3
    pxor xmm1, xmm2
    movdqu XMMWORD PTR [rcx], xmm1
    add rcx, 0x10
    ret
END: 