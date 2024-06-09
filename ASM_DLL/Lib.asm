.data
n qword ?
shift qword ?
.code

; Macro used for calculating current position of processed element since we are working on 1D representation of 2D array
data_offset macro OUT, ROW, COL
    mov OUT, COL       
    imul OUT, n   
    add OUT, ROW      
    shl OUT, 2       
endm

; first we need to calculate mask
; OUTPUT -> RAX, modulo output -> RDX 
; procedure also stores used registers values on stack
; and clean up before the party
init macro
    xor rdx, rdx ; clear EDX register
    mov rax, n ; dividend to eax
    mov rbx, 8 ; divider
    idiv rbx ; RDX contains % 
    
    mov shift, rdx ; Move rdx to shift loop counter
    mov rax, 0FFFFFFFFFFFFFFFFh ; mask value
    movq xmm2, rax ; mask to xmm2
    vpbroadcastd ymm2, xmm2 ; mask to modify
    vpbroadcastd ymm12, xmm2 ; full 8 element mask

    cmp n, 8 ; diffrent handling for diffrent graph size (n e graph_sizes: n < 8 -> small v n > 8 -> large)
    jmp sm_graph

    
       mask_shift:
       cmp shift, 0
       je loop_end

       ; Extract and move
       vextracti128 xmm3, ymm2, 1
       vpsrldq xmm3, xmm3, 4
       vinserti128 ymm2, ymm2, xmm3, 1

       ; Handle lower half of YMM (xmm register)
       cmp shift, 4
       jle mask_shift_end

       ; Shift
       vpsrldq xmm2, xmm2, 4

    mask_shift_end:
       dec shift
       jmp mask_shift

    ; n > 8 case process of calculating desired mask
    sm_graph:
        xor rax, rax ; clear registry
        mov rax, 8 
        sub rax, shift
        mov shift, rax
        jmp mask_shift

    loop_end:
        push rdi
        push r11
        push r12
        push r13
        push r14

        xor rdi, rdi ; rdi is used because of masking
        xor r11, r11 ; help register
        xor r12, r12 ; k
        xor r13, r13 ; i
        xor r14, r14 ; j
endm    

FloydWarshallASM proc
    push rax
    push rbx
    push rdx
    push rcx

    mov n, RDX ; Store N value to variable
    
    init
        
    k_loop:
        cmp r12, n ;  K >= n?
        jge done

        i_loop:
            cmp r13, n ; i >= n?
            jge i_loop_end

            j_loop:
                cmp r14, n ; j >= n?
                jge j_loop_end

                data_offset RDX, r14, r13 ; offset
                vmovdqu ymm4, ymmword ptr [rcx + rdx]  ; Write 8 elements to ymm4 from tab[j][i]
                data_offset RAX, r14, r12 ; offset
                vmovdqu ymm5, ymmword ptr [rcx + rax]  ; Write next 8 elements to ymm5 from  tab[j][k]
                data_offset RAX, r12, r13
                mov r11, [rcx + rax]  ; Write iteration constant element tab[k][i]
                movq xmm6, r11

                vpbroadcastd ymm6, xmm6  ; k point broadcasting 
                vpaddd ymm7, ymm6, ymm5  ; sum
                vpminud ymm8, ymm7, ymm4  ; comparison

                lea rdi, [rcx + rdx] ; effective address (computed) to rdi
                ;mov rdi, rcx
                mov r11, n
                sub r11, r14
                cmp r11, 8
                jge processed_full

                ; processed only part
                vextracti128 xmm9, ymm8, 1 ; Extracting top-half of ymm8 [to save register]
                vextracti128 xmm10, ymm2, 1 ; Extracting top half of mask

                maskmovdqu xmm8, xmm2 ; Saving base elements
                imul r11, 4 ; r11 contains count of saved elements
                add rdx, r11 ; it allows to point to the nearest location after last written item
                lea rdi, [rcx + rdx]
                maskmovdqu xmm9, xmm10 ; Saving top elements

                add r14, r11
                jmp j_loop

                processed_full:
                    vmovdqu ymmword ptr [rcx+rdx], ymm8
                    add r14, 8
                    jmp j_loop

            j_loop_end:
                xor r14, r14
                inc r13
                jmp i_loop
        
        i_loop_end:
            xor r13, r13
            inc r12
            jmp k_loop

   done:
       pop r14
       pop r13
       pop r12
       pop r11
       pop rdi
       pop rcx
       pop rdx
       pop rbx
       pop rax
       ret

FloydWarshallASM endp
end