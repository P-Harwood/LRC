/*
 * Trap_integrator.c
 *
 *  Created on: 22 Oct 2025
 *      Author: a5126135
 */

#include <hpf.h>

int32_t Hpf_run(Hpf *p_hpf, int32_t input)
{
    if (!p_hpf->run_already)
    {
        p_hpf->run_already = true;
        p_hpf->prev_input      = input;
        p_hpf->state = (int32_t)0;
    }
    else
    {
        /* 64768/65536 = 0.98828125 coefficient in Q16 format*/
        p_hpf->state *= (int32_t)64768;
        p_hpf->state >>= 16;
        p_hpf->state += (input - p_hpf->prev_input) << 16;

        p_hpf->prev_input = input;
    }

    return p_hpf->state >> 16;
}

void Hpf_reset(Hpf *p_hpf)
{
    p_hpf->prev_input = (int32_t)0;
    p_hpf->state = (int32_t)0;
    p_hpf->run_already = false;
}
