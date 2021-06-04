/*
 * operation.c
 *
 *  Created on: April 6th, 2021
 *      Author: Kelly Fernandez
 */

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "operation.h"
#include "global_define.h"
#include "global_variables.h"

void Set_buffer_dutycycle(float M, float M_ci)
{

	//control for unipolar modulation, charge injection modulation, and saturation for both

   /* if(M >= 0) //if Vab > 0, modulate positive cycle half bridge, and set lower switch of negative half cycle half-bridge to be on.
	{
	    if (M > 0.97)
	     {
	         duty_cycle1 = 0.97; //If modulation index is greater than or close to 1, saturate to 0.95
	     }
	     else if (M < 0.03)
	     {
	         duty_cycle1 = 0.03; //If modulation index is close to 0, saturate to 0.05
	     }
	     else
	     {
	         duty_cycle1 = M;  //If modulation index doesn't need to be saturated
	     }
	    duty_cycle2 = 0.01; //set lower switch (S4) of negative half cycle half-bridge to be on.

	}

    //if Vab < 0, modulate negative cycle half bridge, and set lower switch of positive half cycle half-bridge to be on.
	else
	   {
	        if (M < -0.97)
	         {
	             duty_cycle2 = 0.97; //If modulation index is greater than or close to 1, saturate to 0.95
	         }
	         else if (M > -0.03)
	         {
	             duty_cycle2 = 0.03; //If modulation index is close to 0, saturate to 0.05
	         }
	         else
	         {
	             duty_cycle2 = -1*M;  //If modulation index doesn't need to be saturated
	         }
	        duty_cycle1 = 0.01;    //set lower switch (S3) of positive half cycle half-bridge to be on.
	        duty_cycle_ci = 0;  //If Vab < 0, set charge injection duty cycle to 0 to avoid circuit from entering CCM

	    }


*/
    //Saturation of charge injection duty cycle
    if(M > 0)
    {
        if(M_ci > 0.97)
        {
            duty_cycle_ci = 0.97;
        }
        else if (M_ci < 0.03)
        {
            duty_cycle_ci = 0.03;
        }
        else
        {
            duty_cycle_ci = M_ci;
        }
    }
    else
    {
        duty_cycle_ci = 0;
    }

    /*if(M > 0)
    {
       duty_cycle_ci = duty_test;
    }
    else
    {
        duty_cycle_ci = 0;
    }*/

	duty_cycle1 = 0.5*(1+M);


    if (duty_cycle1 > 0.98)
        {
            duty_cycle1 = 0.98;
        }
        else if (duty_cycle1 < 0.02)
        {
            duty_cycle1 = 0.02;
        }
    duty_cycle2 = 1 - duty_cycle1;

	//SetEPwmB_X_DutyCycle(EPwm_CH1, 0.5); //secondary half-bridge
	//SetEPwmA_X_DutyCycle(EPwm_CH2, 0.5); //primary half-bridge

    // Set the duty cycle for buffer ePWMs
    SetEPwmB_X_DutyCycle(EPwm_CH1, duty_cycle2); //secondary half-bridge
    SetEPwmA_X_DutyCycle(EPwm_CH2, duty_cycle1); //primary half-bridge
    //SetEPwmA_X_DutyCycle(EPwm_CH3, 0.5); //charge injection switch
    SetEPwmA_X_DutyCycle(EPwm_CH3, duty_cycle_ci);
    //SetEPwmA_X_DutyCycle(EPwm_CH3, duty_test);

}

void SetEPwmA_X_DutyCycle(EPwm_Channel pwm_chan, float duty_cycle)
{
	ePWM[pwm_chan]->CMPA.bit.CMPA = (ePWM[pwm_chan]->TBPRD)*duty_cycle; // Set the duty cycle count (in # of switching cycles) on the CMPA register
}

void SetEPwmB_X_DutyCycle(EPwm_Channel pwm_chan, float duty_cycle)
{
    ePWM[pwm_chan]->CMPB.bit.CMPB = (ePWM[pwm_chan]->TBPRD)*duty_cycle; // Set the duty cycle count (in # of switching cycles) on the CMPA register
}

