void kernel_main() {
    const char *str = "Hello! This Is Valkyrie Kernel v0.0.1";
    char *vidptr = (char*)0xb8000; 
    unsigned int i = 0;

    while(str[i] != '\0') {
        vidptr[i*2] = str[i];    
        vidptr[i*2+1] = 0x07;  
        i++;  
    }
}