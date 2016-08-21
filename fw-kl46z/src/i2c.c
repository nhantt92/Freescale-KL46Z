#include "i2c.h"

void I2C_Set_Tx_Mode(I2C_Type* p)
{
    p->C1 |= I2C_C1_TX_MASK;

}
void I2C_Set_Rx_Mode(I2C_Type* p)
{
    p->C1 &= ~I2C_C1_TX_MASK;
}

void I2C_Set_Slave_Mode(I2C_Type* p)
{
    p->C1  &= ~I2C_C1_MST_MASK;
}
void I2C_Set_Master_Mode(I2C_Type* p)
{
    p->C1  |=  I2C_C1_MST_MASK;
}

// i2c general

void I2C_Give_Nack(I2C_Type* p)
{
    p->C1 |= I2C_C1_TXAK_MASK;
}
void I2C_Give_Ack(I2C_Type* p)
{
    p->C1 &= ~I2C_C1_TXAK_MASK;
}
void I2C_Repeated_Start(I2C_Type* p)
{
    p->C1     |= 0x04;
}
void I2C_Write_Byte(I2C_Type* p, uint8_t data)
{
    p->D = data;
}
unsigned char I2C_Read_Byte(I2C_Type* p)
{
    return p->D;
}
void I2C_Start(I2C_Type* p)
{
    I2C_Set_Master_Mode(p);
    I2C_Set_Tx_Mode(p);
}
void I2C_Stop(I2C_Type* p)
{
    I2C_Set_Slave_Mode(p);
    I2C_Set_Rx_Mode(p);
}
void I2C_Wait(I2C_Type* p)
{
    // wait flag
    while((p->S & I2C_S_IICIF_MASK)==0);

    // clear flag
    p->S |= I2C_S_IICIF_MASK;
}
unsigned char I2C_Get_Ack(I2C_Type* p)
{
    if((p->S & I2C_S_RXAK_MASK) == 0)
        return 1;
    else
        return 0;
}

// -------------------------------------------------
void I2C0_Init(I2C_Type* p)   //Acelerometro
{
  
   SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
   SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTE_MASK;

#ifdef FRDM_REVA
    PORTC->PCR[8] = PORT_PCR_MUX(2);
    PORTC->PCR[9] = PORT_PCR_MUX(2);
#else  
   PORTE->PCR[24] = PORT_PCR_MUX(5);
   PORTE->PCR[25] = PORT_PCR_MUX(5);
#endif

    p->F  = 0x14; // baudrate
    p->C1 = 0x80; // enable IIC
}

void I2C_Deinit(I2C_Type* p)
{
    p->C1 = 0x00;
    
    SIM->SCGC4 &= ~SIM_SCGC4_I2C1_MASK;
}


void I2C_Init(I2C_Type* p)   //Magnetometro
{
    SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;

   //SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    
      // configure GPIO for I2C function
    //PORTE_PCR24 = PORT_PCR_MUX(5);
    //PORTE_PCR25 = PORT_PCR_MUX(5);

    PORTC->PCR[10] = PORT_PCR_MUX(2);
    PORTC->PCR[11] = PORT_PCR_MUX(2);

    
    p->F  = 0x14; // baudrate
    p->C1 = 0x80; // enable IIC
}


