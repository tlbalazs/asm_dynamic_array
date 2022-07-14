#include<iostream>
using namespace std;
int main()
{
    int n = 0;
    char nChar[] = "n=";
    char format[] = "%d";
    const char* nPause[] = { "pause" };
    int* dynamicArr; //= new int[(int)malloc(n * sizeof(int))];

    _asm
    {
        lea eax, nChar
        push eax
        call printf
        pop eax
        lea  eax, n
        push eax
        lea  eax, format
        push eax
        call scanf_s
        pop eax
        pop eax

        mov eax, 4 //integer stores on 4 bytes
        imul eax, n //reserve n*4 byte
        push eax //EAX on top of the Heap
        call dword ptr malloc
        add esp, 4 //clear the stack
        mov dynamicArr, eax //first item of the array is the returned value of EAX

        mov ecx, n //max count of the loop variable
        mov ebx, 1

        dyn_upload:
            mov [eax], ebx; //write value of EBX to EAXs memory address
            inc ebx;
            add eax, 4; //increase EAXs memory address with 4 byte
        loop dyn_upload; //loop until ecx = 0


        mov ecx, n //max count of the loop variable, with ECX register you have not use the CMP to add a condition
        mov ebx, 1

        mov edx, dynamicArr

        dyn_loop:
            mov al, [edx]
            push ecx
            push edx
            //push eax
            mov eax, dynamicArr
            push eax
            call printf
            add esp, 4
            pop edx
            pop ecx
            inc edx
            inc ebx
       loop dyn_loop; //loop until ecx = 0


    }


//for (int i = 0; i < n; i++) cout << dynamicArr[i] << endl;;
    //free the memory
    _asm
    {
        push dynamicArr
        call dword ptr free
        add esp, 4
    }
     
    //call system function with "pause"
    _asm
    {
        push nPause
        call dword ptr system
        pop ebx
    }
    return 0;
}
