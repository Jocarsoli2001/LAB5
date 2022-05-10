/**
 * Laboratorio 5
 *
 * José Santizo (20185)
 *
 * Electrónica digital 2
 *
 */

//--------------------------------- Incluir librerías ----------------------------------
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"


//-------------------------------- Varibles de programa --------------------------------
int Valor_boton = 0;
int i = 0;

//------------------------------- Prototipo de funciones -------------------------------
void delay(uint32_t msec);
void setup(void);


//--------------------------------------- Main -----------------------------------------
int main(void)
{
    // ---------------------------------------------------------------------------------
    // Setup
    // ---------------------------------------------------------------------------------
    setup();

    // ---------------------------------------------------------------------------------
    // Loop principal
    // ---------------------------------------------------------------------------------

	while(1){

	    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0){
	        // Limpiar todos los pines para que comience sin luz
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
            delay(200);

            // Color verde y verde intermitente
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
            delay(2000);

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
            delay(500);

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
            delay(500);

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
            delay(500);

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
            delay(600);

            // Color amarillo
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0A);
            delay(2000);

            // Color Rojo
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x02);
            delay(3000);
	    }


	}
}

//-------------------------------- Prototipo de funciones -----------------------------
//**************************************************************************************************************
// Función de delay en milisegundos
//**************************************************************************************************************
void delay(uint32_t msec)
{
    for (i = 0; i < msec; i++)
    {
        SysCtlDelay(10000);                                                                         // 1 ms de delay
    }

}

//**************************************************************************************************************
// Función de setup para todo el sistema
//**************************************************************************************************************
void setup(void)
{
    // Asignación del reloj del sistema
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);               // 50 MHz

    // Habilitación del reloj para puertos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);                                                    // Puerto F

    // Pines como entradas y salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);                       // Pines 1, 2 y 3 del puerto F como salida
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);        // Pin 4 como entrada con weak pull up
}
