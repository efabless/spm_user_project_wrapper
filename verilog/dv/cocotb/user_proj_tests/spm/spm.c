#define A 0
#define X 1
#define Y0 2
#define Y1 3
#define status 4

#include <firmware_apis.h>

void multiply(int I0, int I1, int *Z){
    USER_writeWord(I0,A);
    USER_writeWord(I1,X);
    while (USER_readWord(status) == 0); // wait until multiplication is finshed
    Z[0] = USER_readWord(Y0);
    Z[1] = USER_readWord(Y1);
}

void main(){
    // Enable managment gpio as output to use as indicator for finishing configuration  
    ManagmentGpio_outputEnable();
    ManagmentGpio_write(1);
    GPIOs_configure(32,GPIO_MODE_MGMT_STD_OUTPUT);
    GPIOs_configure(33,GPIO_MODE_MGMT_STD_OUTPUT);
    GPIOs_configure(34,GPIO_MODE_MGMT_STD_OUTPUT);
    GPIOs_configure(35,GPIO_MODE_MGMT_STD_OUTPUT);
    User_enableIF();
    GPIOs_loadConfigs(); // load the configuration 
    int z[2];
    multiply(5,7, z);
    int pass = 1;
    if (z[0] != 35 | z[1] != 0){
        pass = 0;
    }
    multiply(20,20,z);
    if (z[0] != 20*20 | z[1] != 0){
        pass =0;
    }
    multiply(0x200,0x3000800,z);
    // if (result != 0x200*0x3000800){
    if (z[0] != 0x100000 | z[1] != 0x6){
        pass =0;
    }
    if (pass){
        GPIOs_writeHigh(0xA);
    }else{
        GPIOs_writeHigh(0xF);
    }
    ManagmentGpio_write(0); // start counting from 0
    return;
}
