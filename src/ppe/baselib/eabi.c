/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/ppe/baselib/eabi.c $                                      */
/*                                                                        */
/* OpenPOWER OnChipController Project                                     */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2019                             */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// These variables are declared in linker script to keep track of
// global constructor pointer functions and sbss section.

// assuming link script instructs the c++ compiler to put
// ctor_start_address and ctor_end_address in .rodata

/*
extern void (*ctor_start_address)() __attribute__ ((section (".rodata")));
extern void (*ctor_end_address)() __attribute__ ((section (".rodata")));

extern uint64_t _sbss_start __attribute__ ((section (".sbss")));
extern uint64_t _sbss_end __attribute__ ((section (".sbss")));
*/

// This function will be used to do any C++ handling required before doing
// any main job. Call to this function should get generated by compiler.

// TODO via RTC 152070
// We are also initialising sbss section to zero this function.
// Though it does not do any harm as of now, it is better  if we use loader
// or linker script to zero init sbss section. This way we will be future
// garded if pk  boot uses some static/global data  initialised to
// false in future.

__attribute__((weak)) void __eabi()
{
    // This is the default eabi and can be overridden.
    // eabi environment is already set up by the PK kernel
    // Call static C++ constructors if you use C++ global/static objects

    /*
        do
        {
            // Initialise sbss section
            uint64_t* startAddr = &_sbss_start;

            while ( startAddr != &_sbss_end )
            {
                *startAddr = 0;
                startAddr++;
            }

            // Call global constructors
            void(**ctors)() = &ctor_start_address;

            while( ctors != &ctor_end_address)
            {
                (*ctors)();
                ctors++;
            }

        }
        while (0);
    */

}

#ifdef __cplusplus
} // end extern "C"
#endif
